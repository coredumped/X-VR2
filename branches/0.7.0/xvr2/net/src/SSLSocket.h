/*
 * $Id$
 */
#ifndef __XVR_SSL_SOCKET_H__
#define __XVR_SSL_SOCKET_H__
#include<xvr2/TCPSocket.h>
#include<xvr2/SSLContext.h>
#include<xvr2/SSLConnectFailedException.h>
#include<xvr2/SSLConnectionIsBusyException.h>
#include<xvr2/SSLConnectionClosedException.h>
#include<xvr2/CertificateLookupPendingException.h>
#include<xvr2/SSLGenericException.h>
#include<xvr2/SSLSocketAddIOFailureException.h>
#include<xvr2/NotConnectedException.h>
#include<xvr2/SSLInvalidCertificateException.h>
#include<xvr2/X509IssuerCertificateNotFoundException.h>
#include<xvr2/X509UnableToDecryptCertificateException.h>
#include<xvr2/CertificateIssuerNotFoundLocallyException.h>

namespace xvr2 {
	namespace Net {
		class SSLSocket : public TCPSocket{
			private:
			protected:
				SSLContext ctx;
				void *idata;
				void attach();
			public:
				SSLSocket(const SSLContext &_ctx);
				SSLSocket(const SSLContext &_ctx, const char *thehost, int theport);
				SSLSocket(const SSLContext &_ctx, const String &thehost, int theport);
				SSLSocket(SSLSocket *s);
				SSLSocket(const SSLSocket &s);
				const SSLSocket &operator=(const SSLSocket &s);
				virtual ~SSLSocket();
				virtual void write(const void *buffer, unsigned long size);
				virtual int read(void *buffer, unsigned long size);
		};
	};
};
#endif