/*
 * OF P.S.V.R
 * Copyright (c) 2015 P.S.V.R
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "ofpsvr.h"

MYSQL *ofpsvr_real_connect(MYSQL * mysql)
{
        char *host = getenv("OFPSVR_DB_HOST");
        char *user = getenv("OFPSVR_DB_USER");
        char *passwd = getenv("OFPSVR_DB_PASSWD");
        char *db = getenv("OFPSVR_DB_DB");
        if (!host || !user || !passwd || !db) {
                WRITELOG("Please set these environment variables: \
OFPSVR_DB_HOST, OFPSVR_DB_USER, OFPSVR_DB_PASSWD, OFPSVR_DB_DB\n");
                exit(EXIT_FAILURE);
        }
        return mysql_real_connect(mysql, host, user, passwd, db, 0, NULL, 0);
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
        if (!ofpsvr_real_connect(&my)) {
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
