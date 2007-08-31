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
#include"MD5.h"

namespace xvr2 {
	namespace Util {
////////////////////////// MD5Hash code starts here /////////////////////

		static inline int hex2num(int v){
		        int r;
		        if(v >= '0' && v <= '9')	r = v - '0';
		        else if(v >= 'a' && v <= 'f')	r = v - 'a' + 10;
		        else if(v >= 'A' && v <= 'F')	r = v - 'A' + 10;
		        else throw xvr2::Exception("Not an hex digit");
		        return r;
		}

		MD5Hash::MD5Hash(){
			data[0] = 0;
			data[1] = 0;
			data[2] = 0;
			data[3] = 0;
			data[4] = 0;
			data[5] = 0;
			data[6] = 0;
			data[7] = 0;
			data[8] = 0;
			data[9] = 0;
			data[10] = 0;
			data[11] = 0;
			data[12] = 0;
			data[13] = 0;
			data[14] = 0;
			data[15] = 0;
		}
		MD5Hash::MD5Hash(UInt8 *_data){
			data[0] = _data[0];
			data[1] = _data[1];
			data[2] = _data[2];
			data[3] = _data[3];
			data[4] = _data[4];
			data[5] = _data[5];
			data[6] = _data[6];
			data[7] = _data[7];
			data[8] = _data[8];
			data[9] = _data[9];
			data[10] = _data[10];
			data[11] = _data[11];
			data[12] = _data[12];
			data[13] = _data[13];
			data[14] = _data[14];
			data[15] = _data[15];
		}
		MD5Hash::MD5Hash(const MD5Hash &hash){
			data[0] = hash.data[0];
			data[1] = hash.data[1];
			data[2] = hash.data[2];
			data[3] = hash.data[3];
			data[4] = hash.data[4];
			data[5] = hash.data[5];
			data[6] = hash.data[6];
			data[7] = hash.data[7];
			data[8] = hash.data[8];
			data[9] = hash.data[9];
			data[10] = hash.data[10];
			data[11] = hash.data[11];
			data[12] = hash.data[12];
			data[13] = hash.data[13];
			data[14] = hash.data[14];
			data[15] = hash.data[15];
		}
		MD5Hash::MD5Hash(const String &_data){
			//Verify string length, it should be exactly
			//32 chars long.
			if(_data.size() != 32){
				throw ChecksumingException("Invalid input length.");
			}
			//Read each two chars at a time, then convert each
			//substring assuming they're in hexadecimal form
			int i, j;
			for(i = 0, j = 0; i < 32; i += 2, j++){
				data[j] = (hex2num(_data[i]) << 4) + hex2num(_data[i + 1]);
			}
		}


		UInt8 MD5Hash::operator[](unsigned int idx){
			return data[idx];
		}

		std::string MD5Hash::toString(){
			String str;
			int b1, b2;
			char byte[3];
			byte[2] = 0;
			for(int i = 0; i < 16; i++){
				b1 = (data[i] >> 4);
				b2 = data[i] - (b1 << 4);
				if(b1 > 0x09){
					b1 += 'a' - 10;
				}
				else{
					b1 += '0';
				}
				//b1 = b1 << 4;
				if(b2 > 0x09){
					b2 += 'a' - 10;
				}
				else{
					b2 += '0';
				}
				byte[0] = b1;
				byte[1] = b2;

				str += byte;
			}
			return std::string(str.c_str());
		}
/////////////////////////// MD5Hash code ends here //////////////////////

//////////////////////////// MD5 code starts here ///////////////////////
		static void MD5Transform(UInt32 buf[4], UInt32 const in[16]);
		static void byteReverse(unsigned char *buf, unsigned longs){
			UInt32 t;
			do {
				t = (UInt32) ((unsigned) buf[3] << 8 | buf[2]) << 16 |
				    ((unsigned) buf[1] << 8 | buf[0]);
				*(UInt32 *) buf = t;
				buf += 4;
			} while (--longs);
		}



		void MD5::init(){
			ctx.buf[0] = 0x67452301;
			ctx.buf[1] = 0xefcdab89;
			ctx.buf[2] = 0x98badcfe;
			ctx.buf[3] = 0x10325476;

			ctx.bits[0] = 0;
			ctx.bits[1] = 0;
		}

