#include "wx_pch.h"

#ifdef _DEBUG_MSVC
#define new DEBUG_NEW
#endif

#include <wx/wfstream.h>
#include <wx/txtstrm.h>

#include "codegen/base/ProjectGenerator.h"
#include "UMLDesignerApp.h"
#include "UMLDesignerMain.h"
#include "Project.h"

IMPLEMENT_DYNAMIC_CLASS(udProjectGenerator, wxObject);

// constructor and destructor ///////////////////////////////////////////////////////////////////////////////

udProjectGenerator::udProjectGenerator()
{
	m_pOutLang = NULL;
}

udProjectGenerator::~udProjectGenerator()
{
}

// public finctions /////////////////////////////////////////////////////////////////////////////////////////

void udProjectGenerator::Generate(udProject *src)
{
	wxASSERT( m_pOutLang );
	
	if( wxGetApp().GetRunMode() != UMLDesignerApp::runSILENT )
	{
		wxGetApp().GetMainFrame()->GetLogWindow()->ClearMessages();
	}
	
	if( CheckAlgorithms( src ) )
	{
		// initialize generator
		this->Initialize();

		// process project
		this->ProcessProject(src);

		// clean-up generator
		this->CleanUp();
	}
	else
		wxMessageBox( wxT("Unable to generate project code."), wxT("CodeDesigner"), wxOK | wxICON_ERROR );
}

wxString udProjectGenerator::BeginMark(const wxString& mark)
{
	// create full code mark
	wxString sFullMark = wxString::Format( wxT("['%s' begin (DON'T REMOVE THIS LINE!)]"), mark.c_str() );
	
	// wrap the code mark into comment
	if( m_pOutLang )
	{
		m_pOutLang->PushCode();
		m_pOutLang->SingleLineCommentCmd( sFullMark );
		
		wxString sOut = m_pOutLang->GetCodeBuffer();
		m_pOutLang->PopCode();
		
		return sOut.Trim().Trim( false );
	}
	else
		return sFullMark;
}

wxString udProjectGenerator::EndMark(const wxString& mark)
{
	// create full code mark
	wxString sFullMark = wxString::Format( wxT("['%s' end (DON'T REMOVE THIS LINE!)]"), mark.c_str() );
	
	// wrap the code mark into comment
	if( m_pOutLang )
	{
		m_pOutLang->PushCode();
		m_pOutLang->SingleLineCommentCmd( sFullMark );
		
		wxString sOut = m_pOutLang->GetCodeBuffer();
		m_pOutLang->PopCode();
		
		return sOut.Trim().Trim( false );
	}
	else
		return sFullMark;
}

// protected virtual functions //////////////////////////////////////////////////////////////////////////////

void udProjectGenerator::Initialize()
{
	UMLDesignerApp::SetLogMask( UMLDesignerApp::logWARNINGS | UMLDesignerApp::logERRORS );
	
	wxSetCursor( *wxHOURGLASS_CURSOR );
}

void udProjectGenerator::ProcessProject(udProject *src)
{
}

void udProjectGenerator::CleanUp()
{
	UMLDesignerApp::SetLogMask( UMLDesignerApp::logALL );
	
	wxSetCursor( *wxSTANDARD_CURSOR );
}

// protected functions //////////////////////////////////////////////////////////////////////////////////////

void udProjectGenerator::ClearCodemark(const wxString& mark, const wxFileName& file)
{
	if( file.IsFileReadable() )
	{
		bool fInside = false;
		wxString sOutput, sLine;
		
		wxFileInputStream in( file.GetFullPath() );
		if( in.IsOk() )
		{
			wxTextInputStream tin( in );
			// remove all lines between code marks
			while( !in.Eof() )
			{
				sLine = tin.ReadLine();
				if( !fInside )
				{
					if( !sLine.Contains( BeginMark( mark ) ) ) sOutput << sLine << ENDL;
					else
					{
						sOutput << BeginMark( mark ) << ENDL;
						fInside = true;
					}
				}
				else
				{
					if( sLine.Contains( EndMark( mark ) ) )
					{
						sOutput << EndMark( mark ) << ENDL;
						fInside = false;
					}
				}
			}
		}
		
		// write output to the file
		WriteToFile( sOutput, file );
	}
}

void udProjectGenerator::InsertCodemark(const wxString& mark, const wxFileName& file, const wxString& after)
{
	wxString sLine, sOutput;
	bool fInserted = false;
	
	if( file.IsFileReadable() )
	{
		wxFileInputStream in( file.GetFullPath() );
		if( in.IsOk() )
		{
			wxTextInputStream tin( in );
			while( !in.Eof() )
			{
				sLine = tin.ReadLine();
				
				sOutput << sLine << ENDL;
				if( !fInserted && sLine.Contains( after ) )
				{
					sOutput << BeginMark( mark ) << ENDL;
					sOutput << EndMark( mark ) << ENDL;
					fInserted = true;
				}
			}
		}
	}
	else
	{
		sOutput << BeginMark( mark ) << ENDL;
		sOutput << EndMark( mark ) << ENDL;
	}
	
	// write output to the file
	WriteToFile( sOutput, file );
}

