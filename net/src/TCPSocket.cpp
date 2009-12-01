/*
 * $Id$
 */
/*
 * This class provides all the functionality for working with TCP sockets<br>
 * <b>NOTE: This socket interface is not backward compatible with previous 
 * versions of the xvr2lib library, sorry but all the old interfaces were to
 * redundant and for sanity we took the desicion to upgrade the class this 
 * way</b>
 */
#include<stdio.h>
#ifdef USING_GCC3
#include<iostream>
#include<string>
#else
#include<iostream.h>
#include<string.h>
#endif
#include<TCPSocket.h>
#include<Memory.h>
#include<errno.h>
#ifdef UNIX_SOCKETS
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#include<unistd.h>
#include<sys/poll.h>
#endif
#include<fcntl.h>

#ifndef SOCK_CHUNK_SIZE
#define SOCK_CHUNK_SIZE 4096
#endif

#ifndef READ_TIMEOUT
#define READ_TIMEOUT 30000
#endif

#include<Thread.h>

namespace xvr2{
	namespace Net {

		/** This variable has a static reference to the localhost 
		 *  string */
		static const char *__w6_localhost = "localhost";
		
		TCPSocket &TCPSocket::operator=(TCPSocket s){
			port = s.port;
			tcpsock = s.tcpsock;
			host = strdup(s.host);
			return *this;
		}

#ifndef USING_LINUX
#ifndef SOLARIS
		Mutex __ghbn;
#endif
#endif
		
		int TCPSocket::CreateSocket(const char *thehost, int theport){
#ifdef USING_LINUX
			struct hostent ret;
			int h_errnop;
			char *tmp_buf;
			int tmp_blen;
			int bmem;
#endif
			struct hostent *hp;
			struct sockaddr_in name;
			struct linger opt;
#ifdef SOLARIS
			char *ptr;
#endif
			host = (char *)thehost;
			port = theport;
			tcpsock = socket(PF_INET, SOCK_STREAM, 0);
			if(tcpsock < 0){
				switch(errno){
					case EMFILE:
						throw Exception::ProcOutOfFileDescriptors();
					break;
					case ENFILE:
						throw Exception::SysOutOfFileDescriptors();
					break;
					default:
						throw Exception::IO();
				}
			}
#ifndef USING_LINUX
#ifndef SOLARIS
			__ghbn.lock();
			hp = gethostbyname(thehost);
#else
			//Use Solaris's C library gethostbyname_r implementation
			bmem = 5 * strlen(thehost) + sizeof(hostent);
			tmp_blen = bmem;
			while(true){
				tmp_buf = (char *)Memory::allocBuffer(tmp_blen);
				
				if(gethostbyname_r(thehost, &ret, tmp_buf, tmp_blen, &hp, &h_errnop) != ERANGE){

					break;
				}
				else {
#ifdef USE_DEBUG
					debugmsg(this, "not enough memory to fill the hostent structure in a gethostbyname_r call, retrying...\n");
#endif
					Memory::freeBuffer((void **)&tmp_buf);
					tmp_blen += bmem;
				}
				switch(h_errnop){
					case HOST_NOT_FOUND:
						Memory::freeBuffer((void **)&tmp_buf);
						throw Exception::HostNotFound();
						break;
					case TRY_AGAIN:
						Memory::freeBuffer((void **)&tmp_buf);
						throw Exception::NSTryAgain();
						break;
					case NO_RECOVERY:
						Memory::freeBuffer((void **)&tmp_buf);
						throw Exception::NSFatal();
						break;
					case NO_DATA:
					case NO_ADDRESS:
						Memory::freeBuffer((void **)&tmp_buf);
						throw Exception::NoIPForYou();
						break;
				}
			}

#endif
#else
			//Use glibc gethostbyname_r implementation
			bmem = 2 * strlen(thehost) + sizeof(hostent);
			tmp_blen = bmem;
			while(true){
				tmp_buf = (char *)Memory::allocBuffer(tmp_blen);
				
				if(gethostbyname_r(thehost, &ret, tmp_buf, tmp_blen, &hp, &h_errnop) != ERANGE){

					break;
				}
				else {
#ifdef USE_DEBUG
					debugmsg(this, "not enough memory to fill the hostent structure in a gethostbyname_r call, retrying...\n");
#endif
					tmp_blen += bmem;
				}
				switch(h_errnop){
					case HOST_NOT_FOUND:
						Memory::freeBuffer((void **)&tmp_buf);
						throw Exception::HostNotFound();
						break;
					case TRY_AGAIN:
						Memory::freeBuffer((void **)&tmp_buf);
						throw Exception::NSTryAgain();
						break;
					case NO_RECOVERY:
						Memory::freeBuffer((void **)&tmp_buf);
						throw Exception::NSFatal();
						break;
					case NO_ADDRESS:
						Memory::freeBuffer((void **)&tmp_buf);
						throw Exception::NoIPForYou();
						break;
				}
			}
#endif
			if(hp == NULL){
#ifdef USE_DEBUG
				std::cerr << thehost << " not found!!!" << std::endl;
#endif
#ifndef USING_LINUX
#ifndef SOLARIS
				__ghbn.unlock();
#endif
#endif
#ifdef USING_LINUX
					Memory::freeBuffer((void **)&tmp_buf);
#endif
#ifdef SOLARIS
					Memory::freeBuffer((void **)&tmp_buf);
#endif
				return 0;
			}
			name.sin_family = AF_INET;
			name.sin_port = htons (port);
			name.sin_addr = *(struct in_addr *) hp->h_addr;
			opt.l_onoff = 1;
			opt.l_linger = 0; 
/*#ifdef SOLARIS
			ptr = (char *)&opt;
			setsockopt(tcpsock, SOL_SOCKET, SO_LINGER, ptr, sizeof(opt));
#else
			setsockopt(tcpsock, SOL_SOCKET, SO_LINGER, (struct linger*)&opt, sizeof(opt));
#endif*/

			setSockOption(SO_LINGER, &opt, sizeof(opt));
			if(::connect(tcpsock, (struct sockaddr *)&name, sizeof(name)) != 0){
				tcpsock = -1;
#ifndef USING_LINUX
#ifndef SOLARIS
				__ghbn.unlock();
#endif
#endif
#ifdef USING_LINUX
				Memory::freeBuffer((void **)&tmp_buf);
#endif
#ifdef SOLARIS
				Memory::freeBuffer((void **)&tmp_buf);
#endif
				switch(errno){
					case ETIMEDOUT:
						throw Exception::ConnectionTimeout();
						break;
					case ECONNREFUSED:
						throw Exception::ConnectionRefused();
						break;
					case ENETUNREACH:
						throw Exception::NetworkUnreachable();
						break;
					default:
						throw Exception::Network();
				}
				return 0;
			}
#ifdef USE_DEBUG
			debugmsg(this, "connected\n");
#endif
#ifndef USING_LINUX
#ifndef SOLARIS
			__ghbn.unlock();
#endif
#endif
#ifdef USING_LINUX
			Memory::freeBuffer((void **)&tmp_buf);
#endif
#ifdef SOLARIS
			Memory::freeBuffer((void **)&tmp_buf);
#endif
			return 1;
		}

