#include<xvr2.h>
#include "common.h"

static const char *MYSQL_DRIVER_LOCATION = __XVR2_PREFIX_DIR"/lib/xvr2/mysql_driver.so." __XVR2_VERSION_STRING;
static const char *PGSQL_DRIVER_LOCATION = __XVR2_PREFIX_DIR"/lib/xvr2/pgsql_driver.so." __XVR2_VERSION_STRING;


using namespace xvr2;

static const char *SS_TYPES[] = {
	"NOTYPE",
	"TINYINT",
	"INTEGER",
	"BIGINT",
	"FLOAT",
	"DOUBLE",
	"CHAR",
	"VARCHAR",
	"STRING",
	"BLOB",
	"TEXT0",
	"DATE1",
	"TIME",
	"TIMESTAMP",
	"BIT",
	"BYTE"
};

const char *dnames[] = {
	"MySQL",
	"PostgreSQL"
};

static char *driver_location;
static char *select_statement;
static char *server_location;
static char *db_user;
static char *db_pass;
static char *db_name;
static int db_port;

static bool loopit;

bool parse_args(int argc, char *argv[]){
	int i;
	String s;
	String tmp;
	std::string foo;
	loopit = false;
	for(i = 1; i < argc; i++){
		s = argv[i];
		Tokenizer *t;
		t = new Tokenizer(argv[i], "=");
		if(s.startsWith("--help")){
			std::cout << "Syntax: " << std::endl;
			std::cout << argv[0] << " [host=LOC] [database=DBNAME] [user=DBUSER] [pass=PASSWORD] [select=STMT]" << std::endl;
			std::cout << "where..." << std::endl;
			std::cout << "LOC is the ip address or hostname corresponding to your test database server" << std::endl;
			std::cout << "DBNAME is the database name to be used" << std::endl;
			std::cout << "DBUSER correspond to a valid user in that database" << std::endl;
			std::cout << "PASSWORD correspond to the user's password" << std::endl;
			std::cout << "STMT is a valid select statement for that database" << std::endl;
			//std::cout << "" << std::endl;
			exit(0);
		}
		else if(s.startsWith("host=")){
			tmp = t->next();
			tmp = t->next();
			server_location = strdup(tmp.toCharPtr());
		}
		else if(s.startsWith("user=")){
			tmp = t->next();
			tmp = t->next();
			db_user = strdup(tmp.toCharPtr());
		}
		else if(s.startsWith("database=")){
			tmp = t->next();
			tmp = t->next();
			db_name = strdup(tmp.toCharPtr());
		}
		else if(s.startsWith("password=")){
			tmp = t->next();
			tmp = t->next();
			if(tmp.toCharPtr() != 0){
				db_pass = strdup(tmp.toCharPtr());
			}
			else{
				db_pass = "";
			}
		}
		else if(s.startsWith("select=")){
			tmp = t->next();
			tmp = t->next();
			if(tmp.toCharPtr() != 0){
				select_statement = strdup(tmp.toCharPtr());
			}
		}
		else if(s.endsWith("loop")){
			loopit = true;
		}
		xvr2_delete(t);
	}
	if(server_location == 0){
		std::cout << "Server address: ";
		std::cin >> foo;
		server_location = strdup(foo.c_str());
	}
	if(db_name == 0){
		std::cout << "Database name: ";
		std::cin >> foo;
		db_name = strdup(foo.c_str());
	}
	if(db_user == 0){
		std::cout << "Username: ";
		std::cin >> foo;
		db_user = strdup(foo.c_str());
	}
	if(db_pass == 0){
		std::cout << "Password: \033[8m";
		std::cin >> foo;
		std::cout << "\033[0m";
		std::cout.flush();
		db_pass = strdup(foo.c_str());
	}
	if(select_statement == 0){
		std::cout << "Enter select statement below:" << std::endl;
		select_statement = new char(4096);
		select_statement[0] = 0;
		std::cin.ignore();
		std::cin.getline(select_statement, 4096);
	}
}

