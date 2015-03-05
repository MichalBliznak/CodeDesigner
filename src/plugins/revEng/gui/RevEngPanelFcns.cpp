#include "RevEngPanel.h"

#include <wx/regex.h>


void udRevEngPanel::ForceName(udProjectItem* item, const wxString& name)
{
	bool unique = item->MustBeUnique();
	item->SetMustBeUnique( false );
	
	item->SetName( name );
	
	item->SetMustBeUnique( unique );
}

umlClassItem* udRevEngPanel::CreateClassElement(wxTreeItemId classId)
{
	ctagClass *ctag = (ctagClass*) m_treeSymbols->GetItemData( classId );
	
	if( ctag->m_Type == udCTAGS::ttCLASS )
	{
		umlClassItem *classItem = new umlClassItem();
		udClassElementItem *classElement = new udClassElementItem();
		
		classItem->SetUserData( classElement );
		
		udLABEL::SetContent(ctag->m_Name, classItem, udLABEL::ltTITLE);
		ForceName(classElement, ctag->m_Name);
		
		if( ctag->m_Namespace.IsEmpty() ) m_mapProjectItems[ ctag->m_Name ] = classElement;
		m_mapProjectItems[ ctag->m_Namespace + wxT("::") + ctag->m_Name ] = classElement;
		
		if( m_checkBoxMembers->IsChecked() )
		{
			CreateDataMembers( classElement, classId );
			CreateFunctionMembers( classElement, classId );
		}
		
		classElement->OnCreate();
		classElement->UpdateInnerContent();
		
		return classItem;
	}
	else
		return NULL;
}

void udRevEngPanel::CreateClassAssociations(udDiagramItem* diagram, wxTreeItemId classId)
{
	ctagClass *ctag = (ctagClass*) m_treeSymbols->GetItemData( classId );
	
	//udProjectItem *newClass = udPROJECT::GetDiagramElement( diagram, ctag->m_Name );
	udProjectItem *newClass = m_mapProjectItems[ ctag->m_Namespace + wxT("::") + ctag->m_Name ];
	if( newClass )
	{
		// inheritance 
		wxStringTokenizer tokenz( ctag->m_Inherits, wxT(","), wxTOKEN_STRTOK);
		while( tokenz.HasMoreTokens() )
		{
			udProjectItem *baseClass = udPROJECT::GetDiagramElement( diagram, tokenz.GetNextToken() );
			if( baseClass )
			{
				umlInheritanceItem *connection = new umlInheritanceItem();
				udInherElementItem *connElement = new udInherElementItem();
				
				connection->SetUserData( connElement );
				
				ForceName( connElement, wxT("Inheritance element") );
				
				connection->SetSrcShapeId( ((wxSFShapeBase*)newClass->GetParent())->GetId() );
				connection->SetTrgShapeId( ((wxSFShapeBase*)baseClass->GetParent())->GetId() );
				
				diagram->GetDiagramManager().AddShape( connection, NULL, wxDefaultPosition, sfINITIALIZE, sfDONT_SAVE_STATE );	
			}
		}
		
		// include associations
		//udProjectItem *outerClass = udPROJECT::GetDiagramElement( diagram, ctag->m_Namespace.AfterLast( wxT(':') ) );
		udProjectItem *outerClass = m_mapProjectItems[ ctag->m_Namespace ];
		if( outerClass )
		{
			umlIncludeAssocItem *connection = new umlIncludeAssocItem();
			udIncludeAssocElementItem *connElement = new udIncludeAssocElementItem();
			
			connection->SetUserData( connElement );
			
			ForceName( connElement, wxT("Include association element") );
			connElement->SetAccessType( GetAccessType( ctag->m_Access ) );
			
			connection->SetTrgShapeId( ((wxSFShapeBase*)newClass->GetParent())->GetId() );
			connection->SetSrcShapeId( ((wxSFShapeBase*)outerClass->GetParent())->GetId() );
			
			diagram->GetDiagramManager().AddShape( connection, NULL, wxDefaultPosition, sfINITIALIZE, sfDONT_SAVE_STATE );	
		}
	}
}

