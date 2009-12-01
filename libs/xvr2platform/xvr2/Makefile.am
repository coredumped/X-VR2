## Source directory

h_sources = PlatformException.h Platform.h CPU.h ProcessRunner.h

cc_sources = PlatformException.cpp Platform.cpp CPU.cpp ProcessRunner.cpp

library_includedir=$(includedir)/$(GENERIC_LIBRARY_NAME)
library_include_HEADERS = $(h_sources)

INCLUDES = -I$(top_srcdir)

lib_LTLIBRARIES=libxvr2platform-0.7.1.1.la
libxvr2platform_0_7_1_1_la_SOURCES= $(h_sources) $(cc_sources)
libxvr2platform_0_7_1_1_la_LDFLAGS= -version-info $(GENERIC_LIBRARY_VERSION) -release $(GENERIC_RELEASE)
