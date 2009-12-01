#!/bin/sh
#
# This utility will generate the appropiate output
# for newly created classes
#

function usage(){
	echo "Usage:"
	echo -ne "\t$0 <NEW_CLASS>\n"
}

if [ "$#" -le 0 ]; then
	usage
else

cat _xvr2ClassNames.h | sed '$d' | sed '$d' | sed '$d'  > /tmp/$1.e.h.tmp.newclass
echo "
	extern const char *_xvr2${1};
#endif
};
#endif"  >> /tmp/$1.e.h.tmp.newclass
#cp -vf /tmp/$1.e.h.tmp.newclass _xvr2ClassNames.h


cat _xvr2ClassNames.cpp | sed '$d' | sed '$d' > /tmp/$1.e.cpp.tmp.newclass
echo "
	const char *_xvr2${1} = \"${1}\";
#endif
};" >> /tmp/$1.e.cpp.tmp.newclass
#cp -vf /tmp/$1.e.cpp.tmp.newclass _xvr2ClassNames.cpp


fi
