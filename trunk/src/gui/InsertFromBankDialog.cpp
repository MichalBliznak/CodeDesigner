#include "wx_pch.h"

#ifdef _DEBUG_MSVC
#define new DEBUG_NEW
#endif

#include "gui/InsertFromBankDialog.h"
#include "gui/DependenciesDialog.h"
#include "DiagramBank.h"
#include "UMLDesignerApp.h"
#include "UMLDesignerMain.h"
#include "Art.h"
#include "XS2PG.h"

// constructor and destructor ///////////////////////////////////////////////////////

udInsertFromBankDialog::udInsertFromBankDialog(wxWindow *parent, udPackageItem *package) : _InsertFromBankDialog( parent )
{
	m_Package = package;
	
	// initialize categories
	udDiagramBank& Bank = wxGetApp().GetDiagramBank();
	
	wxArrayString arrCategories;
	Bank.GetCategoriesNames( arrCategories );
	
	for( size_t i = 0; i < arrCategories.GetCount(); i++ )
	{
		m_chCategory->Append( arrCategories[i] );
	}
	m_chCategory->Select(0);
	
	// initialize digrams
	FillDiagrams( m_chCategory->GetStringSelection() );
}

udInsertFromBankDialog::~udInsertFromBankDialog()
{
}

// virtual event handlers ///////////////////////////////////////////////////////////

void udInsertFromBankDialog::OnDeselectAll(wxCommandEvent& event)
{
	DeselectAllItems( m_lstDiagrams );
}

void udInsertFromBankDialog::OnInsertClick(wxCommandEvent& event)
{
	udDiagramBank& Bank = wxGetApp().GetDiagramBank();
	
	udDiagramRecord *pRec;
	udDiagramItem *pDiag;
//	udDiagElementItem *pElement;
	udCodeItem *pDep;
	SerializableList lstElements;
	SerializableList lstDeps;
	
	bool fSuccsess = true;
	
	wxSetCursor( *wxHOURGLASS_CURSOR );
	
	udDiagramCategory *pCat = Bank.GetCategory( m_chCategory->GetStringSelection() );
	if( pCat )
	{
		UMLDesignerApp::ClearLog();
		
		for(int i = 0; i < m_lstDiagrams->GetItemCount(); i++)
		{
			if( m_lstDiagrams->GetItemState( i, wxLIST_STATE_SELECTED ) )
			{
				pRec = (udDiagramRecord*) pCat->GetChildrenList().Item(i)->GetData();
				
				// insert only diagrams dependencies which are not present in active project
				lstDeps.Clear();
				pRec->GetDiagramDependencies( lstDeps );
				
				bool fUnique = true;
				
				// first test whether code item with the same name already exists
				for( SerializableList::iterator it = lstDeps.begin(); it != lstDeps.end(); ++it )
				{
					pDep = (udCodeItem*) *it;
					if( !udProject::Get()->IsUniqueName( pDep->GetName() ) )
					{
						fUnique = false;
						fSuccsess = false;
						UMLDesignerApp::Log( wxT("ERROR: code item with name '") + pDep->GetName() + wxT("' from diagram '") + pRec->GetDiagram()->GetName() + wxT("' already exists in the project.") );
					}
				}
				
				if( fUnique )
				{
					pDiag = (udDiagramItem*) pRec->GetDiagram()->Clone();
					
					// make all diagram's items' names unique
					pDiag->SetName( pDiag->GetName() );
					
//					lstElements.Clear();
//					udPROJECT::GetDiagramElements( pDiag, CLASSINFO(udDiagElementItem), lstElements, sfRECURSIVE );
//					for( SerializableList::iterator it = lstElements.begin(); it != lstElements.end(); ++it )
//					{
//						pElement = (udDiagElementItem*) *it;
//						pElement->SetName( pElement->GetName() );
//						udLABEL::SetContent( pElement->GetName(), (wxSFShapeBase*) pElement->GetParent(), udLABEL::ltTITLE );
//					}

					m_Package->AddChild( pDiag );
					
					// first test whether code item with the same name already exists
					for( SerializableList::iterator it = lstDeps.begin(); it != lstDeps.end(); ++it )
					{
						pDep = (udCodeItem*)(*it)->Clone();
						
						udProject::Get()->AddItem( (xsSerializable*)NULL, pDep );
						UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_ADDED, wxID_ANY, pDep, (udProjectItem*)udProject::Get()->GetRootItem() );//, udfDELAYED );
					}
					
					UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_ADDED, wxID_ANY, pDiag, m_Package );//, udfDELAYED );
				}
			}
		}
	}
	
	wxSetCursor( *wxSTANDARD_CURSOR );
	
	if( fSuccsess ) EndModal( wxID_OK );
	else
		EndModal( wxID_ABORT );
}

void udInsertFromBankDialog::OnSelectAll(wxCommandEvent& event)
{
	SelectAllItems( m_lstDiagrams );
}

void udInsertFromBankDialog::OnCategoryChange(wxCommandEvent& event)
{
	FillDiagrams( m_chCategory->GetStringSelection() );
}

void udInsertFromBankDialog::OnShowDeps(wxCommandEvent& event)
{
	udDiagramBank& Bank = wxGetApp().GetDiagramBank();
	
	udDiagramCategory *pCat = Bank.GetCategory( m_chCategory->GetStringSelection() );
	if( pCat )
	{
		wxArrayInt arrSelection;
		GetSelectedItems( m_lstDiagrams, arrSelection );
		
		SerializableList lstRecords;
		for( size_t i = 0; i < arrSelection.GetCount(); i++ )
		{
			lstRecords.Append( pCat->GetChildrenList().Item(i)->GetData() );
		}
		
		udDependenciesDialog dlg( this, lstRecords );
		
		dlg.ShowModal();
	}
}

void udInsertFromBankDialog::OnUpdateShowDeps(wxUpdateUIEvent& event)
{
	wxArrayInt selected;
	GetSelectedItems( m_lstDiagrams, selected );
	
	event.Enable( !selected.IsEmpty() );
}

// protected member functions ///////////////////////////////////////////////////////

void udInsertFromBankDialog::FillDiagrams(const wxString& category)
{
	udDiagramBank& Bank = wxGetApp().GetDiagramBank();
	
	// insert diagrams
	SerializableList lstDiags;
	udDiagramCategory *pCat = Bank.GetCategory( category );
	if( pCat )
	{
		SerializableList::compatibility_iterator node =  pCat->GetFirstChildNode();
		while( node )
		{
			udDiagramItem *pDiag = ((udDiagramRecord*) node->GetData())->GetDiagram();
			if( pDiag ) lstDiags.Append( pDiag );
			
			node = node->GetNext();
		}
		
		InsertProjectItems( m_lstDiagrams, lstDiags, udfSORT );
	}
}
