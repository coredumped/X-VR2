#!/bin/bash
# $Id$
#
# Este script genera el makefile
#
#
source ../../buildtools/functions.sh

PLATFORM=`get_platform`
OS=`get_os`
PROCESSOR=`get_processor`
echo "" > Makefile
SQLFLAGS=" -I\`pg_config --includedir\` -I../../common "
THREADMODE=PTHREADS
SQLLIBS=' -L`pg_config --libdir` -lpq -lxvr2 -lxvr2db -lxvr2util '
DEBUGMODE=0
MAINTAINER="-gstabs+"
PREFIX="/usr/local"
DRV_VERSION=0
DRV_REVISION=2
DRIVER_FILENAME=pgsql_driver


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
									MAINTAINER="-gstabs+"
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

DEFINES="$DEFINES -DUNIX_SOCKETS -DUSE_POSIX_THREADS -D_REENTRANT -D_THREAD_SAFE"
if [ "$DEBUGMODE" -eq 1 ]; then
	DEFINES="$DEFINES -DUSE_DEBUG "
fi

echo "DEFINES: $DEFINES"

echo "Processor: $PROCESSOR, platform is $PLATFORM"

GPP=`find_gplusplus`
if [ $? -ne 0 ]; then
	exit 1
fi
YACC=`find_bison`
if [ $? -ne 0 ]; then
	exit 1
fi
LEX=`find_flex`
if [ $? -ne 0 ]; then
	exit 1
fi

GCCVERSION=`get_gcc_version $GPP`
GCCREVISION=`get_gcc_revision $GPP`
GCCFULLVERSION=`get_gcc_full_version $GPP`
if [ "$GCCVERSION" -ge 3 ]; then
	DEFINES="$DEFINES -DUSING_GCC3 "
else
        if [ "GCC_${GCCFULLVERSION}" != "GCC_2_96" ]; then
                DEFINES="$DEFINES -std=c99 "
		else
                DEFINES="$DEFINES -D__USE_ISOC99 "
        fi
fi

if [ "$GCCREVISION" -ge 3 ]; then
	DEFINES="$DEFINES -DGCC_REVISION${GCCREVISION} -DGCC_${GCCVERSION}_${GCCREVISION}"
fi

echo "CC=$GPP" >> Makefile

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
echo "CFLAGS=-Wall \$(DEBUG) \$(OPTIMIZE) -DSOLARIS=1 -DSOLARIS2$OSVER=1 -I ${XVR2_SOURCE_DIR}/include -I. -c -DUSE_NEW=1  -D_STRUCTURED_PROC $DEFINES $SQLFLAGS" >> Makefile
if [ $OSVER -eq 8 ]; then
	DEFINES="$DEFINES -DSOLARIS8"
	if [ $THREADMODE = 'PTHREADS' ]; then
 		echo "LIBS=-lposix4 -lposix $SQLLIBS" >> Makefile
	else
		echo "LIBS=-lposix4 $SQLLIBS" >> Makefile
	fi
else
	if [ $OSVER -eq 6 ]; then
		DEFINES="$DEFINES -DSOLARIS6"
		if [ $THREADMODE = 'PTHREADS' ]; then
 			echo "LIBS=-lposix4 -lposix $SQLLIBS" >> Makefile
		else
			echo "LIBS=-lposix4 $SQLLIBS" >> Makefile
		fi
	else
		echo "We haven't tested this on Solaris 7 yet"
		DEFINES="$DEFINES -DSOLARIS7"
		exit 1
	fi
fi

LIBS="$LIBS "

echo "INSTALLDIR=$PREFIX
LIBNAME=$DRIVER_FILENAME.so.${MYVERSION}
SONAME=$DRIVER_FILENAME.so
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
CFLAGS=-Wall \$(DEBUG) \$(OPTIMIZE) -I ${XVR2_SOURCE_DIR}/include -I. -c $DEFINES -Wimplicit -Wreturn-type -Wunused -Wswitch -Wcomment -Wparentheses -Wpointer-arith $SDLCFLAGS $SQLFLAGS" >> Makefile
echo "LIBS=$SQLLIBS" >> Makefile
echo "INSTALLDIR=$PREFIX
LIBNAME=$DRIVER_FILENAME.so.${MYVERSION}
SONAME=$DRIVER_FILENAME.so
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

if [ "$MAINTAINER" = "-gstabs+" ]; then
	echo "	Maintainer:		ON"
else
	echo "	Maintainer:		OFF"
fi

echo "	----------------------------------"
echo " "
echo " "
