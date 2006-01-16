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

THREADMODE=PTHREADS
DEBUGMODE=1
MAINTAINER="-gstabs+"
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

CC_OPTIONS=-fPIC

DEFINES="$SCHUNK"
echo $SCHUNK

DEFINES="$DEFINES -DUNIX_SOCKETS -DUSE_POSIX_THREADS -D_REENTRANT -D_THREAD_SAFE"
if [ "$DEBUGMODE" -eq 1 ]; then
	DEFINES="$DEFINES -DUSE_DEBUG "
fi

######################## PRE-DEFINES ##########################
DEFINES="$DEFINES -DHAVE_MEMCPY -DHAVE_STRCPY -DHAVE_POW -DHAVE_STRTOL"

echo "DEFINES: $DEFINES"

if [ $THREADMODE = 'PTH' ]; then
	echo "PTHCONFIG=pth-config" >> Makefile
fi
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

DEFINES="$DEFINES -DGCC_MAJOR_VERSION=${GCCVERSION} -DGCC_MINOR_VERSION=${GCCREVISION}"

echo "CC=$GPP
YACC=$YACC
LEX=$LEX" >> Makefile

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
	echo "CFLAGS=-Wall \$(DEBUG) \$(OPTIMIZE) -DSOLARIS=1 -DSOLARIS2$OSVER=1 -I../../common -I ${XVR2_SOURCE_DIR}/include -I. -c -DUSE_NEW=1  -D_STRUCTURED_PROC $CC_OPTIONS $DEFINES" >> Makefile
	if [ $OSVER -eq 8 ]; then
		DEFINES="$DEFINES -DSOLARIS8"
		if [ $THREADMODE = 'PTHREADS' ]; then
			echo "LIBS=-lposix4 -ldl -lposix -lpthread" >> Makefile
		else
			echo "LIBS=-I`$(PTHCONFIG) --libdir` `$(PTHCONFIG) --libs` -lrt -ldl" >> Makefile
		fi
	else
		if [ $OSVER -eq 6 ]; then
			DEFINES="$DEFINES -DSOLARIS6"
			if [ $THREADMODE = 'PTHREADS' ]; then
				echo "LIBS=-lposix4 -ldl -lposix -lpthread" >> Makefile
			else
				echo "LIBS=-I`$(PTHCONFIG) --libdir` `$(PTHCONFIG) --libs` -lposix4 -ldl" >> Makefile
			fi
		else
			echo "We haven't tested this on Solaris 7 yet"
			DEFINES="$DEFINES -DSOLARIS7"
			exit 1
		fi
	fi

	echo "INSTALLDIR=$PREFIX
LIBNAME=${MYLIBNAME}.${MYVERSION}
SONAME=${MYLIBNAME}
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
CFLAGS=-Wall \$(DEBUG) \$(OPTIMIZE) -I../../common -I ${XVR2_SOURCE_DIR}/include -I. -c $CC_OPTIONS -Wimplicit -Wreturn-type -Wunused -Wswitch -Wcomment -Wparentheses -Wpointer-arith $DEFINES " >> Makefile
	if [ $THREADMODE = 'PTHREADS' ]; then
		echo "LIBS=-ldl -lrt -lpthread" >> Makefile
	else
		echo 'LIBS=-I`$(PTHCONFIG) --libdir` `$(PTHCONFIG) --libs` -lrt -ldl' >> Makefile
	fi
	echo "INSTALLDIR=$PREFIX
LIBNAME=${MYLIBNAME}.${MYVERSION}
SONAME=${MYLIBNAME}
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

