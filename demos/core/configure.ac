dnl $Id: configure.ac 317 2006-02-11 18:16:24Z mindstorm2600 $

dnl --------------------------------
dnl Initialization macros.
dnl --------------------------------

AC_INIT(String/basic.cpp)
AM_CONFIG_HEADER(config.h)

GENERIC_VERSION=0.7.1.0
PACKAGE=demos

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

xvr2core_required_version=0.7.1.0

dnl -----------------------------------------------
dnl Verify that xvr2core library is already installed
dnl -----------------------------------------------
PKG_CHECK_MODULES(XVR2CORE, [xvr2core >= $xvr2core_required_version],[
	AC_MSG_RESULT([*** xvr2core found ***])
	CPPFLAGS="$CPPFLAGS $XVR2CORE_CFLAGS"
	LIBS="$LIBS $XVR2CORE_LIBS"
],[
	AC_MSG_RESULT([ !!! A suitable version of xvr2core has not been found, unable to build demos, sorry !!! ])
	exit 1
])

DEPS_LIBS=$LIBS
AC_SUBST(DEPS_LIBS)

dnl -----------------------------------------------
dnl Generates Makefile's, configuration files and scripts
dnl -----------------------------------------------

AC_OUTPUT(Makefile \
	buffer/Makefile \
	console/Makefile \
	String/Makefile \
	String/conversion/Makefile \
	Thread/Makefile \
	tokenizer/Makefile \
	file/Makefile
)

echo
echo "######################################"
echo "# X-VR2 Core demos $GENERIC_VERSION"
echo "#"
echo "#  Platform:              $host"
echo "#  Debug mode:            $debug_mode_activated"
echo "#  X-VR2 Core:            $xvr2core_required_version"
