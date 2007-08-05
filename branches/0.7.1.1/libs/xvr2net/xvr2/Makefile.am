## Source directory

h_sources = IPv4Address.h IPv4Resolver.h netdefs.h NetworkExceptions.h \
	    Socket.h SSLContext.h SSLSocket.h TCPServer.h TCPServerSocket.h \
	    TCPSocket.h UDP.h UDPServerSocket.h UDPSocket.h X509.h X509Issuer.h \
	    X509Name.h X509Subject.h

cc_sources = IPv4Address.cpp IPv4Resolver.cpp NetworkExceptions.cpp Socket.cpp \
	     SSLContext.cpp SSLSocket.cpp TCPServer.cpp TCPServerSocket.cpp \
	     TCPSocket.cpp UDP.cpp UDPServerSocket.cpp UDPSocket.cpp X509.cpp \
	     X509Issuer.cpp X509Name.cpp X509Subject.cpp


library_includedir=$(includedir)/$(GENERIC_LIBRARY_NAME)
library_include_HEADERS = $(h_sources)

INCLUDES = -I$(top_srcdir)

lib_LTLIBRARIES=libxvr2net-0.7.1.0.la
libxvr2net_0_7_1_0_la_SOURCES= $(h_sources) $(cc_sources)
libxvr2net_0_7_1_0_la_LDFLAGS= -version-info $(GENERIC_LIBRARY_VERSION) -release $(GENERIC_RELEASE)

rebuild: clean all

