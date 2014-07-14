#include "wx_pch.h"

#ifdef _DEBUG_MSVC
#define new DEBUG_NEW
#endif

#include "ProgressDialog.h"

// constructor and destructor ////////////////////////////////////////////////////////////////

udProgressDialog::udProgressDialog(wxWindow* parent) : _ProgressDialog( parent )
{
}

udProgressDialog::~udProgressDialog()
{
}

// public functions //////////////////////////////////////////////////////////////////////////

void udProgressDialog::Clear()
{
	m_gaProgress->SetValue( 0 );
	
	Update();
	wxYield();
}

void udProgressDialog::SetLabel(const wxString& txt)
{
	m_stLabel->SetLabel( txt );
	
	Update();
	wxYield();
}

void udProgressDialog::SetStepCount(int steps)
{
	m_gaProgress->SetRange( steps );
	
	Update();
	wxYield();
}

void udProgressDialog::Step()
{
	m_gaProgress->SetValue( m_gaProgress->GetValue() + 1 );
	
	Update();
	wxYield();
}

void udProgressDialog::Pulse()
{
	m_gaProgress->Pulse();
	
	Update();
	wxYield();
}
