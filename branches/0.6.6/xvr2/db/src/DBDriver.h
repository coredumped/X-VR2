/*
 * $Id$
 */
#ifndef __XVR2_DB_DRIVER_H__
#define __XVR2_DB_DRIVER_H__
#include<Plugin.h>
#include<DBResultSet.h>
#include<DBDriverInfo.h>
#include<DBField.h>

namespace xvr2{

	namespace DB {

		class ResultSet;
	
		/**
		 * This class is an abstract interface for dynamic loading 
		 * database driver objects
		 *
		 */
		class Driver:public Object{
			private:
			protected:
				/** This is the driver handle */
				Plugin *__drv;
				bool		__do_auto_commit;
				bool		(*__drv_init)(Driver *__me);
				bool		(*__drv_cleanup)();
				void		*(*__drv_connect)(const char *srvr, 
								  const char *dbname, 
								  const char *usr, 
								  const char *pass, 
								  const int port);
				UInt32		(*__drv_disconnect)(void *handle);
				bool		(*__drv_getVersionInfo)(DB::DriverInfo **i);
				bool		(*__drv_commit)(void *handle);
				ResultSet	*(*__drv_query)(void *handle, 
								const char *cmd);
				// The following method pointers are for ResultSet usage
				Field	*(*__drv_fetch_next_row)(void *__res_handle);
				int		(*__drv_numcols)(void *__res_handle);
				int		(*__drv_numrows)(void *__res_handle);
				bool		(*__drv_free_resultset)(void *__res_handle);
				bool		__is_loaded;
			public:
				/** Default constructor it initialzes some 
				 *  defaults only */
				Driver(const String &soname);
				/** Destructor, this will verify if the 
				 *  Driver class is still loaded, if 
				 *  it is then it will unload it and 
				 *  attempt to clear all used resources */
				virtual ~Driver();
				/** This will load the class and any 
				 *  required internal symbols */
				void load();
				/** Use this function to retrieve verion 
				 *  and/or vendor informaton for the 
				 *  driver */
				void getVersionInfo(DB::DriverInfo **info);
				/** Driver supplied database connection 
				 *  function, it will return a <b>handler</b>
				 *  to the current connection if it is 
				 *  successfull.
				 *  The parameter <b>server</b> stands for
				 *  the server IP address or hostname.
				 *  <b>user</b> is the username as to whom
				 *  be connected, <b>pass</b> is the password
				 *  to be used and <b>port</b> is the port
				 *  to be used if there is a need to specify it
				 *  if you send the default <b>0</b> then the
				 *  port used is going to be the default for
				 *  the backend database.
				 */
				virtual void *connect(const String &server, 
						      const String &__dbname,
						      const String &user, const String &pass,
						      int port = 0);
				/** Use this method to send a command to 
				 *  the backend server. <b>__handle</b> is
				 *  the connection handler and <b>command</b>
				 *  is the command to be send to the backend
				 *  database */
				virtual ResultSet *query(void *__handle, 
							 const String &command);
				/** This method will disconnect you from 
				 *  the backend server if you are 
				 *  connected */
				virtual bool disconnect(void *__handle);
				/** The use of this method will turn on 
				 *  autocommits, the idea is that if you 
				 *  issue an  update or delete command this 
				 *  will call the commit command 
				 *  inmediately so there is no reason for 
				 *  you to call it manually everytime 
				 *  you need it */
				virtual void setAutoCommit(bool val = true);
				/** This will commit any transaction based 
				 *  command to the database, when you call 
				 *  commit every submitted delete or update 
				 *  they will execute each other in 
				 *  sequence */
				virtual void commit(void *__handle);
				/** This will return the number of rows for the current
				 *  result handle */
				virtual const int numRows(void *__res_handle);
				/** This will return the number of columns for the current
				 *  result handle */
				virtual const int numCols(void *__res_handle);
				/** This will fetch a row of data from a result obtained
				 *  after issueing a query to the RDBMS */
				Field *fetchRow(void *__res_handle);
				/** This will provide a means for clearing the memory used
				 *  by the resultset, this method must be call to release
				 *  that memory and avoid a memory leak */
				const bool freeResultSet(void *__res_handle);
		};
	};
};

#endif