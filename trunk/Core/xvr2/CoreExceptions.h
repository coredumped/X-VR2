/*
 * $Id:CoreExceptions.h 531 2007-08-11 09:05:29Z mindstorm2600 $
 *
 * X-VR2 
 * 
 * Copyright (C) Juan V. Guerrero 2007
 * 
 * Juan V. Guerrero <mindstorm2600@users.sourceforge.net>
 * 
 * This program is free software, distributed under the terms of
 * the GNU General Public License Version 2. See the LICENSE file
 * at the top of the source tree.
 */
#ifndef __XVR2_CORE_EXCEPTIONS_H__
#define __XVR2_CORE_EXCEPTIONS_H__
#include<xvr2/Object.h>
#include<xvr2/TraceDumper.h>

namespace xvr2{

	/** \class Exception CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  \brief This is the parent class of all the exceptions. */
	class Exception:public ExceptionTracer {
		private:
		protected:
			/** Stores the exception's description as a string */
			char *description;
		public:
			/** Default constructor */
			Exception();
			~Exception();
			/** This constructor assigns to the description the string
			 *  contained in d.
			 *  \param d Description string (the name and or description
			 *  of the exception. */
			Exception(const char *d);
			/** Displays the description of the exception */
			std::string toString();
	};



	/*********************************************************************
	 * EXCEPTIONS DERIVED FROM xvr2::Exception
	 *********************************************************************/
	/** \class BufferTooSmall CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  \brief To be thrown when you are trying to write data in a buffer whose 
	 *  storage size is too small. */
	class BufferTooSmall:public Exception{
		public:
			/** Default constructor */
			BufferTooSmall();
	};
	/** \class ArrayIndexOutOfLimits CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  \brief Throw this exception when an operation over an array exceeds its 
	 *  inbound or outbound limits. */
	class ArrayIndexOutOfLimits:public Exception{
		private:
			int _i;
			int _m;
		public:
			/** Default constructor */
			ArrayIndexOutOfLimits();
			ArrayIndexOutOfLimits(int _index, int _maxval);
			int index();
			int maxval();
	};
	
	/** \class ElementNotFound CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  \brief Use this exception when a search for an element returned no 
	 *  results or the results given doens't match what you were looking for. */
	class ElementNotFound:public Exception{
		public:
			/** Default constructor */
			ElementNotFound();
	};
	/** \class GroupException CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  \brief Generic exception for the group class. */
	class GroupException:public Exception{
		public:
			/** Default constructor */
			GroupException();
	};
	/** \class MemoryException CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  \brief Generic memory exception.
	 *  This exception is thrown whenever a unexpected exception occurrs
	 *  dealing with the Memory class. */
	class MemoryException:public Exception{
		public:
			/** Default constructor */
			MemoryException();
	};
	/** \class MutexException CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  \brief This is the generic exception thrown for mutexes.
	 *  This exception is thrown whenever a unexpected exception occurrs
	 *  dealing with Mutexes. */
	class MutexException:public Exception{
		public:
			/** Default constructor */
			MutexException();
	};
	/** \class NoMoreTokens CoreExceptions.h <xvr2/CoreExceptions.h>
	 * Use or trap this exception when you need to check if a Tokenizer has no 
	 * more tokens to find in the current string. */
	class NoMoreTokens:public Exception{
		public:
			/** Default constructor */
			NoMoreTokens();
	};
	/** \class NullPointer CoreExceptions.h <xvr2/CoreExceptions.h>
	 * Throw this exception when doing something that is not appropiate with
	 * a null pointer. */
	class NullPointer:public Exception{
		public:
			/** Default constructor */
			NullPointer();
	};
	/** \class NumberException CoreExceptions.h <xvr2/CoreExceptions.h>
	 * Throw this exception when expecting a number in an operation and and receiving
	 * something different. */
	class NumberException:public Exception{
		public:
			/** Default constructor */
			NumberException();
	};
	/** \class ParseException CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  Generic parsing exception */
	class ParseException:public Exception{
		public:
			/** Default constructor */
			ParseException();
	};
	/** \class SecurityException CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  This is a generic exception for security-related events. */
	class SecurityException:public Exception{
		public:
			/** Default constructor */
			SecurityException();
	};
	/** \class ThreadException CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  ThreadException Generic Exception. */
	class ThreadException:public Exception{
		public:
			/** Default constructor */
			ThreadException();
	};
	/** \class UserException CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  Generic exception of the user class */
	class UserException:public Exception{
		public:
			/** Default constructor */
			UserException();
	};
	/** \class UndefinedClass CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  \brief This exception is thrown whenever you try to access a class by a 
     *  name which is not the class's name. */
	class UndefinedClassException:public Exception{
		public:
			/** Default constructor */
			UndefinedClassException();
	};






	/*************************************************************************
	 * EXCEPTIONS DERIVED FROM xvr2::GroupException
	 *************************************************************************/
	/** \class GroupNotFound CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  This exception is thrown whenever you are trying to browse the group 
	 *  database for a specific entry and that entry is not available or 
	 *  non-existent */
	class GroupNotFound:public GroupException{
		public:
			/** Default constructor */
			GroupNotFound();
	};


	/*************************************************************************
	 * EXCEPTIONS DERIVED FROM xvr2::MemoryException
	 *************************************************************************/
	/** \class AllocationFailed CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  \brief This exceptions might be thrown if a call to malloc or any other
	 *  memory allocation routine has just failed, it may be posible that you 
	 *  are running out of memory or that this process is trying to allocate 
	 *  the maximum allowable memory size in the current system, sorry */
	class AllocationFailed:public MemoryException{
		public:
			/** Default constructor */
			AllocationFailed();
	};


