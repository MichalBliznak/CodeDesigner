#include "FrameBase.h"
#include "ProjectBase.h"

#include <wx/arrimpl.cpp>

WX_DEFINE_OBJARRAY(PaletteArray);

// global static objects
PalettesMap m_mapElementPalettes;

udPaletteItem* GetPaletteTool(const wxString& className)
{
	PaletteArray *palette;
	PalettesMap::iterator it = m_mapElementPalettes.begin();

	for( it = m_mapElementPalettes.begin(); it != m_mapElementPalettes.end(); it++ )
    {
		palette = it->second;
		for( size_t i = 0; i < palette->GetCount(); i++)
		{
			if( palette->Item(i).m_sClassName == className ) return &palette->Item(i);
		}
    }

	return NULL;
}

udPaletteItem* GetPaletteTool(int id)
{
	PaletteArray *palette;
	PalettesMap::iterator it = m_mapElementPalettes.begin();

	for( it = m_mapElementPalettes.begin(); it != m_mapElementPalettes.end(); it++ )
    {
		palette = it->second;
		for( size_t i = 0; i < palette->GetCount(); i++)
		{
			if( palette->Item(i).m_nId == id ) return &palette->Item(i);
		}
    }

	return NULL;
}

// udWindowManager class ///////////////////////////////////////////////////////

udWindowManager::udWindowManager( wxWindow& wnd, const wxString& wndname)
{
	m_ManagedWindow = &wnd;
	m_Name = wndname;
	
	// try to find record for given window name
	udWindowRecord *pRec = GetRecord( m_Name );
	if( pRec )
	{
		// update window position and size
		m_ManagedWindow->Move( pRec->GetPosition() );
		m_ManagedWindow->SetSize( pRec->GetSize() );
		m_ManagedWindow->Update();
	}
}

udWindowManager::~udWindowManager()
{
	// store information about managed window:
	
	// try to find record for given window name
	udWindowRecord *pRec = GetRecord( m_Name );
	
	// if not exists then create a new one and add it to hidden gui settings category
	if( !pRec )
	{
		pRec = new udWindowRecord( m_Name );
		
		udSettings& AppSettings = IPluginManager::Get()->GetAppSettings();
		
		udSettingsCategory *pGUICat = AppSettings.GetCategory( wxT("Hidden GUI category") );
		if( pGUICat )
		{
			pGUICat->AddChild( pRec );
		}
	}
	
	// update record content
	pRec->SetPosition( m_ManagedWindow->GetPosition() );
	pRec->SetSize( m_ManagedWindow->GetSize() );
}

udWindowRecord* udWindowManager::GetRecord(const wxString& wndname)
{
	udSettings& AppSettings = IPluginManager::Get()->GetAppSettings();
	
	udSettingsCategory *pGUICat = AppSettings.GetCategory( wxT("Hidden GUI category") );
	if( pGUICat )
	{
		udWindowRecord *pRec = (udWindowRecord*) pGUICat->GetFirstChild( CLASSINFO(udWindowRecord) );
		while( pRec )
		{
			if( pRec->GetName() == wndname ) return pRec;
			pRec = (udWindowRecord*) pRec->GetSibbling( CLASSINFO(udWindowRecord) );
		}
	}
	
	return NULL;
}

void udWindowManager::Clear()
{
	// clear all current records
	udSettings& AppSettings = IPluginManager::Get()->GetAppSettings();
	
	udSettingsCategory *pGUICat = AppSettings.GetCategory( wxT("Hidden GUI category") );
	if( pGUICat )
	{
		udWindowRecord *pRec;
		while( (pRec = (udWindowRecord*) pGUICat->GetFirstChild( CLASSINFO(udWindowRecord) )) )
		{
			AppSettings.RemoveItem( pRec );
		}
	}
}

// udWindowRecord class ////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC_CLASS(udWindowRecord, xsSerializable);

udWindowRecord::udWindowRecord(const wxString& name)
{
	m_Name = name;
	m_Position = wxDefaultPosition;
	m_Size = wxDefaultSize;
	
	XS_SERIALIZE( m_Name, wxT("name") );
	XS_SERIALIZE( m_Position, wxT("position") );
	XS_SERIALIZE( m_Size, wxT("size") );
}

udWindowRecord::udWindowRecord()
{
	m_Name = wxT("<unknown>");
	m_Position = wxDefaultPosition;
	m_Size = wxDefaultSize;
	
	XS_SERIALIZE( m_Name, wxT("name") );
	XS_SERIALIZE( m_Position, wxT("position") );
	XS_SERIALIZE( m_Size, wxT("size") );
}
