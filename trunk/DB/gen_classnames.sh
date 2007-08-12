#!/bin/bash
# $Id:gen_classnames.sh 531 2007-08-11 09:05:29Z mindstorm2600 $
# Classname sourcefiles generator to be used if your C++ implementation does
# not support method to investigate ck

namespace=db
cpp_namespace=DB

rm -f /tmp/_xvr2_all_classes.tmp
egrep 'class.*{' xvr2/*h | sed 's/.*class[:blank:]*\(.*\):.*/\1/' | tr -s ' ' | sed 's/class \(.*\){/\1/' | cut -f2 -d: | tr -d ' '  | tr -d '\t' | grep -v publicxvr2 | sort -u > /tmp/_xvr2_all_classes.tmp

echo -ne "Generating header"
#Generate header file
echo '/*'				>  xvr2/_xvr2${namespace}ClassNames.h
echo ' * $Id:gen_classnames.sh 531 2007-08-11 09:05:29Z mindstorm2600 $'				>> xvr2/_xvr2${namespace}ClassNames.h
echo ' */'				>> xvr2/_xvr2${namespace}ClassNames.h
echo ' '				>> xvr2/_xvr2${namespace}ClassNames.h
echo "#ifndef __XVR2_${cpp_namespace}_EMDEDDED_CLASS_NAMES_H__"	>> xvr2/_xvr2${namespace}ClassNames.h
echo "#define __XVR2_${cpp_namespace}_EMDEDDED_CLASS_NAMES_H__"	>> xvr2/_xvr2${namespace}ClassNames.h
echo ' '				>> xvr2/_xvr2${namespace}ClassNames.h
echo '#include<xvr2/xvr2config.h>'	>> xvr2/_xvr2${namespace}ClassNames.h
echo ' '				>> xvr2/_xvr2${namespace}ClassNames.h
echo '#ifdef USE_EMBEDDED_CLASSNAMES'	>> xvr2/_xvr2${namespace}ClassNames.h
echo 'namespace xvr2 {'			>> xvr2/_xvr2${namespace}ClassNames.h
echo "	namespace ${cpp_namespace} {"	>> xvr2/_xvr2${namespace}ClassNames.h
echo ' '				>> xvr2/_xvr2${namespace}ClassNames.h
for symbol in `cat /tmp/_xvr2_all_classes.tmp`
do
	echo $symbol | sed "s/\(.*\)/\t\textern const char *__xvr2_${cpp_namespace}_\1;/" >> xvr2/_xvr2${namespace}ClassNames.h
	echo -ne '.'
done
echo ' '				>> xvr2/_xvr2${namespace}ClassNames.h
echo '	};'				>> xvr2/_xvr2${namespace}ClassNames.h
echo '};'				>> xvr2/_xvr2${namespace}ClassNames.h
echo '#endif'				>> xvr2/_xvr2${namespace}ClassNames.h
echo '#endif'				>> xvr2/_xvr2${namespace}ClassNames.h
echo done

echo -ne "Generating source"
echo '/*'				>  xvr2/_xvr2${namespace}ClassNames.cpp
echo ' * $Id:gen_classnames.sh 531 2007-08-11 09:05:29Z mindstorm2600 $'				>> xvr2/_xvr2${namespace}ClassNames.cpp
echo ' */'				>> xvr2/_xvr2${namespace}ClassNames.cpp
echo '#include<xvr2/xvr2config.h>'	>> xvr2/_xvr2${namespace}ClassNames.cpp
echo ' '				>> xvr2/_xvr2${namespace}ClassNames.cpp
echo '#ifdef USE_EMBEDDED_CLASSNAMES'	>> xvr2/_xvr2${namespace}ClassNames.cpp
echo 'namespace xvr2 {'			>> xvr2/_xvr2${namespace}ClassNames.cpp
echo "	namespace ${cpp_namespace} {"	>> xvr2/_xvr2${namespace}ClassNames.cpp
echo ' '				>> xvr2/_xvr2${namespace}ClassNames.cpp
#Generate source file
for symbol in `cat /tmp/_xvr2_all_classes.tmp`
do
	echo -n $symbol | sed "s/\(.*\)/\t\tconst char \*__xvr2_${cpp_namespace}_\1 = \"xvr2::${cpp_namespace}::/" >> xvr2/_xvr2${namespace}ClassNames.cpp
	echo -e "${symbol}\";" >> xvr2/_xvr2${namespace}ClassNames.cpp
	echo -ne '.'
done
echo done
echo ' '				>> xvr2/_xvr2${namespace}ClassNames.cpp
echo '	};'				>> xvr2/_xvr2${namespace}ClassNames.cpp
echo '};'				>> xvr2/_xvr2${namespace}ClassNames.cpp
echo '#endif'				>> xvr2/_xvr2${namespace}ClassNames.cpp
rm -f /tmp/_xvr2_all_classes.tmp
