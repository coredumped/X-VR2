/*
 * $Id$
 */
#include"config.h"
#include"CoreExceptions.h"
#include"MessageStrings.h"
#include"Memory.h"
#include"_xvr2ClassNames.h"
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
	static char *local_strings[] = {
		"This exception is thrown if while attempting to start a new thread the maximum number of threads supported by the OS has been reached.",
		"An operation was attempted over an invalid Thread"
	};

	Exception::Exception():ExceptionTracer(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName(xvr2::_xvr2Exception);
#endif
		description = (char *)xvr2::strGenericException;
	}
	Exception::~Exception(){
	}
	Exception::Exception(const char *d):ExceptionTracer(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName(xvr2::_xvr2Exception);
#endif
		if(d == 0)
			description = (char *)xvr2::strGenericException;
		else
			description = (char *)d;
	}
	std::string Exception::toString() {
		return std::string(description);
	}

	IOException::IOException(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2IOException);
#endif
#ifndef strerror
		description = (char *)xvr2::excepGenIO;
#else
		description = strerror(errno);
#endif
	}
	BufferTooSmall::BufferTooSmall(){
#if USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2BufferTooSmallException);
#endif
		description = (char *)xvr2::excepBufferTooSmall;
	}
	ArrayIndexOutOfLimits::ArrayIndexOutOfLimits(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2ArrayIndexOutOfLimitsException);
#endif
		description = (char *)xvr2::excepAOB;	
	}
	NoMoreTokens::NoMoreTokens(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2NoMoreTokensException);
#endif
		description = (char *)xvr2::excepNoTokens;
	}
	NullPointer::NullPointer(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2NullPointerException);
#endif
		description = (char *)xvr2::excepNullPtr;
	}

	NumberException::NumberException(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2NumberException);
#endif
		description = (char *)xvr2::excepNumeric;
	}
	ParseException::ParseException(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2ParseException);
#endif
		description = (char *)xvr2::excepParse;
	}
	UndefinedClassException::UndefinedClassException(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2UndefinedClassException);
#endif
		description = (char *)xvr2::excepUndefinedClass;
	}


///////////////////////////////////////
/////// DSOException //////////////////
	DSOException::DSOException(const char *msg){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2DSOException);
#endif
		if(msg)
			description = (char *)msg;
		else
			description = (char *)xvr2::excepGenDSO;
	}

	CantLoadDSO::CantLoadDSO(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2CantLoadDSOException);
#endif
#ifdef _WIN32		
		description = (char *)xvr2::excepNoLoadDSO;
#else
		description = dlerror();
#endif
	}

	CantUnloadDSO::CantUnloadDSO(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2CantUnloadDSOException);
#endif
#ifdef _WIN32		
		description = (char *)xvr2::excepNoUnloadDSO;
#else
		description = dlerror();
#endif
	}

	DSOSymbolException::DSOSymbolException(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2DSOSymbolException);
#endif
#ifdef _WIN32
		description = (char *)xvr2::excepNoLoadSymbol;
#else
		description = dlerror();
#endif
	}
	ElementNotFound::ElementNotFound(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2ElementNotFoundException);
#endif
		description = (char *)xvr2::excepNoElem;
	}


///////////////////////////////////////
/////// FileException //////////////////
	FileException::FileException(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2FileException);
#endif
		description = (char *)xvr2::excepFile;
	}

	FeatureNotAvailableOnPipesOrSocket::FeatureNotAvailableOnPipesOrSocket(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2FeatureNotAvailableOnPipesOrSocketException);
#endif
		description = (char *)xvr2::excepFeatureNotAvailableOnPipesOrSocket;
	}

	FileNotOpened::FileNotOpened(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2FileNotOpenedException);
#endif
		description = (char *)xvr2::excepFileNotOpened;
	}

	FileExists::FileExists(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2FileExistsException);
#endif
		description = (char *)xvr2::excepFileExists;
	}

	ThisIsADirectory::ThisIsADirectory(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2ThisIsADirectoryException);
#endif
		description = (char *)xvr2::excepThisIsADirectory;
	}

	PermissionDenied::PermissionDenied(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2PermissionDeniedException);
#endif
		description = (char *)xvr2::excepPermissionDenied;
	}

	FilenameTooLong::FilenameTooLong(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2FilenameTooLongException);
#endif
		description = (char *)xvr2::excepFilenameTooLong;
	}

	FileOrDirectoryNotFound::FileOrDirectoryNotFound(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2FileOrDirectoryNotFoundException);
