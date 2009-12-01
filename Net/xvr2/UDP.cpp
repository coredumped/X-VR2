/*
 * $Id$
 */
#include"config.h"
#include<xvr2/xvr2config.h>
#include"_xvr2netClassNames.h"
#include"UDP.h"
#include"IPv4Address.h"
#include"Socket.h"
#include"OldUDPSocket.h"
#include"OldUDPServerSocket.h"
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/poll.h>
#if __GNUC__ >= 3
#include<cerrno>
#else
#include<errno.h>
#endif

namespace xvr2{
namespace Net{
	void UDP::send(const OldUDPSocket &s, const void *buf, int size, int flags, int timeout){
		flags |= MSG_NOSIGNAL;
		::sendto(s.tsock, buf, size, flags, (struct ::sockaddr *)&s.ipv4addr, sizeof(s.ipv4addr));
	}
	void UDP::send(const IPv4Address &a, int port, const void *buf, int size, int flags, int timeout){
		OldUDPSocket s(a, port);
		try{
			send(s, buf, size, flags, timeout);
		}
		catch(...){
			throw ;
		}
	}
	int UDP::receive(const IPv4Address &a, int port, void *buf, int size, int flags, int timeout){
		int ret;
		OldUDPServerSocket s(a, port);
		try{
			ret = receive(s, buf, size, flags, timeout);
		}
		catch(...){
			throw ;
		}
		return ret;
	}
	int UDP::receive(const OldUDPServerSocket &s, void *buf, int size, int flags, int timeout){
		::socklen_t ret;
		struct pollfd fd;
		int bytes;
		flags |= MSG_NOSIGNAL;
		ret = sizeof(struct ::sockaddr_in);
		fd.fd = s.tsock;
		fd.events = POLLIN | POLLPRI;
		if(poll(&fd, 1, timeout) == 0){
			throw UDPReceiveTimeout();
		}
		bytes = ::recvfrom(s.tsock, buf, size, flags, (struct ::sockaddr *)&s.ipv4addr, &ret);
		if(bytes < -1){
			switch(errno){
				case ECONNRESET:
					throw ConnectionResetByPeer();
				case ENOMEM:
					throw MemoryException();
				default:
					throw NetworkException();
			}
		}
		return bytes;
	}
	int UDP::receive(int port, void *buf, int size, int flags, int timeout){
		::socklen_t ret;
		struct pollfd fd;
		OldUDPServerSocket s(port);
		struct ::sockaddr_in ipv4addr;
		int bytes;
		fd.fd = s.tsock;
		fd.events = POLLIN | POLLPRI;
		ret = sizeof(struct ::sockaddr_in);
		if(poll(&fd, 1, timeout) == 0){
			throw UDPReceiveTimeout();
		}
		bytes = ::recvfrom(s.tsock, buf, size, flags, (struct ::sockaddr *)&ipv4addr, &ret);
		if(bytes < -1){
			switch(errno){
				case ECONNRESET:
					throw ConnectionResetByPeer();
				case ENOMEM:
					throw MemoryException();
				default:
					throw NetworkException();
			}
		}
		return bytes;
	}
};
};
