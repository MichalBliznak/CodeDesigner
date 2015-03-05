#ifndef _CD_PROJECT_BASE_H
#define _CD_PROJECT_BASE_H

#include "interfaces/Defs.h"

#include "interfaces/IProject.h"
#include "interfaces/IPluginManager.h"

#include <wx/wxsf/wxShapeFramework.h>

#include "DiagramBase.h"
#include "FrameBase.h"
#include "GeneratorBase.h"
#include "SettingsBase.h"
#include "Events.h"

// common shapes
#include "shapes/CircleElement.h"
#include "shapes/DnDElement.h"
#include "shapes/LabelElement.h"
#include "shapes/LineElement.h"
#include "shapes/MultiLabelLineElement.h"
#include "shapes/PolygonElement.h"
#include "shapes/RectElement.h"
#include "shapes/RoundRectElement.h"

#include "codegen/Language.h"
#include "codegen/CommentProcessors.h"

class udSubDiagramElementItem;
class udDiagElementItem;
class udCodeLinkItem;

#define uddvPRIORITY_MIN 255
#define	uddvPRIORITY_MAX 0
#define udfVALID true
#define udfINVALID false
#define uddvFUNCTION_USERIMPLEMENTATION wxT("<user-defined-code>")
#define udfDELAYED true
#define udfCLEAR_CONTENT true
#define udfDONT_CLEAR_CONTENT false
#define udnCOMMON_ITEMS wxT("Common Items")
#define udfUNIQUE_NAME true
#define udfAMBIGUOUS_NAME false
#define udvID_OFFSET 500000

using namespace wxXS;

// base classes ///////////////////////////////////////////////////////////////////

class WXDLLIMPEXP_CD udProjectItem : public IProjectItem
{
public:
	XS_DECLARE_CLONABLE_CLASS(udProjectItem);
	
	udProjectItem();
	udProjectItem(const udProjectItem& obj);
	virtual ~udProjectItem();
	
	virtual void SetName(const wxString& name){m_sName = GetUniqueName( name );}
	virtual void SetDescription(const wxString& desc){m_sDescription = desc;}

    virtual const wxString& GetName() const {return m_sName;}
	virtual const wxString& GetDescription() const {return m_sDescription;}
	virtual wxString GetUniqueId(const udLanguage *lang) {return wxString::Format("ID_%s", lang->MakeValidIdentifier( this->GetName() ).Upper());}
	
	// public functions
	virtual void AcceptChild(const wxString& classname) { m_arrAcceptedChild.Add(classname);	}
	virtual void AcceptSibbling(const wxString& classname) { m_arrAcceptedSibbling.Add(classname); }
	virtual bool IsChildAccepted(const wxString& classname) const { return m_arrAcceptedChild.Index( classname ) != wxNOT_FOUND; }
	virtual bool IsSibblingAccepted(const wxString& classname) const { return m_arrAcceptedSibbling.Index( classname ) != wxNOT_FOUND; }
	virtual void SetMustBeUnique(bool unique) { m_fMustBeUnique = unique; }
	virtual bool MustBeUnique() const { return m_fMustBeUnique; }

    // virtual public functions
	virtual wxMenu* CreateMenu();
		
	virtual void OnCreate();
	virtual void OnCreateCopy();
	virtual void OnTreeTextChange(const wxString& txt);
	virtual void OnShapeTextChange(const wxString& txt, udLABEL::TYPE type, int id);
	virtual bool OnTreeItemBeginDrag(const wxPoint& pos);
	virtual void OnTreeItemEndDrag(const wxPoint& pos);
    virtual void OnEditItem(wxWindow* parent);
    virtual void OnSelection();
    virtual void OnActivation();
    virtual void OnContextMenu(wxWindow* parent, const wxPoint& pos);
	
protected:
	// procted data members
    wxString m_sName;
	wxString m_sDescription;
	
	wxArrayString m_arrAcceptedChild;
	wxArrayString m_arrAcceptedSibbling;
	
	bool m_fMustBeUnique;
	
	// protected functions
	virtual wxString GetUniqueName(const wxString& name);
};

////////////////////////////////////////////////////////////////////////////////

