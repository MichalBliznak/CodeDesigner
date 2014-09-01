#ifndef _DIAG_SCH_H_
#define _DIAG_SCH_H_

#include "projectbase/ProjectBase.h"

// exported classes ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#define udfORIGINAL true
#define udfCODEMARKS true
#define udfLINK false
#define udfNO_CODEMARKS false
#define udnSIMPLE_STATE_CHART wxT("Simple State Chart")
#define udnSTATE_CHART wxT("State Chart")
#define udnCLASS_DIAGRAM wxT("Class Diagram")

// State Chart code items classes /////////////////////////////////////////////////////////////

class WXDLLIMPEXP_CD udActionItem : public udFunctionItem
{
public:
	XS_DECLARE_CLONABLE_CLASS(udActionItem);

    udActionItem();
	udActionItem(const udActionItem &obj);
    virtual ~udActionItem();

	// public virtual functions
	virtual wxString ToString(CODEFORMAT format, udLanguage *lang = NULL);
	virtual void OnEditItem(wxWindow* parent);
	virtual bool OnTreeItemBeginDrag(const wxPoint &pos);
};

class WXDLLIMPEXP_CD udConditionItem : public udFunctionItem
{
public:
	XS_DECLARE_CLONABLE_CLASS(udConditionItem);

    udConditionItem();
	udConditionItem(const udConditionItem &obj);
    virtual ~udConditionItem();

	// public virtual functions
	virtual wxString ToString(CODEFORMAT format, udLanguage *lang = NULL);
	virtual void OnEditItem(wxWindow* parent);
	virtual bool OnTreeItemBeginDrag(const wxPoint &pos);
};

class WXDLLIMPEXP_CD udEventItem : public udVariableItem
{
public:
	XS_DECLARE_CLONABLE_CLASS(udEventItem);

	enum TYPE
	{
		etNORMAL = 0,
		etCRITICAL
	};

    udEventItem();
	udEventItem(const udEventItem &obj);
    virtual ~udEventItem();

	// public member data accessors
	void SetEventType(TYPE et){m_nType = et;}
	
	TYPE GetEventType(){return m_nType;}

	// public virtual functions
	virtual wxString ToString(CODEFORMAT format, udLanguage *lang = NULL);
	virtual void OnEditItem(wxWindow* parent);
	virtual bool OnTreeItemBeginDrag(const wxPoint &pos);

protected:
	// protected data members
	TYPE m_nType;
};


class WXDLLIMPEXP_CD udActionLinkItem : public udFunctionLinkItem
{
public:
	XS_DECLARE_CLONABLE_CLASS(udActionLinkItem);
	
	// constructor
	udActionLinkItem()
	{
		AcceptSibbling(wxT("udActionLinkItem"));
		AcceptSibbling(wxT("udConditionLinkItem"));
		AcceptSibbling(wxT("udEventLinkItem"));
	}
	udActionLinkItem(const udCodeItem *orig) : udFunctionLinkItem(orig)
	{
		AcceptSibbling(wxT("udActionLinkItem"));
		AcceptSibbling(wxT("udConditionLinkItem"));
		AcceptSibbling(wxT("udEventLinkItem"));
	}
	// public functions
	udActionItem* GetOriginalAction(){ return wxDynamicCast( this->GetOriginal(), udActionItem ); }
};

class WXDLLIMPEXP_CD udConditionLinkItem : public udFunctionLinkItem
{
public:
	XS_DECLARE_CLONABLE_CLASS(udConditionLinkItem);
	
	// constructor
	udConditionLinkItem()
	{
		AcceptSibbling(wxT("udActionLinkItem"));
		AcceptSibbling(wxT("udConditionLinkItem"));
		AcceptSibbling(wxT("udEventLinkItem"));
	}
	udConditionLinkItem(const udCodeItem *orig) : udFunctionLinkItem(orig)
	{
		AcceptSibbling(wxT("udActionLinkItem"));
		AcceptSibbling(wxT("udConditionLinkItem"));
		AcceptSibbling(wxT("udEventLinkItem"));
	}
	// public functions
	udConditionItem* GetOriginalCondition(){ return wxDynamicCast( this->GetOriginal(), udConditionItem ); }
};

class WXDLLIMPEXP_CD udEventLinkItem : public udVariableLinkItem
{
public:
	XS_DECLARE_CLONABLE_CLASS(udEventLinkItem);
	
