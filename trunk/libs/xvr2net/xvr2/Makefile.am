## Source directory

h_sources = IPv4Address.h IPv4Resolver.h netdefs.h NetworkExceptions.h \
	    Socket.h SSLContext.h SSLSocket.h TCPServerSocket.h \
	    TCPSocket.h UDP.h UDPServerSocket.h UDPSocket.h X509.h X509Issuer.h \
	    X509Name.h X509Subject.h OldSocket.h OldTCPSocket.h OldTCPServerSocket.h \
	    OldUDPSocket.h OldUDPServerSocket.h SocketExceptions.h IPAddress.h \
	    ClientSocket.h SocketProtocol.h RawSocketInputStream.h \
	    BufferedSocketInputStream.h RawSocketOutputStream.h

cc_sources = IPv4Address.cpp IPv4Resolver.cpp NetworkExceptions.cpp Socket.cpp \
	     SSLContext.cpp SSLSocket.cpp TCPServerSocket.cpp \
	     TCPSocket.cpp UDP.cpp UDPServerSocket.cpp UDPSocket.cpp X509.cpp \
	     X509Issuer.cpp X509Name.cpp X509Subject.cpp OldSocket.cpp OldTCPSocket.cpp \
	     OldTCPServerSocket.cpp OldUDPSocket.cpp OldUDPServerSocket.cpp \
	     SocketExceptions.cpp IPAddress.cpp ClientSocket.cpp SocketProtocol.cpp \
	     RawSocketInputStream.cpp BufferedSocketInputStream.cpp RawSocketOutputStream.cpp



library_includedir=$(includedir)/$(GENERIC_LIBRARY_NAME)/Net
library_include_HEADERS = $(h_sources)

INCLUDES = -I$(top_srcdir)

lib_LTLIBRARIES=libxvr2net.la
libxvr2net_la_SOURCES= $(h_sources) $(cc_sources)
libxvr2net_la_LDFLAGS= -version-info $(GENERIC_LIBRARY_VERSION) -release $(GENERIC_RELEASE)

rebuild: clean all