class WXDLLIMPEXP_CD udLinkItem : public udProjectItem
{
public:
    XS_DECLARE_CLONABLE_CLASS(udLinkItem);

    udLinkItem();
    udLinkItem(const udLinkItem &obj);
    virtual ~udLinkItem();

	// public functions
	virtual udProjectItem* GetOriginal();

    // public virtual functions
    /*virtual void OnContextMenu(wxWindow* parent, const wxPoint& pos);*/
    virtual void OnActivation();
	virtual void OnTreeTextChange(const wxString& txt);
	virtual void OnEditItem(wxWindow* parent);
	
protected:

	virtual wxMenu* CreateMenu();
};

////////////////////////////////////////////////////////////////////////////////

class WXDLLIMPEXP_CD udElementLinkItem : public udLinkItem
{
public:
    XS_DECLARE_CLONABLE_CLASS(udElementLinkItem);

    udElementLinkItem();
    udElementLinkItem(const udElementLinkItem &obj);
    virtual ~udElementLinkItem();

	// public functions
	virtual udProjectItem* GetOriginal();
    
    void UpdateLabels(const wxString& diagram, const wxString& element);
	
    // public data members accessors
    void SetOrigDiagram(const wxString& name){ m_sOriginalDiagram = name; }
    void SetOrigElement(const wxString& name){ m_sOriginalElement = name; }

    wxString GetOrigDiagram(){ return m_sOriginalDiagram; }
    wxString GetOrigElement(){ return m_sOriginalElement; }
	
	// public virtual functions
    virtual void OnShapeTextChange(const wxString& txt, udLABEL::TYPE type, int id);
    virtual void OnSelection();
	virtual void OnContextMenu(wxWindow* parent, const wxPoint& pos);
	
protected:
    // protected data members
    wxString m_sOriginalDiagram;
    wxString m_sOriginalElement;
};

////////////////////////////////////////////////////////////////////////////////

class WXDLLIMPEXP_CD udDiagramLinkItem : public udLinkItem
{
public:
    XS_DECLARE_CLONABLE_CLASS(udDiagramLinkItem);

    udDiagramLinkItem();
    udDiagramLinkItem(const udDiagramLinkItem &obj);
    virtual ~udDiagramLinkItem();

	// public functions
	virtual udProjectItem* GetOriginal();
    
    // public data members accessors
    void SetOrigDiagram(const wxString& name){ m_sOriginalDiagram = name; }

    wxString GetOrigDiagram(){ return m_sOriginalDiagram; }	
	
protected:
    // protected data members
    wxString m_sOriginalDiagram;
};

////////////////////////////////////////////////////////////////////////////////

class WXDLLIMPEXP_CD udAccessType
{
public:
	udAccessType();
	udAccessType(udLanguage::ACCESSTYPE at);
	udAccessType(const udAccessType& obj);
	
	wxMenu* CreateAccessMenu();
	
	// public member data accessors
	void SetAccessType(const udLanguage::ACCESSTYPE& at) {m_nAccessType = at;}
	
	const udLanguage::ACCESSTYPE& GetAccessType() const {return m_nAccessType;}
	
protected:
	// protected data members
	udLanguage::ACCESSTYPE m_nAccessType;

};

////////////////////////////////////////////////////////////////////////////////

class WXDLLIMPEXP_CD udCodeItem : public udProjectItem
{
public:
	XS_DECLARE_CLONABLE_CLASS(udCodeItem);
	
	enum CODEFORMAT
	{
		cfDECLARATION,
		cfDEFINITION,
		cfCALL,
		cfFORMAL
	};

    udCodeItem();
	udCodeItem(const udCodeItem &obj);
    virtual ~udCodeItem();

	// public member data accessors
	void SetCode(const wxString& code){m_sCode = code;}
	void SetInverted(bool fInverted){m_fInverted = fInverted;}
	void SetInline(bool inln){m_fInline = inln;}
	void SetScope(const wxString& scope){m_sScope = scope;}
	
	const wxString& GetCode() const {return m_sCode;}
	bool GetInverted() const {return m_fInverted;}
	bool IsInline() const {return m_fInline;}
	const wxString& GetScope() const {return m_sScope;}
	
