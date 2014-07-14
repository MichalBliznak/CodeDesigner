#include <wx/valgen.h>
#include <wx/msgdlg.h>

#include "ClassInstanceDialog.h"

// constructor and destructor ///////////////////////////////////////////////////////

udClassInstanceDialog::udClassInstanceDialog(wxWindow *parent) : _ClassInstanceDialog( parent )
{
}

udClassInstanceDialog::~udClassInstanceDialog()
{
}

// virtual functions /////////////////////////////////////////////////////////////////////////

void udClassInstanceDialog::OnInit(wxInitDialogEvent& event)
{
	m_textInstName->SetValidator( wxGenericValidator( &m_InstanceName ) );
	m_textParameters->SetValidator( wxGenericValidator( &m_Parameters ) );
	
	event.Skip();
}

void udClassInstanceDialog::OnOk(wxCommandEvent& event)
{
	TransferDataFromWindow();
	
	if( m_InstanceName.IsEmpty() )
	{
		wxMessageBox( wxT("Instance name cannot be empty."), wxT("CodeDesigner"), wxOK | wxICON_ERROR );
		m_textInstName->SetFocus();
		return;
	}
	
	m_IsDynamic = (bool)m_choiceType->GetSelection();
	
	EndModal( wxID_OK );
}

