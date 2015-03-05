#ifndef PROJECT_H
#define PROJECT_H

#include <wx/treectrl.h>

#include "Settings.h"
#include "projectbase/codegen/Language.h"
#include "projectbase/ProjectBase.h"

// project components /////////////////////////////////////////////////////////////

class udRootItem : public udProjectItem
{
public:
    XS_DECLARE_CLONABLE_CLASS(udRootItem);

    udRootItem();
	udRootItem(const udRootItem &obj);
    virtual ~udRootItem();

    // member data accessors
	udProjectSettings& GetSettings(){return m_Settings;}
	
	// public virtual functions
	virtual wxMenu* CreateMenu();
	
	virtual void OnTreeItemEndDrag(const wxPoint &pos);

protected:
    // protected data members
	udProjectSettings m_Settings;

	// protected virtual functions
    virtual wxXmlNode* Serialize(wxXmlNode* node);
    virtual void Deserialize(wxXmlNode* node);
};

class udPackageItem : public udProjectItem
{
public:
    XS_DECLARE_CLONABLE_CLASS(udPackageItem);

    udPackageItem();
	udPackageItem(const udPackageItem &obj);
    virtual ~udPackageItem();
	
	// public virtual functions
	virtual wxMenu* CreateMenu();
	
	virtual bool OnTreeItemBeginDrag(const wxPoint &pos);
	virtual void OnTreeItemEndDrag(const wxPoint &pos);
};

class udCodePackageItem : public udProjectItem
{
public:
    XS_DECLARE_CLONABLE_CLASS(udCodePackageItem);

    udCodePackageItem();
	udCodePackageItem(const udCodePackageItem &obj);
    virtual ~udCodePackageItem();

	// public virtual functions
	virtual wxMenu* CreateMenu();
	
	virtual bool OnTreeItemBeginDrag(const wxPoint &pos);
	virtual void OnTreeItemEndDrag(const wxPoint &pos);
};

class udNoteElementItem : public udDiagElementItem
{
public:
    XS_DECLARE_CLONABLE_CLASS(udNoteElementItem);
};

class udNoteConnElementItem : public udDiagElementItem
{
public:
    XS_DECLARE_CLONABLE_CLASS(udNoteConnElementItem);
};

class udGroupElementItem : public udDiagElementItem
{
public:
    XS_DECLARE_CLONABLE_CLASS(udGroupElementItem);
	
	udGroupElementItem();
	
	virtual void OnEditItem(wxWindow* parent);
};


// main project class /////////////////////////////////////////////////////////////

class udProject : public IProject
{
public:
    XS_DECLARE_CLONABLE_CLASS(udProject);

    udProject();
	udProject(const udProject &obj);
    virtual ~udProject();
	
	// function published by interface
	
	// names functions
	wxString MakeUniqueName(const wxString& name, int threshold = 0);
	bool IsUniqueName(const wxString& name);
	
	// element manipulations
	udProjectItem* CreateProjectItem(const wxString& classname, long parentId );
	udDiagElementItem* GetDiagramElement(const wxString& element);
	udDiagElementItem* GetDiagramElement(const wxString& diagram, const wxString& element);
	void GetDiagramElements(wxClassInfo *type, SerializableList& elements);
	udProjectItem* GetProjectItem(wxClassInfo *type, const wxString& name);
	
	// code items manipulations
	udCodeItem* GetCodeItem(wxClassInfo *type, const wxString& name, const wxString& scope);
	void GetDiagramCodeItems(udDiagramItem *diagram, wxClassInfo *type, SerializableList& codeitems);
	udFunctionItem* GetFunctionImplementedBy(const udDiagramItem *diag);
	
	// links manipulations
	void GetElementLinks(const wxString& diagram, const wxString& element, SerializableList& elements);
	void GetCodeLinks(bool valid, wxClassInfo *type, const wxString& codeitem, const wxString& scope, SerializableList& elements);
	void CheckElementLinks();
	void CheckCodeLinks();

	// diagram manipulations
	udDiagramItem* GetDiagram(const wxString& name);
	udDiagramItem* GetDiagram(udDiagramCanvas *canvas);
	void GetDiagramsRecursively(wxClassInfo *type, SerializableList& diagrams);
	void CloseAllDiagrams();
	
	// other, non-published functions
	
    udProjectSettings& GetSettings(){return ((udRootItem*)GetRootItem())->GetSettings();}

    void CreateRootItem();

	void CloseAllSubdiagrams(udDiagramItem *parent);
	
	// member data accessors
	void SetProjectPath(const wxString& path){m_sProjectPath = path;}
	void SetProjectDirectory(const wxString& path){m_sProjectDir = path;}
	
	const wxString& GetProjectPath() const {return m_sProjectPath;}
	const wxString& GetProjectDirectory() const {return m_sProjectDir;}
	
	// static functions
	static udProject* Get();
	static void AppendSubDiagramsShapes(ShapeList& elements);

protected:
    // protected data members
    static int m_nCounter;
	wxString m_sProjectPath;
	wxString m_sProjectDir;
	
    // protected functions
    static void DiagramOccurenceCount(udDiagramItem *diagram, const wxString& name);
	int OccurenceCount(const wxString& name);

};

#endif // PROJECT_H
