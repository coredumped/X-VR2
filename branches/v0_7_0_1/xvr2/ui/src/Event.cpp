/*
 * $Id$
 */
#include<xvr2/Event.h>

namespace xvr2 {
namespace ui {
	using namespace xvr2::math;
	Event::Event(){;}
	Event::Event(Scalar x, Scalar y, Scalar z):Object3D(x, y, z){ 
	}
	Event::Event(Scalar *_coords):Object3D(_coords){ 
	}
};
};
