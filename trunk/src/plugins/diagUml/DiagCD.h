#ifndef _DIAG_CD_H_
#define _DIAG_CD_H_

#include "projectbase/ProjectBase.h"

#define udnCLASS_DIAGRAM wxT("Class Diagram")

// Class Diagram code items classes /////////////////////////////////////////////////////////////

// project components /////////////////////////////////////////////////////////////

class WXDLLIMPEXP_CD udClassDiagramItem : public udDiagramItem
{
public:
    XS_DECLARE_CLONABLE_CLASS(udClassDiagramItem);

    udClassDiagramItem();
	udClassDiagramItem(const udClassDiagramItem &obj);
    virtual ~udClassDiagramItem();
	
protected:
    // protected virtual functions
    virtual udDiagramCanvas* CreateCanvas();	
};

// diagram elements ///////////////////////////////////////////////////////////////

class WXDLLIMPEXP_CD udClassElementItem : public udDiagElementItem
{
public:
    XS_DECLARE_CLONABLE_CLASS(udClassElementItem);
	
	udClassElementItem();
	
	// public functions
	void SetVariableString(const wxString& txt, int id);
	void SetFunctionString(const wxString& txt, int id);
	
	void AssignMemberCopy(udLinkItem *link);
	
	// public virtual functions
	virtual wxMenu* CreateMenu();
	
	virtual void OnCreateCopy();
	virtual void UpdateInnerContent();
	virtual void OnTreeItemEndDrag(const wxPoint &pos);
	virtual void OnTreeTextChange(const wxString& txt);
	virtual void OnShapeTextChange(const wxString& txt, udLABEL::TYPE type, int id);
	virtual void OnEditItem(wxWindow* parent);
	
	// member data accessors
	void SetIsTemplate(bool IsTemplate) {this->m_IsTemplate = IsTemplate;}
	void SetTemplateName(const wxString& TemplateName) {this->m_TemplateName = TemplateName;}
	bool GetIsTemplate() const {return m_IsTemplate;}
	const wxString& GetTemplateName() const {return m_TemplateName;}
	
protected:
	// protected functions
	void UpdateMembers(const wxString& prevname, const wxString& newname);
	
	// protected data
	bool m_IsTemplate;
	wxString m_TemplateName;
};

class WXDLLIMPEXP_CD udInherElementItem : public udDiagElementItem
{
public:
    XS_DECLARE_CLONABLE_CLASS(udInherElementItem);
};

class WXDLLIMPEXP_CD udInterElementItem : public udDiagElementItem
{
public:
    XS_DECLARE_CLONABLE_CLASS(udInterElementItem);
};

class WXDLLIMPEXP_CD udBiAssocElementItem : public udDiagElementItem
{
public:
    XS_DECLARE_CLONABLE_CLASS(udBiAssocElementItem);
};

class WXDLLIMPEXP_CD udUniAssocElementItem : public udDiagElementItem
{
public:
    XS_DECLARE_CLONABLE_CLASS(udUniAssocElementItem);
};

class WXDLLIMPEXP_CD udBaseAggregElementItem : public udDiagElementItem
{
public:
    XS_DECLARE_CLONABLE_CLASS(udBaseAggregElementItem);
};

class WXDLLIMPEXP_CD udCompAggregElementItem : public udDiagElementItem
{
public:
    XS_DECLARE_CLONABLE_CLASS(udCompAggregElementItem);
};

// code items /////////////////////////////////////////////////////////////////////

class WXDLLIMPEXP_CD udMemberLinkItem : public udCodeLinkItem
{
public:
	XS_DECLARE_CLONABLE_CLASS(udMemberLinkItem);
	
    udMemberLinkItem();
	udMemberLinkItem(const udCodeItem *orig, udLanguage::ACCESSTYPE at);
	udMemberLinkItem(const udMemberLinkItem &obj);
    virtual ~udMemberLinkItem();
	
	// public member data accessors
	void SetAccessType(const udLanguage::ACCESSTYPE& at) {m_nAccessType = at;}
	
	const udLanguage::ACCESSTYPE& GetAccessType() const {return m_nAccessType;}
	
