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

#ifndef OFPSVR_H_ICWCQ40G
#define OFPSVR_H_ICWCQ40G

#define NDEBUG
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

extern struct Article **articles;
extern int articles_len;

extern struct Resource *resources;

extern struct MHD_Response *response_404;
extern struct MHD_Response *response_500;
extern struct MHD_Response *response_index;

extern unsigned long cache_size;
extern int cache_size_silent;
extern int running;

extern mrb_state *mrb;
extern struct RClass *mrb_ofpsvr;

extern jmp_buf main_loop;

// *** Global Functions ***

void add_comment(struct Article *a,struct Comment *c);

char *fill_content(char *name,char *email,char *website,char *body, long posted_at, int number);

int regenerate(struct Article *x,int id);

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

#endif

