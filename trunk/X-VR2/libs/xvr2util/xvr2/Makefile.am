## Source directory
#xvr2/parsers/config-lexer.o  xvr2/parsers/config-parser.o

SUBDIRS = parsers

h_sources = Array.h ConfigFile.h Container.h c_utilities.h List.h \
	RegexException.h Regex.h ExtendedRegex.h _xvr2utilClassNames.h \
	StringCollection.h MD5.h ChecksumExceptions.h

cc_sources = ConfigFile.cpp Container.cpp c_utilities.cpp Regex.cpp \
	RegexException.cpp ExtendedRegex.cpp _xvr2utilClassNames.cpp \
	StringCollection.cpp MD5.cpp ChecksumExceptions.cpp

library_includedir=$(includedir)/$(GENERIC_LIBRARY_NAME)
library_include_HEADERS = $(h_sources)

INCLUDES = -I$(top_srcdir)

lib_LTLIBRARIES=libxvr2util-0.7.1.0.la
libxvr2util_0_7_1_0_la_SOURCES= $(h_sources) $(cc_sources)
libxvr2util_0_7_1_0_la_LDFLAGS= -version-info $(GENERIC_LIBRARY_VERSION) -release $(GENERIC_RELEASE)
libxvr2util_0_7_1_0_la_LIBADD= parsers/*.lo
