#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT(
  [OF P.S.V.R], [0.2], [pmq2001@gmail.com], [ofpsvr],
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
AC_CHECK_HEADERS([limits.h stddef.h stdint.h stdlib.h string.h])
AC_CHECK_HEADER(
  [mruby.h], ,
  [
    AC_MSG_ERROR([Please install mruby; cf. http://www.mruby.org/])
  ])
AC_CHECK_HEADER(
  [check.h], ,
  [
    AC_MSG_ERROR([Please install check; cf. http://check.sourceforge.net/])
  ])

# Checks for libraries.
AC_SEARCH_LIBS([uv_run], [uv])

# Checks for typedefs, structures, and compiler characteristics.
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
AC_CHECK_FUNCS([memchr memset strtoul])

# Adding Options
AC_ARG_WITH([gcov],
  [AS_HELP_STRING([--with-gcov],
    [Generates coverage reports @<:@default=no@:>@])],
  [],
  [with_gcov=no])

AC_ARG_WITH([debugging],
  [AS_HELP_STRING([--with-debugging],
    [Generates coverage reports @<:@default=no@:>@])],
  [],
  [with_debugging=no])

AS_IF([test "x$with_gcov" != xno],
  [AC_SUBST([GCOV_CFLAGS], [--coverage])])

AS_IF([test "x$with_debugging" != xno],
  [
    AC_SUBST([DEBUGGING_CFLAGS], [-g])
    AC_DEFINE([OFPSVR_DEBUG], [1], [Enable debugging])
  ])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
