#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include<string.h>
#include<xvr2/c_utilities.h>

void *__xvr2_util_mempcpy(const void *to, const void *from, size_t bytes){
	void *ret_ptr;
#ifdef __USE_GNU
	ret_ptr = mempcpy((void *)to, (void *)from, bytes);
#else
	ret_ptr = memcpy((void *)to, (void *)from, bytes) + bytes;
#endif
	return ret_ptr;
}