	void UpdateSignature();
	const wxString& GetSignature() const { return m_sSignature; }

	// public virtual functions
	virtual wxString ToString(CODEFORMAT format, udLanguage *lang = NULL);
	
	virtual wxMenu* CreateMenu();
		
	virtual void OnActivation();
	virtual bool OnTreeItemBeginDrag(const wxPoint &pos);
	virtual void OnTreeItemEndDrag(const wxPoint &pos);
	virtual void OnTreeTextChange(const wxString& txt);

protected:
	// protected data members
	wxString m_sCode;
	wxString m_sScope;
	wxString m_sSignature;
	bool m_fInverted;
	bool m_fInline;
	
	// protected functions
	bool DragCodeItem(udCodeLinkItem *link);
};

////////////////////////////////////////////////////////////////////////////////

class WXDLLIMPEXP_CD udCodeLinkItem : public udLinkItem, public udAccessType
{
public:
    XS_DECLARE_CLONABLE_CLASS(udCodeLinkItem);

    udCodeLinkItem();
	udCodeLinkItem(const udCodeItem *orig);	
    udCodeLinkItem(const udCodeLinkItem &obj);
    virtual ~udCodeLinkItem();
	
    // public data members accessors
    void SetOrigCodeItem(const wxString& name){ m_sOriginalCodeItem = name; }
	void SetScope(const wxString& scope){ m_sScope = scope; }
	
	const wxString& GetOrigCodeItem() const { return m_sOriginalCodeItem; }
	const wxString& GetScope() const { return m_sScope; }
	
	// public functions
	virtual wxString ToString(udCodeItem::CODEFORMAT format, udLanguage *lang = NULL) { return ((udCodeItem*)this->GetOriginal())->ToString(format, lang); }
	
	// public virtual functions
	virtual udProjectItem* GetOriginal();
	
	virtual void OnTreeTextChange(const wxString& txt);
	virtual void OnEditItem(wxWindow* parent);
	virtual void OnActivation();
	virtual bool OnTreeItemBeginDrag(const wxPoint &pos);
	virtual void OnTreeItemEndDrag(const wxPoint &pos);
	
protected:
	// protected data members
	wxString m_sOriginalCodeItem;
	wxString m_sScope;
};

// code items classes /////////////////////////////////////////////////////////////

class WXDLLIMPEXP_CD udVariableItem : public udCodeItem
{
public:
	XS_DECLARE_CLONABLE_CLASS(udVariableItem);

	enum DECLLOCATION
	{
		dlBUILTIN,
		dlCODE,
		dlHEADER
	};
	
    udVariableItem();
	udVariableItem(const udVariableItem &obj);
    virtual ~udVariableItem();
	
	// public functions
	virtual wxString GetDataTypeString(CODEFORMAT format, udLanguage *lang);
	virtual wxString GetModifierString(udLanguage *lang);

	// public member data accessors
	void SetValueType(const udLanguage::VALUETYPE& vt) {m_nValueType = vt;}
	void SetDataType(const udLanguage::DATATYPE& dt) {m_nDataType = dt;}
	void SetDataModifier(const udLanguage::DATAMODIFIER& modif) {m_nDataModifier = modif;}
	void SetUserDeclPlace(const DECLLOCATION& dec) {m_nUserDeclPlace = dec;}
	void SetUserDataType(const wxString& name) {m_sUserDataType = name;}
	void SetUserDeclaration(const wxString& code) {m_sUserDeclaration = code;}
	void SetUserDeclFile(const wxString& file) {m_sUserDeclFile = file;}
	void SetValue(const wxString& val) {m_sValue = val;}

	const udLanguage::VALUETYPE& GetValueType() const {return m_nValueType;}
	const udLanguage::DATAMODIFIER& GetDataModifer() const {return m_nDataModifier;}
	const udLanguage::DATATYPE& GetDataType() const {return m_nDataType;}
	const DECLLOCATION& GetUserDeclPlace() const {return m_nUserDeclPlace;}
	const wxString& GetUserDataType() const {return m_sUserDataType;}
	const wxString& GetUserDeclaration() const {return m_sUserDeclaration;}
	const wxString& GetUserDeclFile() const {return m_sUserDeclFile;}
	const wxString& GetValue() const {return m_sValue;}