		void MD5::update(unsigned char const *buf, unsigned len){
			register UInt32 t;
			t = ctx.bits[0];
			if ((ctx.bits[0] = t + ((UInt32) len << 3)) < t)
				ctx.bits[1]++;
			ctx.bits[1] += len >> 29;
			t = (t >> 3) & 0x3f;
			if (t) {
				unsigned char *p = (unsigned char *) ctx.in + t;
				t = 64 - t;
				if (len < t) {
					::memmove(p, buf, len);
					return;
				}
				::memmove(p, buf, t);
				byteReverse(ctx.in, 16);
				MD5Transform(ctx.buf, (UInt32 *) ctx.in);
				buf += t;
				len -= t;
			}
			while (len >= 64) {
				::memmove(ctx.in, buf, 64);
				byteReverse(ctx.in, 16);
				MD5Transform(ctx.buf, (UInt32 *) ctx.in);
				buf += 64;
				len -= 64;
			}
			::memmove(ctx.in, buf, len);
		}

		void MD5::final(UInt8 *_digest){
			unsigned int count;
			unsigned char *p;
			count = (ctx.bits[0] >> 3) & 0x3F;
			p = ctx.in + count;
			*p++ = 0x80;
			count = 64 - 1 - count;
			if (count < 8) {
				memset(p, 0, count);
				byteReverse(ctx.in, 16);
				MD5Transform(ctx.buf, (UInt32 *) ctx.in);
				memset(ctx.in, 0, 56);
			} else {
				memset(p, 0, count - 8);
			}
			byteReverse(ctx.in, 14);
			((UInt32 *) ctx.in)[14] = ctx.bits[0];
			((UInt32 *) ctx.in)[15] = ctx.bits[1];
		
			MD5Transform(ctx.buf, (UInt32 *) ctx.in);
			byteReverse((unsigned char *) ctx.buf, 4);
			::memmove(_digest, ctx.buf, 16);
			::memset((void *)&ctx, 0, sizeof(ctx));
		}


		MD5::MD5(){
			init();
		}

		MD5::MD5(const String &str){
			init();
			update((const unsigned char *)str.toCharPtr(), str.size());
		}

		MD5Hash MD5::digest(){
			UInt8 d[16];
			final(d);
			return MD5Hash(d);
		}

		const MD5 &MD5::digest(MD5Hash &hash){
			UInt8 d[16];
			final(d);
			hash = MD5Hash(d);
			return *this;
		}

		MD5Hash MD5::digest(const String &str){
			MD5 m(str);
			return m.digest();
		}

		MD5Hash MD5::digest(const String &str, MD5Hash &hash){
			MD5 m(str);
			hash = m.digest();
			return hash;
		}
		const MD5 &MD5::operator<<(const Buffer &b){
			update((unsigned char const *)b.data(), b.size());
			return *this;
		}
		const MD5 &MD5::operator<<(const String &s){
			update((unsigned char const *)s.toCharPtr(), s.size());
			return *this;
		}

#define F1(x, y, z) (z ^ (x & (y ^ z)))
#define F2(x, y, z) F1(z, x, y)
#define F3(x, y, z) (x ^ y ^ z)
#define F4(x, y, z) (y ^ (x | ~z))
#define MD5STEP(f, w, x, y, z, data, s) \
	( w += f(x, y, z) + data,  w = w<<s | w>>(32-s),  w += x )

