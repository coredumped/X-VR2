/*
 * $Id$
 */
#include"config.h"
#include<xvr2/xvr2config.h>
#include"_xvr2netClassNames.h"
#include"X509Name.h"
#include<xvr2/BasicString.h>
#include<xvr2/String.h>
#include<xvr2/Tokenizer.h>

namespace xvr2 {
namespace Net {
	X509Name::X509Name(const String &x509_name){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName(__xvr2_Net_X509Name);
#endif
		Tokenizer tok(x509_name, "/");
		String tmp;
		while(!tok.finished()){
			tmp = tok.next();
			if(tmp.startsIWith("C=")){
				debugmsgln(this, tmp.toCharPtr());
				c = tmp;
				c.biteLeft(2);
			}
			else if(tmp.startsIWith("ST=")){
				debugmsgln(this, tmp.toCharPtr());
				st = tmp;
				st.biteLeft(3);
			}
			else if(tmp.startsIWith("L=")){
				debugmsgln(this, tmp.toCharPtr());
				l = tmp;
				l.biteLeft(2);
			}
			else if(tmp.startsIWith("O=")){
				debugmsgln(this, tmp.toCharPtr());
				o = tmp;
				o.biteLeft(2);
			}
			else if(tmp.startsIWith("OU=")){
				debugmsgln(this, tmp.toCharPtr());
				ou = tmp;
				ou.biteLeft(3);
			}
			else if(tmp.startsIWith("CN=")){
				debugmsgln(this, tmp.toCharPtr());
				cn = tmp;
				cn.biteLeft(3);
			}
			else if(tmp.startsIWith("emailAddress=")){
				debugmsgln(this, tmp.toCharPtr());
				e = tmp;
				e.biteLeft(13);
			}
		}
	}
};
};
