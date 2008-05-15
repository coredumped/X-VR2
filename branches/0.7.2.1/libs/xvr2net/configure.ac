dnl $Id$

dnl --------------------------------
dnl Initialization macros.
dnl --------------------------------

AC_INIT(xvr2/TCPSocket.h)
AM_CONFIG_HEADER(config.h)

dnl -----------------------------------------------
dnl Package name and version number (user defined)
dnl -----------------------------------------------

GENERIC_LIBRARY_NAME=xvr2

#release versioning
GENERIC_MAJOR_VERSION=0
GENERIC_MINOR_VERSION=7
GENERIC_MICRO_VERSION=2
GENERIC_PATCH_LEVEL=1


GENERIC_LIBRARY_VERSION=$GENERIC_MINOR_VERSION:$GENERIC_MICRO_VERSION:$GENERIC_PATCH_LEVEL



dnl --------------------------------
dnl Package name and version number
dnl --------------------------------

AC_SUBST(GENERIC_LIBRARY_VERSION)

PACKAGE=$GENERIC_LIBRARY_NAME
AC_SUBST(GENERIC_LIBRARY_NAME)

GENERIC_VERSION=$GENERIC_MAJOR_VERSION.$GENERIC_MINOR_VERSION.$GENERIC_MICRO_VERSION.$GENERIC_PATCH_LEVEL
GENERIC_RELEASE=$GENERIC_MAJOR_VERSION.$GENERIC_MINOR_VERSION.$GENERIC_MICRO_VERSION
AC_SUBST(GENERIC_RELEASE)
AC_SUBST(GENERIC_VERSION)

VERSION=$GENERIC_VERSION

AM_INIT_AUTOMAKE($PACKAGE, $VERSION, no-define)

dnl -----------------------------------------------
dnl Checks for programs.
dnl -----------------------------------------------

AC_PROG_CC
AC_PROG_CXX
AC_LIBTOOL_DLOPEN
AC_PROG_LIBTOOL
AC_PROG_INSTALL

AC_LANG_CPLUSPLUS

CXXFLAGS="$CXXFLAGS -Wall "

dnl -----------------------------------------------
dnl Verify manual features
dnl -----------------------------------------------

#LIBS="$LIBS -ldl"

AC_ARG_ENABLE(debug, AC_HELP_STRING([--enable-debug          Build library in debug mode]), [
		AC_DEFINE(USE_DEBUG, 1, [Activates debug mode])
		debug_mode_activated=on
		AC_MSG_RESULT([ *** This library will be compiled with debug support activated *** ])
		CPPFLAGS="$CPPFLAGS -DUSE_DEBUG"
	], [
		debug_mode_activated=off
	]
)

xvr2core_required_version=0.7.2.0
openssl_required_version=0.9.7

dnl -----------------------------------------------
dnl Verify that xvr2core library is already installed
dnl -----------------------------------------------
PKG_CHECK_MODULES(DEPS, [xvr2core >= $xvr2core_required_version openssl >= $openssl_required_version],[
	AC_MSG_RESULT([*** xvr2core, OpenSSL found])
],[
	exit 1
])
AC_SUBST(DEPS_CFLAGS)
AC_SUBST(DEPS_LIBS)

dnl -----------------------------------------------------------
dnl Doxygen stuff
dnl 1. Detect doxygen path
dnl 2. Verify of the user wants to build the docs automatically
dnl -----------------------------------------------------------
AC_PATH_PROG([DOXYGEN], [doxygen], docs, []
             [$PATH:/usr/local/bin:/opt:/opt/doxygen:/bin:/opt/bin:/opt/sfw/bin:/usr/ccs/bin])
AC_SUBST(DOXYGEN)
AC_ARG_ENABLE(docs, AC_HELP_STRING([--enable-docs          Build library documentation]), [
		DOXYGEN_INPUT_DIR="docs"
		doxygen_docs=yes
],[
		DOXYGEN_INPUT_DIR=""
		doxygen_docs=no
])
AC_SUBST(DOXYGEN_INPUT_DIR)

dnl -----------------------------------------------
dnl Generates Makefile's, configuration files and scripts
dnl -----------------------------------------------

AC_OUTPUT(Makefile \
			xvr2net.pc \
			xvr2/Makefile \
			docs/Makefile \
			docs/Doxyfile
)

echo
echo "######################################"
echo "# X-VR2 Net library $GENERIC_VERSION"
echo "#"
echo "#  Platform:              $host"
echo "#  Debug mode:            $debug_mode_activated"
echo "#  X-VR2 Core:            $xvr2core_required_version"
echo "#  OpenSSL:               `pkg-config openssl --modversion`"
echo "#  Generate docs:         $doxygen_docs"
