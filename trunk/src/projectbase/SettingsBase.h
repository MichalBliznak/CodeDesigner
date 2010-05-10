#ifndef _SETTINGS_BASE_H_
#define _SETTINGS_BASE_H_

#include <wx/filename.h>
#include <wx/wxsf/wxShapeFramework.h>

#include "interfaces/Defs.h"

// custom IO handlers ///////////////////////////////////////////////////////////////////

XS_DECLARE_EXPORTED_IO_HANDLER(wxFileName, xsFileNamePropIO, WXDLLIMPEXP_CD );
XS_DECLARE_EXPORTED_IO_HANDLER(wxFileName, xsDirNamePropIO, WXDLLIMPEXP_CD );

#define XS_SERIALIZE_FILE(x, name) XS_SERIALIZE_PROPERTY(x, wxT("filename"), name);
#define XS_SERIALIZE_DIR(x, name) XS_SERIALIZE_PROPERTY(x, wxT("dirname"), name);

// base classes /////////////////////////////////////////////////////////////////////////

class WXDLLIMPEXP_CD udSettingsCategory : public xsSerializable
{
public:
	DECLARE_DYNAMIC_CLASS(udSettingsCategory);
	
	udSettingsCategory();
	udSettingsCategory(const wxString& name);
	virtual ~udSettingsCategory();
	
	// public members accessors
	void SetName(const wxString& Name) {this->m_sName = Name;}
	const wxString& GetName() const {return m_sName;}
	
protected:
	// protected data members
	wxString m_sName;
};

class WXDLLIMPEXP_CD udHiddenCategory : public udSettingsCategory
{
public:
	DECLARE_DYNAMIC_CLASS(udHiddenCategory);
	
	udHiddenCategory();
	udHiddenCategory(const wxString& name);
	virtual ~udHiddenCategory();
};

class WXDLLIMPEXP_CD udSettings : public wxXmlSerializer
{
public:
	udSettings();
	virtual ~udSettings();
	
	// public functions
	xsProperty* GetProperty(const wxString& name);
	udSettingsCategory* GetCategory(const wxString& name);
	
	// data accessors
	wxString GetPropertyAsString(const wxString& name, const wxString& defval = wxEmptyString );
	
	virtual void CreateCategories()=0;
	virtual bool DeserializeFromXml(const wxString& file);
	virtual bool DeserializeFromXml(wxInputStream& instream);
};

#endif //_SETTINGS_BASE_H_
