/*
 * Multitype container for SQL single data
 *
 * $Id$
 */
#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE
#endif
#include<time.h>
#include<ctype.h>
#include<unistd.h>
#include<xvr2/DBField.h>
#include<xvr2/NumberException.h>
#include<xvr2/NullPointerException.h>
#include<xvr2/Memory.h>
#ifndef USING_GCC3
#define __USE_SVID
#include<errno.h>
#include<stdlib.h>
#include<stdio.h>
#endif
#ifdef GCC_REVISION4
#include<cerrno>
#endif

namespace xvr2{

	namespace DB {

		// Start definition of local variables
		// End definition of local variables
	
		// Start definition of local functions
		// End definition of local functions
	
		//Start implementation of class: Field
	
		Field::Field(const void *data, const UInt32 size){
#ifndef USING_GCC3
			setClassName(xvr2::_xvr2Field);
#endif
			tmpStr = 0;
			tmpString = 0;
			tmpDate = 0;
			tmpTime = 0;
			tmpTimestamp = 0;
			tmpByte = 0;
			tmpBool = 0;
			tmpInt16 = 0;
			tmpInt32 = 0;
			tmpInt64 = 0;
			tmpFloat = 0;
			tmpDouble = 0;
			dataPtr = (void *)data;
			dataLen = size;
			switch(size){
				case 1:
					dataType = BYTE;
					break;
				case 2:
					dataType = TINYINT;
					break;
				case 4:
					dataType = INTEGER;
					break;
				case 8:
					dataType = BIGINT;
					break;
				default:
					dataType = VARCHAR;
			}
		}
	
		Field::Field(){;}
	
		Field::Field(const int type, const void *data, const UInt32 size){
			init(type, data, size);
		}
	
		void Field::init(const int type, const void *data, const UInt32 size){
#ifndef USING_GCC3
			setClassName(xvr2::_xvr2Field);
#endif
			tmpStr = 0;
			tmpString = 0;
			tmpDate = 0;
			tmpTime = 0;
			tmpTimestamp = 0;
			tmpBool = 0;
			tmpInt16 = 0;
			tmpInt32 = 0;
			tmpInt64 = 0;
			tmpFloat = 0;
			tmpDouble = 0;
			dataLen = size;
			dataType = type;
			if(data == 0){
				dataPtr = 0;
				return;
			}
			switch(dataType){
				case BIT:
					tmpBool = new bool();
					*tmpBool = *((bool *)data);
					dataPtr = (void *)tmpBool;
					break;
				case TINYINT:
					tmpInt16 = new Int16();
					*tmpInt16 = *((Int16 *)data);
					dataPtr = (void *)tmpInt16;
					break;
				case INTEGER:
					tmpInt32 = new Int32();
					*tmpInt32 = *((Int32 *)data);
					dataPtr = (void *)tmpInt32;
					break;
				case BIGINT:
					tmpInt64 = new Int64();
					*tmpInt64 = *((Int64 *)data);
					dataPtr = (void *)tmpInt64;
					break;
				case FLOAT:
					tmpFloat = new float();
					*tmpFloat = *((float *)data);
					dataPtr = (void *)tmpFloat;
					break;
				case DOUBLE:
					tmpDouble = new double();
					*tmpDouble = *((double *)data);
					dataPtr = (void *)tmpDouble;
					break;
				case DATE:
					tmpDate = new Date((Date *)data);
					dataPtr = (void *)tmpDate;
					break;
				case TIME:
					tmpTime = new Time((Time *)data);
					dataPtr = (void *)tmpTime;
					break;
				case TIMESTAMP:
					tmpTimestamp = new Timestamp((Timestamp *)data);
					dataPtr = (void *)tmpTimestamp;
					break;
				default:
					dataPtr = (void *)data;
			};		
		}
	
