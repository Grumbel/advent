AC_INIT(Advent, 0.1.0)
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
AC_LANG(C++)

dnl Checking for libraries
AC_CHECK_LIB(qthreads, main)
AC_CHECK_LIB(guile, scm_boot_guile)
AC_CHECK_HEADER(guile/gh.h)

REQUIRED_CLANLIB_VERSION="0.7.4"

PKG_CHECK_MODULES(ADVENT_DEPS,
 [
  clanCore-0.7    >= $REQUIRED_CLANLIB_VERSION
  clanApp-0.7     >= $REQUIRED_CLANLIB_VERSION
  clanDisplay-0.7 >= $REQUIRED_CLANLIB_VERSION
  clanSDL-0.7     >= $REQUIRED_CLANLIB_VERSION
  clanSound-0.7   >= $REQUIRED_CLANLIB_VERSION
  ],
 [CXXFLAGS="$CXXFLAGS $ADVENT_DEPS_CFLAGS"
  LIBS="$LIBS $ADVENT_DEPS_LIBS"])

AC_OUTPUT( Makefile
           src/Makefile 
	   src/boost/Makefile
	   src/guile/Makefile 
	   doc/Makefile
	   doc/examples/Makefile
	   doc/examples/cosmos/Makefile
	   doc/examples/retriever/Makefile
)
