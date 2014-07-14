#!/bin/sh
#*****************************************************************************
#* Copyright (C) 2012 Michal Bliznak
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

APPCONTENTS=./output/CodeDesigner.app/Contents

cd ..

rm -r -f ./output/CodeDesigner.app
mkdir ./output/CodeDesigner.app
mkdir $APPCONTENTS
mkdir $APPCONTENTS/Resources
mkdir $APPCONTENTS/MacOS
mkdir $APPCONTENTS/PlugIns
if [ -f ./output/bin/codedesigner ]; then
	cp ./output/bin/codedesigner $APPCONTENTS/MacOS/codedesigner
else
	cp ./output/bin/codedesigner.app/Contents/MacOS/codedesigner $APPCONTENTS/MacOS/codedesigner
fi
cp ./output/bin/codedesigner-ctags $APPCONTENTS/MacOS/codedesigner-ctags
cp -r ./output/lib/codedesigner/* $APPCONTENTS/PlugIns
rm $APPCONTENTS/PlugIns/plugins/libdiagtest.dylib
cp -r ./src/res/ $APPCONTENTS/Resources/app
cp -r ./src/plugins/res/ $APPCONTENTS/Resources/plugins
cp ./install/macosx/icon.icns $APPCONTENTS/Resources/icon.icns
cp ./install/macosx/docicon.icns $APPCONTENTS/Resources/docicon.icns
cp ./install/macosx/Info.plist $APPCONTENTS/Info.plist

# fix libraries' internal name and path... not really necessary but better
install_name_tool -id @executable_path/../PlugIns/libwx_macu_shapeframework-3.0_cd.dylib $APPCONTENTS/PlugIns/libwx_macu_shapeframework-3.0_cd.dylib
#install_name_tool -id @executable_path/../PlugIns/libwx_macu_propgrid-2.8_cd.dylib $APPCONTENTS/PlugIns/libwx_macu_propgrid-2.8_cd.dylib
#install_name_tool -id @executable_path/../PlugIns/libwx_macu_scintilla-2.8_cd.dylib $APPCONTENTS/PlugIns/libwx_macu_scintilla-2.8_cd.dylib
install_name_tool -id @executable_path/../PlugIns/libcdprojectbase.dylib $APPCONTENTS/PlugIns/libcdprojectbase.dylib
#install_name_tool -id @executable_path/../PlugIns/plugins/libdiagtest.dylib $APPCONTENTS/PlugIns/plugins/libdiagtest.dylib
install_name_tool -id @executable_path/../PlugIns/plugins/libdiaguml.dylib $APPCONTENTS/PlugIns/plugins/libdiaguml.dylib
install_name_tool -id @executable_path/../PlugIns/plugins/libcodelite.dylib $APPCONTENTS/PlugIns/plugins/libcodelite.dylib
install_name_tool -id @executable_path/../PlugIns/plugins/libgenuml.dylib $APPCONTENTS/PlugIns/plugins/libgenuml.dylib
install_name_tool -id @executable_path/../PlugIns/plugins/libreveng.dylib $APPCONTENTS/PlugIns/plugins/libreveng.dylib

# fix links betwen libraries now that we moved them, so they can find each other
# in their new locations
# codedesigner
install_name_tool -change ../../output/lib/codedesigner/libwx_macu_shapeframework-3.0_cd.dylib @executable_path/../PlugIns/libwx_macu_shapeframework-3.0_cd.dylib $APPCONTENTS/MacOS/codedesigner
#install_name_tool -change ../../output/lib/codedesigner/libwx_macu_propgrid-2.8_cd.dylib @executable_path/../PlugIns/libwx_macu_propgrid-2.8_cd.dylib $APPCONTENTS/MacOS/codedesigner
#install_name_tool -change ../../output/lib/codedesigner/libwx_macu_scintilla-2.8_cd.dylib @executable_path/../PlugIns/libwx_macu_scintilla-2.8_cd.dylib $APPCONTENTS/MacOS/codedesigner
install_name_tool -change ../../output/lib/codedesigner/libcdprojectbase.dylib @executable_path/../PlugIns/libcdprojectbase.dylib $APPCONTENTS/MacOS/codedesigner
#install_name_tool -change ../../../output/lib/codedesigner/plugins/libdiagtest.dylib @executable_path/../PlugIns/plugins/libdiagtest.dylib $APPCONTENTS/MacOS/codedesigner
install_name_tool -change ../../../output/lib/codedesigner/plugins/libdiaguml.dylib @executable_path/../PlugIns/plugins/libdiaguml.dylib $APPCONTENTS/MacOS/codedesigner
# projectbase
#install_name_tool -change ../../output/lib/codedesigner/libwx_macu_propgrid-2.8_cd.dylib @executable_path/../PlugIns/libwx_macu_propgrid-2.8_cd.dylib $APPCONTENTS/PlugIns/libcdprojectbase.dylib
#install_name_tool -change ../../output/lib/codedesigner/libwx_macu_scintilla-2.8_cd.dylib @executable_path/../PlugIns/libwx_macu_scintilla-2.8_cd.dylib $APPCONTENTS/PlugIns/libcdprojectbase.dylib
install_name_tool -change ../../output/lib/codedesigner/libwx_macu_shapeframework-3.0_cd.dylib @executable_path/../PlugIns/libwx_macu_shapeframework-3.0_cd.dylib $APPCONTENTS/PlugIns/libcdprojectbase.dylib
# diagtest
#install_name_tool -change ../../output/lib/codedesigner/libwx_macu_shapeframework-2.8_cd.dylib @executable_path/../PlugIns/libwx_macu_shapeframework-2.8_cd.dylib $APPCONTENTS/PlugIns/plugins/libdiagtest.dylib
#install_name_tool -change ../../output/lib/codedesigner/libcdprojectbase.dylib @executable_path/../PlugIns/libcdprojectbase.dylib $APPCONTENTS/PlugIns/plugins/libdiagtest.dylib
# diaguml
install_name_tool -change ../../output/lib/codedesigner/libwx_macu_shapeframework-3.0_cd.dylib @executable_path/../PlugIns/libwx_macu_shapeframework-3.0_cd.dylib $APPCONTENTS/PlugIns/plugins/libdiaguml.dylib
#install_name_tool -change ../../output/lib/codedesigner/libwx_macu_scintilla-2.8_cd.dylib @executable_path/../PlugIns/libwx_macu_scintilla-2.8_cd.dylib $APPCONTENTS/PlugIns/plugins/libdiaguml.dylib
#install_name_tool -change ../../output/lib/codedesigner/libwx_macu_propgrid-2.8_cd.dylib @executable_path/../PlugIns/libwx_macu_propgrid-2.8_cd.dylib $APPCONTENTS/PlugIns/plugins/libdiaguml.dylib
install_name_tool -change ../../output/lib/codedesigner/libcdprojectbase.dylib @executable_path/../PlugIns/libcdprojectbase.dylib $APPCONTENTS/PlugIns/plugins/libdiaguml.dylib
# genuml
install_name_tool -change ../../output/lib/codedesigner/libwx_macu_shapeframework-3.0_cd.dylib @executable_path/../PlugIns/libwx_macu_shapeframework-3.0_cd.dylib $APPCONTENTS/PlugIns/plugins/libgenuml.dylib
install_name_tool -change ../../output/lib/codedesigner/libcdprojectbase.dylib @executable_path/../PlugIns/libcdprojectbase.dylib $APPCONTENTS/PlugIns/plugins/libgenuml.dylib
install_name_tool -change ../../../output/lib/codedesigner/plugins/libdiaguml.dylib @executable_path/../PlugIns/plugins/libdiaguml.dylib $APPCONTENTS/PlugIns/plugins/libgenuml.dylib
# codelite
install_name_tool -change ../../output/lib/codedesigner/libwx_macu_shapeframework-3.0_cd.dylib @executable_path/../PlugIns/libwx_macu_shapeframework-3.0_cd.dylib $APPCONTENTS/PlugIns/plugins/libcodelite.dylib
install_name_tool -change ../../output/lib/codedesigner/libcdprojectbase.dylib @executable_path/../PlugIns/libcdprojectbase.dylib $APPCONTENTS/PlugIns/plugins/libcodelite.dylib
# reveng
install_name_tool -change ../../output/lib/codedesigner/libwx_macu_shapeframework-3.0_cd.dylib @executable_path/../PlugIns/libwx_macu_shapeframework-3.0_cd.dylib $APPCONTENTS/PlugIns/plugins/libreveng.dylib
install_name_tool -change ../../output/lib/codedesigner/libcdprojectbase.dylib @executable_path/../PlugIns/libcdprojectbase.dylib $APPCONTENTS/PlugIns/plugins/libreveng.dylib
install_name_tool -change ../../../output/lib/codedesigner/plugins/libdiaguml.dylib @executable_path/../PlugIns/plugins/libdiaguml.dylib $APPCONTENTS/PlugIns/plugins/libreveng.dylib
