/*
 * $Id$
 */
#include"Object3D.h"

namespace xvr2 {
namespace gl {
	using namespace xvr2::math;
	Object3D::Object3D():Vector3(){;}
	Object3D::Object3D(Scalar _x, Scalar _y, Scalar _z):Vector3(_x, _y, _z){;}
	Object3D::Object3D(Scalar *_c):Vector3(_c){;}
};
};
