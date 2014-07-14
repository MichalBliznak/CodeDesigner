#include <wx/valgen.h>

#include "ActionLinkDialog.h"

// constructor and destructor ////////////////////////////////////////////////////////////////

udActionLinkDialog::udActionLinkDialog(wxWindow *parent, udFunctionLinkItem *link, udLanguage *lang) : _ActionLinkDialog( parent )
{
	m_pLink = link;
	m_pLang = lang;
	
	m_pOriginal = wxDynamicCast( m_pLink->GetOriginal(), udCodeItem );
	
	m_ActionType = 0;
}

udActionLinkDialog::~udActionLinkDialog()
{
}

// virtual functions /////////////////////////////////////////////////////////////////////////

void udActionLinkDialog::OnInit(wxInitDialogEvent& event)
{
	// set validators
	m_eName->SetValidator(wxGenericValidator(&m_Name));
	
	// initialize other components
	//m_stOriginal->SetLabel( m_pOriginal->ToString( udCodeItem::cfFORMAL, m_pLang ) );
	m_chType->SetSelection( m_ActionType );
	
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
	m_pageAdv->TransferDataToWindow();
}

void udActionLinkDialog::OnEditOriginal(wxCommandEvent& event)
{
	if( m_pOriginal )
	{
		wxString sPrevOrigName = m_pOriginal->GetName();
		
		m_pOriginal->OnEditItem( this );
		
		if( sPrevOrigName == m_eName->GetValue() ) m_eName->SetValue( m_pOriginal->GetName() );
		m_stOriginal->SetLabel( m_pOriginal->ToString( udCodeItem::cfFORMAL) );
	}
}

void udActionLinkDialog::OnOk(wxCommandEvent& event)
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
		m_pageAdv->TransferDataFromWindow();
		
		// ... and via direct functions
		m_ActionType = m_chType->GetSelection();
	
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
			wxString sPropValue = m_pgParams->GetPropertyValue( pgID ).GetString();
			if( !sPropValue.IsEmpty() ) m_pLink->GetCallParams()[ m_pgParams->GetPropertyName(pgID) ] = sPropValue;
			
			pgID = m_pgParams->GetNextProperty( pgID );
		}*/
		
		EndModal( wxID_OK );
	}
}
