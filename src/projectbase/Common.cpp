#include "Common.h"
#include "FrameBase.h"
#include "ProjectBase.h"

#include "codegen/Generator.h"

#include <wx/regex.h>

namespace udLABEL
{
	void SetContent(const wxString& name, wxSFShapeBase *element, TYPE type)
	{
		wxASSERT( element );
		if( !element ) return;
		
		uddLabelElement *pLabel;

		SerializableList lstChildren;
		element->GetChildrenRecursively( CLASSINFO( uddLabelElement ), lstChildren );
		SerializableList::compatibility_iterator node = lstChildren.GetFirst();

		while( node )
		{
			pLabel = (uddLabelElement*)node->GetData();
			if( pLabel && (pLabel->GetLabelType() == type) )
			{
				pLabel->SetText( name );
				pLabel->Update();
				break;
			}

			node = node->GetNext();
		}

		element->Update();
	}
	
	void SetContent(const wxString& name, wxSFShapeBase *element, wxXmlSerializer *manager, TYPE type)
	{
		wxASSERT( element );
		wxASSERT( manager );
		if( !element || !manager) return;
		
		SerializableList lstChildren;
		element->GetChildrenRecursively( CLASSINFO( uddLabelElement ), lstChildren );
		SerializableList::compatibility_iterator node = lstChildren.GetFirst();
		while( node )
		{
			uddLabelElement *pLabel = (uddLabelElement*)node->GetData();
			if( pLabel && (pLabel->GetLabelType() == type) )
			{
				wxXmlSerializer *pPrevManager = pLabel->GetParentManager();
				pLabel->SetParentManager( manager );

				pLabel->SetText( name );
				pLabel->Update();

				pLabel->SetParentManager( pPrevManager );
				break;
			}

			node = node->GetNext();
		}

		element->Update();
	}
	
	wxString GetContent(wxSFShapeBase *element, TYPE type)
	{
		uddLabelElement *pLabel;

		SerializableList lstChildren;
		element->GetChildrenRecursively( CLASSINFO( uddLabelElement ), lstChildren );
		SerializableList::compatibility_iterator node = lstChildren.GetFirst();
		while( node )
		{
			pLabel = (uddLabelElement*)node->GetData();
			if( pLabel && (pLabel->GetLabelType() == type) ) return pLabel->GetText();

			node = node->GetNext();
		}

		return wxT("");
	}
	
	void GetQuantity(wxSFShapeBase* element, TYPE type, long* min, long* max)
	{
		wxString sContent = GetContent(element, type);
		if( !sContent.IsEmpty() )
		{
			sContent.Replace( wxT(" "), wxT("") );
			
			wxRegEx regPattern;
			
			// 1
			regPattern.Compile( wxT("^[0-9]*$"), wxRE_ADVANCED );
			if( regPattern.Matches( sContent ) )
			{
				sContent.ToLong( min );
				*max = *min;
				return;
			}
			
			// 1..2
			regPattern.Compile( wxT("^[0-9]*..[0-9]*$"), wxRE_ADVANCED );
			if( regPattern.Matches( sContent ) )
			{
				sContent.BeforeFirst('.').ToLong( min );
				sContent.AfterLast('.').ToLong( max );
				return;
			}
			
			// 0..*
			regPattern.Compile( wxT("^[0-9]*..\\*$"), wxRE_ADVANCED );
			if( regPattern.Matches( sContent ) )
			{
				sContent.BeforeFirst('.').ToLong( min );
				*max = -1;
				return;
			}
			
			*min = -1;
			*max = -1;
		}
	}
}
	
////////////////////////////////////////////////////////////////////////////////

namespace udPROJECT
{
	udDiagramItem* GetParentDiagram(udProjectItem *element)
	{
		wxASSERT(element);
		
		if( element )
		{
			wxSFShapeBase *pParentShape = wxDynamicCast( element->GetParent(), wxSFShapeBase );
			if( pParentShape )
			{
				udDiagramManager *pManager = wxDynamicCast( pParentShape->GetParentManager(), udDiagramManager );
				if( pManager ) return (udDiagramItem*) pManager->GetParentProjItem();
			}
		}
		return NULL;
	}
	
	wxSFShapeBase* GetParentElement(wxSFShapeBase *child)
	{
		wxSFShapeBase *pParent = child;
		while( pParent && (GetPaletteTool(pParent->GetClassInfo()->GetClassName()) == NULL) )
		{
			pParent = pParent->GetParentShape();
		}
		return pParent;
	}
	
