#!/bin/sh
#

# Parse command line options
wxroot=""
wxpath=""
shared="--shared --with-wx-shared"
for args in "$@"
do
    haveroot=`expr "${args}" : '--wx-root=.*'`
	havearch=`expr "${args}" : '--architecture=.*'`
    if ( [ ${args} = "--help" ] || [ ${args} = "-h" ] ); then
        echo "Available options:"
        echo
        echo "--wx-root                 Specify the wxWidgets build path,"
        echo "                          useful for wxWidgets builds not installed"
        echo "                          in your system (alternate/custom builds)"
        echo "                          Example: --wx-root=/home/devel/wx/3.0/buildgtk"
        echo "                          Current: $wxpath"
        echo
        echo "--disable-shared          Use static wxWidgets build instead of shared libraries."
        echo
        echo "--architecture            Specify build architecture."
		echo "							Example: --architecture=i368"
        echo
        exit
	elif( [ ${args} = "--disable-shared" ] ); then
		shared="--shared"
		continue
	elif ( [ "$havearch" -gt "0" ] ); then
        arch=${args//=/" "}
		continue
    elif ( [ "$haveroot" -gt "0" ] ); then
        wxroot=${args}
		wxpath=${wxroot#-*=}/
		wxroot="--wx-root "${wxpath}
        continue
    fi
done

# Autodetect wxWidgets settings
if ${wxpath}wx-config --unicode >/dev/null 2>/dev/null; then
	unicode="--unicode"
fi
if ! ${wxpath}wx-config --debug >/dev/null 2>/dev/null; then
	debug="--disable-wx-debug"
fi
release=`${wxpath}wx-config --release`

propgrid=""
if ( [ `echo "$release < 2.9" | bc` = "1" ] ); then
propgrid="--no-builtin-propgrid"
fi

# ========== CodeLite project files ==========
premake/premake-mac --target cl-gcc --wx-version $release $propgrid $unicode $debug $shared $arch $wxroot $1
echo done...
echo 
#
# ========== GNU Makefile ==========
premake/premake-mac --target gnu --wx-version $release $propgrid $unicode $debug $shared $arch $wxroot $1
echo done...
echo 
#
#
echo Done generating all project files for CodeDesigner
#