void udRevEngPanel::CreateMemberAssociations(udDiagramItem* diagram, wxTreeItemId classId)
{
	wxArrayTreeItemIds arrMembers;
	GetMemberIds( udCTAGS::ttCLASS_MEMBER, classId, arrMembers );
	
	wxArrayTreeItemIds arrClasses;
	GetSelectedTreeIds( udCTAGS::ttCLASS, arrClasses );
	
	ctagClass *ctag = (ctagClass*) m_treeSymbols->GetItemData( classId );
	//udProjectItem *srcClass = udPROJECT::GetDiagramElement( diagram, ctag->m_Name );
	udProjectItem *srcClass = m_mapProjectItems[ ctag->m_Namespace + wxT("::") + ctag->m_Name ];
	
	for( size_t i = 0; i < arrMembers.GetCount(); i++ )
	{
		udCTAGS* mctag = (udCTAGS*) m_treeSymbols->GetItemData( arrMembers[i] );
		
		wxString memberName = mctag->m_Name;
		
		// parse referenced class name
		wxString targetName = wxT(" ") + GetDataType( mctag, udfWITHOUT_DECORATION ) + wxT(" ");
		
		for( size_t j = 0; j < arrClasses.GetCount(); j++ )
		{
			ctagClass *cctag = (ctagClass*) m_treeSymbols->GetItemData( arrClasses[j] );
			
			// IPluginManager::Get()->Log( wxT("DEBUG: ") + targetName + wxT(" ?= ") + cctag->m_Name );
			
			if( targetName.Contains( wxT(" ") + cctag->m_Name + wxT(" ") ) )
			{
				//udProjectItem *trgClass = udPROJECT::GetDiagramElement( diagram, cctag->m_Name );
				udProjectItem *trgClass = m_mapProjectItems[ cctag->m_Namespace + wxT("::") + cctag->m_Name ];
				
				if( srcClass && trgClass )
				{
					umlUniDirectAssocItem *connection = new umlUniDirectAssocItem();
					udUniAssocElementItem *connElement = new udUniAssocElementItem();
					
					connection->SetUserData( connElement );
					
					ForceName( connElement, wxT("Association element") );
					udLABEL::SetContent( memberName, connection, udLABEL::ltASSOC_ROLE1 );
					
					if( mctag->m_Pattern.Contains( wxT("*") ) ) udLABEL::SetContent( wxT("0..1"), connection, udLABEL::ltASSOC_MULT1 );
					else
						udLABEL::SetContent( wxT("1"), connection, udLABEL::ltASSOC_MULT1 );
					
					connection->SetSrcShapeId( ((wxSFShapeBase*)srcClass->GetParent())->GetId() );
					connection->SetTrgShapeId( ((wxSFShapeBase*)trgClass->GetParent())->GetId() );
					
					diagram->GetDiagramManager().AddShape( connection, NULL, wxDefaultPosition, sfINITIALIZE, sfDONT_SAVE_STATE );
				}
			}
		}
	}
}