	udGenerator* CreateGenerator(udDiagramItem *diag)
	{
		udDiagramItem *pDiag = udPROJECT::GetSuperDiagram(diag);
		if(pDiag)
		{
			udGenerator *pGen = (udGenerator*)wxCreateDynamicObject(pDiag->GetActiveGenerator());

			if( pGen )
			{
				// set the default algorithm (it may be changed in generator later)
				pGen->SetActiveAlgorithm(pGen->GetAlgorithms()[pDiag->GetActiveAlgorithm()]);
				return pGen;
			}
		}
		return NULL;
	}
	
	udGenerator* CreateGenerator(const wxString& name)
	{
		udGeneratorInfo* info = IPluginManager::Get()->FindGeneratorInfoByName( name );
		if( info )
		{
			udGenerator *pGen = (udGenerator*)wxCreateDynamicObject( info->GetClassName() );
			if( pGen )
			{
				return pGen;
			}
		}
		return NULL;
	}
	
	udDiagElementItem* GetDiagramElement(wxSFShapeBase *shape, bool omitlinks)
	{
		if( !shape ) return NULL;

		udProjectItem *pElement = wxDynamicCast( shape->GetUserData(), udProjectItem );
		if( pElement && pElement->IsKindOf( CLASSINFO( udElementLinkItem ) ) )
		{
			if( !omitlinks ) return (udDiagElementItem*)((udElementLinkItem*)pElement)->GetOriginal();
			else
				return NULL;
		}
		return (udDiagElementItem*)pElement;
	}

	udDiagElementItem* GetDiagramElement(udDiagramItem *diagram, const wxString& name)
	{
		wxASSERT(diagram);
		if(!diagram)return NULL;

		udDiagElementItem *pElement;
		SerializableList lstElements;
		GetDiagramElements(diagram, CLASSINFO(udDiagElementItem), lstElements, sfNORECURSIVE);

		SerializableList::compatibility_iterator node = lstElements.GetFirst();
		while(node)
		{
			pElement = (udDiagElementItem*)node->GetData();
			if( pElement && (pElement->GetName() == name) ) return pElement;

			node = node->GetNext();
		}

		return NULL;
	}
	
	udDiagramItem* GetSuperDiagram(udDiagramItem *child)
	{
		if( child  )
		{
			if( child->GetSubdiagramElement() )
			{
				// get element shape
				wxSFShapeBase *pShape = (wxSFShapeBase*)child->GetSubdiagramElement()->GetParent();
				// get parent diagram
				return GetSuperDiagram( (udDiagramItem*)((udDiagramManager*)pShape->GetParentManager())->GetParentProjItem() );
			}
			else
				return child;
		}
		else
			return NULL;
	}
	
	void GetSubDiagrams(udDiagramItem* parent, wxClassInfo *type, SerializableList& subdiagrams)
	{
		udDiagramItem *pDiagram;
		SerializableList lstSubDiagElements;
		
		udPROJECT::GetDiagramElements(parent, CLASSINFO(udSubDiagramElementItem), lstSubDiagElements, sfRECURSIVE);

		SerializableList::compatibility_iterator snode = lstSubDiagElements.GetFirst();
		while(snode)
		{
			pDiagram = ((udSubDiagramElementItem*) snode->GetData())->GetSubDiagram();
			if( !type || pDiagram->IsKindOf( type ) ) subdiagrams.Append( pDiagram );
			snode = snode->GetNext();
		}
	}
	
	udProjectItem* GetProjectItem(udProjectItem* parent, wxClassInfo* type, const wxString& name)
	{				
		if( parent )
		{
			udProjectItem *pChild;
			
			SerializableList::compatibility_iterator node = parent->GetFirstChildNode();
			while( node )
			{
				pChild = (udProjectItem*)node->GetData();
				
				if( pChild->IsKindOf( type ) && (pChild->GetName() == name) ) return (udProjectItem*)node->GetData();
				node = node->GetNext();
			}
		}
		return NULL;
	}
	
	void GetDiagramElements(udDiagramItem* diagram, wxClassInfo* type, SerializableList& elements, bool recursive)
	{
		udProjectItem *pElementItem;
		ShapeList lstDiagItems;

		diagram->GetDiagramManager().GetShapes(CLASSINFO(wxSFShapeBase), lstDiagItems);
		ShapeList::compatibility_iterator snode = lstDiagItems.GetFirst();
		while(snode)
		{
			pElementItem = (udProjectItem*)snode->GetData()->GetUserData();
			if( pElementItem )
			{
				if( pElementItem->IsKindOf( type ) ) elements.Append( pElementItem );

				if( recursive && pElementItem->IsKindOf(CLASSINFO(udSubDiagramElementItem)) )
				{
					GetDiagramElements(((udSubDiagramElementItem*)pElementItem)->GetSubDiagram(), type, elements, recursive);
				}
			}

			snode = snode->GetNext();
		}
	}
	
