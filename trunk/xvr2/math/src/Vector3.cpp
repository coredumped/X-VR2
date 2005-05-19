/*
 * $Id$
 */
#include"Vector3.h"
#include<math.h>

namespace xvr2 {
namespace math {
	Vector3::Vector3(){
		mag = -1;
	}
	Vector3::Vector3(const Scalar *_c){
		c[0] = _c[0];
		c[1] = _c[1];
		c[2] = _c[2];
		mag = -1;
	}
	Vector3::Vector3(const Scalar x, const Scalar y, const Scalar z){
		c[0] = x;
		c[1] = y;
		c[2] = z;
		mag = -1;
	}
	Vector3::~Vector3(){
	}
	Vector3::Vector3(const Vector3 &v){
		c[0] = v.c[0];
		c[1] = v.c[1];
		c[2] = v.c[2];
	}
	Vector3::Vector3(const Vector2 &v){
		c[0] = v.c[0];
		c[1] = v.c[1];
		c[2] = 0;
	}
	const Vector3 Vector3::operator! (){
		return Vector3(-c[0], -c[1], -c[2]);
	}
	const bool   Vector3::operator==(const Vector3 &v){
		if(c[0] == v.c[0] && c[1] == v.c[1] && c[2] == v.c[2])
			return true;
		return false;
	}
	const bool   Vector3::operator!=(const Vector3 &v){
		if(*this == v)
			return false;
		return true;
	}
	const Vector3 Vector3::operator+=(const Vector3 &v){
		c[0] += v.c[0];
		c[1] += v.c[1];
		c[2] += v.c[2];
		return *this;
	}
	const Vector3 Vector3::operator-=(const Vector3 &v){
		c[0] -= v.c[0];
		c[1] -= v.c[1];
		c[2] -= v.c[2];
		return *this;
	}
	const Vector3 Vector3::operator*=(const Scalar  s){
		c[0] *= s;
		c[1] *= s;
		c[2] *= s;
		return *this;
	}
	const Vector3 Vector3::unit(){
		Scalar m;
		m = magnitude();
		return Vector3(c[0] / m, c[1] / m, c[2] / m);
	}
	const Scalar  Vector3::magnitude(){
		if(mag < 0)
			mag = ::sqrtf(c[0] * c[0] + c[1] * c[1] + c[2] * c[2]);
		return mag;
	}
	const String *Vector3::toString(){
		String *str;
		str = new String("(");
		str->concat(c[0]);
		str->concat(",");
		str->concat(c[1]);
		str->concat(",");
		str->concat(c[2]);
		str->concat(")");
		return str;
	}
};
};
