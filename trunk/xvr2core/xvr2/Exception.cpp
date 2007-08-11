/*
 * $Id$
 *
 * This is the main class for exception treatment, this section
 * is going to be completely rewritten
 *
 */
#include"config.h"
#include"Exception.h"
#if __GNUC__ >= 3
#include<cerrno>
#else
#include<errno.h>
#endif

#include<string.h>
#include<iostream>
#include<cstdio>
#include"_xvr2ClassNames.h"
#include"MessageStrings.h"
namespace xvr2{
	Exception::Exception(){
		description = (char *)xvr2::strGenericException;
	}
	Exception::~Exception(){
	}

	Exception::Exception(const char *d){
		if(d == 0)
			description = (char *)xvr2::strGenericException;
		else
			description = (char *)d;
	}

	const char *Exception::toString() const {
		return description;
	}
};
