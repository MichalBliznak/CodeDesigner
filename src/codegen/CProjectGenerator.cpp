#include "wx_pch.h"

#ifdef _DEBUG_MSVC
#define new DEBUG_NEW
#endif

#include <wx/sstream.h>

#include "Settings.h"
#include "Project.h"
#include "UMLDesignerApp.h"
#include "UMLDesignerMain.h"
#include "projectbase/gui/ProgressDialog.h"
#include "projectbase/codegen/Generator.h"
#include "codegen/CProjectGenerator.h"
#include "projectbase/codegen/CodeItemsGenerator.h"

#define COMMON_HEADERS_MARK wxT("Common headers")
#define COMMON_DECLARATIONS_MARK wxT("Common declarations for")
#define COMMON_DEFINITIONS_MARK wxT("Common definitions for")

IMPLEMENT_DYNAMIC_CLASS(udCProjectGenerator, udProjectGenerator);

// constructor and destructor ///////////////////////////////////////////////////////////////////////////////

udCProjectGenerator::udCProjectGenerator()
{
}

udCProjectGenerator::~udCProjectGenerator()
{
}

void udCProjectGenerator::Initialize()
{
	udProjectGenerator::Initialize();
}

// protected virtual functions //////////////////////////////////////////////////////////////////////////////

