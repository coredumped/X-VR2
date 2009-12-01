/*
 * Multitype container for SQL single data
 *
 * $Id$
 */
#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE
#endif
#include"config.h"
#include<time.h>
#include<ctype.h>
#include<unistd.h>
#include<xvr2/xvr2config.h>
#include<xvr2/_xvr2dbClassNames.h>
#include<xvr2/DBField.h>
#include<xvr2/Memory.h>
#include<xvr2/DatabaseException.h>
#include<errno.h>
#if __GNUC__ < 3
#define __USE_SVID
#include<stdlib.h>
#include<stdio.h>
#endif
#ifdef GCC_REVISION4
#include<cerrno>
#endif
#if ((__GLIBC__ == 2) && (__GLIBC_MINOR__ > 7))
#include<cstring>
#else
#include<string>
#endif
#include<cstdlib>

namespace xvr2{

	namespace DB {

		// Start definition of local variables
		// End definition of local variables

		// Start definition of local functions
		// End definition of local functions

		//Start implementation of class: Field

		Field::Field(const void *data, const UInt32 size){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(xvr2::__xvr2_DB_Field);
#endif
			tmpStrTINYINT = 0;
			tmpStrINTEGER = 0;
			tmpStrBIGINT = 0;
			tmpStrFLOAT = 0;
			tmpStrDOUBLE = 0;
			tmpStrBIT = 0;
			tmpStrBYTE = 0;
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

		Field::Field(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(xvr2::__xvr2_DB_Field);
#endif
		}

		Field::Field(const int type, const void *data, const UInt32 size){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(xvr2::__xvr2_DB_Field);
#endif
			init(type, data, size);
		}

		void Field::init(const int type, const void *data, const UInt32 size){
#if __GNUC__ < 3
			setClassName(xvr2::_xvr2Field);
#endif
			void *ttmp;
			tmpStrTINYINT = 0;
			tmpStrINTEGER = 0;
			tmpStrBIGINT = 0;
			tmpStrFLOAT = 0;
			tmpStrDOUBLE = 0;
			tmpStrBIT = 0;
			tmpStrBYTE = 0;
			tmpString.clear();
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
					//Perform char conversion for bits
					if(tmpStrBIT != 0){
						ttmp = (void *)tmpStrBIT;
						Memory::freeBuffer(&ttmp);
					}
					tmpStrBIT = (char *)Memory::allocBuffer(2);
					tmpStrBIT[1] = 0;
					if(*((bool *)dataPtr)){
						tmpStrBIT[0] = '1';
					}
					else{
						tmpStrBIT[0] = '0';
					}
					tmpString.assign(tmpStrBIT);
					break;
				case BYTE:
					//Perform char conversion for bytes
					if(tmpStrBYTE == 0){
						ttmp = (void *)tmpStrBYTE;
						Memory::freeBuffer(&ttmp);
					}
					tmpStrBYTE = (char *)Memory::allocBuffer(7);
					if(sprintf(tmpStrBYTE, "0x%x", *((int *)dataPtr)) != 1)
						throw NumberException();
					tmpString.assign(tmpStrBYTE);
					break;
				case TINYINT:
					tmpInt16 = new Int16();
					*tmpInt16 = *((Int16 *)data);
					dataPtr = (void *)tmpInt16;
					//Perform char conversion for tinyints
					Int16 n1;
					//void *ttmp;
					n1 = *((Int16 *)dataPtr);
					if(tmpStrTINYINT != 0){
						ttmp = (void *)tmpStrTINYINT;
						Memory::freeBuffer(&ttmp);
					}
					tmpStrTINYINT = (char *)Memory::allocBuffer(20);
					sprintf(tmpStrTINYINT, "%d", n1);
					tmpString.assign(tmpStrTINYINT);
					break;
				case INTEGER:
					tmpInt32 = new Int32();
					*tmpInt32 = *((Int32 *)data);
					dataPtr = (void *)tmpInt32;
					//Perform char conversion for integers
					Int32 _n2;
					_n2 = *((Int32 *)dataPtr);
					if(tmpStrINTEGER != 0){
						ttmp = (void *)tmpStrINTEGER;
						Memory::freeBuffer(&ttmp);
					}
					tmpStrINTEGER = (char *)Memory::allocBuffer(40);
					sprintf(tmpStrINTEGER, "%d", _n2);
					tmpString.assign(tmpStrINTEGER);
					break;
				case BIGINT:
					tmpInt64 = new Int64();
					*tmpInt64 = *((Int64 *)data);
					dataPtr = (void *)tmpInt64;
					//Perform char conversion for bigints
					Int64 n3;
					n3 = *((Int64 *)dataPtr);
					if(tmpStrBIGINT != 0){
						ttmp = (void *)tmpStrBIGINT;
						Memory::freeBuffer(&ttmp);
					}
					tmpStrBIGINT = (char *)Memory::allocBuffer(64);
					sprintf(tmpStrBIGINT, "%lld", n3);
					tmpString.assign(tmpStrBIGINT);
					break;
				case FLOAT:
					tmpFloat = new float();
					*tmpFloat = *((float *)data);
					dataPtr = (void *)tmpFloat;
					//Perform char conversion for floats
					float n4;
					n4 = *((float *)dataPtr);
					if(tmpStrFLOAT != 0){
						ttmp = (void *)tmpStrFLOAT;
						Memory::freeBuffer(&ttmp);
					}
					tmpStrFLOAT = (char *)Memory::allocBuffer(32);
#if ( defined USING_LINUX || defined SOLARIS )
					if(gcvt(n4, 8, tmpStrFLOAT) != tmpStrFLOAT){
						throw NumberException();
					}
#else
					if(sprintf(tmpStrFLOAT, "%f", n4) != 1){
						throw NumberException();
					}
#endif
					tmpString.assign(tmpStrFLOAT);
					break;
				case DOUBLE:
					tmpDouble = new double();
					*tmpDouble = *((double *)data);
					dataPtr = (void *)tmpDouble;
					//Perform char conversion for doubles
					double n5;
					n5 = *((double *)dataPtr);
					if(tmpStrDOUBLE != 0){
						ttmp = (void *)tmpStrDOUBLE;
						Memory::freeBuffer(&ttmp);
					}
					tmpStrDOUBLE = (char *)Memory::allocBuffer(128);
#if ( defined USING_LINUX || defined SOLARIS )
					if(gcvt(n5, 8, tmpStrDOUBLE) != tmpStrDOUBLE){
						throw NumberException();
					}
#else
					if(sprintf(tmpStrDOUBLE, "%f", n5) != 1){
						throw NumberException();
					}
#endif
					tmpString.assign(tmpStrDOUBLE);
					break;
				case DATE:
					tmpDate = new Date((Date *)data);
					dataPtr = (void *)tmpDate;
					//tmpString.assign(tmpDate->toString().toCharPtr());
					tmpString.assign(tmpDate->toString());
					break;
				case TIME:
					tmpTime = new Time((Time *)data);
					dataPtr = (void *)tmpTime;
					tmpString.assign(tmpTime->toString());
					break;
				case TIMESTAMP:
					tmpTimestamp = new Timestamp(((Timestamp *)data)->unixTime());
					dataPtr = (void *)tmpTimestamp;
					//tmpString.assign(tmpTimestamp->toString().toCharPtr());
					tmpString.assign(tmpTimestamp->toString());
					break;
				case CHAR:
				case TEXT:
				case VARCHAR:
					dataPtr = (void *)data;
					if(dataPtr == 0){
						tmpString.clear();
					}
					else{
						tmpString.assign((char *)data);
					}
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
			if(tmpStrTINYINT != 0){
				ttmp = tmpStrTINYINT;
				Memory::freeBuffer(&ttmp);
			}
			if(tmpStrINTEGER!= 0){
				ttmp = tmpStrINTEGER;
				Memory::freeBuffer(&ttmp);
			}
			if(tmpStrBIGINT!= 0){
				ttmp = tmpStrBIGINT;
				Memory::freeBuffer(&ttmp);
			}
			if(tmpStrFLOAT!= 0){
				ttmp = tmpStrFLOAT;
				Memory::freeBuffer(&ttmp);
			}
			if(tmpStrDOUBLE != 0){
				ttmp = tmpStrDOUBLE;
				Memory::freeBuffer(&ttmp);
			}
			if(tmpStrBIT!= 0){
				ttmp = tmpStrBIT;
				Memory::freeBuffer(&ttmp);
			}
			if(tmpStrBYTE!= 0){
				ttmp = tmpStrBYTE;
				Memory::freeBuffer(&ttmp);
			}
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

		Int16 Field::toTinyInt() const{
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
					throw BufferTooSmall();
					break;
				case  TIME:
					t = (xvr2::Time *)dataPtr;
					val = t->Hour() * 10000 + t->Minute() * 100 + t->Second();
					break;
				case  TIMESTAMP:
					throw BufferTooSmall();
					break;
				case  CHAR:
					Memory::copy(&val, dataPtr, sizeof(char));
					break;
				case  VARCHAR:
					if(dataLen < 1)
						throw BufferTooSmall();
					str = (char *)dataPtr;
					val = str.toInt();
					break;
				//By default if everyone of the option fails convert
				//the data to a String
				case  TEXT:
				case  STRING:
				default:
					if(dataLen < 1)
						throw BufferTooSmall();
					else{
						try{
							val = (Int16)((String *)dataPtr)->toInt();
						}
						catch(...){
							throw UndefinedClassException();
						}
					}
			}
			return val;
		}

		UInt16 Field::toUTinyInt() const{
			return (UInt16)toTinyInt();
		}

		Int32 Field::toInteger() const{
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
						throw BufferTooSmall();
					str = (char *)dataPtr;
					val = str.toInt();
					break;
				//By default if everyone of the option fails convert
				//the data to a String
				case  TEXT:
				case  STRING:
				default:
					if(dataLen < 1)
						throw BufferTooSmall();
					else{
						try{
							val = (Int32)((String *)dataPtr)->toInt();
						}
						catch(...){
							throw UndefinedClassException();
						}
					}
			}
			return val;
		}

