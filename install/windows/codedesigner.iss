[Setup]
AppCopyright=Tomas Bata University, Zlin, Czech Republic, 2010 - 2014
AppName=CodeDesigner RAD
AppVerName=CodeDesigner RAD 1.6.4.3106 Beta (SVN: 354)
ChangesAssociations=true
DefaultGroupName=CodeDesigner RAD
DefaultDirName={pf}\CodeDesigner
OutputBaseFilename=codedesigner-1.6.4.3106
InfoBeforeFile=..\..\changes.txt
LicenseFile=..\..\LICENSE.txt
PrivilegesRequired=none
[Files]
Source: C:\MinGW-4.8.1\bin\mingwm10.dll; DestDir: {app}; Components: core
Source: C:\MinGW-4.8.1\bin\libgcc_s_dw2-1.dll ; DestDir: {app}; Components: core
Source: C:\SourceCode\Libraries\wxWidgets-3.0.1\lib\gcc_dll\wxbase30u_gcc_cl.dll; DestDir: {app}; Components: core
Source: C:\SourceCode\Libraries\wxWidgets-3.0.1\lib\gcc_dll\wxbase30u_xml_gcc_cl.dll; DestDir: {app}; Components: core
Source: C:\SourceCode\Libraries\wxWidgets-3.0.1\lib\gcc_dll\wxmsw30u_core_gcc_cl.dll; DestDir: {app}; Components: core
Source: C:\SourceCode\Libraries\wxWidgets-3.0.1\lib\gcc_dll\wxmsw30u_adv_gcc_cl.dll; DestDir: {app}; Components: core
Source: C:\SourceCode\Libraries\wxWidgets-3.0.1\lib\gcc_dll\wxmsw30u_aui_gcc_cl.dll; DestDir: {app}; Components: core
Source: C:\SourceCode\Libraries\wxWidgets-3.0.1\lib\gcc_dll\wxmsw30u_propgrid_gcc_cl.dll; DestDir: {app}; Components: core
Source: C:\SourceCode\Libraries\wxWidgets-3.0.1\lib\gcc_dll\wxmsw30u_stc_gcc_cl.dll; DestDir: {app}; Components: core
Source: C:\SourceCode\Libraries\wxWidgets-3.0.1\lib\gcc_dll\wxmsw30u_xrc_gcc_cl.dll; DestDir: {app}; Components: core
Source: ..\..\readme_bin.txt; DestDir: {app}; Components: core
Source: ..\..\LICENSE.txt; DestDir: {app}; Components: core
Source: ..\..\samples\TestFullApp.cdp; DestDir: {app}\samples; Components: samples
Source: ..\..\samples\TestClass.cdp; DestDir: {app}\samples; Components: samples
Source: ..\..\output\wxmsw30u_shapeframework_cd.dll; DestDir: {app}; Components: core
Source: ..\..\output\codedesigner.exe; DestDir: {app}; Components: core
Source: ..\..\output\codedesigner-ctags.exe; DestDir: {app}; Components: core
Source: ..\..\output\cdprojectbase.dll; DestDir: {app}; Components: core
Source: ..\..\output\plugins\genuml.dll; DestDir: {app}\plugins; Components: umlgenerator
Source: ..\..\output\plugins\diaguml.dll; DestDir: {app}\plugins; Components: umldiagram
Source: ..\..\output\plugins\codelite.dll; DestDir: {app}\plugins; Components: codelite
Source: ..\..\output\plugins\reveng.dll; DestDir: {app}\plugins; Components: reveng
Source: ..\..\output\res\app\elements\Tool.xpm; DestDir: {app}\res\app\elements; Components: core
Source: ..\..\output\res\app\elements\Bound.xpm; DestDir: {app}\res\app\elements; Components: core
Source: ..\..\output\res\app\elements\LineNote.xpm; DestDir: {app}\res\app\elements; Components: core
Source: ..\..\output\res\app\elements\Note.xpm; DestDir: {app}\res\app\elements; Components: core
Source: ..\..\output\res\app\gui\ZoomAllDis.xpm; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\actionrun.png; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\actionrun.xpm; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\AlignBottom.xpm; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\AlignCenter.xpm; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\AlignLeft.xpm; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\AlignMiddle.xpm; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\AlignRight.xpm; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\AlignTop.xpm; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\AlignCircle.xpm; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\AlignMesh.xpm; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\AlignHTree.xpm; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\AlignVTree.xpm; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\application-icon.ico; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\application-icon.png; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\collapse.xpm; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\configure.png; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\configure.xpm; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\copy.xpm; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\cut.xpm; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\delete.xpm; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\editcopy.png; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\editcopy.xpm; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\editcut.png; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\editcut.xpm; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\editor-icon.ico; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\editor-icon.png; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\editpaste.png; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\editpaste.xpm; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\exit.png; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\exit.xpm; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\filenew.png; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\filenew.xpm; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\fileopen.png; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\fileopen.xpm; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\filepreview.png; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\filepreview.xpm; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\fileprint.png; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\fileprint.xpm; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\filesave.png; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\filesaveas.png; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\filesave.xpm; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\filesaveas.xpm; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\form_blue.xpm; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\GenAll.xpm; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\Grid.xpm; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\helpindex.png; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\helpindex.xpm; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\link_editor.xpm; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\new.xpm; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\organisation.png; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\organisation.xpm; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\paste.xpm; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\Preview.xpm; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\quit.xpm; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\redo.png; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\redo.xpm; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\spellcheck.png; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\spellcheck.xpm; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\throbber.gif; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\undo.png; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\undo.xpm; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\wizard-icon.png; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\wx.xpm; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\Zoom100.xpm; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\Zoom100Dis.xpm; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\gui\ZoomAll.xpm; DestDir: {app}\res\app\gui; Components: core
Source: ..\..\output\res\app\project\Variable_locked.xpm; DestDir: {app}\res\app\project; Components: core
Source: ..\..\output\res\app\project\collapse.png; DestDir: {app}\res\app\project; Components: core
Source: ..\..\output\res\app\project\collapse.xpm; DestDir: {app}\res\app\project; Components: core
Source: ..\..\output\res\app\project\cube_green.png; DestDir: {app}\res\app\project; Components: core
Source: ..\..\output\res\app\project\cube_green.xpm; DestDir: {app}\res\app\project; Components: core
Source: ..\..\output\res\app\project\cube_yellow.png; DestDir: {app}\res\app\project; Components: core
Source: ..\..\output\res\app\project\cube_yellow.xpm; DestDir: {app}\res\app\project; Components: core
Source: ..\..\output\res\app\project\cubes.png; DestDir: {app}\res\app\project; Components: core
Source: ..\..\output\res\app\project\cubes.xpm; DestDir: {app}\res\app\project; Components: core
Source: ..\..\output\res\app\project\Folder.xpm; DestDir: {app}\res\app\project; Components: core
Source: ..\..\output\res\app\project\Folder_code.xpm; DestDir: {app}\res\app\project; Components: core
Source: ..\..\output\res\app\project\Function.xpm; DestDir: {app}\res\app\project; Components: core
Source: ..\..\output\res\app\project\Function_link.xpm; DestDir: {app}\res\app\project; Components: core
Source: ..\..\output\res\app\project\Function_locked.xpm; DestDir: {app}\res\app\project; Components: core
Source: ..\..\output\res\app\project\link_editor.png; DestDir: {app}\res\app\project; Components: core
Source: ..\..\output\res\app\project\link_editor.xpm; DestDir: {app}\res\app\project; Components: core
Source: ..\..\output\res\app\project\Package.xpm; DestDir: {app}\res\app\project; Components: core
Source: ..\..\output\res\app\project\Param.xpm; DestDir: {app}\res\app\project; Components: core
Source: ..\..\output\res\app\project\Root.xpm; DestDir: {app}\res\app\project; Components: core
Source: ..\..\output\res\app\project\Variable.xpm; DestDir: {app}\res\app\project; Components: core
Source: ..\..\output\res\app\project\Variable_link.xpm; DestDir: {app}\res\app\project; Components: core
Source: ..\..\output\res\plugins\elements\UseCase.xpm; DestDir: {app}\res\plugins\elements; Components: umldiagram
Source: ..\..\output\res\plugins\elements\Actor.xpm; DestDir: {app}\res\plugins\elements; Components: umldiagram
Source: ..\..\output\res\plugins\elements\Bound.xpm; DestDir: {app}\res\plugins\elements; Components: umldiagram
Source: ..\..\output\res\plugins\elements\Class.xpm; DestDir: {app}\res\plugins\elements; Components: umldiagram
Source: ..\..\output\res\plugins\elements\ClassTempl.xpm; DestDir: {app}\res\plugins\elements; Components: umldiagram
Source: ..\..\output\res\plugins\elements\Collab.xpm; DestDir: {app}\res\plugins\elements; Components: umldiagram
Source: ..\..\output\res\plugins\elements\CompState.xpm; DestDir: {app}\res\plugins\elements; Components: umldiagram
Source: ..\..\output\res\plugins\elements\Decision.xpm; DestDir: {app}\res\plugins\elements; Components: umldiagram
Source: ..\..\output\res\plugins\elements\Entry.xpm; DestDir: {app}\res\plugins\elements; Components: umldiagram
Source: ..\..\output\res\plugins\elements\Exit.xpm; DestDir: {app}\res\plugins\elements; Components: umldiagram
Source: ..\..\output\res\plugins\elements\Final.xpm; DestDir: {app}\res\plugins\elements; Components: umldiagram
Source: ..\..\output\res\plugins\elements\ForkJoinHor.xpm; DestDir: {app}\res\plugins\elements; Components: umldiagram
Source: ..\..\output\res\plugins\elements\ForkJoinVert.xpm; DestDir: {app}\res\plugins\elements; Components: umldiagram
Source: ..\..\output\res\plugins\elements\History.xpm; DestDir: {app}\res\plugins\elements; Components: umldiagram
Source: ..\..\output\res\plugins\elements\Initial.xpm; DestDir: {app}\res\plugins\elements; Components: umldiagram
Source: ..\..\output\res\plugins\elements\Line1.xpm; DestDir: {app}\res\plugins\elements; Components: umldiagram
Source: ..\..\output\res\plugins\elements\Line2.xpm; DestDir: {app}\res\plugins\elements; Components: umldiagram
Source: ..\..\output\res\plugins\elements\Line3.xpm; DestDir: {app}\res\plugins\elements; Components: umldiagram
Source: ..\..\output\res\plugins\elements\Line4.xpm; DestDir: {app}\res\plugins\elements; Components: umldiagram
Source: ..\..\output\res\plugins\elements\Line5.xpm; DestDir: {app}\res\plugins\elements; Components: umldiagram
Source: ..\..\output\res\plugins\elements\Line6.xpm; DestDir: {app}\res\plugins\elements; Components: umldiagram
Source: ..\..\output\res\plugins\elements\Line7.xpm; DestDir: {app}\res\plugins\elements; Components: umldiagram
Source: ..\..\output\res\plugins\elements\Line8.xpm; DestDir: {app}\res\plugins\elements; Components: umldiagram
Source: ..\..\output\res\plugins\elements\Line9.xpm; DestDir: {app}\res\plugins\elements; Components: umldiagram
Source: ..\..\output\res\plugins\elements\State.xpm; DestDir: {app}\res\plugins\elements; Components: umldiagram
Source: ..\..\output\res\plugins\elements\SubState.xpm; DestDir: {app}\res\plugins\elements; Components: umldiagram
Source: ..\..\output\res\plugins\elements\Enum.xpm; DestDir: {app}\res\plugins\elements; Components: umldiagram
Source: ..\..\output\res\plugins\elements\ClassTempl.xpm; DestDir: {app}\res\plugins\elements; Components: umldiagram
Source: ..\..\output\res\plugins\project\UseCaseDiag.xpm; DestDir: {app}\res\plugins\project; Components: umldiagram
Source: ..\..\output\res\plugins\project\Action.xpm; DestDir: {app}\res\plugins\project; Components: umldiagram
Source: ..\..\output\res\plugins\project\Action_link.xpm; DestDir: {app}\res\plugins\project; Components: umldiagram
Source: ..\..\output\res\plugins\project\Action_locked.xpm; DestDir: {app}\res\plugins\project; Components: umldiagram
Source: ..\..\output\res\plugins\project\ClassDiag.xpm; DestDir: {app}\res\plugins\project; Components: umldiagram
Source: ..\..\output\res\plugins\project\Condition.xpm; DestDir: {app}\res\plugins\project; Components: umldiagram
Source: ..\..\output\res\plugins\project\Condition_link.xpm; DestDir: {app}\res\plugins\project; Components: umldiagram
Source: ..\..\output\res\plugins\project\Condition_locked.xpm; DestDir: {app}\res\plugins\project; Components: umldiagram
Source: ..\..\output\res\plugins\project\Event.xpm; DestDir: {app}\res\plugins\project; Components: umldiagram
Source: ..\..\output\res\plugins\project\Event_link.xpm; DestDir: {app}\res\plugins\project; Components: umldiagram
Source: ..\..\output\res\plugins\project\Event_locked.xpm; DestDir: {app}\res\plugins\project; Components: umldiagram
Source: ..\..\output\res\plugins\project\MemberData.xpm; DestDir: {app}\res\plugins\project; Components: umldiagram
Source: ..\..\output\res\plugins\project\MemberData_link.xpm; DestDir: {app}\res\plugins\project; Components: umldiagram
Source: ..\..\output\res\plugins\project\MemberFunction.xpm; DestDir: {app}\res\plugins\project; Components: umldiagram
Source: ..\..\output\res\plugins\project\MemberFunction_link.xpm; DestDir: {app}\res\plugins\project; Components: umldiagram
Source: ..\..\output\res\plugins\project\SimpleStateChartDiag.xpm; DestDir: {app}\res\plugins\project; Components: umldiagram
Source: ..\..\output\res\plugins\project\StateChartDiag.xpm; DestDir: {app}\res\plugins\project; Components: umldiagram
Source: ..\..\output\res\plugins\project\EnumVal.xpm; DestDir: {app}\res\plugins\project; Components: umldiagram
Source: ..\..\output\res\plugins\gui\scriptimport.xpm; DestDir: {app}\res\plugins\gui; Components: reveng
Source: ..\..\output\res\app\gui\splash.png; DestDir: {app}\res\app\gui
[Dirs]
Name: {app}\plugins; Components: core
Name: {app}\res; Components: core
Name: {app}\samples; Components: samples
Name: {app}\res\app; Components: core
Name: {app}\res\plugins; Components: core
Name: {app}\res\app\elements; Components: core
Name: {app}\res\app\gui; Components: core
Name: {app}\res\app\project; Components: core
Name: {app}\res\plugins\elements; Components: core
Name: {app}\res\plugins\project; Components: core
Name: {app}\res\plugins\gui; Components: core
[Components]
Name: core; Description: Main application files; Flags: fixed; Types: custom compact full
Name: umldiagram; Description: UML diagrams; Types: custom full
Name: umlgenerator; Description: UML code generators; Types: custom full
Name: codelite; Description: CodeLite integration; Types: custom full
Name: reveng; Description: Reverse code engineering; Types: custom full
Name: samples; Description: Sample projects; Types: custom full
[Icons]
Name: {group}\CodeDesigner RAD; Filename: {app}\codedesigner.exe; WorkingDir: {app}; IconFilename: {app}\res\app\gui\application-icon.ico; Comment: CodeDesigner RAD; Components: core; IconIndex: 0
Name: {group}\Uninstall CodeDesigner RAD; Filename: {uninstallexe}
Name: {commondesktop}\CodeDesigner RAD; Filename: {app}\codedesigner.exe; Components: core; Tasks: desktopicon\common; IconIndex: 0
Name: {userdesktop}\CodeDesigner RAD; Filename: {app}\codedesigner.exe; Components: core; Tasks: desktopicon\user; IconIndex: 0
[Registry]
Root: HKCR; Subkey: .cdp; ValueType: string; ValueData: CodeDesignerProjectFile; Flags: uninsdeletevalue
Root: HKCR; Subkey: CodeDesignerProjectFile; ValueType: string; ValueName: ; ValueData: CodeDesigner RAD project file; Flags: uninsdeletekey
Root: HKCR; Subkey: CodeDesignerProjectFile\DefaultIcon; ValueType: string; ValueName: ; ValueData: {app}\codedesigner.exe,0
Root: HKCR; Subkey: CodeDesignerProjectFile\shell\open\command; ValueType: string; ValueName: ; ValueData: """{app}\codedesigner.exe"" ""%1"""
[Tasks]
Name: desktopicon; Description: Create a &desktop icon; GroupDescription: Additional icons:; Components: core
Name: desktopicon\common; Description: For all users; GroupDescription: Additional icons:; Components: core; Flags: exclusive
Name: desktopicon\user; Description: For the current user only; GroupDescription: Additional icons:; Components: core; Flags: exclusive unchecked
[Run]
Filename: {app}\readme_bin.txt; Description: View the README file; Flags: postinstall shellexec skipifsilent
Filename: {app}\codedesigner.exe; Description: Launch application; Flags: postinstall nowait skipifsilent unchecked











