/*
 * $Id$
 */
#include"config.h"
#include<xvr2/xvr2config.h>
#include"_xvr2glClassNames.h"
#include"xvr2/Object3D.h"

namespace xvr2 {
	namespace GL {
		Object3D::Object3D():Math::Vector3(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(__xvr2_GL_Object3D);
#endif
		}
		Object3D::Object3D(Math::Scalar _x, Math::Scalar _y, Math::Scalar _z):Math::Vector3(_x, _y, _z){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(__xvr2_GL_Object3D);
#endif
		}
		Object3D::Object3D(Math::Scalar *_c):Math::Vector3(_c){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(__xvr2_GL_Object3D);
#endif
		}
	};
};