void udCProjectGenerator::ProcessProject(udProject *src)
{
	udDiagramItem *pDiagram;
	udGenerator *pGenerator;
	bool fSuccess;
	
	udProgressDialog progressDlg( NULL );
	
	wxArrayString arrProcessedGenerators;
	
	// get settings of processed project
	udProjectSettings& Settings = src->GetSettings();
	
	wxFileName fnOutDir;
	wxString sPath = Settings.GetProperty(wxT("Output directory"))->ToString();
	fnOutDir.SetPath( sPath );
	if( fnOutDir.IsRelative() )
	{
		sPath = udProject::Get()->GetProjectDirectory() + wxFileName::GetPathSeparator() + sPath;
	}
	
	if( !wxDirExists( sPath ) )
	{
		wxMessageBox(wxT("Output directory '") + sPath + wxT("' doesn't exist. Please check the project settings."), wxT("CodeDesigner"), wxICON_ERROR | wxOK );
		return;
	}
	 
	wxFileName OutFile, HeaderFile, CommonOutFile, CommonHeaderFile;
	
	if( m_pOutLang )
	{
		wxStringOutputStream *pOut;
		
		// get list of diagrams to be generated
		SerializableList lstDiagrams;
		src->GetDiagramsRecursively( CLASSINFO(udDiagramItem), lstDiagrams );
		
		udGenerator::ResetIDCounter();
		
		progressDlg.Clear();
		progressDlg.SetStepCount( lstDiagrams.GetCount() + 1 );
		
		progressDlg.Show();
		progressDlg.Raise();
		
		////////////////////////////////////////////////////////////////////////////////////////////////////////
		// generate code items
		
		// create generator
		udCodeItemsGenerator *pCommonGen = new udCodeItemsGenerator();
		if( pCommonGen )
		{
			pCommonGen->SetActiveLanguage(m_pOutLang);
			
			// construct output file path
			CommonOutFile = GetFullCodePath( Settings.GetProperty(wxT("Code items file name"))->AsString(), m_pOutLang->GetExtension(udLanguage::FE_IMPL) );
						
			// construct header file path
			CommonHeaderFile = GetFullCodePath( Settings.GetProperty(wxT("Code items file name"))->AsString(),m_pOutLang->GetExtension(udLanguage::FE_DECL) );
							
			////////////////////////////////////////////////////////////////////////////////////////////////////////
			// insert 'include' to declaration file
	
			// clear previous code if exists
			if( !CodemarkExists( COMMON_HEADERS_MARK, CommonHeaderFile ) ) InsertCodemark( COMMON_HEADERS_MARK, CommonHeaderFile, 0 );
			else
				ClearCodemark( COMMON_HEADERS_MARK, CommonHeaderFile );

			// Insert header to the implementation file
			InsertIntoCodemark( wxT("#include <stdio.h>\n#include <stdlib.h>\n"), COMMON_HEADERS_MARK, CommonHeaderFile );

			////////////////////////////////////////////////////////////////////////////////////////////////////////
			// common declarations
			wxString sCommonMark( wxString::Format( wxT("%s '%s'"), COMMON_DECLARATIONS_MARK, pCommonGen->GetName().c_str() ) );
			
			// clear previous code if exists
			if( !CodemarkExists( sCommonMark, CommonHeaderFile ) ) InsertCodemark( sCommonMark, CommonHeaderFile, -1 );
			else
				ClearCodemark( sCommonMark, CommonHeaderFile );	
				
			// create output stream
			pOut = new wxStringOutputStream(NULL);
			pCommonGen->SetOutputStream( pOut );
				
			pCommonGen->SetMode( udGenerator::genCOMMON_DECLARATION );
				
			// generate code
			if( pCommonGen->Generate( NULL, sfNORECURSIVE ) )
			{
				InsertIntoCodemark( pOut->GetString(), sCommonMark, CommonHeaderFile );
			}
			
			// clean-up output stream
			delete pOut;
			
			////////////////////////////////////////////////////////////////////////////////////////////////////////
			// insert 'include' to definition file
	
			// clear previous code if exists
			if( !CodemarkExists( COMMON_HEADERS_MARK, CommonOutFile ) ) InsertCodemark( COMMON_HEADERS_MARK, CommonOutFile, 0 );
			else
				ClearCodemark( COMMON_HEADERS_MARK, CommonOutFile );

			// construct header name
			wxString sCIHeaderName = Settings.GetProperty(wxT("Code items file name"))->AsString() + m_pOutLang->GetExtension(udLanguage::FE_DECL);
	
			// Insert header to the implementation file
			InsertIntoCodemark( wxString::Format( wxT("#include \"%s\""), sCIHeaderName.c_str() ) << ENDL, COMMON_HEADERS_MARK, CommonOutFile );

			////////////////////////////////////////////////////////////////////////////////////////////////////////
			// common definitions
			sCommonMark = wxString::Format( wxT("%s '%s'"), COMMON_DEFINITIONS_MARK, pCommonGen->GetName().c_str() );
					
			// clear previous code if exists
			if( !CodemarkExists( sCommonMark, CommonOutFile ) ) InsertCodemark( sCommonMark, CommonOutFile, -1 );
			else
				ClearCodemark( sCommonMark, CommonOutFile );	

			// create output stream
			pOut = new wxStringOutputStream(NULL);
			pCommonGen->SetOutputStream( pOut );
				
			pCommonGen->SetMode( udGenerator::genCOMMON_DEFINITION );
				
			// generate code
			if( pCommonGen->Generate( NULL, sfNORECURSIVE ) )
			{
				InsertIntoCodemark( pOut->GetString(), sCommonMark, CommonOutFile );
			}
					
			// clean-up output stream
			delete pOut;
		}
		
		delete pCommonGen;
		
		progressDlg.Step();
		
		////////////////////////////////////////////////////////////////////////////////////////////////////////
		// generate diagrams
		
		SerializableList::compatibility_iterator node = lstDiagrams.GetLast();
		while( node )
		{
			fSuccess = true;
			
			pDiagram = (udDiagramItem*)node->GetData();
			
			if( !pDiagram->IsGenerated() )
			{
				node = node->GetPrevious();
				continue;
			}
			
			progressDlg.SetLabel(  wxString::Format( wxT("Generating '%s'..."), pDiagram->GetName().c_str() ) );
			Log( wxString::Format( wxT("Generating code for diagram '%s'..."), pDiagram->GetName().c_str() ) );
			
			udDiagramItem *pSuperDiagram = udPROJECT::GetSuperDiagram( pDiagram );
			
			if( pSuperDiagram->GetOutputFile() == wxT("<default>") )
			{
				// construct output file path
				OutFile = GetFullCodePath( Settings.GetProperty(wxT("Base file name"))->AsString(), m_pOutLang->GetExtension(udLanguage::FE_IMPL) );
						
				// construct header file path
				HeaderFile = GetFullCodePath( Settings.GetProperty(wxT("Base file name"))->AsString(), m_pOutLang->GetExtension(udLanguage::FE_DECL) );
			}
			else
			{
				// construct output file path
				//OutFile = wxFileName( pDiagram->GetOutputFile() + m_pOutLang->GetExtension(udLanguage::FE_IMPL) );
				OutFile = GetFullCodePath( pSuperDiagram->GetOutputFile(), m_pOutLang->GetExtension(udLanguage::FE_IMPL) );
						
				// construct header file path
				//HeaderFile = wxFileName( pDiagram->GetOutputFile() + m_pOutLang->GetExtension(udLanguage::FE_DECL) );
				HeaderFile = GetFullCodePath( pSuperDiagram->GetOutputFile(), m_pOutLang->GetExtension(udLanguage::FE_DECL) );
			}
			
			Log( wxString::Format( wxT("Output files: %s, %s."), OutFile.GetFullPath().c_str(), HeaderFile.GetFullPath().c_str() ) );

			pGenerator = udPROJECT::CreateGenerator( pDiagram );
			if( pGenerator )
			{
				pGenerator->SetActiveLanguage(m_pOutLang);
				
				////////////////////////////////////////////////////////////////////////////////////////////////////////
				// create header file
				
				////////////////////////////////////////////////////////////////////////////////////////////////////////
				// generate common diagram declarations
				
				wxString sCommonMark( wxString::Format( wxT("%s '%s'"), COMMON_DECLARATIONS_MARK, pGenerator->GetName().c_str() ) );
				
				if( arrProcessedGenerators.Index( pGenerator->GetName() ) == wxNOT_FOUND )
				{
					// clear previous code if exists
					if( !CodemarkExists( sCommonMark, CommonHeaderFile ) ) InsertCodemark( sCommonMark, CommonHeaderFile, -1 );
					else
						ClearCodemark( sCommonMark, CommonHeaderFile );	

					// create output stream
					pOut = new wxStringOutputStream(NULL);
					pGenerator->SetOutputStream( pOut );
				
					pGenerator->SetMode( udGenerator::genCOMMON_DECLARATION );
				
					// generate code
					fSuccess = pGenerator->Generate( pDiagram, sfNORECURSIVE );
					if( fSuccess )
					{
						InsertIntoCodemark( pOut->GetString(), sCommonMark, CommonHeaderFile );
					}
					
					// clean-up output stream
					delete pOut;
				}
		
				////////////////////////////////////////////////////////////////////////////////////////////////////////
				// generate declaration
				
				////////////////////////////////////////////////////////////////////////////////////////////////////////
				// insert 'include' to declaration file
		
				// clear previous code if exists
				if( !CodemarkExists( COMMON_HEADERS_MARK, HeaderFile ) ) InsertCodemark( COMMON_HEADERS_MARK, HeaderFile, 0 );
				else
					ClearCodemark( COMMON_HEADERS_MARK, HeaderFile );
	
				// construct header name
				wxString sCIHeaderName = Settings.GetProperty(wxT("Code items file name"))->AsString() + m_pOutLang->GetExtension(udLanguage::FE_DECL);
		
				// Insert header to the implementation file
				InsertIntoCodemark( wxString::Format( wxT("#include \"%s\""), sCIHeaderName.c_str() ) << ENDL, COMMON_HEADERS_MARK, HeaderFile );
				
				if( fSuccess )
				{
					// create output stream
					pOut = new wxStringOutputStream(NULL);				
					pGenerator->SetOutputStream(pOut);

					pGenerator->SetMode( udGenerator::genDECLARATION );
					
					// clear previous code if exists
					if( !CodemarkExists( pDiagram->GetName(), HeaderFile ) )
						// append mark to the end of the file (position == -1)
						InsertCodemark( pDiagram->GetName(), HeaderFile, -1 );
					else
						ClearCodemark( pDiagram->GetName(), HeaderFile );
						
					// generate code
					fSuccess =  pGenerator->Generate( pDiagram, sfNORECURSIVE );
					if( fSuccess )
					{
						InsertIntoCodemark( pOut->GetString(), pDiagram->GetName(), HeaderFile );
					}
					
					// clean-up output stream
					delete pOut;
				}
				
				////////////////////////////////////////////////////////////////////////////////////////////////////////
				// insert header guards
				
				// TODO: insert header guards

				////////////////////////////////////////////////////////////////////////////////////////////////////////
				// create definition file
				

				////////////////////////////////////////////////////////////////////////////////////////////////////////
				// insert 'include' to definition file
		
				// clear previous code if exists
				if( !CodemarkExists( COMMON_HEADERS_MARK, OutFile ) ) InsertCodemark( COMMON_HEADERS_MARK, OutFile, 0 );
				else
					ClearCodemark( COMMON_HEADERS_MARK, OutFile );
	
				// construct header name
				wxString sHeaderName;
				if( pSuperDiagram->GetOutputFile() == wxT("<default>") )
				{
					sHeaderName = Settings.GetProperty(wxT("Base file name"))->AsString() + m_pOutLang->GetExtension(udLanguage::FE_DECL);
				}
				else
					sHeaderName = pSuperDiagram->GetOutputFile() + m_pOutLang->GetExtension(udLanguage::FE_DECL);
				//sCIHeaderName = Settings.GetProperty(wxT("Code items file name"))->AsString() + m_pOutLang->GetExtension(udLanguage::FE_DECL);
		
				// Insert header to the implementation file
				//InsertIntoCodemark( wxString::Format( wxT("#include \"%s\""), sHeaderName.c_str() ) << ENDL << wxString::Format( wxT("#include \"%s\""), sCIHeaderName.c_str() ) << ENDL, COMMON_HEADERS_MARK, OutFile );
				InsertIntoCodemark( wxString::Format( wxT("#include \"%s\""), sHeaderName.c_str() ) << ENDL, COMMON_HEADERS_MARK, OutFile );
				
				////////////////////////////////////////////////////////////////////////////////////////////////////////
				// generate common definition
				
				if( fSuccess && (arrProcessedGenerators.Index( pGenerator->GetName() ) == wxNOT_FOUND) )
				{
					sCommonMark = wxString::Format( wxT("%s '%s'"), COMMON_DEFINITIONS_MARK, pGenerator->GetName().c_str() );
					
					// clear previous code if exists
					if( !CodemarkExists( sCommonMark, CommonOutFile ) ) InsertCodemark( sCommonMark, CommonOutFile, -1 );
					else
						ClearCodemark( sCommonMark, CommonOutFile );	

					// create output stream
					pOut = new wxStringOutputStream(NULL);
					pGenerator->SetOutputStream( pOut );
				
					pGenerator->SetMode( udGenerator::genCOMMON_DEFINITION );
				
					// generate code
					fSuccess = pGenerator->Generate( pDiagram, sfNORECURSIVE );
					if( fSuccess )
					{
						InsertIntoCodemark( pOut->GetString(), sCommonMark, CommonOutFile );
					}
					
					// clean-up output stream
					delete pOut;
					
					arrProcessedGenerators.Add( pGenerator->GetName() );
				}
				
				////////////////////////////////////////////////////////////////////////////////////////////////////////
				// generate definition
				
				if( fSuccess )
				{
					// create output stream
					pOut = new wxStringOutputStream(NULL);
					
					pGenerator->SetOutputStream( pOut );
					pGenerator->SetMode( udGenerator::genDEFINITION );
					
					// clear previous code if exists
					if( !CodemarkExists( pDiagram->GetName(), OutFile ) )
						// append mark to the end of the file (position == -1)
						InsertCodemark( pDiagram->GetName(), OutFile, -1 );
					else
						ClearCodemark( pDiagram->GetName(), OutFile );
						
					// generate code
					fSuccess = pGenerator->Generate( pDiagram, sfNORECURSIVE );
					if( fSuccess )
					{
						InsertIntoCodemark( pOut->GetString(), pDiagram->GetName(), OutFile );
					}
					
					// clean-up output stream
					delete pOut;
				}
				// clean-up code generator;
				delete pGenerator;
				
				if( !fSuccess ) wxMessageBox(wxT("Generation process finished with ERROR status. See the log window for more details."), wxT("CodeDesigner"), wxOK | wxICON_WARNING);
				
				progressDlg.Step();
				Log( wxT("Done.") );
			}
			node = node->GetPrevious();
		}
	}
}

void udCProjectGenerator::CleanUp()
{
	udProjectGenerator::CleanUp();
}

