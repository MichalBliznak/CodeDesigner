#include <wx/valgen.h>

#include "DiagramDialog.h"
#include "codegen/Generator.h"

// constructor and destructor ////////////////////////////////////////////////////////////////

udDiagramDialog::udDiagramDialog( wxWindow *parent, udDiagramItem *diag, udLanguage *lang ) : _DiagramDialog( parent )
{
	m_pDiagram = diag;
	m_pLanguage = lang;
	m_Inline = false;
	m_GenerateCode = true;
}

udDiagramDialog::~udDiagramDialog()
{
}

// virtual functions /////////////////////////////////////////////////////////////////////////

void udDiagramDialog::OnInit(wxInitDialogEvent& event)
{
	// set validators
	m_eName->SetValidator(wxGenericValidator(&m_Name));
	m_eDescription->SetValidator(wxGenericValidator(&m_Description));
	m_cbInline->SetValidator(wxGenericValidator(&m_Inline));
	m_cbGenerate->SetValidator(wxGenericValidator(&m_GenerateCode));
	
	// initialize controls
	bool fSubmachine = (m_pDiagram->GetSubdiagramElement() != NULL);
	
	m_cbInline->Enable( !fSubmachine ); 
	m_fpOutputFile->Enable( !fSubmachine ); 
	m_chGenerator->Enable( !fSubmachine ); 
	//m_chAlgorithm->Enable( !fSubmachine );
	
	// initialize choices
	udFRAME::FillGeneratorsChoice( m_chGenerator, m_pLanguage, m_pDiagram );
	
	//udGenerator *pGen = wxGetApp().GetMainFrame()->CreateSelectedGenerator();	
	udGenerator *pGen = udPROJECT::CreateGenerator( m_chGenerator->GetStringSelection() );	
    if(pGen)
    {
		udFRAME::FillAlgorithmsChoice( m_chAlgorithm, m_pLanguage, m_pDiagram, pGen );
		delete pGen;
	}
	
	// initialize other controls
	m_fpOutputFile->SetPath( m_OutputFile );
	
	// use validators to transfer a dataOnGeneratorChange
	TransferDataToWindow();
	m_pageAdv->TransferDataToWindow();
	m_pageGen->TransferDataToWindow();
}

void udDiagramDialog::OnMakeValid(wxCommandEvent& event)
{
	OnNameChange( event );
}

void udDiagramDialog::OnNameChange(wxCommandEvent& event)
{
	udLanguage *pLang = IPluginManager::Get()->GetSelectedLanguage();
	
	if( ( m_Name != m_eName->GetValue() ) && m_cbMakeValid->GetValue() && pLang)
	{
		long nFrom, nTo;
		m_eName->GetSelection(&nFrom, &nTo);
		
		m_eName->ChangeValue( pLang->MakeValidIdentifier( IPluginManager::Get()->GetProject()->MakeUniqueName(  m_eName->GetValue() ) ) );
		
		m_eName->SetSelection( nFrom, nTo );
	}
}

void udDiagramDialog::OnOk(wxCommandEvent& event)
{
	if( m_eName->GetValue() == wxT("") )
	{
		wxMessageBox(wxT("Name cannot be empty."), wxT("CodeDesigner"), wxICON_WARNING | wxOK );
		m_eName->SetFocus();
	}
	else if( (m_Name != m_eName->GetValue()) && !IPluginManager::Get()->GetProject()->IsUniqueName( m_eName->GetValue() ) )
	{
		wxMessageBox(wxT("Name must be unique."), wxT("CodeDesigner"), wxICON_WARNING | wxOK );
		m_eName->SetFocus();		
	}
	else
	{
		// get data via validators...
		TransferDataFromWindow();
		m_pageAdv->TransferDataFromWindow();
		m_pageGen->TransferDataFromWindow();
		
		// ... and via direct functions
		m_OutputFile = m_fpOutputFile->GetPath();
		m_Generator = m_chGenerator->GetStringSelection();
		m_Algorithm = m_chAlgorithm->GetStringSelection();
		
		EndModal( wxID_OK );
	};
}

void udDiagramDialog::OnGeneratorChange(wxCommandEvent& event)
{
	m_chAlgorithm->Clear();
	
	udGenerator *pGen = udPROJECT::CreateGenerator( m_chGenerator->GetStringSelection() );
    if(pGen)
    {
		udFRAME::FillAlgorithmsChoice( m_chAlgorithm, m_pLanguage, m_pDiagram, pGen );
		delete pGen;
	}
}
