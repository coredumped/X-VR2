/*
 * $Id$
 */
#include"Vector4.h"
#include<math.h>

namespace xvr2 {
namespace math {
	Vector4::Vector4(){
		mag = -1;
	}
	Vector4::Vector4(const Scalar *_c){
		c[0] = _c[0];
		c[1] = _c[1];
		c[2] = _c[2];
		c[3] = _c[3];
		mag = -1;
	}
	Vector4::Vector4(const Scalar x, const Scalar y, const Scalar z, const Scalar w){
		c[0] = x;
		c[1] = y;
		c[2] = z;
		c[3] = w;
		mag = -1;
	}
	Vector4::~Vector4(){
	}
	Vector4::Vector4(const Vector4 &v){
		c[0] = v.c[0];
		c[1] = v.c[1];
		c[2] = v.c[2];
		c[3] = v.c[3];
	}
	Vector4::Vector4(const Vector3 &v){
		c[0] = v.c[0];
		c[1] = v.c[1];
		c[2] = v.c[2];
		c[3] = 1.0;
	}
	const Vector4 Vector4::operator! (){
		return Vector4(-c[0], -c[1], -c[2], -c[3]);
	}
	const bool   Vector4::operator==(const Vector4 &v){
		if(c[0] == v.c[0] && c[1] == v.c[1] && c[2] == v.c[2] && c[3] == v.c[3])
			return true;
		return false;
	}
	const bool   Vector4::operator!=(const Vector4 &v){
		if(*this == v)
			return false;
		return true;
	}
	const Vector4 Vector4::operator+=(const Vector4 &v){
		c[0] += v.c[0];
		c[1] += v.c[1];
		c[2] += v.c[2];
		c[3] += v.c[3];
		return *this;
	}
	const Vector4 Vector4::operator-=(const Vector4 &v){
		c[0] -= v.c[0];
		c[1] -= v.c[1];
		c[2] -= v.c[2];
		c[3] -= v.c[3];
		return *this;
	}
	const Vector4 Vector4::operator*=(const Scalar  s){
		c[0] *= s;
		c[1] *= s;
		c[2] *= s;
		c[3] *= s;
		return *this;
	}
	const Vector4 Vector4::unit(){
		Scalar m;
		m = magnitude();
		return Vector4(c[0] / m, c[1] / m, c[2] / m, c[3] / m);
	}
	const Scalar  Vector4::magnitude(){
		if(mag < 0)
			mag = ::sqrtf(c[0] * c[0] + c[1] * c[1] + c[2] * c[2] + c[3] * c[3]);
		return mag;
	}
	const String *Vector4::toString(){
		String *str;
		str = new String("(");
		str->concat(c[0]);
		str->concat(",");
		str->concat(c[1]);
		str->concat(",");
		str->concat(c[2]);
		str->concat(",");
		str->concat(c[3]);
		str->concat(")");
		return str;
	}
};
};
