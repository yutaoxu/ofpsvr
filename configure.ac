#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT(
  [OF P.S.V.R], [8.9.0.2], [pmq2001@gmail.com], [ofpsvr],
  [https://github.com/pmq20/ofpsvr])
AC_CONFIG_MACRO_DIR([m4])
m4_include([m4/headers.m4])
m4_include([m4/ofpsvr_gitignore.m4])
AC_COPYRIGHT([Copyright (c) 2015 P.S.V.R])
AM_INIT_AUTOMAKE(
  [-Wall -Werror foreign subdir-objects] OFPSVR_EXTRA_AUTOMAKE_FLAGS)
AC_CONFIG_SRCDIR([main.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AM_PROG_AR
AC_PROG_RANLIB
AM_PROG_CC_C_O

LT_INIT

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h fcntl.h netdb.h netinet/in.h stddef.h stdint.h  \
                  stdlib.h string.h sys/socket.h sys/time.h unistd.h])
AC_CHECK_HEADER(
  [mysql/mysql.h], ,
  [
    AC_MSG_ERROR([Please install MySQL Connector/C (libmysqlclient);
      cf. https://dev.mysql.com/downloads/connector/c])
  ])
AC_CHECK_HEADER(
  [microhttpd.h], ,
  [
    AC_MSG_ERROR([Please install GNU Libmicrohttpd;
      cf. https://www.gnu.org/software/libmicrohttpd/])
  ])
AC_CHECK_HEADER(
  [openssl/md5.h], ,
  [
    AC_MSG_ERROR([Please install OpenSSL;
      cf. https://www.openssl.org/])
  ])
AC_CHECK_HEADER(
  [check.h], ,
  [
    AC_MSG_ERROR([Please install check;
      cf. http://check.sourceforge.net/])
  ])

# Checks for libraries.
AC_CHECK_LIB([microhttpd], [MHD_queue_response])
AC_CHECK_LIB([mysqlclient], [mysql_init])
AC_CHECK_LIB([pthread], [pthread_mutex_init])
AC_CHECK_LIB([crypto], [MD5])
AC_CHECK_LIB([check], [srunner_run_all])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_PID_T
AC_CHECK_HEADER_STDBOOL
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_INT8_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_FORK
AC_CHECK_FUNCS([strchr strdup strrchr strstr])

# Adding Options
AC_ARG_WITH([gcov],
  [AS_HELP_STRING([--with-gcov],
    [Generates coverage reports @<:@default=no@:>@])],
  [],
  [with_gcov=no])

AC_ARG_ENABLE(debug,
  AS_HELP_STRING([--enable-debug],
                 [enable debugging, default: no]),
  [case "${enableval}" in
               yes) debug=true ;;
               no)  debug=false ;;
               *)   AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
  esac],
  [debug=false])

AS_IF([test "x$with_gcov" != xno],
  [AC_SUBST([GCOV_CFLAGS], [--coverage])])

AS_IF([test x"$debug" = x"true"],
  [
    AC_SUBST([DEBUGGING_CFLAGS], ["-g3 -O0"])
    AC_DEFINE([OFPSVR_DEBUG], [1], [Enable debugging])
  ],
  [
    AC_SUBST([DEBUGGING_CFLAGS], [-O3])
  ])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
