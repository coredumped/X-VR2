/*
 * $Id$
 */
#ifndef __XVR2_INVALID_PARAMETER_EXCEPTION_H__
#define __XVR2_INVALID_PARAMETER_EXCEPTION_H__
#include<xvr2/CoreExceptions.h>
#include<xvr2/String.h>
/** This exception is thrown whenever you call a system call with
 *  an invalid parameter */
namespace xvr2{
	/** \class InvalidParameter CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  \brief This exception is thrown whenever you call a system call with
	 *  an invalid parameter. */
	class InvalidParameter:public Exception{
		private:
			String param_name;
		public:
			/** Default constructor */
			InvalidParameter();
			/** Use this constructor to specify the name of the faulty
			 *  parameter */
			InvalidParameter(const String &_param_name);
			/** Returns the name of the faulty parameter */
			const String &param();
	};
};

#endif
