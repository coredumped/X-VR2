/*
 * $Id$
 */

#ifndef DRV_VERSION
#define DRV_VERSION 0
#endif

#ifndef DRV_REVISION
#define DRV_REVISION 1
#endif

using namespace xvr2;

/** This has to be a pointer to the parent SQLDriver object, sometimes it is needed
 *  to have a reference to this data Object */
static SQLDriver *me;
static DBDriverInfo *info;
xvr2::Mutex __sqlGlobalMutex;

void _init(){
	//Default library loading function
	me = 0;
	std::cout << "Loading $Id$" << std::endl;
}

bool	__drv_init(SQLDriver *__me){
	//Execute driver initialization routines in here
	if(__me == 0)
		throw NullPointerException();
	me = __me;
	info = new DBDriverInfo(DRV_VERSION, DRV_REVISION, "Driver author", "This is a template driver");
	return true;
}

bool	__drv_cleanup(){
	//Cleanup any state variables and or other remaining data
	std::cout << "Template driver, cleaning up... " << std::endl;
	xvr2_delete(info);
	return true;
}

void *__drv_connect(const char *srvr, const char *usr, const char *pass, const int port){
	//use this method to actually connect to the database via TCP/IP
	return (void *)connection_pointer;
}

Uint32 __drv_disconnect(void *handle){
	//A call to this method will disconnect you from the database
	return 1;
}

bool	__drv_getVersionInfo(DBDriverInfo **i){
	//A call to this function will fill the <b>i</b> variable with some
	//information about the driver itself
	*i = info;
	return true;
}

bool	__drv_commit(void *handle){
	// For SQL-based databases use this command to flush commands to the RDBMS
	// engine
	return true;
}

ResultSet *__drv_query(void *handle, const char *cmd){
	//Function will call and execute a query, also it will pass an instance 
	//of a library self-pointer
	ResultSet *r = 0;

	//Modify query replacing conflictive characters with escape secuences
	//Actually perform the query
	//Store the result in the *result pointer and create a new ResultSet instance
	r = new ResultSet(me, (void *)result, true);
	return r;
}

bool	__drv_usedb(void *handle, const char *dbname){
	//Will change to an active database
	return true;
}

SQLField *__drv_fetch_next_row(void *__res_handle){
	//Will fetch the next row in a database
	SQLField *s = 0;
	unsigned int num, n;
	int thetype;
	//Get the number of columns and store them in the num variable
	//Allocate the field array
	s = new SQLField[num];
	//Get the ResultSet row using the database API methods
	if(row == 0)
		return 0;
	//Open a loop to instatiate every data field
	for(n = 0; n < num; n++){
		//Get the name of the current field and store it in the name variable
		//Then set the s[n] element fieldname to name
		s[n].setFieldName(name);
		//Get the type of the field (INTEGER,VARCHAR,etc....) and store it in
		//the type variable
		//Then assign it to the thetype variable
		thetype = type;
		/*
		 * NOTE: 
		 * For some reason MySQL returns rows as a two-dimensional
		 * array of chars so for MySQL thetype will allways resemble
		 * a char array
		 */
		switch(thetype){
			case /* Database API type definition */:
				s[n].init(xvr2::SQLField::/* xvr2 API equivalent */, (void *)(/* DATA POINTER */), /* DATA LENGTH IN BYTES */);
				break;
			default:
				s[n].init(xvr2::SQLField::/* xvr2 API equivalent */, (void *)(/* DATA POINTER */), /* DATA LENGTH IN BYTES */);
				break;
		}
	}
	return s;
}

int	__drv_numcols(void *__res_handle){
	//Will return the number of columns in a query result
	int n = 0;
	//Use database API to retrieve the number of columns gathered during the query and store the value in the n variable
	return n;
}

int	__drv_numrows(void *__res_handle){
	//Will return the number of rows in a query result
	int n = 0;
	//Use database API to retrieve the number of rows gathered during the query and store the value in the n variable
	return n;
}

bool	__drv_free_resultset(void *__res_handle){
	//Call database function API to release the resultset's memory
	return true;
}
