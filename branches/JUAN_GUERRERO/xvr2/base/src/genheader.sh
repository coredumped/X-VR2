echo -ne "Generating global header file with settings..."
rm -f xvr2.h
echo "/*--------------------------------------------------------------------
  This file is auto-generated please don't modify it!!!!

  This software is protected under the terms of the GNU General
  Public License


  Authors:
  		Juan V. Guerrero <coredumped@esolutions4all.com>
 *--------------------------------------------------------------------*/

#ifndef __XVR2_MAIN_HEADER
#define __XVR2_MAIN_HEADER

" > xvr2.h

echo "/*--------------------------------------------------------------------
  This file is auto-generated please don't modify it!!!!

  This software is protected under the terms of the GNU General
  Public License


  Authors:
  		Juan V. Guerrero <coredumped@esolutions4all.com>
 *--------------------------------------------------------------------*/

#ifndef __XVR2_CONFIG_HEADER__
#define __XVR2_CONFIG_HEADER__

/** xvr2 base namespace, it contains basic system objects and calls */
namespace xvr2 {

	/** Base namespace for Database related objects */
	namespace DB {;};

	/** Base namespace for Networking related objects */
	namespace Network {;};

	/** This namespace holds utility related classes and objects like 
	 *  configuration file readers and others.
	 *  Also under this namespace you'll find future additions to xvr2 */
	namespace Util {;};
	/** This namespace is where we group all exception classes */
	namespace Exception {;};
};


" > xvr2config.h

for def in "$@"
do
	echo $def | egrep '\-D' > /dev/null 2>&1
	if [ $? -eq 0 ]; then
		define=`echo "$def" | sed 's/^-D//'`
		echo "#ifndef $define
#define $define
#endif" >> xvr2config.h
	fi
done
echo "#endif" >> xvr2config.h
echo "" >> xvr2.h
echo "#include<xvr2config.h>" >> xvr2.h
for file in `ls *.h | grep -v xvr2 | grep -v '__Destruct'`
do
	echo "#include<$file>" >> xvr2.h
done

echo "#ifdef USE_SDL
#include<SDL.h>
#endif
" >> xvr2.h

echo "
#endif
" >> xvr2.h
echo "done"