	virtual void OnEditItem(wxWindow* parent);
	virtual void OnTreeItemEndDrag(const wxPoint &pos);
	virtual wxString ToString(udCodeItem::CODEFORMAT format, udLanguage *lang = NULL);
	virtual udProjectItem* GetOriginal();

protected:
	// protected data members
	udLanguage::ACCESSTYPE m_nAccessType;
};

class WXDLLIMPEXP_CD udMemberDataItem : public udVariableItem
{
public:
	XS_DECLARE_CLONABLE_CLASS(udMemberDataItem);

    udMemberDataItem();
	udMemberDataItem(const udVariableItem &obj ) : udVariableItem( obj ) {;}
	udMemberDataItem(const udMemberDataItem &obj);
    virtual ~udMemberDataItem();

	// public virtual functions
	virtual wxString ToString(CODEFORMAT format, udLanguage *lang = NULL);
	virtual bool OnTreeItemBeginDrag(const wxPoint &pos);
};

class WXDLLIMPEXP_CD udMemberDataLinkItem : public udMemberLinkItem
{
public:
	XS_DECLARE_CLONABLE_CLASS(udMemberDataLinkItem);
	
	udMemberDataLinkItem() : udMemberLinkItem() {;}
	udMemberDataLinkItem(const udCodeItem *orig, udLanguage::ACCESSTYPE at) : udMemberLinkItem( orig, at ) {;}
	udMemberDataLinkItem(const udMemberDataLinkItem &obj) : udMemberLinkItem( obj ) {;}
};

class WXDLLIMPEXP_CD udMemberFunctionItem : public udFunctionItem
{
public:
	XS_DECLARE_CLONABLE_CLASS(udMemberFunctionItem);

    udMemberFunctionItem();
	udMemberFunctionItem(const udFunctionItem &obj ) : udFunctionItem( obj ) {;}
	udMemberFunctionItem(const udMemberFunctionItem &obj);
    virtual ~udMemberFunctionItem();

	// public virtual functions
	virtual wxMenu* CreateMenu();
	
	virtual wxString ToString(CODEFORMAT format, udLanguage *lang = NULL);
	virtual bool OnTreeItemBeginDrag(const wxPoint &pos);
};

class WXDLLIMPEXP_CD udMemberFunctionLinkItem : public udMemberLinkItem
{
public:
	XS_DECLARE_CLONABLE_CLASS(udMemberFunctionLinkItem);
	
	udMemberFunctionLinkItem() : udMemberLinkItem() {;}
	udMemberFunctionLinkItem(const udCodeItem *orig, udLanguage::ACCESSTYPE at) : udMemberLinkItem( orig, at ) {;}
	udMemberFunctionLinkItem(const udMemberFunctionLinkItem &obj) : udMemberLinkItem( obj ) {;}
};

class WXDLLIMPEXP_CD udConstructorFunctionItem : public udMemberFunctionItem
{
public:
	XS_DECLARE_CLONABLE_CLASS(udConstructorFunctionItem);

    udConstructorFunctionItem();
	udConstructorFunctionItem(const udConstructorFunctionItem &obj);
    virtual ~udConstructorFunctionItem();
	
	// public member data accessors
	StringMap& GetUsedConstructors() { return m_mapUsedConstructors; }
	StringMap& GetCallParams() {return m_mapCallParams; }
	
	// public virtual functions
	virtual wxString ToString(CODEFORMAT format, udLanguage *lang = NULL);
	virtual void OnEditItem(wxWindow* parent);
	
protected:
	StringMap m_mapUsedConstructors;
	StringMap m_mapCallParams;
	
	// protected functions
	wxString GetUpdatedCallParams(const wxString& cons);
};

class WXDLLIMPEXP_CD udDestructorFunctionItem : public udMemberFunctionItem
{
public:
	XS_DECLARE_CLONABLE_CLASS(udDestructorFunctionItem);

    udDestructorFunctionItem();
	udDestructorFunctionItem(const udDestructorFunctionItem &obj);
    virtual ~udDestructorFunctionItem();
	
	// public virtual functions
	virtual wxString ToString(CODEFORMAT format, udLanguage *lang = NULL);
	virtual void OnEditItem(wxWindow* parent);
};

#endif //_DIAG_CD_H_
