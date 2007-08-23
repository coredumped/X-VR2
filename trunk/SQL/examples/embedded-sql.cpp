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
#include<xvr2/String.h>
#include<xvr2/StringBuffer.h>
#include<xvr2/CoreExceptions.h>
#include<iostream>
#include"embedded_common.h"

using namespace xvr2;
using namespace xvr2::SQL;

using std::cout;
using std::cerr;
using std::endl;

#ifndef DEFAULT_DB_FILE
#define DEFAULT_DB_FILE "/tmp/xvr2-embedded.db"
#endif

void help();

static char *username[] = {
		"evil",
		"daemon",
		"tux2016",
		"phantom",
		"spidey"
};

static char *fullname[] = {
		"Darth Vader",
		"DNS Server",
		"A penguin?",
		"Marshmallow Man",
		"A burglar?"
};

int main(int argc, char *argv[]){
	DriverManager *manager;
	Driver *drv;
	String so_driver;
	String dbfile = DEFAULT_DB_FILE;
	Connection *conn = 0;
	for(int i = 1; i < argc; i++){
		String arg = argv[i];
		if(arg == "--driver"){
			StringBuffer tmp;
			tmp << __XVR2_PREFIX_DIR << "/lib/" << argv[i + 1] << "_driver-" <<
				__XVR2_VERSION_STRING << ".so." << __XVR2_MINOR_VERSION_STRING;
			so_driver = tmp.toString();
			dbfile = argv[i + 1];
			dbfile += "-local.db";
			i++;
		}
		else if(arg == "--help" || arg == "-h"){
			help();
			return 0;
		}
		else{
			std::cerr << "Unsupported argument: " << arg << endl;
			help();
			return 1;
		}
	}
	if(so_driver.size() == 0){
		std::cerr << "No driver given, aborting..." << endl;
		help();
		return 1;
	}
	cout << "Loading: " << so_driver << "...";
	cout.flush();
	manager = new DriverManager(so_driver);
	try{
		drv = manager->load();
		conn = new Connection(drv);
		cout << "done" << endl;
	}
	catch(xvr2::DSOSymbolException &dse){
		cerr << "FAILURE!!!" << endl;
		cerr << dse.osErrorMessage() << endl;
		return 1;
	}
	catch(xvr2::DSOException &de){
		cerr << "FAILURE!!!" << endl;
		cerr << de.toString() << endl;
		return 1;
	}
	cout << "Opening datafile: " << dbfile << "...";
	cout.flush();
	try{
		conn->open(dbfile);
		cout << "done" << endl;
	}
	catch(xvr2::SQL::ConnectionFailure &cf){
		cerr << " FAILURE: " << endl;
		cerr << cf.errorMessage() << endl;
		return 1;
	}
	
	try{
		cout << "Creating test table... " << endl;
		conn->execCommand("CREATE TABLE IF NOT EXISTS users ( "
										"id integer primary key AUTOINCREMENT,"
										"username TEXT NOT NULL,"
										"fullname TEXT"
									")");
		cout << "Inserting some data...";
		cout.flush();
		for(int i = 0; i < 5; i++){
			StringBuffer query;
			query << "INSERT INTO users (username, fullname) VALUES (";
			query << "'" << conn->escapeString(username[i]) << "',";
			query << "'" << conn->escapeString(fullname[i]) << "')";
			conn->execCommand(query);
		}
		cout << " done" << endl;
		cout << "Dumping table contents..." << endl;
		ResultSet *r = conn->query("select id,username,fullname from users");
		if(r){
			while(r->fetchRow()){
				cout << r->get(0).toInteger() << " | " << r->get(1).toString() <<
					": " << r->get(2).toString() << endl;
			}
			delete r;
		}
	}
	catch(xvr2::SQL::SQLQueryException &sqe){
		cerr << "While executing: " << sqe.query() << endl;
		cerr << "Failure: " << sqe.errorMessage() << endl;
		return 1;
	}

	conn->disconnect();
	delete conn;
	delete drv;
	delete manager;
	return 0;
}

void help(){
	cout << "embedded-sql --driver <DRIVERNAME>" << endl;
	cout << "Where DRIVERNAME could be: sqlite" << endl;
}
