/*
 * $Id$
 */
#include"config.h"
#include<xvr2/xvr2config.h>
#include"_xvr2glClassNames.h"
#include"xglExceptions.h"
#include"xglDisplayDriver.h"

namespace xvr2 {
namespace GL {


	static const char *_xvr2gl_excep = "Undefined X-VR2 GL error";
	static const char *_xvr2gl_excep1 = "Unable to open X-VR2 Graphics device";
	static const char *_xvr2gl_excep2 = "Unable to close X-VR2 Graphics device";
	static const char *_xvr2gl_excep3 = "Graphic page buffer swap failed";
	static const char *_xvr2gl_excep4 = "Unable to set stereo mode on this graphics device or the display device does not supports it.";
	XGLException::XGLException(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName(__xvr2_GL_XGLException);
#endif
		drv = 0;
		description = (char *)_xvr2gl_excep;
	}

	XGLException::XGLException(const char *m){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName(__xvr2_GL_XGLException);
#endif
		drv = 0;
		description = (char *)m;
	}

	XGLException::XGLException(DisplayDriver *drv, void *hnd){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName(__xvr2_GL_XGLException);
#endif
		description = (char *)drv->getLastError(hnd);
	}

	UnableToOpenGraphicsDevice::UnableToOpenGraphicsDevice(DisplayDriver *drv, void *hnd):XGLException(drv, hnd){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName(__xvr2_GL_UnableToOpenGraphicsDevice);
#endif
	}

	UnableToOpenGraphicsDevice::UnableToOpenGraphicsDevice():XGLException(_xvr2gl_excep1){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName(__xvr2_GL_UnableToOpenGraphicsDevice);
#endif
	}

	UnableToCloseGraphicsDevice::UnableToCloseGraphicsDevice(DisplayDriver *drv, void *hnd):XGLException(drv, hnd){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName(__xvr2_GL_UnableToCloseGraphicsDevice);
#endif
	}

	UnableToCloseGraphicsDevice::UnableToCloseGraphicsDevice():XGLException(_xvr2gl_excep2){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName(__xvr2_GL_UnableToCloseGraphicsDevice);
#endif
	}

	GraphicBufferSwapFailure::GraphicBufferSwapFailure(DisplayDriver *drv, void *hnd):XGLException(drv, hnd){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName(__xvr2_GL_GraphicBufferSwapFailure);
#endif
	}

	GraphicBufferSwapFailure::GraphicBufferSwapFailure():XGLException(_xvr2gl_excep3){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName(__xvr2_GL_GraphicBufferSwapFailure);
#endif
	}

	StereoModeFailure::StereoModeFailure(DisplayDriver *drv, void *hnd):XGLException(drv, hnd){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName(__xvr2_GL_StereoModeFailure);
#endif
	}

	StereoModeFailure::StereoModeFailure():XGLException(_xvr2gl_excep4){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName(__xvr2_GL_StereoModeFailure);
#endif
	}
};
};
