/*
 * $Id$
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
#include"config.h"
#include"CoreExceptions.h"
#include"MessageStrings.h"
#include"Memory.h"
#if __GNUC__ < 3
#include<errno.h>
#include<stdio.h>
#else
#include<cerrno>
#include<cstdio>
#include<iostream>
#endif
#ifndef _WIN32
#include<dlfcn.h>
#endif


namespace xvr2 {
	static const char *__xvr2_local_strings[] = {
		"This exception is thrown if while attempting to start a new thread the maximum number of threads supported by the OS has been reached.",
		"An operation was attempted over an invalid Thread"
	};

	Exception::Exception():ExceptionTracer(){
		description = (char *)xvr2::strGenericException;
	}
	Exception::~Exception(){
	}
	Exception::Exception(const char *d):ExceptionTracer(){
		if(d == 0)
			description = (char *)xvr2::strGenericException;
		else
			description = (char *)d;
	}
	std::string Exception::toString() {
		return std::string(description);
	}

	BufferTooSmall::BufferTooSmall(){
		description = (char *)xvr2::excepBufferTooSmall;
	}
	ArrayIndexOutOfLimits::ArrayIndexOutOfLimits(){
		description = (char *)xvr2::excepAOB;	
		_i = -1;
		_m = -1;
	}
	ArrayIndexOutOfLimits::ArrayIndexOutOfLimits(int _index, int _maxval){
		description = (char *)xvr2::excepAOB;	
		_i = _index;
		_m = _maxval;
	}

	int ArrayIndexOutOfLimits::index(){
		return _i;
	}

	int ArrayIndexOutOfLimits::maxval(){
		return _m;
	}
	NoMoreTokens::NoMoreTokens(){
		description = (char *)xvr2::excepNoTokens;
	}
	NullPointer::NullPointer(){
		description = (char *)xvr2::excepNullPtr;
	}

	NumberException::NumberException(){
		description = (char *)xvr2::excepNumeric;
	}
	ParseException::ParseException(){
		description = (char *)xvr2::excepParse;
	}
	UndefinedClassException::UndefinedClassException(){
		description = (char *)xvr2::excepUndefinedClass;
	}


///////////////////////////////////////
/////// GroupException //////////////////

	GroupException::GroupException(){
		description = (char *)xvr2::excepGroup;
	}


	GroupNotFound::GroupNotFound(){
		description = (char *)xvr2::excepGroupNotFound;
	}


///////////////////////////////////////
/////// IOException //////////////////

///////////////////////////////////////
/////// MemoryException //////////////////
	MemoryException::MemoryException(){
		description = (char *)xvr2::excepMemory;
	}

	AllocationFailed::AllocationFailed(){
		description = (char *)xvr2::excepAllocationFailed;
	}

	ReallocFailed::ReallocFailed(){
		description = (char *)xvr2::excepReallocFailed;
	}


///////////////////////////////////////
/////// MutexException //////////////////
	MutexException::MutexException(){
		description = (char *)xvr2::excepGenMutex;
	}

	DeadLock::DeadLock(){
		description = (char *)xvr2::excepDeadLock;
	}

	UnableToLockMutex::UnableToLockMutex(){
		description = (char *)xvr2::excepMutexNoLock;
	}

	UnableToUnlockMutex::UnableToUnlockMutex(){
		description = (char *)xvr2::excepMutexNoUnlock;
	}



///////////////////////////////////////
/////// ParseException //////////////////
	DateParseException::DateParseException(){
		description = (char *)xvr2::excepDateParse;
	}
	TimeParseException::TimeParseException(){
		description = (char *)xvr2::excepTimeParse;
	}
	BitParseException::BitParseException(){
		description = (char *)xvr2::excepBitParse;
	}
	ByteParseException::ByteParseException(){
		description = (char *)xvr2::excepByteParse;
	}
	

///////////////////////////////////////
/////// SecurityException //////////////////
	SecurityException::SecurityException(){
		description = (char *)xvr2::excepSecurity;
	}

	UserIDDoesNotMatch::UserIDDoesNotMatch(){
		description = (char *)xvr2::excepUserIDDoesNotMatch;
	}

	
///////////////////////////////////////
/////// SemaphoreException //////////////////
	SemaphoreException::SemaphoreException(){
		description = (char *)xvr2::excepSemaphore;
	}


	SemaphoreInitValueException::SemaphoreInitValueException(){
		description = (char *)xvr2::excepSemaphoreInitValue;
	}


	SemaphoreUnableToDestroy::SemaphoreUnableToDestroy(){
		description = (char *)xvr2::excepSemaphoreUnableToDestroy;
	}


	SemaphoreUnableToDecrease::SemaphoreUnableToDecrease(){
		description = (char *)xvr2::excepSemaphoreUnableToDecrease;
	}


	SemaphoreUnableToIncrease::SemaphoreUnableToIncrease(){
		description = (char *)xvr2::excepSemaphoreUnableToIncrease;
	}


///////////////////////////////////////
/////// ThreadException //////////////////
	ThreadException::ThreadException(){
		description = (char *)xvr2::excepGenThread;
	}

	ThreadNotRunning::ThreadNotRunning(){
		description = (char *)xvr2::excepThreadNotRunning;
	}

	ConditionVarWaitTimedOut::ConditionVarWaitTimedOut(){
		description = (char *)xvr2::excepConditionVarWaitTimedOut;
	}
	MaximumNumberOfRunningThreadsReached::MaximumNumberOfRunningThreadsReached(){
		description = (char *)__xvr2_local_strings[0];
	}
	InvalidThread::InvalidThread(){
		description = (char *)__xvr2_local_strings[1];
	}

///////////////////////////////////////
/////// UserException //////////////////
	UserException::UserException(){
		description = (char *)xvr2::excepUser;
	}


	UserNotFound::UserNotFound(){
		description = (char *)xvr2::excepUserNotFound;
	}
};
