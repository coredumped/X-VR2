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
#include<xvr2/StringBuffer.h>
#include<xvr2/SQL/DriverManager.h>
#include<xvr2/Tokenizer.h>
#include<xvr2/SQL/Connection.h>
#include<xvr2/SQL/Field.h>
#include<xvr2/SQL/ResultSet.h>
#include<xvr2/SQL/Driver.h>
#include<iostream>



using namespace xvr2;

const char *dnames[] = {
	"MySQL",
	"PostgreSQL"
};

static std::string select_statement;
static std::string server_location;
static std::string db_user;
static std::string db_pass;
static std::string db_name;
static int db_port;
StringBuffer drv_path;

static bool loopit;
int demo_type;

static const char *drv_arr[] = {
		"pgsql",
		"mysql"
};

static const int port_arr[] = { 5432, 3306 }; 

static const int n_drv = 2;

bool parse_args(int argc, char *argv[]){
	int i;
	String s;
	String tmp;
	std::string foo;
	loopit = false;
	demo_type = -1;
	for(i = 1; i < argc; i++){
		s = argv[i];
		Tokenizer *t;
		t = new Tokenizer(argv[i], "=");
		if(s.startsWith("--help")){
			std::cout << "Syntax: " << std::endl;
			std::cout << argv[0] << " <driver=DRIVER> [host=LOC] "
						<< "[database=DBNAME] "
						<< "[user=DBUSER] [password=PASSWORD] "
						<< "[query=STMT]" << std::endl;
			std::cout << "where..." << std::endl;
			std::cout << "DRIVER is the SQL driver to use, in this case, you"
						 " should provide an rdbms driver and not one for"
						 " embedded database engines, to get a list of"
						 " available drivers, use the --list-drivers"
						 " argument." << std::endl;
			std::cout << "LOC is the ip address or hostname corresponding to"
							" your test database server" << std::endl;
			std::cout << "DBNAME is the database name to be used" << std::endl;
			std::cout << "DBUSER correspond to a valid user in that database" 
						<< std::endl;
			std::cout << "PASSWORD correspond to the user's password" 
						<< std::endl;
			std::cout << "STMT is a valid select statement for that database" 
						<< std::endl;
			exit(0);
		}
		else if(s.startsWith("host=")){
			tmp = t->next();
			tmp = t->next();
			server_location = tmp.toCharPtr();
		}
		else if(s.startsWith("user=")){
			tmp = t->next();
			tmp = t->next();
			db_user = tmp.toCharPtr();
		}
		else if(s.startsWith("database=")){
			tmp = t->next();
			tmp = t->next();
			db_name = tmp.toCharPtr();
		}
		else if(s.startsWith("password=")){
			tmp = t->next();
			tmp = t->next();
			if(tmp.toCharPtr() != 0){
				db_pass = tmp.toCharPtr();
			}
			else{
				db_pass = "";
			}
		}
		else if(s.startsWith("query=")){
			tmp = t->next();
			tmp = t->next();
			if(tmp.toCharPtr() != 0){
				select_statement = tmp;
			}
		}
		else if(s.startsWith("--list-drivers")){
			for(int k = 0; k < n_drv; k++){
				std::cout << drv_arr[k] << std::endl;
			}
			return false;
		}
		else if(s.startsWith("driver=")){
			tmp = t->next();
			tmp = t->next();
			if(tmp.toCharPtr() != 0){
				drv_path << xvr2::InstallationPrefix << "/lib/" << tmp << "_driver-" << xvr2::VersionString << ".so." << xvr2::VersionMinor;
				for(int k = 0; k < n_drv; k++){
					if(tmp.equals(drv_arr[k])){
						db_port = port_arr[k];
					}
				}
			}
			
		}
		xvr2_delete(t);
	}
	if(server_location.size() == 0){
		std::cout << "Server address: ";
		std::cin >> foo;
		server_location = foo.c_str();
	}
	if(db_name.size() == 0){
		std::cout << "Database name: ";
		std::cin >> foo;
		db_name = foo.c_str();
	}
	if(db_user.size() == 0){
		std::cout << "Username: ";
		std::cin >> foo;
		db_user = foo.c_str();
	}
	if(db_pass.size() == 0){
		std::cout << "Password: \033[8m";
		std::cout.flush();
		std::cin >> foo;
		std::cout << "\033[0m";
		std::cout.flush();
		db_pass = foo.c_str();
	}
	if(select_statement.size() == 0){
		char *ss;
		std::cout << "Enter select statement below (no more than"
							" 4096 chars please):" << std::endl;
		ss = new char[4097];
		ss[0] = 0;
		std::cin.ignore();
		std::cin.getline(ss, 4096);
		select_statement = ss;
		delete[] ss;
	}
	return true;
}

int main(int argc, char *argv[]){
	SQL::Driver *drv;
	SQL::DriverManager *manager;
	SQL::Connection *conn = 0;
	SQL::DriverInfo q;
	SQL::ResultSet *r = 0;
	int cj;
	bool capshown;
	if(!parse_args(argc, argv)){
		return 1;
	}
	if(drv_path.toString().size() == 0){
		std::cerr << "No driver given, aborting, please run: " << std::endl;
		std::cerr << argv[0] << " --list-drivers" << std::endl << std::endl;
		return 1;
	}
	ExceptionTracer::enable();
	

	manager = new SQL::DriverManager(drv_path.toString());
	
	try{
		drv = manager->load();
		
	}
	catch(DSOSymbolException e){
		std::cerr << e.getClassName() << ": " << e.toString() << std::endl;
		return 1;
	}
	q = drv->getVersionInfo();
	std::cout << "X-VR2 " << dnames[demo_type] << " " << q.version() << "." << q.revision() << " by: " << q.vendor() << " using: " << q.description() << std::endl;

	conn = new SQL::Connection(drv, server_location, db_name, db_user, db_pass, db_port);

	std::cout << "\n1. Connecting to database... ";
	std::cout.flush();
	try{
		conn->connect();
	}
	catch(Exception econn){
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
	catch(Exception e){
		std::cout << "failed" << std::endl;
		std::cerr << e.toString() << std::endl;
		return 1;
	}
	std::cout << "suceeded" << std::endl;

	std::cout << "3. Reading ResultSet with r->getRow()" << std::endl;
	capshown = false;
	while(r->fetchRow()){
		SQL::Field *ff = (SQL::Field *)r->getRow();
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
	}
	std::cout << "suceeded" << std::endl;
	std::cout << "4. Reading ResultSet with r->get()" << std::endl;
	delete r;
	try{
		r = conn->query(select_statement);
	}
	catch(Exception ex1){
		std::cout << "failed" << std::endl;
		std::cerr << ex1.toString() << std::endl;
		return 1;
	}
	capshown = false;
	while(r->fetchRow()){
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
	manager->unload(drv);
	delete manager;
	return 0;
}
