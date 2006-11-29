/*
 * $Id$
 */
#ifndef __XVR2_CORE_EXCEPTIONS_H__
#define __XVR2_CORE_EXCEPTIONS_H__
#include<xvr2/Object.h>
#include<xvr2/TraceDumper.h>

namespace xvr2{

	/** \class Exception Exception.h <xvr2/CoreExceptions.h>
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
	 *  \brief Throw this exception when an operation over an array exceeds is 
	 *  inbound and outbound limits. */
	class ArrayIndexOutOfLimits:public Exception{
		public:
			/** Default constructor */
			ArrayIndexOutOfLimits();
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
	/** \class IOException CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  \brief This is a generic exception for I/O events.
	 *  This exception is thrown whenever a unexpected exception occurrs
	 *  dealing with the IO related classes. */
	class IOException:public Exception{
		public:
			/** Default constructor */
			IOException();
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
	 * EXCEPTIONS DERIVED FROM xvr2::IOException 
	 *************************************************************************/
	/** \class DSOException CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  \brief Use this exception whenever you want to throw a generic exception
     *  over a dso (dynamic shared object) event. */
	class DSOException:public IOException{
		public:
			/** Default Constructor */
			DSOException(const char *msg = 0);
	};

	/** \class FileException CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  \brief You will only be seeing this exception if a generic 
     *  (undetermined) exception has occurred on a file-based class. */
	class FileException:public IOException{
		public:
			/** Default constructor */
			FileException();
	};
	/** \class NotEnoughKernelMemory CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  \brief This exception will be thrown only if there is not enough memory 
	 *  for kernel use. */
	class NotEnoughKernelMemory:public IOException{
		public:
			/** Default constructor */
			NotEnoughKernelMemory();
	};

	/** \class BrokenPipe CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  \brief This exception is thrown whenever the other end of communication 
     *  has died or in the case of a socket when the remote host has closed 
	 *  connection without warning. */
	class BrokenPipe:public IOException{
		public:
			/** Default constructor */
			BrokenPipe();
	};

	/** \class ProcOutOfFileDescriptors CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  \brief This exception is thrown when the process is going out of 
     *  files. */
	class ProcOutOfFileDescriptors:public IOException{
		public:
			/** Default constructor */
			ProcOutOfFileDescriptors();
	};

	/** \class SysOutOfFileDescriptors CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  \brief This exception is thrown when the system is going out of 
     *  files. */
	class SysOutOfFileDescriptors:public IOException{
		public:
			/** Default constructor */
			SysOutOfFileDescriptors();
	};

	/** \class DeviceOrFIFONotFound CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  \brief This exception will be thrown only if while trying to open a FIFO
	 *  filename the process owning the PIPE is not running or while trying
	 *  to access a special device filename and the associated hardware is
	 *  non-existent. */
	class DeviceOrFIFONotFound:public IOException{
		public:
			/** Default constructor */
			DeviceOrFIFONotFound();
	};
	/** \class DeviceNotFound CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  \brief This exception will be thrown only if while trying to open a 
     * special device file the associated hardware is not properly connected to 
     * the system. */
	class DeviceNotFound:public IOException{
		public:
			/** Default constructor */
			DeviceNotFound();
	};

	/** \class InterruptedSystemCall CoreExceptions.h <xvr2/CoreExceptions.h>
     *  \brief This exception is thrown whenever a system call is interrupted 
     *  by another */
	class InterruptedSystemCall:public IOException{
		public:
			/**
			 * Default constructor
			 */
			InterruptedSystemCall();
	};

	/** \class SocketUnableToWrite CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  \brief This exception is thrown if it is not possible to write data to 
     *  the other end of communications. */
	class SocketUnableToWrite:public IOException{
		public:
			/** Default constructor */
			SocketUnableToWrite();
	};

	/** \class SocketUnableToRead CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  \brief This exception is thrown if it is not possible to read data from 
     *  the other end of communications. */
	class SocketUnableToRead:public IOException{
		public:
			/** Default constructor */
			SocketUnableToRead();
	};

	/*************************************************************************
	 * EXCEPTIONS DERIVED FROM xvr2::DSOException
	 *************************************************************************/
	/** \class CantLoadDSO CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  \brief This exception is thown whenever you're trying to load a 
     *  DSOException and some error ocurred. */
	class CantLoadDSO:public DSOException{
		public:
			/** Default constructor */
			CantLoadDSO();
	};

	/** \class CantUnloadDSO CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  \brief If a DSOException cannot be unloaded, this exception is 
     *  thrown. */
	class CantUnloadDSO:public DSOException{
		public:
			/** Default constructor */
			CantUnloadDSO();
	};

	/** \class DSOSymbolException CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  \brief This is a common error appearing whenever you cant load
	 *  a symbol from a DSOException. */
	class DSOSymbolException:public DSOException{
		public:
			/** Default constructor */
			DSOSymbolException();
	};

