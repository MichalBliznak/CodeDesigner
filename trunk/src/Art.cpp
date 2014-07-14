#include "wx_pch.h"

#ifdef _DEBUG_MSVC
#define new DEBUG_NEW
#endif

#include "Art.h"
#include "UMLDesignerMain.h"

// static class members /////////////////////////////////////////////////////////////

wxImageList *udArt::m_lstImages =  NULL;
ImageMap udArt::m_mapImageIndexes;
int udArt::m_Index = 0;

// public functions /////////////////////////////////////////////////////////////////

void udArt::Initialize()
{
	//int nIndex = 0;
	const wxString &sPath = wxGetApp().GetResourcesPath();
	
    // create image list
    m_lstImages = new wxImageList(16, 16, true);
		
    // static project images
    m_lstImages->Add(wxBitmap(sPath + wxT("app/project/cubes.png"), wxBITMAP_TYPE_PNG)); m_mapImageIndexes[wxT("udRootItem")] = m_Index++; //Root_xpm
    m_lstImages->Add(wxBitmap(sPath + wxT("app/project/cube_green.png"), wxBITMAP_TYPE_PNG)); m_mapImageIndexes[wxT("udPackageItem")] = m_Index++; //Folder_xpm
	m_lstImages->Add(wxBitmap(sPath + wxT("app/project/cube_yellow.png"), wxBITMAP_TYPE_PNG)); m_mapImageIndexes[wxT("udCodePackageItem")] = m_Index++; //Folder_code_xpm
	m_lstImages->Add(wxBitmap(sPath + wxT("app/project/Variable.xpm"), wxBITMAP_TYPE_XPM)); m_mapImageIndexes[wxT("udGenericVariableItem")] = m_Index++;
	m_lstImages->Add(wxBitmap(sPath + wxT("app/project/Variable_locked.xpm"), wxBITMAP_TYPE_XPM)); m_mapImageIndexes[wxT("udImpVariableItem")] = m_Index++;
	m_lstImages->Add(wxBitmap(sPath + wxT("app/project/Variable_link.xpm"), wxBITMAP_TYPE_XPM)); m_mapImageIndexes[wxT("udVariableLinkItem")] = m_Index++;
	m_lstImages->Add(wxBitmap(sPath + wxT("app/project/Function.xpm"), wxBITMAP_TYPE_XPM)); m_mapImageIndexes[wxT("udGenericFunctionItem")] = m_Index++;
	m_lstImages->Add(wxBitmap(sPath + wxT("app/project/Function_locked.xpm"), wxBITMAP_TYPE_XPM)); m_mapImageIndexes[wxT("udImpFunctionItem")] = m_Index++;
	m_lstImages->Add(wxBitmap(sPath + wxT("app/project/Function_link.xpm"), wxBITMAP_TYPE_XPM)); m_mapImageIndexes[wxT("udFunctionLinkItem")] = m_Index++;
	m_lstImages->Add(wxBitmap(sPath + wxT("app/project/Param.xpm"), wxBITMAP_TYPE_XPM)); m_mapImageIndexes[wxT("udParamItem")] = m_Index++;

	m_lstImages->Add(wxBitmap(sPath + wxT("app/elements/Tool.xpm"), wxBITMAP_TYPE_XPM)); m_mapImageIndexes[wxT("udICON_TOOL")] = m_Index++;
	
	//m_lstImages->Add(wxBitmap(sPath + wxT("gui/Preview.xpm"), wxBITMAP_TYPE_XPM)); m_mapImageIndexes[wxT("udICON_PREVIEW")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sPath + wxT("app/gui/Zoom100.xpm"), wxBITMAP_TYPE_XPM)); m_mapImageIndexes[wxT("udICON_ZOOM100")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sPath + wxT("app/gui/ZoomAll.xpm"), wxBITMAP_TYPE_XPM)); m_mapImageIndexes[wxT("udICON_ZOOMALL")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sPath + wxT("app/gui/Grid.xpm"), wxBITMAP_TYPE_XPM)); m_mapImageIndexes[wxT("udICON_GRID")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sPath + wxT("app/gui/AlignLeft.xpm"), wxBITMAP_TYPE_XPM)); m_mapImageIndexes[wxT("udICON_ALIGNLEFT")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sPath + wxT("app/gui/AlignRight.xpm"), wxBITMAP_TYPE_XPM)); m_mapImageIndexes[wxT("udICON_ALIGNRIGHT")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sPath + wxT("app/gui/AlignTop.xpm"), wxBITMAP_TYPE_XPM)); m_mapImageIndexes[wxT("udICON_ALIGNTOP")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sPath + wxT("app/gui/AlignBottom.xpm"), wxBITMAP_TYPE_XPM)); m_mapImageIndexes[wxT("udICON_ALIGNBOTTOM")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sPath + wxT("app/gui/AlignCenter.xpm"), wxBITMAP_TYPE_XPM)); m_mapImageIndexes[wxT("udICON_ALIGNCENTER")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sPath + wxT("app/gui/AlignMiddle.xpm"), wxBITMAP_TYPE_XPM)); m_mapImageIndexes[wxT("udICON_ALIGNMIDDLE")] = m_Index++; 
	
	m_lstImages->Add(wxBitmap(sPath + wxT("app/gui/AlignCircle.xpm"), wxBITMAP_TYPE_XPM)); m_mapImageIndexes[wxT("udICON_ALIGNCIRCLE")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sPath + wxT("app/gui/AlignMesh.xpm"), wxBITMAP_TYPE_XPM)); m_mapImageIndexes[wxT("udICON_ALIGNMESH")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sPath + wxT("app/gui/AlignVTree.xpm"), wxBITMAP_TYPE_XPM)); m_mapImageIndexes[wxT("udICON_ALIGNVTREE")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sPath + wxT("app/gui/AlignHTree.xpm"), wxBITMAP_TYPE_XPM)); m_mapImageIndexes[wxT("udICON_ALIGNHTREE")] = m_Index++; 
	//m_lstImages->Add(wxBitmap(sPath + wxT("gui/GenAll.xpm"), wxBITMAP_TYPE_XPM)); m_mapImageIndexes[wxT("udICON_GENALL")] = m_Index++; 
	
	m_lstImages->Add(wxBitmap(sPath + wxT("app/gui/filenew.png"), wxBITMAP_TYPE_PNG)); m_mapImageIndexes[wxT("udICON_FILENEW")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sPath + wxT("app/gui/fileopen.png"), wxBITMAP_TYPE_PNG)); m_mapImageIndexes[wxT("udICON_FILEOPEN")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sPath + wxT("app/gui/filesave.png"), wxBITMAP_TYPE_PNG)); m_mapImageIndexes[wxT("udICON_FILESAVE")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sPath + wxT("app/gui/filepreview.png"), wxBITMAP_TYPE_PNG)); m_mapImageIndexes[wxT("udICON_FILEPREVIEW")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sPath + wxT("app/gui/fileprint.png"), wxBITMAP_TYPE_PNG)); m_mapImageIndexes[wxT("udICON_FILEPRINT")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sPath + wxT("app/gui/editcopy.png"), wxBITMAP_TYPE_PNG)); m_mapImageIndexes[wxT("udICON_EDITCOPY")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sPath + wxT("app/gui/editcut.png"), wxBITMAP_TYPE_PNG)); m_mapImageIndexes[wxT("udICON_EDITCUT")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sPath + wxT("app/gui/editpaste.png"), wxBITMAP_TYPE_PNG)); m_mapImageIndexes[wxT("udICON_EDITPASTE")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sPath + wxT("app/gui/spellcheck.png"), wxBITMAP_TYPE_PNG)); m_mapImageIndexes[wxT("udICON_SPELLCHECK")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sPath + wxT("app/gui/actionrun.png"), wxBITMAP_TYPE_PNG)); m_mapImageIndexes[wxT("udICON_ACTIONRUN")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sPath + wxT("app/gui/undo.png"), wxBITMAP_TYPE_PNG)); m_mapImageIndexes[wxT("udICON_UNDO")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sPath + wxT("app/gui/redo.png"), wxBITMAP_TYPE_PNG)); m_mapImageIndexes[wxT("udICON_REDO")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sPath + wxT("app/gui/exit.png"), wxBITMAP_TYPE_PNG)); m_mapImageIndexes[wxT("udICON_EXIT")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sPath + wxT("app/gui/helpindex.png"), wxBITMAP_TYPE_PNG)); m_mapImageIndexes[wxT("udICON_HELPINDEX")] = m_Index++; 
	
    // insert diagrams' images
	PaletteArray *palette;
	PalettesMap::iterator it;

	for( it = m_mapElementPalettes.begin(); it != m_mapElementPalettes.end(); ++it )
    {
		palette = it->second;
		for( size_t i = 0; i < palette->GetCount(); i++)
		{
			if( m_mapImageIndexes.find(palette->Item(i).m_sClassName)==m_mapImageIndexes.end() )
			{
				m_lstImages->Add(wxBitmap(sPath + palette->Item(i).m_sIcon, wxBITMAP_TYPE_XPM));
				m_mapImageIndexes[palette->Item(i).m_sClassName] = m_Index++;
			}
		}
    }
}

void udArt::CleanUp()
{
	delete m_lstImages;
	m_mapImageIndexes.clear();
}

wxBitmap udArt::GetBitmap(const wxString& classname)
{
	if( m_lstImages && !classname.IsEmpty() )
	{
		return m_lstImages->GetBitmap( m_mapImageIndexes[classname] );
	}
	else
		return wxNullBitmap;
}

void udArt::AddArt(const wxString& icon, const wxString& classname)
{
	const wxString &sPath = wxGetApp().GetResourcesPath();
	
	wxBitmapType type = wxBITMAP_TYPE_ANY;
	
	if( icon.AfterLast('.').Lower() == wxT("xpm") ) type = wxBITMAP_TYPE_XPM;
	else if( icon.AfterLast('.').Lower() == wxT("png") ) type = wxBITMAP_TYPE_PNG;
	
	m_lstImages->Add( wxBitmap(sPath + icon, type)); m_mapImageIndexes[classname] = m_Index++; 
}

void udArt::RemoveArt(const wxString& classname)
{
	ImageMap::iterator it = m_mapImageIndexes.find(classname);
	if( it != m_mapImageIndexes.end() )
	{
		m_lstImages->Remove( it->second );
	}
}
