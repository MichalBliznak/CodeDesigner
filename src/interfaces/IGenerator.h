#ifndef _IGENERATOR_H_
#define _IGENERATOR_H_

#include <wx/wx.h>

class udGeneratorInfo
{
public:
	void SetClassName(const wxString& ClassName) {this->m_ClassName = ClassName;}
	void SetDiagramClassName(const wxString& DiagramName) {this->m_DiagramClassName = DiagramName;}
	
	void SetDescription(const wxString& Description) {this->m_Description = Description;}
	const wxString& GetDescription() const {return m_Description;}
	const wxString& GetClassName() const {return m_ClassName;}
	const wxString& GetDiagramClassName() const {return m_DiagramClassName;}
	
protected:
	wxString m_ClassName;
	wxString m_DiagramClassName;
	wxString m_Description;
};

#endif //_IGENERATOR_H_