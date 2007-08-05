/*
 * $Id$
 */
#include"config.h"
#include<xvr2/xvr2config.h>
#include"_xvr2glClassNames.h"
#include"xvr2/xglDisplayDriver.h"
namespace xvr2 {
namespace GL {
	DisplayDriver::DisplayDriver(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName(__xvr2_GL_DisplayDriver);
#endif
		drv = 0;
	}
	DisplayDriver::DisplayDriver(const String &driver_path){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName(__xvr2_GL_DisplayDriver);
#endif
		drv = new xvr2::DSO(driver_path);
	}
	DisplayDriver::~DisplayDriver(){
		xvr2_delete(drv);
	}
	void *DisplayDriver::init(){
		void *xvrgldrv;
		if(drv != 0){
			try{
				drv->load();
				//Load all exported symbols here
				__ddrv_init = (void *(*)())drv->getSymbol("__ddrv_init");
				__ddrv_setresolution = (void (*)(void *, int, int))drv->getSymbol("__ddrv_setresolution");
				__ddrv_getresolution = (void (*)(void *, int *, int *))drv->getSymbol("__ddrv_setresolution");
				__ddrv_setdepth = (bool (*)(void *, int))drv->getSymbol("__ddrv_setdepth");
				__ddrv_getdepth = (int (*)(void *))drv->getSymbol("__ddrv_getdepth");
				__ddrv_width = (int (*)(void *))drv->getSymbol("__ddrv_width");
				__ddrv_height = (int (*)(void *))drv->getSymbol("__ddrv_height");
				__ddrv_open = (bool (*)(void *, int))drv->getSymbol("__ddrv_open");
				__ddrv_close = (bool (*)(void *))drv->getSymbol("__ddrv_close");
				__ddrv_swapbuffers = (bool (*)(void *))drv->getSymbol("__ddrv_swapbuffers");
				__ddrv_setstereo = (bool (*)(void *, int))drv->getSymbol("__ddrv_setstereo");
				__ddrv_getstereo = (bool (*)(void *))drv->getSymbol("__ddrv_getstereo");
				__ddrv_getlasterror = (const char *(*)(void *))drv->getSymbol("__ddrv_getlasterror");
				/*__ddrv_ = (void *(*)(void *))drv->getSymbol("__ddrv_");
				__ddrv_ = (void *(*)(void *))drv->getSymbol("__ddrv_");
				__ddrv_ = (void *(*)(void *))drv->getSymbol("__ddrv_");*/
				xvrgldrv = __ddrv_init();
			}
			catch(...){
				throw;
			}
		}
		else{
			throw NullPointer();
		}
		return xvrgldrv;
	}

	const char *DisplayDriver::getLastError(void *hnd){
		char *ptr = 0;
		try{
			ptr = (char *)__ddrv_getlasterror(hnd);
		}
		catch(...){
			throw;
		}
		return ptr;
	}
	
	void DisplayDriver::setResolution(void *hnd, int w, int h){
		__ddrv_setresolution(hnd, w, h);
	}
	void DisplayDriver::setDepth(void *hnd, int bpp){
		if(!__ddrv_setdepth(hnd, bpp))
			throw xvr2::Exception();
	}
	int DisplayDriver::depth(void *hnd){
		int d;
		try{
			d = __ddrv_getdepth(hnd);
		}
		catch(...){
			throw;
		}	
		return d;
	}
	int DisplayDriver::width(void *hnd){
		int n;
		try{
			n = __ddrv_width(hnd);
		}
		catch(...){
			throw;
		}	
		return n;
	}
	int DisplayDriver::height(void *hnd){
		int n;
		try{
			n = __ddrv_height(hnd);
		}
		catch(...){
			throw;
		}	
		return n;
	}
	void DisplayDriver::open(void *hnd, bool fullscreen){
		if(!__ddrv_open(hnd, fullscreen))
			throw UnableToOpenGraphicsDevice(this, hnd);
	}
	void DisplayDriver::close(void *hnd){
		if(!__ddrv_close(hnd))
			throw UnableToOpenGraphicsDevice(this, hnd);
	}
	void DisplayDriver::swapBuffers(void *hnd){
		if(!__ddrv_swapbuffers(hnd))
			throw GraphicBufferSwapFailure(this, hnd);
	}
	void DisplayDriver::setStereo(void *hnd, bool onoff){
		if(!__ddrv_setstereo(hnd, onoff))
			throw StereoModeFailure(this, hnd);
	}
	bool DisplayDriver::stereo(void *hnd){
		bool r;
		try{
			r = __ddrv_getstereo(hnd);
		}
		catch(...){
			throw;
		}
		return r;
	}
	/*void DisplayDriver::(){
	}
	void DisplayDriver::(){
	}
	void DisplayDriver::(){
	}
	void DisplayDriver::(){
	} */
};
};
