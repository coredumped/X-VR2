/*
 * $Id$
 */
#ifndef __XVR2_GFX_VECTOR4_H__
#define __XVR2_GFX_VECTOR4_H__
#include<xvr2/xvr2mathdefs.h>
#include<xvr2/String.h>
#include<xvr2/Vector3.h>

namespace xvr2 {
namespace math {

	/** This class implements 4-D Vectors */
	class Vector4:public xvr2::Object {
		protected:
			Scalar mag;
		public:
			Scalar c[4];
			Vector4();
			Vector4(const Scalar *_c);
			Vector4(const Scalar x, const Scalar y, const Scalar z, const Scalar w = 1.0);
			Vector4(const Vector4 &v);
			Vector4(const Vector3 &v);
			~Vector4();
			const Vector4 operator! ();
			const bool    operator==(const Vector4 &v);
			const bool    operator!=(const Vector4 &v);
			const Vector4 operator+=(const Vector4 &v);
			const Vector4 operator-=(const Vector4 &v);
			const Vector4 operator*=(const Scalar  s);
			const Vector4 unit();
			const Scalar  magnitude();
			const String *toString();
			const Scalar x(){
				return c[0];
			}
			const Scalar y(){
				return c[1];
			}
			const Scalar z(){
				return c[2];
			}
			const Scalar w(){
				return c[3];
			}
			const void setX(const Scalar x){
				c[0] = x;
				mag = -1;
			}
			const void setY(const Scalar y){
				c[1] = y;
				mag = -1;
			}
			const void setZ(const Scalar z){
				c[2] = z;
				mag = -1;
			}
			const void setW(const Scalar w){
				c[3] = w;
				mag = -1;
			}
	};

	inline const Vector4 operator+(const Vector4 &v1, const Vector4 &v2){
		return Vector4(v1.c[0] + v2.c[0], v1.c[1] + v2.c[1], v1.c[2] + v2.c[2], v1.c[3] + v2.c[3]);
	}

	inline const Vector4 operator-(const Vector4 &v1, const Vector4 &v2){
		return Vector4(v1.c[0] - v2.c[0], v1.c[1] - v2.c[1], v1.c[2] - v2.c[2], v1.c[3] - v2.c[3]);
	}

	inline const Vector4 operator*(const Vector4 &v1, const Scalar s){
		return Vector4(v1.c[0] * s, v1.c[1] * s, v1.c[2] * s, v1.c[3] * s);
	}

	inline const Scalar operator*(const Vector4 &v1, const Vector4 &v2){
		return v1.c[0] * v2.c[0] + v1.c[1] * v2.c[1] + v1.c[2] * v2.c[2] + v1.c[3] * v2.c[3];
	}
	
	typedef Vector4 Quaternion;

};
};

#endif

