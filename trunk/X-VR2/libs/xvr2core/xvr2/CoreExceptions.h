/*
 * $Id$
 */
#ifndef __XVR2_CORE_EXCEPTIONS_H__
#define __XVR2_CORE_EXCEPTIONS_H__
#include<xvr2/Object.h>
#include<xvr2/TraceDumper.h>

namespace xvr2{

	/**
	 * \class Exception Exception.h
	 * This is the parent class of all the exceptions
	 */
	class Exception:public ExceptionTracer {
		private:
		protected:
			/**
			 * \var char *description
			 * Stores the exception's description as a string
			 */
			char *description;
		public:
			/**
			 * \fn Exception();
			 * \brief Default constructor
			 */
			Exception();
			~Exception();
			/**
			 * \fn Exception(const char *d)
			 * \brief This constructor assigns to the description the string
			 * contained in d
			 * \param d Description string (the name and or description of the exception
			 */
			Exception(const char *d);
			/**
			 * \fn const char *toString();
			 * \brief Displays the description of the exception
			 */
			const char *toString() const;
	};



	/////////// EXCEPTIONS DERIVED FROM xvr2::Exception //////////////////
	/**
	 * \class BufferTooSmall BufferTooSmall.h
	 * To be thrown when you are trying to write data in a buffer whose storage size is too small
	 */
	class BufferTooSmall:public Exception{
		public:
			/**
			 * Default constructor
			 */
			BufferTooSmall();
	};
	/**
	 * Throw this exception when an operation over an array exceeds is inbound
	 * and outbound limits
	 */
	class ArrayIndexOutOfLimits:public Exception{
		public:
			/**
			 * Default constructor
			 */
			ArrayIndexOutOfLimits();
	};
	
	/**
	 * Use this exception when a search for an element returned no results or the results
	 * given doens't match what you were looking for
	 */
	class ElementNotFound:public Exception{
		public:
			/**
			 * Default constructor
			 */
			ElementNotFound();
	};
	/** Generic exception for the group class */
	class GroupException:public Exception{
		public:
			/**
			 * Default constructor
			 */
			GroupException();
	};
	/** This exception is thrown whenever you call a system call with
	 *  an invalid parameter */
	class InvalidParameter:public Exception{
		public:
			/**
			 * Default constructor
			 */
			InvalidParameter();
			/** Destructor */
			~InvalidParameter();
			/** Use this constructor to specify the name of the faulty
			 *  parameter
			 */
			InvalidParameter(const char *param_name);
	};
	/**
	 * This is a generic exception for I/O events
	 */
	class IOException:public Exception{
		public:
			/**
			 * Default constructor
			 */
			IOException();
	};
	/** Generic memory exception */
	class MemoryException:public Exception{
		public:
			/**
			 * Default constructor
			 */
			MemoryException();
	};
	/**
	 * This is the generic exception thrown for mutexes
	 */
	class MutexException:public Exception{
		public:
			/**
			 * Default constructor
			 */
			MutexException();
	};
	/**
	 * Use or trap this exception when you need to check if ha Tokenizer has no more tokens to
	 * find in the current string
	 */
	class NoMoreTokens:public Exception{
		public:
			/**
			 * Default constructor
			 */
			NoMoreTokens();
	};
	/**
	 * Throw this exception when doing something that is not appropiate with
	 * a null pointer
	 */
	class NullPointer:public Exception{
		public:
			/**
			 * Default constructor
			 */
			NullPointer();
	};
	/**
	 * Throw this exception when expecting a number in an operation and and receiving
	 * something different
	 */
	class NumberException:public Exception{
		public:
			/**
			 * Default constructor
			 */
			NumberException();
	};
	/** Generic parsing exception */
	class ParseException:public Exception{
		public:
			/**
			 * Default constructor
			 */
			ParseException();
	};
	/**
	 * This is a generic exception for security-related events
	 */
	class SecurityException:public Exception{
		public:
			/**
			 * Default constructor
			 */
			SecurityException();
	};
	/**
	 * ThreadException Generic Exception
	 */
	class ThreadException:public Exception{
		public:
			/**
			 * Default constructor
			 */
			ThreadException();
	};
	/** Generic exception of the user class */
	class UserException:public Exception{
		public:
			/**
			 * Default constructor
			 */
			UserException();
	};
	/**
	 * \class UndefinedClass CoreExceptions.h
	 * This exception is thrown whenever you try to access a class by a name
	 * which is not the class's name.
	 */
	class UndefinedClassException:public Exception{
		public:
			/**
			 * Default constructor
			 */
			UndefinedClassException();
	};


