THIS_DIR=`pwd`
VERSION=`cat VERSION`
LIBNAME=libxvr2gl
cd src
./configure.sh "$@" --version=${VERSION} --with-name=${LIBNAME}
cd ..
cd drivers
./configure.sh "$@" --version=${VERSION}
cd ..
echo "VERSION=${VERSION}

all: src/${LIBNAME}.so.${VERSION} drivers demo

clean:
	cd src ; make -f Makefile clean
	cd demos ; make -f Makefile clean
	cd drivers ; make -f Makefile clean

install:
	cd src ; make -f Makefile install

demo:
	cd demos ; make -f Makefile

drivers: alldrivers

alldrivers: drivers/sdl/xvr2_sdl_driver.so.$VERSION

drivers/sdl/xvr2_sdl_driver.so.$VERSION:
	cd drivers ; make -f Makefile

src/${LIBNAME}.so.${VERSION}: src/*.cpp src/*.h
	cd src ; make -f Makefile

drivers-install: alldrivers
	cd drivers ; make -f Makefile install

rebuild: clean all
" > Makefile
