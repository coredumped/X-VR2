/*
 * $Id$
 */
#ifndef __XVR2_FUNCTION_H__
#define __XVR2_FUNCTION_H__
#include<xvr2/xvr2config.h>
#include<xvr2/Object.h>

namespace xvr2 {
	/** \class Function Function.h <xvr2/Function.h>
	 *  \brief
	 *  Interface class for implementing object functions */
	class Function:public Object {
		private:
		protected:
		public:
			/** Default constructor */
			Function();
	};
};

#endif
