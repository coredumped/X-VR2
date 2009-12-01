/*
 * $Id$
 */
#ifndef __XVR2_GL_SDL_DRIVER_H__
#define __XVR2_GL_SDL_DRIVER_H__

// Exported symbols for the display driver interface
extern "C" {
	void		*__ddrv_init		(void);
	void		__ddrv_setresolution	(void *, int, int);
	void		__ddrv_getresolution	(void *, int *, int *);
	bool		__ddrv_setdepth		(void *, int);
	int		__ddrv_getdepth		(void *);
	int		__ddrv_width		(void *);
	int		__ddrv_height		(void *);
	bool		__ddrv_open		(void *, int);
	bool		__ddrv_close		(void *);
	bool		__ddrv_swapbuffers	(void *);
	bool		__ddrv_setstereo	(void *, int);
	bool		__ddrv_getstereo	(void *);
	const char	*__ddrv_getlasterror	(void *);
};
#endif
