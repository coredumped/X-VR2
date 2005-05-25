THIS_DIR=`pwd`
VERSION=`cat VERSION`
LIBNAME=libxvr2ui
cd src
./configure.sh "$@" --version=${VERSION} --with-name=${LIBNAME}
cd ..
echo "VERSION=${VERSION}

all: src/${LIBNAME}.so.${VERSION} demo

clean:
	cd src ; make -f Makefile clean
	cd demos ; make -f Makefile clean

install:
	cd src ; make -f Makefile install

demo:
	cd demos ; make -f Makefile

src/${LIBNAME}.so.${VERSION}: src/*.cpp src/*.h
	cd src ; make -f Makefile

rebuild: clean all
" > Makefile
