--*****************************************************************************
--*	Author:		Michal Bližňák
--*	Date:		18/11/2007
--*	Version:	1.00
--*	
--*	NOTES:
--*		- use the '/' slash for all paths.
--*****************************************************************************

-- Initialize wxWigets and other presets
dofile('../build/premake/scripts/init.lua')

--******* Initial Setup ************
--*	Most of the setting are set here.
--**********************************
  
-- Set the name of your package.
package.name = "CodeDesigner"

-- Set this if you want a different name for your target than the package's name.
targetName = "CodeDesigner"

-- Set the kind of package you want to create.
--		Options: exe | winexe | lib | dll
if( windows) then                                        
	package.kind = "winexe"
else
	package.kind = "exe"
end

-- Setup the package compiler settings.
package.defines = { }
if ( target == "vs2005" ) then
	-- Windows and Visual C++ 2005
	table.insert( package.defines, "_CRT_SECURE_NO_DEPRECATE" )
        table.insert( package.defines, "_DISWARNINGS_MSVC" )
	package.buildflags = { "no-main" }
end
if( ( target == "vs2003" or target == "vs2005" ) and options["no-builtin-wchar"] ) then
	table.insert(package.buildoptions, "/Zc:wchar_t-")
end

-- Set the files to include.
package.files = { matchrecursive( "*.cpp", "*.h", "*.fbp" ) }
-- Set the files to exclude.
package.excludes = { matchrecursive( "controls/*.*", "projectbase/*.*", "plugins/*.*" ) }
-- Set the include paths.
package.includepaths = { "controls/include", "." }
-- Set hardcoded path for loaded shared libraries
if( not windows ) then
	if ( target == "cb-gcc" ) then
		table.insert( package.linkoptions, "-Wl,-rpath,$``ORIGIN/../lib/" .. project.name )
	else
		table.insert( package.linkoptions, "-Wl,-rpath,$$``ORIGIN/../lib/" .. project.name )
	end
end
-- Set windows resource file
if ( (windows) and not (target == "vs2005") ) then    
	table.insert(package.files, "resource.rc")
end
-- Set prebuild command
package.config["Debug"].prebuildcommands = { "python $(ProjectPath)/create_buildnum.py" }

-- Set the libraries it links to.
package.links = { "wxPropGrid", "wxScintilla", "wxShapeFramework", "projectBase" }

-- Setup the output directory options.
--		Note: Use 'libdir' for "lib" kind only.

-- Set precompiled headers support
package.pchheader = "wx_pch.h"
package.pchsource = "wx_pch.cpp"

-- Set wxWidgets presets
dofile('../build/premake/scripts/wxpresets.lua')
