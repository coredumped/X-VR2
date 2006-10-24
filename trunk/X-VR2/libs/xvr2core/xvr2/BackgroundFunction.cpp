/* $Id$ */
#include"BackgroundFunction.h"
namespace xvr2 {
	void BackgroundFunction::registerFinalizer(FinalizerCallback &fc){
		finalizers.push_back(fc);
	}
	void BackgroundFunction::callFinalizers(){
		while(finalizers.size() > 0){
			FinalizerCallback fcb = finalizers.at(0);
			fcb();
			finalizers.pop_front();
		}
	}
};
