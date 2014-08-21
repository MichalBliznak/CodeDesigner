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
#include "projectbase/codegen/CodeItemsGenerator.h"
#include "codegen/PythonProjectGenerator.h"

#define COMMON_HEADERS_MARK wxT("Common imports")
#define COMMON_DEFINITIONS_MARK wxT("Common definitions for")

IMPLEMENT_DYNAMIC_CLASS(udPythonProjectGenerator, udProjectGenerator);

// constructor and destructor ///////////////////////////////////////////////////////////////////////////////

udPythonProjectGenerator::udPythonProjectGenerator()
{
}

udPythonProjectGenerator::~udPythonProjectGenerator()
{
}

void udPythonProjectGenerator::Initialize()
{
	udProjectGenerator::Initialize();
}

// protected virtual functions //////////////////////////////////////////////////////////////////////////////

void udPythonProjectGenerator::ProcessProject(udProject *src)
{
	udDiagramItem *pDiagram;
	udGenerator *pGenerator;
	bool fSuccess;
	wxArrayString arrProcessedGenerators;
	
	udProgressDialog progressDlg( NULL );
	
	// get settings of processed project
	udProjectSettings& Settings = src->GetSettings();
	
	wxString sCommonMark;
		
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
	 
	wxFileName OutFile, DeclFile;
	
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
			OutFile = GetFullCodePath( Settings.GetProperty(wxT("Code items file name"))->AsString(), m_pOutLang->GetExtension(udLanguage::FE_IMPL) );
						   
			// common definitions
			sCommonMark = wxString::Format( wxT("%s '%s'"), COMMON_DEFINITIONS_MARK, pCommonGen->GetName().c_str() );
					
			// clear previous code if exists
			if( !CodemarkExists( sCommonMark, OutFile ) ) InsertCodemark( sCommonMark, OutFile, -1 );
			else
				ClearCodemark( sCommonMark, OutFile );	

			// create output stream
			pOut = new wxStringOutputStream(NULL);
			pCommonGen->SetOutputStream( pOut );
				
			pCommonGen->SetMode( udGenerator::genCOMMON_DEFINITION );
				
			// generate code
			if( pCommonGen->Generate( NULL, sfNORECURSIVE ) )
			{
				InsertIntoCodemark( pOut->GetString(), sCommonMark, OutFile );
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
			}
			else
			{
				// construct output file path
				OutFile = GetFullCodePath( pSuperDiagram->GetOutputFile(), m_pOutLang->GetExtension(udLanguage::FE_IMPL) );
			}
			
			Log( wxString::Format( wxT("Output file: %s."), OutFile.GetFullPath().c_str() ) );

			pGenerator = udPROJECT::CreateGenerator( pDiagram );
			if( pGenerator )
			{
				pGenerator->SetActiveLanguage(m_pOutLang);
		
				////////////////////////////////////////////////////////////////////////////////////////////////////////
				// insert 'import' to definition file
		
				// clear previous code if exists
				if( !CodemarkExists( COMMON_HEADERS_MARK, OutFile ) ) InsertCodemark( COMMON_HEADERS_MARK, OutFile, 0 );
				else
					ClearCodemark( COMMON_HEADERS_MARK, OutFile );
	
				// construct header name
				wxString sImportName = Settings.GetProperty(wxT("Code items file name"))->AsString();
		
				// Insert header to the implementation file
				InsertIntoCodemark( wxString::Format( wxT("from %s import *"), sImportName.c_str() ) << ENDL, COMMON_HEADERS_MARK, OutFile );

				////////////////////////////////////////////////////////////////////////////////////////////////////////
				// create definition file
								
				////////////////////////////////////////////////////////////////////////////////////////////////////////
				// generate common definition

				if( arrProcessedGenerators.Index( pGenerator->GetName() ) == wxNOT_FOUND )
				{
					sCommonMark = wxString::Format( wxT("%s '%s'"), COMMON_DEFINITIONS_MARK, pGenerator->GetName().c_str() );
							
					// clear previous code if exists
					if( !CodemarkExists( sCommonMark, OutFile ) ) InsertCodemark( sCommonMark, OutFile, -1 );
					else
						ClearCodemark( sCommonMark, OutFile );	

					// create output stream
					pOut = new wxStringOutputStream(NULL);
					pGenerator->SetOutputStream( pOut );
						
					pGenerator->SetMode( udGenerator::genCOMMON_DEFINITION );
						
					// generate code
					fSuccess = pGenerator->Generate( pDiagram, sfNORECURSIVE );
					if( fSuccess )
					{
						InsertIntoCodemark( pOut->GetString(), sCommonMark, OutFile );
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
					
					//pGenerator->SetOutputStream( pOut );
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

void udPythonProjectGenerator::CleanUp()
{
	udProjectGenerator::CleanUp();
}

