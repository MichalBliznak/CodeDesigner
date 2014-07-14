#include "wx_pch.h"

#ifdef _DEBUG_MSVC
#define new DEBUG_NEW
#endif

#include <wx/sstream.h>
#include <wx/filename.h>

#include "SettingsDialog.h"

BEGIN_EVENT_TABLE( udSettingsDialog, _SettingsDialog )
	EVT_PG_CHANGED( IDC_SETTINGSDLG_PROPGRID, udSettingsDialog::OnPropertyGridChange )
END_EVENT_TABLE();

// constructor and destructor ////////////////////////////////////////////////////////////////

udSettingsDialog::udSettingsDialog(wxWindow *parent, udSettings& settings, const wxString& title) :  m_Settings( settings ), _SettingsDialog( parent )
{
	SetTitle( title );
	m_sRootName = wxT("Settings");
}

udSettingsDialog::~udSettingsDialog()
{
}

// protected functions ///////////////////////////////////////////////////////////////////////

void udSettingsDialog::InitializeCategories()
{
	m_pCategoryTree->DeleteAllItems();
	
	// create categories tree root
	m_pCategoryTree->AddRoot( m_sRootName );
	
	// create categories tree
	SerializableList::compatibility_iterator node = m_Settings.GetRootItem()->GetFirstChildNode();
	while( node )
	{
		CreateCategory( (udSettingsCategory*)node->GetData(), m_pCategoryTree->GetRootItem() );
		node = node->GetNext();
	}
	m_pCategoryTree->ExpandAll();
	
	// initialize property grid
	m_pCategoryTree->SelectItem( m_pCategoryTree->GetFirstChild( m_pCategoryTree->GetRootItem(), nCookie ) );
}

void udSettingsDialog::CreateCategory(udSettingsCategory* category, const wxTreeItemId& parent)
{
	if( category && !category->IsKindOf( CLASSINFO(udHiddenCategory) ) )
	{
		wxTreeItemId newItem = m_pCategoryTree->AppendItem( parent, category->GetName() );
		
		SerializableList::compatibility_iterator node = category->GetFirstChildNode();
		while( node )
		{
			CreateCategory( (udSettingsCategory*)node->GetData(), newItem );
			node = node->GetNext();
		}
	}
}

void udSettingsDialog::CreateCategoryContent(udSettingsCategory* category)
{
	xsProperty *pProperty;

	// create cathegory title
	m_pPropertyGrid->Clear();
	m_pPropertyGrid->Append( new wxPropertyCategory( category->GetName() ) );
		
	PropertyList::compatibility_iterator node = category->GetProperties().GetFirst();
	while( node )
	{
		pProperty = node->GetData();
		IOFcn_t WriteFcn = udXS2PG::GetWriteFcn( pProperty->m_sDataType );
		if( WriteFcn )
		{
			WriteFcn( m_pPropertyGrid, pProperty->m_sFieldName, pProperty );
		}

		node = node->GetNext();
	}
}

// virtual event handlers /////////////////////////////////////////////////////////////////////////

void udSettingsDialog::OnChangeCategory(wxTreeEvent& event)
{
	wxTreeItemId treeId = event.GetItem();
	
	if( treeId.IsOk() )
	{
		udSettingsCategory *pCategory = m_Settings.GetCategory( m_pCategoryTree->GetItemText( treeId ) );
		if( pCategory )
		{
			CreateCategoryContent( pCategory );
		}
		else
		{
			m_pPropertyGrid->Clear();
			m_pPropertyGrid->Append( new wxPropertyCategory( m_pCategoryTree->GetItemText( treeId ) ) );
		}
	}
}

void udSettingsDialog::OnInit(wxInitDialogEvent& event)
{
	InitializeCategories();
	
	// store current settings content
	wxStringOutputStream out( &m_sPrevSettings );
	if( out.IsOk() )
	{
		m_Settings.SerializeToXml( out );
	}
	
	event.Skip();
}

void udSettingsDialog::OnOk(wxCommandEvent& event)
{	
	EndModal( wxID_OK );
}

void udSettingsDialog::OnCancel(wxCommandEvent& event)
{
	// remove old content
	m_Settings.RemoveAll();
	// restore previous settings content
	wxStringInputStream in( m_sPrevSettings );
	if( in.IsOk() ) 
	{
		m_Settings.DeserializeFromXml( in );
	}
	
	EndModal( wxID_CANCEL );
}

void udSettingsDialog::OnPropertyGridChange(wxPropertyGridEvent& event)
{
	udXS2PG xs2pg;
	
	// get name of changed property
	const wxString& name = event.GetPropertyName();
	
	// assign property value to relevant settings property
	xsProperty *pProperty = m_Settings.GetProperty( name );
	
	IOFcn_t ReadFcn = xs2pg.GetReadFcn( pProperty->m_sDataType );
	if( ReadFcn )
	{
		ReadFcn( m_pPropertyGrid, name, pProperty );
	}
}

void udSettingsDialog::OnDefaults(wxCommandEvent& event)
{
	if( wxMessageBox( wxT("Are you sure you want to set all properties to default values?"), wxT("CodeDesigner"), wxICON_QUESTION | wxYES_NO ) == wxYES )
	{
		m_Settings.RemoveAll();
		m_Settings.CreateCategories();
		
		InitializeCategories();
	}
}
