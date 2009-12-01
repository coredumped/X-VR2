/*
 * $Id$
 */
#include"config.h"
#include<xvr2/xvr2config.h>
#include<xvr2/MessageStrings.h>
#include"_xvr2mathClassNames.h"
#include"PolygonAlignmentException.h"

namespace xvr2 {
        namespace Math {
		static const char *_xvr2PolygonAlignmentExceptionMsg = "Invalid coordinate width for this polygon, perhaps ncoords has not been initilized yet?";

                PolygonAlignmentException::PolygonAlignmentException(){
#ifdef USE_EMBEDDED_CLASSNAMES
                        setClassName(__xvr2_Math_PolygonAlignmentException);
#endif
                        description = (char *)_xvr2PolygonAlignmentExceptionMsg;
                }

        };
};

