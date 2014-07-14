#ifndef __udeventdialog__
#define __udeventdialog__

#include "GUI.h"
#include "../DiagUml.h"
#include "projectbase/codegen/Language.h"

class udEventDialog : public _EventDialog
{

public:
	udEventDialog(wxWindow *parent, udLanguage *lang);
	virtual ~udEventDialog();
	
	// public member data accessors
	
	void SetDescription(const wxString& Description) {this->m_Description = Description;}
	void SetEventType(const udEventItem::TYPE& EventType) {this->m_EventType = EventType;}
	void SetCodeName(const wxString& Name) {this->m_Name = Name;}
	
	const wxString& GetDescription() const {return m_Description;}
	const udEventItem::TYPE& GetEventType() const {return m_EventType;}
	const wxString& GetCodeName() const {return m_Name;}
	
protected:
	// protected data members
	wxString m_Name;
	wxString m_Description;
	udEventItem::TYPE m_EventType;

	udLanguage *m_pLang;

	// protected virtual functions
	virtual void OnInit( wxInitDialogEvent& event );
	virtual void OnNameChange( wxCommandEvent& event );
	virtual void OnMakeValid( wxCommandEvent& event );
	virtual void OnTypeChange( wxCommandEvent& event );
	virtual void OnOk( wxCommandEvent& event );

};

#endif // __udeventdialog__
