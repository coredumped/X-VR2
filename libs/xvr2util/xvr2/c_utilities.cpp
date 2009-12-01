/*
 * $Id$
 */
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include"config.h"
#include<string.h>
#include"c_utilities.h"

void *__xvr2_util_mempcpy(void *to, const void *from, size_t bytes){
	void *ret_ptr;
#ifdef __USE_GNU
	ret_ptr = mempcpy(to, from, bytes);
#else
#ifdef HAVE_MEMCPY
	ret_ptr = (void *)((char *)memcpy(to, from, bytes) + bytes);
#else
	ret_ptr = (void *)((char *)__xvr2_util_memcpy(to, from, bytes) + bytes);
#endif
#endif
	return ret_ptr;
}

void *__xvr2_util_memcpy(void *to, const void *from, size_t bytes){
#ifndef HAVE_MEMCPY
	register size_t i;
#endif
	void *ret_ptr;
#ifdef __USE_GNU
	ret_ptr = memcpy(to, from, bytes);
#else
#ifdef HAVE_MEMCPY
	ret_ptr = memcpy(to, from, bytes);
#else
	for(i = 0; i < bytes; i++){
		*to = *from;
		to++;
		from++;
	}
	ret_ptr = to;
#endif
#endif
	return ret_ptr;
}
