#include "DiagSCH.h"

#include <wx/textdlg.h>
#include <wx/regex.h>
#include <wx/artprov.h>

#include "projectbase/codegen/Generator.h"
#include "projectbase/gui/FunctionDialog.h"
#include "gui/EventDialog.h"
#include "gui/SSCHDiagramDialog.h"
#include "gui/ActionLinkDialog.h"
#include "projectbase/gui/VariableDialog.h"
#include "gui/TransitionDialog.h"
#include "gui/FinalStateDialog.h"
#include "gui/SubStateDialog.h"
#include "gui/CompStateDialog.h"
#include "gui/EventLinkDialog.h"
#include "Ids.h"
#include "DiagIds.h"
#include "shapes/SimpleStateChartDiagram.h"
#include "shapes/StateChartDiagram.h"

#include <wx/wxsf/wxShapeFramework.h>

/////////////////////////////////////////////////////////////////////////////////////
// udSStateChartDiagramItem class ///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udSStateChartDiagramItem, udDiagramItem);

// constructor and destructor ///////////////////////////////////////////////////////

udSStateChartDiagramItem::udSStateChartDiagramItem()
{
    m_sDiagramType = udnSIMPLE_STATE_CHART;
    m_sName = udnSIMPLE_STATE_CHART;

    m_sActiveGenerator = wxT("udSStateChartGenerator");
    m_sActiveAlgorithm = wxT("udLoopCaseAlgorithm");
	m_sInputAction = wxT("<none>");
	m_fNonBlocking = false;
	m_fInline = false;
	
	XS_SERIALIZE(m_sInputAction, wxT("input_action"));
	XS_SERIALIZE(m_fNonBlocking, wxT("non_blocking"));
	XS_SERIALIZE(m_fInline, wxT("inline"));
}

udSStateChartDiagramItem::udSStateChartDiagramItem(const udSStateChartDiagramItem &obj)
: udDiagramItem(obj)
{
    m_sDiagramType = udnSIMPLE_STATE_CHART;
	m_sInputAction = obj.m_sInputAction;
	m_fNonBlocking = obj.m_fNonBlocking;
	m_fInline = obj.m_fInline;
	
	XS_SERIALIZE(m_sInputAction, wxT("input_action"));
	XS_SERIALIZE(m_fNonBlocking, wxT("non_blocking"));
	XS_SERIALIZE(m_fInline, wxT("inline"));
}

udSStateChartDiagramItem::~udSStateChartDiagramItem()
{
}

udDiagramCanvas* udSStateChartDiagramItem::CreateCanvas()
{
    //return new umlSimpleStateChartDiagram(&m_DiagramManager, IPluginManager::Get()->GetMainNotebook(), wxID_ANY);
	return udDiagramItem::CreateCanvas();
}

// public virtual functions //////////////////////////////////////////////////////

void udSStateChartDiagramItem::OnEditItem(wxWindow* parent)
{
	udSChDiagramDialog dlg( parent, this, IPluginManager::Get()->GetSelectedLanguage() );
	udWindowManager dlgman( dlg, wxT("sch_diagram_dialog") );
	
	dlg.SetCodeName( m_sName );
	dlg.SetDescription( m_sDescription );
	dlg.SetInline( m_fInline );
	dlg.SetGenerateCode( m_fGenerate );
	dlg.SetOutputFile( m_sOutputFile );
	dlg.SetInputAction( m_sInputAction );
	dlg.SetNonBlocking( m_fNonBlocking );
	
	if( dlg.ShowModal() == wxID_OK )
	{
		m_sDescription = dlg.GetDescription();
		m_fInline = dlg.IsInline();
		m_fGenerate = dlg.GetGenerateCode();
		m_sInputAction = dlg.GetInputAction();
		m_fNonBlocking = dlg.IsNonBlocking();
		
		if( dlg.GetOutputFile().Contains( wxT(".") ) )
		{
			m_sOutputFile = dlg.GetOutputFile().BeforeLast( '.' );
		}
		else
			m_sOutputFile = dlg.GetOutputFile();
		
		udGenerator *pGen = udPROJECT::CreateGenerator( dlg.GetGenerator() );
		if(pGen)
		{
			SetActiveGenerator( pGen->GetClassInfo()->GetClassName() );
			
			udAlgorithm *pAlg = pGen->FindAlgorithm( dlg.GetAlgorithm() );
			if(pAlg)
			{
				SetActiveAlgorithm( pAlg->GetClassInfo()->GetClassName() );
			}
			
			delete pGen;
		}
		else
		{
			SetActiveGenerator(wxT(""));
			SetActiveAlgorithm(wxT(""));
		}
			
		OnTreeTextChange( dlg.GetCodeName() );
		
		IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, this );
	}
}

void udSStateChartDiagramItem::GetSpecificCodeItems(wxClassInfo* type, SerializableList& codeitems)
{
	// get input action function if supported
	udFunctionItem *pFcn = wxDynamicCast( IPluginManager::Get()->GetProject()->GetProjectItem( CLASSINFO(udFunctionItem), m_sInputAction ), udFunctionItem );
	if( pFcn && pFcn->IsKindOf(type) && (codeitems.IndexOf(pFcn) == wxNOT_FOUND) )
	{
		codeitems.Append( pFcn );
	}
}

/////////////////////////////////////////////////////////////////////////////////////
// udHStateChartDiagramItem class ///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udHStateChartDiagramItem, udSStateChartDiagramItem);

// constructor and destructor ///////////////////////////////////////////////////////

udHStateChartDiagramItem::udHStateChartDiagramItem()
{
    m_sDiagramType = udnSTATE_CHART;
    m_sName = udnSTATE_CHART;

    m_sActiveGenerator = wxT("udHStateChartGenerator");
    m_sActiveAlgorithm = wxT("udLoopCaseAlgorithm");
    //m_sActiveAlgorithm = wxT("udQLAlgorithm");
    //m_sActiveAlgorithm = wxT("udOMPAlgorithm");
}

udHStateChartDiagramItem::udHStateChartDiagramItem(const udHStateChartDiagramItem &obj)
: udSStateChartDiagramItem(obj)
{
    m_sDiagramType = udnSTATE_CHART;
}

udHStateChartDiagramItem::~udHStateChartDiagramItem()
{
}

udDiagramCanvas* udHStateChartDiagramItem::CreateCanvas()
{
    //return new umlStateChartDiagram(&m_DiagramManager, IPluginManager::Get()->GetMainNotebook(), wxID_ANY);
	return udDiagramItem::CreateCanvas();
}

/////////////////////////////////////////////////////////////////////////////////////
// udTransElementItem class //////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udTransElementItem, udDiagElementItem);

// constructor and destructor ///////////////////////////////////////////////////////

udTransElementItem::udTransElementItem()
{
	m_nPriority = uddvPRIORITY_MIN;
	m_sDescription = wxT("Transition's description...");
	m_fMustBeUnique = false;
	
	AcceptChild(wxT("udActionLinkItem"));
	AcceptChild(wxT("udConditionLinkItem"));
	AcceptChild(wxT("udEventLinkItem"));
	
	XS_SERIALIZE_EX(m_nPriority, wxT("priority"), uddvPRIORITY_MIN);
	XS_SERIALIZE( m_sDescription, wxT("description") );
}

udTransElementItem::udTransElementItem(const udTransElementItem &obj)
: udDiagElementItem(obj)
{
	m_nPriority = obj.m_nPriority;
	m_sDescription = obj.m_sDescription;
	
	XS_SERIALIZE_EX(m_nPriority, wxT("priority"), uddvPRIORITY_MIN);
	XS_SERIALIZE( m_sDescription, wxT("description") );
}

