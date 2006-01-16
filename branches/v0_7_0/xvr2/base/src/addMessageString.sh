#!/bin/sh
#
# This utility will generate the appropiate output
# for newly created massage strings
#

function usage(){
	echo "Usage:"
	echo -ne "\t${0} <VARIABLE_NAME> <MESSAGE_STRING>\n"
}

if [ "$#" -le 1 ]; then
	usage
else

desc=$2

cat MessageStrings.h | sed '$d' | sed '$d' | sed '$d' > /tmp/$1.e.h.tmp.newclass
echo "
	extern const char *${1};
};

#endif" >> /tmp/$1.e.h.tmp.newclass
cp     -vf /tmp/$1.e.h.tmp.newclass MessageStrings.h



cat MessageStrings.cpp | sed '$d'  > /tmp/$1.e.cpp.tmp.newclass
echo "
	const char *${1} = \"${desc}\";
};" >> /tmp/$1.e.cpp.tmp.newclass
cp -vf /tmp/$1.e.cpp.tmp.newclass MessageStrings.cpp


fi
