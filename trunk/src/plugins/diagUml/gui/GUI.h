///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  6 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUI_H__
#define __GUI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/stc/stc.h>
#include <wx/notebook.h>
#include <wx/button.h>
#include <wx/gbsizer.h>
#include <wx/dialog.h>
#include <wx/choice.h>
#include <wx/statbox.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>
#include <wx/spinctrl.h>
#include <wx/menu.h>
#include <wx/listbox.h>
#include <wx/listctrl.h>
#include <wx/checklst.h>
#include <wx/statline.h>

///////////////////////////////////////////////////////////////////////////

#define IDC_TRANSDLG_PROPGRID 1000
#define IDC_USEDACTIONS 1001
#define IDM_TRANS_SELECTALL 1002
#define IDM_TRANS_DESELECTALL 1003
#define IDM_TRANS_REMOVEALL 1004
#define ICD_AVAILABLEACTIONS 1005
#define IDM_TRANS_SELECTALLAV 1006
#define IDM_TRANS_DESELECTALLAV 1007
#define IDM_CANDIDATES_SELECTALL 1008
#define IDM_CANDIDATES_DESELECTALL 1009

///////////////////////////////////////////////////////////////////////////////
/// Class _CodeDialog
///////////////////////////////////////////////////////////////////////////////
class _CodeDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxTextCtrl* m_eName;
		wxCheckBox* m_cbMakeValid;
		wxStaticText* m_staticText2;
		wxTextCtrl* m_eDescription;
		wxNotebook* m_pNotebook;
		wxPanel* m_pageAdv;
		wxCheckBox* m_cbInline;
		wxPanel* m_pageEditor;
		wxStyledTextCtrl* m_sciEditor;
		wxStdDialogButtonSizer* bntSizer;
		wxButton* bntSizerOK;
		wxButton* bntSizerCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnInit( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void OnNameChange( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMakeValid( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOk( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		_CodeDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Condition/Action properties"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~_CodeDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class _StateActionDialog
///////////////////////////////////////////////////////////////////////////////
class _StateActionDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxTextCtrl* m_eName;
		wxCheckBox* m_cbMakeValid;
		wxStaticText* m_staticText2;
		wxTextCtrl* m_eDescription;
		wxNotebook* m_pNotebook;
		wxPanel* m_pageAdv;
		wxCheckBox* m_cbInline;
		wxStaticText* m_staticText17;
		wxChoice* m_chType;
		wxPanel* m_pageEditor;
		wxStyledTextCtrl* m_sciEditor;
		wxStdDialogButtonSizer* bntSizer;
		wxButton* bntSizerOK;
		wxButton* bntSizerCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnInit( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void OnNameChange( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMakeValid( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOk( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		_StateActionDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("State action properties"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~_StateActionDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class _EventDialog
///////////////////////////////////////////////////////////////////////////////
class _EventDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxTextCtrl* m_eName;
		wxCheckBox* m_cbMakeValid;
		wxStaticText* m_staticText2;
		wxTextCtrl* m_eDescription;
		wxNotebook* m_pNotebook;
		wxPanel* m_pageAdv;
		wxStaticText* m_staticText11;
		wxChoice* m_chEventType;
		wxStdDialogButtonSizer* bntSizer;
		wxButton* bntSizerOK;
		wxButton* bntSizerCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnInit( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void OnNameChange( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMakeValid( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTypeChange( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOk( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		_EventDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Event properties"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~_EventDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class _ActionLinkDialog
///////////////////////////////////////////////////////////////////////////////
class _ActionLinkDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxTextCtrl* m_eName;
		wxStaticText* m_stOriginal;
		wxButton* btnEditOrig;
		wxNotebook* m_pNotebook;
		wxPanel* m_pageAdv;
		wxStaticText* m_staticText17;
		wxChoice* m_chType;
		wxPanel* m_pageParametersMap;
		wxPropertyGrid* m_pgParams;
		wxStdDialogButtonSizer* bntSizer;
		wxButton* bntSizerOK;
		wxButton* bntSizerCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnInit( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void OnEditOriginal( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOk( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		_ActionLinkDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("State action link properties"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 400,380 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~_ActionLinkDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class _ClassMemberLinkDialog
///////////////////////////////////////////////////////////////////////////////
class _ClassMemberLinkDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxTextCtrl* m_eName;
		wxStaticText* m_stOriginal;
		wxButton* btnEditOrig;
		wxNotebook* m_pNotebook;
		wxPanel* m_pageAdv;
		wxStaticText* m_staticText17;
		wxChoice* m_chType;
		wxStdDialogButtonSizer* bntSizer;
		wxButton* bntSizerOK;
		wxButton* bntSizerCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnInit( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void OnEditOriginal( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOk( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		_ClassMemberLinkDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Class member link properties"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 400,380 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~_ClassMemberLinkDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class _EventLinkDialog
///////////////////////////////////////////////////////////////////////////////
class _EventLinkDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxTextCtrl* m_eName;
		wxStaticText* m_stOriginal;
		wxButton* btnEditOrig;
		wxNotebook* m_pNotebook;
		wxPanel* m_pageAdv;
		wxCheckBox* m_checkBoxClearFlag;
		wxStdDialogButtonSizer* bntSizer;
		wxButton* bntSizerOK;
		wxButton* bntSizerCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnInit( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void OnEditOriginal( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOk( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		_EventLinkDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Event link properties"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 400,380 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~_EventLinkDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class _TransitionDialog
///////////////////////////////////////////////////////////////////////////////
class _TransitionDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxTextCtrl* m_eName;
		wxCheckBox* m_cbMakeValid;
		wxStaticText* m_staticText2;
		wxTextCtrl* m_eDescription;
		wxNotebook* m_pNotebook;
		wxPanel* m_pageCondition;
		wxStaticText* m_staticText51;
		wxChoice* m_chConditions;
		wxStaticText* m_staticText52;
		wxSpinCtrl* m_spinPriority;
		wxPanel* m_pageActions;
		wxStaticText* m_staticText53;
		wxListBox* m_listUsed;
		wxMenu* m_menuUsed;
		wxButton* m_btnAdd;
		wxButton* m_btnRemove;
		wxButton* m_btnUp;
		wxButton* m_btnDown;
		wxStaticText* m_staticText54;
		wxListBox* m_listAvailable;
		wxMenu* m_menuAvailable;
		wxStdDialogButtonSizer* bntSizer;
		wxButton* bntSizerOK;
		wxButton* bntSizerCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnInit( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void OnNameChange( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMakeValid( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnConditionChange( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSelectAllUsed( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDeselectAllUsed( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRemoveAllUsed( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAdd( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateAdd( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnRemove( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateRemove( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnUp( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateUp( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnDown( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateDown( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnSelectAllAvailable( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDeselectAllAvailable( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOk( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		_TransitionDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Transition properties"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~_TransitionDialog();
		
		void m_listUsedOnContextMenu( wxMouseEvent &event )
		{
			m_listUsed->PopupMenu( m_menuUsed, event.GetPosition() );
		}
		
		void m_listAvailableOnContextMenu( wxMouseEvent &event )
		{
			m_listAvailable->PopupMenu( m_menuAvailable, event.GetPosition() );
		}
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class _FinalStateDialog
///////////////////////////////////////////////////////////////////////////////
class _FinalStateDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxTextCtrl* m_eName;
		wxCheckBox* m_cbMakeValid;
		wxStaticText* m_staticText2;
		wxTextCtrl* m_eDescription;
		wxNotebook* m_pNotebook;
		wxPanel* m_pageAdv;
		wxStaticText* m_staticText56;
		wxTextCtrl* m_textRetValue;
		wxButton* m_btnDefault;
		wxStdDialogButtonSizer* bntSizer;
		wxButton* bntSizerOK;
		wxButton* bntSizerCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnInit( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void OnNameChange( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMakeValid( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDefault( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOk( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		_FinalStateDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Final state properties"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~_FinalStateDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class _CompStateDialog
///////////////////////////////////////////////////////////////////////////////
class _CompStateDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxTextCtrl* m_eName;
		wxCheckBox* m_cbMakeValid;
		wxStaticText* m_staticText2;
		wxTextCtrl* m_eDescription;
		wxNotebook* m_pNotebook;
		wxPanel* m_pageActions;
		wxNotebook* m_notebookActions;
		wxPanel* m_pageEntry;
		wxListBox* m_listUsedEntry;
		wxMenu* m_menuUsed;
		wxPanel* m_pageExit;
		wxListBox* m_listUsedExit;
		wxMenu* m_menuUsedExit;
		wxButton* m_btnAdd;
		wxButton* m_btnRemove;
		wxButton* m_btnUp;
		wxButton* m_btnDown;
		wxStaticText* m_staticText54;
		wxListBox* m_listAvailable;
		wxMenu* m_menuAvailable;
		wxStdDialogButtonSizer* bntSizer;
		wxButton* bntSizerOK;
		wxButton* bntSizerCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnInit( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void OnNameChange( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMakeValid( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSelectAllUsed( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDeselectAllUsed( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRemoveAllUsed( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAdd( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateAdd( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnRemove( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateRemove( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnUp( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateUp( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnDown( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateDown( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnSelectAllAvailable( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDeselectAllAvailable( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOk( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		_CompStateDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Composite state properties"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~_CompStateDialog();
		
		void m_listUsedEntryOnContextMenu( wxMouseEvent &event )
		{
			m_listUsedEntry->PopupMenu( m_menuUsed, event.GetPosition() );
		}
		
		void m_listUsedExitOnContextMenu( wxMouseEvent &event )
		{
			m_listUsedExit->PopupMenu( m_menuUsedExit, event.GetPosition() );
		}
		
		void m_listAvailableOnContextMenu( wxMouseEvent &event )
		{
			m_listAvailable->PopupMenu( m_menuAvailable, event.GetPosition() );
		}
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class _ConstructorDialog
///////////////////////////////////////////////////////////////////////////////
class _ConstructorDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxTextCtrl* m_eName;
		wxCheckBox* m_cbMakeValid;
		wxStaticText* m_staticText2;
		wxTextCtrl* m_eDescription;
		wxNotebook* m_pNotebook;
		wxPanel* m_pageAdv;
		wxStaticText* m_staticText461;
		wxChoice* m_chImplementation;
		wxStaticText* m_staticText431;
		wxChoice* m_chFcnModifier;
		wxPanel* m_pageParams;
		wxListCtrl* m_lstParams;
		wxButton* m_btnAdd;
		wxButton* m_btnEdit;
		wxButton* m_btnRemove;
		wxButton* m_btnMoveUp;
		wxButton* m_btnMoveDown;
		wxPanel* m_pageBases;
		wxCheckListBox* m_checkListBases;
		wxStaticText* m_staticText80;
		wxChoice* m_chBaseConstructor;
		wxPropertyGrid* m_pgParams;
		wxPanel* m_pageEditor;
		wxStyledTextCtrl* m_sciEditor;
		wxStdDialogButtonSizer* bntSizer;
		wxButton* bntSizerOK;
		wxButton* bntSizerCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnInit( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void OnNameChange( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMakeValid( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnParamActivated( wxListEvent& event ) { event.Skip(); }
		virtual void OnAddClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEditClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateParamButtons( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnRemoveClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMoveUpClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMoveDownClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBaseClassSelected( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBaseConstructorChange( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEditorTextChange( wxKeyEvent& event ) { event.Skip(); }
		virtual void OnUpdateEditor( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnCancel( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOk( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		_ConstructorDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Constructor properties"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 460,450 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~_ConstructorDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class _DestructorDialog
///////////////////////////////////////////////////////////////////////////////
class _DestructorDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxTextCtrl* m_eName;
		wxCheckBox* m_cbMakeValid;
		wxStaticText* m_staticText2;
		wxTextCtrl* m_eDescription;
		wxNotebook* m_pNotebook;
		wxPanel* m_pageAdv;
		wxStaticText* m_staticText461;
		wxChoice* m_chImplementation;
		wxStaticText* m_staticText431;
		wxChoice* m_chFcnModifier;
		wxPanel* m_pageEditor;
		wxStyledTextCtrl* m_sciEditor;
		wxStdDialogButtonSizer* bntSizer;
		wxButton* bntSizerOK;
		wxButton* bntSizerCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnInit( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void OnNameChange( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMakeValid( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEditorTextChange( wxKeyEvent& event ) { event.Skip(); }
		virtual void OnUpdateEditor( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnCancel( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOk( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		_DestructorDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Destructor properties"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 460,450 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~_DestructorDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class _RenameVirtualDialog
///////////////////////////////////////////////////////////////////////////////
class _RenameVirtualDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText37;
		wxTextCtrl* m_textCtrlName;
		wxCheckBox* m_chbMakeValid;
		wxCheckListBox* m_checkListCandidates;
		wxMenu* m_menuCandidates;
		wxStdDialogButtonSizer* buttonSizer;
		wxButton* buttonSizerOK;
		wxButton* buttonSizerCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnNameChange( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMakeValid( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSelectAll( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDeselectAll( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOk( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		_RenameVirtualDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Refactor virtual function"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~_RenameVirtualDialog();
		
		void m_checkListCandidatesOnContextMenu( wxMouseEvent &event )
		{
			m_checkListCandidates->PopupMenu( m_menuCandidates, event.GetPosition() );
		}
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class _ClassTemplateDialog
///////////////////////////////////////////////////////////////////////////////
class _ClassTemplateDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxTextCtrl* m_eName;
		wxCheckBox* m_cbMakeValid;
		wxStaticText* m_staticText2;
		wxTextCtrl* m_eDescription;
		wxNotebook* m_pNotebook;
		wxPanel* m_pageTempl;
		wxStaticText* m_staticText43;
		wxTextCtrl* m_txtTemplateName;
		wxStdDialogButtonSizer* bntSizer;
		wxButton* bntSizerOK;
		wxButton* bntSizerCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnInit( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void OnNameChange( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMakeValid( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOk( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		_ClassTemplateDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Class template properties"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~_ClassTemplateDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class _ClassInstanceDialog
///////////////////////////////////////////////////////////////////////////////
class _ClassInstanceDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText40;
		wxTextCtrl* m_textInstName;
		wxStaticText* m_staticText41;
		wxTextCtrl* m_textParameters;
		wxStaticText* m_staticText42;
		wxChoice* m_choiceType;
		wxStaticLine* m_staticline1;
		wxStdDialogButtonSizer* m_sdbSizer13;
		wxButton* m_sdbSizer13OK;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnInit( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void OnOk( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		_ClassInstanceDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Class instance"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~_ClassInstanceDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class _EnumElementDialog
///////////////////////////////////////////////////////////////////////////////
class _EnumElementDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxTextCtrl* m_eName;
		wxCheckBox* m_cbMakeValid;
		wxStaticText* m_staticText2;
		wxTextCtrl* m_eDescription;
		wxNotebook* m_pNotebook;
		wxPanel* m_pageAdv;
		wxStaticText* m_staticText11;
		wxTextCtrl* m_eValue;
		wxStdDialogButtonSizer* bntSizer;
		wxButton* bntSizerOK;
		wxButton* bntSizerCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnInit( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void OnNameChange( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMakeValid( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOk( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		_EnumElementDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Enumeration element properties"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~_EnumElementDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class _EnumDialog
///////////////////////////////////////////////////////////////////////////////
class _EnumDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxTextCtrl* m_eName;
		wxCheckBox* m_cbMakeValid;
		wxStaticText* m_staticText2;
		wxTextCtrl* m_eDescription;
		wxNotebook* m_pNotebook;
		wxPanel* m_pageAdv;
		wxStaticText* m_staticText11;
		wxTextCtrl* m_eInstName;
		wxStdDialogButtonSizer* bntSizer;
		wxButton* bntSizerOK;
		wxButton* bntSizerCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnInit( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void OnNameChange( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMakeValid( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOk( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		_EnumDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Enumeration properties"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~_EnumDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class _ClassDialog
///////////////////////////////////////////////////////////////////////////////
class _ClassDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxTextCtrl* m_eName;
		wxCheckBox* m_cbMakeValid;
		wxStaticText* m_staticText2;
		wxTextCtrl* m_eDescription;
		wxNotebook* m_pNotebook;
		wxPanel* m_pageAdv;
		wxCheckBox* m_chbGenerate;
		wxStdDialogButtonSizer* bntSizer;
		wxButton* bntSizerOK;
		wxButton* bntSizerCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnInit( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void OnNameChange( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMakeValid( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOk( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		_ClassDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Class properties"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~_ClassDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class _SubStateDialog
///////////////////////////////////////////////////////////////////////////////
class _SubStateDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxTextCtrl* m_eName;
		wxCheckBox* m_cbMakeValid;
		wxStaticText* m_staticText2;
		wxTextCtrl* m_eDescription;
		wxNotebook* m_pNotebook;
		wxPanel* m_pageAdv;
		wxCheckBox* m_chbStoreRetVal;
		wxStdDialogButtonSizer* bntSizer;
		wxButton* bntSizerOK;
		wxButton* bntSizerCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnInit( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void OnNameChange( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMakeValid( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOk( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		_SubStateDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Sub machine properties"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~_SubStateDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class _AggregationDialog
///////////////////////////////////////////////////////////////////////////////
class _AggregationDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxTextCtrl* m_eName;
		wxCheckBox* m_cbMakeValid;
		wxStaticText* m_staticText2;
		wxTextCtrl* m_eDescription;
		wxNotebook* m_pNotebook;
		wxPanel* m_pageAdv;
		wxCheckBox* m_chbIncludeClass;
		wxStaticText* m_staticText55;
		wxChoice* m_chAccess;
		wxStdDialogButtonSizer* bntSizer;
		wxButton* bntSizerOK;
		wxButton* bntSizerCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnInit( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void OnNameChange( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMakeValid( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOk( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		_AggregationDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Aggregation properties"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~_AggregationDialog();
	
};

#endif //__GUI_H__
