#!/bin/bash
# $Id$
#
# Este script genera el makefile
#
#
MYVERSION="0.1.0"
DRV_VERSION=0
DRV_REVISION=2
PLATFORM=`uname -sr`
OS=`uname -s`
PROCESSOR=`uname -m`
echo "" > Makefile

get_value()
{
	echo $1 | cut -f2 -d'='
}

get_include_deps()
{
	include=$1
	ddeps=""
	for inc in `cat $include | grep include | sed 's/.*[\"|<]\(.*\)[\"|>]/\1/'`
	do
		if [ -f $inc ]; then
			ddeps="$ddeps $inc"
		fi
	done
	echo $ddeps
}

usage()
{
	echo " "
	echo "Usage (parameters with an asterisk are enabled by default): "
	echo "--help				Print this usage message"
	echo "--use-debug			* Activate debug message printing"
	echo "--no-debug			Dectivate debug message printing"
	echo "--disable-mantainer-mode	Disable maintainer mode (Remove symbols in object files)"
	echo "--enable-mantainer-mode		Enable maintainer mode (Leave symbols in object files)"
	echo "--debug-mutexes			Show status messages while locking/unlocking mutexes"
	echo " "
	echo " "
	exit 0
}

SDLCFLAGS=" `sdl-config --cflags` "
SDLLIBS="`sdl-config --libs`"
DEBUGMODE=0
MAINTAINER="-g"
PREFIX="/usr/local"
XVR2GL_DIR=".././"
XVR2GL_INCLUDE="$XVR2GL_DIR/src"
XVR2GL_LIBS="$XVR2GL_DIR/src"

echo " "
for option in `echo "$@"`
do
	if [ "$option" = '--help' ]; then
		usage
	else
		if [ "$option" = '-h' ]; then
			usage
		else
			if [ "$option" = '--use-debug' ]; then
				DEBUGMODE=1
			else
				if [ "$option" = '--no-debug' ]; then
					DEBUGMODE=0
				else
					if [ "$option" = '--disable-maintainer-mode' ]; then
						MAINTAINER=''
					else
						if [ "$option" = '--enable-maintainer-mode' ]; then
							MAINTAINER="-g"
						else 
							if [ "$option" = '--debug-mutexes' ]; then
								DEBUG_MUTEXES=" -DDEBUG_MUTEXES=1"
							else
								echo "$option" | egrep '^--sock-chunk-size' > /dev/null 2>&1
								if [ $? -eq 0 ]; then
									SCHUNK="-DSOCK_CHUNK_SIZE="
									SCHUNK=${SCHUNK}`get_value $option`
								else
									echo "$option" | egrep '^--version=' > /dev/null 2>&1
									if [ $? -eq 0 ]; then
										MYVERSION=`get_value $option`
									else
										echo "$option" | egrep '^--prefix=' > /dev/null 2>&1
										if [ $? -eq 0 ]; then
											PREFIX=`get_value $option`
										fi
									fi
								fi
							fi
						fi
					fi
				fi
			fi
		fi
	fi

done


DEFINES="$SCHUNK"
echo $SCHUNK

if [ "$SDLCMD" ]; then
	DEFINES="$DEFINES -DUSE_SDL"
else
	DEFINES="$DEFINES -DUNIX_SOCKETS -DUSE_POSIX_THREADS -D_REENTRANT -D_THREAD_SAFE"
fi

if [ "$DEBUGMODE" -eq 1 ]; then
	DEFINES="$DEFINES -DUSE_DEBUG "
fi

echo "DEFINES: $DEFINES"

if [ "$THREADMODE" = 'PTH' ]; then
	echo "PTHCONFIG=pth-config" >> Makefile
fi
echo "Processor: $PROCESSOR, platform is $PLATFORM"

echo -ne "Checking g++..."
GPP=`slocate g++ | egrep '.*bin.*\/g\+\+$'`
if [ $? -ne 0 ]; then
	echo "FAILED"
	echo "Unable to find g++, do you have slocate or g++ installed??"
	echo " "
	exit 1
else
	echo "OK"
fi

GCCVERSION=`gcc --version | grep gcc | awk '{print $3}' | sed 's/\..*//'`
if [ "$GCCVERSION" -ge 3 ]; then
#DEFINES="$DEFINES -Wno-deprecated "
DEFINES="$DEFINES -DUSING_GCC3 "
fi

echo "CC=$GPP" >> Makefile

echo -ne "Checking for SDL development libraries"
which sdl-config > /dev/null 2>&1
if [ $? -ne 0 ]; then
echo 'all:

clean:

install:

rebuild: clean all
' > Makefile
	echo "SDL driver will not be built, sdl-config not found!!!"
	exit 0
else
	echo "$(sdl-config --version)"
fi

if [ $OS = 'SunOS' ]; then
echo -ne "$OS 2."
if [ $DEBUGMODE -eq 1 ]; then
	DEBUGSTRING="-DUSE_DEBUG=$DEBUGMODE"
