dnl $Id$

dnl --------------------------------
dnl Initialization macros.
dnl --------------------------------

AC_INIT(xvr2/Object.h)
AM_CONFIG_HEADER(config.h)

dnl -----------------------------------------------
dnl Package name and version number (user defined)
dnl -----------------------------------------------

GENERIC_LIBRARY_NAME=xvr2

#release versioning
GENERIC_MAJOR_VERSION=0
GENERIC_MINOR_VERSION=7
GENERIC_MICRO_VERSION=1
GENERIC_PATCH_LEVEL=0

#API version (often = GENERIC_MAJOR_VERSION.GENERIC_MINOR_VERSION)
GENERIC_API_VERSION=0.7.1
AC_SUBST(GENERIC_API_VERSION)

#shared library versioning
GENERIC_LIBRARY_VERSION=0:7:0


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

dnl -----------------------------------------------
dnl Verify manual features
dnl -----------------------------------------------

LIBS="$LIBS -ldl"

AC_ARG_ENABLE(debug, AC_HELP_STRING([--enable-debug          Build library in debug mode]), [
		AC_DEFINE(USE_DEBUG, 1, [Activates debug mode])
		debug_mode_activated=on
		AC_MSG_RESULT([ *** This library will be compiled with debug support activated *** ])
		CPPFLAGS="$CPPFLAGS -DUSE_DEBUG"
	], [
		debug_mode_activated=off
	]
)

dnl -----------------------------------------------
dnl Miscellaneous function checking
dnl -----------------------------------------------
AC_CHECK_FUNCS(strtol strcpy memcpy pow, [
	threads_library="POSIX Threads (pthreads)"
	ENABLE_XVR2_POSIX_THREADS_SUPPORT=1
	AC_SUBST(ENABLE_XVR2_POSIX_THREADS_SUPPORT)
],[
	exit 1;
])

dnl -----------------------------------------------
dnl Miscellaneous function checking
dnl -----------------------------------------------
AC_CHECK_FUNCS(getgrgid_r, [

],[
	AC_DEFINE(DONT_HAVE_REENTRANT_GETGRGID, 1, [Reentrant getgrgid_r function is not defined])
])


dnl -----------------------------------------------
dnl POSIX Threads testing
dnl -----------------------------------------------
AC_CHECK_LIB(pthread, pthread_create, [
	AC_CHECK_LIB(pthread, pthread_attr_init, [
		AC_CHECK_FUNCS(pthread_self, [
			threads_library="POSIX Threads (pthreads)"
			ENABLE_XVR2_POSIX_THREADS_SUPPORT=1
			AC_SUBST(ENABLE_XVR2_POSIX_THREADS_SUPPORT)
		],[
			AC_MSG_RESULT([ !!! Posix Threads are not supported in this platform !!! ])
			exit 1;
		])
	],[
		AC_MSG_RESULT([ !!! Posix Threads are not supported in this platform !!! ])
		exit 1;
	])
	
],[
	AC_MSG_RESULT([ !!! Posix Threads are not supported in this platform !!! ])
	exit 1;
])

if test "$ENABLE_XVR2_POSIX_THREADS_SUPPORT" = "1"; then
	LIBS="$LIBS -lpthread"
	CPPFLAGS="$CPPFLAGS -DUSE_POSIX_THREADS -D_REENTRANT -D_THREAD_SAFE"
fi

dnl -----------------------------------------------
dnl Generates Makefile's, configuration files and scripts
dnl -----------------------------------------------

AC_OUTPUT(Makefile \
          xvr2core.pc \
          xvr2/Makefile \
          xvr2/xvr2config.h
)

echo
echo "######################################"
echo "# X-VR2 Core library $GENERIC_VERSION"
echo "#"
echo "#  Platform:              $host"
echo "#  Debug mode:            $debug_mode_activated"
echo "#  Thread platform:       $threads_library"
