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
#ifndef __XVR2_NET_URI_H__
#define __XVR2_NET_URI_H__
#include<xvr2/String.h>
#include<xvr2/Map.h>

namespace xvr2 {

	namespace Net {
	
		/** Uniform Resource Identifier class. Use when in need to break
		 *  down a URI's components.
		 *  Basically a URI is a string like this:
		 *  @verbatim
		 *    foo://username:password@example.com:8042/over/there/index.dtb;type=animal?name=ferret#nose
		 *    \ /   \________________/\_________/ \__/\_________/ \___/ \_/ \_________/ \_________/ \__/
		 *     |           |               |        |     |        |     |         |           |     |
		 *   scheme     userinfo       hostname  port  path  filename extension parameter(s) query fragment
		 *          \_______________________________/
		 *                      authority
  		 *  @endverbatim
		 *  So this class purpose is to leverage the taks of parsing a complex
		 *  URI into the above components as easy as possible. */
		class URI : public Object {
			private:
				/** Will parse the contents of _uri in order to obtain all
				 *  its components. */
				void parse();
			public:
				struct _cmpf {
					bool operator()(const String &a, const String &b){
						return strcmp(a.toCharPtr(), b.toCharPtr()) < 0;
					}
				};
				typedef Map<String, String, _cmpf> QueryMap;
				typedef QueryMap::iterator QueryMapIterator;
			protected:
				String _uri;
				String _scheme;
				String _user;
				String _password;
				String _host;
				String _query_string;
				String _param_string;
				String _fragment;
				int _port;
				String _path;
				QueryMap query;
			public:
				/** Default constructor, initializes an empty URI */
				URI();
				/** Initializes a URI object from a xvr2::String containing an uri. */
				URI(const String &uri);
				~URI();
				/** Returns the uri's scheme after a successful parse. */
				const String &scheme();
				/** Returns the uri's scheme after a successful parse. */
				const String &scheme() const;
				/** Retrieves the host part on a uri. */
				const String &host();
				/** Retrieves the host part on a uri. */
				const String &host() const;
				/** Retrieves the port specified in the URI. In case no port is
				 *  specified X-VR2 will to guess it from a list of known
				 *  schemes. */
				int port();
				/** Returns the associated path in the URI. Sometimes a URI
				 *  lacks a path so it is possible to have an empty path, like
				 *  in @verbatim http://example.com @endverbatim */
				const String &path();
				/** Returns the associated path in the URI. Sometimes a URI
				 *  lacks a path so it is possible to have an empty path, like
				 *  in @verbatim http://example.com @endverbatim. */
				const String &path() const ;
				/** Returns a string containing a list of URI parameters, not
				 *  to be confused with the query string which is the one
				 *  that comes after ? (question mark sign).
				 *  It is not very common to the a param string in an URI, in
				 *  fact I've never seen it before so most of the time this 
				 *  method will return an empty String. */
				const String &paramString();
				/** Returns a string containing a list of URI parameters, not
				 *  to be confused with the query string which is the one
				 *  that comes after ? (question mark sign).
				 *  It is not very common to the a param string in an URI, in
				 *  fact I've never seen it before so most of the time this 
				 *  method will return an empty String. */
				const String &paramString() const;
				/** Returns the query string on an URI which is the portion
				 *  that comes after the ? (question mark sign).
				 *  This method returns the string as is, however if you need
				 *  to have it broke down, you may better take a look at the
				 *  queryMap method. */
				const String &queryString();
				/** Returns the query string on an URI which is the portion
				 *  that comes after the ? (question mark sign).
				 *  This method returns the string as is, however if you need
				 *  to have it broke down, you may better take a look at the
				 *  queryMap method. */
				const String &queryString() const;
				/** Returns the fragment portion in the URI. A URI allows to
				 *  specify an offset from where to start displaying or reading
				 *  the addressed document, this is called, the fragment. */
				const String &fragment();
				/** Returns the fragment portion in the URI. A URI allows to
				 *  specify an offset from where to start displaying or reading
				 *  the addressed document, this is called, the fragment. */
				const String &fragment() const;
				/** Retrieves the username from the authority section. Not
				 *  everytime the authority section contains a username and
				 *  password in the URI, for HTTP this practice is being phased
				 *  out more and more. */
				const String &user();
				/** Retrieves the username from the authority section. Not
				 *  everytime the authority section contains a username and
				 *  password in the URI, for HTTP this practice is being phased
				 *  out more and more. */
				const String &user() const;
				/** Retrieves the password from the authority section. Not
				 *  everytime the authority section contains a username and
				 *  password in the URI, for HTTP this practice is being phased
				 *  out more and more. */
				const String &password();
				/** Retrieves the password from the authority section. Not
				 *  everytime the authority section contains a username and
				 *  password in the URI, for HTTP this practice is being phased
				 *  out more and more. */				
				const String &password() const;
				/** Returns a string representation of this URI object. */
				virtual std::string toString();
				/** Allows to change the contents of this URI by assigning it
				 *  a String to be parsed thereafter. */
				URI &operator=(const String &uri_str);
				/** Returns a Map containing the parameter and value of a query
				 *  string.
				 *  The returned Map contains as key the parameter of the query
				 *  and its value would be the expression value, you may very
				 *  well iterate trough the contents of the Map in order to
				 *  obtain both.
				 *  @example uritest.cpp */
				URI::QueryMap queryMap();
		};
	
		class URIParseException : public xvr2::ParseException {
			private:
			protected:
			public:
				URIParseException();
				URIParseException(const std::string &_original_text, const std::string _description);
				const std::string &text();
				const std::string &text() const;
		};
	}

}

#endif /*URI_H_*/
