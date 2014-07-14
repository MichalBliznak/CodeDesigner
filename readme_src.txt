CodeDesigner RAD tool
------------------------------
Author: Michal Bliznak, 2010
e-mail: michal.bliznak@gmail.com
www: http://sourceforge.net/projects/codedesigner


What is CodeDesigner?
-------------------------

CodeDesigner is free and open-source RAD tool suitable for easy creation of various diagrams
describing applications' structure and logic (class diagrams, state charts, ...) and for generation
of production-ready source code from them. The application is available for MS Windows, Linux and
OS X and can be used as a free alternative to Enterprise Architect or IAR Visual State commercial
tools.

In contrast to other similar CASE tools the CodeDesigner is aimed to generation of production-ready
source code from supported diagrams. It means that not only application skeleton can be generated from
diagrams but complete full-featured application including its entry point (main function) can be produced
by a one click.

Supported diagrams:
- UML class diagrams
- Simple state chart
- Hierarchical (UML, Harel) state charts

Supported programming languages:
- ANSI C
- C++
- Python

Supported code generators:
- Class code generator (C++, Python)
- Simple state chart generator
	- GOTO algorithm (C, C++)
	- Loop Case algorithm (C, C++)
	- Else-If algorithm (C, C++, Python)

- Hierarchical state chart generator
	- GOTO algorithm (C, C++)
	- Loop Case algorithm (C, C++)
	- Else-If algorithm (C, C++, Python)

Other features:
- Reverse source code engineering plugin (C, C++, Python)

Requirements:
-------------

- CodeDesigner is based on wxWidgets toolkit (www.wxwidgets.org) and can be built using
  2.9.x and higher versions (monolithic builds of wx.2.9.x libraries are supported only).
- Python interpreter must be available (the application's build number is created by using simple
  python script).
- CodeLite (www.codelite.org) IDE with MinGW C++ compiler or MS Visual Studio 2005/2008 (Express)
  are recommended for opening included workspace/project files but the application can be
  built from the command line as well.


Distribution content:
---------------------
.\output	- Application's binary files
.\build		- Premake build system for creation of various project/make files
.\install	- Installation scripts neede for the application's redistribution
.\samples	- Sample CodeDesigner projects
.\src		- Application's source codes
changes.txt	- Information about the application's version and release changes
LICENSE.txt	- License file


Build instructions:
===================
The application can be build by using prefered IDE (Codelite, CodeBlock and MS Visual Studio 2005/2008
are supported at the moment) or from command line as well. Before this the appropriate workspace/project
files or makefile must be created. This tast can be done via included premake build system in the following
way:

Premake build system:
---------------------
Premake build scripts and executables are suitable for creation of various IDE project files and 
GNU makefile as well. You can simply create Codelite, Code::Blocks and MS VS 2005/2008 project files by invoking of
the included batch scripts.

Installation - win32:

When building on win32, go to the ./build subdirectory and simply type:

> create_build_files.bat

There are few standard build configurations defined in the batch file and you can freely modify it or you can
inkove the premake system directly as follows:

Examples of usage of the premake scripts:

For Codelite Workspace/Project files producing application using shared wxWidgets libs with unicode support type:
> premake\premake-win32.exe --target cl-gcc --unicode --with-wx-shared --shared

For Code::Blocks Workspace/Project filesproducing application using shared wxWidgets libs with unicode support type:
> premake\premake-win32.exe --target cb-gcc --unicode --with-wx-shared --shared

For MSVS 2005/2008 Workspace/Project files producing staticaly built application with unicode support and staticaly linked runtime
and no built-in wchar type:
> premake\premake-win32.exe --target vs2005 --unicode --static-runtime --no-builtin-wchar

For GNU makefile producing application using shared wxWidgets libs with unicode support type:
> premake\premake-win32.exe --target gnu --unicode --with-wx-shared --shared

Note that static/dynamic linking approach can be freely changed (but relevant underlying libraries must be available, of course).


Installation - Unix:

When building on Unix, go to the ./build subdirectory and simply type:

sh ./create_build_files.sh

or you can invoke the premake system as described in the Win32 installation section above.

Examples of usage of the premake scripts on Unix:

For Codelite Workspace/Project files producing application using shared wxWidgets libs with unicode support type: 
premake/premake-linux --target cl-gcc --shared --with-wx-shared --unicode

For Code::Blocks Workspace/Project files producing application using shared wxWidgets libs with unicode support type: 
premake/premake-linux --target cl-gcc --shared --with-wx-shared --unicode

For GNU makefile producing application using shared wxWidgets libs with unicode support without debug information type:
premake/premake-linux --target gnu --shared --with-wx-shared --unicode --disable-wx-debug


Note that all needed executables and scripts are included in the release package so you can use the premake build system immediately.

