/*
 * P.S.V.R 的软件实验室
 * 版权所有 (C) 2009-2015  P.S.V.R
 * 
 * 本程序为自由软件；您可依据自由软件基金会所发表的 GNU 通用公共授权条款，对本程序进行
 * 再发布和/或修改；无论您依据的是本授权的第三版，还是（您可选的）任一日后发行的版本。
 * 
 * 本程序是基于实用的目的而加以发布的，然而并不承担任何担保责任；亦不对适售性或特定目的
 * 的适用性做出默示性担保。详情请参照 GNU 通用公共授权。
 * 
 * 您应该已经收到了附随于本程序的 GNU 通用公共授权的副本；如果没有，请参照
 * <http://www.gnu.org/licenses/>.
 * 
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
