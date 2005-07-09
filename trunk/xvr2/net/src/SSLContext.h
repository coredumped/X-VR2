/*
 * $Id$
 */
#ifndef __XVR2_NET_SSL_CONTEXT_H__
#define __XVR2_NET_SSL_CONTEXT_H__
#include<xvr2/netdefs.h>
#include<xvr2/Object.h>
#include<xvr2/TCPSocket.h>
#include<xvr2/StringBuffer.h>
#include<xvr2/SSLContextCreationException.h>
#include<xvr2/KeyfileUnreadableException.h>
#include<xvr2/CertificateLoadLocationsException.h>
#include<xvr2/NoValidCipherInListException.h>

namespace xvr2 {
namespace Net {
	/**
	 * Instructions on how to create a socket
	 *
	 * SSLContext ctx;
	 * ctx.setPassphrase("somepassword");
	 * ctx.pemCertificateChainFile("chain_file.pem");
	 * ctx.privateKeyfile("pkey.pem");
	 * ctx.loadVerifyLocations("cafile.pem", "/some/path");
	 */
	class SSLContext:public Object{
		private:
			static int passwdCB(char *buf,int num, int rwflag, void *userdata);
		protected:
			void *ctx;
			int method;
			String keyfile;
			void *mydata;
			/** Cypher list */
			StringBuffer c_list;
		public:
			/** Instantiates an uninitialized SSL Context with the specified
			 *  connection method. */
			SSLContext(int _method = SSL_V23);
			SSLContext(const String &_keyfile, int _method = SSL_V23);
			~SSLContext();
			/** This method must be overriden in order to supply a different method
			 *  to obtain the keyfile password. You might want to override in the case
			 *  your are reading the passphrase from a file, console input, etc, etc. */
			virtual int passwordCallback(char *buf, int num, int rwflag, void *userdata);
			/** Permits to set a block of data to be passed to the passwordCallback() method
			 *  when called to save/load a keyfile */
			void setUserdata(void *data);
			/** This method lets you set the default passphrase to be used when saving/loading
			 *  a keifile.
			 *  NOTE: This method is useless if you decide to override the passwordCallback()
			 *  method. */
			void setPassphrase(const char *passphrase);
			void pemCertificateChainFile(const String &chain_file);
			void privateKeyfile(const String &file, int type = KEYFILE_PEM);
			void rsaPrivateKeyfile(const String &file, int type = KEYFILE_PEM);
			void loadVerifyLocations(const String &cafile, const String &capath);
			bool privateKeyIsValid();
			void *getInternal(){
				return ctx;
			}
			void addCipher(const String &cyp);
	};
}
};


#endif