udTransElementItem::~udTransElementItem()
{
}

// public functions ////////////////////////////////////////////////////////////////

void udTransElementItem::OnEditItem(wxWindow *parent)
{
	udTransitionDialog dlg( parent, this, IPluginManager::Get()->GetSelectedLanguage() );
	udWindowManager dlgman( dlg, wxT("transition_dialog") );
	
	dlg.SetCodeName( m_sName );
	dlg.SetDescription( m_sDescription );
	dlg.SetPriority( m_nPriority );
	
	if( dlg.ShowModal() == wxID_OK )
	{
		m_sDescription = dlg.GetDescription();
		
		SetConditionString( dlg.GetConditionString() );
		SetActionString( dlg.GetActionsString() );
		
		m_nPriority = dlg.GetPriority();
		
		OnTreeTextChange( dlg.GetCodeName() );
		
		IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, this );
	}
}

void udTransElementItem::OnShapeTextChange(const wxString &txt, udLABEL::TYPE type, int id)
{
	SetGuardString(txt);
}

// public functions ////////////////////////////////////////////////////////////////

bool udTransElementItem::SetGuardString(const wxString &guard)
{
	bool fSuccess = false;
	wxString sRegex = wxT("^<<.*/\\s*\\[.*\\]\\s*>>$");
	//wxT("<<.*/\\s*\\[.*\\]\\s*>>")
	//wxT("<<\\s*[a-zA-Z0-9_\\(\\)]*\\s*/\\s*\\[\\s*[a-zA-Z0-9_,\\(\\)\\s]*\\s*\\]\\s*>>")
	//wxT("<<\\s*([a-zA-Z0-9_]*(?<CONDARGS>\\([a-zA-Z0-9_,\\s]*\\))*)\\s*/\\s*\\[\\s*(?:(?<ACTIONS>[a-zA-Z0-9_]*(?<ACTARGS>\\([a-zA-Z0-9_,\\s]*\\))\\s*,?\\s*)*)\\]\\s*>>")

	wxRegEx reGuard( sRegex, wxRE_ADVANCED );
	if ( reGuard.Matches( guard ) )
	{
		fSuccess = true;
			
		wxString sGuard = guard;
		sGuard.Replace( wxT("<"), wxT("") );
		sGuard.Replace( wxT(">"), wxT("") );
			
		SetConditionString( sGuard.BeforeFirst('/') );
		
		sGuard = sGuard.AfterLast('[').BeforeFirst(']');
		
		SetActionString( sGuard );
	}
	else
	{
		wxMessageBox( wxString::Format( wxT("Given guard content doesn't match the allowed form '%s'."), sRegex.c_str() ), wxT("CodeDesigner"), wxICON_WARNING | wxOK);
	}

	return fSuccess;
}

void udTransElementItem::SetConditionString(const wxString& cond)
{
	wxString sRegex = wxT("^[\\s]*[0-9]{0,3}[\\s]*[:]?[a-zA-Z0-9_\\(\\),\\s]*$");
	
	wxRegEx reGuard( sRegex, wxRE_ADVANCED );
	if( reGuard.Matches( cond ) )
	{
		// get uniform condition name
		wxString sCond = cond;

		if( !sCond.IsEmpty() )
		{
			// obtain priority level
			wxString sPriority = sCond.BeforeFirst( ':' );
			if( sPriority != sCond )
			{
				sPriority.Trim(true).Trim(false);
			
				if( sPriority.IsEmpty() ) m_nPriority = uddvPRIORITY_MIN;
				else
				{
					sPriority.ToLong( &m_nPriority );
					if( (m_nPriority < uddvPRIORITY_MAX) || (m_nPriority > uddvPRIORITY_MIN) ) m_nPriority = uddvPRIORITY_MIN;
				}
				sCond = sCond.AfterFirst( ':' );
			}
			else
				m_nPriority = uddvPRIORITY_MIN;
			
			sCond.Trim(true).Trim(false);
			
			StoreCallParams();
			
			ClearCodeItems( CLASSINFO(udConditionItem) );
			ClearCodeItems( CLASSINFO(udEventItem) );
			
			if( sCond.IsEmpty() ) return;
			
			sCond = RemoveCallParams( sCond );
			
			// try to find condition or event with similar name
			udCodeItem *pCond = (udCodeItem*) IPluginManager::Get()->GetProject()->GetProjectItem( CLASSINFO(udConditionItem), sCond );
			if( !pCond ) pCond = (udCodeItem*) IPluginManager::Get()->GetProject()->GetProjectItem( CLASSINFO(udEventItem), sCond );
			
			// create a link to condition and assign it to this transition
			if( pCond )
			{
				udCodeLinkItem *pLink = NULL;
					
				if( pCond->IsKindOf( CLASSINFO( udEventItem) ) ) pLink = new udEventLinkItem(pCond);
				else
					pLink = new udConditionLinkItem(pCond);
					
				AssignCodeItem( pLink );
			}
			else
			{
				if( wxMessageBox( wxString::Format( wxT("Condition with name '%s' doesn't exist yet. Would you like to create one?"), sCond.c_str() ), wxT("CodeDesigner"), wxYES_NO | wxICON_QUESTION  ) == wxYES )
				{
					udProjectItem *pRoot =  (udProjectItem*)IPluginManager::Get()->GetProject()->GetRootItem();
					// create new condition
					udConditionItem* pNewCond = (udConditionItem*)IPluginManager::Get()->GetProject()->CreateProjectItem( wxT("udConditionItem"), pRoot->GetId() );
					// create relevant tree item
					if( pNewCond )
					{
						pNewCond->SetName( sCond );
						pNewCond->UpdateSignature();
						
						IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_ADDED, wxID_ANY, pNewCond, pRoot );
						
						// assign the link to selected transition
						AssignCodeItem( new udConditionLinkItem(pNewCond) );
		
					}
				}
			}
			
			RestoreCallParams();
		}
		else
			ClearCodeItems( CLASSINFO(udConditionItem) );
	}
	else
		 wxMessageBox( wxString::Format( wxT("Name '%s' doesn't match the allowed form '%s'."), cond.c_str(), sRegex.c_str() ), wxT("CodeDesigner"), wxOK | wxICON_WARNING );
}
 
void udTransElementItem::SetActionString(const wxString& acts)
{
	wxString sRegex = wxT("^[a-zA-Z0-9_\\(\\),\\s]*$");
	
	wxRegEx reGuard( sRegex, wxRE_ADVANCED);
	if( reGuard.Matches( acts ) )
	{
		// get uniform condition name
		wxString sActions = acts;
		
		StoreCallParams();
		
		ClearCodeItems( CLASSINFO(udActionItem) );
			
		wxString sAct;
			
		sActions = RemoveCallParams( sActions );
		
		wxStringTokenizer tokens( sActions, wxT(","), wxTOKEN_STRTOK );
		while ( tokens.HasMoreTokens() ) 
		{ 
			sAct = tokens.GetNextToken().Trim(true).Trim(false);
			if( sAct.IsEmpty() ) continue;

			// try to find condition with similar name
			udActionItem *pAction = (udActionItem*) IPluginManager::Get()->GetProject()->GetProjectItem( CLASSINFO(udActionItem), sAct );
				
			// create a link to condition and assign it to this transition
			if( pAction )
			{
				AssignCodeItem( new udActionLinkItem(pAction) );
			}
			else
			{
				if( wxMessageBox( wxString::Format( wxT("Action with name '%s' doesn't exist yet. Would you like to create one?"), sAct.c_str() ), wxT("CodeDesigner"), wxYES_NO | wxICON_QUESTION  ) == wxYES )
				{
					udProjectItem *pRoot =  (udProjectItem*) IPluginManager::Get()->GetProject()->GetRootItem();
					// create new condition
					udActionItem* pNewAct = (udActionItem*) IPluginManager::Get()->GetProject()->CreateProjectItem( wxT("udActionItem"), pRoot->GetId() );
					// create relevant tree item
					if( pNewAct )
					{
						pNewAct->SetName( sAct );
						pNewAct->UpdateSignature();
						
						IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_ADDED, wxID_ANY, pNewAct, pRoot );
						
						// assign the link to selected transition
						AssignCodeItem( new udActionLinkItem(pNewAct) );
					}
				}
			}
		}
		
		RestoreCallParams();
	}
	else
		 wxMessageBox( wxString::Format( wxT("Action list '%s' doesn't match the allowed form '%s'."), acts.c_str(), sRegex.c_str() ), wxT("CodeDesigner"), wxOK | wxICON_WARNING );
}

