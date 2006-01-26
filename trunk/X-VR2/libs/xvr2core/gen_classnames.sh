#!/bin/bash
# $Id$
# Classname sourcefiles generator to be used if your C++ implementation does
# not support method to investigate ck

rm -f /tmp/_xvr2_all_classes.tmp
egrep 'class.*{' xvr2/*h | sed 's/.*class[:blank:]*\(.*\):.*/\1/' | tr -s ' ' | sed 's/class \(.*\){/\1/' | cut -f2 -d: | tr -d ' '  | tr -d '\t' | sort -u > /tmp/_xvr2_all_classes.tmp

echo -ne "Generating header"
#Generate header file
echo '/*'				>  xvr2/_xvr2ClassNames.h
echo ' * $Id$'				>> xvr2/_xvr2ClassNames.h
echo ' */'				>> xvr2/_xvr2ClassNames.h
echo ' '				>> xvr2/_xvr2ClassNames.h
echo '#ifndef __XVR2_EMDEDDED_CLASS_NAMES_H__'	>> xvr2/_xvr2ClassNames.h
echo '#define __XVR2_EMDEDDED_CLASS_NAMES_H__'	>> xvr2/_xvr2ClassNames.h
echo ' '				>> xvr2/_xvr2ClassNames.h
echo '#include<xvr2/xvr2config.h>'	>> xvr2/_xvr2ClassNames.h
echo ' '				>> xvr2/_xvr2ClassNames.h
echo '#ifdef USE_EMBEDDED_CLASSNAMES'	>> xvr2/_xvr2ClassNames.h
echo 'namespace xvr2 {'			>> xvr2/_xvr2ClassNames.h
echo ' '				>> xvr2/_xvr2ClassNames.h
for symbol in `cat /tmp/_xvr2_all_classes.tmp`
do
	echo $symbol | sed 's/\(.*\)/\textern const char *_xvr2\1;/' >> xvr2/_xvr2ClassNames.h
	echo -ne '.'
done
echo ' '				>> xvr2/_xvr2ClassNames.h
echo '};'				>> xvr2/_xvr2ClassNames.h
echo '#endif'				>> xvr2/_xvr2ClassNames.h
echo '#endif'				>> xvr2/_xvr2ClassNames.h
echo done

echo -ne "Generating source"
echo '/*'				>  xvr2/_xvr2ClassNames.cpp
echo ' * $Id$'				>> xvr2/_xvr2ClassNames.cpp
echo ' */'				>> xvr2/_xvr2ClassNames.cpp
echo '#include<xvr2/xvr2config.h>'	>> xvr2/_xvr2ClassNames.cpp
echo ' '				>> xvr2/_xvr2ClassNames.cpp
echo '#ifdef USE_EMBEDDED_CLASSNAMES'	>> xvr2/_xvr2ClassNames.cpp
echo 'namespace xvr2 {'			>> xvr2/_xvr2ClassNames.cpp
echo ' '				>> xvr2/_xvr2ClassNames.cpp
#Generate source file
for symbol in `cat /tmp/_xvr2_all_classes.tmp`
do
	echo -n $symbol | sed 's/\(.*\)/\tconst char \*_xvr2\1 = \"xvr2::/' >> xvr2/_xvr2ClassNames.cpp
	echo -e "${symbol}\";" >> xvr2/_xvr2ClassNames.cpp
	echo -ne '.'
done
echo done
echo ' '				>> xvr2/_xvr2ClassNames.cpp
echo '};'				>> xvr2/_xvr2ClassNames.cpp
echo '#endif'				>> xvr2/_xvr2ClassNames.cpp
rm -f /tmp/_xvr2_all_classes.tmp
