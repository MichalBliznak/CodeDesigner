#include <wx/valgen.h>

#include "FunctionDialog.h"
#include "gui/VariableDialog.h"

// constructor and destructor ////////////////////////////////////////////////////////////////

udFunctionDialog::udFunctionDialog(wxWindow *parent, udFunctionItem *item, udLanguage *lang) : _FunctionDialog( parent )
{
	wxASSERT( item );
	
	m_pLang = lang;
	m_pFcnItem = item;
	m_Inline = false;
	
	m_pBackUp = (udFunctionItem*) item->Clone();
}

udFunctionDialog::~udFunctionDialog()
{
	IPluginManager::Get()->EnableInternalEvents( false );
	delete m_pBackUp;
	IPluginManager::Get()->EnableInternalEvents( true );
}

// virtual functions /////////////////////////////////////////////////////////////////////////

void udFunctionDialog::OnInit(wxInitDialogEvent& event)
{
	// set validators
	m_eName->SetValidator(wxGenericValidator(&m_Name));
	m_eDescription->SetValidator(wxGenericValidator(&m_Description));
	m_eTypeName->SetValidator(wxGenericValidator(&m_UserDataType));
	m_chbInline->SetValidator(wxGenericValidator(&m_Inline));
	
	// initialize custo data type declaration place choice
	m_chDefinitionPlace->SetSelection( (int)m_UserDeclLocation );
	
	// initialize file picker
	m_fpDefinitionFile->SetPath( m_UserDeclFile );
	
	// initialize code editor
	udFRAME::InitStyledTextCtrl( m_sciEditor, m_pLang );
	m_chEditedField->SetSelection( 0 );
	m_sciEditor->SetText( m_Code );
	
	// initialize data type choice
	wxString sSymbol;
	size_t nIndex = 0;
	while( (sSymbol = m_pLang->GetDataTypeString( (udLanguage::DATATYPE)nIndex++ ) ) != wxEmptyString ) {
		m_chDataType->Append( sSymbol );
	}
	if( nIndex ) m_chDataType->SetSelection( (int)m_DataType );
	
	// initialize function modifiers choice
	nIndex = 0;
	while( (sSymbol = m_pLang->GetModifierString( (udLanguage::FCNMODIFIER)nIndex++ ) ) != wxEmptyString ) {
		m_chFcnModifier->Append( sSymbol );
	}
	if( nIndex ) m_chFcnModifier->SetSelection( (int)m_FcnModifier );
	
	// initialize data modifiers choice
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
	
	// initialize implementation choice (only unused diagrams can be inserted here)
	wxString sDiagName;
	
	SerializableList lstDiagrams;
	IPluginManager::Get()->GetProject()->GetDiagramsRecursively( CLASSINFO(udDiagramItem), lstDiagrams );
	//udProject::Get()->GetDiagramsRecursively( CLASSINFO(udSubDiagramItem), lstDiagrams );
	
	for( SerializableList::iterator it = lstDiagrams.begin(); it != lstDiagrams.end(); ++it)
	{
		sDiagName = ((udProjectItem*)*it)->GetName();
		
		if( (sDiagName == m_Implementation) || !IPluginManager::Get()->GetProject()->GetFunctionImplementedBy( IPluginManager::Get()->GetProject()->GetDiagram(sDiagName) ) ) m_chImplementation->Append( sDiagName );
	}
	m_chImplementation->SetStringSelection( m_Implementation );
	
	UpdateParameters();
	
	// m_chbInline->Enable( m_pFcnItem->IsKindOf(CLASSINFO(udActionItem)) || m_pFcnItem->IsKindOf(CLASSINFO(udConditionItem)) );
	
	// use validators to transfer a data
	TransferDataToWindow();
	m_pageAdv->TransferDataToWindow();
	m_pageRetVal->TransferDataToWindow();
	m_pageUserDataType->TransferDataToWindow();
	m_pageParams->TransferDataToWindow();
}

void udFunctionDialog::OnNameChange(wxCommandEvent& event)
{
	if( ( m_Name != m_eName->GetValue() ) && m_cbMakeValid->GetValue() && m_pLang)
	{
		long nFrom, nTo;
		m_eName->GetSelection(&nFrom, &nTo);
		
		m_eName->ChangeValue( m_pLang->MakeValidIdentifier( m_eName->GetValue() ) );
		
		m_eName->SetSelection( nFrom, nTo );
	}
}

void udFunctionDialog::OnMakeValid(wxCommandEvent& event)
{
	OnNameChange( event );
}

