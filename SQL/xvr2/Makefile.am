## Source directory

h_sources = DatabaseException.h Connection.h ConnectionMT.h Driver.h \
	    DriverInfo.h DriverManager.h Field.h ResultSet.h 

cc_sources = DatabaseException.cpp Connection.cpp ConnectionMT.cpp Driver.cpp \
	     DriverInfo.cpp DriverManager.cpp Field.cpp \
	     ResultSet.cpp

library_includedir=$(includedir)/$(GENERIC_LIBRARY_NAME)/DB
library_include_HEADERS = $(h_sources)

INCLUDES = -I$(top_srcdir) -I../../Core/xvr2

lib_LTLIBRARIES=libxvr2sql.la
libxvr2sql_la_SOURCES= $(h_sources) $(cc_sources)
libxvr2sql_la_LDFLAGS= -version-info $(GENERIC_LIBRARY_VERSION) -release $(GENERIC_RELEASE)
