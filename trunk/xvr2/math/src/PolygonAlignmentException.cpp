/*
 * $Id$
 */
#include<xvr2/PolygonAlignmentException.h>
#include<xvr2/MessageStrings.h>

namespace xvr2 {
        namespace Exception{
#if GCC_MAJOR_VERSION < 3
		static const char *_xvr2PolygonAlignmentException = "xvr2::Exception::PolygonAlignment";
#endif
		static const char *_xvr2PolygonAlignmentExceptionMsg = "Invalid coordinate width for this polygon, perhaps ncoords has not been initilized yet?";

                PolygonAlignment::PolygonAlignment(){
#if GCC_MAJOR_VERSION < 3
                        setClassName((char *)_xvr2PolygonAlignmentException);
#endif
                        description = (char *)_xvr2PolygonAlignmentExceptionMsg;
                }

        };
};

