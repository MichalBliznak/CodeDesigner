--*****************************************************************************
--*	Author:		Michal Bližňák
--*	Date:		09/01/2010
--*	Version:	1.00
--*	
--*	NOTES:
--*		- use the '/' slash for all paths.
--*****************************************************************************

-- Initialize wxWigets and other presets
dofile('../../../build/premake/scripts/init.lua')

--******* Initial Setup ************
--*	Most of the setting are set here.
--**********************************

-- Set the name of your package.
package.name = "genUml"
-- Set output directory
if( not windows ) then
	package.bindir = "../../../output/lib/" .. project.name .. "/plugins"
else
	package.bindir = "../../../output/plugins"
end
-- Set this if you want a different name for your target than the package's name.
custom_targetName = "genUml";
-- Set the kind of package you want to create.
--		Options: exe | winexe | lib | dll
package.kind = "dll"
-- Set the files to include.
package.files = { matchrecursive( "*.cpp", "*.h" ) }
-- Set the include paths.
package.includepaths = { ".", "../../", "../../controls/include" }
-- Set hardcoded path for loaded shared libraries
if ( target == "cb-gcc" ) then
	table.insert( package.linkoptions, "-Wl,-rpath,$``ORIGIN/" )
else
	table.insert( package.linkoptions, "-Wl,-rpath,$$``ORIGIN/" )
end
-- Set the defines.
package.defines = { "WXMAKINGDLL_CD" }
-- Set the libraries it links to.
package.links = { "wxShapeFramework", "projectBase", "diagUml" }

-- Set wxWidgets presets
dofile('../../../build/premake/scripts/wxpresets.lua')

