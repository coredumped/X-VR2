/*
 * $Id$
 */
#ifndef __XVR2_NET_DEFS_H__
#define __XVR2_NET_DEFS_H__
namespace xvr2 {
	namespace Net {
		/** \enum SSLConnectionMethod
		 *  SSL Connection methods */
		typedef enum {
			/** SSL version 2 client/server */
			SSL_V2,
			/** SSL version 2 client only */
			SSL_V2_CLIENT,
			/** SSL version 2 server only */
			SSL_V2_SERVER,
			/** SSL version 3 client/server */
			SSL_V3,
			/** SSL version 3 client only */
			SSL_V3_CLIENT,
			/** SSL version 3 server only */
			SSL_V3_SERVER,
			/** SSL version 2 client/server */
			TLS_V1,
			/** SSL version 2 client only */
			TLS_V1_CLIENT,
			/** SSL version 2 server only */
			TLS_V1_SERVER,
			/** SSL version 2 & 3 client/server */
			SSL_V23,
			/** SSL version 2 & 3 client/server */
			SSL_V23_CLIENT,
			/** SSL version 2 & 3 client/server */
			SSL_V23_SERVER	
		} SSLConnectionMethod;

		/** \enum SSLKeyfileType
		 *  SSL Keyfile types */
		typedef enum {
			/** Keyfile is in PEM format */
			KEYFILE_PEM,
			/** Keyfile is in ASN.1 format */
			KEYFILE_ASN1,
			/** Keyfile is in default? format */
			KEYFILE_DEFAULT 
		} SSLKeyfileType;
	};
};
#endif
