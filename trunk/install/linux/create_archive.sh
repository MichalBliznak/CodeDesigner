#!/bin/sh

# test whether CodeDesigner version is given
if [ ! -n "$1" ];
then
	echo "Version string must be defined as the script parameter."
	exit 1
fi

# archive name
out="codedesigner"

# create temporary dir
echo "Removing old temporary directory..."
rm -rf $out
mkdir $out

# copy program files
echo "Copying application files..."
cp -R -L ../../bin/* $out
rm -rf `find $out -type d -name .svn`
rm -rf $out/plugins/*diagTest.so
cp ../../LICENSE.txt $out
cp ../../readme_bin.txt $out
chmod +x $out/CodeDesigner

# copy samples
mkdir $out/samples
cp ../../samples/*.* $out/samples

# copy icon
cp ../../src/res/gui/application-icon.png $out/icon.png

# copy wxWidgets files
wxprefix=`wx-config --prefix`

cp $wxprefix/lib/libwx_gtk2u_richtext-2.8.so.0 $out
cp $wxprefix/lib/libwx_gtk2u_aui-2.8.so.0 $out
cp $wxprefix/lib/libwx_gtk2u_xrc-2.8.so.0 $out
cp $wxprefix/lib/libwx_gtk2u_qa-2.8.so.0 $out
cp $wxprefix/lib/libwx_gtk2u_html-2.8.so.0 $out
cp $wxprefix/lib/libwx_gtk2u_adv-2.8.so.0 $out
cp $wxprefix/lib/libwx_gtk2u_core-2.8.so.0 $out
cp $wxprefix/lib/libwx_baseu_xml-2.8.so.0 $out
cp $wxprefix/lib/libwx_baseu_net-2.8.so.0 $out
cp $wxprefix/lib/libwx_baseu-2.8.so.0 $out

# create archive
echo "Creating archive..."
tar -cvzf codedesigner_$1.tgz $out

# remove temporary dir
rm -rf $out

echo "Done."

