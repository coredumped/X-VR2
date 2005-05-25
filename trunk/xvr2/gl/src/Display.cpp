/*
 * $Id$
 */
#include<xglDisplay.h>


namespace xvr2 {
namespace gl {
	Display::Display(){
		drv = 0;
		instance = 0;
	}
	Display::~Display(){
		if(instance){
			this->close();
		}
		xvr2_delete(drv);
	}
	Display::Display(DisplayDriver *_drv){
		drv = _drv;
	}
	Display::Display(const String &driver_path){
		drv = new DisplayDriver(driver_path);
		instance = drv->init();
	}
	Display::Display(const String &driver_path, int _x, int _y, int bps){
		drv = new DisplayDriver(driver_path);
		instance = drv->init();
		setResolution(_x, _y);
		setDepth(bps);
	}
	void Display::setDriver(const String &driver_path){
		drv = new DisplayDriver(driver_path);
		instance = drv->init();
	}
	void Display::setResolution(int _w, int _h){
		drv->setResolution(instance, _w, _h);
	}
	void Display::setDepth(int bitsperpixel){
		drv->setDepth(instance, bitsperpixel);
	}
	const int Display::depth(){
		return drv->depth(instance);
	}
	const int Display::width(){
		return drv->width(instance);
	}
	const int Display::height(){
		return drv->height(instance);
	}
	void Display::open(bool f){
		drv->open(instance, f);
	}
	void Display::close(){
		drv->close(instance);
	}
	void Display::swapBuffers(){
		drv->swapBuffers(instance);
	}
	void Display::setStereo(bool on_off){
		drv->setStereo(instance, on_off);
	}
};
};