void udFunctionDialog::OnOk(wxCommandEvent& event)
{
	if( m_eName->GetValue() == wxT("") )
	{
		wxMessageBox(wxT("Name cannot be empty."), wxT("CodeDesigner"), wxICON_WARNING | wxOK );
		m_eName->SetFocus();
	}
//	else if( m_pFcnItem->MustBeUnique() &&
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
		m_pageRetVal->TransferDataFromWindow();
		if( m_pLang->HasUserDataType() ) m_pageUserDataType->TransferDataFromWindow();
		m_pageParams->TransferDataFromWindow();
		
		// ... and via direct functions
		if( m_chDataType->GetSelection() > -1 ) m_DataType = (udLanguage::DATATYPE) m_chDataType->GetSelection();
		if( m_chModifier->GetSelection() > -1 ) m_DataModifier = (udLanguage::DATAMODIFIER) m_chModifier->GetSelection();
		if( m_chFcnModifier->GetSelection() > -1 ) m_FcnModifier = (udLanguage::FCNMODIFIER) m_chFcnModifier->GetSelection();
		if( m_chValueType->GetSelection() > -1 ) m_ValueType = (udLanguage::VALUETYPE) m_chValueType->GetSelection();
		if( m_chImplementation->GetSelection() > -1) m_Implementation = m_chImplementation->GetStringSelection();
		if( m_pLang->HasUserDataType() )
		{
			m_UserDeclLocation = (udVariableItem::DECLLOCATION) m_chDefinitionPlace->GetSelection();
			m_UserDeclFile = m_fpDefinitionFile->GetPath();
		}
		
		EndModal( wxID_OK );
	}
}

void udFunctionDialog::OnCancel(wxCommandEvent& event)
{
	IPluginManager::Get()->EnableInternalEvents( false );
	
	// remove current (possibly modified) parameters
	SerializableList::compatibility_iterator node = m_pFcnItem->GetFirstChildNode();
	while( node )
	{
		IPluginManager::Get()->GetProject()->RemoveItem( (xsSerializable*)node->GetData() );
		node = m_pFcnItem->GetFirstChildNode();
	}
	// restore previous parameters
	node = m_pBackUp->GetFirstChildNode();
	while( node )
	{
		m_pFcnItem->AddChild( (xsSerializable*)node->GetData()->Clone() );
		node = node->GetNext();
	}
	
	IPluginManager::Get()->EnableInternalEvents( true );
	
	EndModal( wxID_CANCEL );
}

void udFunctionDialog::OnAddClick(wxCommandEvent& event)
{
	// create new variable
	//udVariableItem *pVar = new udVariableItem();
	udParamItem *pVar = new udParamItem();
	
	if( EditParameter( pVar ) ) 
	{
		m_pFcnItem->AddChild( pVar );
		UpdateParameters();
	}
	else
		delete pVar;
}

void udFunctionDialog::OnMoveDownClick(wxCommandEvent& event)
{
	udVariableItem *pVar = GetSelectedParameter();
	if( pVar )
	{
		int nIndex = m_pFcnItem->GetChildrenList().IndexOf( pVar );
		if( nIndex < (int)(m_pFcnItem->GetChildrenList().GetCount() - 1) )
		{
			m_pFcnItem->GetChildrenList().DeleteObject( pVar );
			m_pFcnItem->GetChildrenList().Insert( (size_t)nIndex+1, pVar );
			
			UpdateParameters();
		}
	}
}

void udFunctionDialog::OnMoveUpClick(wxCommandEvent& event)
{
	udVariableItem *pVar = GetSelectedParameter();
	if( pVar )
	{
		int nIndex = m_pFcnItem->GetChildrenList().IndexOf( pVar );
		if( nIndex > 0 )
		{
			m_pFcnItem->GetChildrenList().DeleteObject( pVar );
			m_pFcnItem->GetChildrenList().Insert( (size_t)nIndex-1, pVar );
			
			UpdateParameters();
		}
	}
}

void udFunctionDialog::OnRemoveClick(wxCommandEvent& event)
{
	udVariableItem *pVar = GetSelectedParameter();
	if( pVar )
	{
		IPluginManager::Get()->EnableInternalEvents(false);
		
		m_pFcnItem->GetChildrenList().DeleteObject( pVar );
		delete pVar;
			
		IPluginManager::Get()->EnableInternalEvents(true);
		UpdateParameters();
	}
}

void udFunctionDialog::OnUpdateParamButtons(wxUpdateUIEvent& event)
{
	event.Enable( m_lstParams->GetItemCount() );
}

void udFunctionDialog::OnUpdateDefinitionFile(wxUpdateUIEvent& event)
{
	event.Enable( ((m_chDataType->GetSelection() == (int) udLanguage::DT_USERDEFINED)) && (m_chDefinitionPlace->GetSelection() == 2) );
}

