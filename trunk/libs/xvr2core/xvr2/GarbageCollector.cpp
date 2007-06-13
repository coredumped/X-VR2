/*
 * $Id$
 */
#include"config.h"
#include"xvr2config.h"
#include"GarbageCollector.h"
#include<unistd.h>

#ifndef GARBAGE_DELETE_PAUSE
#define GARBAGE_DELETE_PAUSE 50
#endif

namespace xvr2{

	GarbageCollector::GarbageCollector(){
		//garbage = new Util::List<TemporalBuffer *>();
		garbage = new std::vector<TemporalBuffer *>();
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
		//garbage->add(a);
		garbage->push_back(a);
	}

	void GarbageCollector::collect(){
		UInt32 i;
		//garbage->rewind();
#ifdef USE_DEBUG
		debugmsg(this, "collecting garbage...\n");
#endif
		for(i = 0; i < garbage->size(); i++){
			//if(garbage->get(i)->elapsed() > garbage->get(i)->timeout()){
			if(garbage->at(i)->elapsed() > garbage->at(i)->timeout()){
#ifdef USE_DEBUG
				debugmsg(this, "Attempting to release an element");
#endif
				//garbage->get(i)->free();
				garbage->at(i)->free();
				System::usleep(GARBAGE_DELETE_PAUSE);
#ifdef USE_DEBUG
				debugmsg(this, "removing element from garbage list");
#endif
				//garbage->remove(i);
				TemporalBuffer *tmp = garbage->at(i);
				garbage->erase(garbage->begin() + i);
				delete tmp;
			}
		}
		//garbage->rewind();
#ifdef USE_DEBUG
		debugmsg(this, "collect terminated\n");
#endif
	}
	/*GarbageCollector::
	GarbageCollector::*/
};
