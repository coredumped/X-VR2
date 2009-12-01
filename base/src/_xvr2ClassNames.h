/*
 * $Id$
 *
 * Here we store references to data strings containing the names of every class
 * belonging to this C++ Library
 */
#ifndef __xvr2ClassNames_H__
#define __xvr2ClassNames_H__

namespace xvr2 {
#if __GNUC__ < 3
	extern const char *_xvr2Array;
	extern const char *_xvr2ArrayIndexOutOfLimitsException;
	extern const char *_xvr2BrokenPipeException;
	extern const char *_xvr2CantLoadDSOException;
	extern const char *_xvr2CantUnloadDSOException;
	extern const char *_xvr2ConnectionRefusedException;
	extern const char *_xvr2ConnectionTimeoutException;
	extern const char *_xvr2Container;
	extern const char *_xvr2DSOException;
	extern const char *_xvr2DSOSymbolException;
	extern const char *_xvr2ElementNotFoundException;
	extern const char *_xvr2Exception;
	extern const char *_xvr2System;
	extern const char *_xvr2Threading;
	extern const char *_xvr2IOException;
	extern const char *_xvr2List;
	extern const char *_xvr2Mutex;
	extern const char *_xvr2MutexException;
	extern const char *_xvr2NetworkException;
	extern const char *_xvr2NetworkUnreachableException;
	extern const char *_xvr2nodeT;
	extern const char *_xvr2NoMoreTokensException;
	extern const char *_xvr2NullPointerException;
	extern const char *_xvr2NumberException;
	extern const char *_xvr2Object;
	extern const char *_xvr2Plugin;
	extern const char *_xvr2ProcOutOfFileDescriptorsException;
	extern const char *_xvr2TCPServerSocket;
	extern const char *_xvr2SharedVar;
	extern const char *_xvr2Socket;
	extern const char *_xvr2SocketAlreadyBoundedException;
	extern const char *_xvr2SocketAlreadyUsedException;
	extern const char *_xvr2SocketUnableToReadException;
	extern const char *_xvr2SocketUnableToWriteException;
	extern const char *_xvr2String;
	extern const char *_xvr2SysOutOfFileDescriptorsException;
	extern const char *_xvr2Thread;
	extern const char *_xvr2Tokenizer;
	extern const char *_xvr2UnableToLockMutexException;
	extern const char *_xvr2UnableToUnlockMutexException;
	extern const char *_xvr2DeadLockException;
	extern const char *_xvr2ThreadException;
	extern const char *_xvr2ThreadNotRunningException;
	extern const char *_xvr2FileExistsException;
	extern const char *_xvr2ThisIsADirectoryException;
	extern const char *_xvr2PermissionDeniedException;
	extern const char *_xvr2FilenameTooLongException;
	extern const char *_xvr2FileOrDirectoryNotFoundException;
	extern const char *_xvr2ThisIsNotADirectoryException;
	extern const char *_xvr2DeviceOrFIFONotFoundException;
	extern const char *_xvr2DeviceNotFoundException;
	extern const char *_xvr2UnableToWriteOnReadOnlyFileException;
	extern const char *_xvr2UnableToWriteOnRunningExecutableFileException;
	extern const char *_xvr2FilenameExceedsAddressSpaceException;
	extern const char *_xvr2TooManySymlinksException;
	extern const char *_xvr2NotEnoughStorageSpaceException;
	extern const char *_xvr2NotEnoughKernelMemoryException;
	extern const char *_xvr2MaximumNumberOfOpenFilesForThisProcessException;
	extern const char *_xvr2MaximumNumberOfOpenFilesForThisSystemException;
	extern const char *_xvr2FileException;
	extern const char *_xvr2FileNotOpenedException;
	extern const char *_xvr2FeatureNotAvailableOnPipesOrSocketException;
	extern const char *_xvr2InvalidParameterException;
	extern const char *_xvr2UserIDDoesNotMatchException;
	extern const char *_xvr2SecurityException;
	extern const char *_xvr2FileTooBigException;
#ifdef USE_DEBUG
	extern const char *_xvr2__xvr2_DebugOutput;
#endif
	extern const char *_xvr2WriteWillBlockException;
	extern const char *_xvr2InterruptedSystemCallException;
	extern const char *_xvr2Date;
	extern const char *_xvr2BaseFile;
	extern const char *_xvr2Unix;
	extern const char *_xvr2Time;
	extern const char *_xvr2Timestamp;
	extern const char *_xvr2Chronometer;
	extern const char *_xvr2TextOutput;
	extern const char *_xvr2StandardError;
	extern const char *_xvr2StandardOutput;
	extern const char *_xvr2TextInput;
	extern const char *_xvr2StandardInput;
	extern const char *_xvr2Memory;
	extern const char *_xvr2MemoryException;
	extern const char *_xvr2AllocationFailedException;
	extern const char *_xvr2ReallocFailedException;
	extern const char *_xvr2MathException;
	extern const char *_xvr2TemporalBuffer;
	extern const char *_xvr2GarbageCollector;
	extern const char *_xvr2List__nodeT;
	extern const char *_xvr2AutomatedGC;
	extern const char *_xvr2Group;
	extern const char *_xvr2BufferTooSmallException;
	extern const char *_xvr2GroupException;
	extern const char *_xvr2UserException;
	extern const char *_xvr2User;
	extern const char *_xvr2UserNotFoundException;
	extern const char *_xvr2GroupNotFoundException;
	extern const char *_xvr2Syslog;
	extern const char *_xvr2ConditionVar;
	extern const char *_xvr2ConditionVarWaitTimedOutException;
	extern const char *_xvr2Semaphore;
	extern const char *_xvr2SemaphoreException;
	extern const char *_xvr2SemaphoreInitValueException;
	extern const char *_xvr2SemaphoreUnableToDestroyException;
	extern const char *_xvr2SemaphoreUnableToDecreaseException;
	extern const char *_xvr2SemaphoreUnableToIncreaseException;
	extern const char *_xvr2Log;
	extern const char *_xvr2DBDriverInfo;
	extern const char *_xvr2FileNotFoundException;
	extern const char *_xvr2SQLDriver;
	extern const char *_xvr2SQLConnection;
	extern const char *_xvr2DatabaseException;
	extern const char *_xvr2DBServerUnreachableException;
	extern const char *_xvr2AlreadyConnected2DBException;
	extern const char *_xvr2DBConnectFirstException;
	extern const char *_xvr2ResultSet;
	extern const char *_xvr2SQLResultRow;
	extern const char *_xvr2SQLField;
	extern const char *_xvr2Byte;
	extern const char *_xvr2UndefinedClassException;
	extern const char *_xvr2StringException;
	extern const char *_xvr2ParseException;
	extern const char *_xvr2DateParseException;
	extern const char *_xvr2TimeParseException;
	extern const char *_xvr2BitParseException;
	extern const char *_xvr2ByteParseException;
	extern const char *_xvr2NoDataFetchException;
	extern const char *_xvr2NoMoreRowsException;
	extern const char *_xvr2DBConnectionFailedException;
	extern const char *_xvr2ServerDisconnectedException;
	extern const char *_xvr2SQLQueryException;
	extern const char *_xvr2SQLQueryRDBMSDisconnectedException;
	extern const char *_xvr2UnableToParseQueryException;
	extern const char *_xvr2TCPSocket;
	extern const char *_xvr2ConfigFile;
	extern const char *_xvr2__ParamAndVal;
	extern const char *_xvr2Console;
	extern const char *_xvr2TCPServer;
	extern const char *_xvr2TCPServerSession;
	extern const char *_xvr2IPAddress;
	extern const char *_xvr2HostNotFoundException;
	extern const char *_xvr2NSTryAgainException;
	extern const char *_xvr2NSFatalException;
	extern const char *_xvr2NoIPForYouException;
	extern const char *_xvr2ConnectionResetByPeerException;
	extern const char *_xvr2Connection;
	extern const char *_xvr2DBDriver;
	extern const char *_xvr2Field;
	
	
#endif
};
#endif
