dnl $Id$

dnl --------------------------------
dnl Initialization macros.
dnl --------------------------------


AC_INIT(Core/xvr2/Object.h)
AM_CONFIG_HEADER(config.h)

dnl -----------------------------------------------
dnl Package name and version number (user defined)
dnl -----------------------------------------------

GENERIC_LIBRARY_NAME=xvr2

#release versioning
GENERIC_MAJOR_VERSION=0
GENERIC_MINOR_VERSION=8
GENERIC_MICRO_VERSION=0
GENERIC_PATCH_LEVEL=0
AC_SUBST(GENERIC_MAJOR_VERSION)
AC_SUBST(GENERIC_MINOR_VERSION)
AC_SUBST(GENERIC_MICRO_VERSION)
AC_SUBST(GENERIC_PATCH_LEVEL)


#shared library versioning
GENERIC_LIBRARY_VERSION=$GENERIC_MINOR_VERSION:$GENERIC_MICRO_VERSION:$GENERIC_PATCH_LEVEL
GENERIC_LIBRARY_VERSION_DOTTED=$GENERIC_MINOR_VERSION.$GENERIC_MICRO_VERSION.$GENERIC_PATCH_LEVEL



dnl --------------------------------
dnl Package name and version number
dnl --------------------------------

AC_SUBST(GENERIC_LIBRARY_VERSION)
AC_SUBST(GENERIC_LIBRARY_VERSION_DOTTED)

PACKAGE=$GENERIC_LIBRARY_NAME
AC_SUBST(GENERIC_LIBRARY_NAME)

#GENERIC_VERSION=$GENERIC_MAJOR_VERSION.$GENERIC_MINOR_VERSION.$GENERIC_MICRO_VERSION.$GENERIC_PATCH_LEVEL
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
dnl -----------------------------------------------
dnl If it is GCC verify its version is >= 3.0.0
dnl -----------------------------------------------
if test "$GXX" = "yes" ; then
	AC_MSG_RESULT([GCC Detected, checking version... ])
	AC_TRY_RUN([ 

			int main()
			{
				if(__GNUC__ < 3) return 1;
				return 0;
			}
	], [ echo "GCC version is >= 3" ], 
	[
		echo "X-VR2 must be compiled with GCC versions 3.0.0 and above, please upgrade your compiler"
		exit 1
	]
	)
fi
AC_LIBTOOL_DLOPEN
AC_PROG_LIBTOOL
AC_PROG_INSTALL

AC_LANG_CPLUSPLUS
AC_C_BIGENDIAN([
			SYSTEM_IS_BIGENDIAN=1
			SYSTEM_IS_LITTLEENDIAN=0
			AC_SUBST(SYSTEM_IS_BIGENDIAN)
			xvr2_endianness="BIG ENDIAN"
			echo "System architecture is big-endian"
		],[
			SYSTEM_IS_LITTLEENDIAN=1
			SYSTEM_IS_BIGENDIAN=0
			AC_SUBST(SYSTEM_IS_LITTLEENDIAN)
			xvr2_endianness="LITTLE ENDIAN"
			echo "System architecture is little-endian"
		],[
			echo "Unknown architecture byte ordering"
			exit 1
		]
	      )


CXXFLAGS="$CXXFLAGS -Wall "

dnl -----------------------------------------------
dnl Verify manual features
dnl -----------------------------------------------

LIBS="$LIBS -ldl"

AC_ARG_ENABLE(debug, AC_HELP_STRING([--enable-debug		Build library in debug mode]), [
		AC_DEFINE(USE_DEBUG, 1, [Activates debug mode])
		debug_mode_activated=on
		AC_MSG_RESULT([ *** This library will be compiled with debug support activated *** ])
		CPPFLAGS="$CPPFLAGS -DUSE_DEBUG"
	], [
		debug_mode_activated=off
	]
)

BUILD_EXAMPLES="no"
EXAMPLES_DIR=""

AC_ARG_ENABLE(examples, AC_HELP_STRING([--enable-examples	Build example programs]), [
		BUILD_EXAMPLES="yes"
		EXAMPLES_DIR="examples"		
	], [
		BUILD_EXAMPLES="no"
	]
)

AC_SUBST(EXAMPLES_DIR)

CURL_ENABLED=0
CURL_VERSION=""
USED_HTTP_CLIENT="Native"
AC_ARG_ENABLE(curl, AC_HELP_STRING([--enable-curl    	Build example programs]), [
		
		AC_PATH_PROG([CURL_CONFIG], [curl-config], no, []
			 		 [$PATH:/usr/local/bin:/opt:/opt/doxygen:/bin:/opt/bin:/opt/sfw/bin:/usr/ccs/bin])
		if test "$CURL_CONFIG" = "no"
		then
			AC_MSG_RESULT([No libcurl found])
		else
			CURL_ENABLED=1
			CURL_VERSION=`curl-config --version`
			USED_HTTP_CLIENT=$CURL_VERSION
		fi
	]
)
AC_SUBST(CURL_ENABLED)

