#include <wx/valgen.h>

#include "ConstructorDialog.h"
#include "../shapes/ClassDiagram.h"
#include "projectbase/gui/VariableDialog.h"

BEGIN_EVENT_TABLE( udConstructorDialog, _ConstructorDialog )
	EVT_PG_CHANGED( IDC_TRANSDLG_PROPGRID, udConstructorDialog::OnPropertyGridChange )
END_EVENT_TABLE();

// constructor and destructor ////////////////////////////////////////////////////////////////

udConstructorDialog::udConstructorDialog(wxWindow *parent, udConstructorFunctionItem *item, udLanguage *lang) : _ConstructorDialog( parent )
{
	wxASSERT( item );
	
	m_pLang = lang;
	m_pFcnItem = item;
	
	m_pBackUp = (udFunctionItem*) item->Clone();
	
	m_mapUsedCons = m_pFcnItem->GetUsedConstructors();
	m_mapConsParams = m_pFcnItem->GetCallParams();
}

udConstructorDialog::~udConstructorDialog()
{
	IPluginManager::Get()->EnableInternalEvents( false );
	delete m_pBackUp;
	IPluginManager::Get()->EnableInternalEvents( true );
}

// virtual functions /////////////////////////////////////////////////////////////////////////

void udConstructorDialog::OnInit(wxInitDialogEvent& event)
{
	// set validators
	m_eName->SetValidator(wxGenericValidator(&m_Name));
	m_eDescription->SetValidator(wxGenericValidator(&m_Description));
		
	// initialize code editor
	udFRAME::InitStyledTextCtrl( m_sciEditor, m_pLang );
	m_sciEditor->SetText( m_Code );
		
	// initialize function modifiers choice
	int nIndex = 0;
	wxString sSymbol;
	
	while( (sSymbol = m_pLang->GetModifierString( (udLanguage::FCNMODIFIER)nIndex++ ) ) != wxEmptyString ) {
		m_chFcnModifier->Append( sSymbol );
	}
	if( nIndex ) m_chFcnModifier->SetSelection( (int)m_FcnModifier );
	
	// initialize implementation choice (only unused diagrams can be inserted here)
	wxString sDiagName;
	
	SerializableList lstDiagrams;
	IPluginManager::Get()->GetProject()->GetDiagramsRecursively( CLASSINFO(udSStateChartDiagramItem), lstDiagrams );
	//udProject::Get()->GetDiagramsRecursively( CLASSINFO(udSubDiagramItem), lstDiagrams );
	
	for( SerializableList::iterator it = lstDiagrams.begin(); it != lstDiagrams.end(); ++it)
	{
		sDiagName = ((udProjectItem*)*it)->GetName();
		
		if( (sDiagName == m_Implementation) || !IPluginManager::Get()->GetProject()->GetFunctionImplementedBy( IPluginManager::Get()->GetProject()->GetDiagram(sDiagName) ) ) m_chImplementation->Append( sDiagName );
	}
	m_chImplementation->SetStringSelection( m_Implementation );
	
	// initialize constructor's parameters
	UpdateParameters();
	
	// initialize base classes
	IProject *pProj = IPluginManager::Get()->GetProject();
	udDiagElementItem *pParentClassElement = pProj->GetDiagramElement( m_pFcnItem->GetScope() );
	
	if( pParentClassElement )
	{
		umlClassItem *pParentClass = wxDynamicCast( pParentClassElement->GetParent(), umlClassItem );
		if( pParentClass )
		{
			int index = 0;
			udDiagElementItem *pElement;
			
			ShapeList lstBases;
			umlClassDiagram::GetBaseClasses( pParentClass, lstBases );
			
			for( ShapeList::iterator it = lstBases.begin(); it != lstBases.end(); ++it )
			{
				pElement = (udDiagElementItem*) udPROJECT::GetDiagramElement( *it );
				
				m_checkListBases->Append( pElement->GetName() );
				if( m_pFcnItem->GetUsedConstructors().find( pElement->GetName() ) != m_pFcnItem->GetUsedConstructors().end() ) m_checkListBases->Check( index );
				
				index++;
			}
		}
	}
	
	if( m_checkListBases->GetCount() > 0 )
	{
		// update constructors' choice
		UpdateConstructors( m_checkListBases->GetString(0) );
		
		// update constructor's parameters
		UpdateConsParameters( m_mapUsedCons[m_checkListBases->GetString(0)] );
	}
	
	// use validators to transfer a data
	TransferDataToWindow();
	m_pageAdv->TransferDataToWindow();
	m_pageParams->TransferDataToWindow();
	m_pageBases->TransferDataToWindow();
}

