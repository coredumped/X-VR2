/*
 * $Id$
 */
#ifndef __XVR2_INVALID_PARAMETER_EXCEPTION_H__
#define __XVR2_INVALID_PARAMETER_EXCEPTION_H__
#include<Exception.h>
/** This exception is thrown whenever you call a system call with
 *  an invalid parameter */
namespace xvr2{
	namespace Exception{

		class InvalidParameter:public Exception{
			public:
				/**
				 * Default constructor
				 */
				InvalidParameter();
				/** Destructor */
				~InvalidParameter();
				/** Use this constructor to specify the name of the faulty
				 *  parameter
				 */
				InvalidParameter(const char *param_name);
		};

	};
};

#endif