void udRevEngPanel::CreateDataMembers(udClassElementItem *classItem, wxTreeItemId classId)
{
	wxArrayTreeItemIds arrMembers;
	GetMemberIds( udCTAGS::ttCLASS_MEMBER, classId, arrMembers );
	
	IProject *proj = IPluginManager::Get()->GetProject();
	
	int parentId = proj->GetRootItem()->GetId();
	
	// create code package for new members if doesn't exists
	if( IPluginManager::Get()->IsProjManOrganised() )
	{
		wxString pkgName = IPluginManager::Get()->GetCodePackage( wxT("udMemberDataItem") );
		udProjectItem *package = proj->GetProjectItem( wxClassInfo::FindClass( wxT("udCodePackageItem") ), pkgName );
		if( !package )
		{
			package = proj->CreateProjectItem( wxT("udCodePackageItem"), proj->GetRootItem()->GetId() );
			ForceName( package, pkgName );
		}
		
		parentId = package->GetId();
	}
	
	for(size_t i = 0; i < arrMembers.GetCount(); i++)
	{
		ctagClassMember *ctag = (ctagClassMember*) m_treeSymbols->GetItemData( arrMembers[i] );
		
		// create code item
		udMemberDataItem *data = (udMemberDataItem*) proj->CreateProjectItem( wxT("udMemberDataItem"), parentId );
		ForceName( data, ctag->m_Name );
		data->SetDescription( wxT("Original class member: \"") + ctag->m_Pattern + wxT("\"") );
		data->SetScope( classItem->GetName() );
		
		data->SetDataType( udLanguage::DT_USERDEFINED );
		data->SetUserDataType( GetDataType( ctag, udfWITHOUT_DECORATION ) );
		data->SetUserDeclPlace( udVariableItem::dlBUILTIN );
		data->SetValue( GetDataValue( ctag ) );
		
		data->UpdateSignature();
		
		// assign link to the class
		classItem->AssignCodeItem( new udMemberDataLinkItem( data, GetAccessType( ctag->m_Access ) ) );
	}
}

void udRevEngPanel::CreateFunctionMembers(udClassElementItem *classItem, wxTreeItemId classId)
{
	wxArrayTreeItemIds arrMembers;
	GetMemberIds( udCTAGS::ttCLASS_FUNCTION, classId, arrMembers );
	
	IProject *proj = IPluginManager::Get()->GetProject();
	
	for(size_t i = 0; i < arrMembers.GetCount(); i++)
	{
		ctagClassFunction *ctag = (ctagClassFunction*) m_treeSymbols->GetItemData( arrMembers[i] );
		
		//IPluginManager::Get()->Log( wxT("DEBUG: Member's pattern:") + ctag->m_Pattern + wxT(", signature: ") + ctag->m_Signature );
		
		// create code item
		udMemberFunctionItem *data = NULL;

		if( ctag->m_Name == ctag->m_ParentClass )
		{
			data = (udMemberFunctionItem*) proj->CreateProjectItem( wxT("udConstructorFunctionItem"), proj->GetRootItem()->GetId() );
			ForceName( data, wxT("Constructor ") + ctag->m_Name );
		}
		else if( ctag->m_Name == wxT("~") + ctag->m_ParentClass )
		{
			data = (udMemberFunctionItem*) proj->CreateProjectItem( wxT("udDestructorFunctionItem"), proj->GetRootItem()->GetId() );
			wxString name = ctag->m_Name;
			name.Replace( wxT("~"), wxT("") );
			ForceName( data, wxT("Destructor ") + name );
		}
		else
		{
			data = (udMemberFunctionItem*) proj->CreateProjectItem( wxT("udMemberFunctionItem"), proj->GetRootItem()->GetId() );
			ForceName( data, ctag->m_Name );
		}
		
		// create code package for new members if doesn't exists
		if( IPluginManager::Get()->IsProjManOrganised() )
		{
			wxString pkgName = IPluginManager::Get()->GetCodePackage( data->GetClassInfo()->GetClassName() );
			udProjectItem *package = proj->GetProjectItem( wxClassInfo::FindClass( wxT("udCodePackageItem") ), pkgName );
			if( !package )
			{
				package = proj->CreateProjectItem( wxT("udCodePackageItem"), proj->GetRootItem()->GetId() );
				ForceName( package, pkgName );
			}
			
			data->Reparent( package );
		}
			
		data->SetDescription( wxT("Original class member: \"") + ctag->m_Pattern + wxT("\"") );
		data->SetScope( classItem->GetName() );
		if( m_checkBoxBodies->IsChecked() ) data->SetCode( ctag->m_Content );
		
		data->SetRetValDataType( udLanguage::DT_USERDEFINED );
		data->SetUserRetValDataType( GetDataType( ctag, udfWITHOUT_DECORATION ) );
		data->SetUserRetValDeclPlace( udVariableItem::dlBUILTIN );
		
		// create function arguments
		wxArrayString arrArgs;
		GetFunctionArguments( ctag, arrArgs );
		
		for( size_t j = 0; j < arrArgs.GetCount(); j++ )
		{
			wxString arg = arrArgs[j];
			
			udParamItem *var = new udParamItem();
			
			ForceName( var, arg.AfterLast(' ') );
			var->SetDescription( wxT("Original parameter: \"") + arg + wxT("\"") );
			
			var->SetDataType( udLanguage::DT_USERDEFINED );
			var->SetUserDataType( arg.BeforeLast(' ') );
			var->SetUserDeclPlace( udVariableItem::dlBUILTIN );
			
			data->AddChild( var );
		}
		
		data->UpdateSignature();
		
		// assign link to the class
		classItem->AssignCodeItem( new udMemberFunctionLinkItem( data, GetAccessType( ctag->m_Access ) ) );
	}
}

