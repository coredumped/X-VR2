# $Id$
# X-VR2 DB Sqlite RDBMS Provider driver.

h_sources = sqlite-drv.h

cc_sources = sqlite-drv.cpp


INCLUDES = -I$(top_srcdir) -I../../../Core/xvr2 -I../../../DB/xvr2 \
			-I $(SQLITE_INCLUDES)

lib_LTLIBRARIES=sqlite_driver.la
sqlite_driver_la_CFLAGS= -DDRV_VERSION=0 -DDRV_REVISION=3
sqlite_driver_la_CXXFLAGS= -DDRV_VERSION=0 -DDRV_REVISION=3
sqlite_driver_la_SOURCES= $(h_sources) $(cc_sources)
sqlite_driver_la_LDFLAGS= -module -version-info $(GENERIC_LIBRARY_VERSION) -release $(GENERIC_RELEASE) $(SQLITE_LIBS)

rebuild: clean all