void udConstructorDialog::OnNameChange(wxCommandEvent& event)
{
	if( ( m_Name != m_eName->GetValue() ) && m_cbMakeValid->GetValue() && m_pLang)
	{
		long nFrom, nTo;
		m_eName->GetSelection(&nFrom, &nTo);
		
		m_eName->ChangeValue( m_pLang->MakeValidIdentifier( m_eName->GetValue() ) );
		
		m_eName->SetSelection( nFrom, nTo );
	}
}

void udConstructorDialog::OnMakeValid(wxCommandEvent& event)
{
	OnNameChange( event );
}

void udConstructorDialog::OnOk(wxCommandEvent& event)
{
	if( m_eName->GetValue() == wxT("") )
	{
		wxMessageBox(wxT("Name cannot be empty."), wxT("CodeDesigner"), wxICON_WARNING | wxOK );
		m_eName->SetFocus();
	}
//	else if( (m_Name != m_eName->GetValue()) && !IPluginManager::Get()->GetProject()->IsUniqueName( m_eName->GetValue() ) )
//	{
//		wxMessageBox(wxT("Name must be unique."), wxT("CodeDesigner"), wxICON_WARNING | wxOK );
//		m_eName->SetFocus();		
//	}
	else
	{
		// get data via validators...
		TransferDataFromWindow();
		m_pageAdv->TransferDataFromWindow();
		m_pageParams->TransferDataFromWindow();
		m_pageBases->TransferDataFromWindow();
		
		// ... and via direct functions
		if( m_chImplementation->GetSelection() > -1) m_Implementation = m_chImplementation->GetStringSelection();
		if( m_chFcnModifier->GetSelection() > -1 ) m_FcnModifier = (udLanguage::FCNMODIFIER) m_chFcnModifier->GetSelection();
		m_Code = m_sciEditor->GetText();

		wxString sConsName;
		m_pFcnItem->GetUsedConstructors().clear();
		m_pFcnItem->GetCallParams().clear();
		
		// store info about selected base classes and their constructors
		for( int i = 0; i < (int) m_checkListBases->GetCount(); i++ )
		{
			if( m_checkListBases->IsChecked( i ) )
			{
				sConsName = m_mapUsedCons[m_checkListBases->GetString(i)];
				
				m_pFcnItem->GetUsedConstructors()[m_checkListBases->GetString(i)] = sConsName;
				
				// store info about constructors' parameters
				for( StringMap::iterator it = m_mapConsParams.begin(); it != m_mapConsParams.end(); ++it )
				{
					if( it->first.Contains( sConsName + wxT(":") ) ) m_pFcnItem->GetCallParams()[it->first] = it->second;
				} 
			}
		}
		
		m_pFcnItem->GetCallParams() = m_mapConsParams;
		
		EndModal( wxID_OK );
	}
}

void udConstructorDialog::OnCancel(wxCommandEvent& event)
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

void udConstructorDialog::OnAddClick(wxCommandEvent& event)
{
	// create new variable
	udParamItem *pVar = new udParamItem();
	
	if( EditParameter( pVar ) ) 
	{
		m_pFcnItem->AddChild( pVar );
		UpdateParameters();
	}
	else
		delete pVar;
}

void udConstructorDialog::OnMoveDownClick(wxCommandEvent& event)
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

void udConstructorDialog::OnMoveUpClick(wxCommandEvent& event)
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

