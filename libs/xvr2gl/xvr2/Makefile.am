## Source directory

h_sources = Object3D.h World.h xglDisplayDriver.h xglDisplay.h xglExceptions.h \
	    _xvr2glClassNames.h

cc_sources = Display.cpp DisplayDriver.cpp Object3D.cpp xglExceptions.cpp \
	     _xvr2glClassNames.cpp


library_includedir=$(includedir)/$(GENERIC_LIBRARY_NAME)/GL
library_include_HEADERS = $(h_sources)

INCLUDES = -I$(top_srcdir)

lib_LTLIBRARIES=libxvr2gl.la
libxvr2gl_la_SOURCES= $(h_sources) $(cc_sources)
libxvr2gl_la_LDFLAGS= -version-info $(GENERIC_LIBRARY_VERSION) -release $(GENERIC_RELEASE)
