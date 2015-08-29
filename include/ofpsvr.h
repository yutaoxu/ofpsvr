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

#ifndef OFPSVR_H_ICWCQ40G
#define OFPSVR_H_ICWCQ40G

#define _GNU_SOURCE
/* Get a clean slate of DBEUG macros */
#undef ENABLE_DEBUG
#undef DISABLE_DEBUG
#undef MRB_DEBUG
#undef NDEBUG
#undef HTTP_PARSER_STRICT

#ifdef OFPSVR_DEBUG
#define ENABLE_DEBUG
#define MRB_DEBUG
#define HTTP_PARSER_STRICT 1
#else
#define NDEBUG
#define DISABLE_DEBUG
#define HTTP_PARSER_STRICT 0
#endif /* end of #ifdef OFPSVR_DEBUG */

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#define snprintf c99_snprintf
#endif

#define WRITELOG(...) printf("{%d} ",(int)time(0));printf(__VA_ARGS__);fflush(stdout);

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stddef.h>

#include <sys/select.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/msg.h>
#include <sys/mman.h>
#include <netdb.h>
#include <netinet/in.h>
#include <time.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <microhttpd.h>

#include <mysql/mysql.h>
#include <assert.h>
#include <setjmp.h> 

#include <stdio.h>
#include <mruby.h>
#include <mruby/compile.h>
#include <mruby/string.h>
#include <mruby/error.h>

#define POSTBUFFERSIZE  512
#define OFPSVR_VERSION  8902
#define OFPSVR_PID_FILE "/var/run/ofpsvr.pid"
#define OFPSVR_LOG_FILE "/var/log/ofpsvr.log"

#define OFPSVR_ERRNO_MAP(XX)                                                  \
        XX(-1, "malloc() failed, probably due to memory insufficiency")       \
        XX(-2, "a crucial libuv call failed")

struct Comment
{
  char *content;
  struct Comment *next;
};

struct Resource
{
  char *filename;
  unsigned long sz;
  struct MHD_Response *response;
  struct Resource *next;
};

struct Article
{
  long posted_at;
  char *rfc_posted_at;
  
  pthread_mutex_t hit_related_lock;
  int hit_count;
  
  struct Resource *resources;
  int resource_count;
  
  char *title;
  char *introduction;
  char *body;
  
  pthread_mutex_t comment_related_lock;
  int comment_count;
  struct Comment *comments;
  struct MHD_Response *response;
  size_t page_sz;
};

// *** Global Variables ***
// FIXME: Remove these global var's

extern char *asset_host;

extern struct Article **articles;
extern int articles_len;

extern struct Resource *resources;

extern struct MHD_Response *response_404;
extern struct MHD_Response *response_500;
extern struct MHD_Response *response_index;
extern struct MHD_Response *response_favicon;

extern unsigned char favicon_ico[];
extern unsigned int favicon_ico_len;

extern unsigned long cache_size;
extern int cache_size_silent;
extern int running;

extern mrb_state *mrb;
extern struct RClass *mrb_ofpsvr;

// *** Global Functions ***

void add_comment(struct Article *a,struct Comment *c);

char *fill_content(char *name,char *email,char *website,char *body, long posted_at, int number);

int regenerate(struct Article *x,int id);

void prepare_response_404();
void prepare_response_500();
void prepare_response_index();
void prepare_response_favicon();

struct MHD_Response *generate_blog_response();
struct MHD_Response *generate_blog_response_rss();

int handler (void *cls, struct MHD_Connection *connection,
       const char *url, const char *method,
       const char *version, const char *upload_data,
       size_t *upload_data_size, void **con_cls);

void request_completed (void *cls, struct MHD_Connection *connection,
            void **con_cls, enum MHD_RequestTerminationCode toe);

// mruby Functions
mrb_value ofpsvr_uid(mrb_state *mrb, mrb_value obj);
mrb_value ofpsvr_gid(mrb_state *mrb, mrb_value obj);
mrb_value ofpsvr_halt(mrb_state *mrb, mrb_value obj);
mrb_value ofpsvr_substantiate(mrb_state *mrb, mrb_value obj);

// Main flow control
void terminate();
void substantiate();

MYSQL *ofpsvr_real_connect(MYSQL *mysql);

/* error */
void ofpsvr_fatal(int errono);
void ofpsvr_location_stderr(const char* file, int line);

#endif

