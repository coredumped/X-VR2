#scp -r html/* mindstorm2600@shell.sf.net:/opt/xvr2/website/manual-z/
echo "Compressing..."
cd html ; tar zcf ../docs.tgz * ; cd ..
echo "Uploading..."
scp -r docs.tgz mindstorm2600@shell.sf.net:/home/groups/x/xv/xvr2/htdocs/
echo "Performing remote decompression..."
ssh mindstorm2600@shell.sf.net "cd /home/groups/x/xv/xvr2/htdocs/manual ; rm -rf * ; tar zxf ../docs.tgz"
