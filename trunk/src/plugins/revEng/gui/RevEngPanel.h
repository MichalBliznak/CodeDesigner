#ifndef REVENGPANEL_H
#define REVENGPANEL_H

#include "GUI.h" // Base class: _RevEngPanel

class udRevEngPanel : public _RevEngPanel {

public:
	udRevEngPanel( wxWindow *parent );
	virtual ~udRevEngPanel();
	
protected:
	wxTreeItemId m_treeIdClasses;
	wxTreeItemId m_treeIdFunctions;
	wxTreeItemId m_treeIdVariables;
	
	void GetCheckedFiles(wxArrayString &files);
	void GetSelectedFiles(wxArrayString &files);
	void InitializeSymbolsTree();
	
	virtual void OnAddFilesClick(wxCommandEvent& event);
	virtual void OnBeginDrag(wxTreeEvent& event);
	virtual void OnCheckAllFilesClick(wxCommandEvent& event);
	virtual void OnDeselectAllFilesClick(wxCommandEvent& event);
	virtual void OnParseClick(wxCommandEvent& event);
	virtual void OnRemoveFilesClick(wxCommandEvent& event);
	virtual void OnRightClick(wxTreeEvent& event);
	virtual void OnSelectAllFilesClick(wxCommandEvent& event);
	virtual void OnUncheckAllFilesClick(wxCommandEvent& event);
	virtual void OnUpdateParse(wxUpdateUIEvent& event);
	virtual void OnUpdateRemoveFiles(wxUpdateUIEvent& event);

};

#endif // REVENGPANEL_H
