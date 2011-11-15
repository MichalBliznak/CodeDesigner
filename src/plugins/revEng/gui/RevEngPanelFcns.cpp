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

void udRevEngPanel::CreateClassConnections(udDiagramItem* diagram, wxTreeItemId classId)
{
	ctagClass *ctag = (ctagClass*) m_treeSymbols->GetItemData( classId );
	if( !ctag->m_Inherits.IsEmpty() )
	{
		udProjectItem *newClass = udPROJECT::GetDiagramElement( diagram, ctag->m_Name );
		if( newClass )
		{
			wxStringTokenizer tokenz( ctag->m_Inherits, wxT(",") );
			while( tokenz.HasMoreTokens() )
			{
				udProjectItem *baseClass = udPROJECT::GetDiagramElement( diagram, tokenz.GetNextToken() );
				if( baseClass )
				{
					umlInheritanceItem *connection = new umlInheritanceItem();
					udInherElementItem *connElement = new udInherElementItem();
					
					connection->SetUserData( connElement );
					
					connElement->SetName( wxT("Inheritance element") );
					
					connection->SetSrcShapeId( ((wxSFShapeBase*)newClass->GetParent())->GetId() );
					connection->SetTrgShapeId( ((wxSFShapeBase*)baseClass->GetParent())->GetId() );
					
					diagram->GetDiagramManager().AddShape( connection, NULL, wxDefaultPosition, sfINITIALIZE, sfDONT_SAVE_STATE );	
				}
			}
		}
	}
}
