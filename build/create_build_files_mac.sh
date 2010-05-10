#!/bin/sh
#

# Autodetect wxWidgets settings
if wx-config --unicode >/dev/null 2>/dev/null; then
	unicode="--unicode"
fi
if ! wx-config --debug >/dev/null 2>/dev/null; then
	debug="--disable-wx-debug"
fi
release=`wx-config --release`

# ========== CodeLite project files ==========
premake/premake-mac --target cl-gcc --wx-version $release --shared --with-wx-shared $unicode $debug $1
#premake/premake-mac --target cl-gcc --wx-version $release $unicode $debug $1
echo done...
echo 
#
# ========== GNU Makefile ==========
premake/premake-mac --target gnu --wx-version $release --shared --with-wx-shared $unicode $debug $1
#premake/premake-mac --target gnu --wx-version $release $unicode $debug $1
echo done...
echo 
#
# ========== Code::Blocks project files ==========
#premake/premake-mac --target cb-gcc --wx-version $release --shared --with-wx-shared $unicode $debug $1
#premake/premake-mac --target cb-gcc --wx-version $release $unicode $debug $1
echo done...
echo 
#
echo Done generating all project files for CodeDesigner
#
