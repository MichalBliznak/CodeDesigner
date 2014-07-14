#include <wx/valgen.h>

#include "FunctionLinkDialog.h"

/*BEGIN_EVENT_TABLE( udFunctionLinkDialog, _FunctionLinkDialog )
	EVT_PG_CHANGED( IDC_TRANSDLG_PROPGRID, udFunctionLinkDialog::OnPropertyGridChange )
END_EVENT_TABLE();*/

// constructor and destructor ////////////////////////////////////////////////////////////////

udFunctionLinkDialog::udFunctionLinkDialog(wxWindow *parent, udFunctionLinkItem *link, udLanguage *lang) : _FunctionLinkDialog( parent )
{
	m_pLink = link;
	m_pLang = lang;
	
	m_pOriginal = wxDynamicCast( m_pLink->GetOriginal(), udCodeItem );
}

udFunctionLinkDialog::~udFunctionLinkDialog()
{
}

// virtual functions /////////////////////////////////////////////////////////////////////////

void udFunctionLinkDialog::OnInit(wxInitDialogEvent& event)
{
	// set validators
	m_eName->SetValidator(wxGenericValidator(&m_Name));
	
	// initialize original label
	if( m_pOriginal )
	{
		m_stOriginal->SetLabel( m_pOriginal->ToString( udCodeItem::cfFORMAL, m_pLang ) );
		
		// initialize parameters map
		udParamItem *pParam = (udParamItem*) m_pOriginal->GetFirstChild( CLASSINFO(udParamItem) );
		while( pParam )
		{
			m_pgParams->Append( new wxStringProperty( pParam->GetName(), wxPG_LABEL, m_pLink->GetCallParams()[ pParam->GetName()] ) );
			
			pParam = (udParamItem*) pParam->GetSibbling();
		}
	}
	
	// use validators to transfer a data
	TransferDataToWindow();
}

void udFunctionLinkDialog::OnEditOriginal(wxCommandEvent& event)
{
	if( m_pOriginal )
	{
		wxString sPrevOrigName = m_pOriginal->GetName();
		
		m_pOriginal->OnEditItem( this );
		
		if( sPrevOrigName == m_eName->GetValue() ) m_eName->SetValue( m_pOriginal->GetName() );
		m_stOriginal->SetLabel( m_pOriginal->ToString( udCodeItem::cfFORMAL, m_pLang) );
	}
}

void udFunctionLinkDialog::OnOk(wxCommandEvent& event)
{
	if( m_eName->GetValue() == wxT("") )
	{
		wxMessageBox(wxT("Name cannot be empty."), wxT("CodeDesigner"), wxICON_WARNING | wxOK );
		m_eName->SetFocus();
	}
	else
	{
		// get data via validators...
		TransferDataFromWindow();
		
		// ... and via member functions
		wxString sPropValue;
		m_pLink->GetCallParams().clear();
		
		wxPropertyGridIterator it = m_pgParams->GetIterator( wxPG_ITERATE_PROPERTIES );
		for( ; !it.AtEnd(); ++it )
		{
			wxString sPropValue = (*it)->GetValueAsString();
			if( !sPropValue.IsEmpty() ) m_pLink->GetCallParams()[ (*it)->GetName() ] = sPropValue;
		}
		
		/*wxPGId pgID = m_pgParams->GetFirstProperty();
		while( pgID.IsOk() )
		{
			sPropValue = m_pgParams->GetPropertyValue( pgID ).GetString();
			if( !sPropValue.IsEmpty() ) m_pLink->GetCallParams()[ m_pgParams->GetPropertyName(pgID) ] = sPropValue;
			
			pgID = m_pgParams->GetNextProperty( pgID );
		}*/
		
		EndModal( wxID_OK );
	}
}