bool udTransElementItem::HasCondition()
{
	return GetCondition();
}

bool udTransElementItem::HasActions()
{
	SerializableList lstActions;
	GetActions(lstActions);
	
	return !lstActions.IsEmpty();
}

wxString udTransElementItem::GetGuardString()
{
	return wxT("<< ") + GetConditionString() + wxT(" / [") + GetActionsString() + wxT("] >>");
}

udProjectItem* udTransElementItem::GetCondition(bool original)
{
	SerializableList lstConditions;
	GetCodeItems( CLASSINFO(udConditionItem), lstConditions, original );
	GetCodeItems( CLASSINFO(udEventItem), lstConditions, original );
	
	wxASSERT( lstConditions.GetCount() < 2 );
	
	if( !lstConditions.IsEmpty() ) return (udProjectItem*) lstConditions.GetFirst()->GetData();
	else
		return NULL;
}

wxString udTransElementItem::GetConditionAsString(udCodeItem::CODEFORMAT format, udLanguage *lang)
{
	udProjectItem *pCond = GetCondition();
	if( pCond )
	{
		if( pCond->IsKindOf( CLASSINFO(udCodeItem) ) ) return ((udCodeItem*) pCond)->ToString( format, lang);
		else
			return ((udCodeLinkItem*) pCond)->ToString( format, lang);
	}
	else
		return wxEmptyString;
}

wxString udTransElementItem::GetConditionString()
{
	wxString sCond = GetConditionAsString( udCodeItem::cfFORMAL, NULL );
	if( !sCond.IsEmpty() ) 
	{
		if( m_nPriority != uddvPRIORITY_MIN )
		{
			return wxString::Format( wxT("%d : %s"), m_nPriority, sCond.c_str() );
		}
		else
			return sCond;
	}
	else
		return wxT("");
}

void udTransElementItem::GetActions(SerializableList& actions, bool original)
{
	GetCodeItems( CLASSINFO(udActionItem), actions, original );
}

wxString udTransElementItem::GetActionAsString( udProjectItem *action, udCodeItem::CODEFORMAT format, udLanguage *lang, bool codemarks)
{
	wxString sCode;
	udCodeItem *pCode = NULL;
	
	if( action->IsKindOf(CLASSINFO(udCodeItem)) )
	{
		sCode = ((udCodeItem*)action)->ToString( format, lang);
		pCode = (udCodeItem*)action;
	}
	else if( action->IsKindOf(CLASSINFO(udCodeLinkItem)) )
	{
		sCode = ((udCodeLinkItem*)action)->ToString( format, lang);
		pCode = (udCodeItem*)((udCodeLinkItem*)action)->GetOriginal();
	}
	
	if( lang && codemarks && pCode->IsInline() )
	{
		lang->PushCode();
		int nIndent = lang->GetIndentation();
		lang->SetIndentation(0);
		
		lang->SingleLineCommentCmd( udGenerator::GetBeginCodeMark( pCode ) );
		lang->WriteCodeBlocks( sCode );
		lang->SingleLineCommentCmd( udGenerator::GetEndCodeMark( pCode ) );
		
		wxString sOut = lang->GetCodeBuffer();
		
		lang->PopCode();
		lang->SetIndentation(nIndent);
		
		return sOut;
	}
	else
		return sCode;
	
	
	/*if( action->IsKindOf(CLASSINFO(udCodeItem)) ) return ((udCodeItem*)action)->ToString( format, lang);
	else
		if( action->IsKindOf(CLASSINFO(udCodeLinkItem)) ) return ((udCodeLinkItem*)action)->ToString( format, lang);
	else
		return wxEmptyString;*/
}

void udTransElementItem::GetActionsAsStrings(udCodeItem::CODEFORMAT format, udLanguage *lang, bool codemarks, wxArrayString& actions)
{
	wxString sAction;
	SerializableList lstActions;
	
	GetActions( lstActions );
	
	for( SerializableList::iterator it = lstActions.begin(); it != lstActions.end(); ++it )
	{
		sAction = GetActionAsString( (udProjectItem*)*it, format, lang, codemarks);
		if( !sAction.IsEmpty() ) actions.Add( sAction );
	}
}

wxString udTransElementItem::GetActionsString()
{
	wxString sActs;
	udProjectItem *pAction;
	
	SerializableList lstActions;
	GetActions( lstActions );
	
	SerializableList::compatibility_iterator node = lstActions.GetFirst();
	while( node )
	{
		pAction = (udProjectItem*) node->GetData();
		
		sActs << GetActionAsString( pAction, udCodeItem::cfFORMAL, NULL, udfNO_CODEMARKS );
		
		node = node->GetNext();
		
		if( node ) sActs << wxT(", ");
	}

	return sActs;
}

void udTransElementItem::CopyActionItems(udTransElementItem *source)
{
	if( source )
	{
		SerializableList lstActions;
		source->GetActions( lstActions );
		
		SerializableList::compatibility_iterator node = lstActions.GetFirst();
		while( node )
		{
			AssignCodeItem( (udProjectItem*)node->GetData()->Clone() );
			node = node->GetNext();
		}
	}
}

void udTransElementItem::UpdateInnerContent()
{
	wxSFShapeBase *pParentShape = (wxSFShapeBase*)GetParent();
	if( pParentShape )
	{
		// update parent shape
		udLABEL::SetContent( GetGuardString(), pParentShape, udLABEL::ltGUARD_CONTENT );
		pParentShape->Update();
		
		// refresh canvas if displayed
		wxSFShapeCanvas *pCanvas = pParentShape->GetParentCanvas();
		if( pCanvas ) pCanvas->Refresh(false);
	}
}

// protected virtual functions //////////////////////////////////////////////////////

