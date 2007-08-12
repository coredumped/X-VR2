/*
 * $Id$
 */
#ifndef __XVR2_SSL_X509_H__
#define __XVR2_SSL_X509_H__
#include<xvr2/Net/netdefs.h>
#include<xvr2/String.h>
#include<xvr2/Date.h>
#include<xvr2/Net/X509Issuer.h>
#include<xvr2/Net/X509Subject.h>
#include<xvr2/Net/NetworkExceptions.h>

namespace xvr2 {
namespace Net {
	/** X.509 wrapper class */
	class X509:public Object {
		private:
		protected:
			void *idata;
			X509Issuer *_issuer;
			X509Subject *_subject;
			String _serial;
			String _hash;
			Date *_startDate;
			Date *_endDate;
			String _version;
			bool dont_free;
		public:
			X509();
			X509(void *x509_ptr);
			~X509();
			const X509Issuer &issuer() const;
			const X509Subject &subject() const;
			const String &serial() const;
			const String &hash() const;
			const Date &startDate() const;
			const Date &endDate() const;
			//Date &startDate() const;
			//Date &endDate() const;
			const String &version() const;
			void *getInternal(){
				return idata;
			}
	};
};
};
#endif
