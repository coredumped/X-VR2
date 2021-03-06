#!/bin/bash
# $Id$
#
# Use this script to compile all libraries

LOGFILE=/tmp/_xvr2_autogen_all.tmp.log

for library in `cat COMPILATION_ORDER | grep -v '^\#'`
do
	cd $library
	if [ ! -f configure ]; then
		echo -ne "\n\nAutogenerating ${library}..."
		./autogen.sh 2>&1 | tee $LOGFILE
		if [ $? -ne 0 ]; then
			echo
			cat $LOGIFLE
			exit 1
		fi
		echo done
		echo -ne "\nConfiguring package $library with parameters: \"${@}\"..."
		./configure "$@" 2>&1 | tee $LOGFILE
		if [ $? -ne 0 ]; then
			echo
			cat $LOGIFLE
			exit 1
		fi
		echo done
	fi
	echo "Compiling ${library}..."
	make
	if [ $? -ne 0 ]; then
		exit 1
	fi
	echo -ne "\n\nDo you wish to install this library ($library) [Y/n] "
	#read yesno
	if [ "$yesno" != 'n' ]; then
		cmd=`which sudo`
		if [ -x ${cmd} ]; then
			sudo make install
			if [ $? -ne 0 ]; then
				exit 1
			fi
		else
			su - root -c make install
			if [ $? -ne 0 ]; then
				exit 1
			fi
		fi
	fi
	cd ..
done