void udProjectGenerator::InsertCodemark(const wxString& mark, const wxFileName& file, int pos)
{
	wxString sOutput;
	int nCounter = 0;
	bool fInserted = false;
	
	if( file.IsFileReadable() )
	{
		wxFileInputStream in( file.GetFullPath() );
		if( in.IsOk() )
		{
			wxTextInputStream tin( in );
			while( !in.Eof() )
			{			
				if( !fInserted && (nCounter == pos) )
				{
					sOutput << BeginMark( mark ) << ENDL;
					sOutput << EndMark( mark ) << ENDL;
					fInserted = true;
				}
				sOutput << tin.ReadLine() << ENDL;
			}
			
			// append mark to the end of the file
			if( pos == -1)
			{
				sOutput << BeginMark( mark ) << ENDL;
				sOutput << EndMark( mark ) << ENDL;
			}
		}
	}
	else
	{
		sOutput << BeginMark( mark ) << ENDL;
		sOutput << EndMark( mark ) << ENDL;		
	}

	// write output to the file
	WriteToFile( sOutput, file );
}

void udProjectGenerator::InsertIntoCodemark(const wxString& txt, const wxString& mark, const wxFileName& file)
{	
	if( file.IsFileReadable() )
	{
		wxString sOutput, sLine;
	
		wxFileInputStream in( file.GetFullPath() );
		if( in.IsOk() )
		{
			wxTextInputStream tin( in );
			while( !in.Eof() )
			{
				sLine = tin.ReadLine();
				
				sOutput << sLine << ENDL;
				if( sLine.Contains( BeginMark( mark ) ) )
				{
					sOutput << txt;
				}
			}
		}
		
		// write output to the file
		WriteToFile( sOutput, file );
	}
}

wxString udProjectGenerator::GetCodeFromCodemark(const udCodeItem *item, const wxFileName& file)
{
	wxString sOutput, sPrevOutput;
	bool fFound = false;
	
	if( file.IsFileReadable() )
	{
		wxString sLine;
		bool fInside = false;
		int nIndentation = 0;
		
		wxFileInputStream in( file.GetFullPath() );
		if( in.IsOk() )
		{
			wxTextInputStream tin( in );
			while( !in.Eof() )
			{
				sLine = tin.ReadLine();

				if( sLine.Contains( udGenerator::GetBeginCodeMark( item ) ) )
				{	
					fFound = true;
					fInside = true;
					sOutput = wxT("");
					
					// TODO: implement smarter indentation calculation in code synchronization (it is broken
					// for mixed tabs and spaces...
					nIndentation = sLine.Len() - sLine.Trim(false).Len();
				}
				else if( sLine.Contains( udGenerator::GetEndCodeMark( item ) ) )
				{
					fInside = false;
					sOutput.Trim();
					
					if( !sPrevOutput.IsEmpty() && (sOutput != sPrevOutput ) )
					{
						return wxT("<ambiguous>");
					}
					else
						sPrevOutput = sOutput;
				}
				else
					if( fInside ) sOutput << sLine.Mid( nIndentation ) + ENDL;
			}
		}
	}
	
	if( fFound )return sOutput;
	else
		return wxT("<not found>");
}


void udProjectGenerator::WriteToFile(const wxString& txt, const wxFileName& file)
{
	wxString sOutput = txt;
	
	// insert just one empty line at the end of the file
	sOutput.Trim();
	sOutput << ENDL;
	
	// save output to the file
	wxFileOutputStream out( file.GetFullPath() );
	if( out.IsOk() )
	{
		wxTextOutputStream tout( out );
		#ifdef __WXMSW__
		tout.SetMode( wxEOL_UNIX );
		#endif
		tout << sOutput;
			
		out.Close();
		
		if( m_arrGeneratedFiles.Index( file.GetFullPath() ) == wxNOT_FOUND ) m_arrGeneratedFiles.Add( file.GetFullPath() );
	}
}

bool udProjectGenerator::CodemarkExists(const wxString& mark, const wxFileName& file)
{
	if( file.IsFileReadable() )
	{
		wxFileInputStream in( file.GetFullPath() );
		if( in.IsOk() )
		{
			wxTextInputStream tin( in );
			while( !in.Eof() )
			{
				if( tin.ReadLine().Contains( BeginMark( mark ) ) ) return true;
			}
		}
	}

	return false;
}

void udProjectGenerator::Log(const wxString& msg)
{
	int m_nPrevLogMask = UMLDesignerApp::GetLogMask();
	
	UMLDesignerApp::SetLogMask( UMLDesignerApp::logALL );
	UMLDesignerApp::Log( msg );
	UMLDesignerApp::SetLogMask( m_nPrevLogMask );
}

