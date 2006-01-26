/*
 * $Id$
 */


#include<xvr2/xvr2config.h>
#include<stdio.h>
#include<stdlib.h>
#ifdef UNIX_SOCKETS
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<signal.h>
#include<netdb.h>
#else
#include <SDL_net.h>
#endif
#if __GNUC__ >= 3
#include<iostream>
#include<cerrno>
#else
#include<iostream.h>
#include<errno.h>
#endif
#include<fcntl.h>
#include"config.h"
#include"_xvr2netClassNames.h"
#include<xvr2/TCPServerSocket.h>

namespace xvr2{
	namespace Net{

		TCPServerSocket::TCPServerSocket(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(__xvr2_Net_TCPServerSocket);
#endif
			_created = false;
			port = -1;
			is_a_copy = false;
		}
		
		TCPServerSocket::TCPServerSocket(const int p, const int m){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(__xvr2_Net_TCPServerSocket);
#endif
			_created = false;
			is_a_copy = false;
			CreateSocket(p, m);
		}
		
		int TCPServerSocket::CreateSocket(const int p, bool nonblock, const int m){
			if(_created)
				return 1;
			if(p == 0){
				throw InvalidParameter("\"port <= 0 !!!!\"");
				return 0;
			}
			int ret;
		 	struct sockaddr_in name;
		 	struct linger opt;
#ifdef SOLARIS
		 	char *ptr;
#endif
		 	tsock = -1;
		 	port = p;
		 	maxConn = m;
		 	tsock = socket (PF_INET, SOCK_STREAM, 0);
		 	if (tsock < 0){
				 switch(errno){
				 	case EMFILE:
						_created = false;
						throw ProcOutOfFileDescriptors();
					break;
				 	case ENFILE:
						_created = false;
						throw SysOutOfFileDescriptors();
					break;
					default:
						_created = false;
						throw IOException();
				 }
		 	}
		 	name.sin_family = AF_INET;
		 	name.sin_port = htons (port);
		 	name.sin_addr.s_addr = htonl (INADDR_ANY);
		 
		 	opt.l_onoff = 1;
		 	opt.l_linger = 0; 
			if(nonblock){
#ifdef USE_DEBUG
				if(fcntl(tsock, F_SETFL, O_NONBLOCK) != 0){
					debugmsg(this, "fcntl to nonblock failed, check it!!!!!!");
				}
#else
				fcntl(tsock, F_SETFL, O_NONBLOCK);
#endif
				_nonblock = nonblock;
			}
/*#ifdef SOLARIS
		 	ptr = (char *)&opt;
		 	ret = setsockopt(tsock, SOL_SOCKET, SO_LINGER, ptr, 
					sizeof(opt)); 
#else
		 	ret = setsockopt(tsock, SOL_SOCKET, SO_LINGER, 
					(struct linger*)&opt, sizeof(opt)); 
#endif*/
			setSockOption(SO_LINGER, (void *)&opt, sizeof(opt));
		 	if(ret == -1){
				_created = false;
				throw NetworkException();
			}
			 
		 	if (::bind (tsock, (struct sockaddr *) &name, sizeof (name)) < 0){
				switch(errno){
					case EINVAL:
						_created = false;
						throw SocketAlreadyBounded();
						break;
					default:
						_created = false;
						throw NetworkException();
				}
			}
			_created = true;
			return ret;
		}
		
		TCPSocket *TCPServerSocket::accept(){
			int ss;
			struct sockaddr_in client;
	#ifdef SOLARIS
				int size;
	#else
				size_t size;
				socklen_t tlen;
	#endif
			CreateSocket(port);
			if(listen(tsock, maxConn) != 0){
			        switch(errno){
						case EADDRINUSE:
							throw SocketAlreadyUsed();
							break;
						default:
							throw NetworkException();
		        	}
			}
			size = sizeof(client);
			tlen = size;
			if((ss = ::accept(tsock, (sockaddr *)&client, &tlen)) == -1)
				return NULL; 
			TCPSocket *r = new TCPSocket(ss, port);
			return r;
		}
		
		TCPSocket *TCPServerSocket::asyncAccept(){
			int ss;
			struct sockaddr_in client;
	#ifdef SOLARIS
				int size;
	#else
				size_t size;
				socklen_t tlen;
	#endif
			CreateSocket(port, true);
			if(listen(tsock, maxConn) != 0){
			        switch(errno){
						case EADDRINUSE:
							throw SocketAlreadyUsed();
							break;
						default:
							throw NetworkException();
		        	}
			}
			size = sizeof(client);
			tlen = size;
			if((ss = ::accept(tsock, (sockaddr *)&client, &tlen)) == -1)
				return 0x0; 
			TCPSocket *r = new TCPSocket(ss, port);
			return r;
		}
		
		void TCPServerSocket::close(){
			if(tsock >= 0){
				if(!is_a_copy){
					::close(tsock);	 
				}
				tsock = -1;
			}
		}

	};
}; //end of namespace directive