		Field::~Field(){
			void *ttmp;
			//Destroy datacell completely
			dataPtr = 0;
			dataLen = 0;
			dataType = 0;
			if(tmpStr != 0){
				ttmp = tmpStr;
				Memory::freeBuffer(&ttmp);
			}
			if(tmpString != 0)
				xvr2_delete(tmpString);
			if(tmpDate != 0)
				xvr2_delete(tmpDate);
			if(tmpTime != 0)
				xvr2_delete(tmpTime);
			if(tmpTimestamp != 0)
				xvr2_delete(tmpTimestamp);
			if(tmpBool != 0)
				xvr2_delete(tmpBool);
			if(tmpInt16 != 0)
				xvr2_delete(tmpInt16);
			if(tmpInt32 != 0)
				xvr2_delete(tmpInt32);
			if(tmpInt64 != 0)
				xvr2_delete(tmpInt64);
			if(tmpFloat != 0)
				xvr2_delete(tmpFloat);
			if(tmpDouble != 0)
				xvr2_delete(tmpDouble);
		}
	
		Int16 Field::toTinyInt(){
			Int16 val = 0;
			Time   *t = 0;
			String str;
			if(isNull())
				return 0;
			switch(dataType){
				case  TINYINT:
				case  INTEGER:
				case  BIGINT:
				case  FLOAT:
				case  DOUBLE:
				case  BLOB:
					Memory::copy(&val, dataPtr, sizeof(Int16));
					break;
				case  BIT:
					Memory::copy(&val, dataPtr, sizeof(bool));
					break;
				case  BYTE:
					val = ((xvr2::Byte *)dataPtr)->theByte();
					break;
				case  DATE:
					throw Exception::BufferTooSmall();
					break;
				case  TIME:
					t = (xvr2::Time *)dataPtr;
					val = t->Hour() * 10000 + t->Minute() * 100 + t->Second();
					break;
				case  TIMESTAMP:
					throw Exception::BufferTooSmall();
					break;
				case  CHAR:
					Memory::copy(&val, dataPtr, sizeof(char));
					break;
				case  VARCHAR:
					if(dataLen < 1)
						throw Exception::BufferTooSmall();
					str = (char *)dataPtr;
					val = str.toInt();
					break;
				//By default if everyone of the option fails convert
				//the data to a String
				case  TEXT:
				case  STRING:
				default:
					if(dataLen < 1)
						throw Exception::BufferTooSmall();
					else{
						try{
							val = (Int16)((String *)dataPtr)->toInt();
						}
						catch(...){
							throw Exception::UndefinedClass();
						}
					}
			}
			return val;
		}
	
		UInt16 Field::toUTinyInt(){
			return (UInt16)toTinyInt();
		}
	
		Int32 Field::toInteger(){
			Int32 val = 0;
			Time   *t;
			Date   *d = 0;
			Timestamp *tm = 0;
			String str;
			if(isNull())
				return 0;
			switch(dataType){
				case  TINYINT:
				case  INTEGER:
				case  BIGINT:
				case  FLOAT:
				case  DOUBLE:
				case  BLOB:
					Memory::copy(&val, dataPtr, sizeof(Int32));
					break;
				case  BIT:
					Memory::copy(&val, dataPtr, sizeof(bool));
					break;
				case  BYTE:
					val = ((xvr2::Byte *)dataPtr)->theByte();
					break;
				case  DATE:
					d = (xvr2::Date *)dataPtr;
					val = d->dayofmonth * 1000000 + d->month * 10000 + d->year;
					break;
				case  TIME:
					t = (xvr2::Time *)dataPtr;
					val = t->Hour() * 10000 + t->Minute() * 100 + t->Second();
					break;
				case  TIMESTAMP:
					tm = (xvr2::Timestamp *)dataPtr;
					val = (Int32)tm->timestamp();
					break;
				case  CHAR:
					Memory::copy(&val, dataPtr, sizeof(char));
					break;
				case  VARCHAR:
					if(dataLen < 1)
						throw Exception::BufferTooSmall();
					str = (char *)dataPtr;
					val = str.toInt();
					break;
				//By default if everyone of the option fails convert
				//the data to a String
				case  TEXT:
				case  STRING:
				default:
					if(dataLen < 1)
						throw Exception::BufferTooSmall();
					else{
						try{
							val = (Int32)((String *)dataPtr)->toInt();
						}
						catch(...){
							throw Exception::UndefinedClass();
						}
					}
			}
			return val;
		}
	
		UInt32 Field::toUInteger(){
			return (UInt32)toInteger();
		}
	