dnl -----------------------------------------------
dnl Miscellaneous function checking
dnl -----------------------------------------------
AC_CHECK_FUNCS(strtol strcpy memcpy pow strtoul strtoll strtoull strtof strtod strtold strerror_r, [
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

dnl -----------------------------------------------------------
dnl Doxygen stuff
dnl 1. Detect doxygen path
dnl 2. Verify of the user wants to build the docs automatically
dnl -----------------------------------------------------------
AC_PATH_PROG([DOXYGEN], [doxygen], docs, []
             [$PATH:/usr/local/bin:/opt:/opt/doxygen:/bin:/opt/bin:/opt/sfw/bin:/usr/ccs/bin])
AC_SUBST(DOXYGEN)
AC_ARG_ENABLE(docs, AC_HELP_STRING([--enable-docs          Build library documentation]), [
		DOXYGEN_INPUT_DIR="SDK_Docs"
		doxygen_docs=yes
],[
		DOXYGEN_INPUT_DIR=""
		doxygen_docs=no
])
AC_SUBST(DOXYGEN_INPUT_DIR)



ODBC_DRIVER_ENABLED=no


dnl --------------------------------------------------------------
dnl Verify that PostgreSQL development files are already installed
dnl --------------------------------------------------------------
PGSQL_INCLUDES=""
PGSQL_CFLAGS=""
PGSQL_LIBDIR=""
PGSQL_LIBS=""
PGSQL_DRIVER_ENABLED=no
PGSQL_DRIVER_DIR=""
AC_PATH_PROG([PG_CONFIG], [pg_config], no, []
             [$PATH:/usr/local/bin:/opt:/opt/doxygen:/bin:/opt/bin:/opt/sfw/bin:/usr/ccs/bin])

if test "$PG_CONFIG" = "no"
then
	AC_MSG_RESULT([ PostgreSQL development libraries not found, skipping build of pgsql driver ])
else
	PGSQL_INCLUDES=`pg_config --includedir`
	PGSQL_LIBDIR=`pg_config --libdir`
	PGSQL_LIBS="-L $PGSQL_LIBDIR -lpq"
	PGSQL_DRIVER_ENABLED=yes
	PGSQL_DRIVER_DIR=pgsql
fi
AC_SUBST(PGSQL_DRIVER_DIR)
AC_SUBST(PGSQL_INCLUDES)
AC_SUBST(PGSQL_LIBS)


dnl --------------------------------------------------------------
dnl Verify that SQLite development files are already installed
dnl --------------------------------------------------------------
SQLITE_INCLUDES=""
SQLITE_CFLAGS=""
SQLITE_LIBDIR=""
SQLITE_LIBS=""
SQLITE_DRIVER_ENABLED=no
SQLITE_DRIVER_DIR=""

AC_CHECK_HEADERS(sqlite3.h, [
	SQLITE_DRIVER_ENABLED=yes
	SQLITE_DRIVER_DIR=sqlite
	SQLITE_LIBS=-lsqlite3
])

AC_SUBST(SQLITE_DRIVER_DIR)
AC_SUBST(SQLITE_LIBS)

dnl -----------------------------------------------
dnl Generates Makefile's, configuration files and scripts
dnl -----------------------------------------------

AC_OUTPUT(Makefile \
	Core/Makefile \
	Core/xvr2/Makefile \
	Core/xvr2core.pc \
	Core/xvr2/xvr2config.h \
	Core/xvr2/xvr2config.cpp \
	Core/examples/Makefile \
	Text/Makefile \
	Text/xvr2/Makefile \
	Text/xvr2text.pc \
	SQL/Makefile \
	SQL/xvr2/Makefile \
	SQL/xvr2sql.pc \
	SQL/drivers/Makefile \
	SQL/drivers/pgsql/Makefile \
	SQL/drivers/sqlite/Makefile \
	SQL/examples/Makefile \
	Platform/Makefile \
	Platform/xvr2/Makefile \
	Platform/xvr2platform.pc \
	Net/Makefile \
	Net/examples/Makefile \
	Net/xvr2/Makefile \
	Net/xvr2net.pc \
	SDK_Docs/Doxyfile \
	SDK_Docs/Makefile
)

mkdir -p Core/xvr2/xvr2
mkdir -p Text/xvr2/xvr2/Text
mkdir -p SQL/xvr2/xvr2/SQL
mkdir -p Net/xvr2/xvr2/Net
mkdir -p Platform/xvr2/xvr2/Platform
cd Core/xvr2/xvr2
ln -sf ../*.h .
cd ../../..

cd Text/xvr2/xvr2/Text
ln -sf ../../*.h .
cd ..
ln -sf ../../../Core/xvr2/*.h .
cd ../../..

cd SQL/xvr2/xvr2/SQL
ln -sf ../../*.h .
cd ..
ln -sf ../../../Core/xvr2/*.h .
cd ../../..

cd Platform/xvr2/xvr2/Platform
ln -sf ../../*.h .
cd ..
ln -sf ../../../Core/xvr2/*.h .
cd ../../..

cd Net/xvr2/xvr2/Net
ln -sf ../../*.h .
cd ..
ln -sf ../../../Core/xvr2/*.h .
cd ../../..

echo
echo "###################################################"
echo "# X-VR2 Framework $GENERIC_VERSION"
echo "#"
echo "#  Platform:              $host"
echo "#  Endianness:            $xvr2_endianness"
echo "#  Debug mode:            $debug_mode_activated"
echo "#  Thread platform:       $threads_library"
echo "#  Generate docs:         $doxygen_docs"
echo "#  Build example progs:   $BUILD_EXAMPLES"
echo "#-------------------------------------------------#"
echo "#  Network Options:"
echo "#  HTTPClient:            $USED_HTTP_CLIENT"
echo "#-------------------------------------------------#"
echo "#  SQL Drivers:"
echo "#  PostgreSQL Provider:   $PGSQL_DRIVER_ENABLED"
echo "#  SQLite Provider:       $SQLITE_DRIVER_ENABLED"
echo "#  ODBC Provider:         $ODBC_DRIVER_ENABLED"
