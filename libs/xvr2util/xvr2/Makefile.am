## Source directory


h_sources = Array.h Container.h c_utilities.h List.h \
	RegexException.h Regex.h ExtendedRegex.h _xvr2utilClassNames.h \
	StringCollection.h MD5.h ChecksumExceptions.h

cc_sources = Container.cpp c_utilities.cpp Regex.cpp \
	RegexException.cpp ExtendedRegex.cpp _xvr2utilClassNames.cpp \
	StringCollection.cpp MD5.cpp ChecksumExceptions.cpp

library_includedir=$(includedir)/$(GENERIC_LIBRARY_NAME)/Util
library_include_HEADERS = $(h_sources)

INCLUDES = -I$(top_srcdir)

lib_LTLIBRARIES=libxvr2util.la
libxvr2util_la_SOURCES= $(h_sources) $(cc_sources)
libxvr2util_la_LDFLAGS= -version-info $(GENERIC_LIBRARY_VERSION) -release $(GENERIC_RELEASE)
