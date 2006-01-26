/*
 * $Id$
 */
#ifndef __XVR2_MATH_POLYGON_ALIGNMENT_EXCEPTION_H__
#define __XVR2_MATH_POLYGON_ALIGNMENT_EXCEPTION_H__
#include<xvr2/xvr2config.h>
#include<xvr2/Exception.h>

namespace xvr2{
        namespace Math {
                /**
                 * Throw this exception when somebody is trying to add data to a math::Polygon
                 * whose ncoords has not been properly set.
                 */
                class PolygonAlignmentException:public Exception{
                        public:
                                /**
                                 * Default constructor
                                 */
                                PolygonAlignmentException();
                };
        };
};


#endif

