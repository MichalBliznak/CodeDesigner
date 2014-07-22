--*****************************************************************************
--*	Author:		Michal Bližňák
--*	Date:		09/01/2010
--*	Version:	1.00
--*	
--*	NOTES:
--*		- use the '/' slash for all paths.
--*****************************************************************************

-- Initialize wxWigets and other presets
dofile('../../build/premake/scripts/init.lua')

--******* Initial Setup ************
--*	Most of the setting are set here.
--**********************************

-- Set the name of your package.
package.name = "projectBase"
-- Set this if you want a different name for your target than the package's name.
custom_targetName = "cdprojectbase";
-- Set the kind of package you want to create.
--		Options: exe | winexe | lib | dll
package.kind = "dll"
if( not windows ) then
	package.bindir = "../../output/lib/" .. project.name
else
	package.bindir = "../../output"
end
-- Set the files to include.
package.files = { matchrecursive( "*.cpp", "*.h", "*.fbp" ) }
-- Set the include paths.
package.includepaths = { ".", "../" }
-- Set the defines.
package.defines = { "WXMAKINGDLL_CD" }
-- Set the libraries it links to.
package.links = { "wxShapeFramework" }

-- Set compiler flags.
if( ( target == "cl-gcc" or target == "gnu" ) and options["architecture"] ) then
	table.insert(package.buildoptions, "-arch " .. options["architecture"])
end

-- Set wxWidgets presets
wx_config_libs="std,propgrid,stc"

dofile('../../build/premake/scripts/wxpresets.lua')

-- Must be set here to avoid conflicts with built-in wxWidgets controls (wxPropertyGrid)
table.insert( package.includepaths, "../controls/include" )

