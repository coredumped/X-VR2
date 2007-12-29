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
#include"URI.h"
#include<xvr2/Tokenizer.h>
#include<xvr2/StringBuffer.h>

#ifndef DEFAULT_HTTP_PORT
#define DEFAULT_HTTP_PORT 80
#endif
#ifndef DEFAULT_HTTPS_PORT
#define DEFAULT_HTTPS_PORT 443
#endif
#ifndef DEFAULT_FTP_PORT
#define DEFAULT_FTP_PORT 21
#endif
#ifndef DEFAULT_H323_PORT
#define DEFAULT_H323_PORT 1720
#endif
#ifndef DEFAULT_IMAP_PORT
#define DEFAULT_IMAP_PORT 143
#endif
#ifndef DEFAULT_SMTP_PORT
#define DEFAULT_SMTP_PORT 25
#endif
#ifndef DEFAULT_LDAP_PORT
#define DEFAULT_LDAP_PORT 389
#endif
#ifndef DEFAULT_POP3_PORT
#define DEFAULT_POP3_PORT 110
#endif
#ifndef DEFAULT_SIP_PORT
#define DEFAULT_SIP_PORT 5060
#endif
#ifndef DEFAULT_SIPS_PORT
#define DEFAULT_SIPS_PORT 5061
#endif
#ifndef DEFAULT_SNMP_PORT
#define DEFAULT_SNMP_PORT 161
#endif

namespace xvr2 {

	namespace Net {

		struct __smap {
			bool operator()(const char *a, const char *b){
				return strcmp(a, b) < 0;
			}
		};

		static Map<const char *, int, __smap> _scheme_port;

		URI::URI(){
		}
		
		URI &URI::operator=(const String &uri_str){
			_uri = uri_str;
			parse();
			return *this;
		}
		
		URI::URI(const String &uri){
			_scheme_port.lock();
			if(_scheme_port.size() <= 0){
				_scheme_port["http:"] = DEFAULT_HTTP_PORT;
				_scheme_port["https:"] = DEFAULT_HTTPS_PORT;
				_scheme_port["ftp:"] = DEFAULT_FTP_PORT;
				_scheme_port["h323:"] = DEFAULT_H323_PORT;
				_scheme_port["imap:"] = DEFAULT_IMAP_PORT;
				_scheme_port["smtp:"] = DEFAULT_SMTP_PORT;
				_scheme_port["ldap:"] = DEFAULT_LDAP_PORT;
				_scheme_port["pop:"] = DEFAULT_POP3_PORT;
				_scheme_port["pop3:"] = DEFAULT_POP3_PORT;
				_scheme_port["sip:"] = DEFAULT_SIP_PORT;
				_scheme_port["sips:"] = DEFAULT_SIPS_PORT;
				_scheme_port["snmp:"] = DEFAULT_SNMP_PORT;
			}
			_scheme_port.unlock();
			_uri = uri;
			parse();
		}

		URI::~URI(){
		}
		
		static const char *_scheme_div = ":";

		std::string URI::toString(){
			return std::string(_uri);
		}

		const String &URI::scheme(){
			return _scheme;
		}

		const String &URI::scheme() const {
			return _scheme;
		}

		const String &URI::host(){
			return _host;
		}

		const String &URI::host() const {
			return _host;
		}

		int URI::port(){
			return _port;
		}

		const String &URI::path(){
			return _path;
		}

		const String &URI::path() const {
			return _path;
		}
		const String &URI::paramString(){
			return _param_string;
		}
		
		const String &URI::paramString() const {
			return _param_string;
		}
		
		const String &URI::queryString(){
			return _query_string;
		}
		
		const String &URI::queryString() const {
			return _query_string;
		}
		
		const String &URI::fragment(){
			return _fragment;
		}
		
		const String &URI::fragment() const {
			return _fragment;
		}
		
		const String &URI::user(){
			return _user;
		}
		
		const String &URI::user() const {
			return _user;
		}
		
		const String &URI::password(){
			return _password;
		}
		
		const String &URI::password() const {
			return _password;
		}
		