	// constructor
	udEventLinkItem()
	{
		m_fClearFlag = false;
		
		AcceptSibbling(wxT("udActionLinkItem"));
		AcceptSibbling(wxT("udConditionLinkItem"));
		AcceptSibbling(wxT("udEventLinkItem"));
		
		XS_SERIALIZE_BOOL_EX( m_fClearFlag, wxT("clear_flag"), false );
	}
	udEventLinkItem(const udCodeItem *orig) : udVariableLinkItem(orig)
	{
		m_fClearFlag = false;
		
		AcceptSibbling(wxT("udActionLinkItem"));
		AcceptSibbling(wxT("udConditionLinkItem"));
		AcceptSibbling(wxT("udEventLinkItem"));
		
		XS_SERIALIZE_BOOL_EX( m_fClearFlag, wxT("clear_flag"), false );
	}
	// public functions
	udEventItem* GetOriginalEvent(){ return wxDynamicCast( this->GetOriginal(), udEventItem ); }
	
	// public member data accessors
	void SetClearFlag(bool ClearFlag) {this->m_fClearFlag = ClearFlag;}
	bool IsClearFlag() const {return m_fClearFlag;}
	
	// public virtual functions
	virtual void OnEditItem(wxWindow* parent);
	
protected:
	// protected data members
	bool m_fClearFlag;
};

class WXDLLIMPEXP_CD udStateActionLinkItem : public udActionLinkItem
{
public:
	XS_DECLARE_CLONABLE_CLASS(udStateActionLinkItem);

	enum TYPE
	{
		saENTRY = 0,
		saEXIT
	};

	udStateActionLinkItem();
    udStateActionLinkItem(const udCodeItem *orig, TYPE type);
	udStateActionLinkItem(const udStateActionLinkItem &obj);
    virtual ~udStateActionLinkItem();

	// public member data accessors
	void SetActionType(TYPE type) {m_nActionType = type;}
	
	TYPE GetActionType() const { return m_nActionType; }
	
	// public virtual functions
	virtual void OnEditItem(wxWindow* parent);
	virtual void OnActivation();
	

protected:
	// protected data members
	TYPE m_nActionType;
};

// project components /////////////////////////////////////////////////////////////

class WXDLLIMPEXP_CD udSStateChartDiagramItem : public udDiagramItem
{
public:
    XS_DECLARE_CLONABLE_CLASS(udSStateChartDiagramItem);

    udSStateChartDiagramItem();
	udSStateChartDiagramItem(const udSStateChartDiagramItem &obj);
    virtual ~udSStateChartDiagramItem();
	
	// public member data accessors
	void SetInputAction(const wxString& action){m_sInputAction = action;}
	const wxString& GetInputAction() {return m_sInputAction;}
	void SetInline(bool inln){m_fInline = inln;}
	bool IsInline(){return m_fInline;}
	bool IsNonBlocking(){return m_fNonBlocking;}
	
	// public virtual functions
	virtual void OnEditItem(wxWindow* parent);
	
	virtual void GetSpecificCodeItems(wxClassInfo *type, SerializableList& codeitems);

protected:
	// protected data members
	wxString m_sInputAction;
	bool m_fInline;
	bool m_fNonBlocking;
	
    // protected virtual functions
    virtual udDiagramCanvas* CreateCanvas();
};

class WXDLLIMPEXP_CD udHStateChartDiagramItem : public udSStateChartDiagramItem
{
public:
    XS_DECLARE_CLONABLE_CLASS(udHStateChartDiagramItem);

    udHStateChartDiagramItem();
	udHStateChartDiagramItem(const udHStateChartDiagramItem &obj);
    virtual ~udHStateChartDiagramItem();

protected:
    // protected virtual functions
    virtual udDiagramCanvas* CreateCanvas();
};

// diagram elements ///////////////////////////////////////////////////////////////

class WXDLLIMPEXP_CD udTransElementItem : public udDiagElementItem
{
public:
    XS_DECLARE_CLONABLE_CLASS(udTransElementItem);

    udTransElementItem();
	udTransElementItem(const udTransElementItem &obj);
    virtual ~udTransElementItem();

	// public functions
	bool SetGuardString(const wxString& guard);
	void SetConditionString(const wxString& cond);
	void SetActionString(const wxString& action);
	void SetPriority(int prior){m_nPriority = prior;}
	
	bool HasCondition();
	bool HasActions();

	wxString GetGuardString();
	wxString GetConditionString();
	wxString GetActionsString();
	int GetPriority(){return m_nPriority;}
	
	udProjectItem* GetCondition(bool original = false);
	void GetActions(SerializableList& actions, bool original = false);
	
