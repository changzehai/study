#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])

#手动指定程序名
#这里以test为例
AC_INIT(test,1.0,haha)
AM_INIT_AUTOMAKE(test,1.0)

AC_CONFIG_SRCDIR([test.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

#这里的Makefile与Makefile.am名字要对应
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
