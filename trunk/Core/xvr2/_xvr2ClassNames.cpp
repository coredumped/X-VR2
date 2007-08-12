/*
 * $Id$
 */
#include<xvr2/xvr2config.h>
 
#if __GNUC__ < 3
namespace xvr2 {
 
	const char *_xvr2AllocationFailed = "xvr2::AllocationFailed";
	const char *_xvr2ArrayIndexOutOfLimits = "xvr2::ArrayIndexOutOfLimits";
	const char *_xvr2AutomatedGC = "xvr2::AutomatedGC";
	const char *_xvr2BackgroundFunction = "xvr2::BackgroundFunction";
	const char *_xvr2BaseFile = "xvr2::BaseFile";
	const char *_xvr2BasicStringBuffer = "xvr2::BasicStringBuffer";
	const char *_xvr2BitParseException = "xvr2::BitParseException";
	const char *_xvr2BrokenPipe = "xvr2::BrokenPipe";
	const char *_xvr2BufferTooSmall = "xvr2::BufferTooSmall";
	const char *_xvr2Byte = "xvr2::Byte";
	const char *_xvr2ByteParseException = "xvr2::ByteParseException";
	const char *_xvr2Calendar = "xvr2::Calendar";
	const char *_xvr2CantLoadDSO = "xvr2::CantLoadDSO";
	const char *_xvr2CantUnloadDSO = "xvr2::CantUnloadDSO";
	const char *_xvr2Chronograph = "xvr2::Chronograph";
	const char *_xvr2Chronometer = "xvr2::Chronometer";
	const char *_xvr2ConditionVar = "xvr2::ConditionVar";
	const char *_xvr2ConditionVarWaitTimedOut = "xvr2::ConditionVarWaitTimedOut";
	const char *_xvr2Console = "xvr2::Console";
	const char *_xvr2Date = "xvr2::Date";
	const char *_xvr2DateParseException = "xvr2::DateParseException";
	const char *_xvr2DeadLock = "xvr2::DeadLock";
	const char *_xvr2DebugConsole = "xvr2::DebugConsole";
	const char *_xvr2DetachedThread = "xvr2::DetachedThread";
	const char *_xvr2DeviceNotFound = "xvr2::DeviceNotFound";
	const char *_xvr2DeviceOrFIFONotFound = "xvr2::DeviceOrFIFONotFound";
	const char *_xvr2DSO = "xvr2::DSO";
	const char *_xvr2DSObjectFactory = "xvr2::DSObjectFactory";
	const char *_xvr2DSOException = "xvr2::DSOException";
	const char *_xvr2DSOSymbolException = "xvr2::DSOSymbolException";
	const char *_xvr2ElementNotFound = "xvr2::ElementNotFound";
	const char *_xvr2Exception = "xvr2::Exception";
	const char *_xvr2ExceptionTracer = "xvr2::ExceptionTracer";
	const char *_xvr2FeatureNotAvailableOnPipesOrSocket = "xvr2::FeatureNotAvailableOnPipesOrSocket";
	const char *_xvr2FileException = "xvr2::FileException";
	const char *_xvr2FileExists = "xvr2::FileExists";
	const char *_xvr2FilenameExceedsAddressSpace = "xvr2::FilenameExceedsAddressSpace";
	const char *_xvr2FilenameTooLong = "xvr2::FilenameTooLong";
	const char *_xvr2FileNotFound = "xvr2::FileNotFound";
	const char *_xvr2FileNotOpened = "xvr2::FileNotOpened";
	const char *_xvr2FileOrDirectoryNotFound = "xvr2::FileOrDirectoryNotFound";
	const char *_xvr2FileTooBig = "xvr2::FileTooBig";
	const char *_xvr2Function = "xvr2::Function";
	const char *_xvr2GarbageCollector = "xvr2::GarbageCollector";
	const char *_xvr2Group = "xvr2::Group";
	const char *_xvr2GroupException = "xvr2::GroupException";
	const char *_xvr2GroupNotFound = "xvr2::GroupNotFound";
	const char *_xvr2InterruptedSystemCall = "xvr2::InterruptedSystemCall";
	const char *_xvr2InvalidParameter = "xvr2::InvalidParameter";
	const char *_xvr2InvalidThread = "xvr2::InvalidThread";
	const char *_xvr2IOException = "xvr2::IOException";
	const char *_xvr2JoinableThread = "xvr2::JoinableThread";
	const char *_xvr2Log = "xvr2::Log";
	const char *_xvr2MaximumNumberOfOpenFilesForThisProcess = "xvr2::MaximumNumberOfOpenFilesForThisProcess";
	const char *_xvr2MaximumNumberOfOpenFilesForThisSystem = "xvr2::MaximumNumberOfOpenFilesForThisSystem";
	const char *_xvr2MaximumNumberOfRunningThreadsReached = "xvr2::MaximumNumberOfRunningThreadsReached";
	const char *_xvr2Memory = "xvr2::Memory";
	const char *_xvr2MemoryException = "xvr2::MemoryException";
	const char *_xvr2Mutex = "xvr2::Mutex";
	const char *_xvr2MutexException = "xvr2::MutexException";
	const char *_xvr2NoMoreTokens = "xvr2::NoMoreTokens";
	const char *_xvr2NotEnoughKernelMemory = "xvr2::NotEnoughKernelMemory";
	const char *_xvr2NotEnoughStorageSpace = "xvr2::NotEnoughStorageSpace";
	const char *_xvr2NullPointer = "xvr2::NullPointer";
	const char *_xvr2Number = "xvr2::Number";
	const char *_xvr2NumberException = "xvr2::NumberException";
	const char *_xvr2Object = "xvr2::Object";
	const char *_xvr2ParseException = "xvr2::ParseException";
	const char *_xvr2PermissionDenied = "xvr2::PermissionDenied";
	const char *_xvr2Plugin = "xvr2::Plugin";
	const char *_xvr2Process = "xvr2::Process";
	const char *_xvr2ProcOutOfFileDescriptors = "xvr2::ProcOutOfFileDescriptors";
	const char *_xvr2publicObject,publicstd = "xvr2::publicObject,publicstd";
	const char *_xvr2ReallocFailed = "xvr2::ReallocFailed";
	const char *_xvr2SecurityException = "xvr2::SecurityException";
	const char *_xvr2Semaphore = "xvr2::Semaphore";
	const char *_xvr2SemaphoreException = "xvr2::SemaphoreException";
	const char *_xvr2SemaphoreInitValueException = "xvr2::SemaphoreInitValueException";
	const char *_xvr2SemaphoreUnableToDecrease = "xvr2::SemaphoreUnableToDecrease";
	const char *_xvr2SemaphoreUnableToDestroy = "xvr2::SemaphoreUnableToDestroy";
	const char *_xvr2SemaphoreUnableToIncrease = "xvr2::SemaphoreUnableToIncrease";
	const char *_xvr2SharedVar = "xvr2::SharedVar";
	const char *_xvr2SocketUnableToRead = "xvr2::SocketUnableToRead";
	const char *_xvr2SocketUnableToWrite = "xvr2::SocketUnableToWrite";
	const char *_xvr2StandardError = "xvr2::StandardError";
	const char *_xvr2StandardInput = "xvr2::StandardInput";
	const char *_xvr2StandardOutput = "xvr2::StandardOutput";
	const char *_xvr2String = "xvr2::String";
	const char *_xvr2StringBuffer = "xvr2::StringBuffer";
	const char *_xvr2SumBase = "xvr2::SumBase";
	const char *_xvr2Syslog = "xvr2::Syslog";
	const char *_xvr2SysOutOfFileDescriptors = "xvr2::SysOutOfFileDescriptors";
	const char *_xvr2System = "xvr2::System";
	const char *_xvr2TemporalBuffer = "xvr2::TemporalBuffer";
	const char *_xvr2TextInput = "xvr2::TextInput";
	const char *_xvr2TextOutput = "xvr2::TextOutput";
	const char *_xvr2ThisIsADirectory = "xvr2::ThisIsADirectory";
	const char *_xvr2ThisIsNotADirectory = "xvr2::ThisIsNotADirectory";
	const char *_xvr2Thread = "xvr2::Thread";
	const char *_xvr2ThreadException = "xvr2::ThreadException";
	const char *_xvr2Threading = "xvr2::Threading";
	const char *_xvr2ThreadManager = "xvr2::ThreadManager";
	const char *_xvr2ThreadNotRunning = "xvr2::ThreadNotRunning";
	const char *_xvr2Time = "xvr2::Time";
	const char *_xvr2TimeParseException = "xvr2::TimeParseException";
	const char *_xvr2Timestamp = "xvr2::Timestamp";
	const char *_xvr2Tokenizer = "xvr2::Tokenizer";
	const char *_xvr2TooManySymlinks = "xvr2::TooManySymlinks";
	const char *_xvr2UnableToLockMutex = "xvr2::UnableToLockMutex";
	const char *_xvr2UnableToUnlockMutex = "xvr2::UnableToUnlockMutex";
	const char *_xvr2UnableToWriteOnReadOnlyFile = "xvr2::UnableToWriteOnReadOnlyFile";
	const char *_xvr2UnableToWriteOnRunningExecutableFile = "xvr2::UnableToWriteOnRunningExecutableFile";
	const char *_xvr2UndefinedClassException = "xvr2::UndefinedClassException";
	const char *_xvr2Unix = "xvr2::Unix";
	const char *_xvr2User = "xvr2::User";
	const char *_xvr2UserException = "xvr2::UserException";
	const char *_xvr2UserIDDoesNotMatch = "xvr2::UserIDDoesNotMatch";
	const char *_xvr2UserNotFound = "xvr2::UserNotFound";
	const char *_xvr2WriteWillBlock = "xvr2::WriteWillBlock";
 
};
#endif