#endif
		description = (char *)xvr2::excepFileOrDirectoryNotFound;
	}

	ThisIsNotADirectory::ThisIsNotADirectory(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2ThisIsNotADirectoryException);
#endif
		description = (char *)xvr2::excepThisIsNotADirectory;
	}

	UnableToWriteOnReadOnlyFile::UnableToWriteOnReadOnlyFile(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2UnableToWriteOnReadOnlyFileException);
#endif
		description = (char *)xvr2::excepUnableToWriteOnReadOnlyFile;
	}

	UnableToWriteOnRunningExecutableFile::UnableToWriteOnRunningExecutableFile(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2UnableToWriteOnRunningExecutableFileException);
#endif
		description = (char *)xvr2::excepUnableToWriteOnRunningExecutableFile;
	}

	FilenameExceedsAddressSpace::FilenameExceedsAddressSpace(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2FilenameExceedsAddressSpaceException);
#endif
		description = (char *)xvr2::excepFilenameExceedsAddressSpace;
	}

	TooManySymlinks::TooManySymlinks(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2TooManySymlinksException);
#endif
		description = (char *)xvr2::excepTooManySymlinks;
	}

	NotEnoughStorageSpace::NotEnoughStorageSpace(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2NotEnoughStorageSpaceException);
#endif
		description = (char *)xvr2::excepNotEnoughStorageSpace;
	}

	NotEnoughKernelMemory::NotEnoughKernelMemory(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2NotEnoughKernelMemoryException);
#endif
		description = (char *)xvr2::excepNotEnoughKernelMemory;
	}

	MaximumNumberOfOpenFilesForThisProcess::MaximumNumberOfOpenFilesForThisProcess(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2MaximumNumberOfOpenFilesForThisProcessException);
#endif
		description = (char *)xvr2::excepMaximumNumberOfOpenFilesForThisProcess;
	}

	MaximumNumberOfOpenFilesForThisSystem::MaximumNumberOfOpenFilesForThisSystem(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2MaximumNumberOfOpenFilesForThisSystemException);
#endif
		description = (char *)xvr2::excepMaximumNumberOfOpenFilesForThisSystem;
	}


	WriteWillBlock::WriteWillBlock(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2WriteWillBlockException);
#endif
		description = (char *)xvr2::excepWriteWillBlock;
	}

	FileTooBig::FileTooBig(){
#ifdef USE_EMBEDDED_CLASSNAMES
	        setClassName((char *)xvr2::_xvr2FileTooBigException);
#endif
	        description = (char *)xvr2::excepFileTooBig;
	}

	FileNotFound::FileNotFound(){
#ifdef USE_EMBEDDED_CLASSNAMES
	        setClassName((char *)xvr2::_xvr2FileNotFoundException);
#endif
	        description = (char *)xvr2::excepFileNotFound;
	}


///////////////////////////////////////
/////// GroupException //////////////////

	GroupException::GroupException(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2GroupException);
#endif
		description = (char *)xvr2::excepGroup;
	}


	GroupNotFound::GroupNotFound(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2GroupNotFoundException);
#endif
		description = (char *)xvr2::excepGroupNotFound;
	}


///////////////////////////////////////
/////// IOException //////////////////
	BrokenPipe::BrokenPipe(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2BrokenPipeException);
#endif
		description = (char *)xvr2::excepBrokenPipe;
	}

	ProcOutOfFileDescriptors::ProcOutOfFileDescriptors(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2ProcOutOfFileDescriptorsException);
#endif
		description = (char *)xvr2::excepNoFptrs;
	}

	SysOutOfFileDescriptors::SysOutOfFileDescriptors(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2SysOutOfFileDescriptorsException);
#endif
		description = (char *)xvr2::excepSysNoFptrs;
	}

	DeviceOrFIFONotFound::DeviceOrFIFONotFound(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2DeviceOrFIFONotFoundException);
#endif
		description = (char *)xvr2::excepDeviceOrFIFONotFound;
	}

	DeviceNotFound::DeviceNotFound(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2DeviceNotFoundException);
#endif
		description = (char *)xvr2::excepDeviceNotFound;
	}

	InterruptedSystemCall::InterruptedSystemCall(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2InterruptedSystemCallException);
#endif
		description = (char *)xvr2::excepInterruptedSystemCall;
	}

	SocketUnableToWrite::SocketUnableToWrite(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2SocketUnableToWriteException);
#endif
		description = (char *)xvr2::excepSendFailed;
	}

	SocketUnableToRead::SocketUnableToRead(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2SocketUnableToReadException);