void udRevEngPanel::CreateFunctions(wxTreeItemId fcnId)
{
	IProject *proj = IPluginManager::Get()->GetProject();
	
	int parentId = proj->GetRootItem()->GetId();
	
	ctagFunction *ctag = (ctagFunction*) m_treeSymbols->GetItemData( fcnId );
		
	// create code package for new members if doesn't exists
	if( IPluginManager::Get()->IsProjManOrganised() )
	{
		wxString pkgName = IPluginManager::Get()->GetCodePackage( wxT("udGenericFunctionItem") );
		udProjectItem *package = proj->GetProjectItem( wxClassInfo::FindClass( wxT("udCodePackageItem") ), pkgName );
		if( !package )
		{
			package = proj->CreateProjectItem( wxT("udCodePackageItem"), parentId );
			ForceName( package, pkgName );
		}
		
		parentId = package->GetId();
	}
	
	// create code item
	udGenericFunctionItem *data = (udGenericFunctionItem*) proj->CreateProjectItem( wxT("udGenericFunctionItem"), parentId );
	ForceName( data, ctag->m_Name );

	data->SetDescription( wxT("Original function: \"") + ctag->m_Pattern + wxT("\"") );
	if( m_checkBoxBodies->IsChecked() ) data->SetCode( ctag->m_Content );
	
	data->SetRetValDataType( udLanguage::DT_USERDEFINED );
	data->SetUserRetValDataType( GetDataType( ctag, udfWITHOUT_DECORATION ) );
	data->SetUserRetValDeclPlace( udVariableItem::dlBUILTIN );
	
	// create function arguments
	wxArrayString arrArgs;
	GetFunctionArguments( ctag, arrArgs );
	
	for( size_t j = 0; j < arrArgs.GetCount(); j++ )
	{
		wxString arg = arrArgs[j];
		
		udParamItem *var = new udParamItem();
		
		ForceName( var, arg.AfterLast(' ') );
		var->SetDescription( wxT("Original parameter: \"") + arg + wxT("\"") );
		
		var->SetDataType( udLanguage::DT_USERDEFINED );
		var->SetUserDataType( arg.BeforeLast(' ') );
		var->SetUserDeclPlace( udVariableItem::dlBUILTIN );
		
		data->AddChild( var );
	}
	
	data->UpdateSignature();
}

