--*****************************************************************************
--*	Author:		Michal Bližňák
--*	Date:		18/11/2007
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
package.name = "Ctags"

-- Set this if you want a different name for your target than the package's name.
targetName = "codedesigner-ctags"

-- Set the kind of package you want to create.
--		Options: exe | winexe | lib | dll
if( windows) then                                        
	package.kind = "winexe"
else
	package.kind = "exe"
end

-- Setup the package compiler settings.
if( windows ) then
	package.defines = { "WIN32", "HAVE_REGCOMP", "__USE_GNU", "bool=int", "false=0", "true=1", "strcasecmp=stricmp" }
else
	package.defines = { "HAVE_CONFIG_H" }
end

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
package.files = { matchrecursive( "*.c", "*.h" ) }
if( linux or macosx ) then
	package.excludes = { matchrecursive( "gnu_regex/*" ) }
else
	package.excludes = { "gnu_regex/regexec.c", "gnu_regex/regex_internal.c", "gnu_regex/regex_internal.h", "gnu_regex/regcomp.c" }
end

-- Set the include paths.
package.includepaths = { "." }
if( windows ) then
	table.insert(package.includepaths, "gnu_regex")
end

-- Common setup
package.language = "c"

-- Set object output directory.
if ( options["unicode"] ) then
	package.config["Debug"].objdir = ".objsud"
	package.config["Release"].objdir = ".objsu"
else
	package.config["Debug"].objdir = ".objsd"
	package.config["Release"].objdir = ".objs"
end

-- Set debug flags
if ( options["disable-wx-debug"] and ( not windows ) ) then
	debug_macro = { "NDEBUG" }
else
	debug_macro = { "DEBUG", "_DEBUG" }
end

-- Set the target names
package.config["Release"].target = targetName
package.config["Debug"].target = targetName.."_d"

-- Set the build options.
table.insert( package.buildflags, "extra-warnings" )

if( options["static-runtime"] ) then
	table.insert( package.buildflags, "static-runtime" )	
end

table.insert( package.config["Release"].buildflags, "no-symbols" )
table.insert( package.config["Release"].buildflags, "optimize-speed" )

if ( options["unicode"] ) then
	table.insert( package.buildflags, "unicode" )
end

if ( target == "cb-gcc" or target == "gnu" or target == "cl-gcc") then
--	table.insert( package.buildflags, "no-import-lib" )
	table.insert( package.config["Debug"].buildoptions, "-O0" )
	table.insert( package.config["Release"].buildoptions, "-fno-strict-aliasing" )
end

-- Set the defines.
if ( options["unicode"] ) then
	table.insert( package.defines, { "UNICODE", "_UNICODE" } )
end
