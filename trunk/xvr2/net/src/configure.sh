#!/bin/bash
# $Id$
#
# Este script genera el makefile
#
#
MYVERSION="0.6.6"
MYLIBNAME="libxvr2"
PLATFORM=`uname -sr`
OS=`uname -s`
PROCESSOR=`uname -m`
echo "" > Makefile

find_binary()
{
	binname=$1
	echo -ne "Checking g++..."
	
	BIN=`slocate ${binname} | grep bin | egrep "${binname}\$"`
	if [ $? -ne 0 ]; then
		echo "FAILED"
		echo "Unable to find g++, do you have slocate or g++ installed??"
		echo " "
		exit 1
	else
		echo "OK"
	fi
}

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

THREADMODE=PTHREADS
NETLIB=-lsocket
NETCFLAGS=" -I../base/src "
SDLCMD=''
SDLCFLAGS=''
DEBUGMODE=1
MAINTAINER="-g"
PREFIX="/usr/local"
rm -f ../../common/xvr2.h
rm -f ../../common/xvr2config.h

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
												if [ "$option" == '--dont-use-sdl' ]; then
													SDLCMD=""
													SDLCFLAGS=""
													THREADMODE=PTHREADS
													NETLIB=-lsocket
												else
													echo "$option" | egrep '^--version=' > /dev/null 2>&1
													if [ $? -eq 0 ]; then
														MYVERSION=`get_value $option`
													else
														echo "$option" | egrep '^--with-name=' > /dev/null 2>&1
														if [ $? -eq 0 ]; then
															MYLIBNAME=`get_value $option`
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
	#if [ "$OS" = "Linux" ]; then
	#	DEFINES="$DEFINES --with-dwarf2 "
	#fi
fi

######################## PRE-DEFINES ##########################
DEFINES="$DEFINES -DHAVE_MEMCPY -DHAVE_STRCPY -DHAVE_POW -DHAVE_STRTOL"

echo "DEFINES: $DEFINES"

if [ $THREADMODE = 'PTH' ]; then
	echo "PTHCONFIG=pth-config" >> Makefile
fi
echo "Processor: $PROCESSOR, platform is $PLATFORM"

echo -ne "Checking g++..."
GPP=`slocate g++ | grep bin | egrep '\/g\+\+$'`
if [ $? -ne 0 ]; then
	echo "FAILED"
	echo "Unable to find g++, do you have slocate or g++ installed??"
	echo " "
	exit 1
else
	echo "OK"
fi

echo -ne "Checking GNU Bison..."
YACC=`slocate bison | grep bin | egrep '\/bison$'`
if [ $? -ne 0 ]; then
	echo "FAILED"
	echo "Unable to find GNU Bison, do you have slocate or GNU Bison installed??"
	echo " "
	exit 1
else
	echo "OK"
fi

echo -ne "Checking GNU Flex..."
LEX=`slocate flex | grep bin | egrep '\/flex$'`
if [ $? -ne 0 ]; then
	echo "FAILED"
	echo "Unable to find GNU Flex, do you have slocate or GNU Flex installed??"
	echo " "
	exit 1
else
	echo "OK"
fi

GCCVERSION=`gcc --version | grep gcc | awk '{print $3}' | cut -f1 -d'.'`
if [ "$GCCVERSION" -ge 3 ]; then
DEFINES="$DEFINES -DUSING_GCC3 "
else
DEFINES="$DEFINES -std=c99 "
fi

GCCREVISION=`gcc --version | grep gcc | awk '{print $3}' | cut -f2 -d'.'`
if [ "$GCCREVISION" -ge 3 ]; then
DEFINES="$DEFINES -DGCC_REVISION${GCCREVISION} -DGCC_${GCCVERSION}_${GCCREVISION}"
fi


echo "CC=$GPP
YACC=$YACC
LEX=$LEX" >> Makefile


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
echo "CFLAGS=-Wall \$(DEBUG) \$(OPTIMIZE) -DSOLARIS=1 -DSOLARIS2$OSVER=1 -I../../common -I../../base/src -I. -c -DUSE_NEW=1  -D_STRUCTURED_PROC $SDLCMD $DEFINES" >> Makefile
if [ $OSVER -eq 8 ]; then
	DEFINES="$DEFINES -DSOLARIS8"
	if [ $THREADMODE = 'SDL_THREADS' ]; then
 			echo "LIBS=-lposix4 -lsocket -ldl $SDLCMD $NETLIB" >> Makefile
	else
		if [ $THREADMODE = 'PTHREADS' ]; then
 			echo "LIBS=-lposix4 -lsocket -ldl -lposix -lpthread $SDLCMD $NETLIB" >> Makefile
		else
			if [ $THREADMODE = 'SDL_THREADS' ]; then
 				echo "LIBS=-lposix4 -lsocket -ldl -lposix $SDLCMD $NETLIB" >> Makefile
			else
				echo "LIBS=-I`$(PTHCONFIG) --libdir` `$(PTHCONFIG) --libs` -lrt -lsocket -ldl $SDLCMD $NETLIB" >> Makefile
			fi
		fi
	fi
