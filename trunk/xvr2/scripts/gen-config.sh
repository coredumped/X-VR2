#!/bin/sh
echo "#!/bin/sh
PREFIX=${1}
for param in \"\$@\"
do
	if [ \$param = '--cflags' ]; then
		echo -ne \"-I\${PREFIX}/include/xvr2 \"
	else
		if [ \$param = '--libs' ]; then
			for lib in \`ls \$PREFIX/lib/libxvr2*so | sort\`
			do
				lib=\`basename \$lib | sed 's/lib\(.*\).so.*/\1/'\`
				echo -ne \"-l\${lib} \"
			done
		fi
	fi
done
" > xvr2-config.sh
chmod 755 xvr2-config.sh
