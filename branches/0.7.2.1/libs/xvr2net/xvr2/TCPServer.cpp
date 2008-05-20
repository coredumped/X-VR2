/*
 * TCP oriented server, top-level class
 *
 * $Id$
 */
#include"config.h"
#include<xvr2/xvr2config.h>
#include"_xvr2netClassNames.h"
#include<xvr2/TCPServer.h>
#include<xvr2/DebugConsole.h>

namespace xvr2{
	namespace Net {

		// Start definition of local variables
		// End definition of local variables
	
		// Start definition of local functions
		// End definition of local functions
	
	
	
	
		//Start implementation of class: TCPServer
	
		TCPServer::TCPServer(int pport):TCPServerSocket(pport){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(__xvr2_Net_TCPServer);
#endif
			string_representation.clear();

			string_representation = "xvr2::Net::TCPServer[port=";
			string_representation.concat(pport);
			string_representation.concat("]");
		}
	
	
		TCPServer::~TCPServer(){
#ifdef USE_DEBUG
			debugConsole << "[" << __FILE__ << ":" << __LINE__ << "]: " << this->toString() << ": destroyed" << xvr2::NL;
#endif
		}
	
		void TCPServer::startListener(){
			TCPSocket *client;
#ifdef USE_DEBUG
			int j = 0;
#endif
			continue_loop.setValue(true);
#ifdef USE_DEBUG
			debugConsole << "[" << __FILE__ << ":" << __LINE__ << "]: " << this->toString() << ": starting loop" << xvr2::NL;
#endif
			while(continue_loop.getValue()){
				client = asyncAccept();
				if(continue_loop.getValue()){
					if(client != 0){
#ifdef USE_DEBUG
						debugConsole << "[" << __FILE__ << ":" << __LINE__ << "]: " << this->toString() << ": starting session..." << xvr2::NL;
#endif
						startSession(client);
					}
#ifdef USE_DEBUG
					else{
						if((j % 10000) == 0){
							debugConsole << "[" << __FILE__ << ":" << __LINE__ << "]: " << this->toString() << ": waiting for connections" << xvr2::NL;
						}
						j++;
					}
#endif
				}
				System::usleep(10);
			}
			close();
		}

		void TCPServer::terminate(){
			continue_loop.setValue(false);
#ifdef USE_DEBUG
			debugConsole << "[" << __FILE__ << ":" << __LINE__ << "]: " << this->toString() << ": Stoping listener loop" << xvr2::NL;
#endif
		}

/*		void TCPServer::run(){
			TCPSocket *client = 0;
			client = (TCPSocket *)data;
			if(client != 0){
				sessionDialog(client);
#ifdef USE_DEBUG
				Socket::debugmsg(this, "destroying client socket...\n");
#endif
				client->close();
				delete client;
			}
			else{
#ifdef USE_DEBUG
				Socket::debugmsg(this, "unable to start session, client is null\n");
#endif
				throw NullPointer();
			}
			//killMe();
			return 0;
		}*/

		void TCPServer::sessionDialog(TCPSocket *client){
			static int h;
#if __GNUC__ < 3
			std::cout << xvr2::_xvr2TCPServer << ": please create a subclass from this one and override the sessionDialog method from there. " << std::endl;
			client->writeLine(xvr2::_xvr2TCPServer);
			client->writeLine(": please create a subclass from this one and override the sessionDialog method from there");
#else
			std::cout << "TCPServer: please create a subclass from this one and override the sessionDialog method from there. " << std::endl;
			client->writeLine("TCPServer: please create a subclass from this one and override the sessionDialog method from there");
#endif
			xvr2::System::usleep(2500000);
			client->writeLine(" bye bye\n");
			xvr2::System::usleep(25000);
			if((h++) > 20)
				terminate();
		}

		void TCPServer::startSession(TCPSocket *client){
			//start((void *)client);
		}

		std::string TCPServer::toString(){
			return std::string(string_representation.toCharPtr());
		}

		//void TCPServer::(){
		//}

		//void TCPServer::(){
		//}

		//void TCPServer::(){
		//}

		//void TCPServer::(){
		//}

		//void TCPServer::(){
		//}

		//void TCPServer::(){
		//}

		//void TCPServer::(){
		//}
	
		//End implementation of class: TCPServer
	};
};