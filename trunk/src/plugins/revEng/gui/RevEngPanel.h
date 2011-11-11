#ifndef REVENGPANEL_H
#define REVENGPANEL_H

#include "GUI.h" // Base class: _RevEngPanel
//#include "../diagUml/DiagUml.h"

class ctagClass : public wxTreeItemData
{
public:
	wxString m_Name;
	wxString m_Inherits;
};

class ctagMember : public wxTreeItemData
{
public:
	wxString m_Name;
	wxString m_ParentClass;
	wxString m_Access;
	wxString m_RetType;
};

class ctagFunction : public wxTreeItemData
{
public:
	wxString m_Name;
	wxString m_ParentClass;
	wxString m_Access;
	wxString m_Signature;
	wxString m_RetType;
};

class udRevEngPanel : public _RevEngPanel {

public:
	udRevEngPanel( wxWindow *parent );
	virtual ~udRevEngPanel();
	
protected:
	bool m_fExpanded;
	
	wxTreeItemId m_treeIdClasses;
	wxTreeItemId m_treeIdFunctions;
	wxTreeItemId m_treeIdVariables;
	
	void GetCheckedFiles(wxArrayString &files);
	void GetSelectedFiles(wxArrayString &files);
	void InitializeSymbolsTree();
	
	int ExecCtags(const wxString& cmd, wxArrayString& output);
	
	void ParseClasses(const wxArrayString& ctags);
	void ParseMembers(wxTreeItemId parent, const wxArrayString& ctags);
	void ParseFunctions(wxTreeItemId parent, const wxArrayString& ctags);
	
	wxString FindTagValue(const wxArrayString& items, const wxString& key);
	
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
	virtual void OnExpandTreeClick(wxCommandEvent& event);
	virtual void OnRemoveAllFilesClick(wxCommandEvent& event);
	virtual void OnCreateClassDiagClick(wxCommandEvent& event);
	virtual void OnCreateStateChartClick(wxCommandEvent& event);

};

#endif // REVENGPANEL_H
