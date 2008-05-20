## Source directory

h_sources = DatabaseException.h DBConnection.h DBConnectionMT.h DBDriver.h \
	    DBDriverInfo.h DBDriverManager.h DBField.h DBResultSet.h \
	     _xvr2dbClassNames.h DBConnectionTS.h DBCommand.h

cc_sources = DatabaseException.cpp DBConnection.cpp DBConnectionMT.cpp DBDriver.cpp \
	     DBDriverInfo.cpp DBDriverManager.cpp DBField.cpp \
	     DBResultSet.cpp _xvr2dbClassNames.cpp DBConnectionTS.cpp DBCommand.cpp

library_includedir=$(includedir)/$(GENERIC_LIBRARY_NAME)
library_include_HEADERS = $(h_sources)

INCLUDES = -I$(top_srcdir)

lib_LTLIBRARIES=libxvr2db-0.7.2.1.la
libxvr2db_0_7_2_1_la_SOURCES= $(h_sources) $(cc_sources)
libxvr2db_0_7_2_1_la_LDFLAGS= -version-info $(GENERIC_LIBRARY_VERSION) -release $(GENERIC_RELEASE)
