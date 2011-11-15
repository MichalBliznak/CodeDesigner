#include "RevEngPanel.h"

umlClassItem* udRevEngPanel::CreateClassElement(wxTreeItemId classId)
{
	ctagClass *ctag = (ctagClass*) m_treeSymbols->GetItemData( classId );
	
	umlClassItem *classItem = new umlClassItem();
	udClassElementItem *classElement = new udClassElementItem();
	
	classItem->SetUserData( classElement );
	
	udLABEL::SetContent(ctag->m_Name, classItem, udLABEL::ltTITLE);
	classElement->SetName( ctag->m_Name );
	
	classElement->OnCreate();
	classElement->UpdateInnerContent();
	
	return classItem;
}

umlInheritanceItem* udRevEngPanel::CreateClassConnection(udDiagramItem* diagram, wxTreeItemId classId)
{
	ctagClass *ctag = (ctagClass*) m_treeSymbols->GetItemData( classId );
	if( !ctag->m_Inherits.IsEmpty() )
	{
		udProjectItem *baseClass = udPROJECT::GetDiagramElement( diagram, ctag->m_Inherits );
		udProjectItem *newClass = udPROJECT::GetDiagramElement( diagram, ctag->m_Name );
		
		if( baseClass && newClass )
		{
			umlInheritanceItem *connection = new umlInheritanceItem();
			udInherElementItem *connElement = new udInherElementItem();
			
			connection->SetUserData( connElement );
			
			connElement->SetName( wxT("Inheritance element") );
			
			connection->SetSrcShapeId( ((wxSFShapeBase*)newClass->GetParent())->GetId() );
			connection->SetTrgShapeId( ((wxSFShapeBase*)baseClass->GetParent())->GetId() );
			
			return connection;
		}
	}
	
	return NULL;
}