wxMenu* udTransElementItem::CreateMenu()
{	
	const wxString &sAppPath = IPluginManager::Get()->GetResourcesPath();
	
    // create popup menu
	wxMenu *pPopupMenu = new wxMenu();
	
	wxMenu *pCreateSubMenu = new wxMenu();
	
	wxMenuItem *pItem = new wxMenuItem(pCreateSubMenu, IDM_TRANS_CREATECONDITION, wxT("Condition function"));
	pItem->SetBitmap(IPluginManager::Get()->GetArtBitmap(wxT("udConditionItem")));
	pCreateSubMenu->Append(pItem);

	pItem = new wxMenuItem(pCreateSubMenu, IDM_TRANS_CREATEEVENT, wxT("Event flag"));
	pItem->SetBitmap(IPluginManager::Get()->GetArtBitmap(wxT("udEventItem")));
	pCreateSubMenu->Append(pItem);
	
	pItem = new wxMenuItem(pCreateSubMenu, IDM_TRANS_CREATEACTION, wxT("Action function"));
	pItem->SetBitmap(IPluginManager::Get()->GetArtBitmap(wxT("udActionItem")));
	pCreateSubMenu->Append(pItem);

    pPopupMenu->Append(wxID_ANY, wxT("Create"), pCreateSubMenu);
	
	// insert available conditions/events
	int nId = 0;
	wxMenu *pAssignSubMenu = new wxMenu();
	
	SerializableList lstItems;
	IPluginManager::Get()->GetProject()->GetItems(CLASSINFO(udConditionItem), lstItems);
	IPluginManager::Get()->GetProject()->GetItems(CLASSINFO(udEventItem), lstItems);
	SerializableList::compatibility_iterator node = lstItems.GetFirst();
	while(node)
	{
		pItem = new wxMenuItem(pAssignSubMenu, IDM_TRANS_ASSIGNGUARD + nId++, ((udProjectItem*)node->GetData())->GetName());
		pItem->SetBitmap(IPluginManager::Get()->GetArtBitmap(node->GetData()->GetClassInfo()->GetClassName()));
		pAssignSubMenu->Append(pItem);
		
		if( nId > udvMAX_ITEMS ) break;
		
		node = node->GetNext();
	}
	if( !lstItems.IsEmpty() ) pPopupMenu->Append(wxID_ANY, wxT("Assign condition/event"), pAssignSubMenu);
	
	// insert available actions
	nId = 0;
	pAssignSubMenu = new wxMenu();
	
	lstItems.Clear();
	IPluginManager::Get()->GetProject()->GetItems(CLASSINFO(udActionItem), lstItems);
	node = lstItems.GetFirst();
	while(node)
	{
		wxMenuItem *pItem = new wxMenuItem(pAssignSubMenu, IDM_TRANS_ASSIGNACTION + nId++, ((udProjectItem*)node->GetData())->GetName());
		pItem->SetBitmap(IPluginManager::Get()->GetArtBitmap(node->GetData()->GetClassInfo()->GetClassName()));
		pAssignSubMenu->Append(pItem);
		
		if( nId > udvMAX_ITEMS ) break;
		
		node = node->GetNext();
	}
	if( !lstItems.IsEmpty() ) pPopupMenu->Append(wxID_ANY, wxT("Assign action function"), pAssignSubMenu);
	
	pPopupMenu->AppendSeparator();
	
	if( HasChildren() )
	{
		nId = 0;
		wxMenu *pEditSubMenu = new wxMenu();
		// insert assigned code items
		lstItems.Clear();
		GetCodeItems(CLASSINFO(udCodeItem), lstItems);
		SerializableList::compatibility_iterator node = lstItems.GetFirst();
		while(node)
		{
			wxMenuItem *pItem = new wxMenuItem(pEditSubMenu, IDM_DELAYED_EDITCODE + nId++, ((udProjectItem*)node->GetData())->GetName());
			pItem->SetBitmap(IPluginManager::Get()->GetArtBitmap(node->GetData()->GetClassInfo()->GetClassName()));
			pEditSubMenu->Append(pItem);
		
			if( nId > udvMAX_ITEMS ) break;
		
			node = node->GetNext();
		}
		
		pPopupMenu->Append(wxID_ANY, wxT("Edit"), pEditSubMenu);
		pPopupMenu->AppendSeparator();
	}	
	
	pPopupMenu->Append(IDM_DIAG_CLEARCONDITIONS, wxT("Clear condition/event"));
	pPopupMenu->Append(IDM_DIAG_CLEARACTIONS, wxT("Clear action functions"));
	
	pPopupMenu->AppendSeparator();
	
	pItem = new wxMenuItem(pPopupMenu, wxID_COPY, wxT("Copy\tCtrl+C"));
	//pItem->SetBitmap(wxArtProvider::GetBitmap(wxART_COPY, wxART_MENU));
	pItem->SetBitmap(wxBitmap(sAppPath + wxT("app/gui/editcopy.png"), wxBITMAP_TYPE_PNG));
	pPopupMenu->Append(pItem);

	pItem = new wxMenuItem(pPopupMenu, IDM_DELAYED_CUTELEMENT, wxT("Cut\tCtrl+X"));
	//pItem->SetBitmap(wxArtProvider::GetBitmap(wxART_CUT, wxART_MENU));
	pItem->SetBitmap(wxBitmap(sAppPath + wxT("app/gui/editcut.png"), wxBITMAP_TYPE_PNG));
	pPopupMenu->Append(pItem);

	pPopupMenu->AppendSeparator();
    pPopupMenu->Append(IDM_DELAYED_EDITELEMENT, wxT("Edit properties..."), wxT("Edit diagram element"));
	pPopupMenu->AppendSeparator();
    pPopupMenu->Append(IDM_DELAYED_REMOVEELEMENT, wxT("Remove element"), wxT("Remove diagram element"));
	
	return pPopupMenu;
}

/////////////////////////////////////////////////////////////////////////////////////
// udCompositeStateItem /////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udCompStateElementItem, udDiagElementItem);

// constructor and destructor ///////////////////////////////////////////////////////

udCompStateElementItem::udCompStateElementItem()
{
	AcceptChild(wxT("udStateActionLinkItem"));
}

udCompStateElementItem::udCompStateElementItem(const udCompStateElementItem &obj)
: udDiagElementItem(obj)
{
}

udCompStateElementItem::~udCompStateElementItem()
{
}

// public functions /////////////////////////////////////////////////////////////////

void udCompStateElementItem::ClearActionItems(udStateActionLinkItem::TYPE type)
{
	udStateActionLinkItem *pAct;
	udProjectItem *pItem;
	
	IPluginManager::Get()->EnableInternalEvents(false);
	
	SerializableList::compatibility_iterator node = GetFirstChildNode();
	while( node ) 
	{	
		pItem = (udProjectItem*) node->GetData();
		pAct = wxDynamicCast( pItem, udStateActionLinkItem );
		
		// if the action matches given item type then remove the object from this state
		if( pAct && (pAct->GetActionType() == type) )
		{
			delete pItem;
			GetChildrenList().DeleteNode( node );
			
			node = GetFirstChildNode();
		}
		else
			node = node->GetNext();
	}
	
	IPluginManager::Get()->EnableInternalEvents(true);
}

