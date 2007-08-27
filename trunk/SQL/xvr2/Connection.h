/*
 * $Id:Connection.h 540 2007-08-20 07:51:56Z mindstorm2600 $
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
#ifndef __XVR2_SQL_Connection_H__
#define __XVR2_SQL_Connection_H__

#include<xvr2/xvr2config.h>
#include<xvr2/SQL/Driver.h>
#include<xvr2/SQL/DatabaseException.h>
#include<xvr2/StringBuffer.h>

namespace xvr2{
	namespace SQL {
		/** @brief Handles SQL database connections for RDBMS and embedded 
		 *  engines.
		 *  Tipically you'll get a Connection object after you have an 
		 *  instatiated driver, by the time you have the Connection object
		 *  instatiated you'll still need to perform the database connection
		 *  (if its an RDBMS) or opening (if it is an embbeded db engine), 
		 *  then after successfull usage you'll disconnect or close the
		 *  connection itself. */
		class Connection:public Object{
			private:
				/** @brief Opaque pointer to the "real" connection object. */
				void *__conn;
			protected:
				/** @brief Current driver in use by this Connection instance. */
				Driver	*driver;
				String	_server;
				String	_user;
				String	_password;
				String	_dbname;
				int		_port;
				bool	__connected;
				String	*bulk_delim;
			public:
				/** This constructor will require an instatiated Driver */
				Connection(Driver *drv);
				/** This constructor will initialize the internal driver 
				 *  also will attempt to make a connection to the backend
				 *  database as soon as possible */
				Connection(Driver *drv, const String &server, 
					      const String &dbname,
					      const String &u, const String &p, 
					      int port = 0);
				/** cleanup routine */
				~Connection();
				Connection();
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
				/** @brief Opens a connection to a local (embedded) database
				 *  engine.
				 *  Driver supplied database connection function, this method
				 *  will attempt to open a datafile as if it was a networked
				 *  connection, this is very useful for embedded database
				 *  engines which implement the SQL query language.
				 *  @param datafile A path to the datafile to the opened.
				 *  @return A connection handler. */
				void open(const String &datafile);
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
				/** Use this method to execute commands which do not return
				 *  row information such as INSERT, UPDATE, DELETE, etc. The
				 *  method will only return the number of affected rows. */
				int execCommand(const String &cmd);
				/** Use this method to execute commands which do not return
				 *  row information such as INSERT, UPDATE, DELETE, etc. The
				 *  method will only return the number of affected rows. */
				int execCommand(const StringBuffer &cmd);
				/** This will commit any transaction based 
				 *  command to the database, when you call 
				 *  commit every submitted delete or update 
				 *  they will execute each other in 
				 *  sequence */
				void commit();
				void bulkUploadBegin(const String &table, const String &cols, const String &_delim);
				void bulkUploadData(const String &data);
				void bulkUploadEnd();

				String escapeString(const String &s);
				//char *escapeString(const char *);
				const char *errorMessage();
				/** Checks to see if the connection is still ok */
				const bool isConnected();
		};
	};
};

#endif
