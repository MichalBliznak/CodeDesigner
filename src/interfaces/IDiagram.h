#ifndef _IDIAGRAM_H_
#define _IDIAGRAM_H_

#include <wx/wx.h>
#include <wx/dynarray.h>
#include <wx/wxsf/wxShapeFramework.h>
#include "IProject.h"

/**
 * \class cdDiagramComponentInfo
 * \author Michal
 * \date 14.2.2010
 * \file IDiagram.h
 * \brief 
 */
class udDiagramComponentInfo
{
public:

	enum TYPE
	{
		pitTOOL,
		pitELEMENT,
		pitCONNECTION
	};
	
	udDiagramComponentInfo(const wxString &icon, const wxString &desc, const wxString &className, const wxString &dataClassName, TYPE type) : m_Icon(icon), m_Desc(desc), m_ClassName(className), m_DataClassName(dataClassName), m_Type(type) {;}
	virtual ~udDiagramComponentInfo(){}
	
	// member data accessors
	void SetClassName(const wxString& ClassName) {this->m_ClassName = ClassName;}
	void SetDataClassName(const wxString& DataClassName) {this->m_DataClassName = DataClassName;}
	void SetDescription(const wxString& Desc) {this->m_Desc = Desc;}
	void SetIcon(const wxString& Icon) {this->m_Icon = Icon;}
	void SetType(const TYPE& Type) {this->m_Type = Type;}
	
	const wxString& GetClassName() const {return m_ClassName;}
	const wxString& GetDataClassName() const {return m_DataClassName;}
	const wxString& GetDescription() const {return m_Desc;}
	const wxString& GetIcon() const {return m_Icon;}
	const TYPE& GetType() const {return m_Type;}
	
protected:
	// data members
	wxString m_Icon;
    wxString m_Desc;
    wxString m_ClassName;
    wxString m_DataClassName;
    TYPE m_Type;
};

WX_DECLARE_OBJARRAY_WITH_DECL(udDiagramComponentInfo, DiagramComponentArray, class WXEXPORT);

/**
 * \class cdDiagramInfo
 * \author Michal
 * \date 14.2.2010
 * \file IDiagram.h
 * \brief 
 */
class udDiagramInfo
{
public:
	// member data accessors
	void AddComponentInfo(const udDiagramComponentInfo& info ) {m_ComponentArray.Add(info);}
	void SetDataClassName(const wxString& DataClassName) {this->m_DataClassName = DataClassName;}
	void SetName(const wxString& Name) {this->m_Name = Name;}
	void SetIcon(const wxString& Icon) {this->m_Icon = Icon;}
	
	const DiagramComponentArray& GetComponentArray() const {return m_ComponentArray;}
	const wxString& GetIcon() const {return m_Icon;}
	const wxString& GetDataClassName() const {return m_DataClassName;}
	const wxString& GetName() const {return m_Name;}
	
protected:
	// data members
    wxString m_Name;
	wxString m_DataClassName;
	wxString m_Icon;
	DiagramComponentArray m_ComponentArray;
};

//Every dll must contain at least this function
typedef udDiagramInfo (*GET_DIAGRAM_INFO_FUNC)();

#endif //_IDIAGRAM_H_
