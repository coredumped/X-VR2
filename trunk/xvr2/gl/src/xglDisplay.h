/*
 * $Id$
 */
#ifndef __XVR2_GL_DISPLAY_H__
#define __XVR2_GL_DISPLAY_H__
#include<xvr2/Object.h>
#include<xvr2/String.h>
#include<xglDisplayDriver.h>

namespace xvr2 {
namespace gl {
	/**
	 * Instantiate this class whenever you need to interoperate with the screen
	 * display, in order to use this class you need to call the proper driver.
	 * In order to use this class ypu may follow the example below:
	 * \code
	 * Display *x = new Display("xvr2_sdl_driver.so", 800, 600, 24); //Creates an 800x600
	 * 							//display with 24
	 * 							//bits per pixel
	 *							//display.
	 * x->open();
	 * .
	 * .
	 * .
	 * x->close();
	 * \endcode
	 */
	class Display: public xvr2::Object{
		protected:
			DisplayDriver *drv;
			void *instance;
		public:
			/** Creates a new Display object with no underlying or related
			 * driver, you can use this to implement "dummy" Displays, however
			 * please note that you can only have active display at the time
			 * with the current implementation. */
			Display();
			/** A destructor, this guy, takes care of closing the currently
			 * opened device only if it has been successfully instanciated
			 * from the driver */
			~Display();
			Display(DisplayDriver *_drv);
			Display(const String &driver_path);
			Display(const String &driver_path, int _x, int _y, int bps);
			void setDriver(const String &driver_path);
			void setResolution(int _w, int _h);
			void setDepth(int bitsperpixel);
			const int depth();
			const int width();
			const int height();
			void open(bool fullscreen = false);
			void close();
			void swapBuffers();
			void setStereo(bool on_off = false);
	};
};
};
#endif
