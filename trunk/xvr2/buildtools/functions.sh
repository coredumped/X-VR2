#
# $Id$
# Common functions to be used within the configure scripts
#

STANDARD_BIN_PATHS="/opt/sfw/bin:/bin:/usr/bin:/usr/local/bin:/sbin:/usr/sbin:/usr/local/sbin:${HOME}/bin"

stage1=`dirname $0`
if [ "$stage1" = "." ]; then
	stage1=`pwd`
else
	echo $stage1 | grep '^\./' > /dev/null 2>&1
	if [ $? -eq 0 ]; then
		stage1=`pwd`
	else
		echo $stage1 | grep '/' > /dev/null 2>&1
		if [ $? -ne 0 ]; then
			stage1=`pwd`
		fi
	fi
fi
echo $stage1 | grep 'xvr2$' > /dev/null 2>&1
if [ $? -eq 0 ]; then
	XVR2_SOURCE_DIR=$stage1
else
	XVR2_SOURCE_DIR=`dirname $stage1`
fi


find_binary()
{
	binname=$1
	echo -ne "Checking ${binname}... " >&2
	#FIRST SEE IF THE FILE IS ALREADY IN THE CACHE, IF IT IS THEN GRAB IT FROM THERE
	if [ -f .build_tools.fscache ]; then
		BINX=`grep "^${binname}:" .build_tools.fscache`
		if [ $? -eq 0 ]; then
			echo -ne "cached " >&2
			echo $BINX | cut -f2 -d:
			return 0
		fi
	fi
	gotsomething=0

	for dir in `echo $STANDARD_BIN_PATHS | tr -s ':' ' '`
	do
		for file in echo $dir/*
		do
			ffile=`basename $file`
			if [ "$ffile" = "$binname" ]; then
				if [ -x $dir/$binname ]; then
					echo $dir/$binname
					echo "$binname:$dir/$binname" >> .build_tools.fscache
					gotsomething=1
				fi
			fi
		done
	done
	if [ $gotsomething -eq 0 ]; then
		echo "NOT FOUND" >&2
		return 1
	fi
	return 0
}

find_gcc()
{
	find_binary gcc
}

find_gplusplus()
{
	find_binary g++
}

find_bison()
{
	find_binary bison
}

find_flex()
{
	find_binary flex
}

get_gcc_version()
{
	bin=$1
	$bin -v 2>&1 | grep ^gcc | awk '{print $3}' | cut -f1 -d.
}

get_gcc_revision()
{
	bin=$1
	$bin -v 2>&1 | grep ^gcc | awk '{print $3}' | cut -f2- -d. | sed 's/\./_/g'
}

get_gcc_full_version()
{
	bin=$1
	$bin -v 2>&1 | grep ^gcc | awk '{print $3}' | sed 's/\./_/g'
}

get_platform()
{
	uname -sr
}

get_processor()
{
	uname -m
}

get_os()
{
	uname -s
}

