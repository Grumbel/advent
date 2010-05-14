AC_INIT(Advent, 0.1.1)
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_SRCDIR(src/advent_main.cxx)
AM_INIT_AUTOMAKE

AC_PROG_CC
AC_PROG_CXX

dnl FIXME: So why exactly are we doing this?!
CC=$CXX
AS=gcc

AC_DISABLE_STATIC
AC_PROG_LIBTOOL
AC_PROG_INSTALL

dnl Checking for libraries
AC_MSG_CHECKING(for maintainer mode)
AC_ARG_ENABLE(maintainer-mode, AC_HELP_STRING([--enable-maintainer-mode], [Enable maintainer mode]),, enable_maintainer_mode="no")

if test "$enable_maintainer_mode" != "no"; then
    CXXFLAGS="$CXXFLAGS -g -O0 -Wall -Werror"
    AC_MSG_RESULT([enabled])
else
    AC_MSG_RESULT([disabled])
fi

AC_LANG(C++)

AC_PATH_PROG([SWIG], [swig], [nothing-found])
if test "x$SWIG" = "xnothing-found"; then
   AC_MSG_ERROR([You need Swig - http://www.swig.org to proceed.])
fi

AC_CHECK_LIB(qthreads, main)
AC_CHECK_LIB(guile, scm_boot_guile,, [
  echo "libguile is missing, you need Guile 1.6.x to compile Advent"
  exit
  ])

REQUIRED_CLANLIB_VERSION="1.0.0"

PKG_CHECK_MODULES(ADVENT_DEPS,
 [
  clanCore-1.0    >= $REQUIRED_CLANLIB_VERSION
  clanApp-1.0     >= $REQUIRED_CLANLIB_VERSION
  clanDisplay-1.0 >= $REQUIRED_CLANLIB_VERSION
  clanSDL-1.0     >= $REQUIRED_CLANLIB_VERSION
  clanGL-1.0      >= $REQUIRED_CLANLIB_VERSION
  clanSound-1.0   >= $REQUIRED_CLANLIB_VERSION
  ],
 [CXXFLAGS="$CXXFLAGS $ADVENT_DEPS_CFLAGS"
  LIBS="$LIBS $ADVENT_DEPS_LIBS"])

AC_OUTPUT( Makefile
           src/Makefile 
           src/scripting/Makefile 
)