int rundemo(int demo_type){
	DB::Driver *drv;
	DB::Connection *conn = 0;
	DB::DriverInfo *q = 0;
	DB::ResultSet *r = 0;
	void *dbhandle;
	int ci, cj;
	bool capshown;
	switch(demo_type){
		case XVR2_MYSQL:
			if(driver_location == 0)
				driver_location = (char *)MYSQL_DRIVER_LOCATION;
			db_port = 3306;
			break;
		case XVR2_POSTGRESQL:
			if(driver_location == 0)
				driver_location = (char *)PGSQL_DRIVER_LOCATION;
			db_port = 5432;
			break;
	}
	drv = new DB::Driver(driver_location);
	try{
		drv->load();
	}
	catch(Exception::DSOSymbol e){
		std::cerr << e.getClassName() << ": " << e.toString() << std::endl;
		return 1;
	}
	drv->getVersionInfo(&q);
	std::cout << "X-VR2 " << dnames[demo_type] << " " << q->version() << "." << q->revision() << " by: " << q->vendor().toCharPtr() << " using: " << q->description().toCharPtr() << std::endl;

	conn = new DB::Connection(drv, server_location, db_name, db_user, db_pass, db_port);

	std::cout << "\n1. Connecting to database... ";
	std::cout.flush();
	try{
		conn->connect();
	}
	catch(Exception::Exception econn){
		std::cout << " " << econn.toString();
		std::cout << " failed" << std::endl;
		return 1;
	}
	std::cout << "succeeded" << std::endl;

/******  BEGIN QUERY *******/
	std::cout << "2. Querying database with \"" << select_statement << "\"... ";
	try{
		r = conn->query(select_statement);
	}
	catch(Exception::Exception e){
		std::cout << "failed" << std::endl;
		std::cerr << e.toString() << std::endl;
		return 1;
	}
	std::cout << "suceeded" << std::endl;

	std::cout << "3. Reading ResultSet with r->getRow()" << std::endl;
	capshown = false;
	for(ci = 0; ci < r->numRows(); ci++){
		DB::Field *ff = (DB::Field *)r->getRow();
		if(!capshown){
			for(cj = 0; cj < r->numCols(); cj++){
				std::cout << ff[cj].getFieldName().toCharPtr() << "\t";
			}
			std::cout << std::endl;
			capshown = true;
		}
		std::cout.flush();
		for(cj = 0; cj < r->numCols(); cj++){
			if(cj > 0)
				std::cout << "\t";
			if(ff[cj].isNull()){
				std::cout << "\tNULL";
			}
			else{
				std::cout << ff[cj].toString();
			}
			std::cout.flush();
		}
		std::cout << std::endl;
		r->fetchNextRow();
	}
	std::cout << "suceeded" << std::endl;
	std::cout << "4. Reading ResultSet with r->get()" << std::endl;
	delete r;
	try{
		r = conn->query(select_statement);
	}
	catch(Exception::Exception ex1){
		std::cout << "failed" << std::endl;
		std::cerr << ex1.toString() << std::endl;
		return 1;
	}
	capshown = false;
	for(ci = 0; ci < r->numRows(); ci++){
		if(!capshown){
			for(cj = 0; cj < r->numCols(); cj++){
				std::cout << r->get(cj).getFieldName().toCharPtr() << "\t";
			}
			std::cout << std::endl;
			capshown = true;
		}
		std::cout.flush();
		for(cj = 0; cj < r->numCols(); cj++){
			if(cj > 0)
				std::cout << "\t";
			if(r->get(cj).isNull()){
				std::cout << "\tNULL";
			}
			else{
				std::cout << r->get(cj).toString();
			}
			std::cout.flush();
		}
		std::cout << std::endl;
		r->fetchNextRow();
	}
	std::cout << "suceeded" << std::endl;




/******  END QUERY *******/
	std::cout << "5. Releasing ResultSet... ";
	std::cout.flush();
	try{
		xvr2_delete(r);
	}
	catch(...){
		std::cout << "failed" << std::endl;
		return 1;
	}
	std::cout << "succeeded" << std::endl;

	std::cout << "6. Disconnecting from database... ";
	std::cout.flush();
	try{
		conn->disconnect();
	}
	catch(...){
		std::cout << "failed" << std::endl;
		return 1;
	}
	std::cout << "succeeded" << std::endl;
	xvr2_delete(conn);
	xvr2_delete(drv);
	if(loopit){
		sleep(180);
	}
	return 0;
}
