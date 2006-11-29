/* $Id$ */
#ifndef __XVR2_THREAD_FINALIZATOR_H__
#define __XVR2_THREAD_FINALIZATOR_H__
#include<xvr2/FinalizerCallback.h>
#include<deque>

namespace xvr2 {

	class ThreadFinalizator : public xvr2::Object {
		private:
		protected:
			std::deque<FinalizerCallback *> finalizers;
			ThreadFinalizator();
		public:
			void registerFinalizer(FinalizerCallback *f_cb);
			void callFinalizers();

	};

};

#endif

