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
#include<xvr2/Net/URI.h>
#include<iostream>

using xvr2::Net::URI;

int main(int argc, char *argv[]){
	if(argc <= 1){
		std::cerr << "Please provide a valid URI as an argument, like this: "
				  << argv[0] << " <URI>" << std::endl;
		return 1;
	}

	for(int i = 1; i < argc; i++){
		xvr2::Net::URI uri(argv[i]);
		if(i > 1){
			std::cout << std::endl;
		}
		std::cout << "== " << argv[i] << " ==" << std::endl;
		std::cout << "Scheme:       " << uri.scheme() << std::endl;
		std::cout << "Host:         " << uri.host() << std::endl;
		std::cout << "Port:         " << uri.port() << std::endl;
		std::cout << "Path:         " << uri.path() << std::endl;
		std::cout << "Params:       " << uri.paramString() << std::endl;
		std::cout << "Query String: " << uri.queryString() << std::endl;
		if(uri.queryString().size() > 0){
			xvr2::Net::URI::QueryMap querymap = uri.queryMap();
			for(xvr2::Net::URI::QueryMapIterator iter = querymap.begin();
					iter != querymap.end(); iter++){
				std::cout << "\t" << (*iter).first << ": " 
						  << (*iter).second << std::endl;
			}
		}
		std::cout << "Fragment:     " << uri.fragment() << std::endl;
		std::cout << "User:         " << uri.user() << std::endl;
		std::cout << "Password:     " << uri.password() << std::endl;
	}
	return 0;
}