void udCompStateElementItem::SetActionsString(const wxString& txt, udStateActionLinkItem::TYPE type)
{
	wxString sActs, sAct, sRegex = wxT("^.*/\\s*\\[[a-zA-Z0-9_\\(\\),\\s]*\\]\\s*$");
	wxRegEx reGuard( sRegex, wxRE_ADVANCED);
	
	if( reGuard.Matches( txt ) )
	{
		StoreCallParams();
		
		ClearActionItems( type );
		
		sActs = txt.AfterFirst( '/' );
			
		// parse action list
		sActs = sActs.AfterLast('[').BeforeFirst(']');
		
		// remove call parameters
		sActs = RemoveCallParams( sActs );
	
		wxStringTokenizer atokens( sActs, wxT(","), wxTOKEN_STRTOK );
		while ( atokens.HasMoreTokens() ) 
		{ 
			sAct = atokens.GetNextToken().Trim(true).Trim(false); 

			// try to find condition with similar name
			udActionItem *pAction = (udActionItem*) IPluginManager::Get()->GetProject()->GetProjectItem(CLASSINFO(udActionItem), sAct );
				
			// create a link to condition and assign it to this transition
			if( pAction )
			{
				AssignCodeItem( new udStateActionLinkItem(pAction, type) );
			}
			else
			{
				if( wxMessageBox( wxString::Format( wxT("Action with name '%s' doesn't exist yet. Would you like to create it?"), sAct.c_str() ), wxT("CodeDesigner"), wxYES_NO | wxICON_QUESTION  ) == wxYES )
				{
					udProjectItem *pRoot =  (udProjectItem*) IPluginManager::Get()->GetProject()->GetRootItem();
					// create new action
					udActionItem* pNewAct = (udActionItem*) IPluginManager::Get()->GetProject()->CreateProjectItem( wxT("udActionItem"), pRoot->GetId() );
					// create relevant tree item
					if( pNewAct )
					{
						pNewAct->SetName( sAct );
						// create link
						AssignCodeItem( new udStateActionLinkItem(pNewAct, type) );
							
						IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_ADDED, wxID_ANY, pNewAct, pRoot );
					}
				}
			}
		}
		
		RestoreCallParams();
	}
	else
		wxMessageBox( wxString::Format( wxT("State action '%s' doesn't match the allowed form '%s'."), txt.c_str(), sRegex.c_str() ), wxT("CodeDesigner"), wxOK | wxICON_WARNING );
}

wxString udCompStateElementItem::GetEntryActionsString()
{
	wxString sEntry;
	
	udStateActionLinkItem *pLink;
	SerializableList lstActions;
	GetCodeItems( CLASSINFO(udStateActionLinkItem), lstActions );
	
	SerializableList::compatibility_iterator node = lstActions.GetFirst();
	while( node )
	{
		pLink = (udStateActionLinkItem*) node->GetData();
		if( pLink->GetActionType() == udStateActionLinkItem::saENTRY )
		{
			if( !sEntry.IsEmpty() ) sEntry << wxT(", ");
			sEntry << pLink->ToString( udCodeItem::cfFORMAL, NULL );
		}
		
		node = node->GetNext();
	}
	
	return wxT("entry / [") + sEntry + wxT("]");
}

wxString udCompStateElementItem::GetExitActionsString()
{
	wxString sExit;
	
	udStateActionLinkItem *pLink;
	SerializableList lstActions;
	GetCodeItems( CLASSINFO(udStateActionLinkItem), lstActions );
	
	SerializableList::compatibility_iterator node = lstActions.GetFirst();
	while( node )
	{
		pLink = (udStateActionLinkItem*) node->GetData();
		if( pLink->GetActionType() == udStateActionLinkItem::saEXIT )
		{
			if( !sExit.IsEmpty() ) sExit << wxT(", ");
			sExit << pLink->ToString( udCodeItem::cfFORMAL, NULL );
		}
		
		node = node->GetNext();
	}
	
	return wxT("exit / [") + sExit + wxT("]");
}

// virtual functions ////////////////////////////////////////////////////////////////

wxMenu* udCompStateElementItem::CreateMenu()
{
	const wxString &sAppPath = IPluginManager::Get()->GetResourcesPath();
	
    // create popup menu
	wxMenu *pPopupMenu = new wxMenu();
	
	wxMenu *pCreateSubMenu = new wxMenu();
	
	wxMenuItem *pItem = new wxMenuItem(pCreateSubMenu, IDM_COMPSTATE_ACTION, wxT("Action function"));
	pItem->SetBitmap(IPluginManager::Get()->GetArtBitmap(wxT("udActionItem")));
	pCreateSubMenu->Append(pItem);

    pPopupMenu->Append(wxID_ANY, wxT("Create"), pCreateSubMenu);
	
	// insert available actions
	int nId = 0;
	wxMenu *pAssignSubMenu = new wxMenu();
	
	SerializableList lstItems;
	IPluginManager::Get()->GetProject()->GetItems(CLASSINFO(udActionItem), lstItems);
	SerializableList::compatibility_iterator node = lstItems.GetFirst();
	while(node)
	{
		wxMenuItem *pItem = new wxMenuItem(pAssignSubMenu, IDM_TRANS_ASSIGNACTION + nId++, ((udProjectItem*)node->GetData())->GetName());
		pItem->SetBitmap(IPluginManager::Get()->GetArtBitmap(node->GetData()->GetClassInfo()->GetClassName()));
		pAssignSubMenu->Append(pItem);
		
		if( nId > udvMAX_ITEMS ) break;
		
		node = node->GetNext();
	}
	if( !lstItems.IsEmpty() ) pPopupMenu->Append(wxID_ANY, wxT("Assign action function"), pAssignSubMenu);
	
	pPopupMenu->AppendSeparator();
	
	if( HasChildren() )
	{
		nId = 0;
		wxMenu *pEditSubMenu = new wxMenu();
		// insert assigned code items
		lstItems.Clear();
		GetCodeItems(CLASSINFO(udCodeItem), lstItems);
		SerializableList::compatibility_iterator node = lstItems.GetFirst();
		while(node)
		{
			wxMenuItem *pItem = new wxMenuItem(pEditSubMenu, IDM_DELAYED_EDITCODE + nId++, ((udProjectItem*)node->GetData())->GetName());
			pItem->SetBitmap(IPluginManager::Get()->GetArtBitmap(node->GetData()->GetClassInfo()->GetClassName()));
			pEditSubMenu->Append(pItem);
		
			if( nId > udvMAX_ITEMS ) break;
		
			node = node->GetNext();
		}
		
		pPopupMenu->Append(wxID_ANY, wxT("Edit"), pEditSubMenu);
		pPopupMenu->AppendSeparator();
	}	
	
	pPopupMenu->Append(IDM_DIAG_CLEARACTIONS, wxT("Clear action functions"));
	
	pPopupMenu->AppendSeparator();
	
	// create popup menu	
	pItem = new wxMenuItem(pPopupMenu, wxID_COPY, wxT("Copy\tCtrl+C"));
	//pItem->SetBitmap(wxArtProvider::GetBitmap(wxART_COPY, wxART_MENU));
	pItem->SetBitmap(wxBitmap(sAppPath + wxT("app/gui/editcopy.png"), wxBITMAP_TYPE_PNG));
	pPopupMenu->Append(pItem);

	pItem = new wxMenuItem(pPopupMenu, IDM_DELAYED_CUTELEMENT, wxT("Cut\tCtrl+X"));
	//pItem->SetBitmap(wxArtProvider::GetBitmap(wxART_CUT, wxART_MENU));
	pItem->SetBitmap(wxBitmap(sAppPath + wxT("app/gui/editcut.png"), wxBITMAP_TYPE_PNG));
	pPopupMenu->Append(pItem);

	pPopupMenu->AppendSeparator();
    pPopupMenu->Append(IDM_DELAYED_EDITELEMENT, wxT("Edit properties..."), wxT("Edit diagram element"));
	
	pPopupMenu->AppendSeparator();
    pPopupMenu->Append(IDM_DELAYED_REMOVEELEMENT, wxT("Remove element"), wxT("Remove diagram element"));
	
	return pPopupMenu;
}

void udCompStateElementItem::OnShapeTextChange(const wxString& txt, udLABEL::TYPE type, int id)
{
	switch( type )
	{
		case udLABEL::ltTITLE:
			udDiagElementItem::OnShapeTextChange( txt, type, id );
			break;
			
		case udLABEL::ltSTATE_ENTRYACTIONS:
			SetActionsString( txt, udStateActionLinkItem::saENTRY );
			break;
			
		case udLABEL::ltSTATE_EXITACTIONS:
			SetActionsString( txt, udStateActionLinkItem::saEXIT );
			break;
			
		default:
			break;
	}
}