		void URI::parse(){
			/*              hierarchycal-part
			 *          ____________|____________
			 *         /                         \
			 *   foo://example.com:8042/over/there?name=ferret#nose
      		 *   \_/   \______________/\_________/ \_________/ \__/
      		 *    |          |            |            |        |
      		 * scheme     authority     path          query   fragment
      		 *    |   ____________________|___
      		 *   / \ /                        \
      		 *   urn:example:animal:ferret:nose
      		 */
			size_t pos = 0;
			_scheme.clear();
			_port = -1;
			_path.clear();
			_fragment.clear();
			_query_string.clear();
			_param_string.clear();
			query.lock();
			query.clear();
			query.unlock();
			
			String hier_part;
			String non_hier_part;
			String __uri = _uri;
			
			pos = __uri.find(_scheme_div, 0);
			if(pos == __uri.npos){
				//Path is relative
				if(!__uri.startsWith("//")){
					__uri.insert(0, "//");
				}
				
			}
			else{
				_scheme = __uri.substr(0, pos + 1);
				__uri.biteLeft(pos + 1);
			}
			
			if(__uri.startsWith("//")){
				//Might be an URL
				__uri.biteLeft(2);
				if(__uri.find('?', 0) != __uri.npos){
					xvr2::Tokenizer t1(__uri, "?");
					hier_part = t1.next();
					non_hier_part = t1.next();
				}
				else if(__uri.find('#', 0) != __uri.npos){
					xvr2::Tokenizer t1(__uri, "#");
					hier_part = t1.next();
					non_hier_part = t1.next();
				}
				else{
					hier_part = __uri;
				}
				String address;
				//Now we got hierachical and non-hierarchical parts
				//Process hierarchical part
				if((pos = hier_part.find('/')) != hier_part.npos){
					address = hier_part.substr(0, pos);
					hier_part.biteLeft(pos);
					_path = hier_part;
				}
				else{
					address = hier_part;
				}
				if(address.size() > 0){
					String hostinfo;
					if((pos = address.find('@', 0)) != address.npos){
						Tokenizer t2(address, "@");
						String authinfo = t2.next();
						hostinfo = t2.next();
						if((pos = authinfo.find(':', 0)) == address.npos){
							_user = authinfo;
						}
						else{
							Tokenizer t3(authinfo, ":");
							_user = t3.next();
							_password = t3.next();
						}
					}
					else{
						_user.clear();
						_password.clear();
						hostinfo = address;
					}
					if(hostinfo.size() > 0){
						if(hostinfo.find(':', 0) == address.npos){
							//Only has the ip_address or hostname
							_host = hostinfo;
						}
						else{
							//Has hostname plus port information
							Tokenizer t4(hostinfo, ":");
							_host = t4.next();
							String tmpp = t4.next();
							_port = tmpp.toInt();
						}
					}
				}
				//TODO: Process non-hierarchical part
				if(non_hier_part.size() > 0){
					if(non_hier_part.find('#') == non_hier_part.npos){
						//Does not have a fragment
						_query_string = non_hier_part;
					}
					else{
						//Have a fragment
						Tokenizer t5(non_hier_part, "#");
						_query_string = t5.next();
						_fragment = t5.next();
					}
				}
				
				if(_path.find(';', 0) != _path.npos){
					//Has parameters, retrieve them
					Tokenizer t6(_path, ";");
					_path = t6.next();
					_param_string = t6.next();
				}
			}
			else{
				//Might be an URN
				throw xvr2::Net::URIParseException(_uri, "Resource is not a URI, looks more like a URN");
			}
			if(_scheme.size() > 0){
				_scheme.toLowerCase();
			}
			if(_port == -1){
				_scheme_port.lock();
				_port = _scheme_port[_scheme.c_str()];
				_scheme_port.unlock();
			}
			if(_query_string.size() > 0){
				//Fill in the query map
				Tokenizer t7(_query_string, "&");
				while(!t7.finished()){
					String q1 = t7.next();
					Tokenizer t8(q1, "=");
					try{
						String var = t8.next();
						String val = t8.next();
						query[var] = val;
					}
					catch(NoMoreTokens &nmt){
						StringBuffer sb;
						sb << "Malformed query in URI: " << q1; 
						throw URIParseException(_uri, sb.toString());
					}
				}
			}
		}
		
		URI::QueryMap URI::queryMap(){
			return QueryMap(query);
		}

		URIParseException::URIParseException():ParseException(){
		}
		
		URIParseException::URIParseException(const std::string &_original_text, const std::string _description):ParseException(_original_text){
			description = _description;
		}
	}
}
