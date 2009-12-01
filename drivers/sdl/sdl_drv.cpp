/*
 * $Id$
 */
#include<xvr2/Mutex.h>
#include<xvr2/NullPointerException.h>
#include<xglException.h>
#include"sdl_drv.h"
#include<X11/Xlib.h>

struct __drv_instance {
	public:
		int w;
		int h;
		int bpp;
		bool opened;
		bool setup;
		bool stereo;
		char *lasterr;
		__drv_instance(){
			w = 640;
			h = 480;
			bpp = 16;
			setup = false;
			opened = false;
			stereo = false;
		}
};

static __drv_instance _drvi;
#ifdef USE_XLIB
static __drv_instance *_prev_drvi;
#endif
static xvr2::Mutex _drvim;
static SDL_Surface *__sdl_local_screen;

//static const char *__initFailedMsg = "Unable to initialize video subsystem.";
void *__ddrv_init(){
	void *ptr = 0;
	_drvim.lock();
		if(!_drvi.setup){
			if(SDL_Init(SDL_INIT_VIDEO) < 0){
				//If unable to initialize SDL VIDEO
				//subsystem then declare setup to 
				//false and return a null instance
				_drvi.setup = false;
				ptr = 0x00;
			}
			else{
				_drvi.setup = true;
				ptr = (void *)&_drvi;
			}
		}
		else{
			ptr = (void *)&_drvi;
		}
	_drvim.unlock();
	return ptr;
}

void __ddrv_cleanup(void *instance){
	__drv_instance *i;
	_drvim.lock();
		if(i->setup){
			i = (__drv_instance *)instance;
			i->setup = false;
			SDL_Quit();
		}
	_drvim.unlock();
}

static const char *__devAlreadyOpened = "Display device is currently in operation, please close it first";
void __ddrv_setresolution(void *_instance, int _w, int _h){
	__drv_instance *i;
	i = (__drv_instance *)_instance;
	if(!i->opened){
		i->w = _w;
		i->h = _h;
	}
	else{
		i->lasterr = (char *)__devAlreadyOpened;
		throw xvr2::gl::XGLException(i->lasterr);
	}
}

void __ddrv_getresolution(void *_instance, int *_w, int *_h){
	__drv_instance *i;
	i = (__drv_instance *)_instance;
	*_w = i->w;
	*_h = i->h;
}

bool __ddrv_setdepth(void *_instance, int _bpp){
	__drv_instance *i;
	i = (__drv_instance *)_instance;
	if(!i->opened){
		i->bpp = _bpp;
	}
	else{
		i->lasterr = (char *)__devAlreadyOpened;
		throw xvr2::gl::XGLException(i->lasterr);
	}
	return true;
}

int __ddrv_getdepth(void *_instance){
	__drv_instance *i;
	i = (__drv_instance *)_instance;
	return i->bpp;
}

int __ddrv_width(void *_instance){
	__drv_instance *i;
	i = (__drv_instance *)_instance;
	return i->w;
}

int __ddrv_height(void *_instance){
	__drv_instance *i;
	i = (__drv_instance *)_instance;
	return i->h;
}

bool __ddrv_open(void *_instance, int _full){
	int flags;
	__drv_instance *i;
	i = (__drv_instance *)_instance;
	if(i == 0x00)
		throw xvr2::Exception::NullPointer();
	//First get some information about the current video
	//mode
#ifdef USE_XLIB
	if(getenv("DISPLAY")){
		//The application is running under an X session
		//it is most likely that the SDL backend has
		//been compiled against X
		if(_prev_drvi == 0x00){
			Display *xdpy = XOpenDisplay(0x00);
			_prev_drvi = new __drv_instance();
			_prev_drvi->h = XDisplayHeight(xdpy, XDefaultScreen(xdpy));
			_prev_drvi->w = XDisplayWidth(xdpy, XDefaultScreen(xdpy));
			_prev_drvi->bpp = XDefaultDepth(xdpy, XDefaultScreen(xdpy));
			XCloseDisplay(xdpy);
		}
	}
#endif
	flags = SDL_HWSURFACE|SDL_OPENGL|SDL_DOUBLEBUF;
	if(_full){
		flags |= SDL_FULLSCREEN;
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, i->bpp);
	__sdl_local_screen = SDL_SetVideoMode(i->w, i->h, i->bpp, flags);
	if(__sdl_local_screen == 0){
		i->opened = false;
		return false;
	}
	i->opened = true;
	return true;
}

bool __ddrv_close(void *_instance){
	__drv_instance *i;
	i = (__drv_instance *)_instance;
	//Kill SDL
	SDL_Quit();
	//Query current video mode and compare to last saved status
	//if it defers then restart SDL in fullscreen mode and return
	//video to its previous values.
#ifdef USE_XLIB
	if(getenv("DISPLAY")){
		bool correct_video_mode;
		correct_video_mode = false;
		Display *xdpy = XOpenDisplay(0x00);
		if(!(	_prev_drvi->h == XDisplayHeight(xdpy, XDefaultScreen(xdpy)) &&
			_prev_drvi->w == XDisplayWidth(xdpy, XDefaultScreen(xdpy)) &&
			_prev_drvi->bpp == XDefaultDepth(xdpy, XDefaultScreen(xdpy)))){
			correct_video_mode = true;
		}
		XCloseDisplay(xdpy);
		if(!correct_video_mode){
			//Initialize SDL
			SDL_Init(SDL_INIT_VIDEO);
			//Set video mode to the currently set value
			flags = SDL_HWSURFACE | SDL_FULLSCREEN;
			SDL_SetVideoMode(i->w, i->h, i->bpp, flags);
			//DONT CLOSE SDL
		}
	}
#endif
	i->opened = false;
	return true;
}

static const char *__devNotYetOpened = "Display device is not opened";
bool __ddrv_swapbuffers(void *_instance){
	if(((__drv_instance *)_instance)->opened){
		SDL_GL_SwapBuffers();
		return true;
	}
	((__drv_instance *)_instance)->lasterr = (char *)__devNotYetOpened;
	throw xvr2::gl::XGLException(((__drv_instance *)_instance)->lasterr);
	return false;
}

static const char *__devNotStereoCapable = "Display device is not stereo capable";

bool __ddrv_setstereo(void *_instance, int active){
	((__drv_instance *)_instance)->lasterr = (char *)__devNotStereoCapable;
	((__drv_instance *)_instance)->stereo = false;
	return false;
}

bool __ddrv_getstereo(void *_instance){
	((__drv_instance *)_instance)->lasterr = (char *)__devNotStereoCapable;
	((__drv_instance *)_instance)->stereo = false;
	return false;
}

const char *__ddrv_getlasterror	(void *_instance){
	return ((__drv_instance *)_instance)->lasterr;
}

