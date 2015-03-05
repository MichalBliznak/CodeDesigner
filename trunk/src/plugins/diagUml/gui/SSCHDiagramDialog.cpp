#include "wx_pch.h"

#ifdef _DEBUG_MSVC
#define new DEBUG_NEW
#endif

#include <wx/valgen.h>

#include "SSCHDiagramDialog.h"
#include "../DiagSCH.h"

// constructor and destructor ////////////////////////////////////////////////////////////////

udSChDiagramDialog::udSChDiagramDialog( wxWindow *parent, udDiagramItem *diag, udLanguage *lang ) : udDiagramDialog( parent, diag, lang )
{
	SetTitle( wxT("State Chart diagram properties") );
	
	// create inline option
	m_cbInline = new wxCheckBox( m_pageAdv, wxID_ANY, wxT("Inline code") );
	m_pageAdv->GetSizer()->Add( m_cbInline, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	// create non-blocking option
	m_cbNonBlocking = new wxCheckBox( m_pageAdv, wxID_ANY, wxT("Non-blocking state chart") );
	m_pageAdv->GetSizer()->Add( m_cbNonBlocking, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	// create input action choice
	m_staticTextIA = new wxStaticText( m_pageAdv, wxID_ANY, wxT("Input action:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextIA->Wrap( -1 );
	m_pageAdv->GetSizer()->Add( m_staticTextIA, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxString m_chInputActionChoices[] = { wxT("<none>") };
	int m_chInputActionNChoices = sizeof( m_chInputActionChoices ) / sizeof( wxString );
	m_chInputAction = new wxChoice( m_pageAdv, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chInputActionNChoices, m_chInputActionChoices, 0 );
	m_chInputAction->SetSelection( 0 );
	m_pageAdv->GetSizer()->Add( m_chInputAction, 0, wxALL|wxEXPAND, 5 );

	m_pageAdv->Layout();
}

udSChDiagramDialog::~udSChDiagramDialog()
{
}

// virtual functions /////////////////////////////////////////////////////////////////////////

void udSChDiagramDialog::OnInit(wxInitDialogEvent& event)
{	
	// initialize controls
	bool fSubmachine = (m_pDiagram->GetSubdiagramElement() != NULL);
	
	m_cbInline->Enable( !fSubmachine ); 
	
	// fill input actions choice
	udActionItem *pAction;
	SerializableList lstActions;
	
	IPluginManager::Get()->GetProject()->GetItems( CLASSINFO(udActionItem), lstActions );
	IPluginManager::Get()->GetProject()->GetItems( CLASSINFO(udGenericFunctionItem), lstActions );
	SerializableList::compatibility_iterator node = lstActions.GetFirst();
	while( node )
	{
		pAction = (udActionItem*) node->GetData();
		m_chInputAction->Append( pAction->GetName() );
		
		node = node->GetNext();
	}
	m_chInputAction->SetStringSelection( m_InputAction );
	
	m_cbInline->SetValidator( wxGenericValidator(&m_Inline) );
	m_cbNonBlocking->SetValidator( wxGenericValidator(&m_NonBlocking) );
		
	udDiagramDialog::OnInit( event );
}

void udSChDiagramDialog::OnOk(wxCommandEvent& event)
{
	if( m_eName->GetValue() == wxT("") )
	{
		wxMessageBox(wxT("Name cannot be empty."), wxT("CodeDesigner"), wxICON_WARNING | wxOK );
		m_eName->SetFocus();
	}
//	else if( (m_Name != m_eName->GetValue()) && !IPluginManager::Get()->GetProject()->IsUniqueName( m_eName->GetValue() ) )
//	{
//		wxMessageBox(wxT("Name must be unique."), wxT("CodeDesigner"), wxICON_WARNING | wxOK );
//		m_eName->SetFocus();		
//	}
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
		m_InputAction = m_chInputAction->GetStringSelection();
		
		EndModal( wxID_OK );
	};
}

void udSChDiagramDialog::OnAlgorithmChange(wxCommandEvent& event)
{
}
