VERSION=`cat VERSION`
THIS_DIR=`pwd`
cd base
./configure.sh "$@"
cd $THIS_DIR

cd util
./configure.sh "$@"
cd $THIS_DIR

cd net
./configure.sh "$@"
cd $THIS_DIR

cd db
./configure.sh "$@"
cd $THIS_DIR

cd drivers
./configure.sh "$@"
cd $THIS_DIR



echo "all: base/src/libxvr2.so.${VERSION} step2 step3 step4

docs: step100

base/src/libxvr2.so.${VERSION}: base/src/*.h base/src/*.cpp
	cd base/src ; make -f Makefile

step2: base/src/libxvr2.so.${VERSION} util/src/*.h util/src/*.cpp
	cd util/src ; make -f Makefile

step3: base/src/libxvr2.so.${VERSION} step2 db/src/*.h db/src/*.cpp
	cd db/src ; make -f Makefile

step4: base/src/libxvr2.so.${VERSION} step2 net/src/*.h net/src/*.cpp
	cd net/src ; make -f Makefile
	@echo
	@echo
	@echo 'Now (as root) type: make install'

drivers: base/src/libxvr2.so.${VERSION} all
	cd drivers ; make -f Makefile
	@echo
	@echo
	@echo 'You can now safely install everything, (as root) type'
	@echo "make drivers-install"

drivers-install: drivers
	cd drivers ; make -f Makefile install
	
step100:
	cat Doxyfile.tmpl | sed 's/XVR_VERSION_TAG/${VERSION}/' > Doxyfile 
	doxygen Doxyfile
	
clean:
	rm -rf doc/html doc/latex
	cd base/src ; make -f Makefile clean
	cd util/src ; make -f Makefile clean
	cd net/src ; make -f Makefile clean
	cd db/src ; make -f Makefile clean
	cd drivers ; make -f Makefile clean

install:
	cd base/src ; make -f Makefile install
	cd util/src ; make -f Makefile install
	cd db/src ; make -f Makefile install
	cd net/src ; make -f Makefile install
	@echo
	@echo "To compile the provided drivers type:"
	@echo "make drivers"

rebuild: clean all

lib:
	cd src ; make -f Makefile" > Makefile

	touch .lib