	void FindCodeReferences(const wxString& pattern, SerializableList& references)
	{
		SerializableList lstCodeItems;
		IPluginManager::Get()->GetProject()->GetItems( CLASSINFO(udCodeItem), lstCodeItems );
		
//		wxRegEx rePattern( wxT("^") + pattern + wxT("[\\s]+|") +
//						   wxT("[\\s]+") + pattern + wxT("[\\s]+|") + 
//						   wxT("[\\s]+") + pattern + wxT("$"), wxRE_ADVANCED );

		wxRegEx rePattern( pattern, wxRE_ADVANCED );
		
		for( SerializableList::iterator it = lstCodeItems.begin(); it != lstCodeItems.end(); ++it )
		{
			udCodeItem *pItem = (udCodeItem*)*it;
			
			if( rePattern.Matches( pItem->GetCode() ) )
			{
				references.Append( *it );
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////

namespace udFRAME
{
	void FillGeneratorsChoice(wxChoice *choice, udLanguage *lang, udDiagramItem *diag)
	{
		choice->Clear();

		udGenerator *pGen;
		int diagIndex = 0, counter = 0;

		if(!diag || !lang)return;

		// iterate through all code generators supported by given diagram and selected language
		GeneratorsArray& arrGens = IPluginManager::Get()->GetGenerators();
		
		for( size_t i = 0; i < arrGens.GetCount(); i++ )
		{
			if( arrGens[i].GetDiagramClassName() == diag->GetClassInfo()->GetClassName() )
			{
				pGen = (udGenerator*)wxCreateDynamicObject(arrGens[i].GetClassName());
				if(pGen)
				{
					AlgorithmMap::iterator it = pGen->GetAlgorithms().begin();
					while(it != pGen->GetAlgorithms().end())
					{
						if(it->second->GetSupportedLanguages().Index(lang->GetClassInfo()->GetClassName())!=wxNOT_FOUND)
						{
							choice->Append( arrGens[i].GetDescription() );
							if(pGen->GetClassInfo()->GetClassName() == diag->GetActiveGenerator())diagIndex = counter;
							counter++;
							break;
						}
						it++;
					}
					delete pGen;
				}
			}
		}

		choice->SetSelection(diagIndex);
	}

	void FillAlgorithmsChoice(wxChoice *choice, udLanguage *lang, udDiagramItem *diag, udGenerator *gen)
	{
		choice->Clear();

		if(!gen || !diag || !lang)return;

		int algIndex = 0, counter = 0;

		for( AlgorithmMap::iterator it = gen->GetAlgorithms().begin(); it != gen->GetAlgorithms().end(); ++it )
		{
			if(it->second->GetSupportedLanguages().Index(lang->GetClassInfo()->GetClassName())!=wxNOT_FOUND)
			{
				choice->Append(it->second->GetName());
				if(it->second->GetClassInfo()->GetClassName() == diag->GetActiveAlgorithm())algIndex = counter;
				counter++;
			}
		}

		choice->SetSelection(algIndex);
	}
	
	void InitStyledTextCtrl(wxStyledTextCtrl *sci, udLanguage *lang)
	{
		udSettings &Settings = IPluginManager::Get()->GetAppSettings();

		sci->SetLexer(lang->GetStcLanguageType());
		sci->SetKeyWords(0, lang->GetStcLanguageKeywords());
		sci->StyleSetFont( wxSTC_STYLE_DEFAULT, Settings.GetProperty( wxT("Editor font") )->AsFont() );
		sci->StyleSetBold( wxSTC_C_WORD, true );
		sci->StyleSetForeground( wxSTC_C_WORD, *wxBLUE );
		sci->StyleSetForeground( wxSTC_C_STRING, *wxRED );
		sci->StyleSetForeground( wxSTC_C_STRINGEOL, *wxRED );
		sci->StyleSetForeground( wxSTC_C_PREPROCESSOR, wxColour( 49, 106, 197 ) );
		sci->StyleSetForeground( wxSTC_C_COMMENT, wxColour( 0, 128, 0 ) );
		sci->StyleSetForeground( wxSTC_C_COMMENTLINE, wxColour( 0, 128, 0 ) );
		sci->StyleSetForeground( wxSTC_C_COMMENTDOC, wxColour( 0, 128, 0 ) );
		sci->StyleSetForeground( wxSTC_C_COMMENTLINEDOC, wxColour( 0, 128, 0 ) );
		sci->StyleSetForeground( wxSTC_C_NUMBER, *wxBLUE );
		/*sci->SetUseTabs( true );
		sci->SetTabWidth( (int)lang->GetIndentString().Len() );
		sci->SetTabIndents( true );
		sci->SetBackSpaceUnIndents( true );
		sci->SetIndent( (int)lang->GetIndentString().Len() );*/
		sci->SetSelBackground( true, wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHT ) );
		sci->SetSelForeground( true, wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHTTEXT ) );

		sci->SetCaretWidth( 2 );
		
		sci->SetMarginType( 1, wxSTC_MARGIN_SYMBOL );
		sci->SetMarginMask( 1, wxSTC_MASK_FOLDERS );
		sci->SetMarginWidth( 1, 16);
		sci->SetMarginSensitive( 1, true );
		sci->SetProperty( wxT("fold"), wxT("1") );
		sci->SetFoldFlags( wxSTC_FOLDFLAG_LINEBEFORE_CONTRACTED | wxSTC_FOLDFLAG_LINEAFTER_CONTRACTED );
		sci->SetMarginType( 0, wxSTC_MARGIN_NUMBER );
		
		sci->SetTabIndents(true);
		sci->SetBackSpaceUnIndents(true);
		sci->SetUseTabs( Settings.GetProperty( wxT("Use tabulators") )->AsBool() );
		sci->SetTabWidth( Settings.GetProperty( wxT("Tabulator width") )->AsInt() );
		sci->SetIndent( Settings.GetProperty( wxT("Indentation width") )->AsInt() );

		// markers
		sci->MarkerDefine(wxSTC_MARKNUM_FOLDER,        wxSTC_MARK_BOXPLUS);
		sci->MarkerSetBackground( wxSTC_MARKNUM_FOLDER, wxColour( wxT("DARK GREY") ) );
		sci->MarkerSetForeground( wxSTC_MARKNUM_FOLDER, wxColour( wxT("WHITE") ) );
		
		sci->MarkerDefine(wxSTC_MARKNUM_FOLDEROPEN,    wxSTC_MARK_BOXMINUS);
		sci->MarkerSetBackground( wxSTC_MARKNUM_FOLDEROPEN, wxColour( wxT("DARK GREY") ) );
		sci->MarkerSetForeground( wxSTC_MARKNUM_FOLDEROPEN, wxColour( wxT("WHITE") ) );
		
		sci->MarkerDefine(wxSTC_MARKNUM_FOLDERSUB,     wxSTC_MARK_VLINE);
		sci->MarkerSetBackground( wxSTC_MARKNUM_FOLDERSUB, wxColour( wxT("DARK GREY") ) );
		sci->MarkerSetForeground( wxSTC_MARKNUM_FOLDERSUB, wxColour( wxT("WHITE") ) );
		
		sci->MarkerDefine(wxSTC_MARKNUM_FOLDEREND,     wxSTC_MARK_EMPTY);
		sci->MarkerSetBackground( wxSTC_MARKNUM_FOLDEREND, wxColour( wxT("DARK GREY") ) );
		sci->MarkerSetForeground( wxSTC_MARKNUM_FOLDEREND, wxColour( wxT("WHITE") ) );
		
		sci->MarkerDefine(wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_BOXMINUS);
		sci->MarkerSetBackground( wxSTC_MARKNUM_FOLDEROPENMID, wxColour( wxT("DARK GREY") ) );
		sci->MarkerSetForeground( wxSTC_MARKNUM_FOLDEROPENMID, wxColour( wxT("WHITE") ) );

		sci->MarkerDefine(wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_TCORNER);
		sci->MarkerSetBackground( wxSTC_MARKNUM_FOLDERMIDTAIL, wxColour( wxT("DARK GREY") ) );
		sci->MarkerSetForeground( wxSTC_MARKNUM_FOLDERMIDTAIL, wxColour( wxT("WHITE") ) );
		
		sci->MarkerDefine(wxSTC_MARKNUM_FOLDERTAIL,    wxSTC_MARK_LCORNER);
		sci->MarkerSetBackground( wxSTC_MARKNUM_FOLDERTAIL, wxColour( wxT("DARK GREY") ) );
		sci->MarkerSetForeground( wxSTC_MARKNUM_FOLDERTAIL, wxColour( wxT("WHITE") ) );
		
		sci->SetFoldFlags( wxSTC_FOLDFLAG_LINEAFTER_CONTRACTED );
	}
	
	wxColour GetBcgColour()
	{
		#ifdef __WXGTK__
		wxVisualAttributes attribs = wxToolBar::GetClassDefaultAttributes();
		return attribs.colBg;
		#else
		return wxSystemSettings::GetColour( wxSYS_COLOUR_3DFACE );
		#endif
	}
}