		Int64 Field::toBigInt(){
			Int64 val = 0;
			Time   *t;
			Date   *d = 0;
			Timestamp *tm = 0;
			String str;
			if(isNull())
				return 0;
			switch(dataType){
				case  TINYINT:
				case  INTEGER:
				case  BIGINT:
				case  FLOAT:
				case  DOUBLE:
				case  BLOB:
					Memory::copy(&val, dataPtr, sizeof(Int64));
					break;
				case  BIT:
					Memory::copy(&val, dataPtr, sizeof(bool));
					break;
				case  BYTE:
					val = ((xvr2::Byte *)dataPtr)->theByte();
					break;
				case  DATE:
					d = (xvr2::Date *)dataPtr;
					val = d->dayofmonth * 1000000 + d->month * 10000 + d->year;
					break;
				case  TIME:
					t = (xvr2::Time *)dataPtr;
					val = t->Hour() * 10000 + t->Minute() * 100 + t->Second();
					break;
				case  TIMESTAMP:
					tm = (xvr2::Timestamp *)dataPtr;
					val = (Int32)tm->timestamp();
					break;
				case  CHAR:
					Memory::copy(&val, dataPtr, sizeof(char));
					break;
				case  VARCHAR:
					if(dataLen < 1)
						throw Exception::BufferTooSmall();
					str = (char *)dataPtr;
					val = str.toInt64();
					break;
				//By default if everyone of the option fails convert
				//the data to a String
				case  TEXT:
				case  STRING:
				default:
					if(dataLen < 1)
						throw Exception::BufferTooSmall();
					else{
						try{
							val = (Int64)((String *)dataPtr)->toInt64();
						}
						catch(...){
							throw Exception::UndefinedClass();
						}
					}
			}
			return val;
		}
	
		UInt64 Field::toUBigInt(){
			return (UInt64)toBigInt();
		}
	
		float Field::toFloat(){
			float val = 0;
			Time   *t;
			Date   *d = 0;
			Timestamp *tm = 0;
			String str;
			if(isNull())
				return 0;
			switch(dataType){
				case  TINYINT:
				case  INTEGER:
				case  BIGINT:
				case  FLOAT:
				case  DOUBLE:
				case  BLOB:
					Memory::copy(&val, dataPtr, sizeof(float));
					break;
				case  BIT:
					val = *((bool *)dataPtr);
					break;
				case  BYTE:
					val = ((xvr2::Byte *)dataPtr)->theByte();
					break;
				case  DATE:
					d = (xvr2::Date *)dataPtr;
					val = d->dayofmonth * 1000000 + d->month * 10000 + d->year;
					break;
				case  TIME:
					t = (xvr2::Time *)dataPtr;
					val = t->Hour() * 10000 + t->Minute() * 100 + t->Second();
					break;
				case  TIMESTAMP:
					tm = (xvr2::Timestamp *)dataPtr;
					val = (float)tm->timestamp();
					break;
				case  CHAR:
					Memory::copy(&val, dataPtr, sizeof(char));
					break;
				case  VARCHAR:
					if(dataLen < 1)
						throw Exception::BufferTooSmall();
					str = (char *)dataPtr;
					val = str.toFloat();
					break;
				//By default if everyone of the option fails convert
				//the data to a String
				case  TEXT:
				case  STRING:
				default:
					if(dataLen < 1)
						throw Exception::BufferTooSmall();
					else{
						try{
							val = (float)((String *)dataPtr)->toFloat();
						}
						catch(...){
							throw Exception::UndefinedClass();
						}
					}
			}
			return val;
		}
	
		double Field::toDouble(){
			double val = 0;
			Time   *t;
			Date   *d = 0;
			Timestamp *tm = 0;
			String str;
			if(isNull())
				return 0;
			switch(dataType){
				case  TINYINT:
				case  INTEGER:
				case  BIGINT:
				case  FLOAT:
				case  DOUBLE:
				case  BLOB:
					Memory::copy(&val, dataPtr, sizeof(double));
					break;
				case  BIT:
					val = *((bool *)dataPtr);
					break;
				case  BYTE:
					val = ((xvr2::Byte *)dataPtr)->theByte();
					break;
				case  DATE:
					d = (xvr2::Date *)dataPtr;
					val = d->dayofmonth * 1000000 + d->month * 10000 + d->year;
					break;
				case  TIME:
					t = (xvr2::Time *)dataPtr;
					val = t->Hour() * 10000 + t->Minute() * 100 + t->Second();
					break;
				case  TIMESTAMP:
					tm = (xvr2::Timestamp *)dataPtr;
					val = (double)tm->timestamp();
					break;
				case  CHAR:
					Memory::copy(&val, dataPtr, sizeof(char));
					break;
				case  VARCHAR:
					if(dataLen < 1)
						throw Exception::BufferTooSmall();
					str = (char *)dataPtr;
					val = str.toDouble();
					break;
				//By default if everyone of the option fails convert
				//the data to a String
				case  TEXT:
				case  STRING:
				default:
					if(dataLen < 1)
						throw Exception::BufferTooSmall();
					else{
						try{
							val = (double)((String *)dataPtr)->toDouble();
						}
						catch(...){
							throw Exception::UndefinedClass();
						}
					}
			}
			return val;
		}
	
