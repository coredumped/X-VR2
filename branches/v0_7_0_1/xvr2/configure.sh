VERSION=`cat VERSION`
THIS_DIR=`pwd`
baselib=libxvr2.so
utillib=libxvr2util.so
dblib=libxvr2db.so
netlib=libxvr2net.so
mathlib=libxvr2math.so
gllib=libxvr2gl.so
uilib=libxvr2ui.so

mkdir -p include/xvr2

cd base
./configure.sh "$@" --version="$VERSION" --with-name=$baselib
cd $THIS_DIR

cd util
./configure.sh "$@" --version="$VERSION" --with-name=$utillib
cd $THIS_DIR

cd net
./configure.sh "$@" --version="$VERSION" --with-name=$netlib
cd $THIS_DIR

cd db
./configure.sh "$@" --version="$VERSION" --with-name=$dblib
cd $THIS_DIR

cd math
./configure.sh "$@" --version="$VERSION" --with-name=$mathlib
cd $THIS_DIR

cd gl
./configure.sh "$@" --version="$VERSION" --with-name=$gllib
cd $THIS_DIR

cd ui
./configure.sh "$@" --version="$VERSION" --with-name=$uilib
cd $THIS_DIR

cd drivers
./configure.sh "$@" --version="$VERSION"
cd $THIS_DIR

echo "
baselib=${baselib}.${VERSION}
utillib=${utillib}.${VERSION}
dblib=${dblib}.${VERSION}
netlib=${netlib}.${VERSION}
mathlib=${mathlib}.${VERSION}
gllib=${gllib}.${VERSION}
uilib=${uilib}.${VERSION}

baselibpath=base/src/${baselib}
utillibpath=util/src/${utillib}
dblibpath=db/src/${dblib}
netlibpath=net/src/${netlib}
mathlibpath=math/src/${mathlib}
gllibpath=gl/src/${gllib}
uilibpath=ui/src/${uilib}

all: step1 step2 step3 step4 step5 step6 step7 installmsg

step0: include/xvr2
	mkdir -p include/xvr2
	cp -f base/src/*.h include/xvr2
	cp -f db/src/*.h include/xvr2
	cp -f util/src/*.h include/xvr2
	cp -f net/src/*.h include/xvr2
	cp -f math/src/*.h include/xvr2
	cp -f gl/src/*.h include/xvr2
	cp -f ui/src/*.h include/xvr2

step1: step0 \$(baselibpath)

step2: \$(utillibpath)

step3: \$(dblibpath)

step4: \$(netlibpath)

step5: \$(mathlibpath)

step6: \$(gllibpath)

step7: \$(uilibpath)

docs: step100

\$(baselibpath): base/src/*.h base/src/*.cpp
	cd base/src ; cp -f *.h ../../include/xvr2/ ; make -f Makefile

\$(utillibpath): step1 util/src/*.h util/src/*.cpp
	cd util/src ; cp -f *.h ../../include/xvr2/ ; make -f Makefile

\$(dblibpath): step1 step2 db/src/*.h db/src/*.cpp
	cd db/src ; cp -f *.h ../../include/xvr2/ ; make -f Makefile

\$(netlibpath): step1 step2 net/src/*.h net/src/*.cpp
	cd net/src ; cp -f *.h ../../include/xvr2/ ; make -f Makefile

\$(mathlibpath): step1 step2 math/src/*.h math/src/*.cpp
	cd math/src ; cp -f *.h ../../include/xvr2/ ; make -f Makefile

\$(gllibpath): step1 step2 step5 gl/src/*.h gl/src/*.cpp
	cd gl/src ; cp -f *.h ../../include/xvr2/ ; make -f Makefile

\$(uilibpath): step1 step2 step5 step6 ui/src/*.h ui/src/*.cpp
	cd ui/src ; cp -f *.h ../../include/xvr2/ ; make -f Makefile

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
	@rm -rf include/xvr2/*
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
