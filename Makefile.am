SUBDIRS                = deps/mruby                                           \
                         deps/captcha                                         \
                         deps/libmicrohttpd

ACLOCAL_AMFLAGS        = -I m4

AM_CFLAGS              = -I$(top_srcdir)/include                              \
                         -I$(top_srcdir)/deps/mruby/include                   \
                         -I$(top_srcdir)/deps/libmicrohttpd/src/include       \
                         $(DEBUGGING_CFLAGS)                                  \
                         -std=gnu99 -Werror                                   \
                         -Wall -Wextra -Wno-unused-parameter

include_HEADERS        = include/ofpsvr.h

lib_LTLIBRARIES        = libofpsvr.la
libofpsvr_la_CFLAGS    = $(AM_CFLAGS) $(GCOV_CFLAGS)
libofpsvr_la_SOURCES   = handler.c                                            \
                         mrb_funcs.c                                          \
                         utils.c                                              \
                         errors.c                                             \
                         regenerate.c

bin_PROGRAMS           = ofpsvr
ofpsvr_LDADD           = libofpsvr.la                                         \
                         $(top_srcdir)/deps/mruby/build/host/lib/libmruby.a   \
                         $(top_srcdir)/deps/libmicrohttpd/src/microhttpd/.libs/libmicrohttpd.a
ofpsvr_SOURCES         = main.c

TESTS                  = test/run
check_PROGRAMS         = test/run
test_run_LDADD         = libofpsvr.la -lcheck                                 \
                         $(top_srcdir)/deps/mruby/build/host/lib/libmruby.a   \
                         $(top_srcdir)/deps/libmicrohttpd/src/microhttpd/.libs/libmicrohttpd.a
test_run_SOURCES       = test/errors_test.c                                   \
                         test/run.c