		const char *Field::toChar(){
			char *ret;
			void *ttmp;
			if(isNull())
				return 0;
			switch(dataType){
				case  TINYINT:
					Int16 n1;
					n1 = *((Int16 *)dataPtr);
					if(tmpStr != 0){
						ttmp = (void *)tmpStr;
						Memory::freeBuffer(&ttmp);
					}
					tmpStr = (char *)Memory::allocBuffer(20);
					sprintf(tmpStr, "%d", n1);
					ret = tmpStr;
					break;
				case  INTEGER:
					Int32 n2;
					n2 = *((Int32 *)dataPtr);
					if(tmpStr != 0){
						ttmp = (void *)tmpStr;
						Memory::freeBuffer(&ttmp);
					}
					tmpStr = (char *)Memory::allocBuffer(40);
					sprintf(tmpStr, "%d", n2);
					ret = tmpStr;
					break;
				case  BIGINT:
					Int64 n3;
					n3 = *((Int64 *)dataPtr);
					if(tmpStr != 0){
						ttmp = (void *)tmpStr;
						Memory::freeBuffer(&ttmp);
					}
					tmpStr = (char *)Memory::allocBuffer(64);
					sprintf(tmpStr, "%lld", n3);
					ret = tmpStr;
					break;
				case  FLOAT:
					float n4;
					n4 = *((float *)dataPtr);
					if(tmpStr != 0){
						ttmp = (void *)tmpStr;
						Memory::freeBuffer(&ttmp);
					}
					tmpStr = (char *)Memory::allocBuffer(32);
#if ( defined USING_LINUX || defined SOLARIS )
					if(gcvt(n4, 8, tmpStr) != tmpStr){
						throw Exception::Number();
					}
#else
					if(sprintf(tmpStr, "%f", n4) != 1){
						throw Exception::Number();
					}
#endif
					ret = tmpStr;
					break;
				case  DOUBLE:
					double n5;
					n5 = *((double *)dataPtr);
					if(tmpStr != 0){
						ttmp = (void *)tmpStr;
						Memory::freeBuffer(&ttmp);
					}
					tmpStr = (char *)Memory::allocBuffer(128);
#if ( defined USING_LINUX || defined SOLARIS )
					if(gcvt(n5, 8, tmpStr) != tmpStr){
						throw Exception::Number();
					}
#else
					if(sprintf(tmpStr, "%f", n5) != 1){
						throw Exception::Number();
					}
#endif
					ret = tmpStr;
					break;
				case  CHAR:
				case  VARCHAR:
					ret = (char *)dataPtr;
					break;
				case  STRING:
				case  TEXT:
					try{
						ret = (char *)((String *)dataPtr)->toCharPtr();
					}
					catch(...){
						throw Exception::UndefinedClass();
					}
					break;
				case  BLOB:
					throw Exception::Stringe();
					break;
				case  DATE:
					try{
						//#################################
						//#  I need a better way to implement
						//#  this, please HELP!!!!!!!!!
						//#################################
						ret = ((Date *)dataPtr)->toString()->toCharPtr();
					}
					catch(...){
						throw Exception::UndefinedClass();
					}
					break;
				case  TIME:
					try{
						//#################################
						//#  I need a better way to implement
						//#  this, please HELP!!!!!!!!!
						//#################################
						ret = ((Time *)dataPtr)->toString()->toCharPtr();
					}
					catch(...){
						throw Exception::UndefinedClass();
					}
					break;
				case  TIMESTAMP:
					try{
						//#################################
						//#  I need a better way to implement
						//#  this, please HELP!!!!!!!!!
						//#################################
						ret = ((Timestamp *)dataPtr)->toString()->toCharPtr();
					}
					catch(...){
						throw Exception::UndefinedClass();
					}
					break;
				case  BIT:
					if(tmpStr != 0){
						ttmp = (void *)tmpStr;
						Memory::freeBuffer(&ttmp);
					}
					tmpStr = (char *)Memory::allocBuffer(2);
					tmpStr[1] = 0;
					if(*((bool *)dataPtr)){
						tmpStr[0] = '1';
					}
					else{
						tmpStr[0] = '0';
					}
					ret = tmpStr;
					break;
				case  BYTE:
					if(tmpStr == 0){
						ttmp = (void *)tmpStr;
						Memory::freeBuffer(&ttmp);
					}
					tmpStr = (char *)Memory::allocBuffer(7);
					if(sprintf(tmpStr, "0x%x", *((int *)dataPtr)) != 1)
						throw Exception::Number();
					ret = tmpStr;
					break;
			}
			return ret;
		}
	
	
		const String *Field::toString(){
			String *ret;
			void *ttmp;
			if(isNull())
				return 0;
			switch(dataType){
				case  TINYINT:
					Int16 n1;
					n1 = *((Int16 *)dataPtr);
					if(tmpString != 0){
						xvr2_delete(tmpString);
					}
					tmpString = new String(n1);
					ret = tmpString;
					break;
				case  INTEGER:
					Int32 n2;
					n2 = *((Int32 *)dataPtr);
					if(tmpString != 0){
						xvr2_delete(tmpString);
					}
					tmpString = new String(n2);
					ret = tmpString;
					break;
				case  BIGINT:
					Int64 n3;
					n3 = *((Int64 *)dataPtr);
					if(tmpString != 0){
						xvr2_delete(tmpString);
					}
					tmpString = new String(n3);
					ret = tmpString;
					break;
				case  FLOAT:
					float n4;
					n4 = *((float *)dataPtr);
					if(tmpString != 0){
						xvr2_delete(tmpString);
					}
					tmpString = new String(n4);
					ret = tmpString;
					break;
				case  DOUBLE:
					double n5;
					n5 = *((double *)dataPtr);
					if(tmpString != 0){
						xvr2_delete(tmpString);
					}
					tmpString = new String(n5);
					ret = tmpString;
					break;
				case  CHAR:
				case  VARCHAR:
					if(tmpString != 0){
						xvr2_delete(tmpString);
					}
					tmpString = new String((char *)dataPtr);
					ret = tmpString;
					break;
				case  STRING:
				case  TEXT:
					try{
						ret = ((String *)dataPtr);
					}
					catch(...){
						throw Exception::UndefinedClass();
					}
					break;
				case  BLOB:
					throw Exception::Stringe();
					break;
				case  DATE:
					try{
						//#################################
						//#  I need a better way to implement
						//#  this, please HELP!!!!!!!!!
						//#################################
						ret = ((String *)(((Date *)dataPtr)->toString()));
					}
					catch(...){
						throw Exception::UndefinedClass();
					}
					break;
				case  TIME:
					try{
						//#################################
						//#  I need a better way to implement
						//#  this, please HELP!!!!!!!!!
						//#################################
						ret = ((String *)(((Time *)dataPtr)->toString()));
					}
					catch(...){
						throw Exception::UndefinedClass();
					}
					break;
				case  TIMESTAMP:
					try{
						//#################################
						//#  I need a better way to implement
						//#  this, please HELP!!!!!!!!!
						//#################################
						ret = ((String *)(((Timestamp *)dataPtr)->toString()));
					}
					catch(...){
						throw Exception::UndefinedClass();
					}
					break;
				case  BIT:
					if(tmpString != 0){
						xvr2_delete(tmpString);
					}
					if(*((bool *)dataPtr)){
						tmpString = new String("1");
					}
					else{
						tmpString = new String("0");
					}
					ret = tmpString;
					break;
				case  BYTE:
					if(tmpStr == 0){
						ttmp = (void *)tmpStr;
						Memory::freeBuffer(&ttmp);
					}
					tmpStr = (char *)Memory::allocBuffer(7);
					if(sprintf(tmpStr, "0x%x", *((int *)dataPtr)) != 1)
						throw Exception::Number();
					ret = tmpString;
					break;
			}
			return ret;
		}
	
	
		const String *Field::toText(){
			return this->toString();
		}
	
