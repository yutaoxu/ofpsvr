/*
 * OF P.S.V.R
 * Copyright (C) 2009-2015  P.S.V.R
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ofpsvr.h"

#include <openssl/rand.h>
#include <openssl/sha.h>
#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>

MYSQL *ofpsvr_connect_mysql(MYSQL * mysql)
{
        char *host = getenv("OFPSVR_DB_HOST");
        char *user = getenv("OFPSVR_DB_USER");
        char *passwd = getenv("OFPSVR_DB_PASSWD");
        char *db = getenv("OFPSVR_DB_DB");
        if (NULL == host || NULL == user || NULL == passwd || NULL == db) {
                WRITELOG("Please set these environment variables: \
OFPSVR_DB_HOST, OFPSVR_DB_USER, OFPSVR_DB_PASSWD, OFPSVR_DB_DB\n");
                exit(EXIT_FAILURE);
        }
        return mysql_real_connect(mysql, host, user, passwd, db, 0, NULL, 0);
}

void ofpsvr_connect_redis()
{
        char *hostname = getenv("OFPSVR_REDIS_HOST");
        char *port_str = getenv("OFPSVR_REDIS_PORT");
        int port;

        if (NULL == hostname || NULL == port_str) {
                WRITELOG("Please set these environment variables: \
OFPSVR_REDIS_HOST, OFPSVR_REDIS_PORT\n");
                exit(EXIT_FAILURE);
        }

        port = atoi(port_str);

        struct timeval timeout = { 1, 500000 }; // 1.5 seconds
        ofpsvr_redis = redisConnectWithTimeout(hostname, port, timeout);
        if (ofpsvr_redis == NULL || ofpsvr_redis->err) {
            if (ofpsvr_redis) {
                WRITELOG("Connection error: %s\n", ofpsvr_redis->errstr);
                redisFree(ofpsvr_redis);
            } else {
                WRITELOG("Connection error: can't allocate redis context\n");
            }
            exit(EXIT_FAILURE);
        }
}
        
void substantiate()
{
        MYSQL my;
        for (int i = 0; i < articles_len; ++i) {
                WRITELOG("articles[%d]->hit_count = %d\n", i,
                         articles[i]->hit_count);
        }
        WRITELOG("Now dumping hit_count data\n");
        printf("Connecting DB...");
        fflush(stdout);
        if (!mysql_init(&my)) {
                WRITELOG("mysql_init failed!\n");
                exit(EXIT_FAILURE);
        }
        if (!ofpsvr_connect_mysql(&my)) {
                WRITELOG("mysql_real_connect failed!\n");
                if (mysql_errno(&my)) {
                        WRITELOG("error %d: %s\n", mysql_errno(&my),
                                 mysql_error(&my));
                }
                exit(EXIT_FAILURE);
        }
        if (mysql_set_character_set(&my, "utf8")) {
                WRITELOG("mysql_set_character_set failed!");
                exit(EXIT_FAILURE);
        }
        printf("OK\n");
        for (int i = 0; i < articles_len; ++i) {
                printf("Dumping #%d...", i);
                fflush(stdout);
                char *sql;
                if (asprintf
                    (&sql,
                     "UPDATE ofpsvr_articles SET `hit_count` = '%d' WHERE `id`=%d LIMIT 1",
                     articles[i]->hit_count, i) < 0) {
                        WRITELOG("asprintf failed!");
                        continue;
                }
                if (mysql_query(&my, sql)) {
                        WRITELOG("UPDATE error %d: %s\n", mysql_errno(&my),
                                 mysql_error(&my));
                        free(sql);
                        continue;
                }
                free(sql);
                if (0 == mysql_affected_rows(&my)) {
                        printf("OK but didn't change\n");
                        fflush(stdout);
                } else if (mysql_affected_rows(&my) > 1) {
                        WRITELOG("mysql_affected_rows > 1!\n");
                } else {
                        printf("OK\n");
                        fflush(stdout);
                }
        }
        mysql_close(&my);
}

char *ofpsvr_timestr(long now)
{
        struct tm ts;
        char *buf;
        // Adjust to +8 Beijing TZ
        now += 28800;
        if (!(buf = malloc(200))) {
                WRITELOG("malloc in ofpsvr_timestr failed!\n");
                exit(EXIT_FAILURE);
        }
        gmtime_r(&now, &ts);
        strftime(buf, 200, "%Y年%-m月%-d日 %H:%M:%S", &ts);
        return buf;
}

// Remember to free(random_bytes)
unsigned char *random_bytes(int length) {
    unsigned char *random_bytes = NULL;

    random_bytes = malloc((size_t)length + 1);
    if (! random_bytes) {
        WRITELOG("could not allocate space for random_bytes...\n");
        exit(EXIT_FAILURE);
    }

    if (! RAND_bytes(random_bytes, length)) {
        WRITELOG("could not get random bytes...\n");
        exit(EXIT_FAILURE);
    }

    *(random_bytes + length) = '\0';
    return random_bytes;
}

// Remember to free(buff)
char *base64(const unsigned char *input, int length)
{
  BIO *bmem, *b64;
  BUF_MEM *bptr;

  b64 = BIO_new(BIO_f_base64());
  bmem = BIO_new(BIO_s_mem());
  b64 = BIO_push(b64, bmem);
  BIO_write(b64, input, length);
  BIO_flush(b64);
  BIO_get_mem_ptr(b64, &bptr);

  char *buff = (char *)malloc(bptr->length);
  memcpy(buff, bptr->data, bptr->length - 1);
  buff[bptr->length - 1] = 0;

  BIO_free_all(b64);

  return buff;
}
