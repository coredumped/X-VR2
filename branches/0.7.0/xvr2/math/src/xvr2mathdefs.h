/*
 * $Id$
 */
#ifndef __XVR2_MATH_DEFS_H__
#define __XVR2_MATH_DEFS_H__
#include<xvr2/Object.h>

namespace xvr2 {
namespace math {
	enum coord_comp_enum {
		X, Y, Z, W
	};

	/** Defines a Scalar datatype to be used with Vectors and
	 *  any other non-vectorial quantity */
	typedef float Scalar;

};
};
#endif

