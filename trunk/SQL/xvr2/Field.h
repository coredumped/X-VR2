/*
 * $Id:Field.h 540 2007-08-20 07:51:56Z mindstorm2600 $
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
#ifndef __XVR2_SQL_FIELD_H__
#define __XVR2_SQL_FIELD_H__

#include<xvr2/xvr2config.h>
#include<xvr2/Date.h>
#include<xvr2/Time.h>
#include<xvr2/Timestamp.h>
#include<xvr2/Byte.h>
#include<xvr2/String.h>
#include<xvr2/CoreExceptions.h>
#include<xvr2/SQL/Driver.h>

namespace xvr2{
	namespace SQL {
		/**
		 * Multitype container for SQL single data.
		 * The purpose of Field is to provide a multitype container, because
		 * we need to translate the data that is coming from the ResultSet on a
		 * select statement we need to provide a way to ensure a safe translation of
		 * the data provided.
		 *
		 */
		class Field:public Object{
			private:
				void		*dataPtr;
				UInt32		dataLen;
				int		dataType;
				//Temporary char pointers for datatypes
				char		*tmpStrTINYINT;
				char		*tmpStrINTEGER;
				char		*tmpStrBIGINT;
				char		*tmpStrFLOAT;
				char		*tmpStrDOUBLE;
				char		*tmpStrBIT;
				char		*tmpStrBYTE;

				String		tmpString;
				/*String		tmpStringTINYINT;
				String		tmpStringINTEGER;
				String		tmpStringBIGINT;
				String		tmpStringFLOAT;
				String		tmpStringDOUBLE;
				String		tmpStringBIT;
				String		tmpStringBYTE;*/

				Date		*tmpDate;
				Time		*tmpTime;
				Timestamp	*tmpTimestamp;
				Byte		*tmpByte;
				bool		*tmpBool;
				Int16		*tmpInt16;
				Int32		*tmpInt32;
				Int64		*tmpInt64;
				float		*tmpFloat;
				double		*tmpDouble;
				String		colname;
			public:
				Driver *drv;
				/** This enumeration holds all SQL compatible datatypes,
				 *  this compatible datatypes must also coincide with
				 *  C/C++ and/or xvr2lib's previously defined datatypes */
				enum SQLtypes{
					/** Represents 2 byte integer, the same as Int16 */
					TINYINT   = 1, 
					/** This is a 4 byte integer, the same as Int32 */
					INTEGER   = 2,
					/** An 8 byte integer, this is a 64 bit number, the 
					 *  same as Int64 */
					BIGINT    = 3,
					/** The same as a C float datatype */
					FLOAT     = 4,
					/** The same as a C double */
					DOUBLE    = 5,
					/** An array of 1 byte characters, the same as the C 
					 *  char datatype */
					CHAR      = 6,
					/** A variable null-terminated array of CHARs, the 
					 *  same as a C char[]  */
					VARCHAR   = 7,
					/** The same as a varchar, but this is compatible 
					 *  with the xvr2lib's String class */
					STRING    = 8,
					/** This is a variable number of binary data, it 
					 *  could be text an image or anything else, be 
					 *  carefull with this datatype since you could
					 *  cause a segmentation fault if try to read or
					 *  write past the end of the allocated space for
					 *  the object stored in, it is the C equivalent
					 *  of a void pointer */
					BLOB      = 9,
					/** This is the same thing as a BLOB, but instead of
					 *  being a binary arrangement of data now it is an
					 *  understandable arrangement of characters. It is
					 *  equivalent to a String. */
					TEXT      = 10,
					/** This represents a date object and is also
					 *  equivalent to the Date class datatype */
					DATE      = 11,
					/** This represents a time object and is also
					 *  equivalent to the Time class datatype */
					TIME      = 12,
					/** This represents a timestamp it is the same as
					 *  the Timestamp class */
					TIMESTAMP = 13,
					/** This reprents a boolean datatype such as true
					 *  or false only, for us the is the equivalent to
					 *  the C++ bool datatype */
					BIT       = 14,
					/** This represents a binary 8 bit datatype */
					BYTE      = 15
				};
				/** Default constructor */
				Field();
				/** This will instatiate an SQLResultSet attempting
				 *  to guess the datatype based on the <b>size</b> in bytes,
				 *  <b>data</b> is pointer to the buffer containing the
				 *  the value returned in the current cell from the
				 *  selected row in the ResultSet */
				Field(const void *data, const UInt32 size);
				/** This constructor will instatiate a new object of this 
				 *  class followed by an specified <b>type</b>, <b>data</b>
				 *  pointer and a given pointer <b>size</b>. <b>type</b> must
				 *  be one of the above SQLtypes */
				Field(const int type, const void *data, const UInt32 size);
				/** This constructor will instatiate a new object of this 
				 *  class followed by an specified <b>type</b>, <b>data</b>
				 *  pointer and a given pointer <b>size</b>. <b>type</b> must
				 *  be one of the above SQLtypes */
				void init(const int type, const void *data, const UInt32 size);
				/*void init(const int type, const bool data, const UInt32 size);
				void init(const int type, const int data, const UInt32 size);
				void init(const int type, const int data, const UInt32 size);*/
				/** This destructor will release any used buffeasr and reset
				 *  all internal stored data */
				~Field();
				/** This will convert the data stored on this object to an
				 *  Int16 which is a signed integer of 16 bits (2 bytes)
				 *  length.
				 *  Be aware that if you try to convert the incorrect data
				 *  you may be having an overflow of your current storage
				 *  space, as an example imagine that the Field is
				 *  storing a 32 char VARCHAR, as an Int16 your limits are
				 *  set between -32768 and 32767 so even if the VARCHAR is
				 *  composed of numeric values you wont have enough space
				 *  to store the result translation, in this case the
				 *  BufferTooSmallException is thrown, be carefull with this
				 *  and try allways to convert the correct datatype. 
				 *  A NumberException is thrown only if the source datatype
				 *  is of the type VARCHAR, TEXT or STRING and one or more
				 *  of its characters is NOT a digit */
				Int16		toTinyInt() const;
				/** Is the same as toTinyInt but instead of returning a
				 *  signed quantity this method returns an unsigned one */
				UInt16		toUTinyInt() const;
				/** Returns the data as a 32 bit (4 bytes) signed integer.
				 *  If the data on this cell is coming from a TEXT or
				 *  VARCHAR column type then be prepared to receive the
				 *  NumberException exception if there is a non numeric
				 *  character contained in there.
				 *  Also the BufferTooSmallException may be thrown if the
				 *  number of digits is bigger than <b>10</b>.
				 */
				Int32		toInteger() const;
				/** Is the same as toInteger but instead of returning a
				 *  signed quantity this method returns an unsigned one */
				UInt32		toUInteger() const;
				/** Returns the data as a 64 bit (8 bytes) signed integer.
				 *  If the data on this cell is coming from a TEXT or
				 *  VARCHAR column type then be prepared to receive the
				 *  NumberException exception if there is a non numeric
				 *  character contained in there.
				 *  Also the BufferTooSmallException may be thrown if the
				 *  number of digits is bigger than <b>20</b>.
				 */
				Int64		toBigInt() const;
				/** Is the same as xvr2::ResultSet::toBigInt but instead
				 *  of returning a signed quantity this method returns an 
				 *  unsigned one */
				UInt64		toUBigInt() const;
				/** Returns the data as a 32 bit (4 bytes) floating number
				 *  conforming to the IEEE 754 standard.
				 *  If the data on this cell is coming from a TEXT or
				 *  VARCHAR column type then be prepared to receive the
				 *  NumberException exception if there is a non numeric
				 *  character different from <i>+ -</i> or <i>E</i>.
				 *  Also the BufferTooSmallException may be thrown if the
				 *  number of digits is bigger than <b>10</b> plus 3 for the
				 *  exponent and 2 more for signs.
				 */
				float		toFloat() const;
				/** Returns the data as a 64 bit (8 bytes) floating number
				 *  conforming to the IEEE 754 standard.
				 *  If the data on this cell is coming from a TEXT or
				 *  VARCHAR column type then be prepared to receive the
				 *  NumberException exception if there is a non numeric
				 *  character different from <i>+ -</i> or <i>E</i>.
				 *  Also the BufferTooSmallException may be thrown if the
				 *  number of digits is bigger than <b>20</b> plus 3 for the
				 *  exponent and 2 more for signs.
				 */
				double		toDouble() const;
				/** Returns the data as a null-terminated string of
				 *  char, <b>len</b> is the length of the string. */
				char	*toChar() const;
				/** Returns the data as a String if the data is numeric
				 *  then it will be translated also if it is a Date, Time
				 *  Byte, Bit or Timestamp */
				const String	&toString() const;
				/** Returns the data as a String if the data is numeric
				 *  then it will be translated also if it is a Date, Time
				 *  Byte, Bit or Timestamp */
				const String	&toText() const;
				/** This will return a void data pointer, please take special
				 *  care with BLOBs and try not to pass their addressing
				 *  limits, please use allways the size(); method in order
				 *  know the size of the current BLOB */
				const void	*toBLOB();
				/** This method will convert and return the data as a Date
				 *  pointer */
				const Date	*toDate();
				/** This method will convert and return the data as a Time
				 *  pointer */
				const Time	*toTime();
				/** This method will convert and return the data as a 
				 * Timestamp  pointer */
				Timestamp	toTimestamp();
				Timestamp	toTimestamp() const;
				/** This method will return 0 or 1, a boolean value according
				 *  to the stored data pointer */
				bool		toBit() const;
				/** This method will return 0 or 1, a boolean value according
				 *  to the stored data pointer */
				bool		toBool() const;
				/** With this method ou will get the first byte of the stored
				 *  data pointer */
				const Byte	*toByte();
				/** Returns a constant like SQLtypes describing the datatype
				 *  currently stored */
				const int	getDatatype();
				/** Returns a constant like SQLtypes describing the datatype
				 *  currently stored */
				const int	getDatatype() const;
				/** Returns the size in bytes of the currently stored 
				 *  object */
				const UInt32	size();
				/** Returns the size in bytes of the currently stored 
				 *  object */
				const UInt32	size() const;
				/** Returns the size in bytes of the currently stored 
				 *  object */
				const UInt32	dataSize();
				/** Returns the size in bytes of the currently stored 
				 *  object */
				const UInt32	dataSize() const;
				/** This will set the column name to <b>nam</b> */
				void setFieldName(const String &nam);
				/** This will be the name for this field as configured 
				 *  during the table creation */
				const String &getFieldName() const;
				bool isNull() const;
		};
	};
};

#endif
