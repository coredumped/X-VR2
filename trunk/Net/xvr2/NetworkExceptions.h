/*
 * $Id$
 *
 * X-VR2 
 * 
 * Copyright (C) Juan V. Guerrero 2007
 * 
 * Juan V. Guerrero <mindstorm2600@users.sourceforge.net>
 * 
 * This program is free software, distributed under the terms of
 * the GNU General Public License Version 2. See the LICENSE file
 * at the top of the source tree.
 */
#ifndef __XVR2_NETWORK_EXCEPTION_H__
#define __XVR2_NETWORK_EXCEPTION_H__
#include<xvr2/CoreExceptions.h>
#include<xvr2/SystemException.h>

namespace xvr2 {
	namespace Net {
		/** This is a generic exception it is supposed to be thrown for undefined or
		 * generic network events */
		class NetworkException:public SystemException{
			public:
				/** Default constructor. 
				 *  \warning Not a good idea to instatiate your exception from this
				 *  constructor, since the internal platform networking layer is very
				 *  OS-specific the best approach is to report the OS error condition
				 *  as well. */
				NetworkException();
				/** Constructor properly initializes al error condition reporting
				 *  variables needed by this exception object. */
				NetworkException(OSErrorCodeT error_code);
		};

		class UnsupportedProtocol:public NetworkException {
			private:
				int _proto_id;
			public:
				UnsupportedProtocol();
				UnsupportedProtocol(OSErrorCodeT error_code);
				UnsupportedProtocol(OSErrorCodeT error_code, int _protocol_id);
				int protocolID();
				String protocolName();

		};

		/** Throw this exception when the connection passes the timeout */
		class ConnectionTimeout:public NetworkException{
			public:
				/** Default constructor. 
				 *  \warning Not a good idea to instatiate your exception from this
				 *  constructor, since the internal platform networking layer is very
				 *  OS-specific the best approach is to report the OS error condition
				 *  as well. */
				ConnectionTimeout();
				ConnectionTimeout(OSErrorCodeT error_code);
		};

		/** Throw this exception when the connection gets refused by the other
		 * host */
		class ConnectionRefused:public NetworkException{
			public:
				/** Default constructor. 
				 *  \warning Not a good idea to instatiate your exception from this
				 *  constructor, since the internal platform networking layer is very
				 *  OS-specific the best approach is to report the OS error condition
				 *  as well. */
				ConnectionRefused();
				ConnectionRefused(OSErrorCodeT error_code);
		};

		/** This exception is throw n when the remote host cannot be reached by
		 * this host */
		class NetworkUnreachable:public NetworkException{
			public:
				/** Default constructor. 
				 *  \warning Not a good idea to instatiate your exception from this
				 *  constructor, since the internal platform networking layer is very
				 *  OS-specific the best approach is to report the OS error condition
				 *  as well. */
				NetworkUnreachable();
				NetworkUnreachable(OSErrorCodeT error_code);
		};

		/**Throw this exception whenever yo hav a socket that is already bounded
		 * to an address */
		class SocketAlreadyBounded:public NetworkException{
			public:
				/** Default constructor. 
				 *  \warning Not a good idea to instatiate your exception from this
				 *  constructor, since the internal platform networking layer is very
				 *  OS-specific the best approach is to report the OS error condition
				 *  as well. */
				SocketAlreadyBounded();
				SocketAlreadyBounded(OSErrorCodeT error_code);
		};

		/** This exception is throw n when a previous socket is listening to this port */
		class SocketAlreadyUsed:public NetworkException{
			public:
				/** Default constructor. 
				 *  \warning Not a good idea to instatiate your exception from this
				 *  constructor, since the internal platform networking layer is very
				 *  OS-specific the best approach is to report the OS error condition
				 *  as well. */
				SocketAlreadyUsed();
				SocketAlreadyUsed(OSErrorCodeT error_code);
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
		/** \brief The current connection suffered a reset from the peer */
		class ConnectionResetByPeer:public NetworkException{
			public:
				/**
				 * Default constructor
				 */
				ConnectionResetByPeer();
		};
		/** @brief Unable to find the specified host please check your 
		 *  /etc/hosts file or your DNS client config */
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
		/** @brief The requested name is valid but does not have an 
		 *  IP address. */
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
		/** \brief A non-recoverable name server error occurred. */
		class NSFatal:public NetworkException{
			public:
				/**
				 * Default constructor
				 */
				NSFatal();
		};
		/** \brief A temporary error occurred on an authoritative name server.*/
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

