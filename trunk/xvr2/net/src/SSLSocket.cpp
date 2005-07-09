/*
 * $Id$
 */

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
    		stack->sbio=BIO_new_socket(tcpsock,BIO_NOCLOSE);
		if(stack->sbio == 0x00)
			throw Exception::SSLSocketAddIOFailure();
		SSL_set_bio(stack->ssl, stack->sbio, stack->sbio);
    		if(SSL_connect(stack->ssl) <= 0)
			throw Exception::SSLConnectFailed();
	}

	SSLSocket::SSLSocket(const SSLContext &_ctx){
		idata = 0;
		ctx = _ctx;
		try{
			attach();
		}
		catch(...){
			throw;
		}
	}
	SSLSocket::SSLSocket(const SSLContext &_ctx, const char *thehost, int theport){
		idata = 0;
		ctx = _ctx;
		try{
			attach();
		}
		catch(...){
			throw;
		}
	}
	SSLSocket::SSLSocket(const SSLContext &_ctx, const String &thehost, int theport){
		idata = 0;
		ctx = _ctx;
		try{
			attach();
		}
		catch(...){
			throw;
		}
	}
	SSLSocket::SSLSocket(SSLSocket *s){
		idata = 0;
		ctx = s->ctx;
		try{
			attach();
		}
		catch(...){
			throw;
		}
	}
	SSLSocket::SSLSocket(const SSLSocket &s){
		idata = 0;
		ctx = s.ctx;
		try{
			attach();
		}
		catch(...){
			throw;
		}
	}
	const SSLSocket &SSLSocket::operator=(const SSLSocket &s){
		idata = 0;
		ctx = s.ctx;
		try{
			attach();
		}
		catch(...){
			throw;
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
					throw Exception::SSLConnectionClosed();
					break;
				case SSL_ERROR_WANT_READ:
				case SSL_ERROR_WANT_WRITE:
					throw Exception::SSLConnectionIsBusy();
					break;
				case SSL_ERROR_WANT_CONNECT:
				case SSL_ERROR_WANT_ACCEPT:
					throw Exception::NotConnected();
					break;
				case SSL_ERROR_WANT_X509_LOOKUP:
					throw Exception::CertificateLookupPending();
					break;
				case SSL_ERROR_SYSCALL:
				case SSL_ERROR_SSL:
					throw Exception::SSLGeneric();
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
					throw Exception::SSLConnectionClosed();
					break;
				case SSL_ERROR_WANT_WRITE:
				case SSL_ERROR_WANT_READ:
					throw Exception::SSLConnectionIsBusy();
					break;
				case SSL_ERROR_WANT_CONNECT:
				case SSL_ERROR_WANT_ACCEPT:
					throw Exception::NotConnected();
					break;
				case SSL_ERROR_WANT_X509_LOOKUP:
					throw Exception::CertificateLookupPending();
					break;
				case SSL_ERROR_SYSCALL:
				case SSL_ERROR_SSL:
					throw Exception::SSLGeneric();
					break;
			}
		}
		return ret;
	}
};
};
