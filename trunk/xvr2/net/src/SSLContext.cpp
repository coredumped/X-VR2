/*
 * $Id$
 */
#include<cstdlib>
#include<xvr2/SSLContext.h>
#include<xvr2/Mutex.h>
#include<openssl/ssl.h>
#include<openssl/x509.h>
#include<openssl/err.h>

namespace xvr2 {
namespace Net {

	class __ssl_ctx_cb_args{
		public:
		SSLContext *meptr;
		void *userdata;
		char *passphrase;
		__ssl_ctx_cb_args(){
			meptr = 0;
			userdata = 0;
			passphrase = 0;
		}
		__ssl_ctx_cb_args(SSLContext *c, char *p, void *u){
			meptr = c;
			passphrase = p;
			userdata = u;
		}
	} ;

	//static Mutex _init_M;

	static bool __ssl_lib_initialized = false;

	static void __init_ssl_library(SSLContext *creator){
		//_init_M.lock();
		if(!__ssl_lib_initialized){
#ifdef USE_DEBUG
			creator->debugmsgln(creator, "Initializing OpenSSL library...");
#endif
			SSL_library_init();
			SSL_load_error_strings();
			atexit(ERR_free_strings);
			__ssl_lib_initialized = true;
		}
		//_init_M.unlock();
	}
	
	SSLContext::SSLContext(int _method){
		__init_ssl_library(this);
		method = _method;
		ctx = 0;
		mydata = 0;
		switch(method){
			case SSL_V2:
				ctx = SSL_CTX_new(SSLv2_method());
				break;
			case SSL_V2_CLIENT:
				ctx = SSL_CTX_new(SSLv2_client_method());
				break;
			case SSL_V2_SERVER:
				ctx = SSL_CTX_new(SSLv2_server_method());
				break;
			case SSL_V3:
				ctx = SSL_CTX_new(SSLv3_method());
				break;
			case SSL_V3_CLIENT:
				ctx = SSL_CTX_new(SSLv3_client_method());
				break;
			case SSL_V3_SERVER:
				ctx = SSL_CTX_new(SSLv3_server_method());
				break;
			case SSL_V23_CLIENT:
				ctx = SSL_CTX_new(SSLv23_client_method());
				break;
			case SSL_V23_SERVER:
				ctx = SSL_CTX_new(SSLv23_server_method());
				break;
			case SSL_V23:
			default:
				ctx = SSL_CTX_new(SSLv23_method());
		}
		if(ctx == 0){
			throw Exception::SSLContextCreation();
		}
		//Initialize password callback
		__ssl_ctx_cb_args *x;
		x = new __ssl_ctx_cb_args(this, 0, 0);
		mydata = x;
#ifdef USE_DEBUG
		debugmsgln(this, "Initializing password callback...");
#endif
		SSL_CTX_set_default_passwd_cb((SSL_CTX *)ctx, passwdCB);
#ifdef USE_DEBUG
		debugmsgln(this, "Initializing default password callback userdata...");
#endif
		SSL_CTX_set_default_passwd_cb_userdata((SSL_CTX *)ctx, mydata);
	}
	SSLContext::~SSLContext(){
		if(ctx != 0){
#ifdef USE_DEBUG
			debugmsgln(this, "Released");
#endif
			SSL_CTX_free((SSL_CTX *)ctx);
			if(mydata != 0){
				__ssl_ctx_cb_args *x;
				x = (__ssl_ctx_cb_args *)mydata;
				delete x;
			}
		}
	}


	int SSLContext::passwdCB(char *buf,int num, int rwflag, void *userdata){
		__ssl_ctx_cb_args *data;
		data = (__ssl_ctx_cb_args *)userdata;
		return data->meptr->passwordCallback(buf, num, rwflag, data->userdata);
	}

	int SSLContext::passwordCallback(char *buf,int num, int rwflag, void *data){
		__ssl_ctx_cb_args *x;
		x = (__ssl_ctx_cb_args *)mydata;
		if(x->passphrase == 0){
			return 0;
		}
		strncpy(buf, (char *)(x->passphrase), num);
		buf[num - 1] = '\0';
		return(strlen(buf));
	}

