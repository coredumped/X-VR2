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
#include"config.h"
#include<xvr2/xvr2config.h>
#include"ResultSet.h"

namespace xvr2{

	namespace SQL {

		ResultSet::ResultSet(Driver *drv, void *__handle, bool __status, UInt64 _afrows){
			r_handle = __handle;
			if(drv == 0)
				throw NullPointer();
			driver = drv;
			_status = __status;
			row = 0;
			if(_status == true && r_handle != 0)
				fetchNextRow();
	
			afrows = _afrows;
			ncols = 0;
			is_a_select = false;
		}
	
		ResultSet::ResultSet(Driver *drv, void *__handle, bool __status){
			driver = drv;
			_status = __status;
			row = 0;
			if(__status){
				r_handle = __handle;
				if(drv == 0 || __handle == 0)
					throw NullPointer();
				if(_status == true && r_handle != 0)
					fetchNextRow();
				ncols = driver->numCols(__handle);
				afrows = -1;
				is_a_select = true;
			}
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
			return driver->numRows(r_handle);
		}
	
		const int ResultSet::numCols(){
			return ncols;
		}
	
		const String &ResultSet::getColName(const int index){
			if(!is_a_select){
			}
			if(row == 0){
				throw NoDataFetch();
			}
			if(index < 0 || index > numCols()){
				throw ArrayIndexOutOfLimits(index, numCols());
			}
			return row[index].getFieldName();
		}
	
		const Field *ResultSet::getRow(){
			if(row == 0){
				throw NoDataFetch();
			}
			return row;
		}
	
		const Field &ResultSet::get(const int index){
			if(row == 0){
				throw NoDataFetch();
			}
			if(index < 0 || index > numCols()){
				throw ArrayIndexOutOfLimits(index, numCols());
			}
			return row[index];
		}

		const Field &ResultSet::get(const char *colname){
			bool found = false;
			int index;
			if(row == 0){
				throw NoDataFetch();
			}
			for(index = 0; index < ncols ; index++){
				if(row[index].getFieldName().equals(colname)){
					found = true;
					break;
				}
			}
			if(found == false){
				throw ArrayIndexOutOfLimits(index, ncols);
			}
			return row[index];
		}
	
		const Field &ResultSet::get(const String &colname){
			bool found = false;
			int index;
			if(row == 0){
				throw NoDataFetch();
			}
			for(index = 0; index < ncols ; index++){
				if(row[index].getFieldName().equals(colname.toCharPtr())){
					found = true;
					break;
				}
			}
			if(found == false){
				throw ArrayIndexOutOfLimits(index, ncols);
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
