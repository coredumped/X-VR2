/*
 * $Id$
 */
#include<DBResultSet.h>
#include<NullPointerException.h>
#include<ArrayIndexOutOfLimitsException.h>

namespace xvr2{

	namespace DB {

		ResultSet::ResultSet(Driver *drv, void *__handle, bool __status, UInt64 _afrows){
#ifndef USING_GCC3
			setClassName(xvr2::_xvr2ResultSet);
#endif
			r_handle = __handle;
			if(drv == 0)
				throw Exception::NullPointer();
			driver = drv;
			_status = __status;
			row = 0;
			if(_status == true && r_handle != 0)
				fetchNextRow();
	
			afrows = _afrows;
			nrows = afrows;
			ncols = 0;
			is_a_select = false;
		}
	
		ResultSet::ResultSet(Driver *drv, void *__handle, bool __status){
#ifndef USING_GCC3
			setClassName(xvr2::_xvr2ResultSet);
#endif
			r_handle = __handle;
			if(drv == 0 || __handle == 0)
				throw Exception::NullPointer();
			driver = drv;
			_status = __status;
			row = 0;
			if(_status == true && r_handle != 0)
				fetchNextRow();
	
			nrows = driver->numRows(__handle);
			ncols = driver->numCols(__handle);
			afrows = nrows;
			is_a_select = true;
		}
	
		ResultSet::~ResultSet(){
			if(row != 0)
				xvr2_delete_array(row);
			//Call here a driver provided resultset cleanup
			try{
				if(r_handle != 0)
					driver->freeResultSet(r_handle);
			}
			catch(...){
				throw;
			}
		}
	
		bool ResultSet::status(){
			return _status;
		}
	
		const int ResultSet::numRows(){
			return nrows;
		}
	
		const int ResultSet::numCols(){
			return ncols;
		}
	
		const String &ResultSet::getColName(const int index){
			if(!is_a_select){
			}
			if(row == 0){
				throw Exception::NoDataFetch();
			}
			if(index < 0 || index > numCols()){
				throw Exception::ArrayIndexOutOfLimits();
			}
			return row[index].getFieldName();
		}
	
		const Field *ResultSet::getRow(){
			if(row == 0){
				throw Exception::NoDataFetch();
			}
			return row;
		}
	
		const Field &ResultSet::get(const int index){
			if(row == 0){
				throw Exception::NoDataFetch();
			}
			if(index < 0 || index > numCols()){
				throw Exception::ArrayIndexOutOfLimits();
			}
			return row[index];
		}
	
		const Field &ResultSet::get(const char *colname){
			bool found = false;
			int index;
			if(row == 0){
				throw Exception::NoDataFetch();
			}
			for(index = 0; index < ncols ; index++){
				if(    ((String *)&(row[index].getFieldName()))->equals(colname)){
					found = true;
					break;
				}
			}
			if(found == false){
				throw Exception::ArrayIndexOutOfLimits();
			}
			return row[index];
		}
	
		const Field &ResultSet::get(const String &colname){
			bool found = false;
			int index;
			if(row == 0){
				throw Exception::NoDataFetch();
			}
			for(index = 0; index < ncols ; index++){
				if(    ((String *)&(row[index].getFieldName()))->equals(((String *)&colname)->toCharPtr())){
					found = true;
					break;
				}
			}
			if(found == false){
				throw Exception::ArrayIndexOutOfLimits();
			}
			return row[index];
		}
	
		const Field *ResultSet::fetchNextRow(){
			if(row != 0){
				xvr2_delete_array(row);
			}
			row = driver->fetchRow(r_handle);
			return row;
		}
	
		const UInt64 ResultSet::affectedRows(){
			return afrows;
		}

		const char *ResultSet::errorMessage(){
			return driver->resultErrorMessage(r_handle);
		}
	};
};