	/////////// EXCEPTIONS DERIVED FROM xvr2::IOException //////////////////
	/**
	 * Use this exception whenever you want to throw a generic exception over
	 * a dso (dynamic shared object) event */
	class DSOException:public IOException{
		public:
			/**
			 * Default Constructor
			 */
			DSOException(const char *msg = 0);
	};

	/**
	 * You will only be seeing this exception if a generic (undetermined)
	 * exception has occurred on a file-based class
	 */
	class FileException:public IOException{
		public:
			/**
			 * Default constructor
			 */
			FileException();
	};
	/**
	 * This exception will be thrown only if there is not enough memory 
	 * for kernel use
	 */
	class NotEnoughKernelMemory:public IOException{
		public:
			/**
			 * Default constructor
			 */
			NotEnoughKernelMemory();
	};

	/**
	 * This exception is thrown whenever the other end of communication has died
	 * or in the case of a socket when the remote host has closed connection without
	 * warning
	 */
	class BrokenPipe:public IOException{
		public:
			/**
			 * Default constructor
			 */
			BrokenPipe();
	};

	/**
	 * This exception is thrown when the process is going out of files
	 */
	class ProcOutOfFileDescriptors:public IOException{
		public:
			/**
			 * Default constructor
			 */
			ProcOutOfFileDescriptors();
	};

	/**
	 * This exception is thrown when the system is going out of files
	 */
	class SysOutOfFileDescriptors:public IOException{
		public:
			/**
			 * Default constructor
			 */
			SysOutOfFileDescriptors();
	};

	/**
	 * This exception will be thrown only if while trying to open a FIFO
	 * filename the process owning the PIPE is not running or while trying
	 * to access a special device filename and the associated hardware is
	 * non-existent
	 */
	class DeviceOrFIFONotFound:public IOException{
		public:
			/**
			 * Default constructor
			 */
			DeviceOrFIFONotFound();
	};
	/**
	 * This	exception will be thrown only if while trying to open a special
	 * device file the associated hardware is not properly connected to the
	 * system
	 */
	class DeviceNotFound:public IOException{
		public:
			/**
			 * Default constructor
			 */
			DeviceNotFound();
	};

	/** This exception is thrown whenever a system call is interrupted by another */
	class InterruptedSystemCall:public IOException{
		public:
			/**
			 * Default constructor
			 */
			InterruptedSystemCall();
	};

	/**
	 * This exception is thrown if it is not possible to write data to the other
	 * end of communications
	 */
	class SocketUnableToWrite:public IOException{
		public:
			/**
			 * Default constructor
			 */
			SocketUnableToWrite();
	};

	/**
	 * This exception is thrown if it is not possible to read data from the other
	 * end of communications
	 */
	class SocketUnableToRead:public IOException{
		public:
			/**
			 * Default constructor
			 */
			SocketUnableToRead();
	};


	/////////// EXCEPTIONS DERIVED FROM xvr2::DSOException //////////////////
	/**
	 * This exception is thown whenever you're trying to load a DSOException and some error
	 * ocurred
	 */
	class CantLoadDSO:public DSOException{
		public:
			/**
			 * Default constructor
			 */
			CantLoadDSO();
	};

	/**
	 * If a DSOException cannot be unloaded, this exception is thrown
	 */
	class CantUnloadDSO:public DSOException{
		public:
			/**
			 * Default constructor
			 */
			CantUnloadDSO();
	};

	/**
	 * This is a common error appearing whenever you cant load
	 * a symbol from a DSOException
	 */
	class DSOSymbolException:public DSOException{
		public:
			/**
			 * Default constructor
			 */
			DSOSymbolException();
	};


	/////////// EXCEPTIONS DERIVED FROM xvr2::FileException //////////////////
	/**
	 * This exception will be thrown only if you enable the checking while
	 * creating a new file in write or append mode */
	class FileExists:public FileException{
		public:
			/**
			 * Default constructor
			 */
			FileExists();
	};
	/** This exception is thrown when u are attempting to execute an
	 *  operation that is only valid to common files and for PIPEs
	 *  or Sockets */
	class FeatureNotAvailableOnPipesOrSocket:public FileException{
		public:
			/**
			 * Default constructor
			 */
			FeatureNotAvailableOnPipesOrSocket();
	};

