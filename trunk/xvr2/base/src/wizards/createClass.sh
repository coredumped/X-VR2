#!/bin/bash
#
# Use this wizard to add a new class to the library whenever you need to
#
# $Id$

if [ $# -lt 1 ]; then
	echo "$(basename $0) <NEWCLASS> [DESCRIPTION] [PARENTCLASS]"
	exit 1
fi

classname=$1
description=$2
parentclass=$3

pwd | egrep 'wizards$' > /dev/null 2>&1
if [ $? -eq 0 ]; then
	cd ..
fi

temporal1=`mktemp /tmp/xx-1.XXXXXX`
temporal2=`mktemp /tmp/yy-2.XXXXXX`

####### BEGIN HEADER CREATION ########
cat Class.h.template | sed "s/\<Class\>/${classname}/" > $temporal1
if [ "${parentclass}" ]; then
	cat $temporal1 | sed "s/ParentClass/${parentclass}/" | sed "s/CLASS_H/${classname}_H/" > $temporal2
else
	cat $temporal1 | sed 's/:public ParentClass//' | sed 's/#include<ParentClass.*//' | sed "s/CLASS_H/${classname}_H/" > $temporal2
fi
cat $temporal2 | sed "s/This.*ion.*/${description}/" > $temporal1
cp -vf $temporal1 ${classname}.h
####### END HEADER CREATION ########




###### BEGIN IMPLEMENTATION ########
cat Class.cpp.template | sed "s/\<Class\>/${classname}/g" | sed "s/_xvr2Class/_xvr2${classname}/" > $temporal1
cat $temporal1 | sed "s/ParentClass/${parentclass}/" > $temporal2
cat $temporal2 | sed "s/This.*ion.*/${description}/" > $temporal1
cp -vf $temporal1 ${classname}.cpp
####### END IMPLEMENTATION #########



######## BEGIN CLASS REGISTRATION ########
echo "Registering new class..."
./addClass.sh $classname
######### END CLASS REGISTRATION #########



######## BEGIN CVS REPOSITORY ADDITION ########
echo -ne "Add to cvs repository (y/n)? "
read opt
if [ "${opt}" = 'y' ]; then
	echo "Adding to CVS Repository..."
	cvs add $classname.h $classname.cpp
else
	echo "I wont touch CVS"
fi
######### END CVS REPOSITORY ADDITION #########

#cat ${classname}.h
#cat ${classname}.cpp

rm -f $temporal1
rm -f $temporal2
