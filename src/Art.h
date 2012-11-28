/***************************************************************
 * Name:      Art.h
 * Purpose:   Application artwork defines
 * Author:    Michal Bližňák (michal.bliznak@tiscali.cz)
 * Created:   2007-07-11
 * Copyright: Michal Bližňák ()
 * License:
 **************************************************************/

#ifndef ART_H_INCLUDED
#define ART_H_INCLUDED

#include <wx/hashmap.h>
#include <wx/bitmap.h>
#include <wx/imaglist.h>

WX_DECLARE_STRING_HASH_MAP( int, ImageMap );

class udArt
{
public:
	// static functions
	static void Initialize();
	static void CleanUp();
	
	static void AddArt(const wxString& icon, const wxString& classname);
	static void RemoveArt(const wxString& classname);
	
	static wxBitmap GetBitmap(const wxString& classname);
	static int GetImageIndex(const wxString& classname) {return m_mapImageIndexes[classname];}
	
	static wxImageList* GetImageList() {return m_lstImages;}
	

protected:
	// data members
	static int m_Index;
	static wxImageList *m_lstImages;
	static ImageMap m_mapImageIndexes;
};

#endif // ART_H_INCLUDED
