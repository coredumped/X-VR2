/*
 * $Id$
 */
#ifndef __GARBAGE_COLECTOR_H__
#define __GARBAGE_COLECTOR_H__
#include<xvr2/System.h>
#include<xvr2/TemporalBuffer.h>
#include<xvr2/ElementNotFoundException.h>
#if __GNUC__ >= 3
#include<vector>
#else
#include<vector.h>
#endif

namespace xvr2{
	/**
	 * This the garbage collector base class, it is the basic
	 * object for temporary buffer collection an release.
	 * Do not implement this class or any other of its sub 
	 * classes, THIS IS FOR INTERNAL USE ONLY!!!!
	 */
	class GarbageCollector:public System{
		protected:
			/**
			 * This list holds the temporarybuffer
			 * objects to be collected when they reach
			 * their maximum time to live
			 */
			//Util::List<TemporalBuffer *> *garbage;
			std::vector<TemporalBuffer *> *garbage;
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
