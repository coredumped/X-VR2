# $Id$
# X-VR2 DB PostgreSQL RDBMS Provider driver.

h_sources = pgsql-drvng.h

cc_sources = pgsql-drvng.cpp


INCLUDES = -I$(top_srcdir) -I../../../Core/xvr2 -I../../../SQL/xvr2 \
			-I $(PGSQL_INCLUDES)

lib_LTLIBRARIES=pgsql_driver.la
pgsql_driver_la_CFLAGS= -DDRV_VERSION=0 -DDRV_REVISION=3
pgsql_driver_la_CXXFLAGS= -DDRV_VERSION=0 -DDRV_REVISION=3
pgsql_driver_la_SOURCES= $(h_sources) $(cc_sources)
pgsql_driver_la_LDFLAGS= -module -version-info $(GENERIC_LIBRARY_VERSION) -release $(GENERIC_RELEASE) $(PGSQL_LIBS)

#LDADD=

rebuild: clean all
