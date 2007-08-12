/*
 * $Id$
 */
#ifndef  __XVR2_SSL_X509_NAME_H__
#define  __XVR2_SSL_X509_NAME_H__
#include<xvr2/String.h>
#include<xvr2/Net/netdefs.h>
#include<xvr2/Net/NetworkExceptions.h>

namespace xvr2 {
namespace Net {
	class X509Name:public Object {
			//Common name
			String cn;
			//Organization
			String o;
			//Organizational Unit
			String ou;
			//e-mail
			String e;
			//Country
			String c;
			//State
			String st;
			//Location
			String l;
		public:
			X509Name(const String &x509_name);
			/** Returns the x509 name's cn entry */
			const String &commonName() const {
				return cn;
			}
			/** Returns the x509 name's o entry */
			const String &organization() const {
				return o;
			}
			/** Returns the x509 name's ou entry */
			const String &organizationalUnit() const {
				return ou;
			}
			/** Returns the x509 name's emailAddress entry */
			const String &email() const {
				return e;
			}
			/** Returns the x509 name's c entry */
			const String &country() const {
				return c;
			}
			/** Returns the x509 name's st entry */
			const String &state() const {
				return st;
			}
			/** Returns the x509 name's l entry */
			const String &location() const {
				return l;
			}
	};
};
};

#endif