void udCompStateElementItem::OnEditItem(wxWindow* parent)
{
	udCompStateDialog dlg( parent, this, IPluginManager::Get()->GetSelectedLanguage() );
	udWindowManager dlgman( dlg, wxT("comp_state_dialog") );
	
	dlg.SetCodeName( m_sName );
	dlg.SetDescription( m_sDescription );
	
	if( dlg.ShowModal() == wxID_OK )
	{
		m_sDescription = dlg.GetDescription();
		
		SetActionsString( wxT("entry / [") + dlg.GetEntryActionsString() + wxT("]"), udStateActionLinkItem::saENTRY );
		SetActionsString( wxT("exit / [") + dlg.GetExitActionsString() + wxT("]"), udStateActionLinkItem::saEXIT );

		OnTreeTextChange( dlg.GetCodeName() );
		
		IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, this );
	}
}

void udCompStateElementItem::UpdateInnerContent()
{	
	wxSFShapeBase *pParentShape = (wxSFShapeBase*)GetParent();
	if( pParentShape )
	{
		// update parent shape
		udLABEL::SetContent( GetEntryActionsString(), pParentShape, udLABEL::ltSTATE_ENTRYACTIONS );
		pParentShape->Update();
		
		udLABEL::SetContent( GetExitActionsString(), pParentShape, udLABEL::ltSTATE_EXITACTIONS );
		pParentShape->Update();
		
		// refresh canvas if displayed
		wxSFShapeCanvas *pCanvas = pParentShape->GetParentCanvas();
		if( pCanvas ) pCanvas->Refresh(false);
	}
}

/////////////////////////////////////////////////////////////////////////////////////
// udSimpleStateElement class////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udSimpleStateElementItem, udDiagElementItem);

/////////////////////////////////////////////////////////////////////////////////////
// udFinalElementItem class//////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udFinalElementItem, udDiagElementItem);

// constructor and destructor ///////////////////////////////////////////////////////

udFinalElementItem::udFinalElementItem()
{
	m_sRetVal = wxT("<default>");
	
	XS_SERIALIZE_EX( m_sRetVal, wxT("return_value"), wxT("<default>") );
}

udFinalElementItem::udFinalElementItem(const udFinalElementItem& obj) : udDiagElementItem(obj)
{
	m_sRetVal = obj.m_sRetVal;
	
	XS_SERIALIZE_EX( m_sRetVal, wxT("return_value"), wxT("<default>") );
}

udFinalElementItem::~udFinalElementItem()
{
}

// virtual functions ////////////////////////////////////////////////////////////////

void udFinalElementItem::OnEditItem(wxWindow* parent)
{
	udFinalStateDialog dlg( parent,  IPluginManager::Get()->GetSelectedLanguage() );
	udWindowManager dlgman( dlg, wxT("final_state_dialog") );
	
	dlg.SetCodeName( m_sName );
	dlg.SetDescription( m_sDescription );
	dlg.SetReturnValue( m_sRetVal );
	
	if( dlg.ShowModal() == wxID_OK )
	{
		m_sDescription = dlg.GetDescription();
		m_sRetVal = dlg.GetReturnValue();
		
		OnTreeTextChange( dlg.GetCodeName() );
	}
	
	IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, this );
	
/*	wxTextEntryDialog dlg(parent, wxT("Please enter return value:"), wxT("Edit final state properties"), m_sRetVal );

	if( dlg.ShowModal() == wxID_OK )
	{
		m_sRetVal = dlg.GetValue();
		
		UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, this );
	}*/
}

/////////////////////////////////////////////////////////////////////////////////////
// udInitialElementItem class////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udInitialElementItem, udDiagElementItem);

/////////////////////////////////////////////////////////////////////////////////////
// udDecisionElementItem class///////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udDecisionElementItem, udDiagElementItem);

/////////////////////////////////////////////////////////////////////////////////////
// udHistoryElementItem class////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udHistoryElementItem, udDiagElementItem);

/////////////////////////////////////////////////////////////////////////////////////
// udActionItem class ///////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udActionItem, udFunctionItem);

// constructor and destructor //////////////////////udFinalElementItem/////////////////////////////////

udActionItem::udActionItem()
{
	m_sName = wxT("Action");
	m_sDescription = wxT("Action's description...");
}

udActionItem::udActionItem(const udActionItem &obj)
: udFunctionItem(obj)
{
}

udActionItem::~udActionItem()
{
}

// virtual functions ////////////////////////////////////////////////////////////////

wxString udActionItem::ToString(CODEFORMAT format, udLanguage *lang)
{
	switch(format)
	{
		case cfCALL:
			if( m_fInline )	return m_sCode;
			else
				if( lang )	return udFunctionItem::ToString( format, lang ) + lang->Delimiter();
			else
				return udFunctionItem::ToString( format, lang );
			
		case cfFORMAL:
			/*return m_sName + wxT(" : Action");*/
			
		case cfDECLARATION:
		
		case cfDEFINITION:
			return udFunctionItem::ToString( format, lang );
			
		default:
			return m_sName;
	}
}

bool udActionItem::OnTreeItemBeginDrag(const wxPoint& pos)
{
	return DragCodeItem( new udActionLinkItem(this) );
}

void udActionItem::OnEditItem(wxWindow* parent)
{
	udFunctionDialog dlg( parent, this, IPluginManager::Get()->GetSelectedLanguage() );
	udWindowManager dlgman( dlg, wxT("action_dialog") );
	
	dlg.SetTitle( wxT("Action function properties") );
	
	dlg.SetCodeName( m_sName );
	dlg.SetCode( m_sCode );
	dlg.SetDescription( m_sDescription );
	dlg.SetDataType( m_nRetValDataType );
	dlg.SetDataModifier( m_nRetValModifier );
	dlg.SetFcnModifier( m_nFcnModifier );
	dlg.SetValueType( m_nRetValType );
	dlg.SetUserDataType( m_sUserRetValDataType );
	dlg.SetUserDeclaration( m_sUserRetValDecl );
	dlg.SetUserDeclFile( m_sUserRetValDeclFile );
	dlg.SetUserDeclPlace( m_nUserRetValDeclPlace );
	dlg.SetInline( m_fInline );
	dlg.SetImplementation( m_sImplementation );
	
	if( dlg.ShowModal() == wxID_OK )
	{
		m_sCode = dlg.GetCode();
		m_sDescription = dlg.GetDescription();
		m_nRetValDataType = dlg.GetDataType();
		m_nRetValType = dlg.GetValueType();
		m_nRetValModifier = dlg.GetDataModifier();
		m_nFcnModifier = dlg.GetFcnModifier();
		m_sUserRetValDataType = dlg.GetUserDataType();
		m_sUserRetValDecl = dlg.GetUserDeclaration();
		m_sUserRetValDeclFile = dlg.GetUserDeclFile();
		m_nUserRetValDeclPlace = dlg.GetUserDeclPlace();
		m_fInline = dlg.GetInline();
		m_sImplementation = dlg.GetImplementation();
		
		OnTreeTextChange( dlg.GetCodeName() );
	}
	
	IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, this );
}

/////////////////////////////////////////////////////////////////////////////////////
// udStateActionLinkItem class //////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udStateActionLinkItem, udActionLinkItem);

// constructor and destructor ///////////////////////////////////////////////////////

