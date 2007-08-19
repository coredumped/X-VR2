## Source directory

h_sources = DatabaseException.h Connection.h ConnectionMT.h Driver.h \
	    DriverInfo.h DriverManager.h Field.h ResultSet.h 

cc_sources = DatabaseException.cpp DBConnection.cpp DBConnectionMT.cpp DBDriver.cpp \
	     DBDriverInfo.cpp DBDriverManager.cpp DBField.cpp \
	     DBResultSet.cpp

library_includedir=$(includedir)/$(GENERIC_LIBRARY_NAME)/DB
library_include_HEADERS = $(h_sources)

INCLUDES = -I$(top_srcdir) ../../Core

lib_LTLIBRARIES=libxvr2db.la
libxvr2db_la_SOURCES= $(h_sources) $(cc_sources)
libxvr2db_la_LDFLAGS= -version-info $(GENERIC_LIBRARY_VERSION) -release $(GENERIC_RELEASE)
