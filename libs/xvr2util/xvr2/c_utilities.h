/*
 * $Id$
 */
#ifndef __XVR2_UTILITY_CLIB_FUNCTIONS__
#define __XVR2_UTILITY_CLIB_FUNCTIONS__
#include<sys/types.h>

extern "C" {
	extern void *__xvr2_util_mempcpy(void *to, const void *from, size_t bytes);
	extern void *__xvr2_util_memcpy(void *to, const void *from, size_t bytes);
}

namespace xvr2 {
	namespace Util {
		template<class PtrT>
		inline
		PtrT *mempcpy(const PtrT *to, const PtrT *from, size_t elems){
			PtrT *ret;
			ret = (PtrT *)__xvr2_util_mempcpy(to, from, elems * sizeof(PtrT));
			return ret;
		}

		template<class PtrT>
		inline
		PtrT *memcpy(const PtrT *to, const PtrT *from, size_t elems){
			PtrT *ret;
			ret = (PtrT *)__xvr2_util_memcpy(to, from, elems * sizeof(PtrT));
			return ret;
		}
	};
};

#endif

