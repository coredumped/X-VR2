/*
 * $Id$
 * 
 * Here we store references to some error and message strings, this way we are
 * sure that they're saved in the data segment of the binary
 *
 */
#include"config.h"
#include "MessageStrings.h"


namespace xvr2{

	const char *strGenericException = "Generic Exception";
	const char *excepAOB =  "Unable to read an element outside the limits of this array";
	const char *excepNullPtr =  "Null pointer";
	const char *excepNumeric =  "Number exception";
	const char *excepNoElem =  "Element not found exception";
	const char *excepNoTokens =  "No more tokens in this String";
	const char *excepGenMutex =  "Generic mutex exception";
	const char *excepMutexNoLock =  "Unable to lock mutex";
	const char *excepMutexNoUnlock =  "Unable to unlock mutex";
	const char *excepGenNet =  "Generic network error";
	const char *excepNetTimeout =  "Connection timeout while attempting to contact the remote host";
	const char *excepNetRefused =  "Connection refused by the other host";
	const char *excepNetUnreach = "Unable to reach that network, please check your routing config";
	const char *excepGenIO =  "Generic i/o error";
	const char *excepBrokenPipe =  "Broken pipe while doing an I/O operation";
	const char *excepSockUsed =  "Socket already bounded :-(";
	const char *excepSockListening =  "Another socket is already listening through this port :-(";
	const char *excepNoFptrs =  "There are not enough file descriptors for this process";
	const char *excepSysNoFptrs =  "There are not enough file descriptors in the system";
	const char *excepSendFailed =  "Unable to send data to the other host";
	const char *excepRecvFailed =  "Unable to recieve data from the other host";
	const char *excepGenDSO =  "Dynamic Shared Object generic exception";
	const char *excepNoLoadDSO =  "Unable to load DLL";
	const char *excepNoUnloadDSO =  "Unable to unload DLL";
	const char *excepNoLoadSymbol =  "Unable to load symbol from DLL";
	const char *excepDeadLock = "Locking this mutex will cause a DEADLOCK";
	const char *excepGenThread = "Thread Generic Exception";
	const char *excepThreadNotRunning = "This thread is not even running";

        const char *excepFileExists = "filename already exists and O_CREAT and O_EXCL were used";
        const char *excepThisIsADirectory = "filename refers to a directory and the access requested involved writing (that is, O_WRONLY or O_RDWR is set).";
        const char *excepPermissionDenied = "The  requested  access to the file is not allowed, or one of the directories in filename did not allow search  (execute)  permission, or the file did not exist yet and write access to the parent directory is not allowed.";
        const char *excepFilenameTooLong = "pathname was too long.";
        const char *excepFileOrDirectoryNotFound = "O_CREAT is not set and the named file does  not  exist.   Or,  a directory  component in pathname does not exist or is a dangling symbolic link.";
        const char *excepThisIsNotADirectory = "A component used as a directory in pathname is not, in  fact,  a directory,  or  O_DIRECTORY was specified and pathname was not a directory.";
        const char *excepDeviceOrFIFONotFound = "O_NONBLOCK | O_WRONLY is set, the named file is a  FIFO  and  no process has the file open for reading.  Or, the file is a device special file and no corresponding device exists.";
        const char *excepDeviceNotFound = "pathname refers to a device special file  and  no  corresponding device  exists.  (This is a Linux kernel bug - in this situation ENXIO must be returned.)";
        const char *excepUnableToWriteOnReadOnlyFile = "pathname refers to a file on a read-only  filesystem  and  write access was requested.";
        const char *excepUnableToWriteOnRunningExecutableFile = "pathname  refers to an executable image which is currently being executed and write access was requested.";
        const char *excepFilenameExceedsAddressSpace = "pathname points outside your accessible address space.";
        const char *excepTooManySymlinks = "Too many symbolic links were encountered in resolving  pathname, or O_NOFOLLOW was specified but pathname was a symbolic link.";
        const char *excepNotEnoughStorageSpace = "pathname  was  to  be created but the device containing pathname has no room for the new file.";
        const char *excepNotEnoughKernelMemory = "Insufficient kernel memory was available.";
        const char *excepMaximumNumberOfOpenFilesForThisProcess = "The process already has the maximum number of files open.";
        const char *excepMaximumNumberOfOpenFilesForThisSystem = "The limit on the total number of files open on  the  system  has been reached.";
        const char *excepFile = "Generic file error";
        const char *excepFileNotOpened = "Unable to operate on a non-opened file, please open it first";
	const char *excepInvalidParameter = "Invalid parameter for this system call";
	const char *excepFeatureNotAvailableOnPipesOrSocket = "This operation is not available for Pipes, FIFOs or Sockets";
        const char *excepUserIDDoesNotMatch = "The  process  does not have permission to send the signal to any of the receiving processes.  For a process to have permission to send  a signal  to  process pid it must either have root privileges, or the real or effective user ID of the  sending  process must  equal  the real or saved set-user-ID of the receiving process.  In the case of SIGCONT it suffices when the  sending  and receiving processes belong to the same session.";
        const char *excepSecurity = "Generic security exception";
        const char *excepFileTooBig = "This exception is thrown whenever you attempt to write pass the maximum offset allowed or while writing a file will make it grow pass the implementation defined size for the current OS.";