		const Date *Field::toDate(){
			Date *ret = 0;
			struct tm tt;
			if(isNull())
				return 0;
			switch(dataType){
				case  TINYINT:
					throw Exception::DateParse();
					break;
				case  INTEGER:
				case  BIGINT:
					UInt32 n1;
					n1 = *((UInt32 *)dataPtr);
					if(tmpDate != 0)
						xvr2_delete(tmpDate);
					tmpDate = new Date(n1);
					ret = tmpDate;
					break;
				case  FLOAT:
					throw Exception::DateParse();
					break;
				case  DOUBLE:
					throw Exception::DateParse();
					break;
				case  CHAR:
				case  VARCHAR:
					if(strptime((char *)dataPtr, "%Y-%m-%d %H:%M:%S", &tt) != 0){
						throw Exception::DateParse();
					}
					else{
						if(strptime((char *)dataPtr, "%d-%m-%Y %H:%M:%S", &tt) != 0){
							throw Exception::DateParse();
						}
						else{
							if(strptime((char *)dataPtr, "%D", &tt) != 0){
								throw Exception::DateParse();
							}
							else{
								if(strptime((char *)dataPtr, "%a %b %d %H:%M:%S %Z %Y", &tt) != 0){
									throw Exception::DateParse();
								}
								else{
									if(strptime((char *)dataPtr, "%x", &tt) != 0){
										throw Exception::DateParse();
									}
								}
							}
						}
					}
					if(tmpDate != 0)
						xvr2_delete(tmpDate);
					tmpDate = new Date(tt.tm_year, tt.tm_mon, tt.tm_wday, tt.tm_mday, tt.tm_hour, tt.tm_min, tt.tm_sec);
					ret = tmpDate;
					break;
				case  STRING:
				case  TEXT:
					char *dataStr;
					try{
						dataStr = (char *)(((String *)dataPtr)->toCharPtr());
					}
					catch(...){
						throw Exception::UndefinedClass();
					}
					if(strptime((char *)dataStr, "%Y-%m-%d %H:%M:%S", &tt) != 0){
						throw Exception::DateParse();
					}
					else{
						if(strptime((char *)dataStr, "%d-%m-%Y %H:%M:%S", &tt) != 0){
							throw Exception::DateParse();
						}
						else{
							if(strptime((char *)dataStr, "%D", &tt) != 0){
								throw Exception::DateParse();
							}
							else{
								if(strptime((char *)dataStr, "%a %b %d %H:%M:%S %Z %Y", &tt) != 0){
									throw Exception::DateParse();
								}
								else{
									if(strptime((char *)dataStr, "%x", &tt) != 0){
										throw Exception::DateParse();
									}
								}
							}
						}
					}
					if(tmpDate != 0)
						xvr2_delete(tmpDate);
					tmpDate = new Date(tt.tm_year, tt.tm_mon, tt.tm_wday, tt.tm_mday, tt.tm_hour, tt.tm_min, tt.tm_sec);
					ret = tmpDate;
					break;
				case  BLOB:
					throw Exception::DateParse();
					break;
				case  DATE:
					ret = (Date *)dataPtr;
					break;
				case  TIME:
					if(tmpDate != 0)
						delete tmpDate;
					tt.tm_year = 0;
					tt.tm_mon = 0;
					tt.tm_wday = 0;
					tt.tm_mday = 0;
					tt.tm_hour = ((Time *)dataPtr)->Hour();
					tt.tm_min = ((Time *)dataPtr)->Minute();
					tt.tm_sec = ((Time *)dataPtr)->Second();
					tmpDate = new Date(tt.tm_year, tt.tm_mon, tt.tm_wday, tt.tm_mday, tt.tm_hour, tt.tm_min, tt.tm_sec);
					ret = tmpDate;
					break;
				case  TIMESTAMP:
					if(tmpDate != 0)
						xvr2_delete(tmpDate);
					tmpDate = new Date(((Timestamp *)dataPtr)->timestamp());
					ret = tmpDate;
					break;
				case  BIT:
					throw Exception::DateParse();
					break;
				case  BYTE:
					throw Exception::DateParse();
					break;
			}
			return ret;
		}
	
