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
#		else
#			ninc=`slocate $inc | grep usr | grep include | egrep "\/$inc\$" | head -1`
#			if [ $? -eq 0 ]; then
#				ddeps="$ddeps $ninc"
#			fi
		fi
	done
	echo $ddeps
}

usage()
{
	echo " "
	echo "Usage (parameters with an asterisk are enabled by default): "
	echo "--with-pth			* Use GNU Portable threads (GNU Pth)"
	echo "--with-pthreads			Use POSIX Threads"
	echo "--with-sdl-threads		Use SDL POSIX threads encapsulation"
	echo "--help				Print this usage message"
	echo "--use-debug			* Activate debug message printing"
	echo "--no-debug			Dectivate debug message printing"
	echo "--disable-mantainer-mode	Disable maintainer mode (Remove symbols in object files)"
	echo "--enable-mantainer-mode		Enable maintainer mode (Leave symbols in object files)"
	echo "--debug-mutexes			Show status messages while locking/unlocking mutexes"
	echo "--dont-use-sdl			Disables the use of SDL for network and threads"
	echo "					(reduces portability)"
	echo "--sock-chunk-size		Change socket buffer chunk size in bytes while sending"
	echo "				huge amounts of data through the net (default: 4096)"
	echo "--prefix			Specifies the prefix installation directory"
	echo " "
	echo " "
	exit 0
}

#THREADMODE=SDL_THREADS
#NETLIB=-lSDL_net
#SDLCMD='`sdl-config --libs`'
#SDLCFLAGS='`sdl-config --cflags`'
SQLFLAGS=' -I`pg_config --includedir` -I../../db/src -I../../base/src -I../../common -I../../exception/src '
THREADMODE=PTHREADS
NETLIB=-lsocket
SQLLIBS=' -L`pg_config --libdir` -lpq -lxvr2 '
DEBUGMODE=0
MAINTAINER="-g"
PREFIX="/usr/local"

echo " "
for option in `echo "$@"`
do
	if [ "$option" = '--help' ]; then
		usage
	else
		if [ "$option" = '-h' ]; then
			usage
		else
			if [ "$option" = '--with-pth' ]; then
				THREADMODE=PTH
				pth-config --help > /dev/null 2>&1
				if [ $? -ne 0]; then
					echo "Unable to find Pth: is pth-config in your PATH??"
					exit 1
				fi
			else
				if [ "$option" = '--with-pthreads' ]; then
					THREADMODE=PTHREADS
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
											if [ "$option" = '--use-sdl-threads' ]; then
												THREADMODE=SDL_THREADS
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
GPP=`slocate g++ | egrep '\/g\+\+$'`
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


#echo -ne "Checking sdl-config..."
#sdl-config --libs > /dev/null 2>&1
#if [ $? -ne 0 ]; then
#	echo "FAILED"
#	echo "Unable to find sdl-config, do you have SDL installed??"
#	echo " "
#	exit 1
#else
#	echo "OK"
#	echo "SDL version: $(sdl-config --version)"
#fi

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
echo "CFLAGS=-Wall \$(DEBUG) \$(OPTIMIZE) -DSOLARIS=1 -DSOLARIS2$OSVER=1 -I../../src -I. -c -DUSE_NEW=1  -D_STRUCTURED_PROC $SDLCMD $DEFINES $SQLFLAGS" >> Makefile
if [ $OSVER -eq 8 ]; then
	DEFINES="$DEFINES -DSOLARIS8"
	if [ $THREADMODE = 'SDL_THREADS' ]; then
 			echo "LIBS=-lposix4 -lsocket -ldl $SDLCMD $NETLIB $SQLLIBS" >> Makefile
	else
		if [ $THREADMODE = 'PTHREADS' ]; then
 			echo "LIBS=-lposix4 -lsocket -ldl -lposix -lpthread $SDLCMD $NETLIB" $SQLLIBS >> Makefile
		else
			if [ $THREADMODE = 'SDL_THREADS' ]; then
 				echo "LIBS=-lposix4 -lsocket -ldl -lposix $SDLCMD $NETLIB $SQLLIBS" >> Makefile
			else
				echo "LIBS=-I`$(PTHCONFIG) --libdir` `$(PTHCONFIG) --libs` -lrt -lsocket -ldl $SDLCMD $NETLIB $SQLLIBS" >> Makefile
			fi
		fi
	fi
else
	if [ $OSVER -eq 6 ]; then
		DEFINES="$DEFINES -DSOLARIS6"
		if [ $THREADMODE = 'SDL_THREADS' ]; then
 				echo "LIBS=-lposix4 -lsocket -ldl $SDLCMD $NETLIB $SQLLIBS" >> Makefile
		else
			if [ $THREADMODE = 'PTHREADS' ]; then
 				echo "LIBS=-lposix4 -lsocket -ldl -lposix -lpthread $SDLCMD $NETLIB $SQLLIBS" >> Makefile
			else
				echo "LIBS=-I`$(PTHCONFIG) --libdir` `$(PTHCONFIG) --libs` -lposix4 -lsocket -ldl $SDLCMD $NETLIB $SQLLIBS" >> Makefile
			fi
		fi
	else
		echo "We haven't tested this on Solaris 7 yet"
		DEFINES="$DEFINES -DSOLARIS7"
		exit 1
	fi
fi

LIBS="$LIBS "

echo "INSTALLDIR=$PREFIX
LIBNAME=pgsql_driver.so.${MYVERSION}
SONAME=pgsql_driver.so
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
CFLAGS=-Wall \$(DEBUG) \$(OPTIMIZE) -I. -I../.,/src -c $DEFINES -Wimplicit -Wreturn-type -Wunused -Wswitch -Wcomment -Wparentheses -Wpointer-arith $SDLCFLAGS $SQLFLAGS" >> Makefile
if [ $THREADMODE = 'SDL_THREADS' ]; then
	echo "LIBS=-ldl -lrt $SDLCMD $NETLIB $SQLLIBS" >> Makefile
else
	if [ $THREADMODE = 'PTHREADS' ]; then
		echo "LIBS=-ldl -lrt -lpthread $NETLIB $SQLLIBS" >> Makefile
	else
		echo 'LIBS=-I`$(PTHCONFIG) --libdir` `$(PTHCONFIG) --libs` -lrt -ldl `sdl-config --libs` $NETLIB $SQLLIBS' >> Makefile
	fi
fi
echo "INSTALLDIR=$PREFIX
LIBNAME=pgsql_driver.so.${MYVERSION}
SONAME=pgsql_driver.so
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

if [ $THREADMODE = 'PTH' ]; then
	echo "	Threads:		GNU Pth"
else
	if [ $THREADMODE = 'SDL_THREADS' ]; then
		echo "	Threads:		POSIX Threads (SDL Encapsulation)"
	else
		echo "	Threads:		POSIX Threads"
	fi
fi

if [ "$MAINTAINER" = "-g" ]; then
	echo "	Maintainer:		ON"
else
	echo "	Maintainer:		OFF"
fi

if [ "$SCHUNK" ]; then
	echo "	Socket chunk size:	$SCHUNK"
fi

if [ ! "$SDLCMD" ]; then
	echo "	SDL encapsulation:	OFF"
else
	echo "	SDL encapsulation:	ON"
fi
echo "	----------------------------------"
echo " "
echo " "
