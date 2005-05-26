#
# $Id$
# Common functions to be used within the configure scripts
#

STANDARD_BIN_PATHS="/opt/sfw/bin:/bin:/usr/bin:/usr/local/bin:/sbin:/usr/sbin:/usr/local/sbin:${HOME}/bin"

find_binary()
{
	binname=$1
	gotsomething=0
	echo -ne "Checking ${binname}..." > 2
	for dir in `echo $STANDARD_BIN_PATHS | tr -s ':' ' '`
	do
		for file in echo $dir/*
		do
			ffile=`basename $file`
			if [ "$ffile" = "$binname" ]; then
				if [ -x $dir/$binname ]; then
					echo $dir/$binname
					gotsomething=1
				fi
			fi
		done
	done
	if [ $gotsomething -eq 0 ]; then
		echo "$binname NOT FOUND" 1>&2
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

