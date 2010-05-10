#ifndef __udsettingsdialog__
#define __udsettingsdialog__

#include "GUI.h"
#include "Settings.h"
#include "XS2PG.h"

class udSettingsDialog : public _SettingsDialog
{
public:
	udSettingsDialog(wxWindow *parent, udSettings& settings, const wxString& title);
	virtual ~udSettingsDialog();

protected:
	// protected virtual event handlers
	virtual void OnInit( wxInitDialogEvent& event );
	virtual void OnChangeCategory( wxTreeEvent& event );
	virtual void OnOk( wxCommandEvent& event );
	virtual void OnCancel( wxCommandEvent& event );
	virtual void OnDefaults( wxCommandEvent& event );
	
	// protected event handlers
	void OnPropertyGridChange( wxPropertyGridEvent& event );
	
	// protected functions
	void InitializeCategories();
	void CreateCategory(udSettingsCategory *category, const wxTreeItemId& parent);
	void CreateCategoryContent(udSettingsCategory* category);

	// protected data membres
	udSettings& m_Settings;
	
	wxString m_sPrevSettings;
	wxString m_sRootName;
	
	DECLARE_EVENT_TABLE();

private:
	// private data members
	wxTreeItemIdValue nCookie;
};

#endif // __udsettingsdialog__
