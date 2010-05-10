#ifndef __udclassmemberlinkdialog__
#define __udclassmemberlinkdialog__

#include "GUI.h"
#include "projectbase/ProjectBase.h"
#include "projectbase/codegen/Language.h"

class udClassMemberLinkDialog : public _ClassMemberLinkDialog
{

public:
	udClassMemberLinkDialog(wxWindow *parent, udCodeItem *orig, udLanguage *lang);
	virtual ~udClassMemberLinkDialog();
	
	// member data accessors
	void SetCodeName(const wxString& Name) {this->m_Name = Name;}
	void SetAccessType(const int& ActionType) {this->m_AccessType = ActionType;}
	
	const wxString& GetCodeName() const {return m_Name;}
	const int& GetAccessType() const {return m_AccessType;}
	
protected:
	// protected data members
	wxString m_Name;
	int m_AccessType;
	
	udCodeItem *m_pOriginal;
	udLanguage *m_pLang;
	
	// protected virtual functions
	virtual void OnInit(wxInitDialogEvent &event);
	virtual void OnEditOriginal( wxCommandEvent &event );
	virtual void OnOk( wxCommandEvent& event );
};

#endif // __udclassmemberlinkdialog__
