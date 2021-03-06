/*
 * $Id$
 */
#include"config.h"
#include<xvr2/xvr2config.h>
#include"_xvr2mathClassNames.h"
#include"Vector2.h"
#include<math.h>
#include<sstream>

namespace xvr2 {
	namespace Math {
		Vector2::Vector2(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(__xvr2_Math_Vector2);
#endif
			mag = -1;
		}
		Vector2::Vector2(const Scalar *_c){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(__xvr2_Math_Vector2);
#endif
			c[0] = _c[0];
			c[1] = _c[1];
			mag = -1;
			
		}
		Vector2::Vector2(const Scalar x, const Scalar y){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(__xvr2_Math_Vector2);
#endif
			c[0] = x;
			c[1] = y;
			mag = -1;
		}
		Vector2::~Vector2(){
		}
		Vector2::Vector2(const Vector2 &v){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(__xvr2_Math_Vector2);
#endif
			c[0] = v.c[0];
			c[1] = v.c[1];
			mag = v.mag;
		}
		const Vector2 Vector2::operator! (){
			return Vector2(-c[0], -c[1]);
		}
		const bool   Vector2::operator==(const Vector2 &v){
			if(c[0] == v.c[0] && c[1] == v.c[1])
				return true;
			return false;
		}
		const bool   Vector2::operator!=(const Vector2 &v){
			if(*this == v)
				return false;
			return true;
		}
		const Vector2 Vector2::operator+=(const Vector2 &v){
			c[0] += v.c[0];
			c[1] += v.c[1];
			return *this;
		}
		const Vector2 Vector2::operator-=(const Vector2 &v){
			c[0] -= v.c[0];
			c[1] -= v.c[1];
			return *this;
		}
		const Vector2 Vector2::operator*=(const Scalar  s){
			c[0] *= s;
			c[1] *= s;
			return *this;
		}
		const Vector2 Vector2::unit(){
			Scalar m;
			m = magnitude();
			return Vector2(c[0] / m, c[1] / m);
		}
		const Scalar  Vector2::magnitude(){
			if(mag < 0)
				mag = ::hypotf(c[0], c[1]);
			return mag;
		}
		/*const String *Vector2::toString(){
			String *str;
			str = new String("(");
			str->concat(c[0]);
			str->concat(",");
			str->concat(c[1]);
			str->concat(")");
			return str;
		}*/
		std::string Vector2::toString(){
			std::stringstream buf;
			/*if(string_representation != 0){
				delete string_representation;
				string_representation = 0;
			}*/
			buf << "(" << c[0] << "," << c[1] << ")";
			//string_representation = new std::string(buf.str());
			//return *string_representation;
			return std::string(buf.str());
		}

		static char *__v_open_paren = "(";
		static char *__v_close_paren = ")";
		static char *__v_comma = ",";

		std::ostream& operator<<(std::ostream& stream, Vector2 s){
			stream << __v_open_paren << s.c[0] << __v_comma << s.c[1] << __v_close_paren;
			return stream;
		}
	};
};