void udFunctionDialog::OnUpdateEditor(wxUpdateUIEvent& event)
{
	event.Enable( ( (m_chEditedField->GetSelection() == 0) && (m_chImplementation->GetStringSelection() == wxT("<user-defined-code>")) ) ||
				  ( (m_chDataType->GetSelection() == (int) udLanguage::DT_USERDEFINED) && (m_chDefinitionPlace->GetSelection() == 1) ) );
}

void udFunctionDialog::OnUpdateUserDataType(wxUpdateUIEvent& event)
{
	event.Enable( (m_chDataType->GetSelection() == (int) udLanguage::DT_USERDEFINED) );
}

void udFunctionDialog::OnEditorChoice(wxCommandEvent& event)
{
	if( m_chEditedField->GetSelection() == 1 )
	{
		m_sciEditor->SetText( m_UserDeclaration );
	}
	else
		m_sciEditor->SetText( m_Code );
}

void udFunctionDialog::UpdateParameters()
{
	long nIndex = 0;
	udVariableItem *pVar;
	
	m_lstParams->ClearAll();
	m_lstParams->InsertColumn(0, wxT("Type"));
	m_lstParams->InsertColumn(1, wxT("Name"));
	
	SerializableList::compatibility_iterator node = m_pFcnItem->GetFirstChildNode();
	while( node )
	{
		pVar = wxDynamicCast( node->GetData(), udVariableItem );
		if( pVar )
		{
			if( pVar->GetDataType() == udLanguage::DT_USERDEFINED )
			{
				m_lstParams->InsertItem( nIndex, pVar->GetUserDataType() + m_pLang->GetValueType(  pVar->GetValueType() ).Sign() );
			}
			else
				m_lstParams->InsertItem( nIndex, m_pLang->GetDataTypeString( pVar->GetDataType() ) + m_pLang->GetValueType(  pVar->GetValueType() ).Sign() );
				
			m_lstParams->SetItemPtrData( nIndex, (wxUIntPtr)pVar );
			m_lstParams->SetItem( nIndex++, 1, pVar->GetName() );
		}
		node = node->GetNext();
	}
	
	if( nIndex )
	{
		m_lstParams->SetColumnWidth( 0, wxLIST_AUTOSIZE );
		m_lstParams->SetColumnWidth( 1, wxLIST_AUTOSIZE );
	}
}

void udFunctionDialog::OnEditClick(wxCommandEvent& event)
{
	if( EditParameter( GetSelectedParameter() ) )
	{
		UpdateParameters();
	}
}

void udFunctionDialog::OnParamActivated(wxListEvent& event)
{
	if( EditParameter( (udVariableItem*) event.GetItem().GetData() ) )
	{
		UpdateParameters();
	}
}

bool udFunctionDialog::EditParameter(udVariableItem* param)
{
	if( param )
	{
		// parameter name don't have to be unique
		udVariableDialog dlg( this, param, m_pLang );
		dlg.SetTitle( wxT("Parameter properties") );
		
		dlg.SetCodeName( param->GetName() );
		dlg.SetDescription( param->GetDescription() );
		dlg.SetDataType( param->GetDataType() );
		dlg.SetDataModifier( param->GetDataModifer() );
		dlg.SetValueType( param->GetValueType() );
		dlg.SetUserDataType( param->GetUserDataType() );
		dlg.SetUserDeclPlace( param->GetUserDeclPlace() );
		dlg.SetUserDeclFile( param->GetUserDeclFile() );
		dlg.SetUserDeclaration( param->GetUserDeclaration() );
		dlg.SetDefaultValue( param->GetValue() );
		
		if( dlg.ShowModal() == wxID_OK )
		{
			param->SetName( dlg.GetCodeName() );
			param->SetDescription( dlg.GetDescription() );
			param->SetDataType( dlg.GetDataType() );
			param->SetDataModifier( dlg.GetDataModifier() );
			param->SetValueType( dlg.GetValueType() );
			param->SetUserDataType( dlg.GetUserDataType() );
			param->SetUserDeclPlace( dlg.GetUserDeclPlace() );
			param->SetUserDeclFile( dlg.GetUserDeclFile() );
			param->SetUserDeclaration( dlg.GetUserDeclaration() );
			param->SetValue( dlg.GetDefaultValue() );
			
			return true;
		}
	}
	
	return false;
}


udVariableItem* udFunctionDialog::GetSelectedParameter()
{
	long nIndex = -1;

	nIndex = m_lstParams->GetNextItem( nIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
	if (nIndex != -1) 
	{
		return (udVariableItem*) m_lstParams->GetItemData( nIndex );
	}
	
	return NULL;
}

void udFunctionDialog::OnEditorKillFocus(wxFocusEvent& event)
{
	event.Skip();
	
	if( m_chEditedField->GetSelection() == 1 ) m_UserDeclaration = m_sciEditor->GetText();
	else
		m_Code = m_sciEditor->GetText();
}

