#!/bin/bash
#
# Automatic Makefile generator (Only works for programs which
# only have one source file)

#Retrieve a list of all .cpp files in the current directory, if a subdirectory is
#found check if it has a genmake.sh, if it has it, then run it.

for item in *
do
	if [ -d $item ]; then
		if [ -x $item/genmake.sh ]; then
			THIS_DIR=`pwd`
			cd $item
			./genmake.sh
			cd $THIS_DIR
		fi
	else
		echo $item | egrep '\.cpp$' > /dev/null 2>&1
		if [ $? -eq 0 ]; then
			CPPFILES="${CPPFILES} $item"
		fi
	fi
done

# Process every gathered source .cpp file and generate its corresponding Makefile entry