		TCPSocket::TCPSocket(TCPSocket *s){
#ifndef USING_GCC3
		   	setClassName(xvr2::_xvr2TCPSocket);
#endif
			tcpsock = s->tcpsock;
			host = s->host;
			port = s->port;
#ifdef USE_DEBUG
			debugmsg(this, " cloned\n");
#endif
		}
		
		TCPSocket::TCPSocket(const TCPSocket &s){
#ifndef USING_GCC3
		   	setClassName(xvr2::_xvr2TCPSocket);
#endif
			tcpsock = s.tcpsock;
			host = (char *)__w6_localhost;
			port = s.port;
		}
		
		TCPSocket::TCPSocket(TCPsocket s, int pport){
#ifndef USING_GCC3
			setClassName(xvr2::_xvr2TCPSocket);
#endif
			host = (char *)__w6_localhost;
			tcpsock = s;
			port = pport;
#ifdef USE_DEBUG
			debugmsg(this, "connected to a TCPServerSocket\n");
#endif
		}
		
		TCPSocket::TCPSocket(const char *thehost, const int theport){
#ifndef USING_GCC3
			setClassName(xvr2::_xvr2TCPSocket);
#endif
			try{
				CreateSocket(thehost, theport);
			}
			catch(...){
				throw;
			}
		}
		
		TCPSocket::~TCPSocket(){;}
		
		void TCPSocket::close(void){
			if(tcpsock >= 0){
				/*::shutdown(tcpsock, SHUT_RDWR);
#ifdef USE_DEBUG
				debugmsg(this, "shutdown\n");
#endif*/
				::close(tcpsock);
#ifdef USE_DEBUG
				debugmsg(this, "closed\n");
#endif
				tcpsock = -1;
			}
		}
		
		void TCPSocket::writeLine(const char *str){
			write(str, strlen(str) + 1);
		}

		void TCPSocket::writeLine(const String &str){
			writeLine(str.toCharPtr());
		}
		