	wxString GetConditionAsString(udCodeItem::CODEFORMAT format, udLanguage *lang);
	wxString GetActionAsString( udProjectItem *action, udCodeItem::CODEFORMAT format, udLanguage *lang, bool codemarks);
	void GetActionsAsStrings(udCodeItem::CODEFORMAT format, udLanguage *lang, bool codemarks, wxArrayString& actions);
	
	void CopyActionItems(udTransElementItem *source);

	// public virtual functions
	virtual wxMenu* CreateMenu();
	
	virtual void OnEditItem(wxWindow* parent);
	virtual void OnShapeTextChange(const wxString& txt, udLABEL::TYPE type, int id);
	virtual void UpdateInnerContent();

protected:
	// protected data members
	long m_nPriority;
};

class WXDLLIMPEXP_CD udCompStateElementItem : public udDiagElementItem
{
public:
    XS_DECLARE_CLONABLE_CLASS(udCompStateElementItem);

    udCompStateElementItem();
	udCompStateElementItem(const udCompStateElementItem &obj);
    virtual ~udCompStateElementItem();
	
	// public functions
	void SetActionsString(const wxString& txt, udStateActionLinkItem::TYPE type);
	
	wxString GetEntryActionsString();
	wxString GetExitActionsString();
	
	void ClearActionItems(udStateActionLinkItem::TYPE type);

	// public virtual functions
	virtual wxMenu* CreateMenu();
	
	virtual void OnShapeTextChange(const wxString& txt, udLABEL::TYPE type, int id);
	virtual void OnEditItem(wxWindow* parent);
	virtual void UpdateInnerContent();
};

class WXDLLIMPEXP_CD udSimpleStateElementItem : public udDiagElementItem
{
public:
    XS_DECLARE_CLONABLE_CLASS(udSimpleStateElementItem);
};

class WXDLLIMPEXP_CD udInitialElementItem : public udDiagElementItem
{
public:
    XS_DECLARE_CLONABLE_CLASS(udInitialElementItem);
};

class WXDLLIMPEXP_CD udFinalElementItem : public udDiagElementItem
{
public:
    XS_DECLARE_CLONABLE_CLASS(udFinalElementItem);
	
	// constructor
	udFinalElementItem();
	udFinalElementItem(const udFinalElementItem &obj);
	~udFinalElementItem();
	
	// public member data accessors
	void SetRetVal(const wxString& RetVal) {this->m_sRetVal = RetVal;}
	
	const wxString& GetRetVal() const {return m_sRetVal;}
	
	// public virtual functions
	virtual void OnEditItem(wxWindow* parent);
	
protected:
	// protected data members
	wxString m_sRetVal;
};

class WXDLLIMPEXP_CD udDecisionElementItem : public udDiagElementItem
{
public:
    XS_DECLARE_CLONABLE_CLASS(udDecisionElementItem);
};

class WXDLLIMPEXP_CD udHistoryElementItem : public udDiagElementItem
{
public:
    XS_DECLARE_CLONABLE_CLASS(udHistoryElementItem);
};

class WXDLLIMPEXP_CD udSCHSubDiagramElementItem : public udSubDiagramElementItem
{
public:
    XS_DECLARE_CLONABLE_CLASS(udSCHSubDiagramElementItem);
	
	// constructor
	udSCHSubDiagramElementItem();
	udSCHSubDiagramElementItem(const udSCHSubDiagramElementItem& obj);
	
	// public member data accessors
	void SetStoreRetVal(bool StoreRetVal) {this->m_StoreRetVal = StoreRetVal;}
	bool GetStoreRetVal() const {return m_StoreRetVal;}
	
	// public virtual functions
	virtual void OnEditItem(wxWindow* parent);
	
protected:
	bool m_StoreRetVal;
};

class WXDLLIMPEXP_CD udHCHSubDiagramElementItem : public udSubDiagramElementItem
{
public:
    XS_DECLARE_CLONABLE_CLASS(udHCHSubDiagramElementItem);
	
	// constructor
	udHCHSubDiagramElementItem();
	udHCHSubDiagramElementItem(const udHCHSubDiagramElementItem& obj);
	
	// public member data accessors
	void SetStoreRetVal(bool StoreRetVal) {this->m_StoreRetVal = StoreRetVal;}
	bool GetStoreRetVal() const {return m_StoreRetVal;}
	
	// public virtual functions
	virtual void OnEditItem(wxWindow* parent);
	
protected:
	bool m_StoreRetVal;
};

#endif //_DIAG_SCH_H_
