/*
 * $Id$
 * To be thrown when you are trying to write data in a buffer whose storage size is too small
 */
#ifndef __XVR2_BUFFERTOOSMALL_H__
#define __XVR2_BUFFERTOOSMALL_H__
#include<Exception.h>

namespace xvr2 {
	namespace Exception {
				/**
				 * \class BufferTooSmall BufferTooSmall.h
				 * To be thrown when you are trying to write data in a buffer whose storage size is too small
				 */
                class BufferTooSmall:public Exception{
                        public:
                                /**
                                 * Default constructor
                                 */
                                BufferTooSmall();
                };
	};
};

#endif
