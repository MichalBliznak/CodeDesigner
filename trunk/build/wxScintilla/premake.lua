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
package.name = "wxScintilla"
-- Set this if you want a different name for your target than the package's name.
targetName = "scintilla"
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
package.files =
{
	matchfiles( "../../src/controls/src/wxScintilla/*.cpp", "../../src/controls/include/wx/wxScintilla/*.h" ),
	matchrecursive( "../../src/controls/src/wxScintilla/scintilla/*.cxx", "../../src/controls/src/wxScintilla/scintilla/*.h" )
}
-- Set the include paths.
package.includepaths = { "../../src/controls/include", "../../src/controls/src/wxScintilla", "../../src/controls/src/wxScintilla/scintilla/include", "../../src/controls/src/wxScintilla/scintilla/src" }
-- Set libraries to link.
if ( windows ) then
	package.links = { "Gdi32" }
end

-- Set the defines.
package.defines = { "WXMAKINGDLL_SCI", "MONOLITHIC", "LINK_LEXERS", "SCI_LEXER", "SCI_NAMESPACE", "__WX__" }

-- Set compiler flags.
if( ( target == "cl-gcc" or target == "gnu" ) and options["architecture"] ) then
	table.insert(package.buildoptions, "-arch " .. options["architecture"])
end

-- Set wxWidgets presets
dofile('../premake/scripts/wxpresets.lua')

