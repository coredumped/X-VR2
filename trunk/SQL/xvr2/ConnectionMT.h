/*
 * $Id:ConnectionMT.h 540 2007-08-20 07:51:56Z mindstorm2600 $
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
#ifndef __XVR2_SQL_ConnectionMT_H__
#define __XVR2_SQL_ConnectionMT_H__

#include<xvr2/xvr2config.h>
#include<xvr2/SQL/Driver.h>
#include<xvr2/SQL/Connection.h>
#include<xvr2/Mutex.h>

namespace xvr2{
	namespace SQL {
		/**
		 * This class encapsulates the Connection class and provides a much more 
		 * complete interface to the SQL database connection paradigm in addition
		 * to a thread safe environment.
		 */
		class ConnectionMT:public Connection {
			private:
				Mutex mt;
			protected:
			public:
				/** This constructor will require an instatiated Driver */
				ConnectionMT(Driver *drv);
				/** This constructor will initialize the internal driver 
				 *  also will attempt to make a connection to the backend
				 *  database as soon as possible */
				ConnectionMT(Driver *drv, const String &server, 
					      const String &dbname,
					      const String &u, const String &p, 
					      int port = 0);
				/** cleanup routine */
				~ConnectionMT();
				ConnectionMT();
				/** This routine will connect you to the specified <b>server</b>
				 *  using the username <b>u</b>, password <b>p</b> and port
				 *  <b>port</b>.
				 *  If the connection is not successfull this method will
				 *  throw an appropiate exception.  */
				void connect(const String &server, const String &u, 
					     const String &dbname,
					     const String &p, int port = 0);
				/** This routine will connect you to the specified <b>server</b>
				 *  using the username <b>u</b>, password <b>p</b> and port
				 *  <b>port</b>.
				 *  If the connection is not successfull this method will
				 *  throw an appropiate exception.  */
				void connect(Driver *d, const String &server, const String &u, 
					     const String &dbname,
					     const String &p, int port = 0);
				/** This method will attempt to connect using the last
				 *  username, server, password and port supplied in a call
				 *  connect or the one used in the constructor */
				void connect();
				/** A call to this method will inmediately disconnect you
				 *  from the backend database */
				void disconnect();
				/** This method will send the command <b>cmd</b> to the
				 *  backend database, if it is a select it will return
				 *  a ResultSet <i>containing</i> the data returned by the 
				 *  database. If it is another type of command like an
				 *  update or delete or any other that does not return
				 *  data or a status completion of success or failure
				 *  then the returned ResultSet will not contain any data
				 *  instead call the <b>status</b> method of the ResultSet
				 *  to know if the call succeeded or not*/
				ResultSet *query(const String &cmd);
				ResultSet *query(const StringBuffer &cmd);
				/** Use this method to execute command which do not return
				 *  row information such as INSERT, UPDATE, DELETE, etc. The
				 *  method will return the number of affected rows. */
				int execCommand(const String &cmd);
				/** Use this method to execute command which do not return
				 *  row information such as INSERT, UPDATE, DELETE, etc. The
				 *  method will return the number of affected rows. */
				int execCommand(const StringBuffer &cmd);
				/** This will commit any transaction based 
				 *  command to the database, when you call 
				 *  commit every submitted delete or update 
				 *  they will execute each other in 
				 *  sequence */
				void commit();
				/** Sets the connection in bulk upload mode.
				 *  After calling this method and depending on the driver used
				 *  the RDBMS link will enter in a special mode so you can load
				 *  data in the specified table following the given column
				 *  ordering dividing each field by the given delimiter.
				 *  @param table The table to load data into.
				 *  @param cols A comma delimited order set of columns in the 
				 *  given table which values are to by loaded.
				 *  @param _delim Specifies the delimiter to be used between
				 *  fields in a bulk upload operation dataline.
				 *  @see bulkUploadData.
				 *  Look at the following sample code
				 *  @code
				 *  xvr2::DB::ConnectionMT *conn;
				 *  // Perform connection steps here
				 *  conn->bulkUploadBegin("foo_table", "name,lastname", "|"); //Put connection in bulk upload mode
				 *  conn->bulkUploadData("Jannette|Mejia");
				 *  conn->bulkUploadData("Juan|Guerrero");
				 *  conn->bulkUploadData("Natalie|Guerrero");
				 *  conn->bulkUploadData("Francisco|Guerrero");
				 *  conn->bulkUploadEnd();                                    //Restore connection to normal mode
				 *  // The rest of the program should go after this.
				 *  @endcode */				
				void bulkUploadBegin(const String &table, const String &cols, const String &_delim);
				/** Uploads a bulk of data to the RDBMS.
				 *  By calling this method you can actually load data to a DB
				 *  the format for this data must be same as specified while
				 *  calling xvr2::DB::bulkUploadBegin that is, string form
				 *  by concatenating each field of data delimited by the
				 *  specified string.
				 *  Look at the following sample code
				 *  @code
				 *  xvr2::DB::ConnectionMT *conn;
				 *  // Perform connection steps here
				 *  conn->bulkUploadBegin("foo_table", "name,lastname", "|"); //Put connection in bulk upload mode
				 *  conn->bulkUploadData("Jannette|Mejia");
				 *  conn->bulkUploadData("Juan|Guerrero");
				 *  conn->bulkUploadData("Natalie|Guerrero");
				 *  conn->bulkUploadData("Francisco|Guerrero");
				 *  conn->bulkUploadEnd();                                    //Restore connection to normal mode
				 *  // The rest of the program should go after this.
				 *  @endcode
				 *  @param data The data to be uploaded. */
				void bulkUploadData(const String &data);
				/** After bulk uploading data resets the connection to its
				 *  normal state. */
				void bulkUploadEnd();
				
				/** Changes the connection state to bulk download mode.
				 *  After calling this method the underlying connection will
				 *  move from its @e normal state to a special mode which will
				 *  allow you to download data in a specific format faster than
				 *  performing a select, very helpful when you need to download
				 *  a huge dataset.
				 *  @param table The table name from where you which to perform
				 *  the data extraction.
				 *  @param cols A comma delimited list of columns to be fetched
				 *  from the given table
				 *  @param _delim The delimiter to be used between each field
				 *  in a retrieved data row. */
				void bulkDownloadBegin(const String &table, const String &cols, const String &_delim);
				/** Allows you to fetch one row of data after the connection has
				 *  been put in bulk download mode.
				 *  @return A xvr2::String containing the retrieved data row
				 *  in the format given by bulkDownloadBegin, if the returned 
				 *  string is empty then all data has been completely retrieved
				 *  @see bulkDownloadBegin
				 *  An example could be something like:
				 *  @code
				 *  xvr2::DB::Connection conn;
				 *  //Perform connection steps here
				 *  conn->bulkDownloadBegin("bar_table", "name,lastname", "|");
				 *  while(true){
				 *    xvr2::String data = conn->bulkDownloadData();
				 *    if(data.size() == 0){
				 *      break;
				 *    }
				 *    else{
				 *      //Do something with the returned data row.
				 *    }
				 *  }
				 *  conn->bulkDownloadEnd(); 
				 *  @endcode */
				xvr2::String bulkDownloadData();
				/** Moves the connection from bulk download mode to @e normal
				 *  mode. */
				void bulkDownloadEnd();

				String escapeString(const String &s);
				char *escapeString(const char *);
				const char *errorMessage();
				/** Checks to see if the connection is still ok */
				const bool isConnected();
		};
	};
};

#endif