	/**
	 * This exception will be thrown only if you are attempting to open
	 * a file but the given filename corresponds to a directory
	 */
	class ThisIsADirectory:public FileException{
		public:
			/**
			 * Default constructor
			 */
			ThisIsADirectory();
	};
	/**
	 * This exception will be thrown only if the current process does not
	 * own the rights to do a specific operation on this file
	 */
	class PermissionDenied:public FileException{
		public:
			/**
			 * Default constructor
			 */
			PermissionDenied();
	};
	/**
	 * This exception will be thrown only if you are attempting to open a 
	 * very large filename
	 */
	class FilenameTooLong:public FileException{
		public:
			/**
			 * Default constructor
			 */
			FilenameTooLong();
	};
	/**
	 * This exception will be thrown only if you are opening a file for
	 * reading and the currently opened file does not exist
	 */
	class FileOrDirectoryNotFound:public FileException{
		public:
			/**
			 * Default constructor
			 */
			FileOrDirectoryNotFound();
	};
	/**
	 * This exception will be thrown only if you are attempting to open a 
	 * directory and the given filename is not a directory
	 */
	class ThisIsNotADirectory:public FileException{
		public:
			/**
			 * Default constructor
			 */
			ThisIsNotADirectory();
	};
	/**
	 * This exception will be thrown only if you attempt to execute an
	 * operation on a non-opened file
	 */
	class FileNotOpened:public FileException{
		public:
			/**
			 * Default constructor
			 */
			FileNotOpened();
	};
	/**
	 * This exception will be thrown only if you are trying to write on a
	 * read only opened file
	 */
	class UnableToWriteOnReadOnlyFile:public FileException{
		public:
			/**
			 * Default constructor
			 */
			UnableToWriteOnReadOnlyFile();
	};
	/**
	 * This exception will be thrown only if you are trying to write on an
	 * executable file of process which is already running
	 */
	class UnableToWriteOnRunningExecutableFile:public FileException{
		public:
			/**
			 * Default constructor
			 */
			UnableToWriteOnRunningExecutableFile();
	};
	/**
	 * This exception will be thrown only if you are trying to reach file 
	 * which is outside of the address provided by its parent directory
	 */
	class FilenameExceedsAddressSpace:public FileException{
		public:
			/**
			 * Default constructor
			 */
			FilenameExceedsAddressSpace();
	};
	/**
	 * This exception will be thrown only if the file you are trying to read
	 * is the last symlink in a very large chain
	 */
	class TooManySymlinks:public FileException{
		public:
			/**
			 * Default constructor
			 */
			TooManySymlinks();
	};
	/**
	 * This exception will be thrown only if there is not enough room to 
	 * to open this file
	 */
	class NotEnoughStorageSpace:public FileException{
		public:
			/**
			 * Default constructor
			 */
			NotEnoughStorageSpace();
	};
	/**
	 * This exception will be thrown only if the maximum number of opened
	 * files
	 */
	class MaximumNumberOfOpenFilesForThisProcess:public FileException{
		public:
			/**
			 * Default constructor
			 */
			MaximumNumberOfOpenFilesForThisProcess();
	};
	/**
	 * This exception will be thrown only if this system has reached the
	 * maximum number of opened files that the kernel can handle
	 */
	class MaximumNumberOfOpenFilesForThisSystem:public FileException{
		public:
			/**
			 * Default constructor
			 */
			MaximumNumberOfOpenFilesForThisSystem();
	};

	/** This exception is thrown whenever you attempt to write pass the maximum offset allowed or while writing a file will make it grow pass the implementation defined size for the current OS. */
	class FileTooBig:public FileException{
	        public:
	                /**
	                 * Default constructor
	                 */
	                FileTooBig();
	};

	/** The file was opened with NON-BLOCKING feature but if u write the process will block every I/O */
	class WriteWillBlock:public FileException{
		public:
			/**
			 * Default constructor
			 */
			WriteWillBlock();
	};

	/** Unable to find the requested file */
	class FileNotFound:public FileException{
		public:
			/**
			 * Default constructor
			 */
			FileNotFound();
	};


	/////////// EXCEPTIONS DERIVED FROM xvr2::GroupException //////////////////
	/** This exception is thrown whenever you are trying to browse the group database for a specific entry and that entry is not available or non-existent */
	class GroupNotFound:public GroupException{
		public:
			/**
			 * Default constructor
			 */
			GroupNotFound();
	};


	/////////// EXCEPTIONS DERIVED FROM xvr2::MemoryException //////////////////
	/** A call to malloc or any other memory allocation routine has just failed, it may be posible that you are running out of memory or that this process is trying to allocate the maximum allowable memory size in the current system, sorry */
	class AllocationFailed:public MemoryException{
		public:
			/**
			 * Default constructor
			 */
			AllocationFailed();
	};


