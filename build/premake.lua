project.name = "CodeDesigner"

project.bindir = "../bin"
project.libdir = "../bin"

-- Configurations. All I am doing is reordering them so that
-- it defaults to a Release build.
project.configs = { "Release", "Debug" }

-- Add packages here.
dopackage( "propgrid" )
dopackage( "wxScintilla" )
dopackage( "wxShapeFramework" )
dopackage( "../src/projectbase" )
dopackage( "../src/plugins/diagTest" )
dopackage( "../src/plugins/diagUml" )
dopackage( "../src/plugins/genUml" )
dopackage( "../src" )

function CreateSymlink( pathToLink, symLink )
	os.execute( "ln -s -f -n " .. pathToLink .. " " .. symLink  )
end

if( not os.fileexists("../bin") ) then
	os.mkdir("../bin")
end

-- Create symlinks to plugins and images
if ( not windows) then
	-- Create needed directories
	if ( not os.fileexists( "../bin/plugins" ) ) then
		os.mkdir( "../bin/plugins" )
	end
	-- Create symlinks
	if( not os.fileexists( "../bin/res" ) ) then
		CreateSymlink( "../src/res", "../bin/res" )
	end
	if( not os.fileexists( "../bin/plugins/res" ) ) then
		CreateSymlink( "../../src/plugins/res", "../bin/plugins/res" )
	end
else
	-- Create needed directories
	if ( not os.fileexists( "../bin/plugins" ) ) then
		os.mkdir( "../bin/plugins" )
	end
	-- Copy neede files (images)
	if( not os.fileexists( "../bin/res" ) ) then
		os.execute( "xcopy ../src/res ../bin/res /Y" )
	end
	if( not os.fileexists( "../bin/plugins/res" ) ) then
		os.execute( "xcopy ../src/plugins/res ../bin/plugins/res /Y" )
	end
end

