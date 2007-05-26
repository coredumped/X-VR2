/*
 * $Id$
 */

#include"config.h"
#include<xvr2/xvr2config.h>
#include"_xvr2netClassNames.h"
#include"TCPSocket.h"
#include"SSLSocket.h"
#include<openssl/ssl.h>

namespace xvr2 {
namespace Net {

	class ssl_internal_stack{
		public:
			::SSL *ssl;
			::BIO *sbio;
			ssl_internal_stack(){
				ssl = 0;
				sbio = 0;
			}
			~ssl_internal_stack(){
				if(ssl != 0){
					SSL_free(ssl);
				}
				if(sbio != 0){
					BIO_free_all(sbio);
				}
			}
	} ;

	void SSLSocket::attach(){
		ssl_internal_stack *stack;
		if(idata != 0){
			stack = (ssl_internal_stack *)idata;
			delete stack;
		}
		stack = new ssl_internal_stack();
		stack->ssl = SSL_new((SSL_CTX *)ctx.getInternal());
    		stack->sbio=BIO_new_socket(tsock,BIO_NOCLOSE);
		if(stack->sbio == 0x00)
			throw SSLSocketAddIOFailure();
		SSL_set_bio(stack->ssl, stack->sbio, stack->sbio);
    		if(SSL_connect(stack->ssl) <= 0)
			throw SSLConnectFailed();
		//Verify certificate now
		int vres;
		if((vres = SSL_get_verify_result(stack->ssl)) != X509_V_OK){
#ifdef USE_DEBUG
			::X509 *x5;
			x5 = SSL_get_peer_certificate(stack->ssl);
			X509 cert(x5);
			X509_free(x5);
#endif
			switch(vres){
				case X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT:
					throw X509IssuerCertificateNotFound();
				case X509_V_ERR_UNABLE_TO_DECRYPT_CERT_SIGNATURE:
					throw X509UnableToDecryptCertificate();
				case X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT_LOCALLY:
#ifdef USE_DEBUG
					debugmsg(this, "Certificate not found locally.\n");
#endif
					throw CertificateIssuerNotFoundLocally();
				default:
					throw SSLInvalidCertificate();
			}
		}
	}

	SSLSocket::SSLSocket(const SSLContext &_ctx){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName(__xvr2_Net_SSLSocket);
#endif
		idata = 0;
		ctx = _ctx;
		try{
			attach();
		}
		catch(...){
			throw ;
		}
	}
	//SSLSocket::SSLSocket(const SSLContext &_ctx, const char *thehost, int theport):TCPSocket(thehost, theport){
	SSLSocket::SSLSocket(const SSLContext &_ctx, const char *thehost, int theport){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName(__xvr2_Net_SSLSocket);
#endif
		port = theport;
		idata = 0;
		ctx = _ctx;
		try{
			attach();
		}
		catch(...){
			throw ;
		}
	}
	SSLSocket::SSLSocket(const SSLContext &_ctx, const String &thehost, int theport){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName(__xvr2_Net_SSLSocket);
#endif
		port = theport;
		idata = 0;
		ctx = _ctx;
		try{
			attach();
		}
		catch(...){
			throw ;
		}
	}
	SSLSocket::SSLSocket(SSLSocket *s){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName(__xvr2_Net_SSLSocket);
#endif
		idata = 0;
		ctx = s->ctx;
		try{
			attach();
		}
		catch(...){
			throw ;
		}
	}
	SSLSocket::SSLSocket(const SSLSocket &s){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName(__xvr2_Net_SSLSocket);
#endif
		idata = 0;
		ctx = s.ctx;
		try{
			attach();
		}
		catch(...){
			throw ;
		}
	}
	const SSLSocket &SSLSocket::operator=(const SSLSocket &s){
		idata = 0;
		ctx = s.ctx;
		try{
			attach();
		}
		catch(...){
			throw ;
		}
		return *this;
	}
	SSLSocket::~SSLSocket(){
		if(idata != 0){
			ssl_internal_stack *stack;
			stack = (ssl_internal_stack *)idata;
			delete stack;
		}
	}
	void SSLSocket::write(const void *buffer, unsigned long size){
		ssl_internal_stack *stack;
		stack = (ssl_internal_stack *)idata;
		int ret;
		if((ret = SSL_write(stack->ssl, buffer, size)) <= 0){
			switch(SSL_get_error(stack->ssl, ret)){
				case SSL_ERROR_ZERO_RETURN:
					throw SSLConnectionClosed();
					break;
				case SSL_ERROR_WANT_READ:
				case SSL_ERROR_WANT_WRITE:
					throw SSLConnectionIsBusy();
					break;
				case SSL_ERROR_WANT_CONNECT:
				case SSL_ERROR_WANT_ACCEPT:
					throw NotConnected();
					break;
				case SSL_ERROR_WANT_X509_LOOKUP:
					throw CertificateLookupPending();
					break;
				case SSL_ERROR_SYSCALL:
				case SSL_ERROR_SSL:
					throw SSLGeneric();
					break;
			}
		}
	}
	int SSLSocket::read(void *buffer, unsigned long size){
		ssl_internal_stack *stack;
		stack = (ssl_internal_stack *)idata;
		if(SSL_pending(stack->ssl) == 0){
			((char *)buffer)[0] = 0;
			return 0;
		}
		int ret;
		if((ret = SSL_read(stack->ssl, buffer, size)) <= 0){
			switch(SSL_get_error(stack->ssl, ret)){
				case SSL_ERROR_ZERO_RETURN:
					throw SSLConnectionClosed();
					break;
				case SSL_ERROR_WANT_WRITE:
				case SSL_ERROR_WANT_READ:
					throw SSLConnectionIsBusy();
					break;
				case SSL_ERROR_WANT_CONNECT:
				case SSL_ERROR_WANT_ACCEPT:
					throw NotConnected();
					break;
				case SSL_ERROR_WANT_X509_LOOKUP:
					throw CertificateLookupPending();
					break;
				case SSL_ERROR_SYSCALL:
				case SSL_ERROR_SSL:
					throw SSLGeneric();
					break;
			}
		}
		return ret;
	}
};
};
