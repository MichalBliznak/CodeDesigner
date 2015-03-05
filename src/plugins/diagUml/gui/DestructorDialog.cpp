#include <wx/valgen.h>

#include "DestructorDialog.h"
#include "projectbase/gui/VariableDialog.h"

// constructor and destructor ////////////////////////////////////////////////////////////////

udDestructorDialog::udDestructorDialog(wxWindow *parent, udLanguage *lang) : _DestructorDialog( parent )
{
	m_pLang = lang;
}

udDestructorDialog::~udDestructorDialog()
{
}

// virtual functions /////////////////////////////////////////////////////////////////////////

void udDestructorDialog::OnInit(wxInitDialogEvent& event)
{
	// set validators
	m_eName->SetValidator(wxGenericValidator(&m_Name));
	m_eDescription->SetValidator(wxGenericValidator(&m_Description));
		
	// initialize code editor
	udFRAME::InitStyledTextCtrl( m_sciEditor, m_pLang );
	m_sciEditor->SetText( m_Code );
		
	// initialize function modifiers choice
	int nIndex = 0;
	wxString sSymbol;
	
	while( (sSymbol = m_pLang->GetModifierString( (udLanguage::FCNMODIFIER)nIndex++ ) ) != wxEmptyString ) {
		m_chFcnModifier->Append( sSymbol );
	}
	if( nIndex ) m_chFcnModifier->SetSelection( (int)m_FcnModifier );
	
	// initialize implementation choice (only unused diagrams can be inserted here)
	wxString sDiagName;
	
	SerializableList lstDiagrams;
	IPluginManager::Get()->GetProject()->GetDiagramsRecursively( CLASSINFO(udSStateChartDiagramItem), lstDiagrams );
	//udProject::Get()->GetDiagramsRecursively( CLASSINFO(udSubDiagramItem), lstDiagrams );
	
	for( SerializableList::iterator it = lstDiagrams.begin(); it != lstDiagrams.end(); ++it)
	{
		sDiagName = ((udProjectItem*)*it)->GetName();
		
		if( (sDiagName == m_Implementation) || !IPluginManager::Get()->GetProject()->GetFunctionImplementedBy( IPluginManager::Get()->GetProject()->GetDiagram(sDiagName) ) ) m_chImplementation->Append( sDiagName );
	}
	m_chImplementation->SetStringSelection( m_Implementation );
		
	// use validators to transfer a data
	TransferDataToWindow();
	m_pageAdv->TransferDataToWindow();
}

void udDestructorDialog::OnNameChange(wxCommandEvent& event)
{
	if( ( m_Name != m_eName->GetValue() ) && m_cbMakeValid->GetValue() && m_pLang)
	{
		long nFrom, nTo;
		m_eName->GetSelection(&nFrom, &nTo);
		
		m_eName->ChangeValue( m_pLang->MakeValidIdentifier( m_eName->GetValue() ) );
		
		m_eName->SetSelection( nFrom, nTo );
	}
}

void udDestructorDialog::OnMakeValid(wxCommandEvent& event)
{
	OnNameChange( event );
}

void udDestructorDialog::OnOk(wxCommandEvent& event)
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
		
		// ... and via direct functions
		if( m_chImplementation->GetSelection() > -1) m_Implementation = m_chImplementation->GetStringSelection();
		if( m_chFcnModifier->GetSelection() > -1 ) m_FcnModifier = (udLanguage::FCNMODIFIER) m_chFcnModifier->GetSelection();
		
		EndModal( wxID_OK );
	}
}

void udDestructorDialog::OnCancel(wxCommandEvent& event)
{	
	EndModal( wxID_CANCEL );
}
