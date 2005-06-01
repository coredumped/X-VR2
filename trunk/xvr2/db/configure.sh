#!/bin/bash
#
# $Id$

source ../buildtools/functions.sh
get_libname "$@"
get_libversion "$@"
LIBNAMEX="${MYLIBNAME}.${MYVERSION}"
THIS_DIR=`pwd`
cd src
./configure.sh "$@"
cd $THIS_DIR
echo "
all: src/${LIBNAMEX}

clean:
	cd src ; make -f Makefile clean

install:
	cd src ; make -f Makefile install

src/${LIBNAMEX}: src/*.h src/*.cpp
	cd src ; make -f Makefile" > Makefile
