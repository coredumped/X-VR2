#!/bin/sh
#
# This utility will generate the appropiate output
# for newly created exceptions
#

function usage(){
	echo "Usage:"
	echo -ne "\taddException.sh <NEW_EXCEPTION> <PARENT_CLASS>\n"
}

if [ "$#" -le 0 ]; then
	usage
else
	#cat Exception.h | sed '$d' | sed '$d' | sed '$d' > /tmp/$1.h.tmp.newclass

	printf "Description: "
	read desc
	echo "/*
 * \$Id\$
 */
#include<Exception.h>
#include<${2}Exception.h>
#ifndef __xvr2_${1}Exception_H__
#define __xvr2_${1}Exception_H__

namespace xvr2 {
	/**
	 * \\class ${1}Exception
	 * \\version \$Revision\$
	 * \\brief $desc
	 */
	class ${1}Exception:public ${2}Exception{
		public:
			/**
			 * Default constructor
			 */
			${1}Exception();
	};

};
#endif
" >> /tmp/$1.h.tmp.newclass

cp -vf /tmp/$1.h.tmp.newclass ${1}Exception.h



#cat Exception.cpp | sed '$d' > /tmp/$1.cpp.tmp.newclass
	echo "/*
 * \$Id\$
 */
#include<${1}Exception.h>
#include<MessageStrings.h>

namespace xvr2{

	${1}Exception::${1}Exception(){
		setClassName((char *)xvr2::_xvr2${1}Exception);
		description = (char *)xvr2::excep${1};
	}

};"   >> /tmp/$1.cpp.tmp.newclass
cp -vf   /tmp/$1.cpp.tmp.newclass ${1}Exception.cpp







cat MessageStrings.h | sed '$d' | sed '$d' | sed '$d' > /tmp/$1.e.h.tmp.newclass
echo "
	extern const char *excep${1};
};

#endif" >> /tmp/$1.e.h.tmp.newclass
cp     -vf /tmp/$1.e.h.tmp.newclass MessageStrings.h



cat MessageStrings.cpp | sed '$d'  > /tmp/$1.e.cpp.tmp.newclass
echo "
	const char *excep${1} = \"${desc}\";
};" >> /tmp/$1.e.cpp.tmp.newclass
cp -vf /tmp/$1.e.cpp.tmp.newclass MessageStrings.cpp






cat _xvr2ClassNames.h | sed '$d' | sed '$d'  > /tmp/$1.e.h.tmp.newclass
echo "
	extern const char *_xvr2${1}Exception;
};
#endif"  >> /tmp/$1.e.h.tmp.newclass
cp -vf /tmp/$1.e.h.tmp.newclass _xvr2ClassNames.h





cat _xvr2ClassNames.cpp | sed '$d' > /tmp/$1.e.cpp.tmp.newclass
echo "
	const char *_xvr2${1}Exception = \"${1}Exception\";
};" >> /tmp/$1.e.cpp.tmp.newclass
cp -vf /tmp/$1.e.cpp.tmp.newclass _xvr2ClassNames.cpp


fi
