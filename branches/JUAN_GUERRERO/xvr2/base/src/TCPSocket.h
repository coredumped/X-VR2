/*
 * $Id$
 */
#ifndef ___SOCKET_H__
#define ___SOCKET_H__
#include<sys/socket.h>

#include<String.h>
#include<Socket.h>
#include<NetworkException.h>
#include<ConnectionResetByPeerException.h>
#include<HostNotFoundException.h>
#include<NSTryAgainException.h>
#include<NSFatalException.h>
#include<NoIPForYouException.h>

namespace xvr2{
	namespace Network{

		/**
		 * \class TCPSocket
		 * \version $Revision$
		 * \brief This class provides all the functionality for working with TCP 
		 * sockets, from connection to sending a receiving data from a connected
		 * peer,
		 */
		class TCPSocket:public Socket{
			protected:
		 		/** Stores the hostname where the socket is going 
				 *  to be connected */
		 		char *host;
				/**
				 * This routine creates the socket by calling 
				 * socket(2) and resolving the argument 
				 * \b thehost to its IP representation in case
				 * the address is given as a name, 
				 * this socket is connected to the port 
				 * \b theport
				 */
				int CreateSocket(const char *thehost, int theport);
			public:
				/** This is a default constructor that does 
				 *  nothing */
				TCPSocket(){;}
				/**
				 * This constructor takes as an argument the host 
				 * location as an IP number or as a name, also the
				 * port to connect to, take in count that in the 
				 * very moment that this class is instantiated the
				 * socket would try to connect with the remote 
				 * host inmediately */
				TCPSocket(const char *thehost, int theport);
				/**
				 * This constructor tekas as an argument the host 
				 * location as an IP number or as a name, also the
				 * port to connect to, take in count that in the
				 * very moment that this class is instantiated the
				 * socket would try to connect with the remote 
				 * host inmediately */
				TCPSocket(TCPsocket s, int pport);
				/** Pointer copy-constructor */
				TCPSocket(TCPSocket *s);
				/**
				 * This is a copy constructor
				 */
				TCPSocket(const TCPSocket &s);
				/**
				 * Use this operator to create copies of an already
				 * existent TCPSocket */
				TCPSocket &operator=(TCPSocket s);
				/**
				 * This destructor does nothing
				 */
				~TCPSocket();
				/**
				 * Closes the communications channel with the 
				 * remote host inmmediately
				 */
				void close(void);
				/**
				 * Returns the port associated with this socket
				 */
				const int getPort(){
					return port;
				}
				
				/**
				 * This method will send a null-terminated string
				 * of bytes to the other end of communications
				 */
				void writeLine(const char *str);
				/**
				 * This method will send a null-terminated string
				 * of bytes to the other end of communications
				 */
				void writeLine(const String &str);
				/**
				 * Use this method when you need to send a fixed 
				 * lenght buffer of bytes to the remote host, the 
				 * routine will cut the buffer in chunks so the 
				 * transfer can be safelly completed without 
				 * out of memory error that might be caused if you
				 * attempt to send a very big buffer of data
				 */
				void write(const void *buffer, unsigned long size);
				/**
				 * Attempts to read a continuos byte string, it will
				 * stop reading data when it finds the 0x00 or \n 
				 * character, in the case we lost connection
				 * with the server the string will be fixed to be
				 * null-terminated and then the method will throw
				 * a BrokenPipeException.
				 * This method will attempt to allocate memory to the
				 * str pointer so please remember to release the 
				 * allocated block using Memory::freeBuffer
				 */
				void readLine(char **str);
				/**
				 * Use this method when you need to receive a 
				 * fixed lenght buffer of bytes from the remote 
				 * host, the routine will cut the buffer in chunks
				 * so the transfer can be safelly completed 
				 * without out of memory error that might be 
				 * caused if you attempt to receive a very big 
				 * buffer of data
				 */
				void read(void *buffer, unsigned long size);
		};
	}; //End of Network namespace directive
}; //End of xvr2 namespace directive

#endif
