///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  6 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUI_PROJECTBASE_H__
#define __GUI_PROJECTBASE_H__

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
#include <wx/filepicker.h>
#include <wx/button.h>
#include <wx/choice.h>
#include <wx/notebook.h>
#include <wx/gbsizer.h>
#include <wx/dialog.h>
#include <wx/statbox.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>
#include <wx/listctrl.h>
#include <wx/stc/stc.h>
#include <wx/menu.h>
#include <wx/checklst.h>
#include <wx/gauge.h>

///////////////////////////////////////////////////////////////////////////

#define IDC_TRANSDLG_PROPGRID 1000
#define IDM_SELECT_ALL 1001
#define IDM_DESELECT_ALL 1002

///////////////////////////////////////////////////////////////////////////////
/// Class _DiagramDialog
///////////////////////////////////////////////////////////////////////////////
class _DiagramDialog : public wxDialog 
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
		wxCheckBox* m_cbGenerate;
		wxPanel* m_pageGen;
		wxStaticText* m_staticText14;
		wxFilePickerCtrl* m_fpOutputFile;
		wxButton* m_btnReset;
		wxStaticText* m_staticText15;
		wxStaticText* m_staticText16;
		wxChoice* m_chGenerator;
		wxChoice* m_chAlgorithm;
		wxStdDialogButtonSizer* bntSizer;
		wxButton* bntSizerOK;
		wxButton* bntSizerCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnInit( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void OnNameChange( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMakeValid( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnReset( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnGeneratorChange( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOk( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		_DiagramDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Diagram properties"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~_DiagramDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class _CodeLinkDialog
///////////////////////////////////////////////////////////////////////////////
class _CodeLinkDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxTextCtrl* m_eName;
		wxStaticText* m_stOriginal;
		wxButton* btnEditOrig;
		wxNotebook* m_pNotebook;
		wxPanel* m_pageAdv;
		wxStdDialogButtonSizer* bntSizer;
		wxButton* bntSizerOK;
		wxButton* bntSizerCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnInit( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void OnEditOriginal( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOk( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		_CodeLinkDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Code link properties"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 400,380 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~_CodeLinkDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class _FunctionLinkDialog
///////////////////////////////////////////////////////////////////////////////
class _FunctionLinkDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxTextCtrl* m_eName;
		wxStaticText* m_stOriginal;
		wxButton* btnEditOrig;
		wxNotebook* m_pNotebook;
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
		
		_FunctionLinkDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Function link properties"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 400,380 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~_FunctionLinkDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class _FunctionDialog
///////////////////////////////////////////////////////////////////////////////
class _FunctionDialog : public wxDialog 
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
		wxCheckBox* m_chbInline;
		wxStaticText* m_staticText461;
		wxChoice* m_chImplementation;
		wxStaticText* m_staticText431;
		wxChoice* m_chFcnModifier;
		wxPanel* m_pageRetVal;
		wxStaticText* m_staticText43;
		wxChoice* m_chModifier;
		wxStaticText* m_staticText44;
		wxChoice* m_chDataType;
		wxStaticText* m_staticText45;
		wxChoice* m_chValueType;
		wxPanel* m_pageUserDataType;
		wxStaticText* m_staticText46;
		wxTextCtrl* m_eTypeName;
		wxStaticText* m_staticText48;
		wxChoice* m_chDefinitionPlace;
		wxStaticText* m_staticText47;
		wxFilePickerCtrl* m_fpDefinitionFile;
		wxPanel* m_pageParams;
		wxListCtrl* m_lstParams;
		wxButton* m_btnAdd;
		wxButton* m_btnEdit;
		wxButton* m_btnRemove;
		wxButton* m_btnMoveUp;
		wxButton* m_btnMoveDown;
		wxPanel* m_pageEditor;
		wxChoice* m_chEditedField;
		wxStyledTextCtrl* m_sciEditor;
		wxStdDialogButtonSizer* bntSizer;
		wxButton* bntSizerOK;
		wxButton* bntSizerCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnInit( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void OnNameChange( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMakeValid( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateUserDataType( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnUpdateDefinitionFile( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnParamActivated( wxListEvent& event ) { event.Skip(); }
		virtual void OnAddClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEditClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateParamButtons( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnRemoveClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMoveUpClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMoveDownClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEditorChoice( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEditorKillFocus( wxFocusEvent& event ) { event.Skip(); }
		virtual void OnUpdateEditor( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnCancel( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOk( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		_FunctionDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Function properties"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~_FunctionDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class _VariableDialog
///////////////////////////////////////////////////////////////////////////////
class _VariableDialog : public wxDialog 
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
		wxStaticText* m_staticText43;
		wxChoice* m_chModifier;
		wxStaticText* m_staticText44;
		wxChoice* m_chDataType;
		wxStaticText* m_staticText45;
		wxChoice* m_chValueType;
		wxStaticText* m_staticText431;
		wxTextCtrl* m_eDefVal;
		wxPanel* m_pageUserDataType;
		wxStaticText* m_staticText46;
		wxTextCtrl* m_eTypeName;
		wxStaticText* m_staticText48;
		wxChoice* m_chDefinitionPlace;
		wxStaticText* m_staticText47;
		wxFilePickerCtrl* m_fpDefinitionFile;
		wxPanel* m_pageEditor;
		wxStyledTextCtrl* m_sciEditor;
		wxStdDialogButtonSizer* bntSizer;
		wxButton* bntSizerOK;
		wxButton* bntSizerCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnInit( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void OnNameChange( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMakeValid( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateUserDataType( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnUpdateDefinitionFile( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnUpdateEditor( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnOk( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		_VariableDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Variable properties"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~_VariableDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class _ChoiceDialog
///////////////////////////////////////////////////////////////////////////////
class _ChoiceDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_stextComment;
		wxChoice* m_chChoice;
		wxStdDialogButtonSizer* btnSizer;
		wxButton* btnSizerOK;
	
	public:
		
		_ChoiceDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Select a choice"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE ); 
		~_ChoiceDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class _ElementDialog
///////////////////////////////////////////////////////////////////////////////
class _ElementDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxTextCtrl* m_eName;
		wxCheckBox* m_cbMakeValid;
		wxStaticText* m_staticText2;
		wxTextCtrl* m_eDescription;
		wxStdDialogButtonSizer* bntSizer;
		wxButton* bntSizerOK;
		wxButton* bntSizerCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnInit( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void OnNameChange( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMakeValid( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOk( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		_ElementDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Diagram element properties"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~_ElementDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class _UpdateCodeDialog
///////////////////////////////////////////////////////////////////////////////
class _UpdateCodeDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText;
		wxCheckListBox* m_checkListCodeItems;
		wxMenu* m_menuChecklist;
		wxStaticText* m_staticText33;
		wxStyledTextCtrl* m_scintillaCode;
		wxButton* m_btnPrev;
		wxButton* m_btnNext;
		wxButton* m_btnCancel;
		wxButton* m_btnUpdate;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnInit( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void OnChangeCodeitem( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSelectAll( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDeselectAll( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPrevious( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNext( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCancel( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdate( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		_UpdateCodeDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Update code references"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 400,380 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~_UpdateCodeDialog();
		
		void m_checkListCodeItemsOnContextMenu( wxMouseEvent &event )
		{
			m_checkListCodeItems->PopupMenu( m_menuChecklist, event.GetPosition() );
		}
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class _ScopedElementDialog
///////////////////////////////////////////////////////////////////////////////
class _ScopedElementDialog : public wxDialog 
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
		wxStaticText* m_staticText43;
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
		
		_ScopedElementDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Diagram element properties"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~_ScopedElementDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class _ProgressDialog
///////////////////////////////////////////////////////////////////////////////
class _ProgressDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_stLabel;
		wxGauge* m_gaProgress;
	
	public:
		
		_ProgressDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Progress..."), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDIALOG_NO_PARENT|wxSTAY_ON_TOP ); 
		~_ProgressDialog();
	
};

#endif //__GUI_PROJECTBASE_H__
