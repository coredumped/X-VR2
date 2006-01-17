/*
 * $Id$
 */
#ifndef __XVR2_EXCEPTION_TRACE_DUMPER_H__
#define __XVR2_EXCEPTION_TRACE_DUMPER_H__
#include<xvr2/Object.h>

namespace xvr2{
	namespace Exception{
		class ExceptionTracer : public Object {
			private:
				static bool isEnabled();
			protected:
				virtual void dumpTrace();
				//static bool enabled;
			public:
				ExceptionTracer();
				static void enable();
				static void disable();
		};
	};
};

#endif
