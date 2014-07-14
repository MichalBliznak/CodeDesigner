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
if [ -f ./output/bin/codedesigner_d]; then
	cp ./output/bin/codedesigner_d $APPCONTENTS/MacOS/codedesigner_d
else
	cp ./output/bin/codedesigner.app/Contents/MacOS/codedesigner_d $APPCONTENTS/MacOS/codedesigner_d
fi
cp ./output/bin/codedesigner-ctags_d $APPCONTENTS/MacOS/codedesigner-ctags_d
cp -r ./output/lib/codedesigner/* $APPCONTENTS/PlugIns
rm $APPCONTENTS/PlugIns/plugins/libdiagtest_d.dylib
cp -r ./src/res/ $APPCONTENTS/Resources/app
cp -r ./src/plugins/res/ $APPCONTENTS/Resources/plugins
cp ./install/macosx/icon.icns $APPCONTENTS/Resources/icon.icns
cp ./install/macosx/docicon.icns $APPCONTENTS/Resources/docicon.icns
cp ./install/macosx/Info.plist $APPCONTENTS/Info.plist

# fix libraries' internal name and path... not really necessary but better
install_name_tool -id @executable_path/../PlugIns/libwx_macud_shapeframework-3.0_cd.dylib $APPCONTENTS/PlugIns/libwx_macud_shapeframework-3.0_cd.dylib
#install_name_tool -id @executable_path/../PlugIns/libwx_macud_propgrid-2.8_cd.dylib $APPCONTENTS/PlugIns/libwx_macud_propgrid-2.8_cd.dylib
#install_name_tool -id @executable_path/../PlugIns/libwx_macud_scintilla-2.8_cd.dylib $APPCONTENTS/PlugIns/libwx_macud_scintilla-2.8_cd.dylib
install_name_tool -id @executable_path/../PlugIns/libcdprojectbase_d.dylib $APPCONTENTS/PlugIns/libcdprojectbase_d.dylib
#install_name_tool -id @executable_path/../PlugIns/plugins/libdiagtest_d.dylib $APPCONTENTS/PlugIns/plugins/libdiagtest_d.dylib
install_name_tool -id @executable_path/../PlugIns/plugins/libdiaguml_d.dylib $APPCONTENTS/PlugIns/plugins/libdiaguml_d.dylib
install_name_tool -id @executable_path/../PlugIns/plugins/libcodelite_d.dylib $APPCONTENTS/PlugIns/plugins/libcodelite_d.dylib
install_name_tool -id @executable_path/../PlugIns/plugins/libgenuml_d.dylib $APPCONTENTS/PlugIns/plugins/libgenuml_d.dylib
install_name_tool -id @executable_path/../PlugIns/plugins/libreveng_d.dylib $APPCONTENTS/PlugIns/plugins/libreveng_d.dylib

# fix links betwen libraries now that we moved them, so they can find each other
# in their new locations
# codedesigner
install_name_tool -change ../../output/lib/codedesigner/libwx_macud_shapeframework-3.0_cd.dylib @executable_path/../PlugIns/libwx_macud_shapeframework-3.0_cd.dylib $APPCONTENTS/MacOS/codedesigner_d
#install_name_tool -change ../../output/lib/codedesigner/libwx_macud_propgrid-2.8_cd.dylib @executable_path/../PlugIns/libwx_macud_propgrid-2.8_cd.dylib $APPCONTENTS/MacOS/codedesigner_d
#install_name_tool -change ../../output/lib/codedesigner/libwx_macud_scintilla-2.8_cd.dylib @executable_path/../PlugIns/libwx_macud_scintilla-2.8_cd.dylib $APPCONTENTS/MacOS/codedesigner_d
install_name_tool -change ../../output/lib/codedesigner/libcdprojectbase_d.dylib @executable_path/../PlugIns/libcdprojectbase_d.dylib $APPCONTENTS/MacOS/codedesigner_d
i#nstall_name_tool -change ../../../output/lib/codedesigner/plugins/libdiagtest_d.dylib @executable_path/../PlugIns/plugins/libdiagtest_d.dylib $APPCONTENTS/MacOS/codedesigner_d
install_name_tool -change ../../../output/lib/codedesigner/plugins/libdiaguml_d.dylib @executable_path/../PlugIns/plugins/libdiaguml_d.dylib $APPCONTENTS/MacOS/codedesigner_d
# projectbase
#install_name_tool -change ../../output/lib/codedesigner/libwx_macud_propgrid-2.8_cd.dylib @executable_path/../PlugIns/libwx_macud_propgrid-2.8_cd.dylib $APPCONTENTS/PlugIns/libcdprojectbase_d.dylib
#install_name_tool -change ../../output/lib/codedesigner/libwx_macud_scintilla-2.8_cd.dylib @executable_path/../PlugIns/libwx_macud_scintilla-2.8_cd.dylib $APPCONTENTS/PlugIns/libcdprojectbase_d.dylib
install_name_tool -change ../../output/lib/codedesigner/libwx_macud_shapeframework-3.0_cd.dylib @executable_path/../PlugIns/libwx_macud_shapeframework-3.0_cd.dylib $APPCONTENTS/PlugIns/libcdprojectbase_d.dylib
# diagtest
#install_name_tool -change ../../output/lib/codedesigner/libwx_macud_shapeframework-2.8_cd.dylib @executable_path/../PlugIns/libwx_macud_shapeframework-2.8_cd.dylib $APPCONTENTS/PlugIns/plugins/libdiagtest_d.dylib
#install_name_tool -change ../../output/lib/codedesigner/libcdprojectbase_d.dylib @executable_path/../PlugIns/libcdprojectbase_d.dylib $APPCONTENTS/PlugIns/plugins/libdiagtest_d.dylib
# diaguml
install_name_tool -change ../../output/lib/codedesigner/libwx_macud_shapeframework-3.0_cd.dylib @executable_path/../PlugIns/libwx_macud_shapeframework-3.0_cd.dylib $APPCONTENTS/PlugIns/plugins/libdiaguml_d.dylib
#install_name_tool -change ../../output/lib/codedesigner/libwx_macud_scintilla-2.8_cd.dylib @executable_path/../PlugIns/libwx_macud_scintilla-2.8_cd.dylib $APPCONTENTS/PlugIns/plugins/libdiaguml_d.dylib
#install_name_tool -change ../../output/lib/codedesigner/libwx_macud_propgrid-2.8_cd.dylib @executable_path/../PlugIns/libwx_macud_propgrid-2.8_cd.dylib $APPCONTENTS/PlugIns/plugins/libdiaguml_d.dylib
install_name_tool -change ../../output/lib/codedesigner/libcdprojectbase_d.dylib @executable_path/../PlugIns/libcdprojectbase_d.dylib $APPCONTENTS/PlugIns/plugins/libdiaguml_d.dylib
# genuml
install_name_tool -change ../../output/lib/codedesigner/libwx_macud_shapeframework-3.0_cd.dylib @executable_path/../PlugIns/libwx_macud_shapeframework-3.0_cd.dylib $APPCONTENTS/PlugIns/plugins/libgenuml_d.dylib
install_name_tool -change ../../output/lib/codedesigner/libcdprojectbase_d.dylib @executable_path/../PlugIns/libcdprojectbase_d.dylib $APPCONTENTS/PlugIns/plugins/libgenuml_d.dylib
install_name_tool -change ../../../output/lib/codedesigner/plugins/libdiaguml_d.dylib @executable_path/../PlugIns/plugins/libdiaguml_d.dylib $APPCONTENTS/PlugIns/plugins/libgenuml_d.dylib
# codelite
install_name_tool -change ../../output/lib/codedesigner/libwx_macud_shapeframework-3.0_cd.dylib @executable_path/../PlugIns/libwx_macud_shapeframework-3.0_cd.dylib $APPCONTENTS/PlugIns/plugins/libcodelite_d.dylib
install_name_tool -change ../../output/lib/codedesigner/libcdprojectbase_d.dylib @executable_path/../PlugIns/libcdprojectbase_d.dylib $APPCONTENTS/PlugIns/plugins/libcodelite_d.dylib
# reveng
install_name_tool -change ../../output/lib/codedesigner/libwx_macud_shapeframework-3.0_cd.dylib @executable_path/../PlugIns/libwx_macud_shapeframework-3.0_cd.dylib $APPCONTENTS/PlugIns/plugins/libreveng_d.dylib
install_name_tool -change ../../output/lib/codedesigner/libcdprojectbase_d.dylib @executable_path/../PlugIns/libcdprojectbase_d.dylib $APPCONTENTS/PlugIns/plugins/libreveng_d.dylib
install_name_tool -change ../../../output/lib/codedesigner/plugins/libdiaguml_d.dylib @executable_path/../PlugIns/plugins/libdiaguml_d.dylib $APPCONTENTS/PlugIns/plugins/libreveng_d.dylib
