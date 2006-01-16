/*
 * $Id$
 *
 * This is the main class for exception treatment, this section
 * is going to be completely rewritten
 *
 */
#include<xvr2/Exception.h>
#include<errno.h>
#include<string.h>
#include<iostream>
#include<cstdio>
#include<xvr2/_xvr2ClassNames.h>
#include<xvr2/MessageStrings.h>
namespace xvr2{
	namespace Exception {

		Exception::Exception(){
#if __GNUC__ < 3
			setClassName(xvr2::_xvr2Exception);
#endif
			description = (char *)xvr2::strGenericException;
		}
		Exception::~Exception(){
		}

		Exception::Exception(const char *d){
#if __GNUC__ < 3
			setClassName(xvr2::_xvr2Exception);
#endif
			if(d == 0)
				description = (char *)xvr2::strGenericException;
			else
				description = (char *)d;
		}

		const char *Exception::toString() const {
			return description;
		}
	};
};
