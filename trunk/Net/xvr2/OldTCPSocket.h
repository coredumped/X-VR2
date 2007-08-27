/*
 * $Id$
 */
#ifndef __XVR2_OLD_TCP_SOCKET_H__
#define __XVR2_OLD_TCP_SOCKET_H__
#include<sys/socket.h>

#include<xvr2/String.h>
#include<xvr2/Net/OldSocket.h>
#include<xvr2/Net/IPv4Address.h>
#include<xvr2/Net/NetworkExceptions.h>
#include<xvr2/InvalidParameterException.h>
#include<xvr2/RawInputStream.h>
#include<xvr2/RawOutputStream.h>

namespace xvr2{
	namespace Net {

		/**
		 * \class OldTCPSocket
		 * \version $Revision: 531 $
		 * \brief This class provides all the functionality for working with TCP 
		 * sockets, from connection to sending a receiving data from a connected
		 * peer.
		 *  \deprecated This class will be dropped as of xvr2net version
		 *  8.0.3 please migrate your code before that, it has only been
		 *  kept for compatibility with previous releases.
		 */
		class OldTCPSocket:public OldSocket{
			protected:
				bool _created;
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
				int CreateSocket(const IPv4Address *addr, int theport);
				int CreateSocket(const char *thehost, int theport);
				RawInputStream out;
				RawOutputStream in;
			public:
				/** This is a default constructor that does 
				 *  nothing */
				OldTCPSocket();
				/**
				 * This constructor takes as an argument the host 
				 * location as an IP number or as a name, also the
				 * port to connect to, take in count that in the 
				 * very moment that this class is instantiated the
				 * socket would try to connect with the remote 
				 * host inmediately */
				//OldTCPSocket(const char *thehost, int theport);
				OldTCPSocket(const String &thehost, int theport);
				/**
				 * This constructor tekas as an argument the host 
				 * location as an IP number or as a name, also the
				 * port to connect to, take in count that in the
				 * very moment that this class is instantiated the
				 * socket would try to connect with the remote 
				 * host inmediately */
				OldTCPSocket(int s, int pport);
				/** Pointer copy-constructor */
				OldTCPSocket(OldTCPSocket *s);
				/**
				 * This is a copy constructor
				 */
				OldTCPSocket(const OldTCPSocket &s);
				OldTCPSocket(const IPv4Address *ip, int theport);
				OldTCPSocket(const IPv4Address &ip, int theport);
				/**
				 * Use this operator to create copies of an already
				 * existent OldTCPSocket */
				OldTCPSocket &operator=(const OldTCPSocket &s);
				/**
				 * This destructor does nothing
				 */
				virtual ~OldTCPSocket();
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
				virtual void write(const void *buffer, unsigned long size);
				//const OldTCPSocket &operator << (const String &str) const;
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
				virtual void readLine(char **str);
				/**
				 * Use this method when you need to receive a 
				 * fixed lenght buffer of bytes from the remote 
				 * host, the routine will cut the buffer in chunks
				 * so the transfer can be safelly completed 
				 * without out of memory error that might be 
				 * caused if you attempt to receive a very big 
				 * buffer of data
				 */
				virtual int read(void *buffer, unsigned long size);
				virtual std::string toString();

				RawInputStream &outputStream();
				RawOutputStream &inputStream();

		};
	}; //End of Network namespace directive
}; //End of xvr2 namespace directive

#endif
