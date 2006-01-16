/*
 * $Id$
 */
#ifndef __XVR2_STANDARD_OUTPUT_H__
#define __XVR2_STANDARD_OUTPUT_H__
#include<xvr2/TextOutput.h>

namespace xvr2{
	/** This class represents the Standard Output output stream */
	class StandardOutput:public TextOutput{
		protected:
			void outputMethod(const void *buff, UInt32 size);
		public:
			StandardOutput();
	};
};

#endif
