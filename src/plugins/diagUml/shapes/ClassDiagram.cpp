#include "ClassDiagram.h"
#include "classdiagram/InheritanceItem.h"
#include "classdiagram/InterfaceItem.h"
#include "classdiagram/TemplateBindItem.h"

IMPLEMENT_DYNAMIC_CLASS(umlClassDiagram, udDiagramCanvas)

umlClassDiagram::umlClassDiagram() : udDiagramCanvas()
{
}

umlClassDiagram::umlClassDiagram(wxSFDiagramManager *manager, wxWindow *parent, long id)
: udDiagramCanvas(manager, parent, id)
{
}

umlClassDiagram::~umlClassDiagram()
{

}

void umlClassDiagram::GetBaseClasses(umlClassItem* shape, ShapeList& bases)
{
	wxASSERT(shape);
	if( !shape ) return;
	
	umlClassItem *pClass;
	wxSFDiagramManager *pDiagManager = shape->GetShapeManager();
	
	ShapeList lstAssocs;
	pDiagManager->GetAssignedConnections( shape, CLASSINFO(umlInheritanceItem), wxSFShapeBase::lineSTARTING, lstAssocs );
	pDiagManager->GetAssignedConnections( shape, CLASSINFO(umlInterfaceItem), wxSFShapeBase::lineSTARTING, lstAssocs );
	pDiagManager->GetAssignedConnections( shape, CLASSINFO(umlTemplateBindItem), wxSFShapeBase::lineSTARTING, lstAssocs );
	
	for( ShapeList::iterator it = lstAssocs.begin(); it != lstAssocs.end(); ++it )
	{
		pClass =  wxDynamicCast( pDiagManager->FindShape( ((wxSFLineShape*)*it)->GetTrgShapeId() ), umlClassItem );
		if( pClass ) bases.Append( pClass );
	}
}

void umlClassDiagram::GetOuterClasses(umlClassItem* shape, ShapeList& bases)
{
	wxASSERT(shape);
	if( !shape ) return;
	
	umlClassItem *pClass;
	wxSFDiagramManager *pDiagManager = shape->GetShapeManager();
	
	ShapeList lstAssocs;
	pDiagManager->GetAssignedConnections( shape, CLASSINFO(umlInheritanceItem), wxSFShapeBase::lineSTARTING, lstAssocs );
	pDiagManager->GetAssignedConnections( shape, CLASSINFO(umlInterfaceItem), wxSFShapeBase::lineSTARTING, lstAssocs );
	pDiagManager->GetAssignedConnections( shape, CLASSINFO(umlTemplateBindItem), wxSFShapeBase::lineSTARTING, lstAssocs );
	pDiagManager->GetAssignedConnections( shape, CLASSINFO(umlUniDirectAssocItem), wxSFShapeBase::lineSTARTING, lstAssocs );
	pDiagManager->GetAssignedConnections( shape, CLASSINFO(umlBasicAggregItem), wxSFShapeBase::lineSTARTING, lstAssocs );
	pDiagManager->GetAssignedConnections( shape, CLASSINFO(umlCompAggregItem), wxSFShapeBase::lineSTARTING, lstAssocs );
	
	for( ShapeList::iterator it = lstAssocs.begin(); it != lstAssocs.end(); ++it )
	{
		pClass =  wxDynamicCast( pDiagManager->FindShape( ((wxSFLineShape*)*it)->GetTrgShapeId() ), umlClassItem );
		if( pClass ) bases.Append( pClass );
	}
}

void umlClassDiagram::GetClassMembers(umlClassItem* shape, wxClassInfo* type, udLanguage::ACCESSTYPE at, SerializableList& members)
{
	wxASSERT(shape);
	
	udProjectItem *pClassElement = udPROJECT::GetDiagramElement(shape);
	if( pClassElement )
	{
		SerializableList lstAllMembers;
		pClassElement->GetChildren( type, lstAllMembers );
		
		for( SerializableList::iterator it = lstAllMembers.begin(); it != lstAllMembers.end(); ++it )
		{
			if( (*it)->IsKindOf( CLASSINFO(udMemberLinkItem) ) )
			{
				if( (at == -1) || (((udMemberLinkItem*)*it)->GetAccessType() == at) ) members.Append( *it );
			}
		}
	}
}

void umlClassDiagram::GetClassAssociations(umlClassItem* shape, wxClassInfo* type, wxSFLineShape::CONNECTMODE direction, udLanguage::ACCESSTYPE at, ShapeList& assocs)
{
	wxASSERT(shape);
	
	ShapeList lstAssocs;
	
	shape->GetShapeManager()->GetAssignedConnections( shape, type, direction, lstAssocs );
	
	for( ShapeList::iterator it = lstAssocs.begin(); it != lstAssocs.end(); ++it )
	{
		udDiagElementItem *pAssocElement = udPROJECT::GetDiagramElement( *it );
		if( pAssocElement && (pAssocElement->GetAccessType() == at) ) assocs.Append( *it );
	}
}

