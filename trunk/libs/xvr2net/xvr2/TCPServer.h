/*
 * $Id$
 */
#ifndef __XVR2_TCPServer_H__
#define __XVR2_TCPServer_H__

#include<xvr2/Net/TCPSocket.h>
#include<xvr2/Net/TCPServerSocket.h>
//#include<xvr2/TCPServerSession.h>
#include<xvr2/SharedVar.h>
#include<xvr2/Thread.h>
#include<xvr2/Net/NetworkExceptions.h>

namespace xvr2{
	namespace Net {
		//class TCPServerSession;
		/**
		 * \deprecated
		 * \class TCPServer TCPServer.h <xvr2/TCPServer.h>
		 * TCP oriented server, top-level class
		 *
		 */
		class TCPServer:protected TCPServerSocket, protected xvr2::Thread{
			private:
			protected:
				/**
				 * This is a pointer to the session manager, it will
				 * point to an object instantiated from a subclass
				 * of  TCPServerSession
				 */
				SharedVar<bool> continue_loop;
				void run() = 0;
				/**
				 * This method handles the conversation between the
				 * client and server sockets, override it in your 
				 * implementation */
				virtual void sessionDialog(TCPSocket *client);
				/** 
				 * This method is calls the Thread::start() function
				 * so the listener thread starts working as it 
				 * should be */
				void startSession(TCPSocket *client);
				/**
				 * Call this method whenever you desire to stop 
				 * listening connections on the currently defined
				 * port */
				void terminate();
			public:
				/**
				 * Default constructor, it takes a TCPServerSession
				 * user-defined subclass as a parameter
				 */
				TCPServer(int pport);
				virtual ~TCPServer();
				/**
				 * This method will start the connection listener
				 * loop, inside this loop new threads are triggered
				 * to handle remote connections */
				virtual void startListener();
				virtual std::string toString();
		};
	};
};

#endif
