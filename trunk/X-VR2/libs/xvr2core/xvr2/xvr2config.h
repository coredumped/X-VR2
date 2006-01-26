/*--------------------------------------------------------------------
  This software is protected under the terms of the GNU General
  Public License


  Authors:
  		Juan V. Guerrero <mindstorm2600@users.sourceforge.net>
 *--------------------------------------------------------------------*/

#ifndef __XVR2_CONFIG_HEADER__
#define __XVR2_CONFIG_HEADER__

/** xvr2 base namespace, it contains basic system objects and calls */
namespace xvr2 {

	/** Base namespace for Database related objects */
	namespace DB {;};

	/** Base namespace for Networking related objects */
	namespace Net {;};

	/** This namespace holds utility related classes and objects like 
	 *  configuration file readers and others.
	 *  Also under this namespace you'll find future additions to xvr2 */
	namespace Util {;};
	namespace math {;};
	namespace gl {;};
	namespace ui {;};
};

#if __GNUC__ < 3
#define USE_EMBEDDED_CLASSNAMES
#endif

#define ENABLE_XVR2_POSIX_THREADS_SUPPORT 1

#if 1 == 1
	#ifndef USE_POSIX_THREADS
		#define USE_POSIX_THREADS
	#endif
	#ifndef _REENTRANT
		#define _REENTRANT
	#endif
	#ifndef _THREAD_SAFE
		#define _THREAD_SAFE
	#endif
#endif

#if defined (__unix__) || defined (__linux__) || defined (__unix) || defined (__linux)
	#ifndef UNIX_SOCKETS
		#define UNIX_SOCKETS
	#endif
#else
	#undef UNIX_SOCKETS
#endif


#if defined(__linux) || defined(__linux__)

	#ifndef USING_LINUX
		#define USING_LINUX
	#endif
	#ifndef __GNU
		#define __GNU
	#endif
#else
/* Add code for other architectures here */

#endif


#ifndef __XVR2_PREFIX_DIR
#define __XVR2_PREFIX_DIR "/usr/local"
#endif
#ifndef __XVR2_VERSION_STRING
#define __XVR2_VERSION_STRING "0.7.1.0"
#endif
#endif
