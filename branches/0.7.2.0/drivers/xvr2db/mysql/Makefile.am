# $Id$


h_sources = mysql-drv.h

cc_sources = mysql-drv.cpp

INCLUDES = -I$(top_srcdir)

lib_LTLIBRARIES=mysql_driver-0.7.1.1.la

mysql_driver_0_7_1_1_la_SOURCES= $(h_sources) $(cc_sources)

mysql_driver_0_7_1_1_la_LDFLAGS= -module -version-info $(GENERIC_LIBRARY_VERSION) -release $(GENERIC_RELEASE)

rebuild: clean all

