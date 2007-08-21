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
#ifndef __XVR2_RESULTSET_H__
#define __XVR2_RESULTSET_H__
#include<xvr2/xvr2config.h>
#include<xvr2/SQL/Driver.h>
#include<xvr2/SQL/Field.h>
#include<xvr2/SQL/DatabaseException.h>

namespace xvr2{

	namespace SQL {

		class Driver;
		/**
		 * @brief Implements result set handling from SELECT-type queries.
		 *
		 */
		class ResultSet:public Object{
			private:
			protected:
				bool _status;
				/** A generic handle to the driver's specific resultset object */ 
				void *r_handle;
				/** Points to the SQL driver in use */
				Driver *driver;
				/** Holds the currect row in the stream */
				Field *row;
				int ncols;
				UInt64 afrows;
				bool is_a_select;
			public:
				/* Constructor, please do not call it directly */
				ResultSet(Driver *drv, void *__rhandle, bool __status);
				/* Constructor, please do not call it directly */
				ResultSet(Driver *drv, void *__rhandle, bool __status, UInt64 afrows);
				~ResultSet();
				/** Will hold the status of the previous query, if it was a query or not */
				bool status();
				/** Returns the number of retrieved rows in the ResultSet */
				const int numRows();
				/** Returns the number of retrieved columns in the ResultSet */
				const int numCols();
				/** Returns the name of a column */
				const String &getColName(const int index);
				/** This will return the current retrieved row as an 
				 *  array of Field elements */
				const Field *getRow();
				/** This will return the value of the given column: <b>index</b>
				 *  in the currently retrieved row */
				const Field &get(const int index);
				/** This will return the value of the given column name:
				 *  <b>colname</b> in the currently retrieved row */
				const Field &get(const char *colname);
				/** This will return the value of the given column name:
				 *  <b>colname</b> in the currently retrieved row */
				const Field &get(const String &colname);
				/** Use this method to move to next row to be read from the
				 *  result stream. This method will also return an array
				 *  of Field elements representing the cells of the
				 *  current row.<p>In case you reached the last row this
				 *  method will return NULL instead of the Field array*/
				const Field *fetchNextRow();
				/** In the case you ran an update, delete or another query
				 *  which does not return a ResultSet but alters the 
				 *  content of a tables, this method will tell you how
				 *  many rows got affected as a result of the operation */
				const UInt64 affectedRows();
				/** Returns the error message as returned by the RDBMS after
				 *  this query was sent */
				const char *errorMessage();
		};

	};
};

#endif