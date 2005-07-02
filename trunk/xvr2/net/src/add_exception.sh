#!/bin/bash
#
# $Id$
#
if [ "$#" -lt 1 ]; then
	echo "Usage:"
	echo -e "\t$0 <exception_classname> [exception_parent_classname]\n"
fi
name=$1

if [ "$2" = "" ]; then
	parent="Network"
else
	parent=$2
fi

include=${name}Exception.h
sourcecpp=${name}Exception.cpp

defname="${name}_EXCEPTION"

echo "/*
 * \$Id\$
 */
#ifndef __XVR2_NET_${defname}_H__
#define __XVR2_NET_${defname}_H__
#include<xvr2/Exception.h>
#include<xvr2/IOException.h>
#include<xvr2/NetworkException.h>
namespace xvr2 {
	namespace Exception{

		class ${name}:public ${parent}{
			public:
				/** Default constructor */
				${name}();
		};

	};
};
#endif
" > ${include}

echo "/*
 * \$Id\$
 */
#include<xvr2/${include}>

namespace xvr2 {
	namespace Exception{
#ifndef USING_GCC3
		static const char *_local_class_name_${name} = \"xvr2::Exception::${name}\";
#endif
		static const char *_desc_${name} = \"${name} exception thrown\";

		${name}::${name}(){
#ifndef USING_GCC3
			setClassName((char *)_local_class_name_${name});
#endif
			description = (char *)_desc_${name};
		}
	};
};
" > ${sourcecpp}
