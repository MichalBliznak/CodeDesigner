#!/bin/sh
#

# Set path prefix to local wx-config script if needed
wx_prefix="/home/michal/Src/Projekty/wxWidgets-trunk/build-release/"
echo

echo "wxWidgets prefix: "$wx_prefix

# Autodetect wxWidgets settings
if "$wx_prefix"wx-config --unicode >/dev/null 2>/dev/null; then
	unicode="--unicode"
fi
if ! "$wx_prefix"wx-config --debug >/dev/null 2>/dev/null; then
	debug="--disable-wx-debug"
fi
release=`"$wx_prefix"wx-config --release`

# ========== CodeLite project files ==========
premake/premake-linux --target cl-gcc --wx-version $release --wx-config-prefix $wx_prefix --shared --with-wx-shared $unicode $debug $1
#premake/premake-linux --target cl-gcc --wx-version $release --wx-config-prefix $wx_prefix $unicode $debug $1
echo done...
echo 
#
# ========== GNU Makefile ==========
premake/premake-linux --target gnu --wx-version $release --wx-config-prefix $wx_prefix --shared --with-wx-shared $unicode $debug $1
#premake/premake-linux --target gnu --wx-version $release --wx-config-prefix $wx_prefix $unicode $debug $1
echo done...
echo 
#
# ========== Code::Blocks project files ==========
#premake/premake-linux --target cb-gcc --wx-version $release --wx-config-prefix $wx_prefix --shared --with-wx-shared $unicode $debug $1
#premake/premake-linux --target cb-gcc --wx-version $release --wx-config-prefix $wx_prefix $unicode $debug $1
echo done...
echo 
#
echo Done generating all project files for CodeDesigner
#
