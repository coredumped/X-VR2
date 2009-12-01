#$Id$


h_sources = RegexException.h Regex.h ExtendedRegex.h \
	MD5.h ChecksumExceptions.h

cc_sources = Regex.cpp RegexException.cpp ExtendedRegex.cpp \
	MD5.cpp ChecksumExceptions.cpp

library_includedir=$(includedir)/$(GENERIC_LIBRARY_NAME)/Text
library_include_HEADERS = $(h_sources)

INCLUDES = -I$(top_srcdir) ../../Core

lib_LTLIBRARIES=libxvr2text.la
libxvr2text_la_SOURCES= $(h_sources) $(cc_sources)
libxvr2text_la_LDFLAGS= -version-info $(GENERIC_LIBRARY_VERSION) -release $(GENERIC_RELEASE)