else
	if [ $OSVER -eq 6 ]; then
		DEFINES="$DEFINES -DSOLARIS6"
		if [ $THREADMODE = 'SDL_THREADS' ]; then
 				echo "LIBS=-lposix4 -lsocket -ldl $SDLCMD $NETLIB" >> Makefile
		else
			if [ $THREADMODE = 'PTHREADS' ]; then
 				echo "LIBS=-lposix4 -lsocket -ldl -lposix -lpthread $SDLCMD $NETLIB" >> Makefile
			else
				echo "LIBS=-I`$(PTHCONFIG) --libdir` `$(PTHCONFIG) --libs` -lposix4 -lsocket -ldl $SDLCMD $NETLIB" >> Makefile
			fi
		fi
	else
		echo "We haven't tested this on Solaris 7 yet"
		DEFINES="$DEFINES -DSOLARIS7"
		exit 1
	fi
fi

echo "INSTALLDIR=$PREFIX
LIBNAME=${MYLIBNAME}.so.${MYVERSION}
SONAME=${MYLIBNAME}.so
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
CFLAGS=-Wall \$(DEBUG) \$(OPTIMIZE) -I../../common -I../../base/src -I. -c $DEFINES -Wimplicit -Wreturn-type -Wunused -Wswitch -Wcomment -Wparentheses -Wpointer-arith -Wmissing-prototypes $SDLCFLAGS" >> Makefile
if [ $THREADMODE = 'SDL_THREADS' ]; then
	echo "LIBS=-ldl -lrt $SDLCMD $NETLIB" >> Makefile
else
	if [ $THREADMODE = 'PTHREADS' ]; then
		echo "LIBS=-ldl -lrt -lpthread $NETLIB" >> Makefile
	else
		echo 'LIBS=-I`$(PTHCONFIG) --libdir` `$(PTHCONFIG) --libs` -lrt -ldl `sdl-config --libs` $NETLIB' >> Makefile
	fi
fi
echo "INSTALLDIR=$PREFIX
LIBNAME=${MYLIBNAME}.so.${MYVERSION}
SONAME=${MYLIBNAME}.so
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

echo "\$(LIBNAME): $DEPS " >> Makefile
echo -ne "\t\$(CC) \$(BUILDLIB) -o \$(LIBNAME) $DEPS\n" >> Makefile
#echo -ne "\tcd ../../common ; ./genheader.sh $DEFINES\n" >> Makefile
echo -ne "\tcp -vf \$(LIBNAME) ../../libs/ \n" >> Makefile
echo -ne "\tcd ../../libs ; ln -sf \$(LIBNAME) \$(SONAME) \n" >> Makefile
echo -ne "\t@echo -ne \"\\\\nNow type make install to install this package\\\\n\"\n\n" >> Makefile

for src in `ls *.cpp`
do
 OUTPUT=`echo $src | sed 's/cpp/o/'`
 HEADER=`echo $src | sed 's/cpp/h/'`
 DDEPS="$OUTPUT: $src "
 echo -ne "\nAdding: $src\n"
 for inc in `cat $src | grep "#include" | sed 's/#include.*[\"|\<]\(.*\)[\"|\>]/\1/'`
 do
	 if  [ -f "$inc" ] ; then
		DDEPS="$DDEPS $inc"
	 	echo -ne "\tDepends on: $inc "
		NDEPS=`get_include_deps $inc`
		echo $NDEPS
		DDEPS="$DDEPS $NDEPS"
		#echo " "
	 fi
 done
 echo $DDEPS >> Makefile
 #echo "$OUTPUT: $src $HEADER" >> Makefile 
 echo -ne "\t\$(CC) \$(CFLAGS) -o $OUTPUT $src\n\n" >> Makefile
done


echo 'clean:
	rm -f *.o $(LIBNAME) core ../../common/xvr2.h ../../common/xvr2config.h
	touch ../../common/xvr2config.h
	touch ../../common/xvr2.h

rebuild: clean all

install: all
	mkdir -p $(INSTALLDIR)/include
	mkdir -p $(INSTALLDIR)/include/xvr2
	mkdir -p $(INSTALLDIR)/lib
	cp *.h $(INSTALLDIR)/include/xvr2
	cp ../../common/*.h $(INSTALLDIR)/include/
	cp $(LIBNAME) $(INSTALLDIR)/lib
	rm -f $(INSTALLDIR)/lib/$(SONAME)
	ln -s $(INSTALLDIR)/lib/$(LIBNAME) $(INSTALLDIR)/lib/$(SONAME)
	/sbin/ldconfig

cleaninstall: clean install' >> Makefile


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
rm -f ../../common/xvr2.h
rm -f ../../common/xvr2config.h
touch ../../common/xvr2.h
touch ../../common/xvr2config.h