	/*************************************************************************
	 * EXCEPTIONS DERIVED FROM xvr2::FileException
	 *************************************************************************/
	/** \class FileExists CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  \brief Exception thrown when the file to be used alreadyeady exists.
     *  This exception will be thrown only if you enable the checking 
     *  while creating a new file in write or append mode. */
	class FileExists:public FileException{
		public:
			/** Default constructor */
			FileExists();
	};
	/** \class FeatureNotAvailableOnPipesOrSocket CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  This exception is thrown when u are attempting to execute an
	 *  operation that is only valid to common files and for PIPEs
	 *  or Sockets */
	class FeatureNotAvailableOnPipesOrSocket:public FileException{
		public:
			/** Default constructor */
			FeatureNotAvailableOnPipesOrSocket();
	};

	/** \class ThisIsADirectory CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  This exception will be thrown only if you are attempting to open
	 *  a file but the given filename corresponds to a directory. */
	class ThisIsADirectory:public FileException{
		public:
			/** Default constructor */
			ThisIsADirectory();
	};
	/** \class PermissionDenied CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  This exception will be thrown only if the current process does not
	 *  own the rights to do a specific operation on this file. */
	class PermissionDenied:public FileException{
		public:
			/** Default constructor */
			PermissionDenied();
	};
	/** \class FilenameTooLong CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  This exception will be thrown only if you are attempting to open a 
	 *  very large filename. */
	class FilenameTooLong:public FileException{
		public:
			/** Default constructor */
			FilenameTooLong();
	};
	/** \class FileOrDirectoryNotFound CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  This exception will be thrown only if you are opening a file for
	 *  reading and the currently opened file does not exist. */
	class FileOrDirectoryNotFound:public FileException{
		public:
			/** Default constructor */
			FileOrDirectoryNotFound();
	};
	/** \class ThisIsNotADirectory CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  This exception will be thrown only if you are attempting to open a 
	 *  directory and the given filename is not a directory. */
	class ThisIsNotADirectory:public FileException{
		public:
			/** Default constructor */
			ThisIsNotADirectory();
	};
	/** \class FileNotOpened CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  This exception will be thrown only if you attempt to execute an
	 *  operation on a non-opened file. */
	class FileNotOpened:public FileException{
		public:
			/** Default constructor */
			FileNotOpened();
	};
	/** \class UnableToWriteOnReadOnlyFile CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  This exception will be thrown only if you are trying to write on a
	 *  read only opened file. */
	class UnableToWriteOnReadOnlyFile:public FileException{
		public:
			/** Default constructor */
			UnableToWriteOnReadOnlyFile();
	};
	/** \class UnableToWriteOnRunningExecutableFile CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  This exception will be thrown only if you are trying to write on an
	 *  executable file of process which is already running. */
	class UnableToWriteOnRunningExecutableFile:public FileException{
		public:
			/** Default constructor */
			UnableToWriteOnRunningExecutableFile();
	};
	/** \class FilenameExceedsAddressSpace CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  This exception will be thrown only if you are trying to reach file 
	 *  which is outside of the address provided by its parent directory. */
	class FilenameExceedsAddressSpace:public FileException{
		public:
			/** Default constructor */
			FilenameExceedsAddressSpace();
	};
	/** \class TooManySymlinks CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  This exception will be thrown only if the file you are trying to read
	 *  is the last symlink in a very large chain. */
	class TooManySymlinks:public FileException{
		public:
			/** Default constructor */
			TooManySymlinks();
	};
	/** \class NotEnoughStorageSpace CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  This exception will be thrown only if there is not enough room to 
	 *  to open this file. */
	class NotEnoughStorageSpace:public FileException{
		public:
			/** Default constructor */
			NotEnoughStorageSpace();
	};
	/** \class MaximumNumberOfOpenFilesForThisProcess CoreExceptions.h <xvr2/CoreExceptions.h>
	 * This exception will be thrown only if the maximum number of opened
	 * files. */
	class MaximumNumberOfOpenFilesForThisProcess:public FileException{
		public:
			/** Default constructor */
			MaximumNumberOfOpenFilesForThisProcess();
	};
	/** \classMaximumNumberOfOpenFilesForThisSystem CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  This exception will be thrown only if this system has reached the
	 *  maximum number of opened files that the kernel can handle */
	class MaximumNumberOfOpenFilesForThisSystem:public FileException{
		public:
			/**
			 * Default constructor
			 */
			MaximumNumberOfOpenFilesForThisSystem();
	};

	/** \class FileTooBig CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  This exception is thrown whenever you attempt to write pass the maximum offset 
	 *  allowed or while writing a file will make it grow pass the implementation 
	 *  defined size for the current OS. */
	class FileTooBig:public FileException{
	        public:
	                /** Default constructor */
	                FileTooBig();
	};

	/** \class WriteWillBlock CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  The file was opened with NON-BLOCKING feature but if u write the process will 
	 *  block every I/O. */
	class WriteWillBlock:public FileException{
		public:
			/** Default constructor */
			WriteWillBlock();
	};

	/** \class FileNotFound CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  Unable to find the requested file. */
	class FileNotFound:public FileException{
		public:
			/** Default constructor */
			FileNotFound();
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
};

#endif