void udRevEngPanel::CreateVariables(wxTreeItemId varId)
{
	IProject *proj = IPluginManager::Get()->GetProject();
	
	int parentId = proj->GetRootItem()->GetId();
	
	// create code package for new variables if doesn't exists
	if( IPluginManager::Get()->IsProjManOrganised() )
	{
		wxString pkgName = IPluginManager::Get()->GetCodePackage( wxT("udGenericVariableItem") );
		udProjectItem *package = proj->GetProjectItem( wxClassInfo::FindClass( wxT("udCodePackageItem") ), pkgName );
		if( !package )
		{
			package = proj->CreateProjectItem( wxT("udCodePackageItem"), parentId );
			ForceName( package, pkgName );
		}
		
		parentId = package->GetId();
	}
	
	ctagVariable *ctag = (ctagVariable*) m_treeSymbols->GetItemData( varId );
	
	// create code item
	udGenericVariableItem *data = (udGenericVariableItem*) proj->CreateProjectItem( wxT("udGenericVariableItem"), parentId );
	ForceName( data, ctag->m_Name );
	data->SetDescription( wxT("Original variable: \"") + ctag->m_Pattern + wxT("\"") );
	
	data->SetDataType( udLanguage::DT_USERDEFINED );
	data->SetUserDataType( GetDataType( ctag, udfWITHOUT_DECORATION ) );
	data->SetUserDeclPlace( udVariableItem::dlBUILTIN );
	data->SetValue( GetDataValue( ctag ) );
	
	data->UpdateSignature();
}

umlEnumItem* udRevEngPanel::CreateEnumElement(wxTreeItemId enumId)
{
	ctagEnum *ctag = (ctagEnum*) m_treeSymbols->GetItemData( enumId );
	
	if( ctag->m_Type == udCTAGS::ttENUM )
	{
		umlEnumItem *enumItem = new umlEnumItem();
		udEnumElementItem *enumElement = new udEnumElementItem();
		
		enumItem->SetUserData( enumElement );
		
		udLABEL::SetContent(ctag->m_Name, enumItem, udLABEL::ltTITLE);
		ForceName( enumElement, ctag->m_Name );
		
		if( ctag->m_Namespace.IsEmpty() ) m_mapProjectItems[ ctag->m_Name ] = enumElement;
		m_mapProjectItems[ ctag->m_Namespace + wxT("::") + ctag->m_Name ] = enumElement;
		
		if( m_checkBoxMembers->IsChecked() )
		{
			CreateEnumItems( enumElement, enumId );
		}
		
		enumElement->OnCreate();
		enumElement->UpdateInnerContent();
		
		return enumItem;
	}
	else
		return NULL;
}

void udRevEngPanel::CreateEnumItems(udEnumElementItem* enumItem, wxTreeItemId enumId)
{
	wxArrayTreeItemIds arrMembers;
	GetMemberIds( udCTAGS::ttENUM_ITEM, enumId, arrMembers );
	
	for(size_t i = 0; i < arrMembers.GetCount(); i++)
	{
		ctagEnumItem *ctag = (ctagEnumItem*) m_treeSymbols->GetItemData( arrMembers[i] );
		
		// create code item
		udEnumValueItem *data = new udEnumValueItem();
		ForceName( data, ctag->m_Name );
		data->SetValue( ctag->m_Value );
		data->SetDescription( wxT("Original class member: \"") + ctag->m_Pattern + wxT("\"") );
		
		// assign link to the class
		enumItem->AssignCodeItem( data );
	}
}

void udRevEngPanel::CreateEnumAssociations(udDiagramItem* diagram, wxTreeItemId enumId)
{
	ctagEnum *ctag = (ctagEnum*) m_treeSymbols->GetItemData( enumId );
	
	//udProjectItem *newEnum = udPROJECT::GetDiagramElement( diagram, ctag->m_Name );
	udProjectItem *newEnum = m_mapProjectItems[ ctag->m_Namespace + wxT("::") + ctag->m_Name ];
	if( newEnum )
	{
		// include associations
		//udProjectItem *outerClass = udPROJECT::GetDiagramElement( diagram, ctag->m_Namespace.AfterLast( wxT(':') ) );
		udProjectItem *outerClass = m_mapProjectItems[ ctag->m_Namespace ];
		if( outerClass )
		{
			umlIncludeAssocItem *connection = new umlIncludeAssocItem();
			udIncludeAssocElementItem *connElement = new udIncludeAssocElementItem();
			
			connection->SetUserData( connElement );
			
			ForceName( connElement, wxT("Include association element") );
			connElement->SetAccessType( GetAccessType( ctag->m_Access ) );
			
			connection->SetTrgShapeId( ((wxSFShapeBase*)newEnum->GetParent())->GetId() );
			connection->SetSrcShapeId( ((wxSFShapeBase*)outerClass->GetParent())->GetId() );
			
			diagram->GetDiagramManager().AddShape( connection, NULL, wxDefaultPosition, sfINITIALIZE, sfDONT_SAVE_STATE );	
		}
	}
}

