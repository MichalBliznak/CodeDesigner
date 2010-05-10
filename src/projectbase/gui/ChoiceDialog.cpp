#include "ChoiceDialog.h"

// constructor and destructor ///////////////////////////////////////////////////////

udChoiceDialog::udChoiceDialog(wxWindow *parent) : _ChoiceDialog( parent )
{
}

udChoiceDialog::~udChoiceDialog()
{
}

// public functions ////////////////////////////////////////////////////////////////

int udChoiceDialog::GetChoice()
{
	return m_chChoice->GetSelection();
}

wxString udChoiceDialog::GetChoiceString()
{
	return m_chChoice->GetStringSelection();
}

void udChoiceDialog::SetComment(const wxString& txt)
{
	m_stextComment->SetLabel( txt );
}

void udChoiceDialog::SetChoices(int n, const wxString choices [])
{
	wxASSERT( choices );
	
	// initialize choices
	for( int i = 0; i < n; i++ )
	{
		m_chChoice->Append( choices[i] );
	}
	if( n > 0 ) m_chChoice->SetSelection( 0 );
}

void udChoiceDialog::SetChoices(const wxArrayString& choices)
{
	// initialize choices
	for( size_t i = 0; i < choices.GetCount(); i++ )
	{
		m_chChoice->Append( choices[i] );
	}
	if( !choices.IsEmpty() ) m_chChoice->SetSelection( 0 );	
}
