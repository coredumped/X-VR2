/*
 * $Id$
 */
#ifndef __XVR2_GL_3D_OBJECT_H__
#define __XVR2_GL_3D_OBJECT_H__
#include<xvr2/Object.h>
#include<xvr2/Vector3.h>

namespace xvr2 {
namespace gl {
	using namespace xvr2::math;
	class Object3D:public Vector3 {
		public:
			Object3D();
			Object3D(Scalar _x, Scalar _y, Scalar _z);
			Object3D(Scalar *_c);
	};
};
};

#endif

