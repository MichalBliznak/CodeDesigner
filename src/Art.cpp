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
	const wxString &sAppPath = wxGetApp().GetPath();
	
    // create image list
    m_lstImages = new wxImageList(16, 16, true);
		
    // static project images
    m_lstImages->Add(wxBitmap(sAppPath + wxT("res/project/cubes.xpm"), wxBITMAP_TYPE_XPM)); m_mapImageIndexes[wxT("udRootItem")] = m_Index++; //Root_xpm
    m_lstImages->Add(wxBitmap(sAppPath + wxT("res/project/cube_green.xpm"), wxBITMAP_TYPE_XPM)); m_mapImageIndexes[wxT("udPackageItem")] = m_Index++; //Folder_xpm
	m_lstImages->Add(wxBitmap(sAppPath + wxT("res/project/cube_yellow.xpm"), wxBITMAP_TYPE_XPM)); m_mapImageIndexes[wxT("udCodePackageItem")] = m_Index++; //Folder_code_xpm
	m_lstImages->Add(wxBitmap(sAppPath + wxT("res/project/Variable.xpm"), wxBITMAP_TYPE_XPM)); m_mapImageIndexes[wxT("udGenericVariableItem")] = m_Index++;
	m_lstImages->Add(wxBitmap(sAppPath + wxT("res/project/Variable_locked.xpm"), wxBITMAP_TYPE_XPM)); m_mapImageIndexes[wxT("udImpVariableItem")] = m_Index++;
	m_lstImages->Add(wxBitmap(sAppPath + wxT("res/project/Variable_link.xpm"), wxBITMAP_TYPE_XPM)); m_mapImageIndexes[wxT("udVariableLinkItem")] = m_Index++;
	m_lstImages->Add(wxBitmap(sAppPath + wxT("res/project/Function.xpm"), wxBITMAP_TYPE_XPM)); m_mapImageIndexes[wxT("udGenericFunctionItem")] = m_Index++;
	m_lstImages->Add(wxBitmap(sAppPath + wxT("res/project/Function_locked.xpm"), wxBITMAP_TYPE_XPM)); m_mapImageIndexes[wxT("udImpFunctionItem")] = m_Index++;
	m_lstImages->Add(wxBitmap(sAppPath + wxT("res/project/Function_link.xpm"), wxBITMAP_TYPE_XPM)); m_mapImageIndexes[wxT("udFunctionLinkItem")] = m_Index++;
	m_lstImages->Add(wxBitmap(sAppPath + wxT("res/project/Param.xpm"), wxBITMAP_TYPE_XPM)); m_mapImageIndexes[wxT("udParamItem")] = m_Index++;

	m_lstImages->Add(wxBitmap(sAppPath + wxT("res/elements/Tool.xpm"), wxBITMAP_TYPE_XPM)); m_mapImageIndexes[wxT("udICON_TOOL")] = m_Index++;
	
	//m_lstImages->Add(wxBitmap(sAppPath + wxT("res/gui/Preview.xpm"), wxBITMAP_TYPE_XPM)); m_mapImageIndexes[wxT("udICON_PREVIEW")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sAppPath + wxT("res/gui/Zoom100.xpm"), wxBITMAP_TYPE_XPM)); m_mapImageIndexes[wxT("udICON_ZOOM100")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sAppPath + wxT("res/gui/ZoomAll.xpm"), wxBITMAP_TYPE_XPM)); m_mapImageIndexes[wxT("udICON_ZOOMALL")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sAppPath + wxT("res/gui/Grid.xpm"), wxBITMAP_TYPE_XPM)); m_mapImageIndexes[wxT("udICON_GRID")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sAppPath + wxT("res/gui/AlignLeft.xpm"), wxBITMAP_TYPE_XPM)); m_mapImageIndexes[wxT("udICON_ALIGNLEFT")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sAppPath + wxT("res/gui/AlignRight.xpm"), wxBITMAP_TYPE_XPM)); m_mapImageIndexes[wxT("udICON_ALIGNRIGHT")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sAppPath + wxT("res/gui/AlignTop.xpm"), wxBITMAP_TYPE_XPM)); m_mapImageIndexes[wxT("udICON_ALIGNTOP")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sAppPath + wxT("res/gui/AlignBottom.xpm"), wxBITMAP_TYPE_XPM)); m_mapImageIndexes[wxT("udICON_ALIGNBOTTOM")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sAppPath + wxT("res/gui/AlignCenter.xpm"), wxBITMAP_TYPE_XPM)); m_mapImageIndexes[wxT("udICON_ALIGNCENTER")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sAppPath + wxT("res/gui/AlignMiddle.xpm"), wxBITMAP_TYPE_XPM)); m_mapImageIndexes[wxT("udICON_ALIGNMIDDLE")] = m_Index++; 
	//m_lstImages->Add(wxBitmap(sAppPath + wxT("res/gui/GenAll.xpm"), wxBITMAP_TYPE_XPM)); m_mapImageIndexes[wxT("udICON_GENALL")] = m_Index++; 
	
	m_lstImages->Add(wxBitmap(sAppPath + wxT("res/gui/filenew.png"), wxBITMAP_TYPE_PNG)); m_mapImageIndexes[wxT("udICON_FILENEW")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sAppPath + wxT("res/gui/fileopen.png"), wxBITMAP_TYPE_PNG)); m_mapImageIndexes[wxT("udICON_FILEOPEN")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sAppPath + wxT("res/gui/filesave.png"), wxBITMAP_TYPE_PNG)); m_mapImageIndexes[wxT("udICON_FILESAVE")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sAppPath + wxT("res/gui/filepreview.png"), wxBITMAP_TYPE_PNG)); m_mapImageIndexes[wxT("udICON_FILEPREVIEW")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sAppPath + wxT("res/gui/fileprint.png"), wxBITMAP_TYPE_PNG)); m_mapImageIndexes[wxT("udICON_FILEPRINT")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sAppPath + wxT("res/gui/editcopy.png"), wxBITMAP_TYPE_PNG)); m_mapImageIndexes[wxT("udICON_EDITCOPY")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sAppPath + wxT("res/gui/editcut.png"), wxBITMAP_TYPE_PNG)); m_mapImageIndexes[wxT("udICON_EDITCUT")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sAppPath + wxT("res/gui/editpaste.png"), wxBITMAP_TYPE_PNG)); m_mapImageIndexes[wxT("udICON_EDITPASTE")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sAppPath + wxT("res/gui/spellcheck.png"), wxBITMAP_TYPE_PNG)); m_mapImageIndexes[wxT("udICON_SPELLCHECK")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sAppPath + wxT("res/gui/actionrun.png"), wxBITMAP_TYPE_PNG)); m_mapImageIndexes[wxT("udICON_ACTIONRUN")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sAppPath + wxT("res/gui/undo.png"), wxBITMAP_TYPE_PNG)); m_mapImageIndexes[wxT("udICON_UNDO")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sAppPath + wxT("res/gui/redo.png"), wxBITMAP_TYPE_PNG)); m_mapImageIndexes[wxT("udICON_REDO")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sAppPath + wxT("res/gui/exit.png"), wxBITMAP_TYPE_PNG)); m_mapImageIndexes[wxT("udICON_EXIT")] = m_Index++; 
	m_lstImages->Add(wxBitmap(sAppPath + wxT("res/gui/helpindex.png"), wxBITMAP_TYPE_PNG)); m_mapImageIndexes[wxT("udICON_HELPINDEX")] = m_Index++; 
	
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
				m_lstImages->Add(wxBitmap(sAppPath + palette->Item(i).m_sIcon, wxBITMAP_TYPE_XPM));
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
	const wxString &sAppPath = wxGetApp().GetPath();
	
	wxBitmapType type = wxBITMAP_TYPE_ANY;
	
	if( icon.AfterLast('.').Lower() == wxT("xpm") ) type = wxBITMAP_TYPE_XPM;
	else if( icon.AfterLast('.').Lower() == wxT("png") ) type = wxBITMAP_TYPE_PNG;
	
	m_lstImages->Add( wxBitmap(sAppPath + icon, type)); m_mapImageIndexes[classname] = m_Index++; 
}

void udArt::RemoveArt(const wxString& classname)
{
	ImageMap::iterator it = m_mapImageIndexes.find(classname);
	if( it != m_mapImageIndexes.end() )
	{
		m_lstImages->Remove( it->second );
	}
}
