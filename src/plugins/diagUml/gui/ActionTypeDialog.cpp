#include "wx_pch.h"

#ifdef _DEBUG_MSVC
#define new DEBUG_NEW
#endif

#include "ActionTypeDialog.h"

// constructor and destructor ///////////////////////////////////////////////////////

udActionTypeDialog::udActionTypeDialog(wxWindow *parent) : udChoiceDialog( parent )
{
	wxString choices[] = {wxT("Entry"), wxT("Exit")};
	
	SetChoices( 2, choices );
	SetTitle( wxT("State action type") );
	SetComment( wxT("Select type of assigned state action:") );
}

udActionTypeDialog::~udActionTypeDialog()
{
}
