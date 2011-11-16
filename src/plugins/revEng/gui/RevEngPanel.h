#ifndef REVENGPANEL_H
#define REVENGPANEL_H

#include "GUI.h" // Base class: _RevEngPanel
#include "../diagUml/DiagUml.h"

#define udfWITH_DECORATION true
#define udfWITHOUT_DECORATION true

class udCTAGS : public wxTreeItemData
{
public:
	enum TYPE
	{
		ttUNDEFINED,
		ttCLASS,
		ttCLASS_MEMBER,
		ttCLASS_FUNCTION,
		ttFUNCTION
	};

	wxString m_Name;
	wxString m_Pattern;
	
	TYPE m_Type;
};

class ctagClass : public udCTAGS
{
public:
	ctagClass() { m_Type = ttCLASS; }
	
	wxString m_Inherits;
};

class ctagClassMember : public udCTAGS
{
public:
	ctagClassMember() { m_Type = ttCLASS_MEMBER; }
	wxString m_ParentClass;
	wxString m_Access;
};

class ctagClassFunction : public udCTAGS
{
public:
	ctagClassFunction() { m_Type = ttCLASS_FUNCTION; }
	wxString m_ParentClass;
	wxString m_Access;
	wxString m_Signature;
};

class ctagFunction : public udCTAGS
{
public:
	ctagFunction() { m_Type = ttFUNCTION; }
	wxString m_Signature;
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
	void GetSelectedTreeIds(udCTAGS::TYPE type, wxArrayTreeItemIds &items);
	void GetClassMembersIds(udCTAGS::TYPE type, wxTreeItemId classId, wxArrayTreeItemIds &items);
	void InitializeSymbolsTree();
	
	int ExecCtags(const wxString& cmd, wxArrayString& output);
	
	void ParseClasses(const wxArrayString& ctags);
	void ParseMemberData(wxTreeItemId parent, const wxArrayString& ctags);
	void ParseMemberFunctions(wxTreeItemId parent, const wxArrayString& ctags);
	
	wxString FindTagValue(const wxArrayString& items, const wxString& key);
	wxString FindTagPattern(const wxString& ctag);
	
	wxString GetDataType(udCTAGS *ctag, bool decorations );
	udLanguage::ACCESSTYPE GetAccessType(const wxString& at);
	void GetFunctionArguments(udCTAGS *ctag, wxArrayString& args);
	
	umlClassItem* CreateClassElement( wxTreeItemId classId );
	void CreateClassInheritance( udDiagramItem* manager, wxTreeItemId classId );
	void CreateClassAssociations( udDiagramItem* manager, wxTreeItemId classId );
	
	void CreateDataMembers( udClassElementItem *classItem, wxTreeItemId classId );
	void CreateFunctionMembers( udClassElementItem *classItem, wxTreeItemId classId );
	
	virtual void OnAddFilesClick(wxCommandEvent& event);
	virtual void OnCheckAllFilesClick(wxCommandEvent& event);
	virtual void OnDeselectAllFilesClick(wxCommandEvent& event);
	virtual void OnParseClick(wxCommandEvent& event);
	virtual void OnRemoveFilesClick(wxCommandEvent& event);
	virtual void OnSelectAllFilesClick(wxCommandEvent& event);
	virtual void OnUncheckAllFilesClick(wxCommandEvent& event);
	virtual void OnUpdateParse(wxUpdateUIEvent& event);
	virtual void OnUpdateRemoveFiles(wxUpdateUIEvent& event);
	virtual void OnExpandTreeClick(wxCommandEvent& event);
	virtual void OnRemoveAllFilesClick(wxCommandEvent& event);
	virtual void OnCreateClassDiagClick(wxCommandEvent& event);
	virtual void OnCreateStateChartClick(wxCommandEvent& event);
	virtual void OnRemoveAllSymbolsClick(wxCommandEvent& event);

};

#endif // REVENGPANEL_H