void udConstructorDialog::OnRemoveClick(wxCommandEvent& event)
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

void udConstructorDialog::OnUpdateParamButtons(wxUpdateUIEvent& event)
{
	event.Enable( m_lstParams->GetItemCount() );
}

void udConstructorDialog::UpdateParameters()
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

void udConstructorDialog::OnEditClick(wxCommandEvent& event)
{
	if( EditParameter( GetSelectedParameter() ) )
	{
		UpdateParameters();
	}
}

void udConstructorDialog::OnParamActivated(wxListEvent& event)
{
	if( EditParameter( (udVariableItem*) event.GetItem().GetData() ) )
	{
		UpdateParameters();
	}
}

bool udConstructorDialog::EditParameter(udVariableItem* param)
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


udVariableItem* udConstructorDialog::GetSelectedParameter()
{
	long nIndex = -1;

	nIndex = m_lstParams->GetNextItem( nIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
	if (nIndex != -1) 
	{
		return (udVariableItem*) m_lstParams->GetItemData( nIndex );
	}
	
	return NULL;
}

void udConstructorDialog::OnBaseConstructorChange(wxCommandEvent& event)
{
	m_mapUsedCons[m_sSelectedBaseClass] = event.GetString();
	
	UpdateConsParameters( event.GetString() );
}

void udConstructorDialog::OnBaseClassSelected(wxCommandEvent& event)
{
	m_sSelectedBaseClass = event.GetString();
	
	IProject *pProj = IPluginManager::Get()->GetProject();
	
	udDiagElementItem *pBaseClassElement = pProj->GetDiagramElement( m_sSelectedBaseClass );
	if( pBaseClassElement )
	{		
		// update constructors' choice
		UpdateConstructors( m_sSelectedBaseClass );
		
		// update constructor's parameters
		UpdateConsParameters( m_mapUsedCons[m_sSelectedBaseClass] );
	}
}

void udConstructorDialog::UpdateConstructors(const wxString& baseclass)
{
	m_chBaseConstructor->Clear();
	
	udConstructorFunctionItem *pConst;
	IProject *pProj = IPluginManager::Get()->GetProject();
	
	SerializableList lstConstructors;
	pProj->GetItems( CLASSINFO(udConstructorFunctionItem), lstConstructors );
		
	for( SerializableList::iterator it = lstConstructors.begin(); it != lstConstructors.end(); ++it )
	{
		pConst = (udConstructorFunctionItem*) *it;
		if( pConst->GetScope() == baseclass ) m_chBaseConstructor->Append( pConst->GetName() );
	}
	
	// select prefered constructor
	if( m_mapUsedCons[baseclass] != wxEmptyString )
	{
		m_chBaseConstructor->SetStringSelection( m_mapUsedCons[baseclass] );
	}
}

void udConstructorDialog::UpdateConsParameters(const wxString& cons)
{
	IProject *pProj = IPluginManager::Get()->GetProject();
	m_pgParams->Clear();
	
	// fill property grid with parameters of selected constructor
	udConstructorFunctionItem *pCons = (udConstructorFunctionItem*) pProj->GetProjectItem( CLASSINFO(udConstructorFunctionItem), cons );
	if( pCons )
	{
		udParamItem *pParam = (udParamItem*) pCons->GetFirstChild( CLASSINFO(udParamItem) );
		while( pParam )
		{
			m_pgParams->Append( new wxStringProperty( pParam->GetName(), wxPG_LABEL, m_mapConsParams[ cons + wxT(":") + pParam->GetName()] ) );
				
			pParam = (udParamItem*) pParam->GetSibbling();
		}
	}
}

void udConstructorDialog::OnPropertyGridChange(wxPropertyGridEvent& event)
{
	if( !event.GetPropertyValue().GetString().IsEmpty() )
	{
		m_mapConsParams[ m_chBaseConstructor->GetStringSelection() + wxT(":") + event.GetPropertyName() ] = event.GetPropertyValue().GetString();
	}
}
