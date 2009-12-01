all: base/src/libxvr2.so.0.6.6 step2 step3 step4 step5 step6

docs: step7

base/src/libxvr2.so.0.6.6:
	cd base ; make -f Makefile

step2: base/src/libxvr2.so.0.6.6
	cd util ; make -f Makefile

step3: base/src/libxvr2.so.0.6.6
	cd gfx ; make -f Makefile

step4: base/src/libxvr2.so.0.6.6 step2
	cd gui ; make -f Makefile

step5: base/src/libxvr2.so.0.6.6
	cd db ; make -f Makefile

step6: base/src/libxvr2.so.0.6.6 step2 step5
	cd drivers ; make -f Makefile
	
step7:
	cat Doxyfile.tmpl | sed 's/XVR_VERSION_TAG/0.6.6/' > Doxyfile 
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
	cd src ; make -f Makefile
