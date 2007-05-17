THIS_DIR=`pwd`
VERSION=`cat ../VERSION`
cd src
./configure.sh "$@" --version=${VERSION} --with-name=libxvr2net
cd ..
echo "VERSION=${VERSION}

all: src/libxvr2net.so.${VERSION}

clean:
	cd src ; make -f Makefile clean

install:
	cd src ; make -f Makefile install

src/libxvr2net.so.${VERSION}:
	cd src ; make -f Makefile" > Makefile