	// public virtual functions
	virtual wxString ToString(CODEFORMAT format, udLanguage *lang = NULL);
	virtual void OnEditItem(wxWindow* parent);

protected:
	// protected data members
	DECLLOCATION m_nUserDeclPlace;
	
	udLanguage::VALUETYPE m_nValueType;
	udLanguage::DATATYPE m_nDataType;
	udLanguage::DATAMODIFIER m_nDataModifier;

	wxString m_sUserDataType;
	wxString m_sUserDeclaration;
	wxString m_sUserDeclFile;
	wxString m_sValue;
	
	// protected functions
	
private:
	// private functions
	void MarkSerializableDataMembers();
};

////////////////////////////////////////////////////////////////////////////////

class WXDLLIMPEXP_CD udGenericVariableItem : public udVariableItem
{
public:
    XS_DECLARE_CLONABLE_CLASS(udGenericVariableItem);
};

////////////////////////////////////////////////////////////////////////////////

class WXDLLIMPEXP_CD udVariableLinkItem : public udCodeLinkItem
{
public:
	XS_DECLARE_CLONABLE_CLASS(udVariableLinkItem);
	
	// constructor
	udVariableLinkItem() {;}
	udVariableLinkItem(const udCodeItem *orig) : udCodeLinkItem(orig) {;}
	// public functions
	udVariableItem* GetOriginalVariable(){ return wxDynamicCast( this->GetOriginal(), udVariableItem ); }
};

////////////////////////////////////////////////////////////////////////////////

class WXDLLIMPEXP_CD udParamItem : public udVariableItem
{
public:
	XS_DECLARE_CLONABLE_CLASS(udParamItem);

	udParamItem();
	udParamItem(const udParamItem& obj) : udVariableItem(obj) {;}
	virtual ~udParamItem() {;}
	
	virtual wxString GetDataTypeString(CODEFORMAT format, udLanguage *lang);
	
	// public virtual functions
	virtual void OnTreeTextChange(const wxString& txt);
	virtual wxString ToString(CODEFORMAT format, udLanguage *lang = NULL);
};

////////////////////////////////////////////////////////////////////////////////

class WXDLLIMPEXP_CD udFunctionItem : public udCodeItem
{
public:
	XS_DECLARE_CLONABLE_CLASS(udFunctionItem);

    udFunctionItem();
	udFunctionItem(const udFunctionItem &obj);
    virtual ~udFunctionItem();
	
	// public functions
	wxString GetDataTypeString(udLanguage *lang);
	wxString GetModifierString(udLanguage *lang);
	wxString GetParametersString(CODEFORMAT format, udLanguage *lang);

	// public member data accessors
	void SetRetValDataType(const udLanguage::DATATYPE& type) {m_nRetValDataType = type;}
	void SetRetValType(const udLanguage::VALUETYPE& vt) {m_nRetValType = vt;}
	void SetRetValModifier(const udLanguage::DATAMODIFIER& modif) {m_nRetValModifier = modif;}
	void SetUserRetValDataType(const wxString& name) {m_sUserRetValDataType = name;}
	void SetUserRetValDecl(const wxString& code) {m_sUserRetValDecl = code;}
	void SetUserRetValDeclFile(const wxString& file) {m_sUserRetValDeclFile = file;}
	void SetUserRetValDeclPlace(const udVariableItem::DECLLOCATION& dec) {m_nUserRetValDeclPlace = dec;}
	void SetFcnModifier(const udLanguage::FCNMODIFIER& modif) {m_nFcnModifier = modif;}
	void SetImplementation(const wxString& Implementation) {this->m_sImplementation = Implementation;}

	const udLanguage::DATATYPE& GetRetValDataType() const {return m_nRetValDataType;}
	const udLanguage::VALUETYPE& GetRetValType() const {return m_nRetValType;}
	const udLanguage::DATAMODIFIER& GetRetValModifer() const {return m_nRetValModifier;}
	const wxString& GetUserRetValDataType() const {return m_sUserRetValDataType;}
	const wxString& GetUserRetValDecl() const {return m_sUserRetValDecl;}
	const wxString& GetUserRetValDeclFile() const {return m_sUserRetValDeclFile;}
	const udVariableItem::DECLLOCATION& GetUserRetValDeclPlace() const {return m_nUserRetValDeclPlace;}
	const udLanguage::FCNMODIFIER& GetFunctionModifer() const {return m_nFcnModifier;}
	const wxString& GetImplementation() const {return m_sImplementation;}

