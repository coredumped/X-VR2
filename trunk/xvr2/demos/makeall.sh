for dir in `ls | grep -v CVS`
do
	if [ -d $dir ]; then
		echo " === Building demos in $dir === "
		cd $dir
		if [ -f Makefile ]; then
			make -f Makefile "$@"
		else
			if [ -f genmake.sh ]; then
				chmod +x genmake.sh
				./genmake.sh
				make -f Makefile "$@"
			fi
		fi
		cd ..
	fi
done