	const char *msgNothingLoaded = "Nothing loaded";
	const char *msgThreadOverride = "You should override this method in a new class\n";
	const char *msgDetachingThread = "DETACHING THREAD";
	const char *constDEVNULL = "/dev/null";
	const char *excepWriteWillBlock = "The file was opened with NON-BLOCKING feature but if u write the process will block every I/O";
	const char *excepInterruptedSystemCall = "This exception is thrown whenever a system call is interrupted by another";
	const char *msgPleaseOverride = "Please override this method";
	const char *excepMemory = "Generic memory exception";
	const char *excepAllocationFailed = "A call to malloc or any other memory allocation routine has just failed, it may be posible that you are running out of memory or that this process is trying to allocate the maximum allowable memory size in the current system, sorry";
	const char *excepReallocFailed = "I was unable to decrease/enlarge your memory buffer";
	const char *excepMath = "Generic mathematical exception";
	const char *excepBufferTooSmall = "You are trying to write data in a buffer whose storage size is too small";
	const char *excepGroup = "Generic exception for the group class";
	const char *excepUser = "Generic exception of the user class";
	const char *excepUserNotFound = "This exception is thrown whenever you are trying to browse the user database for a specific entry and that entry is not available or non-existent";
	const char *excepGroupNotFound = "This exception is thrown whenever you are trying to browse the group database for a specific entry and that entry is not available or non-existent";
	const char *excepConditionVarWaitTimedOut = "The condition variable was signaled before wait interval has been reached, as a consecuence the controlled Mutex will be re-acquired";
	const char *excepSemaphore = "Generic semaphore exception";
	const char *excepSemaphoreInitValue = "The initialization value for this semaphore is too big, unable to create semaphore, sorry";
	const char *excepSemaphoreUnableToDestroy = "I'm unable to destroy this semaphore right now, maybe one or more threads are waiting for it";
	const char *excepSemaphoreUnableToDecrease = "Unable to decrease this semaphore's value, it is already very low";
	const char *excepSemaphoreUnableToIncrease = "I'm unable to increase the value of this semaphore right now is bigger than the maximum defined by this thread implementation, sorry";
	const char *constNOVENDOR = "Undefined vendor";
	const char *excepFileNotFound = "Unable to find the requested file";
	const char *excepDatabaseException = "Generic database exception";
	const char *excepDBServerUnreachable = "Unable to reach the database server";
	const char *excepAlreadyConnected2DB = "An attempt to reconnect using the same connection failed because you are already connected";
	const char *excepDBConnectFirst = "In order to complete the current command to the SQL backend, please connect to the backend first";
	const char *excepUndefinedClass = "This class is not defined, are you sure this is the class you think it is?";
	const char *excepString = "Generic String exception";
	const char *excepParse = "Generic parsing exception";
	const char *excepDateParse = "Unable to parse and obtain a Date from the current object";
	const char *excepTimeParse = "Unable to parse and obtain a Time instance from the current object";
	const char *excepBitParse = "This exception is thrown whenever you try to parse bit from an undefined format string or a too hard to transform datatype";
	const char *excepByteParse = "Unable to parse a byte from here, probably the data is smaller than a byte?";
	const char *excepNoDataFetch = "Unable to complete the operation until you do a fetchRow first, sorry";
	const char *excepNoMoreRows = "There are no more rows to fetch from this ResultSet";
	const char *excepDBConnectionFailed = "Unable to connect to the specified database server";

	const char *excepServerDisconnected = "There was a sudden disconnection from the RDBMS";
	const char *excepSQLQuery = "Generic SQL query exception";
	const char *excepSQLQueryRDBMSDisconnected = "For some reason the server got disconnected while executing the underlying query.";
	const char *excepUnableToParseQuery = "The SQL query sentece provided was not compatible or understood by the RDBMS engine, please provide an appropiate SQL query with escape secuences were needed";
	const char *excepHostNotFound = "Unable to find the specified host please check your /etc/hosts file or your DNS client config";
	const char *excepNSTryAgain = "A temporary error occurred on an authoritative name server.  Try again later.";

	const char *excepNSFatal = "A non-recoverable name server error occurred.";

	const char *excepNoIPForYou = "The requested name is valid but does not have an IP address.";

	const char *excepConnectionResetByPeer = "The current connection suffered a reset from the peer";
};
