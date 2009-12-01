/*
 * $Id$
 */
#ifndef __XVR2_NETWORK_EXCEPTION_H__
#define __XVR2_NETWORK_EXCEPTION_H__
#include<xvr2/Exception.h>
#include<xvr2/IOException.h>
namespace xvr2 {
	namespace Exception{

		/** This is a generic exception it is supposed to be thrown for undefined or
		 * generic network events */
		class Network:public Exception{
			public:
				/**
				 * Default constructor
				 */
				Network();
		};

		/** Throw this exception when the connection passes the timeout */
		class ConnectionTimeout:public Network{
			public:
				/**
				 * Default constructor
				 */
				ConnectionTimeout();
		};

		/** Throw this exception when the connection gets refused by the other
		 * host */
		class ConnectionRefused:public Network{
			public:
				/**
				 * Default constructor
				 */
				ConnectionRefused();
		};

		/** This exception is thrown when the remote host cannot be reached by
		 * this host */
		class NetworkUnreachable:public Network{
			public:
				/**
				 * Default constructor
				 */
				NetworkUnreachable();
		};

		/**Throw this exception whenever yo hav a socket that is already bounded
		 * to an address */
		class SocketAlreadyBounded:public Network{
			public:
				SocketAlreadyBounded();
		};

		/** This exception is thrown when a previous socket is listening to this port */
		class SocketAlreadyUsed:public Network{
			public:
				SocketAlreadyUsed();
		};

	};
};

#endif