////////////////////////////////////////////////////////////////////////////////

wxString udRevEngPanel::GetDataType(udCTAGS* ctag, bool decorations )
{
	wxString dataType;
	
	wxString name = ctag->m_Name;
	wxString pattern = ctag->m_Pattern;
	
	wxRegEx reName;
	if( reName.Compile( wxT(" .*::") + name ) && reName.Matches( pattern ) )
	{
		name = reName.GetMatch( pattern );
	}
	else if( reName.Compile( wxT(" ") + name + wxT("$") ) && reName.Matches( pattern ) )
	{
		name += wxT(" ");
		pattern += wxT(" ");
	}
	
	if( m_LangType == udCTAGS::ltCPP )
	{
		int namePos = wxNOT_FOUND;
		
		if( ctag->m_Type == udCTAGS::ttCLASS_MEMBER )
		{
			namePos = pattern.Find( name );
		}
		else if( ctag->m_Type == udCTAGS::ttCLASS_FUNCTION )
		{
			if( pattern.Contains( ((ctagClassFunction*)ctag)->m_ParentClass ) )
			{
				namePos = pattern.Find( ((ctagClassFunction*)ctag)->m_ParentClass );
			}
			else
				namePos = pattern.Find( name );
		}
		else
			namePos = pattern.Find( name );
			
		if( namePos != wxNOT_FOUND ) dataType = pattern.Mid(0, namePos);

		if( !decorations )
		{
			dataType.Replace( wxT("*"), wxT("") );
			dataType.Replace( wxT("&"), wxT("") );
		}
		
		dataType.Trim().Trim(false);
	}
	
	return dataType;
}

wxString udRevEngPanel::GetDataValue(udCTAGS* ctag)
{
	if( ctag->m_Type == udCTAGS::ttVARIABLE || ctag->m_Type == udCTAGS::ttVARIABLE )
	{
		wxString val = ctag->m_Pattern.AfterLast( wxT('=') );
		val.Replace( wxT(";"), wxT("") );
		return val.Trim().Trim(false);
	}
	else
		return wxEmptyString;
}

udLanguage::ACCESSTYPE udRevEngPanel::GetAccessType(const wxString& at)
{
	if( at == wxT("public") ) return udLanguage::AT_PUBLIC;
	else if( at == wxT("protected") ) return udLanguage::AT_PROTECTED;
	else if( at == wxT("private") ) return udLanguage::AT_PRIVATE;
	else return udLanguage::AT_PUBLIC;
}

void udRevEngPanel::GetFunctionArguments(udCTAGS* ctag, wxArrayString& args)
{
	wxString signature;
	
	if( ctag->m_Type == udCTAGS::ttCLASS_FUNCTION )
	{
		signature = ((ctagClassFunction*)ctag)->m_Signature;
	}
	else if( ctag->m_Type == udCTAGS::ttFUNCTION )
	{
		signature = ((ctagFunction*)ctag)->m_Signature;
	}
	
	int lpPos = signature.Find( wxT("(") );
	int rpPos = signature.Find( wxT(")") );
	
	if( lpPos != wxNOT_FOUND && rpPos != wxNOT_FOUND )
	{
		signature = signature.Mid( lpPos + 1, rpPos - lpPos - 1 );
	}
	
	args.Clear();
	
	wxStringTokenizer tokenz( signature, wxT(","), wxTOKEN_STRTOK );
	while( tokenz.HasMoreTokens() )
	{
		wxString arg = tokenz.GetNextToken().Trim().Trim(false);
		if( !arg.IsEmpty() ) args.Add( arg );
	}
}
