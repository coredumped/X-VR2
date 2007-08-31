# $Id$


h_sources = pgsql-drvng.h

cc_sources = pgsql-drvng.cpp

#library_includedir=$(includedir)/$(GENERIC_LIBRARY_NAME)
#library_include_HEADERS = $(h_sources)

INCLUDES = -I$(top_srcdir)

lib_LTLIBRARIES=pgsql_driver-0.7.1.1.la
pgsql_driver_0_7_1_1_la_SOURCES= $(h_sources) $(cc_sources)
pgsql_driver_0_7_1_1_la_LDFLAGS= -module -version-info $(GENERIC_LIBRARY_VERSION) -release $(GENERIC_RELEASE)
