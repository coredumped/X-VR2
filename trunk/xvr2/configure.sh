VERSION=`cat VERSION`
THIS_DIR=`pwd`
cd base
./configure.sh "$@"
cd $THIS_DIR
cd util
./configure.sh "$@"
cd $THIS_DIR
cd db
./configure.sh "$@"
cd $THIS_DIR
cd gfx
./configure.sh "$@"
cd $THIS_DIR
cd gui
./configure.sh "$@"
cd $THIS_DIR
cd drivers
./configure.sh "$@"
cd $THIS_DIR



echo "all: base/src/libxvr2.so.${VERSION} step2 step3 step4 step5 step6

docs: step7

base/src/libxvr2.so.${VERSION}: base/src/*.h base/src/*.cpp
	cd base/src ; make -f Makefile

step2: base/src/libxvr2.so.${VERSION} util/src/*.h util/src/*.cpp
	cd util/src ; make -f Makefile

step3: base/src/libxvr2.so.${VERSION} gfx/src/*.h gfx/src/*.cpp
	cd gfx/src ; make -f Makefile

step4: base/src/libxvr2.so.${VERSION} step2 gui/src/*.h gui/src/*.cpp
	cd gui/src ; make -f Makefile

step5: base/src/libxvr2.so.${VERSION} step2 db/src/*.h db/src/*.cpp
	cd db/src ; make -f Makefile

step6: base/src/libxvr2.so.${VERSION} step2 step5
	cd drivers ; make -f Makefile
	
step7:
	cat Doxyfile.tmpl | sed 's/XVR_VERSION_TAG/${VERSION}/' > Doxyfile 
	doxygen Doxyfile
	
clean:
	rm -rf doc/html doc/latex
	cd base/src ; make -f Makefile clean
	cd gfx/src ; make -f Makefile clean
	cd gui/src ; make -f Makefile clean
	cd util/src ; make -f Makefile clean
	cd db/src ; make -f Makefile clean
	cd drivers ; make -f Makefile clean

install:
	cd base/src ; make -f Makefile install
	cd gfx/src ; make -f Makefile install
	cd gui/src ; make -f Makefile install
	cd util/src ; make -f Makefile install
	cd db/src ; make -f Makefile install
	cd drivers ; make -f Makefile install

rebuild: clean all

lib:
	cd src ; make -f Makefile" > Makefile

	touch .lib
