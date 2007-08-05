/*
 * $Id$
 */
#include"config.h"
#include<xvr2/xvr2config.h>
#include"_xvr2netClassNames.h"
#include<xvr2/NetworkExceptions.h>
#include<xvr2/MessageStrings.h>
#include<openssl/err.h>

namespace xvr2 {
	namespace Net{

		static const char *_desc_CertificateIssuerNotFoundLocally = "CertificateIssuerNotFoundLocally exception throw n";
		static const char *_desc_CertificateLoadLocations = "CertificateLoadLocations exception throw n";
		static const char *_desc_CertificateLookupPending = "CertificateLookupPending exception throw n";
		static const char *_desc_Crypto = "Crypto exception throw n";
		static const char *_desc_KeyfileUnreadable = "KeyfileUnreadable exception throw n";
		static const char *_desc_NoDataForReading = "NoDataForReading exception throw n";
		static const char *_desc_NotConnected = "NotConnected exception throw n";
		static const char *_desc_NoValidCipherInList = "NoValidCipherInList exception throw n";
		static const char *_desc_SSLConnectFailed = "SSLConnectFailed exception throw n";
		static const char *_desc_SSLConnectionClosed = "SSLConnectionClosed exception throw n";
		static const char *_desc_SSLConnectionIsBusy = "The read/write operation was not completed, try again later";
		static const char *_desc_SSLInvalidCertificate = "Certificate is not valid";
		//static const char *_desc_SSLContextCreation = "SSLContextCreation exception throw n";
		//static const char *_desc_SSLGeneric = "SSLGeneric exception throw n";
		static const char *_desc_SSLInvalidPeerCertificate = "Peer's certificate is not valid";
		static const char *_desc_SSLSocketAddIOFailure = "SSLSocketAddIOFailure exception throw n";
		static const char *_desc_UDPReceiveTimeout = "UDPReceiveTimeout exception throw n";
		static const char *_desc_X509 = "X509 exception throw n";
		static const char *_desc_X509IssuerCertificateNotFound = "X509IssuerCertificateNotFound exception throw n";
		static const char *_desc_X509UnableToDecryptCertificate = "X509UnableToDecryptCertificate exception throw n";
		/***** LAST EXCEPTION DESCRIPTION *****/

		NetworkException::NetworkException(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(__xvr2_Net_NetworkException);
#endif
#ifndef strerror
			description = (char *)xvr2::excepGenNet;
#else
			description = strerror(errno);
#endif
		}

		ConnectionTimeout::ConnectionTimeout(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(__xvr2_Net_ConnectionTimeoutException);
#endif
			description = (char *)xvr2::excepNetTimeout;
		}

		ConnectionRefused::ConnectionRefused(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(__xvr2_Net_ConnectionRefusedException);
#endif
			description = (char *)xvr2::excepNetRefused;
		}

		NetworkUnreachable::NetworkUnreachable(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(__xvr2_Net_NetworkUnreachableException);
#endif
			description = (char *)xvr2::excepNetUnreach;
		}

		SocketAlreadyBounded::SocketAlreadyBounded(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(__xvr2_Net_SocketAlreadyBoundedException);
#endif
			description = (char *)xvr2::excepSockUsed;
		}

		SocketAlreadyUsed::SocketAlreadyUsed(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(__xvr2_Net_SocketAlreadyUsedException);
#endif
			description = (char *)xvr2::excepSockListening;
		}


		CertificateIssuerNotFoundLocally::CertificateIssuerNotFoundLocally(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(__xvr2_Net_CertificateIssuerNotFoundLocally);
#endif
			description = (char *)_desc_CertificateIssuerNotFoundLocally;
		}

		CertificateLoadLocations::CertificateLoadLocations(){
#if USE_EMBEDDED_CLASSNAMES
			setClassName(__xvr2_Net_CertificateLoadLocations);
#endif
			description = (char *)_desc_CertificateLoadLocations;
		}

		CertificateLookupPending::CertificateLookupPending(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_Net_CertificateLookupPending);
#endif
			description = (char *)_desc_CertificateLookupPending;
		}

