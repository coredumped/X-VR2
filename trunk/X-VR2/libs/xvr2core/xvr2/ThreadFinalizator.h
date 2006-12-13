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
			std::deque<FinalizerCallback *> cancelCBs;
			ThreadFinalizator();
		public:
			void registerFinalizer(FinalizerCallback *f_cb);
			/** Registers a new cancellation callback to be called in the
			 *  event of thread cancellation only. */
			void registerCancellationCB(FinalizerCallback *f_cb);
			void callFinalizers();
			void callCancellationCallbacks();
			void removeCancellationCBs();

	};

};

#endif

