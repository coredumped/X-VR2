THIS_DIR=`pwd`
VERSION=`cat ../VERSION`
#DEPS="../../base/src/Plugin.h ../../base/src/System.h ../../base/src/Exception.h "
ALL=
DRIVERS=`ls | grep -v CVS | grep -v database | grep -v graphics`
for dir in `echo $DRIVERS`
do
	if [ -d $dir ]; then
		#Only process if it has a configure.sh script
		if [ -f $dir/configure.sh ]; then
			echo "Configuring $dir driver..."
			cd $dir
			./configure.sh "$@" --version=${VERSION}
			cd ..
			ALL="${ALL} ${dir}/${dir}-driver.so.${VERSION}"
		fi
	fi
done
echo "VERSION=${VERSION}

all: ${ALL}

" > Makefile

#### Generate per-project build targets

for dir in `echo $DRIVERS`
do
	if [ -d $dir ]; then
		#Only process if it has a Makefile
		if [ -f $dir/Makefile ]; then
			echo "${dir}/${dir}-driver.so.${VERSION}: ${DEPS} ${dir}/*.h ${dir}/*.cpp" >> Makefile
			echo -e "\tcd ${dir} ; make -f Makefile" >> Makefile
			echo "" >> Makefile
			echo "${dir}/*.h:" >> Makefile
			echo "" >> Makefile
			echo "${dir}/*.cpp:" >> Makefile
			echo "" >> Makefile
		fi
	fi
done

#### Generate per-project clean targets
echo "
clean:" >> Makefile
for dir in `echo $DRIVERS`
do
	if [ -d $dir ]; then
		#Only process if it has a Makefile
		if [ -f $dir/Makefile ]; then
			echo -e "\tcd ${dir} ; make -f Makefile clean" >> Makefile
		fi
	fi
done

#### Generate per-project install targets
echo "
install:" >> Makefile
for dir in `echo $DRIVERS`
do
	if [ -d $dir ]; then
		#Only process if it has a Makefile
		if [ -f $dir/Makefile ]; then
			echo -e "\tcd ${dir} ; make -f Makefile install" >> Makefile
		fi
	fi
done

echo "
rebuild: clean all" >> Makefile
