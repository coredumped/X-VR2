/*
 * $Id$
 */
#ifndef __XVR2_GL_DISPLAY_DRIVER_H__
#define __XVR2_GL_DISPLAY_DRIVER_H__
#include<xvr2/Object.h>
#include<xvr2/DSO.h>
#include<xvr2/CoreExceptions.h>
#include<xvr2/GL/xglExceptions.h>

namespace xvr2 {
namespace GL {
	class DisplayDriver: public xvr2::Object{
		protected:
			DSO	 *drv;
			void		*(*__ddrv_init)		(void);
			void		(*__ddrv_setresolution)	(void *, int, int);
			void		(*__ddrv_getresolution)	(void *, int *, int *);
			bool		(*__ddrv_setdepth)	(void *, int);
			int		(*__ddrv_getdepth)	(void *);
			int		(*__ddrv_width)		(void *);
			int		(*__ddrv_height)	(void *);
			bool		(*__ddrv_open)		(void *,int);
			bool		(*__ddrv_close)		(void *);
			bool		(*__ddrv_swapbuffers)	(void *);
			bool		(*__ddrv_setstereo)	(void *,int);
			bool		(*__ddrv_getstereo)	(void *);
			const char	*(*__ddrv_getlasterror)	(void *);
		public:
			DisplayDriver();
			~DisplayDriver();
			DisplayDriver(const String &driver_path);
			void *init();
			void setResolution(void *instance, const int w, const int h);
			void setDepth(void *instance, const int bpp);
			int depth(void *instance);
			int width(void *instance);
			int height(void *instance);
			void open(void *instance, bool fullscreen = false);
			void close(void *instance);
			void swapBuffers(void *instance);
			void setStereo(void *instance, bool on_off = true);
			bool stereo(void *instance);
			const char *getLastError(void *instance);
	};
};
};
#endif