echo "\$(LIBNAME): $DEPS parsers/config-parser.o parsers/config-lexer.o" >> Makefile
echo -ne "\t\$(CC) \$(BUILDLIB) -o \$(LIBNAME) $DEPS parsers/config-lexer.o parsers/config-parser.o\n" >> Makefile
echo -ne "\tcd ../../common ; ./genheader.sh $DEFINES -D'__XVR2_PREFIX_DIR \"${PREFIX}\"' -D'__XVR2_VERSION_STRING \"${MYVERSION}\"'\n" >> Makefile
echo -ne "\tcd ../../scripts ; ./gen-config.sh ${PREFIX}\n" >> Makefile
echo -ne "\tcp -vf \$(LIBNAME) ../../libs/ \n" >> Makefile
echo -ne "\tcd ../../libs ; ln -sf \$(LIBNAME) \$(SONAME) \n" >> Makefile
echo -ne "\t@echo -ne \"\\\\nNow type make install to install this package\\\\n\"\n\n" >> Makefile

for src in `ls *.cpp`
do
	OUTPUT=`echo $src | sed 's/cpp/o/'`
	HEADER=`echo $src | sed 's/cpp/h/'`
	DDEPS="$OUTPUT: $src "
	echo -ne "\nAdding: $src\n"
	for inc in `cat $src | grep "#include" | sed 's/#include.*[\"|\<]\(.*\)[\"|\>]/\1/' | grep xvr2 | sed 's/xvr2\///'`
	do
		#if  [ -f "$inc" ] ; then
			DDEPS="$DDEPS $inc"
			echo -ne "\tDepends on: $inc "
			NDEPS=`get_include_deps $inc`
			echo $NDEPS
			DDEPS="$DDEPS $NDEPS"
			#echo " "
		#fi
	done
	echo $DDEPS >> Makefile
	#echo "$OUTPUT: $src $HEADER" >> Makefile 
	echo -ne "\t\$(CC) \$(CFLAGS) -o $OUTPUT $src\n\n" >> Makefile
done
echo "parsers/config-parser.o: parsers/config.y parsers/config.lex" >> Makefile
echo -ne "\tcd parsers ; export CFLAGS=\"\$(CFLAGS)\" ; export YACC=\"\$(YACC)\" ; export LEX=\"\$(LEX)\" ; make config-parser.o\n\n" >> Makefile
echo "parsers/config-lexer.o: parsers/config.y parsers/config.lex" >> Makefile
echo -ne "\tcd parsers ; export CFLAGS=\"\$(CFLAGS)\" ; export YACC=\"\$(YACC)\" ; export LEX=\"\$(LEX)\" ; make config-lexer.o\n\n" >> Makefile


echo 'clean:
	rm -f *.o $(LIBNAME) core ../../common/xvr2.h ../../common/xvr2config.h
	touch ../../common/xvr2config.h
	touch ../../common/xvr2.h
	cd parsers ; make clean

rebuild: clean all

install: all
	mkdir -p $(INSTALLDIR)/include
	mkdir -p $(INSTALLDIR)/include/xvr2
	mkdir -p $(INSTALLDIR)/lib
	mkdir -p $(INSTALLDIR)/bin
	cp *.h $(INSTALLDIR)/include/xvr2
	cp ../../common/*.h $(INSTALLDIR)/include/
	cp $(LIBNAME) $(INSTALLDIR)/lib
	rm -f $(INSTALLDIR)/lib/$(SONAME)
	ln -s $(INSTALLDIR)/lib/$(LIBNAME) $(INSTALLDIR)/lib/$(SONAME)
	cp ../../scripts/xvr2-config.sh $(INSTALLDIR)/bin/
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
	if [ $THREADMODE = 'PTHREADS' ]; then
		echo "	Threads:		POSIX Threads"
	else
		echo "	Threads:		GNU PTh"
	fi
fi

if [ "$MAINTAINER" = "-gstabs+" ]; then
	echo "	Maintainer:		ON"
else
	echo "	Maintainer:		OFF"
fi

echo "	----------------------------------"
echo " "
echo " "
rm -f ../../common/xvr2.h
rm -f ../../common/xvr2config.h
touch ../../common/xvr2.h
touch ../../common/xvr2config.h