		ConnectionResetByPeer::ConnectionResetByPeer(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)xvr2::_xvr2ConnectionResetByPeerException);
#endif
			description = (char *)xvr2::excepConnectionResetByPeer;
		}


		Crypto::Crypto(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_Net_Crypto);
#endif
			description = (char *)_desc_Crypto;
		}

		HostNotFound::HostNotFound(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)xvr2::_xvr2HostNotFoundException);
#endif
			description = (char *)xvr2::excepHostNotFound;
		}


		KeyfileUnreadable::KeyfileUnreadable(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_Net_KeyfileUnreadable);
#endif
			description = (char *)_desc_KeyfileUnreadable;
		}

		NoDataForReading::NoDataForReading(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_Net_NoDataForReading);
#endif
			description = (char *)_desc_NoDataForReading;
		}

		NoIPForYou::NoIPForYou(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)xvr2::_xvr2NoIPForYouException);
#endif
			description = (char *)xvr2::excepNoIPForYou;
		}


		NotConnected::NotConnected(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_Net_NotConnected);
#endif
			description = (char *)_desc_NotConnected;
		}

		NoValidCipherInList::NoValidCipherInList(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_Net_NoValidCipherInList);
#endif
			description = (char *)_desc_NoValidCipherInList;
		}

		NSFatal::NSFatal(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)xvr2::_xvr2NSFatalException);
#endif
			description = (char *)xvr2::excepNSFatal;
		}

		NSTryAgain::NSTryAgain(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)xvr2::_xvr2NSTryAgainException);
#endif
			description = (char *)xvr2::excepNSTryAgain;
		}

		SSLConnectFailed::SSLConnectFailed(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_Net_SSLConnectFailed);
#endif
			description = (char *)_desc_SSLConnectFailed;
		}

		SSLConnectionClosed::SSLConnectionClosed(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_Net_SSLConnectionClosed);
#endif
			description = (char *)_desc_SSLConnectionClosed;
		}

		SSLConnectionIsBusy::SSLConnectionIsBusy(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_Net_SSLConnectionIsBusy);
#endif
			description = (char *)_desc_SSLConnectionIsBusy;
		}
		
		SSLContextCreation::SSLContextCreation(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_Net_SSLContextCreation);
#endif
			//description = _desc_SSLContextCreation;
			description = (char *)ERR_lib_error_string(ERR_get_error());
#ifdef USE_DEBUG
			debugmsgln(this, description);
#endif
		}

		SSLGeneric::SSLGeneric(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_Net_SSLGeneric);
#endif
			//description = (char *)_desc_SSLGeneric;
			description = (char *)ERR_lib_error_string(ERR_get_error());
		}

		SSLInvalidCertificate::SSLInvalidCertificate(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_Net_SSLInvalidCertificate);
#endif
			description = (char *)_desc_SSLInvalidCertificate;
		}

		SSLInvalidPeerCertificate::SSLInvalidPeerCertificate(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_Net_SSLInvalidPeerCertificate);
#endif
			description = (char *)_desc_SSLInvalidPeerCertificate;
		}

		SSLSocketAddIOFailure::SSLSocketAddIOFailure(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_Net_SSLSocketAddIOFailure);
#endif
			description = (char *)_desc_SSLSocketAddIOFailure;
		}

		UDPReceiveTimeout::UDPReceiveTimeout(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_Net_UDPReceiveTimeout);
#endif
			description = (char *)_desc_UDPReceiveTimeout;
		}

		X509Exception::X509Exception(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_Net_X509);
#endif
			description = (char *)_desc_X509;
		}

		X509IssuerCertificateNotFound::X509IssuerCertificateNotFound(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_Net_X509IssuerCertificateNotFound);
#endif
			description = (char *)_desc_X509IssuerCertificateNotFound;
		}

		X509UnableToDecryptCertificate::X509UnableToDecryptCertificate(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_Net_X509UnableToDecryptCertificate);
#endif
			description = (char *)_desc_X509UnableToDecryptCertificate;
		}
	};
};

