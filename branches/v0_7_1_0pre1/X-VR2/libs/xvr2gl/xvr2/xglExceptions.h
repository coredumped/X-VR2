/*
 * $Id$
 */
#ifndef __XVR2_GL_EXCEPTION_H__
#define __XVR2_GL_EXCEPTION_H__
#include<xvr2/Exception.h>


namespace xvr2 {
namespace GL {
	class DisplayDriver;

	class XGLException:public xvr2::Exception::Exception {
		protected:
			DisplayDriver *drv;
		public:
			XGLException();
			XGLException(const char *msg);
			XGLException(DisplayDriver *drv, void *hnd);
	};

	class UnableToOpenGraphicsDevice:public XGLException {
		public:
			UnableToOpenGraphicsDevice();
			UnableToOpenGraphicsDevice(DisplayDriver *drv, void *hnd);
	};

	class UnableToCloseGraphicsDevice:public XGLException {
		public:
			UnableToCloseGraphicsDevice();
			UnableToCloseGraphicsDevice(DisplayDriver *drv, void *hnd);
	};

	class GraphicBufferSwapFailure:public XGLException {
		public:
			GraphicBufferSwapFailure();
			GraphicBufferSwapFailure(DisplayDriver *drv, void *hnd);
	};

	class StereoModeFailure:public XGLException {
		public:
			StereoModeFailure();
			StereoModeFailure(DisplayDriver *drv, void *hnd);
	};
};
};
#endif
