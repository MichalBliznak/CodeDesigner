project.name = "codedesigner"

if( not windows ) then
	project.bindir = "../output/bin"
	project.libdir = "../output/lib/" .. project.name
else
	project.bindir = "../output"
	project.libdir = "../output"
end

local resdir = "../output/share/" .. project.name

-- Configurations. All I am doing is reordering them so that
-- it defaults to a Release build.
project.configs = { "Release", "Debug" }

-- Add packages here.
dopackage( "wxShapeFramework" )
dopackage( "../src/projectbase" )
dopackage( "../src/plugins/diagTest" )
dopackage( "../src/plugins/diagUml" )
dopackage( "../src/plugins/genUml" )
dopackage( "../src/plugins/codelite" )
dopackage( "../src/plugins/revEng" )
dopackage( "../src" )
dopackage( "../src/ctags" )

function CreateSymlink( pathToLink, symLink )
	os.execute( "ln -s -f -n " .. pathToLink .. " " .. symLink  )
end

if( not os.fileexists("../output") ) then
	os.mkdir("../output")
end

-- Create symlinks to plugins and images
if ( not windows) then
	-- Create needed directories
	if ( not os.fileexists( resdir ) ) then
		os.mkdir( resdir )
	end
	-- Create symlinks
	if( not os.fileexists( resdir .. "/app" ) ) then
		CreateSymlink( "../../../src/res", resdir .. "/app" )
	end
	if( not os.fileexists( resdir .. "/plugins" ) ) then
		CreateSymlink( "../../../src/plugins/res", resdir .. "/plugins" )
	end
else
	-- Create needed directories
	if ( not os.fileexists( "..\\bin\\plugins" ) ) then
		os.mkdir( "..\\bin\\plugins" )
	end
	-- Copy needed files (images)
	if( not os.fileexists( "..\\output\\res\\app" ) ) then
		os.execute( "xcopy ..\\src\\res ..\\output\\res\\app /Y /s /i /q" )
	end
	if( not os.fileexists( "..\\output\\res\\plugins" ) ) then
		os.execute( "xcopy ..\\src\\plugins\\res ..\\output\\res\\plugins /Y /s /i /q" )
	end
end