		const Time *Field::toTime(){
			Time *ret = 0;
			struct tm tt;
			if(isNull())
				return 0;
			switch(dataType){
				case  TINYINT:
					throw Exception::DateParse();
					break;
				case  INTEGER:
				case  BIGINT:
					UInt32 n1;
					n1 = *((UInt32 *)dataPtr);
					if(tmpDate != 0)
						xvr2_delete(tmpDate);
					tmpTime = new Time(n1);
					ret = tmpTime;
					break;
				case  FLOAT:
					throw Exception::DateParse();
					break;
				case  DOUBLE:
					throw Exception::DateParse();
					break;
				case  CHAR:
				case  VARCHAR:
					if(strptime((char *)dataPtr, "%Y-%m-%d %H:%M:%S", &tt) != 0){
						throw Exception::DateParse();
					}
					else{
						if(strptime((char *)dataPtr, "%d-%m-%Y %H:%M:%S", &tt) != 0){
							throw Exception::DateParse();
						}
						else{
							if(strptime((char *)dataPtr, "%D", &tt) != 0){
								throw Exception::DateParse();
							}
							else{
								if(strptime((char *)dataPtr, "%a %b %d %H:%M:%S %Z %Y", &tt) != 0){
									throw Exception::DateParse();
								}
								else{
									if(strptime((char *)dataPtr, "%x", &tt) != 0){
										throw Exception::DateParse();
									}
								}
							}
						}
					}
					if(tmpTime != 0)
						xvr2_delete(tmpTime);
					tmpTime = new Time(tt.tm_hour, tt.tm_min, tt.tm_sec);
					ret = tmpTime;
					break;
				case  STRING:
				case  TEXT:
					char *dataStr;
					try{
						dataStr = (char *)(((String *)dataPtr)->toCharPtr());
					}
					catch(...){
						throw Exception::UndefinedClass();
					}
					if(strptime((char *)dataStr, "%H:%M:%S", &tt) != 0){
						throw Exception::DateParse();
					}
					else{
						if(strptime((char *)dataStr, "%H:%M", &tt) != 0){
							throw Exception::DateParse();
						}
					}
					if(tmpTime != 0)
						xvr2_delete(tmpTime);
					tmpTime = new Time(tt.tm_hour, tt.tm_min, tt.tm_sec);
					ret = tmpTime;
					break;
				case  BLOB:
					throw Exception::DateParse();
					break;
				case  DATE:
					if(tmpTime != 0)
						delete tmpTime;
					tt.tm_hour = ((Date *)dataPtr)->hour;
					tt.tm_min = ((Date *)dataPtr)->minute;
					tt.tm_sec = ((Date *)dataPtr)->second;
					tmpTime = new Time(tt.tm_hour, tt.tm_min, tt.tm_sec);
					ret = tmpTime;
					break;
				case  TIME:
					ret = (Time *)dataPtr;
					break;
				case  TIMESTAMP:
					if(tmpTime != 0)
						xvr2_delete(tmpTime);
					tmpTime = new Time(((Timestamp *)dataPtr)->timestamp());
					ret = tmpTime;
					break;
				case  BIT:
					throw Exception::DateParse();
					break;
				case  BYTE:
					throw Exception::DateParse();
					break;
			}
			return ret;
		}
	
	
		const Timestamp *Field::toTimestamp(){
			Timestamp *ret = 0;
			if(isNull())
				return 0;
			switch(dataType){
				case  TINYINT:
					throw Exception::DateParse();
					break;
				case  INTEGER:
				case  BIGINT:
					UInt32 n1;
					n1 = *((UInt32 *)dataPtr);
					if(tmpTimestamp != 0)
						xvr2_delete(tmpTimestamp);
					tmpTimestamp = new Timestamp(n1);
					ret = tmpTimestamp;
					break;
				case  FLOAT:
					throw Exception::DateParse();
					break;
				case  DOUBLE:
					throw Exception::DateParse();
					break;
				case  CHAR:
				case  VARCHAR:
					UInt32 nx1;
					nx1 = strtoul((const char *)dataPtr, (char **)0, 10);
					if(errno == ERANGE)
						throw Exception::Number();
					if(tmpTimestamp != 0)
						xvr2_delete(tmpTimestamp);
					tmpTimestamp = new Timestamp(nx1);
					ret = tmpTimestamp;
					break;
				case  STRING:
				case  TEXT:
					UInt32 nx2;
					nx2 = ((String *)dataPtr)->toUInt();
					if(tmpTimestamp != 0)
						xvr2_delete(tmpTimestamp);
					tmpTimestamp = new Timestamp(nx2);
					ret = tmpTimestamp;
					break;
				case  BLOB:
					throw Exception::DateParse();
					break;
				case  DATE:
					if(tmpTimestamp != 0)
						xvr2_delete(tmpTimestamp);
					tmpTimestamp = new Timestamp(((Date *)dataPtr)->unixTime());
					ret = tmpTimestamp;
					break;
				case  TIME:
					if(tmpTimestamp != 0)
						xvr2_delete(tmpTimestamp);
					tmpTimestamp = new Timestamp(((Time *)dataPtr)->timestamp());
					ret = tmpTimestamp;
					break;
				case  TIMESTAMP:
					ret = (Timestamp *)dataPtr;
					break;
				case  BIT:
					throw Exception::DateParse();
					break;
				case  BYTE:
					throw Exception::DateParse();
					break;
			}
			return ret;
		}
	