	// public virtual functions
	virtual wxString ToString(CODEFORMAT format, udLanguage *lang = NULL);
	virtual void OnEditItem(wxWindow* parent);

protected:
	// protected data members
	udLanguage::DATATYPE m_nRetValDataType;
	udLanguage::VALUETYPE m_nRetValType;
	udLanguage::DATAMODIFIER m_nRetValModifier;
	wxString m_sUserRetValDataType;
	wxString m_sUserRetValDecl;
	wxString m_sUserRetValDeclFile;
	udVariableItem::DECLLOCATION m_nUserRetValDeclPlace;
	udLanguage::FCNMODIFIER m_nFcnModifier;
	wxString m_sImplementation;
	
	// protected functions
	
	
private:
	// private functions
	void MarkSerializableDataMembers();
};

////////////////////////////////////////////////////////////////////////////////

class WXDLLIMPEXP_CD udGenericFunctionItem : public udFunctionItem
{
public:
    XS_DECLARE_CLONABLE_CLASS(udGenericFunctionItem);
	virtual ~udGenericFunctionItem(){;}
	
	// public virtual functions
	virtual wxString ToString(udCodeItem::CODEFORMAT format, udLanguage *lang = NULL);
};

class WXDLLIMPEXP_CD udFunctionLinkItem : public udCodeLinkItem
{
public:
	XS_DECLARE_CLONABLE_CLASS(udFunctionLinkItem);
	
	// constructor
	udFunctionLinkItem();
	udFunctionLinkItem(const udCodeItem *orig);
	udFunctionLinkItem(const udFunctionLinkItem& obj);
	virtual ~udFunctionLinkItem() {;}
	
	// public functions
	udFunctionItem* GetOriginalFunction(){ return wxDynamicCast( this->GetOriginal(), udFunctionItem ); }
	
	// call parameters handling
	StringMap& GetCallParams() {return m_mapCallParams;}
	wxString GetUpdatedFunctionCall(udCodeItem::CODEFORMAT format, udLanguage *lang);
	
	// public virtual functions
	virtual wxString ToString(udCodeItem::CODEFORMAT format, udLanguage *lang = NULL);
	virtual void OnEditItem(wxWindow* parent);
	
protected:
	// protected data members
	StringMap m_mapCallParams;
};

class WXDLLIMPEXP_CD udDiagramItem : public udProjectItem
{
public:
    XS_DECLARE_CLONABLE_CLASS(udDiagramItem);

    udDiagramItem();
	udDiagramItem(const udDiagramItem &obj);
    virtual ~udDiagramItem();

    // public member data accessors
    void SetDiagramType(const wxString& type){m_sDiagramType = type;}
    void SetActiveAlgorithm(const wxString& name){m_sActiveAlgorithm = name;}
    void SetActiveGenerator(const wxString& name){m_sActiveGenerator = name;}
	void SetOutputFile(const wxString& path){m_sOutputFile = path;}
	void SetSubdiagramElement(udSubDiagramElementItem *sub){m_pSubElement = sub;}
	void EnableGeneration(bool enab){m_fGenerate = enab;}

    const wxString& GetDiagramType(){return m_sDiagramType;}
    udDiagramManager& GetDiagramManager(){return m_DiagramManager;}
    udDiagramManager* GetDiagramManagerPointer(){return &m_DiagramManager;}
    const wxString& GetActiveAlgorithm(){return m_sActiveAlgorithm;}
    const wxString& GetActiveGenerator(){return m_sActiveGenerator;}
	const wxString& GetOutputFile() {return m_sOutputFile;}
	udSubDiagramElementItem* GetSubdiagramElement(){return m_pSubElement;}
	bool IsGenerated(){return m_fGenerate;}

