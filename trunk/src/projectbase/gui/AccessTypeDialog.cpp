#include "AccessTypeDialog.h"

// constructor and destructor ///////////////////////////////////////////////////////

udAccessTypeDialog::udAccessTypeDialog(wxWindow *parent) : udChoiceDialog( parent )
{
	wxString choices[] = {wxT("public"), wxT("protected"), wxT("private")};
	
	SetChoices( 3, choices );
	SetTitle( wxT("Access type") );
	SetComment( wxT("Select access type to this class member:") );
}

udAccessTypeDialog::~udAccessTypeDialog()
{
}
