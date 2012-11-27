--*****************************************************************************
--*	Author:		Michal Bližňák
--*	Date:		09/01/2010
--*	Version:	1.00
--*	
--*	NOTES:
--*		- use the '/' slash for all paths.
--*****************************************************************************

-- Initialize wxWigets and other presets
dofile('../premake/scripts/init.lua')
wx_custom = "_cd"

--******* Initial Setup ************
--*	Most of the setting are set here.
--**********************************

-- Set the name of your package.
package.name = "wxShapeFramework"
-- Set this if you want a different name for your target than the package's name.
targetName = "shapeframework"
-- Set the kind of package you want to create.
--		Options: exe | winexe | lib | dll
package.kind = "dll"
-- Set package binary dir
if( not windows ) then
	package.bindir = "../../output/lib/" .. project.name
else
	package.bindir = "../../output"
end
-- Set the files to include.
package.files = { matchfiles( "../../src/controls/src/wxShapeFramework/*.cpp", "../../src/controls/src/wxShapeFramework/wxxmlserializer/*.cpp", "../../src/controls/include/wx/wxsf/*.h", "../../src/controls/include/wx/wxxmlserializer/*.h") }
-- Set the include paths.
package.includepaths = { "../../src/controls/include", "../../src/controls/src/wxShapeFramework" }
-- Set the defines.
package.defines = { "WXMAKINGDLL_WXSF", "WXMAKINGDLL_WXXS", "MONOLITHIC" }

-- Set compiler flags.
if( ( target == "cl-gcc" or target == "gnu" ) and options["architecture"] ) then
	table.insert(package.buildoptions, "-arch " .. options["architecture"])
end

-- Set wxWidgets presets
dofile('../premake/scripts/wxpresets.lua')

