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

cd math
./configure.sh "$@"
cd $THIS_DIR

cd gl
./configure.sh "$@"
cd $THIS_DIR

cd ui
./configure.sh "$@"
cd $THIS_DIR



echo "
baselib=libxvr2.so.${VERSION}
utillib=libxvr2util.so.${VERSION}
dblib=libxvr2db.so.${VERSION}
netlib=libxvr2net.so.${VERSION}
mathlib=libxvr2math.so.${VERSION}
gllib=libxvr2gl.so.${VERSION}
uilib=libxvr2ui.so.${VERSION}

baselibpath=base/src/${baselib}
utillibpath=util/src/${utillib}
dblibpath=db/src/${dblib}
netlibpath=net/src/${netlib}
mathlibpath=math/src/${mathlib}
gllibpath=gl/src/${gllib}
uilibpath=ui/src/${uilib}

all: step1 step2 step3 step4 step5 step6 step7 installmsg

step1: ${baselibpath}

step2: ${utillibpath}

step3: ${dblibpath}

step4: ${netlibpath}

step5: ${mathlibpath}

step6: ${gllibpath}

step7: ${uilibpath}

docs: step100

${baselibpath}: base/src/*.h base/src/*.cpp
	cd base/src ; make -f Makefile

${utillibpath}: step1 util/src/*.h util/src/*.cpp
	cd util/src ; make -f Makefile

${dblibpath}: step1 step2 db/src/*.h db/src/*.cpp
	cd db/src ; make -f Makefile

${netlibpath}: step1 step2 net/src/*.h net/src/*.cpp
	cd net/src ; make -f Makefile

${mathlibpath}: step1 step2 math/src/*.h math/src/*.cpp
	cd math/src ; make -f Makefile

${gllibpath}: step1 step2 step5 gl/src/*.h gl/src/*.cpp
	cd gl/src ; make -f Makefile

${uilibpath}: step1 step2 step5 step6 ui/src/*.h ui/src/*.cpp
	cd ui/src ; make -f Makefile

installmsg:
	@echo
	@echo
	@echo 'Now (as root) type: make install'

drivers: step1 step2 step3 step4
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
	cd math/src ; make -f Makefile clean
	cd gl/src ; make -f Makefile clean
	cd ui/src ; make -f Makefile clean
	cd drivers ; make -f Makefile clean

install:
	cd base/src ; make -f Makefile install
	cd util/src ; make -f Makefile install
	cd db/src ; make -f Makefile install
	cd net/src ; make -f Makefile install
	cd math/src ; make -f Makefile install
	cd gl/src ; make -f Makefile install
	cd ui/src ; make -f Makefile install
	@echo
	@echo "To compile the provided drivers type:"
	@echo "make drivers"

rebuild: clean all

lib:
	cd src ; make -f Makefile" > Makefile

	touch .lib
