/*
 * $Id$
 */
#include"xvr2/xglException.h"
#include"xvr2/xglDisplayDriver.h"

namespace xvr2 {
namespace gl {


	static const char *_xvr2gl_excep = "Undefined X-VR2 GL error";
	static const char *_xvr2gl_excep1 = "Unable to open X-VR2 Graphics device";
	static const char *_xvr2gl_excep2 = "Unable to close X-VR2 Graphics device";
	static const char *_xvr2gl_excep3 = "Graphic page buffer swap failed";
	static const char *_xvr2gl_excep4 = "Unable to set stereo mode on this graphics device or the display device does not supports it.";
	XGLException::XGLException(){
		drv = 0;
		description = (char *)_xvr2gl_excep;
	}

	XGLException::XGLException(const char *m){
		drv = 0;
		description = (char *)m;
	}

	XGLException::XGLException(DisplayDriver *drv, void *hnd){
		description = (char *)drv->getLastError(hnd);
	}

	UnableToOpenGraphicsDevice::UnableToOpenGraphicsDevice(DisplayDriver *drv, void *hnd):XGLException(drv, hnd){
	}

	UnableToOpenGraphicsDevice::UnableToOpenGraphicsDevice():XGLException(_xvr2gl_excep1){
	}

	UnableToCloseGraphicsDevice::UnableToCloseGraphicsDevice(DisplayDriver *drv, void *hnd):XGLException(drv, hnd){
	}

	UnableToCloseGraphicsDevice::UnableToCloseGraphicsDevice():XGLException(_xvr2gl_excep2){
	}

	GraphicBufferSwapFailure::GraphicBufferSwapFailure(DisplayDriver *drv, void *hnd):XGLException(drv, hnd){
	}

	GraphicBufferSwapFailure::GraphicBufferSwapFailure():XGLException(_xvr2gl_excep3){
	}

	StereoModeFailure::StereoModeFailure(DisplayDriver *drv, void *hnd):XGLException(drv, hnd){
	}

	StereoModeFailure::StereoModeFailure():XGLException(_xvr2gl_excep4){
	}
};
};
