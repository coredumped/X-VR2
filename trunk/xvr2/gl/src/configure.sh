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
	echo "--help				Print this usage message"
	echo "--use-debug			* Activate debug message printing"
	echo "--no-debug			Dectivate debug message printing"
	echo "--disable-mantainer-mode		Disable maintainer mode (Remove symbols in object files)"
	echo "--enable-mantainer-mode		Enable maintainer mode (Leave symbols in object files)"
	echo "--debug-mutexes			Show status messages while locking/unlocking mutexes"
	echo "--prefix				Specifies the prefix installation directory"
	echo " "
	echo " "
	exit 0
}

DEBUGMODE=1
MAINTAINER="-g"
PREFIX="/usr/local"
XVR2LIBS=" -lxvr2 "

echo " "
for option in `echo "$@"`
do
	if [ "$option" = '--help' ]; then
		usage
	else
		if [ "$option" = '-h' ]; then
			usage
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

done

XVR2CFLAGS="`xvr2-config.sh --cflags` "

DEFINES="-DXVR2MATH_VERSION=\"\\\"${MYVERSION}\\\"\" "

if [ "$DEBUGMODE" -eq 1 ]; then
	DEFINES="$DEFINES -DUSE_DEBUG "
fi

######################## PRE-DEFINES ##########################
echo "DEFINES: $DEFINES"

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
DEFINES="$DEFINES -DSOLARIS"
echo "
DEBUG=$MAINTAINER $DEBUGSTRING $DEBUG_MUTEXES
#DEBUG=
OPTIMIZE=" >> Makefile
OSVER=`uname -r | sed 's/5\.//'`
echo $OSVER
echo "CFLAGS=-Wall \$(DEBUG) \$(OPTIMIZE) -DSOLARIS=1 -DSOLARIS2$OSVER=1 -I. -c -DUSE_NEW=1 ${XVR2CFLAGS} -D_STRUCTURED_PROC $SDLCMD $DEFINES" >> Makefile
echo "LIBS=$XVR2LIBS -lm" >> Makefile
echo "INSTALLDIR=$PREFIX
LIBNAME=${MYLIBNAME}.so.${MYVERSION}
SONAME=${MYLIBNAME}.so
BUILDLIB=-G
all: \$(LIBNAME)" >> Makefile

else

DEFINES="$DEFINES -DUSING_LINUX -D__GNU"
echo "
DEBUG=$MAINTAINER $DEBUGSTRING $DEBUG_MUTEXES
#DEBUG=$MAINTAINER -DUSE_DEBUG=$DEBUGMODE
#DEBUG=
OPTIMIZE=
CFLAGS=-Wall \$(DEBUG) \$(OPTIMIZE) -I. ${XVR2CFLAGS} -c $DEFINES -Wimplicit -Wreturn-type -Wunused -Wswitch -Wcomment -Wparentheses -Wpointer-arith $SDLCFLAGS" >> Makefile
echo "LIBS=$XVR2LIBS -lm" >> Makefile
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
echo -ne "\tcp -vf \$(LIBNAME) ../libs/ \n" >> Makefile
echo -ne "\tcd ../libs ; ln -sf \$(LIBNAME) \$(SONAME) \n" >> Makefile
echo -ne "\trm -f ../xvr2/*.h \n" >> Makefile
echo -ne "\tcp -vf *.h ../xvr2/ \n" >> Makefile
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
	rm -f *.o $(LIBNAME) core

rebuild: clean all

install: all
	mkdir -p $(INSTALLDIR)/include
	mkdir -p $(INSTALLDIR)/include/xvr2
	mkdir -p $(INSTALLDIR)/lib
	cp *.h $(INSTALLDIR)/include/xvr2
	cp $(LIBNAME) $(INSTALLDIR)/lib
	rm -f $(INSTALLDIR)/lib/$(SONAME)
	ln -s $(INSTALLDIR)/lib/$(LIBNAME) $(INSTALLDIR)/lib/$(SONAME)
	/sbin/ldconfig

cleaninstall: clean install' >> Makefile


echo " "
echo " "
