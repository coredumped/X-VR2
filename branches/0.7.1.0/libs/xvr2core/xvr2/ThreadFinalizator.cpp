/* $Id$ */
#include"ThreadFinalizator.h"

namespace xvr2 {

	ThreadFinalizator::ThreadFinalizator(){
	}

	void ThreadFinalizator::registerFinalizer(FinalizerCallback *f_cb){
		finalizers.push_back(f_cb);
	}

	void ThreadFinalizator::registerCancellationCB(FinalizerCallback *f_cb){
		cancelCBs.push_back(f_cb);
	}

	void ThreadFinalizator::callFinalizers(){
		while(finalizers.size() > 0){
			FinalizerCallback *f_cb = finalizers[0];
			f_cb->operator()();
			finalizers.pop_front();
			delete f_cb;
		}
	}

	void ThreadFinalizator::callCancellationCallbacks(){
		while(cancelCBs.size() > 0){
			FinalizerCallback *f_cb = cancelCBs[0];
			f_cb->operator()();
			cancelCBs.pop_front();
			delete f_cb;
		}
	}

	void ThreadFinalizator::removeCancellationCBs(){
		cancelCBs.clear();
	}
};

