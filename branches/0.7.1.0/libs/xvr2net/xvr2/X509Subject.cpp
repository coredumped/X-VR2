/*
 * $Id$
 */
#include"config.h"
#include<xvr2/xvr2config.h>
#include"_xvr2netClassNames.h"
#include"xvr2/X509Subject.h"
#include"xvr2/Tokenizer.h"

namespace xvr2 {
namespace Net {
	X509Subject::X509Subject(const String &x509_name):X509Name(x509_name){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName(__xvr2_Net_X509Subject);
#endif
	}
};
};
