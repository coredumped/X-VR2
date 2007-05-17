/* $Id$ */
/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef __XVR2_UTIL_MD5_H__
#define __XVR2_UTIL_MD5_H__
#include<xvr2/String.h>
#include<xvr2/Buffer.h>
#include<xvr2/CoreExceptions.h>
#include<xvr2/Util/ChecksumExceptions.h>

namespace xvr2 {
	namespace Util {

		struct MD5Context {
			UInt32 buf[4];
			UInt32 bits[2];
			UInt8 in[64];
		};

		class MD5Hash : public xvr2::Object {
			protected:
				UInt8 data[16];
			public:
				MD5Hash();
				MD5Hash(UInt8 *_data);
				MD5Hash(const MD5Hash &hash);
				MD5Hash(const String &_data);
				UInt8 operator[](unsigned int idx);
				virtual std::string toString();
		};

		class MD5 : public xvr2::Object {
			protected:
				MD5Context ctx;
				void init();
				void update(unsigned char const *buf, unsigned len);
				void final(UInt8 *_digest);
			public:
				MD5();
				MD5(const String &str);
				MD5Hash digest();
				const MD5 &digest(MD5Hash &hash);
				const MD5 &operator<<(const Buffer &b);
				const MD5 &operator<<(const String &s);
				static MD5Hash digest(const String &str);
				static MD5Hash digest(const String &str, MD5Hash &hash);
		};
		
	};

};

#endif

