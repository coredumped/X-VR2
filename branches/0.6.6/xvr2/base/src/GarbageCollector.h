/*
 * $Id$
 */
#ifndef __GARBAGE_COLECTOR_H__
#define __GARBAGE_COLECTOR_H__
#include<System.h>
#include<TemporalBuffer.h>
#include<ElementNotFoundException.h>
#include<List.h>

namespace xvr2{
	/**
	 * This the garbage collector base class, it is the basic
	 * object for temporary buffer collection an release.
	 * Do not implement this class or any of other of its sub 
	 * classes, THIS IS FOR INTERNAL USE ONLY!!!!
	 *
	 */
	class GarbageCollector:public System{
		protected:
			/**
			 * This list holds the temporarybuffer
			 * objects to be collected when they reach
			 * their maximum time to live
			 */
			Util::List<TemporalBuffer *> *garbage;
		public:
			/**
			`* Default constructor, this will initialize 
			`* the <i>garbage</i> List
			`*/
			GarbageCollector();	
			virtual ~GarbageCollector();	
			/** Add a new memory object to be collected */
			void add(TemporalBuffer *a);
			virtual void collect();
	};

};

#endif