udStateActionLinkItem::udStateActionLinkItem()
{
	m_nActionType = saENTRY;
	
	m_arrAcceptedSibbling.Clear();
	AcceptSibbling(wxT("udStateActionLinkItem"));
	
	XS_SERIALIZE_INT( m_nActionType, wxT("action_type") );
}

udStateActionLinkItem::udStateActionLinkItem(const udCodeItem *orig, TYPE type)
{
	m_sName = orig->GetName();
	m_sOriginalCodeItem = orig->GetSignature();
	m_nActionType = type;
	
	m_arrAcceptedSibbling.Clear();
	AcceptSibbling(wxT("udStateActionLinkItem"));
	
	XS_SERIALIZE_INT( m_nActionType, wxT("action_type") );
}

udStateActionLinkItem::udStateActionLinkItem(const udStateActionLinkItem &obj)
: udActionLinkItem(obj)
{
	m_nActionType = obj.m_nActionType;
	
	XS_SERIALIZE_INT( m_nActionType, wxT("action_type") );
}

udStateActionLinkItem::~udStateActionLinkItem()
{
}

// virtual functions ////////////////////////////////////////////////////////////////

void udStateActionLinkItem::OnEditItem(wxWindow* parent)
{
	udActionLinkDialog dlg( parent, this, IPluginManager::Get()->GetSelectedLanguage() );
	udWindowManager dlgman( dlg, wxT("state_action_link_dialog") );
	
	dlg.SetCodeName( m_sName );
	dlg.SetActionType( (int) m_nActionType );
	
	if( dlg.ShowModal() == wxID_OK )
	{
		m_nActionType = (TYPE) dlg.GetActionType();
		
		OnTreeTextChange( dlg.GetCodeName() );
		
		IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, this );
	}
}

void udStateActionLinkItem::OnActivation()
{
	OnEditItem( IPluginManager::Get()->GetMainFrame() );	
}

/////////////////////////////////////////////////////////////////////////////////////
// udActionLinkItem class ///////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udActionLinkItem, udFunctionLinkItem);

/////////////////////////////////////////////////////////////////////////////////////
// udConditionItem class ////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udConditionItem, udFunctionItem);

// constructor and destructor ///////////////////////////////////////////////////////

udConditionItem::udConditionItem()
{
	m_sName = wxT("Condition");
	m_fInverted = false;
	
	m_nRetValDataType = udLanguage::DT_BOOL;

	m_sDescription = wxT("Condition's description...");
}

udConditionItem::udConditionItem(const udConditionItem &obj)
: udFunctionItem(obj)
{
}

udConditionItem::~udConditionItem()
{
}

// virtual functions ////////////////////////////////////////////////////////////////

wxString udConditionItem::ToString(CODEFORMAT format, udLanguage *lang)
{
	wxString sOut;
	
	switch( format )
	{
		case cfCALL:
			if( lang )
			{
				if( m_fInverted ) sOut << lang->Not() << wxT(" ( ");
					
				if( m_fInline )	sOut << m_sCode;
				else
					sOut << udFunctionItem::ToString( format, lang );
						
				if( m_fInverted ) sOut << wxT(" )");
			}
			else
			{
				if( m_fInverted ) sOut = wxT("'NOT' " );
				sOut << m_sName << wxT("()");
			}
			return sOut;
			
		case cfFORMAL:
			/*return m_sName + wxT(" : Condition");*/
			
		case cfDECLARATION:
		
		case cfDEFINITION:
			return udFunctionItem::ToString( format, lang );
		
		default:
			return m_sName;
	}
}

bool udConditionItem::OnTreeItemBeginDrag(const wxPoint& pos)
{
	return DragCodeItem( new udConditionLinkItem(this) );
}

void udConditionItem::OnEditItem(wxWindow* parent)
{
	udFunctionDialog dlg( parent, this, IPluginManager::Get()->GetSelectedLanguage() );
	udWindowManager dlgman( dlg, wxT("condition_dialog") );
	
	dlg.SetTitle( wxT("Conditional function properties") );
	
	dlg.SetCodeName( m_sName );
	dlg.SetCode( m_sCode );
	dlg.SetDescription( m_sDescription );
	dlg.SetDataType( m_nRetValDataType );
	dlg.SetDataModifier( m_nRetValModifier );
	dlg.SetFcnModifier( m_nFcnModifier );
	dlg.SetValueType( m_nRetValType );
	dlg.SetUserDataType( m_sUserRetValDataType );
	dlg.SetUserDeclaration( m_sUserRetValDecl );
	dlg.SetUserDeclFile( m_sUserRetValDeclFile );
	dlg.SetUserDeclPlace( m_nUserRetValDeclPlace );
	dlg.SetInline( m_fInline );
	dlg.SetImplementation( m_sImplementation );
	
	if( dlg.ShowModal() == wxID_OK )
	{
		m_sCode = dlg.GetCode();
		m_sDescription = dlg.GetDescription();
		m_nRetValDataType = dlg.GetDataType();
		m_nRetValType = dlg.GetValueType();
		m_nRetValModifier = dlg.GetDataModifier();
		m_nFcnModifier = dlg.GetFcnModifier();
		m_sUserRetValDataType = dlg.GetUserDataType();
		m_sUserRetValDecl = dlg.GetUserDeclaration();
		m_sUserRetValDeclFile = dlg.GetUserDeclFile();
		m_nUserRetValDeclPlace = dlg.GetUserDeclPlace();
		m_fInline = dlg.GetInline();
		m_sImplementation = dlg.GetImplementation();
		
		OnTreeTextChange( dlg.GetCodeName() );
	}
	
	IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, this );
}

/////////////////////////////////////////////////////////////////////////////////////
// udConditionLinkItem class ////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udConditionLinkItem, udFunctionLinkItem);

/////////////////////////////////////////////////////////////////////////////////////
// udEventItem class ////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udEventItem, udVariableItem);

// constructor and destructor ///////////////////////////////////////////////////////

udEventItem::udEventItem()
{
	m_sName = wxT("Event");
	m_sDescription = wxT("Event's description...");
	m_nType = etNORMAL;
	m_fInverted = false;
	
	m_nDataType = udLanguage::DT_UINT8;
	m_nDataModifier = udLanguage::DM_EXTERN;
	m_sValue = wxT("0");
	
	RemoveProperty( GetProperty(wxT("code")) );
	XS_SERIALIZE_INT( m_nType, wxT("evt_type") );
}

udEventItem::udEventItem(const udEventItem &obj)
: udVariableItem(obj)
{
	m_nType = obj.m_nType;
	m_fInverted = obj.m_fInverted;
	
	RemoveProperty( GetProperty(wxT("code")) );
	XS_SERIALIZE_INT( m_nType, wxT("evt_type") );
}

udEventItem::~udEventItem()
{
}

// virtual functions ////////////////////////////////////////////////////////////////

