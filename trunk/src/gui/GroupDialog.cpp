#include "wx_pch.h"

#ifdef _DEBUG_MSVC
#define new DEBUG_NEW
#endif

#include "GroupDialog.h"

#include <wx/valgen.h>

// constructor and destructor //////////////////////////////////////////////////

udGroupDialog::udGroupDialog(wxWindow *parent) : _GroupDialog(parent)
{	
}

udGroupDialog::~udGroupDialog()
{
}

// virtual event handlers //////////////////////////////////////////////////////

void udGroupDialog::OnInitDialog(wxInitDialogEvent& event)
{
	m_eName->SetValidator( wxGenericValidator(&m_Name) );
	m_eDescription->SetValidator( wxGenericValidator(&m_Description) );
	
	m_colourPicker->SetColour( m_Colour );
	
	event.Skip();
}

void udGroupDialog::OnOk(wxCommandEvent& event)
{
	TransferDataFromWindow();
	
	m_Colour = m_colourPicker->GetColour();
	
	EndModal( wxID_OK );
}
