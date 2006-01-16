THIS_DIR=`pwd`
VERSION=`cat ../VERSION`
cd src
./configure.sh "$@" --version=${VERSION} --with-name=libxvr2gfx
cd ..
echo "VERSION=${VERSION}

all: src/libxvr2gfx.so.${VERSION}

clean:
	rm -rf doc/html doc/latex
	cd src ; make -f Makefile clean

install:
	cd src ; make -f Makefile install

src/libxvr2gfx.so.${VERSION}:
	cd src ; make -f Makefile" > Makefile
