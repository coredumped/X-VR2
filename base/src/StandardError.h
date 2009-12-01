/*
 * $Id$
 */
#ifndef __XVR2_STANDARD_ERROR_H__
#define __XVR2_STANDARD_ERROR_H__
#include<TextOutput.h>

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