fi
DEFINES="$DEFINES -DSOLARIS"
echo "
DEBUG=$MAINTAINER $DEBUGSTRING $DEBUG_MUTEXES
#DEBUG=
OPTIMIZE=" >> Makefile
OSVER=`uname -r | sed 's/5\.//'`
echo $OSVER
echo "CFLAGS=-Wall \$(DEBUG) \$(OPTIMIZE) -DSOLARIS=1 -DSOLARIS2$OSVER=1 -I../../src -I. -c $DEFINES `xvr2-config.sh --cflags` $SDLCFLAGS" >> Makefile
if [ $OSVER -eq 8 ]; then
	DEFINES="$DEFINES -DSOLARIS8"
	echo "LIBS=$SDLLIBS" >> Makefile
else
	if [ $OSVER -eq 6 ]; then
		DEFINES="$DEFINES -DSOLARIS6"
		echo "LIBS=$SDLLIBS -lxvr2" >> Makefile
	else
		echo "We haven't tested this on Solaris 7 yet"
		DEFINES="$DEFINES -DSOLARIS7"
		exit 1
	fi
fi

LIBS="$LIBS `xvr2-config.sh --libs`"

echo "INSTALLDIR=$PREFIX
LIBNAME=xvr2_sdl_driver.so.${MYVERSION}
SONAME=xvr2_sdl_driver.so
BUILDLIB=-G
all: \$(LIBNAME)" >> Makefile
else
if [ "$NETLIB" = "-lsocket" ]; then
	NETLIB=""
fi
DEFINES="$DEFINES -DUSING_LINUX -D__GNU"
echo "
DEBUG=$MAINTAINER $DEBUGSTRING $DEBUG_MUTEXES
#DEBUG=$MAINTAINER -DUSE_DEBUG=$DEBUGMODE
#DEBUG=
OPTIMIZE=
CFLAGS=-Wall \$(DEBUG) \$(OPTIMIZE) -I. -I../.,/src -c $DEFINES -Wimplicit -Wreturn-type -Wunused -Wswitch -Wcomment -Wparentheses -Wpointer-arith  `xvr2-config.sh --cflags` $SDLCFLAGS" >> Makefile
echo "LIBS=`xvr2-config.sh --libs` $SDLLIBS" >> Makefile
echo "INSTALLDIR=$PREFIX
LIBNAME=xvr2_sdl_driver.so.${MYVERSION}
SONAME=xvr2_sdl_driver.so
BUILDLIB=-shared -Wl,-soname,\$(LIBNAME) \$(LIBS)
all: \$(LIBNAME)" >> Makefile
fi

echo -ne "Serching for dependencies"
DEPS=""
for src in `ls *.cpp`
do
 OUTPUT=`echo $src | sed 's/cpp/o/'`
 DEPS="$DEPS $OUTPUT"
 echo -ne "."
done
echo "done"

echo "\$(LIBNAME): $DEPS" >> Makefile
echo -ne "\t\$(CC) \$(BUILDLIB) -o \$(LIBNAME) $DEPS\n" >> Makefile

for src in `ls *.cpp`
do
 OUTPUT=`echo $src | sed 's/cpp/o/'`
 HEADER=`echo $src | sed 's/cpp/h/'`
 DDEPS="$OUTPUT: $src "
 echo "Adding: $src"
 for inc in `cat $src | grep "#include" | sed 's/#include.*[\"|\<]\(.*\)[\"|\>]/\1/'`
 do
	 if  [ -f "$inc" ] ; then
		DDEPS="$DDEPS $inc"
	 	echo -ne "\tDepends on: $inc "
		NDEPS=`get_include_deps $inc`
		echo $NDEPS
		DDEPS="$DDEPS $NDEPS"
		echo " "
	 fi
 done
 echo $DDEPS >> Makefile
 #echo "$OUTPUT: $src $HEADER" >> Makefile 
 echo -ne "\t\$(CC) \$(CFLAGS) -DDRV_VERSION=${DRV_VERSION} -DDRV_REVISION=${DRV_REVISION} -o $OUTPUT $src\n\n" >> Makefile
done


echo 'clean:
	rm -f *.o $(LIBNAME) core

install: all
	mkdir -p $(INSTALLDIR)/lib/xvr2
	cp -vf $(LIBNAME) $(INSTALLDIR)/lib/xvr2
	cd $(INSTALLDIR)/lib/xvr2 ; rm -f $(SONAME) ; ln -sf $(LIBNAME) $(SONAME)

rebuild: clean all
' >> Makefile


echo " "
echo " "
echo "	----------------------------------"
echo "	Configuration:"
echo " "
if [ $DEBUGMODE -eq 1 ]; then
	echo "	Debugmode:		ON"
else
	echo "	Debugmode:		OFF"
fi

if [ "$MAINTAINER" = "-g" ]; then
	echo "	Maintainer:		ON"
else
	echo "	Maintainer:		OFF"
fi

echo "	----------------------------------"
echo " "
echo " "
