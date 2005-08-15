/*
 * $Id$
 */
#include"xvr2/UDP.h"
#include"xvr2/IPv4Address.h"
#include"xvr2/Socket.h"
#include"xvr2/UDPSocket.h"
#include"xvr2/UDPServerSocket.h"
#include"xvr2/UDPReceiveTimeoutException.h"
#include"xvr2/ConnectionResetByPeerException.h"
#include"xvr2/NetworkException.h"
#include"xvr2/MemoryException.h"
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/poll.h>

namespace xvr2{
namespace Net{
	void UDP::send(const UDPSocket &s, const void *buf, int size, int flags, int timeout){
		flags |= MSG_NOSIGNAL;
		::sendto(s.tsock, buf, size, flags, (struct ::sockaddr *)&s.ipv4addr, sizeof(s.ipv4addr));
	}
	void UDP::send(const IPv4Address &a, int port, const void *buf, int size, int flags, int timeout){
		UDPSocket s(a, port);
		try{
			send(s, buf, size, flags, timeout);
		}
		catch(...){
			throw;
		}
	}
	int UDP::receive(const IPv4Address &a, int port, void *buf, int size, int flags, int timeout){
		int ret;
		UDPServerSocket s(a, port);
		try{
			ret = receive(s, buf, size, flags, timeout);
		}
		catch(...){
			throw;
		}
		return ret;
	}
	int UDP::receive(const UDPServerSocket &s, void *buf, int size, int flags, int timeout){
		::socklen_t ret;
		struct pollfd fd;
		int bytes;
		flags |= MSG_NOSIGNAL;
		ret = sizeof(struct ::sockaddr_in);
		fd.fd = s.tsock;
		fd.events = POLLIN | POLLPRI;
		if(poll(&fd, 1, timeout) == 0){
			throw Exception::UDPReceiveTimeout();
		}
		bytes = ::recvfrom(s.tsock, buf, size, flags, (struct ::sockaddr *)&s.ipv4addr, &ret);
		if(bytes < -1){
			switch(errno){
				case ECONNRESET:
					throw Exception::ConnectionResetByPeer();
				case ENOMEM:
					throw Exception::Memory();
				default:
					throw Exception::Network();
			}
		}
		return bytes;
	}
	int UDP::receive(int port, void *buf, int size, int flags, int timeout){
		::socklen_t ret;
		struct pollfd fd;
		UDPServerSocket s(port);
		struct ::sockaddr_in ipv4addr;
		int bytes;
		fd.fd = s.tsock;
		fd.events = POLLIN | POLLPRI;
		ret = sizeof(struct ::sockaddr_in);
		if(poll(&fd, 1, timeout) == 0){
			throw Exception::UDPReceiveTimeout();
		}
		bytes = ::recvfrom(s.tsock, buf, size, flags, (struct ::sockaddr *)&ipv4addr, &ret);
		if(bytes < -1){
			switch(errno){
				case ECONNRESET:
					throw Exception::ConnectionResetByPeer();
				case ENOMEM:
					throw Exception::Memory();
				default:
					throw Exception::Network();
			}
		}
		return bytes;
	}
};
};
