SUBDIRS                = deps/libmicrohttpd                                   \
                         deps/hiredis

ACLOCAL_AMFLAGS        = -I m4

AM_CFLAGS              = -I$(top_srcdir)/include                              \
                         -I$(top_srcdir)/deps/libmicrohttpd/src/include       \
                         -I$(top_srcdir)/deps/hiredis                         \
                         $(DEBUGGING_CFLAGS)                                  \
                         -std=gnu99 -pedantic                                 \
                         -Wall -Wextra -Wno-unused-parameter

include_HEADERS        = include/ofpsvr.h

bin_PROGRAMS           = ofpsvr
ofpsvr_CFLAGS          = $(AM_CFLAGS)
ofpsvr_LDADD           = $(top_srcdir)/deps/hiredis/libhiredis.a              \
                         $(top_srcdir)/deps/libmicrohttpd/src/microhttpd/.libs/libmicrohttpd.a
ofpsvr_SOURCES         = main.c                                               \
                         handler.c                                            \
                         utils.c                                              \
                         errors.c                                             \
                         regenerate.c                                         \
                         favicon.c
