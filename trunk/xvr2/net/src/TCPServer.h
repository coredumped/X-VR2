/*
 * $Id$
 */
#ifndef __XVR2_TCPServer_H__
#define __XVR2_TCPServer_H__

#include<TCPSocket.h>
#include<TCPServerSocket.h>
//#include<TCPServerSession.h>
#include<SharedVar.h>
#include<Thread.h>
#include<NullPointerException.h>

namespace xvr2{
	namespace Network {
		//class TCPServerSession;
		/**
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
				void *run(void *);
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
				~TCPServer();
				/**
				 * This method will start the connection listener
				 * loop, inside this loop new threads are triggered
				 * to handle remote connections */
				virtual void startListener();
		};
	};
};

#endif
