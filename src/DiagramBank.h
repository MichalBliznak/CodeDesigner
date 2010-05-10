#ifndef DIAGRAMBANK_H
#define DIAGRAMBANK_H

#include "wx/wxsf/wxShapeFramework.h"
#include "Project.h"

class udDiagramRecord : public xsSerializable
{
public:
	XS_DECLARE_CLONABLE_CLASS(udDiagramRecord);
	
	udDiagramRecord();
	udDiagramRecord(const udDiagramRecord &obj);
	virtual ~udDiagramRecord();
	
	// public functions
	udDiagramItem* GetDiagram();
	void GetDiagramDependencies(SerializableList& deps);
	
	// member data accessors
	void SetDescription(const wxString& Description) {this->m_Description = Description;}
	const wxString& GetDescription() const {return m_Description;}
	
protected:
	// protected data members
	wxString m_Description;
};

class udDiagramCategory : public xsSerializable
{	
public:
	DECLARE_DYNAMIC_CLASS(udDiagramCategory);

	udDiagramCategory();
	virtual ~udDiagramCategory();
	
	// public functions
	udDiagramRecord* GetDiagramRecord(const wxString& diagname);
	
	void AddDiagram(udDiagramItem *diag, const wxString& desc);
	void RemoveDiagram(const wxString& diagname);
	void CopyContent(udDiagramCategory *dest);
	
	// public member data accessors
	void SetName(const wxString& Name) {this->m_Name = Name;}
	const wxString& GetName() const {return m_Name;}
	
protected:
	// protected data members
	wxString m_Name;
};

class udDiagramBank : public wxXmlSerializer
{
public:
	DECLARE_DYNAMIC_CLASS(udDiagramBank);
	
	udDiagramBank();
	virtual ~udDiagramBank();
	
	// public function
	udDiagramCategory* CreateCategory(const wxString& name);
	udDiagramCategory* GetCategory(const wxString& name);
	void RemoveCategory(const wxString& name);
	
	void CreateCategories();
	void GetCategoriesNames(wxArrayString& categories);
};

#endif // DIAGRAMBANK_H
