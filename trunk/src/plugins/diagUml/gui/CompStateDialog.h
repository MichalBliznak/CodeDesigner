#ifndef __udcompstatendialog__
#define __udcompstatendialog__

#include "GUI.h"
#include "../DiagUml.h"
#include "projectbase/codegen/Language.h"

class udCompStateDialog : public _CompStateDialog
{

public:
	udCompStateDialog(wxWindow *parent, udCompStateElementItem *state, udLanguage *lang);
	virtual ~udCompStateDialog();
	
	// member data accessors
	void SetDescription(const wxString& Description) {this->m_Description = Description;}
	void SetCodeName(const wxString& Name) {this->m_Name = Name;}
	
	const wxString& GetDescription() const {return m_Description;}
	const wxString& GetCodeName() const {return m_Name;}
	
	// public functions
	wxString GetEntryActionsString();
	wxString GetExitActionsString();
		
protected:
	// protected data members
	wxString m_Name;
	wxString m_Description;
	
	udLanguage *m_pLang;
	udCompStateElementItem *m_pState;
	
	// protected functions
	wxListBox* GetActiveUsedList();

	// protected virtual functions
	virtual void OnInit(wxInitDialogEvent &event);
	virtual void OnNameChange(wxCommandEvent &event);
	virtual void OnMakeValid( wxCommandEvent &event );
	virtual void OnOk( wxCommandEvent& event );
	
	virtual void OnSelectAllUsed( wxCommandEvent& event );
	virtual void OnDeselectAllUsed( wxCommandEvent& event );
	virtual void OnRemoveAllUsed( wxCommandEvent& event );
	virtual void OnAdd( wxCommandEvent& event );
	virtual void OnUpdateAdd( wxUpdateUIEvent& event );
	virtual void OnRemove( wxCommandEvent& event );
	virtual void OnUpdateRemove( wxUpdateUIEvent& event );
	virtual void OnUp( wxCommandEvent& event );
	virtual void OnUpdateUp( wxUpdateUIEvent& event );
	virtual void OnDown( wxCommandEvent& event );
	virtual void OnUpdateDown( wxUpdateUIEvent& event );
	virtual void OnSelectAllAvailable( wxCommandEvent& event );
	virtual void OnDeselectAllAvailable( wxCommandEvent& event );
	virtual void OnConditionChange( wxCommandEvent& event );
	
};

#endif // __udcompstatendialog__