		static void
		MD5Transform(UInt32 buf[4], UInt32 const in[16])
		{
			register UInt32 a, b, c, d;
		
			a = buf[0];
			b = buf[1];
			c = buf[2];
			d = buf[3];
		
			MD5STEP(F1, a, b, c, d, in[0] + 0xd76aa478, 7);
			MD5STEP(F1, d, a, b, c, in[1] + 0xe8c7b756, 12);
			MD5STEP(F1, c, d, a, b, in[2] + 0x242070db, 17);
			MD5STEP(F1, b, c, d, a, in[3] + 0xc1bdceee, 22);
			MD5STEP(F1, a, b, c, d, in[4] + 0xf57c0faf, 7);
			MD5STEP(F1, d, a, b, c, in[5] + 0x4787c62a, 12);
			MD5STEP(F1, c, d, a, b, in[6] + 0xa8304613, 17);
			MD5STEP(F1, b, c, d, a, in[7] + 0xfd469501, 22);
			MD5STEP(F1, a, b, c, d, in[8] + 0x698098d8, 7);
			MD5STEP(F1, d, a, b, c, in[9] + 0x8b44f7af, 12);
			MD5STEP(F1, c, d, a, b, in[10] + 0xffff5bb1, 17);
			MD5STEP(F1, b, c, d, a, in[11] + 0x895cd7be, 22);
			MD5STEP(F1, a, b, c, d, in[12] + 0x6b901122, 7);
			MD5STEP(F1, d, a, b, c, in[13] + 0xfd987193, 12);
			MD5STEP(F1, c, d, a, b, in[14] + 0xa679438e, 17);
			MD5STEP(F1, b, c, d, a, in[15] + 0x49b40821, 22);
		
			MD5STEP(F2, a, b, c, d, in[1] + 0xf61e2562, 5);
			MD5STEP(F2, d, a, b, c, in[6] + 0xc040b340, 9);
			MD5STEP(F2, c, d, a, b, in[11] + 0x265e5a51, 14);
			MD5STEP(F2, b, c, d, a, in[0] + 0xe9b6c7aa, 20);
			MD5STEP(F2, a, b, c, d, in[5] + 0xd62f105d, 5);
			MD5STEP(F2, d, a, b, c, in[10] + 0x02441453, 9);
			MD5STEP(F2, c, d, a, b, in[15] + 0xd8a1e681, 14);
			MD5STEP(F2, b, c, d, a, in[4] + 0xe7d3fbc8, 20);
			MD5STEP(F2, a, b, c, d, in[9] + 0x21e1cde6, 5);
			MD5STEP(F2, d, a, b, c, in[14] + 0xc33707d6, 9);
			MD5STEP(F2, c, d, a, b, in[3] + 0xf4d50d87, 14);
			MD5STEP(F2, b, c, d, a, in[8] + 0x455a14ed, 20);
			MD5STEP(F2, a, b, c, d, in[13] + 0xa9e3e905, 5);
			MD5STEP(F2, d, a, b, c, in[2] + 0xfcefa3f8, 9);
			MD5STEP(F2, c, d, a, b, in[7] + 0x676f02d9, 14);
			MD5STEP(F2, b, c, d, a, in[12] + 0x8d2a4c8a, 20);
		
			MD5STEP(F3, a, b, c, d, in[5] + 0xfffa3942, 4);
			MD5STEP(F3, d, a, b, c, in[8] + 0x8771f681, 11);
			MD5STEP(F3, c, d, a, b, in[11] + 0x6d9d6122, 16);
			MD5STEP(F3, b, c, d, a, in[14] + 0xfde5380c, 23);
			MD5STEP(F3, a, b, c, d, in[1] + 0xa4beea44, 4);
			MD5STEP(F3, d, a, b, c, in[4] + 0x4bdecfa9, 11);
			MD5STEP(F3, c, d, a, b, in[7] + 0xf6bb4b60, 16);
			MD5STEP(F3, b, c, d, a, in[10] + 0xbebfbc70, 23);
			MD5STEP(F3, a, b, c, d, in[13] + 0x289b7ec6, 4);
			MD5STEP(F3, d, a, b, c, in[0] + 0xeaa127fa, 11);
			MD5STEP(F3, c, d, a, b, in[3] + 0xd4ef3085, 16);
			MD5STEP(F3, b, c, d, a, in[6] + 0x04881d05, 23);
			MD5STEP(F3, a, b, c, d, in[9] + 0xd9d4d039, 4);
			MD5STEP(F3, d, a, b, c, in[12] + 0xe6db99e5, 11);
			MD5STEP(F3, c, d, a, b, in[15] + 0x1fa27cf8, 16);
			MD5STEP(F3, b, c, d, a, in[2] + 0xc4ac5665, 23);
		
			MD5STEP(F4, a, b, c, d, in[0] + 0xf4292244, 6);
			MD5STEP(F4, d, a, b, c, in[7] + 0x432aff97, 10);
			MD5STEP(F4, c, d, a, b, in[14] + 0xab9423a7, 15);
			MD5STEP(F4, b, c, d, a, in[5] + 0xfc93a039, 21);
			MD5STEP(F4, a, b, c, d, in[12] + 0x655b59c3, 6);
			MD5STEP(F4, d, a, b, c, in[3] + 0x8f0ccc92, 10);
			MD5STEP(F4, c, d, a, b, in[10] + 0xffeff47d, 15);
			MD5STEP(F4, b, c, d, a, in[1] + 0x85845dd1, 21);
			MD5STEP(F4, a, b, c, d, in[8] + 0x6fa87e4f, 6);
			MD5STEP(F4, d, a, b, c, in[15] + 0xfe2ce6e0, 10);
			MD5STEP(F4, c, d, a, b, in[6] + 0xa3014314, 15);
			MD5STEP(F4, b, c, d, a, in[13] + 0x4e0811a1, 21);
			MD5STEP(F4, a, b, c, d, in[4] + 0xf7537e82, 6);
			MD5STEP(F4, d, a, b, c, in[11] + 0xbd3af235, 10);
			MD5STEP(F4, c, d, a, b, in[2] + 0x2ad7d2bb, 15);
			MD5STEP(F4, b, c, d, a, in[9] + 0xeb86d391, 21);
		
			buf[0] += a;
			buf[1] += b;
			buf[2] += c;
			buf[3] += d;
		}
///////////////////////////// MD5 code ends here ////////////////////////
	};
};

