#include <wx/valgen.h>

#include "gui/VariableDialog.h"

// constructor and destructor ////////////////////////////////////////////////////////////////

udVariableDialog::udVariableDialog(wxWindow *parent, udVariableItem *var, udLanguage *lang) : _VariableDialog( parent )
{
	m_pLang = lang;
	//m_fUnique = unique;
	m_pVarItem = var;
	
	m_DataType = udLanguage::DT_INT;
	m_DataModifier = udLanguage::DM_NONE;
	m_ValueType = udLanguage::VT_VALUE;
}

udVariableDialog::~udVariableDialog()
{
}

// virtual functions /////////////////////////////////////////////////////////////////////////

void udVariableDialog::OnInit(wxInitDialogEvent& event)
{
	// set validators
	m_eName->SetValidator(wxGenericValidator(&m_Name));
	m_eDescription->SetValidator(wxGenericValidator(&m_Description));
	m_eDefVal->SetValidator(wxGenericValidator(&m_DefaultValue));
	m_eTypeName->SetValidator(wxGenericValidator(&m_UserDataType));
		
	// initialize custo data type declaration place choice
	m_chDefinitionPlace->SetSelection( (int)m_UserDeclLocation );
	
	// initialize file picker
	m_fpDefinitionFile->SetPath( m_UserDeclFile );
	
	// initialize code editor
	m_sciEditor->SetText( m_UserDeclaration );
	udFRAME::InitStyledTextCtrl( m_sciEditor, m_pLang );
	
	// initialize data type combo box
	wxString sSymbol;
	size_t nIndex = 0;
	while( (sSymbol = m_pLang->GetDataTypeString( (udLanguage::DATATYPE)nIndex++ ) ) != wxEmptyString ) {
		m_chDataType->Append( sSymbol );
	}
	if( nIndex ) m_chDataType->SetSelection( (int)m_DataType );
	
	// initialize modifiers choice
	nIndex = 0;
	while( (sSymbol = m_pLang->GetModifierString( (udLanguage::DATAMODIFIER)nIndex++ ) ) != wxEmptyString ) {
		m_chModifier->Append( sSymbol );
	}
	if( nIndex ) m_chModifier->SetSelection( (int)m_DataModifier );
	
	// initialize value type choice
	nIndex = 0;
	while( (sSymbol = m_pLang->GetValueType( (udLanguage::VALUETYPE)nIndex++ ).Name() ) != wxEmptyString ) {
		m_chValueType->Append( sSymbol );
	}
	if( nIndex ) m_chValueType->SetSelection( (int)m_ValueType );
	
	// use validators to transfer a data
	TransferDataToWindow();
	m_pageAdv->TransferDataToWindow();
	m_pageUserDataType->TransferDataToWindow();
}

void udVariableDialog::OnNameChange(wxCommandEvent& event)
{
	if( ( m_Name != m_eName->GetValue() ) && m_cbMakeValid->GetValue() && m_pLang)
	{
		long nFrom, nTo;
		m_eName->GetSelection(&nFrom, &nTo);
		
//		if( m_pVarItem->MustBeUnique() )
//			m_eName->ChangeValue( m_pLang->MakeValidIdentifier( IPluginManager::Get()->GetProject()->MakeUniqueName(  m_eName->GetValue() ) ) );
//		else
		m_eName->ChangeValue( m_pLang->MakeValidIdentifier( m_eName->GetValue() ) );
			
		m_eName->SetSelection( nFrom, nTo );
	}
}

void udVariableDialog::OnMakeValid(wxCommandEvent& event)
{
	OnNameChange( event );
}

void udVariableDialog::OnOk(wxCommandEvent& event)
{
	if( m_eName->GetValue() == wxT("") )
	{
		wxMessageBox(wxT("Name cannot be empty."), wxT("CodeDesigner"), wxICON_WARNING | wxOK );
		m_eName->SetFocus();
	}
//	else if( m_pVarItem->MustBeUnique() &&
//			(m_Name != m_eName->GetValue()) &&
//			!IPluginManager::Get()->GetProject()->IsUniqueName( m_eName->GetValue() ) )
//	{
//		wxMessageBox(wxT("Name must be unique."), wxT("CodeDesigner"), wxICON_WARNING | wxOK );
//		m_eName->SetFocus();		
//	}
	else
	{
		// get data via validators...
		TransferDataFromWindow();
		m_pageAdv->TransferDataFromWindow();
		if( m_pLang->HasUserDataType() ) m_pageUserDataType->TransferDataFromWindow();
		
		// ... and via direct functions
		if( m_pLang->HasUserDataType() ) 
		{
			m_UserDeclaration = m_sciEditor->GetText();
			m_UserDeclFile = m_fpDefinitionFile->GetPath();
		}
		if( m_chDataType->GetSelection() > -1 ) m_DataType = (udLanguage::DATATYPE) m_chDataType->GetSelection();
		if( m_chModifier->GetSelection() > -1 ) m_DataModifier = (udLanguage::DATAMODIFIER) m_chModifier->GetSelection();
		if( m_chValueType->GetSelection() > -1 ) m_ValueType = (udLanguage::VALUETYPE) m_chValueType->GetSelection();
		if( m_chDefinitionPlace->GetSelection() > -1 ) m_UserDeclLocation = (udVariableItem::DECLLOCATION) m_chDefinitionPlace->GetSelection();

		EndModal( wxID_OK );
	}
}

void udVariableDialog::OnUpdateDefinitionFile(wxUpdateUIEvent& event)
{
	event.Enable( (m_chDataType->GetSelection() == (int)udLanguage::DT_USERDEFINED) && (m_chDefinitionPlace->GetSelection() == 2) );
}

void udVariableDialog::OnUpdateEditor(wxUpdateUIEvent& event)
{
	event.Enable( (m_chDataType->GetSelection() == (int)udLanguage::DT_USERDEFINED) && (m_chDefinitionPlace->GetSelection() == 1)  );
}

void udVariableDialog::OnUpdateUserDataType(wxUpdateUIEvent& event)
{
	event.Enable( (m_chDataType->GetSelection() == (int)udLanguage::DT_USERDEFINED) );
}

