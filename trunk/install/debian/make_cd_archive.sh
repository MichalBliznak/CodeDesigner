#!/bin/bash
#*****************************************************************************
#* Copyright (C) 2007 Ryan Mulder
#*
#* This program is free software; you can redistribute it and/or
#* modify it under the terms of the GNU General Public License
#* as published by the Free Software Foundation; either version 2
#* of the License, or (at your option) any later version.
#*
#* This program is distributed in the hope that it will be useful,
#* but WITHOUT ANY WARRANTY; without even the implied warranty of
#* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#* GNU General Public License for more details.
#*
#* You should have received a copy of the GNU General Public License
#* along with this program; if not, write to the Free Software
#* Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
#*
#*****************************************************************************
# this function does the actual work of copying files and archiving
# the version is passed to it as the first argument, below
function archive
{
  set -e
  
  # copy wx lib to lib dir
  wxprefix=`wx-config --prefix`
  cp -L $wxprefix/lib/libwx_gtk2u_richtext-3.0.so.0 output/lib/codedesigner
  cp -L $wxprefix/lib/libwx_gtk2u_aui-3.0.so.0 output/lib/codedesigner
  cp -L $wxprefix/lib/libwx_gtk2u_xrc-3.0.so.0 output/lib/codedesigner
  cp -L $wxprefix/lib/libwx_gtk2u_qa-3.0.so.0 output/lib/codedesigner
  cp -L $wxprefix/lib/libwx_gtk2u_html-3.0.so.0 output/lib/codedesigner
  cp -L $wxprefix/lib/libwx_gtk2u_adv-3.0.so.0 output/lib/codedesigner
  cp -L $wxprefix/lib/libwx_gtk2u_core-3.0.so.0 output/lib/codedesigner
  cp -L $wxprefix/lib/libwx_gtk2u_stc-3.0.so.0 output/lib/codedesigner
  cp -L $wxprefix/lib/libwx_gtk2u_propgrid-3.0.so.0 output/lib/codedesigner
  cp -L $wxprefix/lib/libwx_baseu_xml-3.0.so.0 output/lib/codedesigner
  cp -L $wxprefix/lib/libwx_baseu_net-3.0.so.0 output/lib/codedesigner
  cp -L $wxprefix/lib/libwx_baseu-3.0.so.0 output/lib/codedesigner

  # copy the output directory to the share directory
  mkdir output/share/codedesigner
  mv -t output/share/codedesigner/ output/plugins
  mv -t output/share/codedesigner/ output/*.*

  # rename the output folder for tar
  mv output codedesigner

  # create archive
  name="CodeDesigner_v"$1"-$2.tar.bz2"
  if [ -f $name ]
  then
    rm $name
  fi
  tar cjf $name codedesigner
}

changelog="changes.txt"

if [ ! -f $changelog ];
then
  echo "Sorry, could not find "$changelog". Need it to parse the version."
  exit 1
fi

cat "$changelog" |
while read line;
do
 version=`expr match "$line" '.*\([0-9]\.[0-9]\{1,2\}\.[0-9]\+\)'`
 if [ -n "$version" ]
 then
 echo "$version"
   # because I redirected cat to the while loop, bash spawned a subshell
   # this means "version" will go out of scop at the end of the loop
   # so I need to do everything here
   if [ ${#version} -ge 7 ]
   then
     version=${version/0/}
   fi
   label=`expr match "$line" '.*(\(.*\))'`
   archive $version $label
   break
 fi
done

exit

