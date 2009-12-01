/*
 * $Id$
 */
#ifndef __XVR2_GFX_VECTOR3_H__
#define __XVR2_GFX_VECTOR3_H__
#include<xvr2/xvr2config.h>
#include<xvr2/String.h>
#include<xvr2/Math/xvr2mathdefs.h>
#include<xvr2/Math/Vector2.h>

namespace xvr2 {
namespace Math {

	/** This class implements 3-D Vectors */
	class Vector3:public xvr2::Object {
		protected:
			Scalar mag;
		public:
			Scalar c[3];
			Vector3();
			Vector3(const Scalar *_c);
			Vector3(const Scalar x, const Scalar y, const Scalar z);
			Vector3(const Vector3 &v);
			Vector3(const Vector2 &v);
			~Vector3();
			const Vector3 operator! ();
			const bool    operator==(const Vector3 &v);
			const bool    operator!=(const Vector3 &v);
			const Vector3 operator+=(const Vector3 &v);
			const Vector3 operator-=(const Vector3 &v);
			const Vector3 operator*=(const Scalar  s);
			const Vector3 unit();
			const Scalar  magnitude();
			//const String *toString();
			std::string toString();
			const Scalar x(){
				return c[0];
			}
			const Scalar y(){
				return c[1];
			}
			const Scalar z(){
				return c[2];
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
	};

	inline const Vector3 operator+(const Vector3 &v1, const Vector3 &v2){
		return Vector3(v1.c[0] + v2.c[0], v1.c[1] + v2.c[1], v1.c[2] + v2.c[2]);
	}

	inline const Vector3 operator-(const Vector3 &v1, const Vector3 &v2){
		return Vector3(v1.c[0] - v2.c[0], v1.c[1] - v2.c[1], v1.c[2] - v2.c[2]);
	}

	inline const Vector3 operator*(const Vector3 &v1, const Scalar s){
		return Vector3(v1.c[0] * s, v1.c[1] * s, v1.c[2] * s);
	}

	inline const Scalar operator*(const Vector3 &v1, const Vector3 &v2){
		return v1.c[0] * v2.c[0] + v1.c[1] * v2.c[1] + v1.c[2] * v2.c[2];
	}

	/** Vectorial cross product
	 *       |  x  y  z |
         * UxV = | Ux Uy Uz |
         *       | Vx Vy Vz | */
	inline const Vector3 cross3 (const Vector3 &u, const Vector3 &v){
		return Vector3(u.c[1] * v.c[2] - u.c[2] * v.c[1], u.c[2] * v.c[0] - u.c[0] * v.c[2], u.c[0] * v.c[1] - u.c[1] * v.c[0]);
	}
};
};

#endif