    // public function
    udDiagramCanvas* ShowDiagramPage();
	udDiagramCanvas* GetDiagramPage() {return m_pCurrentUMLCanvas;}
    void CloseDiagramPage();
    void OnDestroyDiagramPage();
	void UpdateDiagramPageLabel();

	// public virtual functions
	virtual wxMenu* CreateMenu();
	
    virtual void OnActivation();
	virtual void OnTreeTextChange(const wxString& txt);
	virtual bool OnTreeItemBeginDrag(const wxPoint &pos);
	virtual void OnEditItem(wxWindow* parent);
	
	virtual void GetSpecificCodeItems(wxClassInfo *type, SerializableList& codeitems);

protected:

    // protected data members
    wxString m_sDiagramType;
	
    udDiagramManager m_DiagramManager;
    udDiagramCanvas *m_pCurrentUMLCanvas;
	udSubDiagramElementItem *m_pSubElement;

    wxString m_sActiveGenerator;
    wxString m_sActiveAlgorithm;
	
	wxString m_sOutputFile;
	bool m_fGenerate;

    // protected virtual functions
    virtual udDiagramCanvas* CreateCanvas();

    virtual wxXmlNode* Serialize(wxXmlNode* node);
    virtual void Deserialize(wxXmlNode* node);
};

// diagram elements ///////////////////////////////////////////////////////////////

class WXDLLIMPEXP_CD udDiagElementItem : public udProjectItem, public udAccessType
{
public:
	friend class udElementLinkItem;
	
    XS_DECLARE_CLONABLE_CLASS(udDiagElementItem);

    udDiagElementItem();
	udDiagElementItem(const udDiagElementItem &obj);
    virtual ~udDiagElementItem();
	
	// code items handling
	void AssignCodeItem(udProjectItem *item);
	void ClearCodeItems(wxClassInfo *origtype);
	udProjectItem* GetCodeItem(wxClassInfo *type, const wxString& name, bool original = false);
	void GetCodeItems(wxClassInfo *type, SerializableList &list, bool original = false);

    // virtual public functions
	virtual wxMenu* CreateMenu();
	virtual wxString GetUniqueId(const udLanguage *lang);
	
    virtual void OnSelection();
    virtual void OnActivation();
	virtual void OnEditItem(wxWindow* parent);
	virtual void OnTreeTextChange(const wxString& txt);
	virtual bool OnTreeItemBeginDrag(const wxPoint &pos);
	virtual void OnTreeItemEndDrag(const wxPoint &pos);
	virtual void OnShapeTextChange(const wxString& txt, udLABEL::TYPE type, int id);
	virtual void OnContextMenu(wxWindow* parent, const wxPoint& pos);
	
	virtual void UpdateInnerContent(){;}

protected:	
	// protected data members
	StringMap m_mapStoredCallParams;
	
	// protected functions
	wxString RemoveCallParams(const wxString& txt);
	
	void StoreCallParams();
	void RestoreCallParams();
	
	bool UpdateSubmenu(wxMenu *submenu, const wxArrayString& items, bool clear);
	void UpdateAffectedCodeItems(const wxString& prevname, const wxString& newname);

	// protected virtual functions
	
    virtual wxXmlNode* Serialize(wxXmlNode* node);
    virtual void Deserialize(wxXmlNode* node);
	
	virtual wxString GetUniqueName(const wxString& name);
};

////////////////////////////////////////////////////////////////////////////////

class WXDLLIMPEXP_CD udSubDiagramElementItem : public udDiagElementItem
{
public:
    XS_DECLARE_CLONABLE_CLASS(udSubDiagramElementItem);

    udSubDiagramElementItem();
	udSubDiagramElementItem(const udSubDiagramElementItem &obj);
    virtual ~udSubDiagramElementItem();
	
	udDiagramItem* GetSubDiagram(){return m_pSubDiagram;}

	virtual wxMenu* CreateMenu();

	virtual void OnCreate();
    virtual void OnActivation();
	virtual void OnTreeTextChange(const wxString& txt);
	virtual void OnShapeTextChange(const wxString& txt, udLABEL::TYPE type, int id);

protected:
    udDiagramItem* m_pSubDiagram;
	
	// protected functions
	virtual wxString GetUniqueName(const wxString& name);
};

#endif //_CD_PROJECT_BASE_H
