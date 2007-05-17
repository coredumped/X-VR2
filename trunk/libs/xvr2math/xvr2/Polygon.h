/*
 * $Id$
 */
#ifndef __XVR2_MATH_POLYGON_H__
#define __XVR2_MATH_POLYGON_H__
#include<xvr2/xvr2config.h>
#include<xvr2/Math/xvr2mathdefs.h>
#include<xvr2/Math/PolygonAlignmentException.h>

namespace xvr2 {
namespace Math {

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

