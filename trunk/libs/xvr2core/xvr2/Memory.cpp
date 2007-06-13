/*
 * $Id$
 */
#include"config.h"
#include"Memory.h"
#include<cstdlib>
#include<string>

#ifndef GC_SCAN_PERIOD
#define GC_SCAN_PERIOD 250
#endif

namespace xvr2{

	Memory::Memory(){
		usingGC = false;
		garbage = 0;
	}
	
	Memory::~Memory(){
		if(usingGC){
			xvr2_delete(garbage);
			usingGC = false;
		}
	}

	void *Memory::allocBuffer(UInt32 size){
		void *ptr;
		ptr = malloc(size);
		if(ptr == 0x0){
			throw AllocationFailed();
		}
#ifndef SPEED_ENHANCE
		((char *)ptr)[0] = 0;
#endif
		return ptr;
	}

	Buffer Memory::alloc(UInt32 size){
		return Buffer((void *)(new UInt8(size)), size, true);
	}

	void Memory::freeBuffer(void **buf){
#ifndef USING_LINUX
		if(buf == 0x0)
			throw NullPointer();
#endif
		free(*buf);
		*buf = 0;
	}

	void *Memory::reallocBuffer(void *buf, UInt32 newsize){
		void *p;
#ifndef USING_LINUX
		if(buf == 0x0)
			throw NullPointer();
#endif
		p = realloc(buf, newsize);
		if(p == 0x0){
			throw ReallocFailed();
		}
		return p;
	}

	void *Memory::temporaryAlloc(UInt32 size, UInt32 timeout){
		if(!usingGC){
			garbage = new AutomatedGC(GC_SCAN_PERIOD);
			usingGC = true;
		}
		TemporalBuffer *buf = new TemporalBuffer(size, timeout);
		garbage->add(buf);
		return buf->buffer;
	}

	void Memory::clearBuffer(void *buf, UInt32 siz, UInt8 value){
		memset(buf, value, siz);
	}

	void *Memory::duplicate(const void *buf, UInt32 siz){
		void *tmp;
		tmp = allocBuffer(siz);
		memcpy(tmp, buf, siz);
		return tmp;
	}

	void Memory::copy(void *dst, const void *src, UInt32 siz){
		memcpy(dst, src, siz);
	}
};
