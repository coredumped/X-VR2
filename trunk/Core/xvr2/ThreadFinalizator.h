/* $Id$ */
#ifndef __XVR2_THREAD_FINALIZATOR_H__
#define __XVR2_THREAD_FINALIZATOR_H__
#include<xvr2/FinalizerCallback.h>
#include<deque>

namespace xvr2 {
	/** \class ThreadFinalizator ThreadFinalizator.h <xvr2/ThreadFinalizator.h>
	 *  \brief
	 *  Interface class for handling Thread finalization stuff */
	class ThreadFinalizator : public xvr2::Object {
		private:
		protected:
			/** Doubly-ended queue which stores finalization callbacks */
			std::deque<FinalizerCallback *> finalizers;
			/** Doubly-ended queue which stores cancellation callbacks */
			std::deque<FinalizerCallback *> cancelCBs;
			/** Protected default constructor to prevent user initialization */
			ThreadFinalizator();
		public:
			/** Registers a new finalization callback to be called when
			 *  thread finalizes */
			void registerFinalizer(FinalizerCallback *f_cb);
			/** Registers a new cancellation callback to be called in the
			 *  event of thread cancellation only. */
			void registerCancellationCB(FinalizerCallback *f_cb);
			/** Calls each finalizer in reverse registration order.
			 *  \warning DO NOT CALL THIS METHOD DIRECTLY */
			void callFinalizers();
			/** Calls each cancellation callback in reverse registration order.
			 *  \warning DO NOT CALL THIS METHOD DIRECTLY */
			void callCancellationCallbacks();
			/** Removes all cancellation callbacks without executing them.
			 *  \warning DO NOT CALL THIS METHOD DIRECTLY */
			void removeCancellationCBs();

	};

};

#endif

