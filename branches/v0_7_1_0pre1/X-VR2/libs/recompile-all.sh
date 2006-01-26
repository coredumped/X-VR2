#!/bin/bash
# $Id$
#
# Use this script to re-compile all libraries from
# the ground up

LOGFILE=/tmp/_xvr2_autogen_all.tmp.log

for library in `cat COMPILATION_ORDER | grep -v '^\#'`
do
	cd $library
	if [ ! -f configure ]; then
		echo -ne "\n\nAutogenerating ${library}..."
		./autogen.sh > $LOGFILE 2>&1
		if [ $? -ne 0 ]; then
			echo
			cat $LOGIFLE
			exit 1
		fi
		echo done
	fi
	echo -ne "\nConfiguring package $library with parameters: \"${@}\"..."
	./configure "$@" > $LOGFILE 2>&1
	if [ $? -ne 0 ]; then
		echo
		cat $LOGIFLE
		exit 1
	fi
	echo done
	echo "Compiling..."
	make clean
	make
	if [ $? -ne 0 ]; then
		exit 1
	fi
	echo -ne "\n\nDo you wish to install this library ($library) [Y/n] "
	read yesno
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