	/** I was unable to decrease/enlarge your memory buffer */
	class ReallocFailed:public MemoryException{
		public:
			/**
			 * Default constructor
			 */
			ReallocFailed();
	};


	/////////// EXCEPTIONS DERIVED FROM xvr2::MutexException //////////////////
	/**
	 * This exception is triggered when a deadlock is detected
	 */
	class DeadLock:public MutexException{
		public:
			/**
			 * Default constructor
			 */
			DeadLock();
	};

	/**
	 * This exception is used when a mutex failed to lock the current thread
	 */
	class UnableToLockMutex:public MutexException{
		public:
			/**
			 * Default constructor
			 */
			UnableToLockMutex();
	};

	/**
	 * This exception is used when a mutex failed to unlock the current thread
	 */
	class UnableToUnlockMutex:public MutexException{
		public:
			/**
			 * Default constructor
			 */
			UnableToUnlockMutex();
	};


	/////////// EXCEPTIONS DERIVED FROM xvr2::ParseException //////////////////
	/** Unable to parse and obtain a Date from the current object */
	class DateParseException:public ParseException{
		public:
			/**
			 * Default constructor
			 */
			DateParseException();
	};
	/** Unable to parse and obtain a Time instance from the current object */
	class TimeParseException:public ParseException{
		public:
			/**
			 * Default constructor
			 */
			TimeParseException();
	};
	/** This exception is thrown whenever you try to parse bit from an undefined format string or a too hard to transform datatype */
	class BitParseException:public ParseException{
		public:
			/**
			 * Default constructor
			 */
			BitParseException();
	};
	/** Unable to parse a byte from here, probably the data is smaller than a byte? */
	class ByteParseException:public ParseException{
		public:
			/**
			 * Default constructor
			 */
			ByteParseException();
	};


	/////////// EXCEPTIONS DERIVED FROM xvr2::SecurityException //////////////////
	/**
	 * This is a generic exception for security-related events
	 */
	class UserIDDoesNotMatch:public SecurityException{
		public:
			/**
			 * Default constructor
			 */
			UserIDDoesNotMatch();
	};


	/////////// EXCEPTIONS DERIVED FROM xvr2::ThreadException //////////////////
	/** Generic semaphore exception */
	class SemaphoreException:public ThreadException{
		public:
			/**
			 * Default constructor
			 */
			SemaphoreException();
	};
	/**
	 * If you try to execute an operation that can only be placed
	 * over a running Thred and you're current thread is not running yet
	 * this is the exception that is going to be thrown */
	class ThreadNotRunning:public ThreadException{
		public:
			/**
			 * Default constructor
			 */
			ThreadNotRunning();
	};
	/** The condition variable was signaled before wait interval has been reached, as a consecuence the controlled Mutex will be re-acquired */
	class ConditionVarWaitTimedOut:public ThreadException{
		public:
			/**
			 * Default constructor
			 */
			ConditionVarWaitTimedOut();
	};

	/////////// EXCEPTIONS DERIVED FROM xvr2::SemaphoreException //////////////////
	/** The initialization value for this semaphore is too big, unable to create semaphore, sorry */
	class SemaphoreInitValueException:public SemaphoreException{
		public:
			/**
			 * Default constructor
			 */
			SemaphoreInitValueException();
	};


	/** I'm unable to destroy this semaphore right now, maybe one or more threads are waiting for it */
	class SemaphoreUnableToDestroy:public SemaphoreException{
		public:
			/**
			 * Default constructor
			 */
			SemaphoreUnableToDestroy();
	};


	/** Unable to decrease this semaphore's value, it is already very low */
	class SemaphoreUnableToDecrease:public SemaphoreException{
		public:
			/**
			 * Default constructor
			 */
			SemaphoreUnableToDecrease();
	};


	/** I'm unable to increase the value of this semaphore right now is bigger than the maximum defined by this thread implementation, sorry */
	class SemaphoreUnableToIncrease:public SemaphoreException{
		public:
			/**
			 * Default constructor
			 */
			SemaphoreUnableToIncrease();
	};


	/////////// EXCEPTIONS DERIVED FROM xvr2::UserException //////////////////
	/** This exception is thrown whenever you are trying to browse the user database for a specific entry and that entry is not available or non-existent */
	class UserNotFound:public UserException{
		public:
			/**
			 * Default constructor
			 */
			UserNotFound();
	};
};


#endif
