dnl $Id$

dnl --------------------------------
dnl Initialization macros.
dnl --------------------------------

AC_INIT(mysql-drv.h)
AM_CONFIG_HEADER(config.h)

dnl -----------------------------------------------
dnl Package name and version number (user defined)
dnl -----------------------------------------------

GENERIC_LIBRARY_NAME=mysql_driver

#release versioning
GENERIC_MAJOR_VERSION=0
GENERIC_MINOR_VERSION=8
GENERIC_MICRO_VERSION=0
GENERIC_PATCH_LEVEL=0
AC_SUBST(GENERIC_MAJOR_VERSION)
AC_SUBST(GENERIC_MINOR_VERSION)
AC_SUBST(GENERIC_MICRO_VERSION)
AC_SUBST(GENERIC_PATCH_LEVEL)

GENERIC_LIBRARY_VERSION=$GENERIC_MINOR_VERSION:$GENERIC_MICRO_VERSION:$GENERIC_PATCH_LEVEL
GENERIC_LIBRARY_VERSION_DOTTED=$GENERIC_MINOR_VERSION.$GENERIC_MICRO_VERSION.$GENERIC_PATCH_LEVEL


dnl --------------------------------
dnl Package name and version number
dnl --------------------------------

AC_SUBST(GENERIC_LIBRARY_VERSION)

PACKAGE=$GENERIC_LIBRARY_NAME
AC_SUBST(GENERIC_LIBRARY_NAME)

GENERIC_VERSION=$GENERIC_MAJOR_VERSION.$GENERIC_MINOR_VERSION.$GENERIC_MICRO_VERSION
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

xvr2core_required_version=0.8.0
xvr2util_required_version=0.8.0
xvr2db_required_version=0.8.0

DRV_VERSION=0
DRV_REVISION=3

dnl -----------------------------------------------
dnl Verify that xvr2core library is already installed
dnl -----------------------------------------------
PKG_CHECK_MODULES(DEPS, [xvr2core >= $xvr2core_required_version  xvr2util >= $xvr2util_required_version xvr2db >= $xvr2db_required_version],[
	AC_MSG_RESULT([*** xvr2core, xvr2util and xvr2db found])
],[
	exit 1
])
AC_SUBST(DEPS_CFLAGS)
AC_SUBST(DEPS_LIBS)

dnl --------------------------------------------------------------
dnl Verify that MySQL development files are already installed
dnl --------------------------------------------------------------
MYSQL_INCLUDES=`mysql_config --cflags`
MYSQL_CFLAGS="-I $MYSQL_INCLUDES"
MYSQL_LIBDIR=`mysql_config --libs_r`
MYSQL_LIBS="-L $MYSQL_LIBDIR -lpq"

CPPFLAGS="$CPPFLAGS $DEPS_CFLAGS $MYSQL_CFLAGS -DDRV_VERSION=${DRV_VERSION} -DDRV_REVISION=${DRV_REVISION}"
LIBS="$LIBS $DEPS_LIBS $MYSQL_LIBS"


dnl -----------------------------------------------
dnl Generates Makefile's, configuration files and scripts
dnl -----------------------------------------------

AC_OUTPUT(Makefile)

echo
echo "######################################"
echo "# X-VR2 DB MySQL Driver $GENERIC_VERSION"
echo "#"
echo "#  Platform:              $host"
echo "#  Debug mode:            $debug_mode_activated"
echo "#  X-VR2 Core:            `pkg-config xvr2core --modversion`"
echo "#  X-VR2 Util:            `pkg-config xvr2util --modversion`"
echo "#  X-VR2 DB:              `pkg-config xvr2db --modversion`"
echo "#  MySQL:                 `mysql_config --version`"
