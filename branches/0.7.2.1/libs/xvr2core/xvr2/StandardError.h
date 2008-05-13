/*
 * $Id$
 */
#ifndef __XVR2_STANDARD_ERROR_H__
#define __XVR2_STANDARD_ERROR_H__
#include<xvr2/TextOutput.h>
#include<xvr2/CoreExceptions.h>

namespace xvr2{
	/** This class represents the Standard Error output stream */
	class StandardError:public TextOutput{
		protected:
			void outputMethod(const void *buff, UInt32 size);
		public:
			StandardError();
	};
};

#endif
