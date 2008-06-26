/*
 * $Id$
 */
#ifndef __XVR2_NETWORK_EXCEPTION_H__
#define __XVR2_NETWORK_EXCEPTION_H__
#include<xvr2/CoreExceptions.h>
namespace xvr2 {
	namespace Net {
		/** This is a generic exception it is supposed to be throw n for undefined or
		 * generic network events */
		class NetworkException:public Exception{
			public:
				/**
				 * Default constructor
				 */
				NetworkException();
		};

		/** Throw this exception when the connection passes the timeout */
		class ConnectionTimeout:public NetworkException{
			public:
				/**
				 * Default constructor
				 */
				ConnectionTimeout();
		};

		/** Throw this exception when the connection gets refused by the other
		 * host */
		class ConnectionRefused:public NetworkException{
			public:
				/**
				 * Default constructor
				 */
				ConnectionRefused();
		};

		/** This exception is throw n when the remote host cannot be reached by
		 * this host */
		class NetworkUnreachable:public NetworkException{
			public:
				/**
				 * Default constructor
				 */
				NetworkUnreachable();
		};

		/**Throw this exception whenever yo hav a socket that is already bounded
		 * to an address */
		class SocketAlreadyBounded:public NetworkException{
			public:
				SocketAlreadyBounded();
		};

		/** This exception is throw n when a previous socket is listening to this port */
		class SocketAlreadyUsed:public NetworkException{
			public:
				SocketAlreadyUsed();
		};

		class CertificateLoadLocations:public NetworkException{
			public:
				/** Default constructor */
				CertificateLoadLocations();
		};
		class CertificateLookupPending:public NetworkException{
			public:
				/** Default constructor */
				CertificateLookupPending();
		};
		/**
		 * @class ConnectionResetByPeer
		 * @version $Revision$
		 * @brief The current connection suffered a reset from the peer
		 */
		class ConnectionResetByPeer:public NetworkException{
			public:
				/**
				 * Default constructor
				 */
				ConnectionResetByPeer();
		};
		/**
		 * @class HostNotFound
		 * @version $Revision$
		 * @brief Unable to find the specified host please check your /etc/hosts file or your DNS client config 
		 */
		class HostNotFound:public NetworkException{
			public:
				/**
				 * Default constructor
				 */
				HostNotFound();
		};
		class KeyfileUnreadable:public NetworkException{
			public:
				/** Default constructor */
				KeyfileUnreadable();
		};
		class NoDataForReading:public NetworkException{
			public:
				/** Default constructor */
				NoDataForReading();
		};
		/**
		 * @class NoIPForYou
		 * @version $Revision$
		 * @brief The requested name is valid but does not have an IP address. */
		class NoIPForYou:public NetworkException{
			public:
				/**
				 * Default constructor
				 */
				NoIPForYou();
		};
		class NotConnected:public NetworkException{
			public:
				/** Default constructor */
				NotConnected();
		};
		class NoValidCipherInList:public NetworkException{
			public:
				/** Default constructor */
				NoValidCipherInList();
		};
		/**
		 * @class NSFatal
		 * @version $Revision$
		 * @brief A non-recoverable name server error occurred. */
		class NSFatal:public NetworkException{
			public:
				/**
				 * Default constructor
				 */
				NSFatal();
		};
		/**
		 * @class NSTryAgain
		 * @version $Revision$
		 * @brief A temporary error occurred on an authoritative name server.  Try */
		class NSTryAgain:public NetworkException{
			public:
				/**
				 * Default constructor
				 */
				NSTryAgain();
		};

		class SSLConnectFailed:public NetworkException{
			public:
				/** Default constructor */
				SSLConnectFailed();
		};


		class SSLConnectionClosed:public NetworkException{
			public:
				/** Default constructor */
				SSLConnectionClosed();
		};


		class SSLConnectionIsBusy:public NetworkException{
			public:
				/** Default constructor */
				SSLConnectionIsBusy();
		};

		/** Exception throw n whenever an SSLContext object failed instatiation */
		class SSLContextCreation:public NetworkException{
			public:
				/** Default constructor */
				SSLContextCreation();
		};

		class SSLGeneric:public NetworkException{
			public:
				/** Default constructor */
				SSLGeneric();
		};

		class UDPReceiveTimeout:public NetworkException{
			public:
				/** Default constructor */
				UDPReceiveTimeout();
		};

		class SSLInvalidCertificate:public SSLGeneric{
			public:
				/** Default constructor */
				SSLInvalidCertificate();
		};

		class SSLInvalidPeerCertificate:public SSLGeneric{
			public:
				/** Default constructor */
				SSLInvalidPeerCertificate();
		};

		class SSLSocketAddIOFailure:public SSLGeneric {
			public:
				/** Default constructor */
				SSLSocketAddIOFailure();
		};

		class Crypto:public NetworkException {
			public:
				/** Default constructor */
				Crypto();
		};

		class X509Exception:public Crypto{
			public:
				/** Default constructor */
				X509Exception();
		};

		class CertificateIssuerNotFoundLocally:public X509Exception{
			public:
				/** Default constructor */
				CertificateIssuerNotFoundLocally();
		};

		class X509IssuerCertificateNotFound:public X509Exception{
			public:
				/** Default constructor */
				X509IssuerCertificateNotFound();
		};

		class X509UnableToDecryptCertificate:public X509Exception{
			public:
				/** Default constructor */
				X509UnableToDecryptCertificate();
		};

	};
};
#endif

