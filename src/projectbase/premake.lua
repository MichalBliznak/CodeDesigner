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
custom_targetName = "projectBase";
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
package.includepaths = { ".", "../", "../controls/include" }
-- Set the defines.
package.defines = { "WXMAKINGDLL_CD" }
-- Set the libraries it links to.
package.links = { "wxPropGrid", "wxScintilla", "wxShapeFramework" }

-- Set wxWidgets presets
dofile('../../build/premake/scripts/wxpresets.lua')

