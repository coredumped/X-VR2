/*
 * $Id$
 */
#ifndef __XVR2_GL_3D_OBJECT_H__
#define __XVR2_GL_3D_OBJECT_H__
#include<xvr2/Object.h>
#include<xvr2/Vector3.h>

namespace xvr2 {
	namespace GL {

		class Object3D:public Math::Vector3 {
			public:
				Object3D();
				Object3D(Math::Scalar _x, Math::Scalar _y, Math::Scalar _z);
				Object3D(Math::Scalar *_c);
		};

	};
};

#endif

