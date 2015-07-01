ACLOCAL_AMFLAGS        = -I m4

AM_CFLAGS              = -I$(top_srcdir)/include                              \
                         -I$(top_srcdir)/deps/mruby/include                   \
                         $(DEBUGGING_CFLAGS)                                  \
                         -std=gnu99 -pedantic -Werror                         \
                         -Wall -Wextra -Wno-unused-parameter

include_HEADERS        = include/ofpsvr.h

lib_LTLIBRARIES        = libofpsvr.la
libofpsvr_la_LDFLAGS   = -no-undefined
libofpsvr_la_CFLAGS    = $(AM_CFLAGS) $(GCOV_CFLAGS)
libofpsvr_la_SOURCES   = handler.c                                            \
                         main.c                                               \
                         mrb_funcs.c                                          \
                         regenerate.c

bin_PROGRAMS           = ofpsvr
ofpsvr_LDADD           = libofpsvr.la
ofpsvr_SOURCES         = main.c

TESTS                  = test/run
check_PROGRAMS         = test/run
test_run_LDADD         = libofpsvr.la -lcheck
test_run_SOURCES       = test/errors_test.c                                   \
                         test/run.c
