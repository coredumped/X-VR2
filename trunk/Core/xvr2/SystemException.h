/*
 * $Id$
 *
 * X-VR2 
 * 
 * Copyright (C) Juan V. Guerrero 2007
 * 
 * Juan V. Guerrero <mindstorm2600@users.sourceforge.net>
 * 
 * This program is free software, distributed under the terms of
 * the GNU General Public License Version 2. See the LICENSE file
 * at the top of the source tree.
 */
#ifndef __XVR2_SYSTEMEXCEPTION_H__
#define __XVR2_SYSTEMEXCEPTION_H__
#include<xvr2/DataTypes.h>
#include<xvr2/CoreExceptions.h>
#include<xvr2/String.h>

namespace xvr2 {
	/** \class SystemException SystemException.h <xvr2/SystemException.h>
	 *  General platform dependent exception which interfaces with host
	 *  OS C library error reporting facilities. */
	class SystemException : public Exception {
		private:
			/** Stores the current OS error code value. */
			OSErrorCodeT os_errno;
		protected:
		public:
			/** Default constructor, try not to use it.
			 *  \warning Basically this contructor tries to read the latest
			 *  error code returned by the host OS error reporting
			 *  mechanism, the reason why it is not wise to use 
			 *  this constructor is basically because in a multi-threaded
			 *  application each thread holds its own OS error code
			 *  variable, so if this exception is to be crossed between
			 *  threads you'll end up reporting the latest error code
			 *  on the receiving thread using its value there, which
			 *  of course, is not the same you'll be reporting from
			 *  the failed thread. */
			SystemException();
			/** This constructor properly initializes the exception based
			 *  on the error code you report after reading the last OS
			 *  reported error code.
			 *  @param error_code OS last return error code, in UNIX platforms
			 *  this should be the value of the errno global variable. */
			SystemException(OSErrorCodeT error_code);
			/** Copy contructor takes care of properly initlializing all 
			 *  internal variables by copying their values from the given 
			 *  source exception object.
			 *  \param se The source exception object from where we'll be
			 *  instatiating. */
			SystemException(const SystemException &se);
			/** Returns the error code's value at the time the exception
			 *  was thrown. */
			OSErrorCodeT osErrorCode();
			/** Returns an String describing a textual representation of the
			 *  error condition thrown. */
			String osErrorMessage();
			/** Deprecated method, please don't use.
			 *  \deprecated This method will be removed in X-VR2 version 0.8.3 */
			int code();
			/** Deprecated method, please don't use.
			 *  \deprecated This method will be removed in X-VR2 version 0.8.3 */
			virtual String message(); 
	};

	/** \class IOException CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  \brief This is a generic exception for I/O events.
	 *  This exception is thrown whenever a unexpected exception occurrs
	 *  dealing with the IO related classes. */
	class IOException:public SystemException{
		public:
			/** Default constructor */
			IOException();
			IOException(OSErrorCodeT error_code);
	};
	/** \class DSOException CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  \brief Use this exception whenever you want to throw a generic exception
	 *  over a dso (dynamic shared object) event. */
	class DSOException:public SystemException{
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
			FileException(OSErrorCodeT error_code);
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
};


#endif