		UInt32 Field::toUInteger() const{
			return (UInt32)toInteger();
		}

		Int64 Field::toBigInt() const{
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
						throw BufferTooSmall();
					str = (char *)dataPtr;
					val = str.toInt64();
					break;
				//By default if everyone of the option fails convert
				//the data to a String
				case  TEXT:
				case  STRING:
				default:
					if(dataLen < 1)
						throw BufferTooSmall();
					else{
						try{
							val = (Int64)((String *)dataPtr)->toInt64();
						}
						catch(...){
							throw UndefinedClassException();
						}
					}
			}
			return val;
		}

		UInt64 Field::toUBigInt() const{
			return (UInt64)toBigInt();
		}

		float Field::toFloat() const{
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
						throw BufferTooSmall();
					str = (char *)dataPtr;
					val = str.toFloat();
					break;
				//By default if everyone of the option fails convert
				//the data to a String
				case  TEXT:
				case  STRING:
				default:
					if(dataLen < 1)
						throw BufferTooSmall();
					else{
						try{
							val = (float)((String *)dataPtr)->toFloat();
						}
						catch(...){
							throw UndefinedClassException();
						}
					}
			}
			return val;
		}

		double Field::toDouble() const{
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
						throw BufferTooSmall();
					str = (char *)dataPtr;
					val = str.toDouble();
					break;
				//By default if everyone of the option fails convert
				//the data to a String
				case  TEXT:
				case  STRING:
				default:
					if(dataLen < 1)
						throw BufferTooSmall();
					else{
						try{
							val = (double)((String *)dataPtr)->toDouble();
						}
						catch(...){
							throw UndefinedClassException();
						}
					}
			}
			return val;
		}

		char *Field::toChar() const{
			char *ret = 0;
			//void *ttmp;
			if(isNull())
				return 0;
			switch(dataType){
				case  TINYINT:
					ret = tmpStrTINYINT;
					break;
				case  INTEGER:
					ret = tmpStrINTEGER;
					break;
				case  BIGINT:
					ret = tmpStrBIGINT;
					break;
				case  FLOAT:
					ret = tmpStrFLOAT;
					break;
				case  DOUBLE:
					ret = tmpStrDOUBLE;
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
						throw UndefinedClassException();
					}
					break;
				case  BLOB:
					throw Exception();
					break;
				case  DATE:
					try{
						//#################################
						//#  I need a better way to implement
						//#  this, please HELP!!!!!!!!!
						//#################################
						ret = (char *)(((Date *)dataPtr)->toString().c_str());
					}
					catch(...){
						throw UndefinedClassException();
					}
					break;
				case  TIME:
					try{
						//#################################
						//#  I need a better way to implement
						//#  this, please HELP!!!!!!!!!
						//#################################
						ret = (char *)(((Time *)dataPtr)->toString().c_str());
					}
					catch(...){
						throw UndefinedClassException();
					}
					break;
				case  TIMESTAMP:
					try{
						//#################################
						//#  I need a better way to implement
						//#  this, please HELP!!!!!!!!!
						//#################################
						ret = (char *)(((Timestamp *)dataPtr)->toString().c_str());
					}
					catch(...){
						throw UndefinedClassException();
					}
					break;
				case  BIT:
					ret = tmpStrBIT;
					break;
				case  BYTE:
					ret = tmpStrBYTE;
					break;
			}
			return ret;
		}


		const String &Field::toString() const{
			return tmpString;
		}


		const String &Field::toText() const{
			return tmpString;
		}

		const Date *Field::toDate(){
			Date *ret = 0;
			struct tm tt;
			if(isNull())
				return 0;
			switch(dataType){
				case  TINYINT:
					throw DateParseException();
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
					throw DateParseException();
					break;
				case  DOUBLE:
					throw DateParseException();
					break;
				case  CHAR:
				case  VARCHAR:
					if(strptime((char *)dataPtr, "%Y-%m-%d %H:%M:%S", &tt) != 0){
						throw DateParseException();
					}
					else{
						if(strptime((char *)dataPtr, "%d-%m-%Y %H:%M:%S", &tt) != 0){
							throw DateParseException();
						}
						else{
							if(strptime((char *)dataPtr, "%D", &tt) != 0){
								throw DateParseException();
							}
							else{
								if(strptime((char *)dataPtr, "%a %b %d %H:%M:%S %Z %Y", &tt) != 0){
									throw DateParseException();
								}
								else{
									if(strptime((char *)dataPtr, "%x", &tt) != 0){
										throw DateParseException();
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
						throw UndefinedClassException();
					}
					if(strptime((char *)dataStr, "%Y-%m-%d %H:%M:%S", &tt) != 0){
						throw DateParseException();
					}
					else{
						if(strptime((char *)dataStr, "%d-%m-%Y %H:%M:%S", &tt) != 0){
							throw DateParseException();
						}
						else{
							if(strptime((char *)dataStr, "%D", &tt) != 0){
								throw DateParseException();
							}
							else{
								if(strptime((char *)dataStr, "%a %b %d %H:%M:%S %Z %Y", &tt) != 0){
									throw DateParseException();
								}
								else{
									if(strptime((char *)dataStr, "%x", &tt) != 0){
										throw DateParseException();
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
					throw DateParseException();
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
					throw DateParseException();
					break;
				case  BYTE:
					throw DateParseException();
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
					throw DateParseException();
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
					throw DateParseException();
					break;
				case  DOUBLE:
					throw DateParseException();
					break;
				case  CHAR:
				case  VARCHAR:
					if(strptime((char *)dataPtr, "%Y-%m-%d %H:%M:%S", &tt) != 0){
						throw DateParseException();
					}
					else{
						if(strptime((char *)dataPtr, "%d-%m-%Y %H:%M:%S", &tt) != 0){
							throw DateParseException();
						}
						else{
							if(strptime((char *)dataPtr, "%D", &tt) != 0){
								throw DateParseException();
							}
							else{
								if(strptime((char *)dataPtr, "%a %b %d %H:%M:%S %Z %Y", &tt) != 0){
									throw DateParseException();
								}
								else{
									if(strptime((char *)dataPtr, "%x", &tt) != 0){
										throw DateParseException();
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
						throw UndefinedClassException();
					}
					if(strptime((char *)dataStr, "%H:%M:%S", &tt) != 0){
						throw DateParseException();
					}
					else{
						if(strptime((char *)dataStr, "%H:%M", &tt) != 0){
							throw DateParseException();
						}
					}
					if(tmpTime != 0)
						xvr2_delete(tmpTime);
					tmpTime = new Time(tt.tm_hour, tt.tm_min, tt.tm_sec);
					ret = tmpTime;
					break;
				case  BLOB:
					throw DateParseException();
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
					throw DateParseException();
					break;
				case  BYTE:
					throw DateParseException();
					break;
			}
			return ret;
		}

		Timestamp Field::toTimestamp() const {
			if(isNull()){
				throw FieldIsNull(colname);
			}
			switch(dataType){
				case  TINYINT:
					throw DateParseException();
					break;
				case  INTEGER:
				case  BIGINT:
					UInt32 n1;
					n1 = *((UInt32 *)dataPtr);
					return Timestamp(n1);
					break;
				case  FLOAT:
					throw DateParseException();
					break;
				case  DOUBLE:
					throw DateParseException();
					break;
				case  CHAR:
				case  VARCHAR:
					UInt32 nx1;
					nx1 = strtoul((const char *)dataPtr, (char **)0, 10);
					if(errno == ERANGE)
						throw NumberException();
					return Timestamp(nx1);
					break;
				case  STRING:
				case  TEXT:
					UInt32 nx2;
					nx2 = ((String *)dataPtr)->toUInt();
					return Timestamp(nx2);
					break;
				case  BLOB:
					throw DateParseException();
					break;
				case  DATE:
					return Timestamp(((Date *)dataPtr)->unixTime());
					break;
				case  TIME:
					return Timestamp(((Time *)dataPtr)->timestamp());
					break;
				case  TIMESTAMP:
					//Timestamp *ret = (Timestamp *)dataPtr;
					return Timestamp(((Timestamp *)dataPtr)->unixTime());
					break;
				case  BIT:
					throw DateParseException();
					break;
				case  BYTE:
					throw DateParseException();
					break;
			}
			//return ret;
			return Timestamp();
		}

		Timestamp Field::toTimestamp(){
			//Timestamp *ret = 0;
			if(isNull()){
				//return 0;
				throw FieldIsNull(colname);
			}
			switch(dataType){
				case  TINYINT:
					throw DateParseException();
					break;
				case  INTEGER:
				case  BIGINT:
					UInt32 n1;
					n1 = *((UInt32 *)dataPtr);
					if(tmpTimestamp != 0)
						xvr2_delete(tmpTimestamp);
					tmpTimestamp = new Timestamp(n1);
					//ret = tmpTimestamp;
					return Timestamp(n1);
					break;
				case  FLOAT:
					throw DateParseException();
					break;
				case  DOUBLE:
					throw DateParseException();
					break;
				case  CHAR:
				case  VARCHAR:
					UInt32 nx1;
					nx1 = strtoul((const char *)dataPtr, (char **)0, 10);
					if(errno == ERANGE)
						throw NumberException();
					if(tmpTimestamp != 0)
						xvr2_delete(tmpTimestamp);
					tmpTimestamp = new Timestamp(nx1);
					//ret = tmpTimestamp;
					return Timestamp(nx1);
					break;
				case  STRING:
				case  TEXT:
					UInt32 nx2;
					nx2 = ((String *)dataPtr)->toUInt();
					if(tmpTimestamp != 0)
						xvr2_delete(tmpTimestamp);
					tmpTimestamp = new Timestamp(nx2);
					//ret = tmpTimestamp;
					return Timestamp(nx2);
					break;
				case  BLOB:
					throw DateParseException();
					break;
				case  DATE:
					if(tmpTimestamp != 0)
						xvr2_delete(tmpTimestamp);
					tmpTimestamp = new Timestamp(((Date *)dataPtr)->unixTime());
					//ret = tmpTimestamp;
					return Timestamp(((Date *)dataPtr)->unixTime());
					break;
				case  TIME:
					if(tmpTimestamp != 0)
						xvr2_delete(tmpTimestamp);
					tmpTimestamp = new Timestamp(((Time *)dataPtr)->timestamp());
					//ret = tmpTimestamp;
					return Timestamp(((Time *)dataPtr)->timestamp());
					break;
				case  TIMESTAMP:
					//Timestamp *ret = (Timestamp *)dataPtr;
					return Timestamp(((Timestamp *)dataPtr)->unixTime());
					break;
				case  BIT:
					throw DateParseException();
					break;
				case  BYTE:
					throw DateParseException();
					break;
			}
			//return ret;
			return Timestamp();
		}

		bool Field::toBool() const{
			return toBit();
		}

		bool Field::toBit() const{
			bool ret = 0;
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
					throw BitParseException();
					break;
				case  STRING:
				case  TEXT:
					break;
				case  DATE:
				case  TIME:
				case  TIMESTAMP:
					throw BitParseException();
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
			Byte *ret = 0;
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
					throw ByteParseException();
					break;
				case  BYTE:
					ret = (Byte *)dataPtr;
					break;
			}
			return ret;
		}

		const int Field::getDatatype(){
			return dataType;
		}

		const int Field::getDatatype() const {
			return dataType;
		}

		const UInt32 Field::size(){
			return dataLen;
		}

		const UInt32 Field::size() const{
			return dataLen;
		}

		const UInt32 Field::dataSize(){
			return dataLen;
		}

		const UInt32 Field::dataSize() const{
			return dataLen;
		}

		void Field::setFieldName(const String &nam){
			colname = nam.toCharPtr();
		}

		const String &Field::getFieldName() const {
			return colname;
		}

		bool Field::isNull() const{
			if(dataPtr == 0)
				return true;
			return false;
		}

		//End implementation of class: Field
	};
};
