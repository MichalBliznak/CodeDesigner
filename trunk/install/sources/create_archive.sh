#!/bin/sh

# test whether CodeDesigner version is given
if [ ! -n "$1" ];
then
	echo "Version string must be defined as the script parameter."
	exit 1
fi

# archive name
out="codedesigner_src"

# create temporary dir
echo "Removing old temporary directory..."
rm -rf $out
mkdir $out
mkdir $out/build

# copy program files
echo "Copying build files..."
cp -R -L ../../build/premake $out/build
# cp -R -L ../../build/propgrid $out/build
# cp -R -L ../../build/wxScintilla $out/build
cp -R -L ../../build/wxShapeFramework $out/build
cp ../../build/create_build_files.* $out/build
cp ../../build/premake.lua $out/build

echo "Copying source files..."
cp -R -L ../../src $out
cp ../../LICENSE.txt $out
cp ../../changes.txt $out
cp ../../readme_src.txt $out

echo "Remove unneeded files and directories..."
rm -rf `find $out -type d -name .svn`
rm -rf `find $out -type d -name .objsu`
rm -rf `find $out -type d -name .objsud`
rm -rf `find $out -type f -name *.project`
rm -rf `find $out -type f -name *.mk`
rm -rf `find $out -type f -name Makefile`

# copy samples
mkdir $out/samples
cp ../../samples/*.* $out/samples

# create archive
echo "Creating archive..."
tar -cvzf codedesigner_src-$1.tgz $out
zip -r codedesigner_src-$1.zip $out

# remove temporary dir
rm -rf $out

echo "Done."