	/** \class ReallocFailed CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  I was unable to decrease/enlarge your memory buffer */
	class ReallocFailed:public MemoryException{
		public:
			/**
			 * Default constructor
			 */
			ReallocFailed();
	};


	/*************************************************************************
	 * EXCEPTIONS DERIVED FROM xvr2::MutexException
	 *************************************************************************/
	/** \class DeadLock CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  This exception is triggered when a deadlock is detected. */
	class DeadLock:public MutexException{
		public:
			/** Default constructor */
			DeadLock();
	};

	/** \class UnableToLockMutex CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  This exception is used when a mutex failed to lock the current thread. */
	class UnableToLockMutex:public MutexException{
		public:
			/** Default constructor */
			UnableToLockMutex();
	};

	/** \class UnableToUnlockMutex CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  This exception is used when a mutex failed to unlock the current thread. */
	class UnableToUnlockMutex:public MutexException{
		public:
			/** Default constructor */
			UnableToUnlockMutex();
	};

	/*************************************************************************
	 * EXCEPTIONS DERIVED FROM xvr2::ParseException
	 *************************************************************************/
	/** \class DateParseException CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  Unable to parse and obtain a Date from the current object */
	class DateParseException:public ParseException{
		public:
			/** Default constructor */
			DateParseException();
	};
	/** \class TimeParseException CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  Unable to parse and obtain a Time instance from the current object */
	class TimeParseException:public ParseException{
		public:
			/**
			 * Default constructor
			 */
			TimeParseException();
	};
	/** \class BitParseException CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  This exception is thrown whenever you try to parse bit from an undefined format string or a too hard to transform datatype */
	class BitParseException:public ParseException{
		public:
			/** Default constructor */
			BitParseException();
	};
	/** \class ByteParseException CoreExceptions.h <xvr2/CoreExceptions.h>
	 * Unable to parse a byte from here, probably the data is smaller than a byte? */
	class ByteParseException:public ParseException{
		public:
			/** Default constructor */
			ByteParseException();
	};


	/*************************************************************************
	 * EXCEPTIONS DERIVED FROM xvr2::SecurityException
	 *************************************************************************/
	/** \class UserIDDoesNotMatch CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  \brief This is a generic exception for security-related events */
	class UserIDDoesNotMatch:public SecurityException{
		public:
			/** Default constructor */
			UserIDDoesNotMatch();
	};


	/*************************************************************************
	 * EXCEPTIONS DERIVED FROM xvr2::ThreadException
	 *************************************************************************/
	/** \class SemaphoreException CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  \brief Generic semaphore exception */
	class SemaphoreException:public ThreadException{
		public:
			/** Default constructor */
			SemaphoreException();
	};
	/** \class ThreadNotRunning CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  \brief If you try to execute an operation that can only be placed
	 *  over a running Thred and you're current thread is not running yet
	 *  this is the exception that is going to be thrown */
	class ThreadNotRunning:public ThreadException{
		public:
			/** Default constructor */
			ThreadNotRunning();
	};
	/** \class MaximumNumberOfRunningThreadsReached CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  \brief Tbis exception is thrown if while attempting to start a new thread the maximum
	 *  number of threads supported by the OS has been reached. */
	class MaximumNumberOfRunningThreadsReached:public ThreadException{
		public:
			/** Default constructor */
			MaximumNumberOfRunningThreadsReached();
	};
	/** \class ConditionVarWaitTimedOut CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  The condition variable was signaled before wait interval has been reached, as a 
	 *  consecuence the controlled Mutex will be re-acquired */
	class ConditionVarWaitTimedOut:public ThreadException{
		public:
			/** Default constructor */
			ConditionVarWaitTimedOut();
	};
	/** \class InvalidThread CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  The user provided thread object is not being managed by the ThreadManager	
	 *  so its is invalid */
	class InvalidThread:public ThreadException{
		public:
			/** Default constructor */
			InvalidThread();
	};


	/*************************************************************************
	 * EXCEPTIONS DERIVED FROM xvr2::SemaphoreException
	 *************************************************************************/
	/** \class SemaphoreInitValueException CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  The initialization value for this semaphore is too big, unable to create 
	 *  semaphore, sorry */
	class SemaphoreInitValueException:public SemaphoreException{
		public:
			/** Default constructor */
			SemaphoreInitValueException();
	};


	/** \class SemaphoreUnableToDestroy CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  I'm unable to destroy this semaphore right now, maybe one or more threads are waiting
	 *  for it */
	class SemaphoreUnableToDestroy:public SemaphoreException{
		public:
			/** Default constructor */
			SemaphoreUnableToDestroy();
	};


	/** \class SemaphoreUnableToDecrease CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  Unable to decrease this semaphore's value, it is already very low */
	class SemaphoreUnableToDecrease:public SemaphoreException{
		public:
			/** Default constructor */
			SemaphoreUnableToDecrease();
	};


	/** \class SemaphoreUnableToIncrease CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  I'm unable to increase the value of this semaphore right now is bigger than the maximum
	 *  defined by this thread implementation, sorry */
	class SemaphoreUnableToIncrease:public SemaphoreException{
		public:
			/** Default constructor */
			SemaphoreUnableToIncrease();
	};


	/*************************************************************************
	 * EXCEPTIONS DERIVED FROM xvr2::UserException
	 *************************************************************************/
	/** \class UserNotFound CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  This exception is thrown whenever you are trying to browse the user database for a 
	 *  specific entry and that entry is not available or non-existent */
	class UserNotFound:public UserException{
		public:
			/** Default constructor */
			UserNotFound();
	};
}

#endif

