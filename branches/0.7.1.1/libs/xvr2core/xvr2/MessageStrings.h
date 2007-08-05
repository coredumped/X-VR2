/*
 * $Id$
 * 
 * Here we store references to some error and message strings, this way we are
 * sure that they're saved in the data segment of the binary
 *
 */
#ifndef _xvr2MessageStrings_H_
#define _xvr2MessageStrings_H_

namespace xvr2{
	extern const char *strGenericException;
	extern const char *excepAOB;
	extern const char *excepNullPtr;
	extern const char *excepNumeric;
	extern const char *excepNoElem;
	extern const char *excepNoTokens;
	extern const char *excepGenMutex;
	extern const char *excepMutexNoLock;
	extern const char *excepMutexNoUnlock;
	extern const char *excepGenNet;
	extern const char *excepNetTimeout;
	extern const char *excepNetRefused;
	extern const char *excepNetUnreach;
	extern const char *excepGenIO;
	extern const char *excepBrokenPipe;
	extern const char *excepSockUsed;
	extern const char *excepSockListening;
	extern const char *excepNoFptrs;
	extern const char *excepSysNoFptrs;
	extern const char *excepSendFailed;
	extern const char *excepRecvFailed;
	extern const char *excepGenDSO;
	extern const char *excepNoLoadDSO;
	extern const char *excepNoUnloadDSO;
	extern const char *excepNoLoadSymbol;
	extern const char *excepDeadLock;
	extern const char *excepGenThread;
	extern const char *excepThreadNotRunning;
	extern const char *excepFileExists;
	extern const char *excepThisIsADirectory;
	extern const char *excepPermissionDenied;
	extern const char *excepFilenameTooLong;
	extern const char *excepFileOrDirectoryNotFound;
	extern const char *excepThisIsNotADirectory;
	extern const char *excepDeviceOrFIFONotFound;
	extern const char *excepDeviceNotFound;
	extern const char *excepUnableToWriteOnReadOnlyFile;
	extern const char *excepUnableToWriteOnRunningExecutableFile;
	extern const char *excepFilenameExceedsAddressSpace;
	extern const char *excepTooManySymlinks;
	extern const char *excepNotEnoughStorageSpace;
	extern const char *excepNotEnoughKernelMemory;
	extern const char *excepMaximumNumberOfOpenFilesForThisProcess;
	extern const char *excepMaximumNumberOfOpenFilesForThisSystem;
	extern const char *excepFile;
	extern const char *excepFileNotOpened;
        extern const char *excepUserIDDoesNotMatch;
        extern const char *excepSecurity;
        extern const char *excepFileTooBig;



	extern const char *msgNothingLoaded;
	extern const char *msgThreadOverride;
	extern const char *msgDetachingThread;
	extern const char *excepInvalidParameter;
	extern const char *excepFeatureNotAvailableOnPipesOrSocket;

	extern const char *constDEVNULL;
	extern const char *excepWriteWillBlock;
	extern const char *excepInterruptedSystemCall;
	extern const char *msgPleaseOverride;
	extern const char *excepMemory;
	extern const char *excepAllocationFailed;
	extern const char *excepReallocFailed;
	extern const char *excepMath;
	extern const char *excepBufferTooSmall;
	extern const char *excepGroup;
	extern const char *excepUser;
	extern const char *excepUserNotFound;
	extern const char *excepGroupNotFound;
	extern const char *excepConditionVarWaitTimedOut;
	extern const char *excepSemaphore;
	extern const char *excepSemaphoreInitValue;
	extern const char *excepSemaphoreUnableToDestroy;
	extern const char *excepSemaphoreUnableToDecrease;
	extern const char *excepSemaphoreUnableToIncrease;
	extern const char *constNOVENDOR;
	extern const char *excepFileNotFound;
	extern const char *excepDatabaseException;
	extern const char *excepDBServerUnreachable;
	extern const char *excepAlreadyConnected2DB;
	extern const char *excepDBConnectFirst;
	extern const char *excepUndefinedClass;
	extern const char *excepString;
	extern const char *excepParse;
	extern const char *excepDateParse;
	extern const char *excepTimeParse;
	extern const char *excepBitParse;
	extern const char *excepByteParse;
	extern const char *excepNoDataFetch;
	extern const char *excepNoMoreRows;
	extern const char *excepDBConnectionFailed;
	extern const char *excepServerDisconnected;
	extern const char *excepSQLQuery;
	extern const char *excepSQLQueryRDBMSDisconnected;
	extern const char *excepUnableToParseQuery;
	extern const char *excepHostNotFound;

	extern const char *excepNSTryAgain;

	extern const char *excepNSFatal;

	extern const char *excepNoIPForYou;

	extern const char *excepConnectionResetByPeer;
};

#endif
