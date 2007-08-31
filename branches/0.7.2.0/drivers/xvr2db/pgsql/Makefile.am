# $Id$


h_sources = pgsql-drvng.h

cc_sources = pgsql-drvng.cpp

#library_includedir=$(includedir)/$(GENERIC_LIBRARY_NAME)
#library_include_HEADERS = $(h_sources)

INCLUDES = -I$(top_srcdir)

lib_LTLIBRARIES=pgsql_driver-0.7.2.0.la
pgsql_driver_0_7_2_0_la_SOURCES= $(h_sources) $(cc_sources)
pgsql_driver_0_7_2_0_la_LDFLAGS= -module -version-info $(GENERIC_LIBRARY_VERSION) -release $(GENERIC_RELEASE)
