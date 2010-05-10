#include "wx_pch.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#ifdef _DEBUG_MSVC
#define new DEBUG_NEW
#endif

#include "DiagramBank.h"

// udDiagramRecord //////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udDiagramRecord, xsSerializable);

udDiagramRecord::udDiagramRecord()
{
	m_Description = wxT("Diagram record's description...");
	
	XS_SERIALIZE( m_Description, wxT("description") );
}

udDiagramRecord::udDiagramRecord(const udDiagramRecord& obj) : xsSerializable(obj)
{
	m_Description = obj.m_Description;
	
	XS_SERIALIZE( m_Description, wxT("description") );
}

udDiagramRecord::~udDiagramRecord()
{
}

/////////////////////////////////////////////////////////////////////////////////////////

udDiagramItem* udDiagramRecord::GetDiagram()
{
	return (udDiagramItem*) GetFirstChild( CLASSINFO(udDiagramItem) );
}

void udDiagramRecord::GetDiagramDependencies(SerializableList& deps)
{
	udCodeItem *pCode = (udCodeItem*) GetFirstChild( CLASSINFO(udCodeItem) );
	while( pCode )
	{	
		deps.Append( pCode );
		pCode = (udCodeItem*) pCode->GetSibbling( CLASSINFO(udCodeItem) );
	}
}

// udDiagramCategory ////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC_CLASS(udDiagramCategory, xsSerializable);

udDiagramCategory::udDiagramCategory()
{
	m_Name = wxT("Common");
	
	XS_SERIALIZE( m_Name, wxT("name") );
}

udDiagramCategory::~udDiagramCategory()
{
}

/////////////////////////////////////////////////////////////////////////////////////////

udDiagramRecord* udDiagramCategory::GetDiagramRecord(const wxString& diagname)
{
	udDiagramRecord *pRec;
	udDiagramItem *pDiag;
	
	SerializableList::compatibility_iterator node = GetFirstChildNode();
	while( node )
	{
		pRec = (udDiagramRecord*) node->GetData();
		
		pDiag = pRec->GetDiagram();
		if( pDiag && (pDiag->GetName() == diagname) ) return pRec;
		
		node = node->GetNext();
	}
	
	return NULL;
}

void udDiagramCategory::AddDiagram(udDiagramItem* diag, const wxString& desc)
{
	udDiagramRecord *pRec = new udDiagramRecord();
	
	if( pRec )
	{
		// add diagram to the record
		xsSerializable *pNewDiag = pRec->AddChild( (xsSerializable*) diag->Clone() );
		if( pNewDiag )
		{
			// in some cases the diagram's serialization could be disabled
			pNewDiag->EnableSerialization( true );
			
			// add description
			pRec->SetDescription( desc );
			
			// get all diagram dependecies
			SerializableList lstDeps;
			udProject::Get()->GetDiagramCodeItems( diag, CLASSINFO(udCodeItem), lstDeps );
			for( SerializableList::iterator it = lstDeps.begin(); it != lstDeps.end(); ++it )
			{
				pRec->AddChild( (xsSerializable*)(*it)->Clone() );
			}
			
			AddChild( pRec );
		}
		else
			delete pRec;
	}
}

void udDiagramCategory::RemoveDiagram(const wxString& diagname)
{
	udDiagramRecord *pRec = GetDiagramRecord( diagname );
	if( pRec )
	{
		GetChildrenList().DeleteObject( pRec );
		delete pRec;
	}
}

void udDiagramCategory::CopyContent(udDiagramCategory* dest)
{
	udDiagramRecord *pRec;
	
	SerializableList::compatibility_iterator node = GetFirstChildNode();
	while( node )
	{
		pRec = (udDiagramRecord*) node->GetData();
		dest->AddChild( (xsSerializable*) pRec->Clone() );
		
		node = node->GetNext();
	}
}

// udDiagramBank ////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC_CLASS(udDiagramBank, wxXmlSerializer);

udDiagramBank::udDiagramBank()
{
	SetSerializerOwner( wxT("CodeDesigner") );
	SetSerializerRootName( wxT("categories") );
	SetSerializerVersion( wxT("1") );
}

udDiagramBank::~udDiagramBank()
{
}

/////////////////////////////////////////////////////////////////////////////////////////

udDiagramCategory* udDiagramBank::GetCategory(const wxString& name)
{
	udDiagramCategory *pCat;
	
	SerializableList::compatibility_iterator node = GetRootItem()->GetFirstChildNode();
	while( node )
	{
		pCat = (udDiagramCategory*) node->GetData();
		
		if( pCat->GetName() == name ) return pCat;
		
		node = node->GetNext();
	}
	
	return NULL;
}

udDiagramCategory* udDiagramBank::CreateCategory(const wxString& name)
{
	udDiagramCategory *pCat = new udDiagramCategory();
	if( pCat )
	{
		pCat->SetName( name );
		AddItem( GetRootItem(), pCat );
	}
	
	return pCat;
}

void udDiagramBank::RemoveCategory(const wxString& name)
{
	udDiagramCategory *pCat = GetCategory( name );
	if( pCat )
	{
		RemoveItem( pCat );
	}
}

void udDiagramBank::CreateCategories()
{
	AddItem( GetRootItem(), new udDiagramCategory() );
}

void udDiagramBank::GetCategoriesNames(wxArrayString& categories)
{
	udDiagramCategory *pCat;
	
	SerializableList::compatibility_iterator node = GetRootItem()->GetFirstChildNode();
	while( node )
	{
		pCat = (udDiagramCategory*) node->GetData();
		
		categories.Add( pCat->GetName() );
		
		node = node->GetNext();
	}
}