	void SSLContext::setUserdata(void *data){
		__ssl_ctx_cb_args *x;
		x = (__ssl_ctx_cb_args *)mydata;
		x->userdata = data;
		x->passphrase = 0;
#ifdef USE_DEBUG
		debugmsgln(this, "Setting userdata...");
#endif
		SSL_CTX_set_default_passwd_cb_userdata((SSL_CTX *)ctx, mydata);
	}

	void SSLContext::setPassphrase(const char *passphrase){
		__ssl_ctx_cb_args *x;
		x = (__ssl_ctx_cb_args *)mydata;
		x->passphrase = (char *)passphrase;
#ifdef USE_DEBUG
		debugmsgln(this, "Setting passphrase...");
#endif
		SSL_CTX_set_default_passwd_cb_userdata((SSL_CTX *)ctx, mydata);
	}

	void SSLContext::pemCertificateChainFile(const String &chain_file){
#ifdef USE_DEBUG
		debugmsgln(this, "Loading certificate chain file in PEM format");
#endif
		if(!(SSL_CTX_use_certificate_chain_file((SSL_CTX *)ctx, chain_file.toCharPtr()))) 
			throw Exception::KeyfileUnreadable();
	}

	void SSLContext::privateKeyfile(const String &file, int type){
#ifdef USE_DEBUG
		debugmsgln(this, "Loading private key file in PEM format");
#endif
		switch(type){
			case SSLContext::KEYFILE_DEFAULT:
				if(!SSL_CTX_use_PrivateKey_file((SSL_CTX *)ctx, file.toCharPtr(), X509_FILETYPE_DEFAULT))
					throw Exception::KeyfileUnreadable();
				break;
			case SSLContext::KEYFILE_ASN1:
				if(!SSL_CTX_use_PrivateKey_file((SSL_CTX *)ctx, file.toCharPtr(), X509_FILETYPE_ASN1))
					throw Exception::KeyfileUnreadable();
				break;
			default:
			case SSLContext::KEYFILE_PEM:
				if(!SSL_CTX_use_PrivateKey_file((SSL_CTX *)ctx, file.toCharPtr(), X509_FILETYPE_PEM))
					throw Exception::KeyfileUnreadable();
				break;
		}
	}
	void SSLContext::rsaPrivateKeyfile(const String &file, int type){
		switch(type){
			case SSLContext::KEYFILE_DEFAULT:
				if(!SSL_CTX_use_RSAPrivateKey_file((SSL_CTX *)ctx, file.toCharPtr(), X509_FILETYPE_DEFAULT))
					throw Exception::KeyfileUnreadable();
				break;
			case SSLContext::KEYFILE_ASN1:
#ifdef USE_DEBUG
		debugmsgln(this, "Loading RSA private key file in ASN1 format");
#endif
				if(!SSL_CTX_use_RSAPrivateKey_file((SSL_CTX *)ctx, file.toCharPtr(), X509_FILETYPE_ASN1))
					throw Exception::KeyfileUnreadable();
				break;
			default:
			case SSLContext::KEYFILE_PEM:
#ifdef USE_DEBUG
		debugmsgln(this, "Loading RSA private key file in PEM format");
#endif
				if(!SSL_CTX_use_RSAPrivateKey_file((SSL_CTX *)ctx, file.toCharPtr(), X509_FILETYPE_PEM))
					throw Exception::KeyfileUnreadable();
				break;
		}
	}
	void SSLContext::loadVerifyLocations(const String &cafile, const String &capath){
#ifdef USE_DEBUG
		debugmsgln(this, "Loading certificate verification locations");
#endif
		if(!SSL_CTX_load_verify_locations((SSL_CTX *)ctx, cafile.toCharPtr(), capath.toCharPtr())){
			throw Exception::CertificateLoadLocations();
		}
	}

	bool SSLContext::privateKeyIsValid(){
#ifdef USE_DEBUG
		debugmsgln(this, "Verifying private key validity");
#endif
		if(SSL_CTX_check_private_key((SSL_CTX *)ctx) == 1)
			return true;
		return false;
	}

};
};
