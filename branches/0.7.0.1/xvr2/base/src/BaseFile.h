/*
 * $Id$
 */
#ifndef __XVR2_FILE_H__
#define __XVR2_FILE_H__
#include<xvr2/System.h>
#include<xvr2/String.h>
#include<xvr2/SecurityException.h>
#include<xvr2/InvalidParameterException.h>
#include<xvr2/FileException.h>

namespace xvr2{

	/**
	 * \class BaseFile
	 * \brief This class implements the basic File I/O handling stuff, it is the base of
	 * every file-based UNIX subsystem.
	 * \note This class does not implement buffering
	 */
	class BaseFile:public System{
		protected:
			/** 
			 * \var int handler
			 * \brief Base file handler, this is just a reference pointer to the opened file in the OS */
			int handler;
			/** This will store the associated filename */
			String filename;
			/** This variable stores the current file opening mode */
			int filemode;
			/** This flag will say if the file is currently opened or not */
			bool _opened;
		public:
			/**
			 * To set permissions on a file please use an ORed
			 * combination of the following data
			 */
			enum chmodBits{
				/** Set user id on execution */
				SET_UID     = 04000,
				/** Set group id on execution */
				SET_GID     = 02000,
				/** Set the sticky bit */
				STICKY      = 01000,
				/** Owner can read */
				OWNER_READ  = 00400,
				/** Owner can write */
				OWNER_WRITE = 00200,
				/** Owner can execute, search */
				OWNER_EXEC  = 00100,
				/** Group can read */
				GROUP_READ  = 00040,
				/** Group can write */
				GROUP_WRITE = 00020,
				/** Group can execute, search */
				GROUP_EXEC  = 00010,
				/** Others can read */
				OTHER_READ  = 00004,
				/** Others can write */
				OTHER_WRITE = 00002,
				/** Others can execute, search */
				OTHER_EXEC  = 00001
			};
			/**
			 * Use this enum when u want to call the setOffset
			 * method
			 */
			enum OffsetStartingPoint{
				/** Move the offset from the begining of the file */
				FROM_THE_BEGINING,
				/** Move the offset from the file pointer's current position */
				FROM_CURRENT_POSITION,
				/** Move the offset backwards from the end of the file */
				FROM_THE_END
			};
			/**
			 * Use this enum to identify the type of the
			 * file to be open
			 */
			enum FileOpenMode{
				/** The file can only be read, 
				 *  secuentially */
				READ_ONLY,
				/** The file can only be write, 
				 *  secuentially */
				WRITE_ONLY,
				/** The file can be read-written,
				 *  be carefull if your writing data
				 *  to an already existing file*/
				READ_WRITE,
				/** The file is open for writing
				 *  at the end */
				APPEND
			};
			/** Default constructor initializes the filename
			 *  to /dev/null */
			BaseFile();
			/** This will initialize the filename to the 
			 *  specified by fname */
			BaseFile(const char *fname);
			BaseFile(const String &fname);
			virtual ~BaseFile(){
				filename.deleteString();
				close();
			}
			virtual void setFilename(const char *fname);
			virtual void setFilename(const String &fname);
			/** This method will open a file with the given 
			 *  openmode */
			virtual void open(FileOpenMode mode);
			/** This method will open a file with the given 
			 *  openmode and will set the filename to fname */
			virtual void open(const char *fname, FileOpenMode mode);
			/** This method will open a file with the given 
			 *  openmode and will set the filename to fname */
			virtual void open(const String &fname, FileOpenMode mode);
			/** This method will give you the offset for the file
			 *  pointer, is very usefull when you are dealing
			 *  with random files */
			virtual UInt32 getOffset();
			/** This method will set the offset for the file
			 *  pointer, is very usefull when you are dealing
			 *  with random files */
			virtual UInt32 setOffset(UInt32 off, OffsetStartingPoint from = BaseFile::FROM_THE_BEGINING);
			/** Calling this will close the currently opened file */
			virtual void close();
			/** This will write all content in the file 
			 *  buffers to the destination file */
			virtual void flush();
			/** Obtain the size of the current file it 
			 *  doesn't matter if the file is already 
			 *  opened or not */
			UInt32 getSize();
			/** Change the reading permission per file as in the chmod system call */
			int chmod(int perms);

			/** Sends the data buffer specified by <b>buffer</b> to the current file which has <b>size</b> bytes*/
			virtual UInt32 write(const void *buffer, UInt32 size);
			/** Sends the data buffer specified by <b>buffer</b> to the current file */
			virtual UInt32 write(const char *buffer);
			/** Retrieves <b>size</b> bytes from the data buffer specified by <b>buffer</b> from the current file */
			virtual UInt32 read(void *buffer, UInt32 size);
			/** Will tell you if the file is currently open */
			bool isOpen() const {
				return _opened;
			}

			const String &getFilename();
	};

};

#endif
