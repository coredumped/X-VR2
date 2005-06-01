/*
 * $Id$
 */
#include<xvr2/GarbageCollector.h>
#include<unistd.h>

#ifndef GARBAGE_DELETE_PAUSE
#define GARBAGE_DELETE_PAUSE 50
#endif

namespace xvr2{

	GarbageCollector::GarbageCollector(){
#ifndef USING_GCC3
		setClassName(xvr2::_xvr2GarbageCollector);
#endif
		garbage = new Util::List<TemporalBuffer *>();
	}

	GarbageCollector::~GarbageCollector(){
		//Implement cleanup here
		collect();
		System::usleep(GARBAGE_DELETE_PAUSE);
		delete garbage;
	}

	void GarbageCollector::add(TemporalBuffer *a){
#ifdef USE_DEBUG
		debugmsg(this, "Adding element to garbage list");
#endif
		garbage->add(a);
	}

	void GarbageCollector::collect(){
		UInt32 i;
		garbage->rewind();
#ifdef USE_DEBUG
		debugmsg(this, "collecting garbage...\n");
#endif
		for(i = 0; i < garbage->size(); i++){
			if(garbage->get(i)->elapsed() > garbage->get(i)->timeout()){
#ifdef USE_DEBUG
				debugmsg(this, "Attempting to release an element");
#endif
				garbage->get(i)->free();
				System::usleep(GARBAGE_DELETE_PAUSE);
#ifdef USE_DEBUG
				debugmsg(this, "removing element from garbage list");
#endif
				garbage->remove(i);
			}
		}
		garbage->rewind();
#ifdef USE_DEBUG
		debugmsg(this, "collect terminated\n");
#endif
	}
	/*GarbageCollector::
	GarbageCollector::*/
};