		bool Field::toBool(){
			return toBit();
		}
	
		bool Field::toBit(){
			bool ret;
			if(isNull())
				return 0;
			switch(dataType){
				case  TINYINT:
				case  INTEGER:
				case  BIGINT:
				case  FLOAT:
				case  DOUBLE:
					if((*((int *)(dataPtr))) > 0){
						ret = true;
					}
					else{
						ret = false;
					}
					break;
				case  CHAR:
				case  VARCHAR:
					if(((char *)dataPtr)[0] - '0' > 0){
						ret = true;
					}
					else{
						ret = false;
					}
					break;
				case  BLOB:
					throw Exception::BitParse();
					break;
				case  STRING:
				case  TEXT:
					break;
				case  DATE:
				case  TIME:
				case  TIMESTAMP:
					throw Exception::BitParse();
					break;
				case  BIT:
					ret = *((bool *)dataPtr);
					break;
				case  BYTE:
					if(((Byte *)dataPtr)->theByte() > 0){
						ret = true;
					}
					else{
						ret = false;
					}
					break;
			}
			return ret;
		}
	
	
		const Byte *Field::toByte(){
			Byte *ret;
			if(isNull())
				return 0;
			switch(dataType){
				case  TINYINT:
				case  INTEGER:
				case  BIGINT:
				case  FLOAT:
				case  DOUBLE:
				case  CHAR:
				case  VARCHAR:
				case  BLOB:
				case  STRING:
				case  TEXT:
				case  DATE:
				case  TIME:
				case  TIMESTAMP:
					if(tmpByte != 0)
						xvr2_delete(tmpByte);
					tmpByte = new Byte(((UInt8 *)dataPtr)[0]);
					ret = tmpByte;
					break;
				case  BIT:
					throw Exception::ByteParse();
					break;
				case  BYTE:
					ret = (Byte *)dataPtr;
					break;
			}
			return ret;
		}
	/*
		void Field::toTinyInt(){
			Int16 val;
			switch(dataType){
				case  TINYINT:
					break;
				case  INTEGER:
					break;
				case  BIGINT:
					break;
				case  FLOAT:
					break;
				case  DOUBLE:
					break;
				case  CHAR:
					break;
				case  VARCHAR:
					break;
				case  STRING:
					break;
				case  BLOB:
					break;
				case  TEXT:
					break;
				case  DATE:
					break;
				case  TIME:
					break;
				case  TIMESTAMP:
					break;
				case  BIT:
					break;
				case  BYTE:
					break;
			}
		}*/

		const int Field::getDatatype(){
			return dataType;
		}
	
		const UInt32 Field::size(){
			return dataLen;
		}
	
		const UInt32 Field::dataSize(){
			return dataLen;
		}
	
		void Field::setFieldName(const String &nam){
			colname = nam.toCharPtr();
		}
	
		const String &Field::getFieldName(){
			return colname;
		}
	
		const bool Field::isNull(){
			if(dataPtr == 0)
				return true;
			return false;
		}
	
		//End implementation of class: Field
	};
};
