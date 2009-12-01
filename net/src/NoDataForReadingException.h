/*
 * $Id$
 */
#ifndef __XVR2_NET_NoDataForReading_EXCEPTION_H__
#define __XVR2_NET_NoDataForReading_EXCEPTION_H__
#include<xvr2/Exception.h>
#include<xvr2/IOException.h>
#include<xvr2/NetworkException.h>
namespace xvr2 {
	namespace Exception{

		class NoDataForReading:public Network{
			public:
				/** Default constructor */
				NoDataForReading();
		};

	};
};
#endif

