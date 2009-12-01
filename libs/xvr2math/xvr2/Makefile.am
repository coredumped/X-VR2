## Source directory

h_sources = MathException.h PolygonAlignmentException.h Polygon.h Vector2.h \
	    Vector3.h Vector4.h _xvr2mathClassNames.h xvr2mathdefs.h

cc_sources = MathException.cpp PolygonAlignmentException.cpp Polygon.cpp \
	     Vector2.cpp Vector3.cpp Vector4.cpp _xvr2mathClassNames.cpp \
	     xvr2mathdefs.cpp

library_includedir=$(includedir)/$(GENERIC_LIBRARY_NAME)
library_include_HEADERS = $(h_sources)

INCLUDES = -I$(top_srcdir)

lib_LTLIBRARIES=libxvr2math-0.7.1.0.la
libxvr2math_0_7_1_0_la_SOURCES= $(h_sources) $(cc_sources)
libxvr2math_0_7_1_0_la_LDFLAGS= -version-info $(GENERIC_LIBRARY_VERSION) -release $(GENERIC_RELEASE)
