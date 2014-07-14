#include "wx_pch.h"

#ifdef _DEBUG_MSVC
#define new DEBUG_NEW
#endif

#include "gui/EditorPanel.h"
#include "UMLDesignerApp.h"
#include "UMLDesignerMain.h"

BEGIN_EVENT_TABLE ( udCodeEditorPanel,  _EditorPanel )
	EVT_STC_MARGINCLICK( wxID_ANY, udCodeEditorPanel::OnMarginClick )
	EVT_CD_ITEM_SELECTED( wxID_ANY, udCodeEditorPanel::OnProjectItemSelected )
END_EVENT_TABLE ()

// constructor and destructor ///////////////////////////////////////////////////////////////

udCodeEditorPanel::udCodeEditorPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size )
: _EditorPanel( parent, id, pos, size )
{
	m_pPrevLang = NULL;
	
	m_scintillaEditor->SetReadOnly( true );
	
	m_stCodeItem->SetLabel( wxT("") );
}

// event handlers ///////////////////////////////////////////////////////////////////////////

void udCodeEditorPanel::OnSave( wxCommandEvent& event )
{
	udCodeItem *pCI = GetAsCodeItem( wxGetApp().GetMainFrame()->GetSelectedProjectItem() );
	if( pCI )
	{
		pCI->SetCode( m_scintillaEditor->GetText() );
		//UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, pCI );
		UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_SELECTED, wxID_ANY, wxGetApp().GetMainFrame()->GetSelectedProjectItem() );
	}
}

void udCodeEditorPanel::OnMarginClick ( wxStyledTextEvent &event )
{
	if ( event.GetMargin() == 1 )
	{
		int lineClick = m_scintillaEditor->LineFromPosition ( event.GetPosition() );
		int levelClick = m_scintillaEditor->GetFoldLevel ( lineClick );

		if ( ( levelClick & wxSTC_FOLDLEVELHEADERFLAG ) > 0 )
		{
			m_scintillaEditor->ToggleFold ( lineClick );
		}
	}
}

void udCodeEditorPanel::OnProjectItemSelected(udProjectEvent& event)
{
	if( IsShown() )
	{
		udCodeItem *pCI = GetAsCodeItem( event.GetProjectItem() );
			
		// initialize the editor only if neccessary (i.e. active language has been changed)
		if( m_pPrevLang != wxGetApp().GetMainFrame()->GetSelectedLanguage() ) 
		{
			m_pPrevLang = wxGetApp().GetMainFrame()->GetSelectedLanguage();
			udFRAME::InitStyledTextCtrl( m_scintillaEditor, m_pPrevLang );
		}
			
		m_scintillaEditor->SetReadOnly( false );
		
		// update editor's content
		if( pCI )
		{
			m_stCodeItem->SetLabel( wxT("Code item: ") + pCI->GetName() );
			
			if( pCI->GetProperty(wxT("code")) )	m_scintillaEditor->SetText( pCI->GetCode() );
			else
			{
				m_scintillaEditor->SetText( wxT("<no editable content>") );
				m_scintillaEditor->SetReadOnly( true );
			}
		}
		else
		{
			m_stCodeItem->SetLabel( wxT("Code item: <none>") );
			m_scintillaEditor->SetText( wxT("<no editable content>") );
			m_scintillaEditor->SetReadOnly( true );
		}
	}
}

void udCodeEditorPanel::OnUpdateSave(wxUpdateUIEvent& event)
{
	event.Enable( CanSave() );
}

void udCodeEditorPanel::OnKeyDown(wxKeyEvent& event)
{
	switch( event.GetKeyCode() )
	{
		case 's':
		case 'S':
			if( event.AltDown() && CanSave() )
			{
				wxCommandEvent evt;
				OnSave( evt );
			}
			else
				event.Skip();
			break;
			
		default:
			event.Skip();
	}
}

// protected functions //////////////////////////////////////////////////////////////////////

udCodeItem* udCodeEditorPanel::GetAsCodeItem(udProjectItem* item)
{	
	udCodeItem *pCI = NULL;
	
	if( item )
	{
		// get original code item
		if( item->IsKindOf(CLASSINFO(udCodeLinkItem)) ) pCI = (udCodeItem*)((udCodeLinkItem*)item)->GetOriginal();
		else 
			pCI = wxDynamicCast( item, udCodeItem );
	}
	
	return pCI;
}
bool udCodeEditorPanel::CanSave()
{
	if( wxGetApp().GetMainFrame() )
	{
		udCodeItem *pCI = GetAsCodeItem( wxGetApp().GetMainFrame()->GetSelectedProjectItem() );
		return ( pCI && (m_scintillaEditor->GetText() != wxT("<no editable content>")) && (pCI->GetCode() != m_scintillaEditor->GetText()) );
	}
	
	return false;
}
