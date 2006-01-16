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
	echo $XVR_SOURCE_DIR | grep 'xvr2$' > /dev/null 2>&1
	if [ $? -ne 0 ]; then
		XVR2_SOURCE_DIR=`dirname $XVR2_SOURCE_DIR`
	fi
fi


find_binary()
{
	binname=$1
	echo -ne "Checking ${binname}... " >&2
	#FIRST SEE IF THE FILE IS ALREADY IN THE CACHE, IF IT IS THEN GRAB IT FROM THERE
	if [ -f ${XVR2_SOURCE_DIR}/.build_tools.fscache ]; then
		BINX=`grep "^${binname}:" ${XVR2_SOURCE_DIR}/.build_tools.fscache`
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
					echo "$binname:$dir/$binname" >> ${XVR2_SOURCE_DIR}/.build_tools.fscache
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
	$bin -v 2>&1 | grep ^gcc | awk '{print $3}' | cut -f2 -d. | sed 's/\./_/g'
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

get_include_deps()
{
	includex=$1
	ddepsx=""
	for incx in `cat $includex | grep include | sed 's/.*[\"|<]\(.*\)[\"|>]/\1/' | grep xvr2 | sed 's/xvr2\///'`
	do
		if [ -f $incx ]; then
			ddepsx="$ddepsx $inc"
		fi
	done
	echo $ddepsx
}

usage()
{
	echo " "
	echo "Usage (parameters with an asterisk are enabled by default): "
	echo "--with-pth			* Use GNU Portable threads (GNU Pth)"
	echo "--with-pthreads			Use POSIX Threads"
	echo "--with-sdl-threads		Use SDL POSIX threads encapsulation"
	echo "--help				Print this usage message"
	echo "--use-debug			* Activate debug message printing"
	echo "--no-debug			Dectivate debug message printing"
	echo "--disable-mantainer-mode	Disable maintainer mode (Remove symbols in object files)"
	echo "--enable-mantainer-mode		Enable maintainer mode (Leave symbols in object files)"
	echo "--debug-mutexes			Show status messages while locking/unlocking mutexes"
	echo "--dont-use-sdl			Disables the use of SDL for network and threads"
	echo "					(reduces portability)"
	echo "--sock-chunk-size		Change socket buffer chunk size in bytes while sending"
	echo "				huge amounts of data through the net (default: 4096)"
	echo "--prefix			Specifies the prefix installation directory"
	echo " "
	echo " "
	exit 0
}

get_value()
{
	echo $1 | cut -f2 -d'='
}


get_valuex()
{
	echo $1 | cut -f2 -d'='
}

get_libname()
{
	for option in `echo "$@"`
	do
		echo "$option" | egrep '^--with-name=' > /dev/null 2>&1
		if [ $? -eq 0 ]; then
			MYLIBNAME=`get_valuex $option`
		fi
	done
}

get_libversion()
{
	for option in `echo "$@"`
	do
		echo "$option" | egrep '^--version=' > /dev/null 2>&1
		if [ $? -eq 0 ]; then
			MYVERSION=`get_valuex $option`
		fi
	done
}
