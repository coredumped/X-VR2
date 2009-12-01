#!/bin/bash
# $Id$
#
# Call this script to autogenerate configure script
# for each of the libraries

LOGFILE=/tmp/_xvr2_autogen_all.tmp.log

for library in `cat COMPILATION_ORDER | grep -v '^\#'`
do
	echo -ne "Autogenerating ${library}..."
	cd $library
	./autogen.sh > $LOGFILE 2>&1
	if [ $? -ne 0 ]; then
		echo
		cat $LOGFILE
		exit 1
	fi
	echo done
	cd ..
done
