#include<xvr2.h>

using namespace xvr2;

#define DRIVER_LOCATION  __XVR2_PREFIX_DIR "/lib/xvr2/pgsql_driver.so"
#define SELECT_STATEMENT "select * from network_device"
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

int main(int argc, char *argv[]){
	DB::Driver *drv;
	DB::Connection *conn = 0;
	DB::DriverInfo *q = 0;
	DB::ResultSet *r = 0;
	void *dbhandle;
	int ci,
 cj;
	drv = new DB::Driver(DRIVER_LOCATION);
	try{
		drv->load();
	}
	catch(Exception::DSOSymbol e){
		std::cerr << e.getClassName() << ": " << e.toString() << std::endl;
		return 1;
	}
	drv->getVersionInfo(&q);
	std::cout << "X-VR2 PostgreSQL driver " << q->version() << "." << q->revision() << " by: " << ((String *)&q->vendor())->toCharPtr() << " using: " << ((String *)&q->description())->toCharPtr() << std::endl;

	conn = new DB::Connection(drv, "127.0.0.1", "xvr2", "postgres", "", 5432);

	std::cout << "\n1. Connecting to database... ";
	std::cout.flush();
	try{
		conn->connect();
	}
	catch(...){
		std::cout << "failed" << std::endl;
		return 1;
	}
	std::cout << "succeeded" << std::endl;

/******  BEGIN QUERY *******/
	std::cout << "\n2. Querying database with \"" << SELECT_STATEMENT << "\"... ";
	try{
		r = conn->query(SELECT_STATEMENT);
	}
	catch(Exception::Exception e){
		std::cout << "failed" << std::endl;
		std::cerr << e.toString() << std::endl;
		return 1;
	}
	std::cout << "suceeded" << std::endl;

	std::cout << "Number of columns: " << r->numCols() << std::endl;
	std::cout << "Number of rows: " << r->numRows() << std::endl << std::endl;

	std::cout << "\n3. Reading ResultSet... " << std::endl;
	bool capshown = false;
	for(ci = 0; ci < r->numRows(); ci++){
		DB::Field *ff = (DB::Field *)r->getRow();
		if(!capshown){
			for(cj = 0; cj < r->numCols(); cj++){
				std::cout << ((String *)&ff[cj].getFieldName())->toCharPtr() << "\t";
			}
			std::cout << std::endl;
			capshown = true;
		}
		std::cout.flush();
		for(cj = 0; cj < r->numCols(); cj++){
			/*int magic;
			magic = ff[cj].getDatatype();
			std::cout << "\t[" << SS_TYPES[magic] << "]";
			std::cout.flush();*/
			std::cout << "\t" << ff[cj].toChar();
			std::cout.flush();
		}
		//std::cout << ff[0].toInteger();
		/*std::cout << ((DB::Field *)&r->get("datname"))->toChar();
		std::cout << "\t" << ff[1].toChar();
		std::cout << "\t" << ff[2].toInteger();
		std::cout << "\t" << ff[3].toBool();
		std::cout << "\t\t" << ff[4].toBool();*/
		std::cout << std::endl;
		r->fetchNextRow();
	}
	std::cout << "suceeded" << std::endl;
/******  END QUERY *******/
	std::cout << "\n4. Releasing ResultSet... ";
	std::cout.flush();
	try{
		xvr2_delete(r);
	}
	catch(...){
		std::cout << "failed" << std::endl;
		return 1;
	}
	std::cout << "succeeded" << std::endl;

	std::cout << "\n5. Disconnecting from database... ";
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
	if(argc > 1){
		if(strcmp(argv[1], "--loop") == 0){
			int mins = 0;
			std::cout << "Loop for 10 minutes" << std::endl;
			while(mins < 10){
				sleep(60);
				mins++;
			}
		}
	}
	return 0;
}
