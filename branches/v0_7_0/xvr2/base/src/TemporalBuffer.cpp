/*
 * $Id$
 */
#include<xvr2/TemporalBuffer.h>
#include<xvr2/Memory.h>
#include<xvr2/Timestamp.h>


namespace xvr2{

	TemporalBuffer::TemporalBuffer(){
#if __GNUC__ < 3
		setClassName(xvr2::_xvr2TemporalBuffer);
#endif
		buffer = 0x0000;
		_timeout = 0;
		_timeout = 0;
	}

	TemporalBuffer::TemporalBuffer(UInt32 size, UInt32 t){
#if __GNUC__ < 3
		setClassName(xvr2::_xvr2TemporalBuffer);
#endif
		alloc(size);
		_timeout = t;
	}

	void *TemporalBuffer::alloc(UInt32 size){
		Timestamp t;
		buffer = Memory::allocBuffer(size);
		started = t.timestamp();
		return buffer;
	}

	void TemporalBuffer::free(){
		Memory::freeBuffer(&buffer);
	}

	UInt32 TemporalBuffer::elapsed(){
		Timestamp t;
		_elapsed = started - t.timestamp();
		return _elapsed;
	}

	UInt32 TemporalBuffer::timeout(){
		return _timeout;
	}
};
