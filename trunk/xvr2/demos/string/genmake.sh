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

allbins=`echo $CPPFILES | sed 's/\.cpp//g'`

echo 'CC=g++
DEBUG=-gstabs+
' > Makefile
echo "all: $allbins" >> Makefile
echo >> Makefile

# Process every gathered source .cpp file and generate its corresponding Makefile entry
for file in $CPPFILES
do
	binfile=`echo $file | sed 's/\.cpp//'`
	echo "$binfile: $file" >> Makefile
	echo "	\$(CC) \$(DEBUG) -o $binfile $file \`xvr2-config.sh --cflags --libs\`" >> Makefile
	echo >> Makefile
done
echo "clean: " >> Makefile
echo "	rm -f $allbins" >> Makefile
echo "" >> Makefile
echo "rebuild: clean all" >> Makefile