#endif
		description = (char *)xvr2::excepRecvFailed;
	}


///////////////////////////////////////
/////// MemoryException //////////////////
	MemoryException::MemoryException(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2MemoryException);
#endif
		description = (char *)xvr2::excepMemory;
	}

	AllocationFailed::AllocationFailed(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2AllocationFailedException);
#endif
		description = (char *)xvr2::excepAllocationFailed;
	}

	ReallocFailed::ReallocFailed(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2ReallocFailedException);
#endif
		description = (char *)xvr2::excepReallocFailed;
	}


///////////////////////////////////////
/////// MutexException //////////////////
	MutexException::MutexException(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2MutexException);
#endif
		description = (char *)xvr2::excepGenMutex;
	}

	DeadLock::DeadLock(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2DeadLockException);
#endif
		description = (char *)xvr2::excepDeadLock;
	}

	UnableToLockMutex::UnableToLockMutex(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2UnableToLockMutexException);
#endif
		description = (char *)xvr2::excepMutexNoLock;
	}

	UnableToUnlockMutex::UnableToUnlockMutex(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2UnableToUnlockMutexException);
#endif
		description = (char *)xvr2::excepMutexNoUnlock;
	}



///////////////////////////////////////
/////// ParseException //////////////////
	DateParseException::DateParseException(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2DateParseException);
#endif
		description = (char *)xvr2::excepDateParse;
	}
	TimeParseException::TimeParseException(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2TimeParseException);
#endif
		description = (char *)xvr2::excepTimeParse;
	}
	BitParseException::BitParseException(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2BitParseException);
#endif
		description = (char *)xvr2::excepBitParse;
	}
	ByteParseException::ByteParseException(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2ByteParseException);
#endif
		description = (char *)xvr2::excepByteParse;
	}
	

///////////////////////////////////////
/////// SecurityException //////////////////
	SecurityException::SecurityException(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2SecurityException);
#endif
		description = (char *)xvr2::excepSecurity;
	}

	UserIDDoesNotMatch::UserIDDoesNotMatch(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2UserIDDoesNotMatchException);
#endif
		description = (char *)xvr2::excepUserIDDoesNotMatch;
	}

	
///////////////////////////////////////
/////// SemaphoreException //////////////////
	SemaphoreException::SemaphoreException(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2SemaphoreException);
#endif
		description = (char *)xvr2::excepSemaphore;
	}


	SemaphoreInitValueException::SemaphoreInitValueException(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2SemaphoreInitValueException);
#endif
		description = (char *)xvr2::excepSemaphoreInitValue;
	}


	SemaphoreUnableToDestroy::SemaphoreUnableToDestroy(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2SemaphoreUnableToDestroyException);
#endif
		description = (char *)xvr2::excepSemaphoreUnableToDestroy;
	}


	SemaphoreUnableToDecrease::SemaphoreUnableToDecrease(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2SemaphoreUnableToDecreaseException);
#endif
		description = (char *)xvr2::excepSemaphoreUnableToDecrease;
	}


	SemaphoreUnableToIncrease::SemaphoreUnableToIncrease(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2SemaphoreUnableToIncreaseException);
#endif
		description = (char *)xvr2::excepSemaphoreUnableToIncrease;
	}


///////////////////////////////////////
/////// ThreadException //////////////////
	ThreadException::ThreadException(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2ThreadException);
#endif
		description = (char *)xvr2::excepGenThread;
	}

	ThreadNotRunning::ThreadNotRunning(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2ThreadNotRunningException);
#endif
		description = (char *)xvr2::excepThreadNotRunning;
	}

	ConditionVarWaitTimedOut::ConditionVarWaitTimedOut(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2ConditionVarWaitTimedOutException);
#endif
		description = (char *)xvr2::excepConditionVarWaitTimedOut;
	}
	MaximumNumberOfRunningThreadsReached::MaximumNumberOfRunningThreadsReached(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2MaximumNumberOfRunningThreadsReached);
#endif
		description = (char *)local_strings[0];
	}
	InvalidThread::InvalidThread(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2InvalidThread);
#endif
		description = (char *)local_strings[1];
	}

///////////////////////////////////////
/////// UserException //////////////////
	UserException::UserException(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2UserException);
#endif
		description = (char *)xvr2::excepUser;
	}


	UserNotFound::UserNotFound(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName((char *)xvr2::_xvr2UserNotFoundException);
#endif
		description = (char *)xvr2::excepUserNotFound;
	}
};