bool udProjectGenerator::CheckAlgorithms(udProject* src)
{
	// check, whether all currently set algorithms in project's diagram support used language
	bool fSuccess = true;
	
	udDiagramItem *pDiagram;
	udGenerator *pGenerator;
	
	SerializableList lstDiagrams;
	src->GetDiagramsRecursively( CLASSINFO(udDiagramItem), lstDiagrams );
	
	SerializableList::compatibility_iterator node = lstDiagrams.GetFirst();
	while( node )
	{
		pDiagram = (udDiagramItem*) node->GetData();
		
		pGenerator = udPROJECT::CreateGenerator( pDiagram );
		if( pGenerator )
		{
			if( pGenerator->GetActiveAlgorithm()->GetSupportedLanguages().Index( m_pOutLang->GetClassInfo()->GetClassName() ) == wxNOT_FOUND )
			{
				Log( wxString::Format( wxT("ERROR: Code generation algorithm used in '%s' diagram doesn't support selected programming language.\n"), pDiagram->GetName().c_str() ) );
				fSuccess = false;
			}
			delete pGenerator;
		}
		
		node = node->GetNext();
	}
	
	return fSuccess;
}

wxFileName udProjectGenerator::GetFullCodePath(const wxString& name, const wxString& ext)
{
	// get settings of processed project
	udProjectSettings& Settings = udProject::Get()->GetSettings();
	
	wxString sPath;
	wxFileName fnOutDir, fnOutFile;
	
	fnOutDir.SetPath( Settings.GetProperty(wxT("Output directory"))->ToString() );
	fnOutFile.SetPath( name );
	
	if( fnOutFile.IsRelative() )
	{
		if( fnOutDir.IsRelative() )
		{
			sPath = udProject::Get()->GetProjectDirectory() + wxFileName::GetPathSeparator();
		}
		
		sPath += fnOutDir.GetPath() + wxFileName::GetPathSeparator() + name + ext;
	}
	else
		sPath += name + ext;
	
	return wxFileName( sPath );
}

void udProjectGenerator::GetModifiedUserCode(const udLanguage* lang, SerializableList& items, wxArrayString& origcode, wxArrayString& modifcode, int *ambiguous)
{
	wxBusyCursor busy;
	
	udProject *pProject = udProject::Get();
	
	// initialize code items checklist	
	udSettings& Settings = pProject->GetSettings();
	
	// get files where modified code could be
	wxArrayString arrFiles;
	arrFiles.Add( udProjectGenerator::GetFullCodePath( Settings.GetProperty(wxT("Code items file name"))->AsString(), lang->GetExtension(udLanguage::FE_IMPL) ).GetFullPath() );
	arrFiles.Add( udProjectGenerator::GetFullCodePath( Settings.GetProperty(wxT("Base file name"))->AsString(), lang->GetExtension(udLanguage::FE_IMPL) ).GetFullPath() );
	
	SerializableList lstDiagrams;
	pProject->GetDiagramsRecursively( NULL, lstDiagrams );
	for( SerializableList::iterator it = lstDiagrams.begin(); it != lstDiagrams.end(); ++it ) {
		wxString sFileName;
		udDiagramItem *pDiagram = udPROJECT::GetSuperDiagram( (udDiagramItem*)*it );
		if( pDiagram->GetOutputFile() != wxT("<default>") ) {
			sFileName = udProjectGenerator::GetFullCodePath( pDiagram->GetOutputFile(), lang->GetExtension(udLanguage::FE_IMPL) ).GetFullPath();
			if( arrFiles.Index( sFileName ) == wxNOT_FOUND ) arrFiles.Add( sFileName );
		}
	}
	
	// get all codeitems
	SerializableList lstCodeItems;
	udProject::Get()->GetItems( CLASSINFO(udFunctionItem), lstCodeItems );
	
	UMLDesignerApp::ClearLog();
	UMLDesignerApp::Log( wxT("Starting code synchronization...") );
	
	for( size_t i = 0; i < arrFiles.GetCount(); i++ )
	{
		wxString sFileName = arrFiles[i];
		
		for( SerializableList::iterator it = lstCodeItems.begin(); it != lstCodeItems.end(); ++it )
		{
			udFunctionItem *pCodeItem = (udFunctionItem*) *it;
			
			if( pCodeItem->GetImplementation() != uddvFUNCTION_USERIMPLEMENTATION ) continue;
			
			wxString sCode = udProjectGenerator::GetCodeFromCodemark( pCodeItem, sFileName );
			if( sCode == wxT("<ambiguous>") )
			{
				(*ambiguous)++;
				UMLDesignerApp::Log( wxString::Format( wxT("WARNING: Instances of '%s::%s' generated code are ambiguous."), pCodeItem->GetScope().c_str(), pCodeItem->GetName().c_str() ) );
			}
			else if( sCode != wxT("<not found>") )
			{
				if( sCode != pCodeItem->GetCode() )
				{
					items.Append( pCodeItem );
					modifcode.Add( sCode );
					origcode.Add( pCodeItem->GetCode() );
				}
				else
					UMLDesignerApp::Log( wxString::Format( wxT("Code item '%s::%s' is identical."), pCodeItem->GetScope().c_str(), pCodeItem->GetName().c_str() ) );
			}
		}
	}
	
	UMLDesignerApp::Log( wxT("Done.") );
}