		void TCPSocket::write(const void *buffer, unsigned long size){
			unsigned int i;
			int len, ret ;
			char *tmpbuf;
			char *ptr;
			unsigned int siz;
			if(size < SOCK_CHUNK_SIZE){
				siz = ::send (tcpsock, (void*)buffer, size, MSG_NOSIGNAL);
				if(siz < size) {
					switch(errno){
						case EINVAL:
							throw Exception::SocketUnableToWrite();
							break;
						case EPIPE:
							throw Exception::BrokenPipe();
							break;
						default:
							throw Exception::Network();
					}
				}
			}
			else{
				tmpbuf = new char[SOCK_CHUNK_SIZE + 1];
				ptr = (char *)buffer;
				siz = size - (size % SOCK_CHUNK_SIZE);
				for(i = 0; i < siz; i += SOCK_CHUNK_SIZE){
					memcpy(tmpbuf, (ptr + i), SOCK_CHUNK_SIZE);
					len = strlen (tmpbuf) ;
					ret = send(tcpsock, tmpbuf, SOCK_CHUNK_SIZE, MSG_NOSIGNAL);
					if(ret < len ) {
						switch(errno){
							case EINVAL:
								throw Exception::SocketUnableToWrite();
								break;
							case EPIPE:
								throw Exception::BrokenPipe();
								break;
							default:
								throw Exception::Network();
						}
					}
				}
				if(size % SOCK_CHUNK_SIZE != 0){
					memcpy(tmpbuf, (ptr + siz), size - siz);
					len = strlen (tmpbuf) ;
					ret = send(tcpsock, tmpbuf, size - siz, MSG_NOSIGNAL) ;
					if(ret < len ) {
						switch(errno){
							case EINVAL:
								throw Exception::SocketUnableToWrite();
								break;
							case EPIPE:
								throw Exception::BrokenPipe();
								break;
							default:
								throw Exception::Network();
						}
					}
				}
				delete tmpbuf;
			}
		}
		
		
		
		void TCPSocket::readLine(char **str){
			//This one is quite awful because what one has to do  
			// is read every byte until the end without knowing how 
			//many data bytes are comming through the channel
			char *tmpbuf;
			char chr[2];
			unsigned long s_size = 3;
			chr[0] = 0;
			chr[1] = 0;
			tmpbuf = (char *)xvr2::Memory::allocBuffer(s_size);
			tmpbuf[0] = 0;
			while(true){
				try{
					read((void *)chr, 1) ;
				}
				catch(Exception::BrokenPipe epipe_ex){
					chr[0] = 0;
					tmpbuf = (char *)xvr2::Memory::reallocBuffer(tmpbuf, ++s_size);
					strncat(tmpbuf, chr, 1);
					throw;
				}
				tmpbuf = (char *)xvr2::Memory::reallocBuffer(tmpbuf, ++s_size);
				if(chr[0] == '\n')
					chr[0] = 0;
				strncat(tmpbuf, chr, 1);
				if(chr[0] == 0)
					break;
			}
			*str = tmpbuf;
		}
		
		void TCPSocket::read(void *buffer, unsigned long size){
		//////// ############  BEGIN UNIX CODE #####################
			unsigned int i;
			char *tmpbuf;
			char *ptr;
			unsigned int siz;
			struct pollfd fd;
			fd.fd = tcpsock;
			fd.events = POLLIN | POLLPRI;
			if(poll(&fd, 1, READ_TIMEOUT) == 0){
#ifdef USE_DEBUG
				debugmsg(this, "Connection timed out");
#endif
				throw Exception::ConnectionTimeout();
			}
			if(size < SOCK_CHUNK_SIZE){
				if(::recv(tcpsock, buffer, size, MSG_NOSIGNAL|MSG_DONTWAIT) == -1){
					switch(errno){
						case EINVAL:
							throw Exception::SocketUnableToRead();
							break;
						case EPIPE:
							throw Exception::BrokenPipe();
							break;
						case ECONNRESET:
							throw Exception::ConnectionResetByPeer();
							break;
						default:
							throw Exception::Network();
					}
				}
			}
			else{
				tmpbuf = new char[SOCK_CHUNK_SIZE + 1];
				ptr = (char *)buffer;
				siz = size - (size % SOCK_CHUNK_SIZE);
				for(i = 0; i < siz; i += SOCK_CHUNK_SIZE){
					if(poll(&fd, 1, READ_TIMEOUT) == 0){
#ifdef USE_DEBUG
						debugmsg(this, "Connection timed out");
#endif
						throw Exception::ConnectionTimeout();
					}
					if(::recv(tcpsock, tmpbuf, SOCK_CHUNK_SIZE, MSG_NOSIGNAL|MSG_DONTWAIT) == -1){
						switch(errno){
							case EINVAL:
								throw Exception::SocketUnableToRead();
								break;
							case EPIPE:
								throw Exception::BrokenPipe();
								break;
							default:
								throw Exception::Network();
						}
					}
					memcpy((ptr + i), tmpbuf, SOCK_CHUNK_SIZE);
				}
				if(size % SOCK_CHUNK_SIZE != 0){
					if(poll(&fd, 1, READ_TIMEOUT) == 0){
#ifdef USE_DEBUG
						debugmsg(this, "Connection timed out");
#endif
						throw Exception::ConnectionTimeout();
					}
					if(::recv(tcpsock, tmpbuf, size - siz, MSG_NOSIGNAL|MSG_DONTWAIT) == -1){
						switch(errno){
							case EINVAL:
								throw Exception::SocketUnableToRead();
								break;
							case EPIPE:
								throw Exception::BrokenPipe();
								break;
							default:
								throw Exception::Network();
						}
					}
					memcpy((ptr + siz), tmpbuf, size - siz);
				}
				delete tmpbuf;
			}
		}
	};
};
