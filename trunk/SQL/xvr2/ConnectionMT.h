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
				void bulkUploadBegin(const String &table, const String &cols, const String &_delim);
				void bulkUploadData(const String &data);
				void bulkUploadEnd();

				String escapeString(const String &s);
				char *escapeString(const char *);
				const char *errorMessage();
				/** Checks to see if the connection is still ok */
				const bool isConnected();
		};
	};
};

#endif