wxString udEventItem::ToString(CODEFORMAT format, udLanguage *lang)
{
	wxString sOut;
		
	switch( format )
	{
		case cfCALL:
			if( lang )	
			{
				if( m_fInverted ) sOut << lang->Not() << wxT(" ( ");
				sOut << udVariableItem::ToString( format, lang );
				if( m_fInverted ) sOut << wxT(" )");
			}
			else
			{
				if( m_fInverted ) sOut = wxT("'NOT'" );
				sOut << m_sName;
			}
			return sOut;
		
		case cfDECLARATION:
		case cfDEFINITION:	
			if( lang )
			{
				wxString sOut = udVariableItem::ToString( format, lang );
				bool fHasExtern = lang->GetModifierString( udLanguage::DM_EXTERN) != wxT("") && 
								  sOut.Contains( lang->GetModifierString( udLanguage::DM_EXTERN) );
								  
				if( fHasExtern ) {
					sOut.Replace( lang->GetModifierString( udLanguage::DM_EXTERN ), wxT("") );
					sOut.Trim(false);
				}
				sOut = lang->GetModifierString( udLanguage::DM_VOLATILE) + wxT(" ") + sOut;
				if( fHasExtern ) {
					sOut = lang->GetModifierString( udLanguage::DM_EXTERN) + wxT(" ") + sOut;
				}
				return sOut.Trim(false);
			}
			else
				return m_sName;
				
		case cfFORMAL:
			/*return m_sName + wxT(" : Event");*/
		
		/*case cfDEFINITION:
			return udVariableItem::ToString( format, lang );*/
		
		default:
			return m_sName;
	}
}

bool udEventItem::OnTreeItemBeginDrag(const wxPoint& pos)
{
	return DragCodeItem( new udEventLinkItem(this) );
}

void udEventItem::OnEditItem(wxWindow* parent)
{
	udVariableDialog dlg( parent, this, IPluginManager::Get()->GetSelectedLanguage() );
	udWindowManager dlgman( dlg, wxT("event_dialog") );
	
	dlg.SetTitle( wxT("Event flag properties") );
	
	dlg.SetCodeName( m_sName );
	dlg.SetDescription( m_sDescription );
	dlg.SetDataType( m_nDataType );
	dlg.SetDataModifier( m_nDataModifier );
	dlg.SetValueType( m_nValueType );
	dlg.SetDefaultValue( m_sValue );
	dlg.SetUserDeclaration( m_sUserDeclaration );
	dlg.SetUserDataType( m_sUserDataType );
	dlg.SetUserDeclFile( m_sUserDeclFile );
	dlg.SetUserDeclPlace( m_nUserDeclPlace );
	
	if( dlg.ShowModal() == wxID_OK )
	{
		m_sDescription = dlg.GetDescription();
		m_nDataType = dlg.GetDataType();
		m_nDataModifier = dlg.GetDataModifier();
		m_nValueType = dlg.GetValueType();
		m_sValue = dlg.GetDefaultValue();
		m_sUserDeclaration = dlg.GetUserDeclaration();
		m_sUserDataType = dlg.GetUserDataType();
		m_sUserDeclFile = dlg.GetUserDeclFile();
		m_nUserDeclPlace = dlg.GetUserDeclPlace();
		
		OnTreeTextChange( dlg.GetCodeName() );
		
		IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, this );
	}
	
	/*udEventDialog dlg( parent, wxGetApp().GetMainFrame()->GetSelectedLanguage() );
	
	dlg.SetCodeName( m_sName );
	dlg.SetEventType( m_nType );
	dlg.SetDescription( m_sDescription );
	
	if( dlg.ShowModal() == wxID_OK )
	{
		m_sDescription = dlg.GetDescription();
		m_nType = dlg.GetEventType();
		
		OnTreeTextChange( dlg.GetCodeName() );
		
		UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, this );
	}*/
}

/////////////////////////////////////////////////////////////////////////////////////
// udEventLinkItem class ////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udEventLinkItem, udVariableLinkItem);

void udEventLinkItem::OnEditItem(wxWindow* parent)
{
	udEventLinkDialog dlg( parent, wxDynamicCast( GetOriginal(), udCodeItem ), IPluginManager::Get()->GetSelectedLanguage() );
	udWindowManager dlgman( dlg, wxT("code_link_dialog") );
	
	dlg.SetCodeName( m_sName );
	dlg.SetClearFlag( m_fClearFlag );
	
	if( dlg.ShowModal() == wxID_OK )
	{
		OnTreeTextChange( dlg.GetCodeName() );
		m_fClearFlag = dlg.IsClearFlag();
		
		IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, this );
	}	
}

/////////////////////////////////////////////////////////////////////////////////////
// udSCHSubDiagramElementItem class /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udSCHSubDiagramElementItem, udSubDiagramElementItem);

udSCHSubDiagramElementItem::udSCHSubDiagramElementItem() : udSubDiagramElementItem()
{
    m_sName = wxT("SubDiagram");
	m_StoreRetVal = true;

	m_pSubDiagram = new udSStateChartDiagramItem();
	m_pSubDiagram->EnableSerialization(false);
	m_pSubDiagram->SetSubdiagramElement(this);

    XS_SERIALIZE_DYNAMIC_OBJECT_NO_CREATE(m_pSubDiagram, wxT("subdiagram"));
	XS_SERIALIZE_EX( m_StoreRetVal, wxT("store_ret_val"), true );
}

udSCHSubDiagramElementItem::udSCHSubDiagramElementItem(const udSCHSubDiagramElementItem& obj)
: udSubDiagramElementItem( obj )
{
	m_StoreRetVal = obj.m_StoreRetVal;
	
	XS_SERIALIZE_EX( m_StoreRetVal, wxT("store_ret_val"), true );
}

void udSCHSubDiagramElementItem::OnEditItem(wxWindow* parent)
{
	udSubStateDialog dlg( parent,  IPluginManager::Get()->GetSelectedLanguage() );
	udWindowManager dlgman( dlg, wxT("sub_state_dialog") );
	
	dlg.SetCodeName( m_sName );
	dlg.SetDescription( m_sDescription );
	dlg.SetStoreRetVal( m_StoreRetVal );
	
	if( dlg.ShowModal() == wxID_OK )
	{
		m_sDescription = dlg.GetDescription();
		m_StoreRetVal = dlg.GetStoreRetVal();
		
		OnTreeTextChange( dlg.GetCodeName() );
	}
	
	IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, this );
}

/////////////////////////////////////////////////////////////////////////////////////
// udHCHSubDiagramElementItem class /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udHCHSubDiagramElementItem, udSubDiagramElementItem);

udHCHSubDiagramElementItem::udHCHSubDiagramElementItem() : udSubDiagramElementItem()
{
    m_sName = wxT("SubDiagram");
	m_StoreRetVal = true;

	m_pSubDiagram = new udHStateChartDiagramItem();
	m_pSubDiagram->EnableSerialization(false);
	m_pSubDiagram->SetSubdiagramElement(this);

    XS_SERIALIZE_DYNAMIC_OBJECT_NO_CREATE(m_pSubDiagram, wxT("subdiagram"));
	XS_SERIALIZE_EX( m_StoreRetVal, wxT("store_ret_val"), true );
}

udHCHSubDiagramElementItem::udHCHSubDiagramElementItem(const udHCHSubDiagramElementItem& obj)
: udSubDiagramElementItem( obj )
{
	m_StoreRetVal = obj.m_StoreRetVal;
	
	XS_SERIALIZE_EX( m_StoreRetVal, wxT("store_ret_val"), true );
}

void udHCHSubDiagramElementItem::OnEditItem(wxWindow* parent)
{
	udSubStateDialog dlg( parent,  IPluginManager::Get()->GetSelectedLanguage() );
	udWindowManager dlgman( dlg, wxT("sub_state_dialog") );
	
	dlg.SetCodeName( m_sName );
	dlg.SetDescription( m_sDescription );
	dlg.SetStoreRetVal( m_StoreRetVal );
	
	if( dlg.ShowModal() == wxID_OK )
	{
		m_sDescription = dlg.GetDescription();
		m_StoreRetVal = dlg.GetStoreRetVal();
		
		OnTreeTextChange( dlg.GetCodeName() );
	}
	
	IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, this );
}

