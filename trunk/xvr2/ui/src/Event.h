/*
 * $Id$
 */
#include<xvr2/Object3D.h>
#include<xvr2/Vector3.h>

namespace xvr2 {
namespace ui {
	using namespace xvr2::gl;
	using namespace xvr2::math;
	class Event : public Object3D {
		private:
		protected:
		public:
			Event();
			Event(Scalar x, Scalar y, Scalar z);
			Event(Scalar *_coords);
	};
};
};
