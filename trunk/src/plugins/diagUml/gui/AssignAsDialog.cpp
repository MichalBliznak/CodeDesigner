#include "AssignAsDialog.h"

// constructor and destructor ///////////////////////////////////////////////////////

udAssignAsDialog::udAssignAsDialog(wxWindow *parent) : udChoiceDialog( parent )
{
	wxString choices[] = {wxT("Condition function"), wxT("Action function")};
	
	SetChoices( 2, choices );
	SetTitle( wxT("Function type") );
	SetComment( wxT("Assign dropped item as:") );
}

udAssignAsDialog::~udAssignAsDialog()
{
}
