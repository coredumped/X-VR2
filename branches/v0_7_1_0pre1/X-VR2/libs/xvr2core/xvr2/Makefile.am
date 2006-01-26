## Source directory

#SUBDIRS = parsers

h_sources = ArrayIndexOutOfLimitsException.h AutomatedGC.h BaseFile.h BasicStringBuffer.h \
	BasicString.h BufferTooSmall.h Byte.h Calendar.h Chronograph.h Chronometer.h \
	ConditionVar.h Console.h DataTypes.h Date.h DebugConsole.h __Destruct.h \
	DetachedThread.h DSObject.h DSOException.h DSO.h ElementNotFoundException.h \
	Exception.h FileException.h GarbageCollector.h GroupException.h Group.h \
	InvalidParameterException.h IOException.h JoinableThread.h Log.h \
	MemoryException.h Memory.h MessageStrings.h MutexException.h Mutex.h \
	NoMoreTokensException.h NullPointerException.h NumberException.h Object.h \
	ParseException.h Plugin.h Process.h SecurityException.h SemaphoreException.h \
	Semaphore.h SharedVar.h StandardError.h StandardInput.h StandardOutput.h \
	StringBuffer.h StringException.h String.h Syslog.h System.h TemporalBuffer.h \
	TextInput.h TextOutput.h ThreadException.h Thread.h Threading.h ThreadManager.h \
	Time.h Timestamp.h Tokenizer.h TraceDumper.h UndefinedClass.h Unix.h UserException.h \
	User.h _xvr2ClassNames.h xvr2config.h

cc_sources = ArrayIndexOutOfLimitsException.cpp AutomatedGC.cpp BaseFile.cpp BasicString.cpp BufferTooSmall.cpp \
	Byte.cpp Chronometer.cpp ConditionVar.cpp Console.cpp Date.cpp DebugConsole.cpp \
	DetachedThread.cpp DSObject.cpp DSO.cpp DSOException.cpp ElementNotFoundException.cpp Exception.cpp \
	FileException.cpp GarbageCollector.cpp Group.cpp GroupException.cpp InvalidParameterException.cpp \
	IOException.cpp JoinableThread.cpp Log.cpp Memory.cpp MemoryException.cpp \
	MessageStrings.cpp Mutex.cpp MutexException.cpp NoMoreTokensException.cpp NullPointerException.cpp \
	NumberException.cpp Object.cpp ParseException.cpp Plugin.cpp SecurityException.cpp Semaphore.cpp \
	SemaphoreException.cpp StandardError.cpp StandardInput.cpp StandardOutput.cpp StringBuffer.cpp \
	String.cpp StringException.cpp Syslog.cpp System.cpp TemporalBuffer.cpp TextInput.cpp TextOutput.cpp \
	Thread.cpp ThreadException.cpp Threading.cpp ThreadManager.cpp Time.cpp Timestamp.cpp Tokenizer.cpp \
	TraceDumper.cpp UndefinedClass.cpp Unix.cpp User.cpp UserException.cpp _xvr2ClassNames.cpp

library_includedir=$(includedir)/$(GENERIC_LIBRARY_NAME)
library_include_HEADERS = $(h_sources)

INCLUDES = -I$(top_srcdir)

lib_LTLIBRARIES=libxvr2core-0.7.1.0.la
libxvr2core_0_7_1_0_la_SOURCES= $(h_sources) $(cc_sources)
libxvr2core_0_7_1_0_la_LDFLAGS= -version-info $(GENERIC_LIBRARY_VERSION) -release $(GENERIC_RELEASE)

