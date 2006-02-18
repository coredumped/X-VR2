/*
 * $Id$
 */
#include<xvr2/CoreExceptions.h>
#include<xvr2/GarbageCollector.h>
#include<xvr2/Thread.h>

#ifndef __AUTOMATED_GC_H__
#define __AUTOMATED_GC_H__

namespace xvr2{

	/**
	 * \class AutomatedGC AutomatedGC.h
	 * \brief This class is a more advanced interface for the garbage colletor, it
	 * will automatically check its garbage list to see if some TemporalBuffers
	 * has expired. It will do the checking every <b>_scanperiod</b> milliseconds
	 * \todo Implement some test programs
	 */
	class AutomatedGC:public GarbageCollector, public Thread{
		protected:
			/**
			 * \var UInt32 _scanperiod
			 * \brief The time in milliseconds for polling the garbage list
			 */
			UInt32 _scanperiod;
			/** 
			 * \var bool keepscanning
			 * \brief This will determine wheter the main garbage scanning
			 * loop should continue or not
			 */
			bool keepscanning;
		public:
			/**
			 * \fn AutomatedGC(UInt32 speriod)
			 * \brief This is the default constructor, it will initialize the
			 * poll time to speriod milliseconds
			 * \param speriod Specifies how often the garbage list will be queried (the
			 * value must be in milliseconds)
			 */
			AutomatedGC(UInt32 speriod);
			/**
			 * \fn void startChecking()
			 * \brief Call this function to enable the garbage scanning 
			 * process. Basically it will start a background process (using a thread)
			 * that will check if there is garbage to be released.
			 */
			void startChecking();
			/**
			 * \fn void *run()
			 * \brief This is the overriden version of Thread::run
			 * \return This method never returns
			 * \warning PLEASE DONT CALL THIS FUNCTION DIRECTLY
			 */
			void run();
			/**
			 * \fn void stop()
			 * \brief This will stop forever the garbage collecting process if you need to
			 * restart it, just call the startChecking() method again
			 */
			void stop();
	};

};

#endif
