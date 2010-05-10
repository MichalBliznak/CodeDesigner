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
package.name = "diagUml"
-- Set output directory
package.bindir = "../../../bin/plugins"
-- Set this if you want a different name for your target than the package's name.
custom_targetName = "diagUml";
-- Set the kind of package you want to create.
--		Options: exe | winexe | lib | dll
package.kind = "dll"
-- Set the files to include.
package.files = { matchrecursive( "*.cpp", "*.h", "*.fbp" ) }
-- Set the include paths.
package.includepaths = { ".", "../../", "../../controls/include" }
-- Set the defines.
package.defines = { "WXMAKINGDLL_CD" }
-- Set the libraries it links to.
package.links = { "wxPropGrid", "wxScintilla", "wxShapeFramework", "projectBase" }

-- Set wxWidgets presets
dofile('../../../build/premake/scripts/wxpresets.lua')

