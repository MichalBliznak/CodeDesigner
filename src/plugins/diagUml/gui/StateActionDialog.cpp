#include <wx/valgen.h>

#include "StateActionDialog.h"
#include "../DiagUml.h"

// constructor and destructor ////////////////////////////////////////////////////////////////

udStateActionDialog::udStateActionDialog(wxWindow *parent, udLanguage *lang) : _StateActionDialog( parent )
{
	m_pLang = lang;
	m_Inline = false;
	m_ActionType = 0;
}

udStateActionDialog::~udStateActionDialog()
{
}

// virtual functions /////////////////////////////////////////////////////////////////////////

void udStateActionDialog::OnInit(wxInitDialogEvent& event)
{
	// set validators
	m_eName->SetValidator(wxGenericValidator(&m_Name));
	m_eDescription->SetValidator(wxGenericValidator(&m_Description));
	m_cbInline->SetValidator(wxGenericValidator(&m_Inline));
	
	m_sciEditor->SetText( m_Code );
	m_chType->SetSelection( m_ActionType );
	
	// fill conditions choice
	/*udConditionItem *pCond;
	SerializableList lstConditions;
	udProject::Get()->GetItems( CLASSINFO(udConditionItem), lstConditions );
	
	SerializableList::compatibility_iterator node = lstConditions.GetFirst();
	while(node)
	{
		pCond = (udConditionItem*) node->GetData();
		
		m_chCondition->Append( pCond->GetName() );
		node = node->GetNext();
	}
	m_chCondition->SetStringSelection( m_Guard );*/
	
	// initialize code editor
	udFRAME::InitStyledTextCtrl( m_sciEditor, m_pLang );
	
	// use validators to transfer a data
	TransferDataToWindow();
	m_pageAdv->TransferDataToWindow();
}

void udStateActionDialog::OnNameChange(wxCommandEvent& event)
{
	if( ( m_Name != m_eName->GetValue() ) && m_cbMakeValid->GetValue() && m_pLang)
	{
		long nFrom, nTo;
		m_eName->GetSelection(&nFrom, &nTo);
		
		m_eName->ChangeValue( m_pLang->MakeValidIdentifier( m_eName->GetValue() ) );
		
		m_eName->SetSelection( nFrom, nTo );
	}
}

void udStateActionDialog::OnMakeValid(wxCommandEvent& event)
{
	OnNameChange( event );
}

void udStateActionDialog::OnOk(wxCommandEvent& event)
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
		m_Code = m_sciEditor->GetText();
		m_ActionType = m_chType->GetSelection();
		//m_Guard = m_chCondition->GetStringSelection();
		
		EndModal( wxID_OK );
	}
}
