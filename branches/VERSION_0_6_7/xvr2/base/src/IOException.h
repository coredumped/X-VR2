/*
 * $Id$
 */
#ifndef __XVR2_IO_EXCEPTION_H__
#define __XVR2_IO_EXCEPTION_H__
#include<Exception.h>


namespace xvr2 {
	namespace Exception{

		class Exception;

		/**
		 * This is a generic exception for I/O events
		 */
		class IO:public Exception{
			public:
				/**
				 * Default constructor
				 */
				IO();
		};

		/**
		 * This exception is thrown whenever the other end of communication has died
		 * or in the case of a socket when the remote host has closed connection without
		 * warning
		 */
		class BrokenPipe:public IO{
			public:
				/**
				 * Default constructor
				 */
				BrokenPipe();
		};

		/**
		 * This exception is thrown when the process is going out of files
		 */
		class ProcOutOfFileDescriptors:public IO{
			public:
				/**
				 * Default constructor
				 */
				ProcOutOfFileDescriptors();
		};

		/**
		 * This exception is thrown when the system is going out of files
		 */
		class SysOutOfFileDescriptors:public IO{
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
		class DeviceOrFIFONotFound:public IO{
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
		class DeviceNotFound:public IO{
			public:
				/**
				 * Default constructor
				 */
				DeviceNotFound();
		};

		/** This exception is thrown whenever a system call is interrupted by another */
		class InterruptedSystemCall:public IO{
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
		class SocketUnableToWrite:public IO{
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
		class SocketUnableToRead:public IO{
			public:
				/**
				 * Default constructor
				 */
				SocketUnableToRead();
		};

	};
};


#endif
