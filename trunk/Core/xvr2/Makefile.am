## $Id$

h_sources = CoreExceptions.h BasicStringBuffer.h \
	BasicString.h Byte.h Calendar.h Chronograph.h Chronometer.h \
	ConditionVar.h Console.h DataTypes.h Date.h DebugConsole.h __Destruct.h \
	DSObject.h DSO.h DetachedThread.h JoinableThread.h\
	FileLogger.h Memory.h MessageStrings.h Mutex.h Object.h \
	Semaphore.h SharedVar.h StandardError.h StandardInput.h \
	StandardOutput.h StringBuffer.h String.h System.h \
	TextInput.h TextOutput.h Thread.h Threading.h \
	ThreadManager.h Time.h Timestamp.h Tokenizer.h TraceDumper.h \
	xvr2config.h Conversion.h Function.h \
	BackgroundFunction.h Buffer.h StreamInterface.h SystemException.h \
	StdioInterface.h StdioInputFile.h StdioOutputFile.h FinalizerCallback.h \
	RawInputStream.h RawOutputStream.h RawStreamInterface.h StreamException.h \
	BufferedTextInputStream.h InvalidParameterException.h \
	ThreadFinalizator.h FileException.h Vector.h PipelineFilter.h \
	Pipeline.h Queue.h HashMap.h Map.h Deque.h Logger.h

cc_sources = CoreExceptions.cpp BasicString.cpp \
	Byte.cpp Chronometer.cpp ConditionVar.cpp Console.cpp Date.cpp \
	DebugConsole.cpp DSObject.cpp DSO.cpp \
	FileLogger.cpp Memory.cpp DetachedThread.cpp JoinableThread.cpp \
	MessageStrings.cpp Mutex.cpp Object.cpp Semaphore.cpp StandardError.cpp \
	StandardInput.cpp StandardOutput.cpp StringBuffer.cpp String.cpp \
	System.cpp TextInput.cpp TextOutput.cpp \
	Thread.cpp Threading.cpp ThreadManager.cpp Time.cpp Timestamp.cpp \
	Tokenizer.cpp TraceDumper.cpp \
	Conversion.cpp Buffer.cpp StreamInterface.cpp SystemException.cpp \
	StdioInterface.cpp StdioInputFile.cpp StdioOutputFile.cpp \
	BackgroundFunction.cpp RawInputStream.cpp RawOutputStream.cpp \
	RawStreamInterface.cpp StreamException.cpp FinalizerCallback.cpp\
	BufferedTextInputStream.cpp InvalidParameterException.cpp \
	ThreadFinalizator.cpp FileException.cpp Function.cpp xvr2config.cpp \
	PipelineFilter.cpp Logger.cpp

library_includedir=$(includedir)/$(GENERIC_LIBRARY_NAME)
library_include_HEADERS = $(h_sources)

INCLUDES = -I$(top_srcdir)

lib_LTLIBRARIES=libxvr2core.la
libxvr2core_la_SOURCES= $(h_sources) $(cc_sources)
libxvr2core_la_LDFLAGS= -version-info $(GENERIC_LIBRARY_VERSION) -release $(GENERIC_RELEASE)

rebuild: clean all
