/*
 * $Id$
 */
#ifndef __XVR2_MATH_POLYGON_H__
#define __XVR2_MATH_POLYGON_H__
#include<xvr2/xvr2mathdefs.h>
#include<xvr2/PolygonAlignmentException.h>

namespace xvr2 {
namespace math {

	class Polygon:public xvr2::Object {
		protected:
			int ncoords;
			int nelems;
		public:
			Scalar *p;
			Polygon();
			Polygon(int numcoords);
			Polygon(const Scalar *_points, int numcoords);
			Polygon(const Scalar *_points, int numcoords, int numelem);
			void addPoint(const Scalar *pdata);
			void addData(const Scalar *pdata, int numpoints);
	};

};
};
#endif

