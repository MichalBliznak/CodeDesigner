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

if [ ! -f "../../output/bin/codedesigner-ctags" ];
then
	echo "CTAGS utility doesn't exist in bin directory."
	exit 1
fi

# copy program files
echo "Copying application files..."
cp -R -L ../../output/* $out
rm -rf `find $out -type d -name .svn`
rm -rf `find $out -type f -name *gtk2ud*`
rm -rf `find $out -type f -name *_d*`
rm -rf $out/lib/codedesigner/plugins/*diagtest.so
cp ../../LICENSE.txt $out
cp ../../changes.txt $out
cp ../../readme_bin.txt $out
chmod +x $out/bin/codedesigner
chmod +x $out/bin/ctags

# copy samples
mkdir $out/samples
cp ../../samples/*.* $out/samples

# copy icon
cp ../../src/res/gui/application-icon.png $out/icon.png

# copy wxWidgets files
wxprefix=`wx-config --prefix`

cp $wxprefix/lib/libwx_gtk2u_richtext-3.0.so.0 $out/lib/codedesigner
cp $wxprefix/lib/libwx_gtk2u_aui-3.0.so.0 $out/lib/codedesigner
cp $wxprefix/lib/libwx_gtk2u_xrc-3.0.so.0 $out/lib/codedesigner
cp $wxprefix/lib/libwx_gtk2u_qa-3.0.so.0 $out/lib/codedesigner
cp $wxprefix/lib/libwx_gtk2u_html-3.0.so.0 $out/lib/codedesigner
cp $wxprefix/lib/libwx_gtk2u_adv-3.0.so.0 $out/lib/codedesigner
cp $wxprefix/lib/libwx_gtk2u_core-3.0.so.0 $out/lib/codedesigner
cp $wxprefix/lib/libwx_gtk2u_stc-3.0.so.0 $out/lib/codedesigner
cp $wxprefix/lib/libwx_gtk2u_propgrid-3.0.so.0 $out/lib/codedesigner
cp $wxprefix/lib/libwx_baseu_xml-3.0.so.0 $out/lib/codedesigner
cp $wxprefix/lib/libwx_baseu_net-3.0.so.0 $out/lib/codedesigner
cp $wxprefix/lib/libwx_baseu-3.0.so.0 $out/lib/codedesigner

# create archive
echo "Creating archive..."
tar -cvzf codedesigner-$1.tgz $out

# remove temporary dir
rm -rf $out

echo "Done."

