rm -f *.h
echo -ne "Generating global header file with settings..."
rm -f xvr2.h
echo "/*--------------------------------------------------------------------
  This file is auto-generated please don't modify it!!!!

  This software is protected under the terms of the GNU General
  Public License


  Authors:
  		Juan V. Guerrero <mindstorm2600@users.sourceforge.net>
 *--------------------------------------------------------------------*/

#ifndef __XVR2_MAIN_HEADER
#define __XVR2_MAIN_HEADER

" > xvr2.h

echo "/*--------------------------------------------------------------------
  This file is auto-generated please don't modify it!!!!

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
		echo $define | grep ' '
		if [ $? -eq 0 ]; then
			definexxx=`echo $define | cut -f1 -d' '`
		else
			definexxx=$define
		fi
		echo "#ifndef $definexxx" >> xvr2config.h
		echo "#define $define
#endif" >> xvr2config.h
	fi
done
echo "#endif" >> xvr2config.h
echo "" >> xvr2.h
echo "#include<xvr2config.h>" >> xvr2.h
for file in `find ../ -name "*.h" | grep -v "/xvr2" | grep -v '__Destruct' | grep -v drivers | grep -v parser`
do
	echo $file | egrep '\.\./demos' > /dev/null
	if [ $? -eq 0 ]; then
		echo -ne '.'
	else
		filex=`basename $file`
		echo "#include<xvr2/$filex>" >> xvr2.h
	fi
done

echo "#ifdef USE_SDL
#include<SDL.h>
#endif
" >> xvr2.h

echo "
#endif
" >> xvr2.h
echo "done"
