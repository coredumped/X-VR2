/*
 * $Id$
 */
#ifndef __XVR2_OLD_SERVER_SOCKET_H__
#define __XVR2_OLD_SERVER_SOCKET_H__

#include<xvr2/Net/NetworkExceptions.h>
#include<xvr2/Net/OldTCPSocket.h>
#include<xvr2/InvalidParameterException.h>

namespace xvr2{
	namespace Net {
		/** This class handles the socket server interface
		 *  \deprecated This class will be dropped as of xvr2net version
		 *  8.0.3 please migrate your code before that, it has only been
		 *  kept for compatibility with previous releases.
		 */
		class OldTCPServerSocket:public OldSocket{
			protected:
			/** * Tells if the server socket has been created or not */
			bool _created;
			/**
			 * This will tell if a call to accept() will block or not
			 */
			bool _nonblock;
			/** This method binds a server socket to the port
			 *  specified by <b>theport</b>
			 */
			int CreateSocket(const int theport, bool nonblock = false,
					const int m = 256);
			/** Stores the value of the backlog parameter for
			 *  the <b>listen(2)</b> system call */
			int maxConn;
			bool is_a_copy;
			public:
			/** Default constructor, use carefully */
			OldTCPServerSocket();
			/** This constructor takes as an argument the port
			 *  where to listen requests and the size of the
			 *  backlog */
			OldTCPServerSocket(const int pport, const int m = 256);
			/** Destroys the server socket closing connections
			 *  to every client connected */
			virtual ~OldTCPServerSocket(){
				close();
			}
			/** Waits for a client to connect from a remote 
			 *  host returning it's client socket, please note that
			 *  this method will wait until a connection is made, so it
			 *  will block the program or current thread execution. 
			 */
			virtual OldTCPSocket *accept();
			/** Waits for a client to connect from a remote 
			 *  host returning it's client socket, however this is an
			 *  asynchronous call, this means that a call to the method 
			 *  might return NULL or a OldTCPSocket object, if it is NULL
			 *  it means that nobody has connect to it up to the moment.
			 *  The reason for this method is that sometimes you would
			 *  like to have a loop and do something if nobody connect
			 *  to the OldTCPServerSocket.
			 */
			virtual OldTCPSocket *asyncAccept();
			/** Closes communication to all clients and 
			 *  shuts down the socket */
			virtual void close();
			/** Returns the port number where the server 
			 *  socket was bounded */
			const int getPort(){
				return port;
			}

			void setPort(int port){
			}
		};
	} //end of Network namespace directive
} //end of xvr2 namespace directive

#endif
