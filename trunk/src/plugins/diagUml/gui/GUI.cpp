///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  6 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wx_pch.h"

#include "GUI.h"

///////////////////////////////////////////////////////////////////////////

_CodeDialog::_CodeDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 460,430 ), wxDefaultSize );
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	wxGridBagSizer* controlSizer;
	controlSizer = new wxGridBagSizer( 0, 0 );
	controlSizer->SetFlexibleDirection( wxBOTH );
	controlSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Name (must be valid language identifier);"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	controlSizer->Add( m_staticText1, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxBoxSizer* nameSizer;
	nameSizer = new wxBoxSizer( wxHORIZONTAL );
	
	m_eName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_eName->SetMaxLength( 0 ); 
	nameSizer->Add( m_eName, 1, wxALL|wxEXPAND, 5 );
	
	m_cbMakeValid = new wxCheckBox( this, wxID_ANY, wxT("Make valid"), wxDefaultPosition, wxDefaultSize, 0 );
	nameSizer->Add( m_cbMakeValid, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	controlSizer->Add( nameSizer, wxGBPosition( 1, 0 ), wxGBSpan( 1, 2 ), wxEXPAND, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Description:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	controlSizer->Add( m_staticText2, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_eDescription = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 400,100 ), wxTE_MULTILINE );
	m_eDescription->SetMaxLength( 0 ); 
	m_eDescription->SetMinSize( wxSize( 400,100 ) );
	
	controlSizer->Add( m_eDescription, wxGBPosition( 3, 0 ), wxGBSpan( 1, 2 ), wxEXPAND|wxALL, 5 );
	
	m_pNotebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_pNotebook->SetMinSize( wxSize( -1,200 ) );
	
	m_pageAdv = new wxPanel( m_pNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* advSizer;
	advSizer = new wxBoxSizer( wxVERTICAL );
	
	m_cbInline = new wxCheckBox( m_pageAdv, wxID_ANY, wxT("Inline code"), wxDefaultPosition, wxDefaultSize, 0 );
	advSizer->Add( m_cbInline, 0, wxALL, 5 );
	
	
	m_pageAdv->SetSizer( advSizer );
	m_pageAdv->Layout();
	advSizer->Fit( m_pageAdv );
	m_pNotebook->AddPage( m_pageAdv, wxT("Advanced"), true );
	m_pageEditor = new wxPanel( m_pNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* editorSizer;
	editorSizer = new wxBoxSizer( wxVERTICAL );
	
	m_sciEditor = new wxStyledTextCtrl( m_pageEditor, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, wxEmptyString );
	m_sciEditor->SetUseTabs( true );
	m_sciEditor->SetTabWidth( 4 );
	m_sciEditor->SetIndent( 4 );
	m_sciEditor->SetTabIndents( true );
	m_sciEditor->SetBackSpaceUnIndents( true );
	m_sciEditor->SetViewEOL( false );
	m_sciEditor->SetViewWhiteSpace( false );
	m_sciEditor->SetMarginWidth( 2, 0 );
	m_sciEditor->SetIndentationGuides( true );
	m_sciEditor->SetMarginType( 1, wxSTC_MARGIN_SYMBOL );
	m_sciEditor->SetMarginMask( 1, wxSTC_MASK_FOLDERS );
	m_sciEditor->SetMarginWidth( 1, 16);
	m_sciEditor->SetMarginSensitive( 1, true );
	m_sciEditor->SetProperty( wxT("fold"), wxT("1") );
	m_sciEditor->SetFoldFlags( wxSTC_FOLDFLAG_LINEBEFORE_CONTRACTED | wxSTC_FOLDFLAG_LINEAFTER_CONTRACTED );
	m_sciEditor->SetMarginType( 0, wxSTC_MARGIN_NUMBER );
	m_sciEditor->SetMarginWidth( 0, m_sciEditor->TextWidth( wxSTC_STYLE_LINENUMBER, wxT("_99999") ) );
	{
		wxFont font = wxFont( 9, 70, 90, 90, false, wxEmptyString );
		m_sciEditor->StyleSetFont( wxSTC_STYLE_DEFAULT, font );
	}
	m_sciEditor->MarkerDefine( wxSTC_MARKNUM_FOLDER, wxSTC_MARK_BOXPLUS );
	m_sciEditor->MarkerSetBackground( wxSTC_MARKNUM_FOLDER, wxColour( wxT("BLACK") ) );
	m_sciEditor->MarkerSetForeground( wxSTC_MARKNUM_FOLDER, wxColour( wxT("WHITE") ) );
	m_sciEditor->MarkerDefine( wxSTC_MARKNUM_FOLDEROPEN, wxSTC_MARK_BOXMINUS );
	m_sciEditor->MarkerSetBackground( wxSTC_MARKNUM_FOLDEROPEN, wxColour( wxT("BLACK") ) );
	m_sciEditor->MarkerSetForeground( wxSTC_MARKNUM_FOLDEROPEN, wxColour( wxT("WHITE") ) );
	m_sciEditor->MarkerDefine( wxSTC_MARKNUM_FOLDERSUB, wxSTC_MARK_EMPTY );
	m_sciEditor->MarkerDefine( wxSTC_MARKNUM_FOLDEREND, wxSTC_MARK_BOXPLUS );
	m_sciEditor->MarkerSetBackground( wxSTC_MARKNUM_FOLDEREND, wxColour( wxT("BLACK") ) );
	m_sciEditor->MarkerSetForeground( wxSTC_MARKNUM_FOLDEREND, wxColour( wxT("WHITE") ) );
	m_sciEditor->MarkerDefine( wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_BOXMINUS );
	m_sciEditor->MarkerSetBackground( wxSTC_MARKNUM_FOLDEROPENMID, wxColour( wxT("BLACK") ) );
	m_sciEditor->MarkerSetForeground( wxSTC_MARKNUM_FOLDEROPENMID, wxColour( wxT("WHITE") ) );
	m_sciEditor->MarkerDefine( wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_EMPTY );
	m_sciEditor->MarkerDefine( wxSTC_MARKNUM_FOLDERTAIL, wxSTC_MARK_EMPTY );
	m_sciEditor->SetSelBackground( true, wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHT ) );
	m_sciEditor->SetSelForeground( true, wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHTTEXT ) );
	m_sciEditor->SetFont( wxFont( 9, 70, 90, 90, false, wxEmptyString ) );
	m_sciEditor->SetMinSize( wxSize( 400,100 ) );
	
	editorSizer->Add( m_sciEditor, 1, wxEXPAND | wxALL, 5 );
	
	
	m_pageEditor->SetSizer( editorSizer );
	m_pageEditor->Layout();
	editorSizer->Fit( m_pageEditor );
	m_pNotebook->AddPage( m_pageEditor, wxT("Editor"), false );
	
	controlSizer->Add( m_pNotebook, wxGBPosition( 4, 0 ), wxGBSpan( 1, 2 ), wxEXPAND | wxALL, 5 );
	
	bntSizer = new wxStdDialogButtonSizer();
	bntSizerOK = new wxButton( this, wxID_OK );
	bntSizer->AddButton( bntSizerOK );
	bntSizerCancel = new wxButton( this, wxID_CANCEL );
	bntSizer->AddButton( bntSizerCancel );
	bntSizer->Realize();
	
	controlSizer->Add( bntSizer, wxGBPosition( 5, 0 ), wxGBSpan( 1, 2 ), wxALIGN_RIGHT|wxEXPAND|wxBOTTOM|wxRIGHT, 5 );
	
	
	controlSizer->AddGrowableCol( 0 );
	controlSizer->AddGrowableRow( 4 );
	
	mainSizer->Add( controlSizer, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( mainSizer );
	this->Layout();
	mainSizer->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _CodeDialog::OnInit ) );
	m_eName->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( _CodeDialog::OnNameChange ), NULL, this );
	m_cbMakeValid->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _CodeDialog::OnMakeValid ), NULL, this );
	bntSizerOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _CodeDialog::OnOk ), NULL, this );
}

_CodeDialog::~_CodeDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _CodeDialog::OnInit ) );
	m_eName->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( _CodeDialog::OnNameChange ), NULL, this );
	m_cbMakeValid->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _CodeDialog::OnMakeValid ), NULL, this );
	bntSizerOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _CodeDialog::OnOk ), NULL, this );
	
}

_StateActionDialog::_StateActionDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 460,430 ), wxDefaultSize );
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	wxGridBagSizer* controlSizer;
	controlSizer = new wxGridBagSizer( 0, 0 );
	controlSizer->SetFlexibleDirection( wxBOTH );
	controlSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Name (must be valid language identifier);"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	controlSizer->Add( m_staticText1, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxBoxSizer* nameSizer;
	nameSizer = new wxBoxSizer( wxHORIZONTAL );
	
	m_eName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_eName->SetMaxLength( 0 ); 
	nameSizer->Add( m_eName, 1, wxALL|wxEXPAND, 5 );
	
	m_cbMakeValid = new wxCheckBox( this, wxID_ANY, wxT("Make valid"), wxDefaultPosition, wxDefaultSize, 0 );
	nameSizer->Add( m_cbMakeValid, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	controlSizer->Add( nameSizer, wxGBPosition( 1, 0 ), wxGBSpan( 1, 2 ), wxEXPAND, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Description:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	controlSizer->Add( m_staticText2, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_eDescription = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 400,100 ), wxTE_MULTILINE );
	m_eDescription->SetMaxLength( 0 ); 
	m_eDescription->SetMinSize( wxSize( 400,100 ) );
	
	controlSizer->Add( m_eDescription, wxGBPosition( 3, 0 ), wxGBSpan( 1, 2 ), wxEXPAND|wxALL, 5 );
	
	m_pNotebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_pNotebook->SetMinSize( wxSize( -1,200 ) );
	
	m_pageAdv = new wxPanel( m_pNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* advSizer;
	advSizer = new wxBoxSizer( wxVERTICAL );
	
	m_cbInline = new wxCheckBox( m_pageAdv, wxID_ANY, wxT("Inline code"), wxDefaultPosition, wxDefaultSize, 0 );
	advSizer->Add( m_cbInline, 0, wxALL, 5 );
	
	m_staticText17 = new wxStaticText( m_pageAdv, wxID_ANY, wxT("Type:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText17->Wrap( -1 );
	advSizer->Add( m_staticText17, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxString m_chTypeChoices[] = { wxT("Entry action"), wxT("Exit action") };
	int m_chTypeNChoices = sizeof( m_chTypeChoices ) / sizeof( wxString );
	m_chType = new wxChoice( m_pageAdv, wxID_ANY, wxDefaultPosition, wxSize( 200,-1 ), m_chTypeNChoices, m_chTypeChoices, 0 );
	m_chType->SetSelection( 0 );
	m_chType->SetMinSize( wxSize( 200,-1 ) );
	
	advSizer->Add( m_chType, 0, wxALL|wxEXPAND, 5 );
	
	
	m_pageAdv->SetSizer( advSizer );
	m_pageAdv->Layout();
	advSizer->Fit( m_pageAdv );
	m_pNotebook->AddPage( m_pageAdv, wxT("Advanced"), true );
	m_pageEditor = new wxPanel( m_pNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* editorSizer;
	editorSizer = new wxBoxSizer( wxVERTICAL );
	
	m_sciEditor = new wxStyledTextCtrl( m_pageEditor, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, wxEmptyString );
	m_sciEditor->SetUseTabs( true );
	m_sciEditor->SetTabWidth( 4 );
	m_sciEditor->SetIndent( 4 );
	m_sciEditor->SetTabIndents( true );
	m_sciEditor->SetBackSpaceUnIndents( true );
	m_sciEditor->SetViewEOL( false );
	m_sciEditor->SetViewWhiteSpace( false );
	m_sciEditor->SetMarginWidth( 2, 0 );
	m_sciEditor->SetIndentationGuides( true );
	m_sciEditor->SetMarginType( 1, wxSTC_MARGIN_SYMBOL );
	m_sciEditor->SetMarginMask( 1, wxSTC_MASK_FOLDERS );
	m_sciEditor->SetMarginWidth( 1, 16);
	m_sciEditor->SetMarginSensitive( 1, true );
	m_sciEditor->SetProperty( wxT("fold"), wxT("1") );
	m_sciEditor->SetFoldFlags( wxSTC_FOLDFLAG_LINEBEFORE_CONTRACTED | wxSTC_FOLDFLAG_LINEAFTER_CONTRACTED );
	m_sciEditor->SetMarginType( 0, wxSTC_MARGIN_NUMBER );
	m_sciEditor->SetMarginWidth( 0, m_sciEditor->TextWidth( wxSTC_STYLE_LINENUMBER, wxT("_99999") ) );
	{
		wxFont font = wxFont( 9, 70, 90, 90, false, wxEmptyString );
		m_sciEditor->StyleSetFont( wxSTC_STYLE_DEFAULT, font );
	}
	m_sciEditor->MarkerDefine( wxSTC_MARKNUM_FOLDER, wxSTC_MARK_BOXPLUS );
	m_sciEditor->MarkerSetBackground( wxSTC_MARKNUM_FOLDER, wxColour( wxT("BLACK") ) );
	m_sciEditor->MarkerSetForeground( wxSTC_MARKNUM_FOLDER, wxColour( wxT("WHITE") ) );
	m_sciEditor->MarkerDefine( wxSTC_MARKNUM_FOLDEROPEN, wxSTC_MARK_BOXMINUS );
	m_sciEditor->MarkerSetBackground( wxSTC_MARKNUM_FOLDEROPEN, wxColour( wxT("BLACK") ) );
	m_sciEditor->MarkerSetForeground( wxSTC_MARKNUM_FOLDEROPEN, wxColour( wxT("WHITE") ) );
	m_sciEditor->MarkerDefine( wxSTC_MARKNUM_FOLDERSUB, wxSTC_MARK_EMPTY );
	m_sciEditor->MarkerDefine( wxSTC_MARKNUM_FOLDEREND, wxSTC_MARK_BOXPLUS );
	m_sciEditor->MarkerSetBackground( wxSTC_MARKNUM_FOLDEREND, wxColour( wxT("BLACK") ) );
	m_sciEditor->MarkerSetForeground( wxSTC_MARKNUM_FOLDEREND, wxColour( wxT("WHITE") ) );
	m_sciEditor->MarkerDefine( wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_BOXMINUS );
	m_sciEditor->MarkerSetBackground( wxSTC_MARKNUM_FOLDEROPENMID, wxColour( wxT("BLACK") ) );
	m_sciEditor->MarkerSetForeground( wxSTC_MARKNUM_FOLDEROPENMID, wxColour( wxT("WHITE") ) );
	m_sciEditor->MarkerDefine( wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_EMPTY );
	m_sciEditor->MarkerDefine( wxSTC_MARKNUM_FOLDERTAIL, wxSTC_MARK_EMPTY );
	m_sciEditor->SetSelBackground( true, wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHT ) );
	m_sciEditor->SetSelForeground( true, wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHTTEXT ) );
	m_sciEditor->SetFont( wxFont( 9, 70, 90, 90, false, wxEmptyString ) );
	m_sciEditor->SetMinSize( wxSize( 400,100 ) );
	
	editorSizer->Add( m_sciEditor, 1, wxEXPAND | wxALL, 5 );
	
	
	m_pageEditor->SetSizer( editorSizer );
	m_pageEditor->Layout();
	editorSizer->Fit( m_pageEditor );
	m_pNotebook->AddPage( m_pageEditor, wxT("Editor"), false );
	
	controlSizer->Add( m_pNotebook, wxGBPosition( 4, 0 ), wxGBSpan( 1, 2 ), wxEXPAND | wxALL, 5 );
	
	bntSizer = new wxStdDialogButtonSizer();
	bntSizerOK = new wxButton( this, wxID_OK );
	bntSizer->AddButton( bntSizerOK );
	bntSizerCancel = new wxButton( this, wxID_CANCEL );
	bntSizer->AddButton( bntSizerCancel );
	bntSizer->Realize();
	
	controlSizer->Add( bntSizer, wxGBPosition( 5, 0 ), wxGBSpan( 1, 2 ), wxALIGN_RIGHT|wxEXPAND|wxBOTTOM|wxRIGHT, 5 );
	
	
	controlSizer->AddGrowableCol( 0 );
	controlSizer->AddGrowableRow( 4 );
	
	mainSizer->Add( controlSizer, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( mainSizer );
	this->Layout();
	mainSizer->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _StateActionDialog::OnInit ) );
	m_eName->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( _StateActionDialog::OnNameChange ), NULL, this );
	m_cbMakeValid->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _StateActionDialog::OnMakeValid ), NULL, this );
	bntSizerOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _StateActionDialog::OnOk ), NULL, this );
}

_StateActionDialog::~_StateActionDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _StateActionDialog::OnInit ) );
	m_eName->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( _StateActionDialog::OnNameChange ), NULL, this );
	m_cbMakeValid->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _StateActionDialog::OnMakeValid ), NULL, this );
	bntSizerOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _StateActionDialog::OnOk ), NULL, this );
	
}

_EventDialog::_EventDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 400,430 ), wxDefaultSize );
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	wxGridBagSizer* controlSizer;
	controlSizer = new wxGridBagSizer( 0, 0 );
	controlSizer->SetFlexibleDirection( wxBOTH );
	controlSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Name (must be valid language identifier);"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	controlSizer->Add( m_staticText1, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxBoxSizer* nameSizer;
	nameSizer = new wxBoxSizer( wxHORIZONTAL );
	
	m_eName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_eName->SetMaxLength( 0 ); 
	nameSizer->Add( m_eName, 1, wxALL|wxEXPAND, 5 );
	
	m_cbMakeValid = new wxCheckBox( this, wxID_ANY, wxT("Make valid"), wxDefaultPosition, wxDefaultSize, 0 );
	nameSizer->Add( m_cbMakeValid, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	controlSizer->Add( nameSizer, wxGBPosition( 1, 0 ), wxGBSpan( 1, 2 ), wxEXPAND, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Description:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	controlSizer->Add( m_staticText2, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_eDescription = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 400,100 ), wxTE_MULTILINE );
	m_eDescription->SetMaxLength( 0 ); 
	m_eDescription->SetMinSize( wxSize( 400,100 ) );
	
	controlSizer->Add( m_eDescription, wxGBPosition( 3, 0 ), wxGBSpan( 1, 2 ), wxEXPAND|wxALL, 5 );
	
	m_pNotebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_pNotebook->SetMinSize( wxSize( -1,200 ) );
	
	m_pageAdv = new wxPanel( m_pNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* advSizer;
	advSizer = new wxBoxSizer( wxVERTICAL );
	
	m_staticText11 = new wxStaticText( m_pageAdv, wxID_ANY, wxT("Event type:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	advSizer->Add( m_staticText11, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxString m_chEventTypeChoices[] = { wxT("Normal event"), wxT("Critical event") };
	int m_chEventTypeNChoices = sizeof( m_chEventTypeChoices ) / sizeof( wxString );
	m_chEventType = new wxChoice( m_pageAdv, wxID_ANY, wxDefaultPosition, wxSize( 200,-1 ), m_chEventTypeNChoices, m_chEventTypeChoices, 0 );
	m_chEventType->SetSelection( 0 );
	advSizer->Add( m_chEventType, 0, wxALL|wxEXPAND, 5 );
	
	
	m_pageAdv->SetSizer( advSizer );
	m_pageAdv->Layout();
	advSizer->Fit( m_pageAdv );
	m_pNotebook->AddPage( m_pageAdv, wxT("Advanced"), true );
	
	controlSizer->Add( m_pNotebook, wxGBPosition( 4, 0 ), wxGBSpan( 1, 2 ), wxEXPAND | wxALL, 5 );
	
	bntSizer = new wxStdDialogButtonSizer();
	bntSizerOK = new wxButton( this, wxID_OK );
	bntSizer->AddButton( bntSizerOK );
	bntSizerCancel = new wxButton( this, wxID_CANCEL );
	bntSizer->AddButton( bntSizerCancel );
	bntSizer->Realize();
	
	controlSizer->Add( bntSizer, wxGBPosition( 5, 0 ), wxGBSpan( 1, 2 ), wxALIGN_RIGHT|wxEXPAND|wxBOTTOM|wxRIGHT, 5 );
	
	
	controlSizer->AddGrowableCol( 0 );
	controlSizer->AddGrowableRow( 4 );
	
	mainSizer->Add( controlSizer, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( mainSizer );
	this->Layout();
	mainSizer->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _EventDialog::OnInit ) );
	m_eName->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( _EventDialog::OnNameChange ), NULL, this );
	m_cbMakeValid->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _EventDialog::OnMakeValid ), NULL, this );
	m_chEventType->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( _EventDialog::OnTypeChange ), NULL, this );
	bntSizerOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _EventDialog::OnOk ), NULL, this );
}

_EventDialog::~_EventDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _EventDialog::OnInit ) );
	m_eName->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( _EventDialog::OnNameChange ), NULL, this );
	m_cbMakeValid->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _EventDialog::OnMakeValid ), NULL, this );
	m_chEventType->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( _EventDialog::OnTypeChange ), NULL, this );
	bntSizerOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _EventDialog::OnOk ), NULL, this );
	
}

_ActionLinkDialog::_ActionLinkDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 400,380 ), wxDefaultSize );
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	wxGridBagSizer* controlSizer;
	controlSizer = new wxGridBagSizer( 0, 0 );
	controlSizer->SetFlexibleDirection( wxBOTH );
	controlSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Link name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	controlSizer->Add( m_staticText1, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_eName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_eName->SetMaxLength( 0 ); 
	controlSizer->Add( m_eName, wxGBPosition( 1, 0 ), wxGBSpan( 1, 2 ), wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* originalSizer;
	originalSizer = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Original code item:") ), wxHORIZONTAL );
	
	m_stOriginal = new wxStaticText( this, wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stOriginal->Wrap( -1 );
	m_stOriginal->SetFont( wxFont( 9, 74, 90, 92, false, wxT("Sans") ) );
	
	originalSizer->Add( m_stOriginal, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnEditOrig = new wxButton( this, wxID_ANY, wxT("Edit original"), wxDefaultPosition, wxDefaultSize, 0 );
	originalSizer->Add( btnEditOrig, 0, wxRIGHT|wxLEFT, 5 );
	
	
	controlSizer->Add( originalSizer, wxGBPosition( 2, 0 ), wxGBSpan( 1, 2 ), wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_pNotebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_pNotebook->SetMinSize( wxSize( -1,200 ) );
	
	m_pageAdv = new wxPanel( m_pNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* advSizer;
	advSizer = new wxBoxSizer( wxVERTICAL );
	
	m_staticText17 = new wxStaticText( m_pageAdv, wxID_ANY, wxT("Type:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText17->Wrap( -1 );
	advSizer->Add( m_staticText17, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxString m_chTypeChoices[] = { wxT("Entry action"), wxT("Exit action") };
	int m_chTypeNChoices = sizeof( m_chTypeChoices ) / sizeof( wxString );
	m_chType = new wxChoice( m_pageAdv, wxID_ANY, wxDefaultPosition, wxSize( 200,-1 ), m_chTypeNChoices, m_chTypeChoices, 0 );
	m_chType->SetSelection( 0 );
	m_chType->SetMinSize( wxSize( 200,-1 ) );
	
	advSizer->Add( m_chType, 0, wxALL|wxEXPAND, 5 );
	
	
	m_pageAdv->SetSizer( advSizer );
	m_pageAdv->Layout();
	advSizer->Fit( m_pageAdv );
	m_pNotebook->AddPage( m_pageAdv, wxT("Advanced"), true );
	m_pageParametersMap = new wxPanel( m_pNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* paramSizer;
	paramSizer = new wxBoxSizer( wxVERTICAL );
	
	m_pgParams = new wxPropertyGrid(m_pageParametersMap, IDC_TRANSDLG_PROPGRID, wxDefaultPosition, wxDefaultSize, wxPG_BOLD_MODIFIED|wxPG_DEFAULT_STYLE);
	paramSizer->Add( m_pgParams, 1, wxEXPAND | wxALL, 5 );
	
	
	m_pageParametersMap->SetSizer( paramSizer );
	m_pageParametersMap->Layout();
	paramSizer->Fit( m_pageParametersMap );
	m_pNotebook->AddPage( m_pageParametersMap, wxT("Call parameters"), false );
	
	controlSizer->Add( m_pNotebook, wxGBPosition( 3, 0 ), wxGBSpan( 1, 2 ), wxEXPAND | wxALL, 5 );
	
	bntSizer = new wxStdDialogButtonSizer();
	bntSizerOK = new wxButton( this, wxID_OK );
	bntSizer->AddButton( bntSizerOK );
	bntSizerCancel = new wxButton( this, wxID_CANCEL );
	bntSizer->AddButton( bntSizerCancel );
	bntSizer->Realize();
	
	controlSizer->Add( bntSizer, wxGBPosition( 4, 0 ), wxGBSpan( 1, 2 ), wxALIGN_RIGHT|wxEXPAND|wxBOTTOM|wxRIGHT, 5 );
	
	
	controlSizer->AddGrowableCol( 0 );
	controlSizer->AddGrowableRow( 3 );
	
	mainSizer->Add( controlSizer, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( mainSizer );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _ActionLinkDialog::OnInit ) );
	btnEditOrig->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ActionLinkDialog::OnEditOriginal ), NULL, this );
	bntSizerOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ActionLinkDialog::OnOk ), NULL, this );
}

_ActionLinkDialog::~_ActionLinkDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _ActionLinkDialog::OnInit ) );
	btnEditOrig->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ActionLinkDialog::OnEditOriginal ), NULL, this );
	bntSizerOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ActionLinkDialog::OnOk ), NULL, this );
	
}

_ClassMemberLinkDialog::_ClassMemberLinkDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 400,380 ), wxDefaultSize );
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	wxGridBagSizer* controlSizer;
	controlSizer = new wxGridBagSizer( 0, 0 );
	controlSizer->SetFlexibleDirection( wxBOTH );
	controlSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Link name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	controlSizer->Add( m_staticText1, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_eName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_eName->SetMaxLength( 0 ); 
	controlSizer->Add( m_eName, wxGBPosition( 1, 0 ), wxGBSpan( 1, 2 ), wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* originalSizer;
	originalSizer = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Original code item:") ), wxHORIZONTAL );
	
	m_stOriginal = new wxStaticText( this, wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stOriginal->Wrap( -1 );
	m_stOriginal->SetFont( wxFont( 9, 74, 90, 92, false, wxT("Sans") ) );
	
	originalSizer->Add( m_stOriginal, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnEditOrig = new wxButton( this, wxID_ANY, wxT("Edit original"), wxDefaultPosition, wxDefaultSize, 0 );
	originalSizer->Add( btnEditOrig, 0, wxRIGHT|wxLEFT, 5 );
	
	
	controlSizer->Add( originalSizer, wxGBPosition( 2, 0 ), wxGBSpan( 1, 2 ), wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_pNotebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_pNotebook->SetMinSize( wxSize( -1,200 ) );
	
	m_pageAdv = new wxPanel( m_pNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* advSizer;
	advSizer = new wxBoxSizer( wxVERTICAL );
	
	m_staticText17 = new wxStaticText( m_pageAdv, wxID_ANY, wxT("Access:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText17->Wrap( -1 );
	advSizer->Add( m_staticText17, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxString m_chTypeChoices[] = { wxT("public"), wxT("protected"), wxT("private") };
	int m_chTypeNChoices = sizeof( m_chTypeChoices ) / sizeof( wxString );
	m_chType = new wxChoice( m_pageAdv, wxID_ANY, wxDefaultPosition, wxSize( 200,-1 ), m_chTypeNChoices, m_chTypeChoices, 0 );
	m_chType->SetSelection( 0 );
	m_chType->SetMinSize( wxSize( 200,-1 ) );
	
	advSizer->Add( m_chType, 0, wxALL|wxEXPAND, 5 );
	
	
	m_pageAdv->SetSizer( advSizer );
	m_pageAdv->Layout();
	advSizer->Fit( m_pageAdv );
	m_pNotebook->AddPage( m_pageAdv, wxT("Advanced"), true );
	
	controlSizer->Add( m_pNotebook, wxGBPosition( 3, 0 ), wxGBSpan( 1, 2 ), wxEXPAND | wxALL, 5 );
	
	bntSizer = new wxStdDialogButtonSizer();
	bntSizerOK = new wxButton( this, wxID_OK );
	bntSizer->AddButton( bntSizerOK );
	bntSizerCancel = new wxButton( this, wxID_CANCEL );
	bntSizer->AddButton( bntSizerCancel );
	bntSizer->Realize();
	
	controlSizer->Add( bntSizer, wxGBPosition( 4, 0 ), wxGBSpan( 1, 2 ), wxALIGN_RIGHT|wxEXPAND|wxBOTTOM|wxRIGHT, 5 );
	
	
	controlSizer->AddGrowableCol( 0 );
	controlSizer->AddGrowableRow( 3 );
	
	mainSizer->Add( controlSizer, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( mainSizer );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _ClassMemberLinkDialog::OnInit ) );
	btnEditOrig->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ClassMemberLinkDialog::OnEditOriginal ), NULL, this );
	bntSizerOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ClassMemberLinkDialog::OnOk ), NULL, this );
}

_ClassMemberLinkDialog::~_ClassMemberLinkDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _ClassMemberLinkDialog::OnInit ) );
	btnEditOrig->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ClassMemberLinkDialog::OnEditOriginal ), NULL, this );
	bntSizerOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ClassMemberLinkDialog::OnOk ), NULL, this );
	
}

_EventLinkDialog::_EventLinkDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 400,380 ), wxDefaultSize );
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	wxGridBagSizer* controlSizer;
	controlSizer = new wxGridBagSizer( 0, 0 );
	controlSizer->SetFlexibleDirection( wxBOTH );
	controlSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Link name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	controlSizer->Add( m_staticText1, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_eName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_eName->SetMaxLength( 0 ); 
	controlSizer->Add( m_eName, wxGBPosition( 1, 0 ), wxGBSpan( 1, 2 ), wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* originalSizer;
	originalSizer = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Original code item:") ), wxHORIZONTAL );
	
	m_stOriginal = new wxStaticText( this, wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stOriginal->Wrap( -1 );
	m_stOriginal->SetFont( wxFont( 9, 74, 90, 92, false, wxT("Sans") ) );
	
	originalSizer->Add( m_stOriginal, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnEditOrig = new wxButton( this, wxID_ANY, wxT("Edit original"), wxDefaultPosition, wxDefaultSize, 0 );
	originalSizer->Add( btnEditOrig, 0, wxRIGHT|wxLEFT, 5 );
	
	
	controlSizer->Add( originalSizer, wxGBPosition( 2, 0 ), wxGBSpan( 1, 2 ), wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_pNotebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_pNotebook->SetMinSize( wxSize( -1,200 ) );
	
	m_pageAdv = new wxPanel( m_pNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* advSizer;
	advSizer = new wxBoxSizer( wxVERTICAL );
	
	m_checkBoxClearFlag = new wxCheckBox( m_pageAdv, wxID_ANY, wxT("Clear event flag"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBoxClearFlag->SetToolTip( wxT("Clear event flag automatically") );
	
	advSizer->Add( m_checkBoxClearFlag, 0, wxALL, 5 );
	
	
	m_pageAdv->SetSizer( advSizer );
	m_pageAdv->Layout();
	advSizer->Fit( m_pageAdv );
	m_pNotebook->AddPage( m_pageAdv, wxT("Advanced"), true );
	
	controlSizer->Add( m_pNotebook, wxGBPosition( 3, 0 ), wxGBSpan( 1, 2 ), wxEXPAND | wxALL, 5 );
	
	bntSizer = new wxStdDialogButtonSizer();
	bntSizerOK = new wxButton( this, wxID_OK );
	bntSizer->AddButton( bntSizerOK );
	bntSizerCancel = new wxButton( this, wxID_CANCEL );
	bntSizer->AddButton( bntSizerCancel );
	bntSizer->Realize();
	
	controlSizer->Add( bntSizer, wxGBPosition( 4, 0 ), wxGBSpan( 1, 2 ), wxALIGN_RIGHT|wxEXPAND|wxBOTTOM|wxRIGHT, 5 );
	
	
	controlSizer->AddGrowableCol( 0 );
	controlSizer->AddGrowableRow( 3 );
	
	mainSizer->Add( controlSizer, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( mainSizer );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _EventLinkDialog::OnInit ) );
	btnEditOrig->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _EventLinkDialog::OnEditOriginal ), NULL, this );
	bntSizerOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _EventLinkDialog::OnOk ), NULL, this );
}

_EventLinkDialog::~_EventLinkDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _EventLinkDialog::OnInit ) );
	btnEditOrig->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _EventLinkDialog::OnEditOriginal ), NULL, this );
	bntSizerOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _EventLinkDialog::OnOk ), NULL, this );
	
}

_TransitionDialog::_TransitionDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 460,500 ), wxDefaultSize );
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	wxGridBagSizer* controlSizer;
	controlSizer = new wxGridBagSizer( 0, 0 );
	controlSizer->SetFlexibleDirection( wxBOTH );
	controlSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Name (must be valid language identifier);"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	controlSizer->Add( m_staticText1, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxBoxSizer* nameSizer;
	nameSizer = new wxBoxSizer( wxHORIZONTAL );
	
	m_eName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_eName->SetMaxLength( 0 ); 
	nameSizer->Add( m_eName, 1, wxALL|wxEXPAND, 5 );
	
	m_cbMakeValid = new wxCheckBox( this, wxID_ANY, wxT("Make valid"), wxDefaultPosition, wxDefaultSize, 0 );
	nameSizer->Add( m_cbMakeValid, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	controlSizer->Add( nameSizer, wxGBPosition( 1, 0 ), wxGBSpan( 1, 2 ), wxEXPAND, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Description:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	controlSizer->Add( m_staticText2, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_eDescription = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 450,100 ), wxTE_MULTILINE );
	m_eDescription->SetMaxLength( 0 ); 
	m_eDescription->SetMinSize( wxSize( 450,100 ) );
	
	controlSizer->Add( m_eDescription, wxGBPosition( 3, 0 ), wxGBSpan( 1, 2 ), wxEXPAND|wxALL, 5 );
	
	m_pNotebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_pNotebook->SetMinSize( wxSize( -1,200 ) );
	
	m_pageCondition = new wxPanel( m_pNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* conditionSizer;
	conditionSizer = new wxFlexGridSizer( 2, 2, 0, 0 );
	conditionSizer->AddGrowableCol( 1 );
	conditionSizer->SetFlexibleDirection( wxBOTH );
	conditionSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText51 = new wxStaticText( m_pageCondition, wxID_ANY, wxT("Condition:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText51->Wrap( -1 );
	conditionSizer->Add( m_staticText51, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_chConditionsChoices;
	m_chConditions = new wxChoice( m_pageCondition, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chConditionsChoices, 0 );
	m_chConditions->SetSelection( 0 );
	conditionSizer->Add( m_chConditions, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText52 = new wxStaticText( m_pageCondition, wxID_ANY, wxT("Priority:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText52->Wrap( -1 );
	conditionSizer->Add( m_staticText52, 0, wxBOTTOM|wxRIGHT|wxLEFT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_spinPriority = new wxSpinCtrl( m_pageCondition, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 255, 255 );
	conditionSizer->Add( m_spinPriority, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	m_pageCondition->SetSizer( conditionSizer );
	m_pageCondition->Layout();
	conditionSizer->Fit( m_pageCondition );
	m_pNotebook->AddPage( m_pageCondition, wxT("Condition"), true );
	m_pageActions = new wxPanel( m_pNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* actionsSizer;
	actionsSizer = new wxFlexGridSizer( 1, 3, 0, 0 );
	actionsSizer->AddGrowableCol( 0 );
	actionsSizer->AddGrowableCol( 2 );
	actionsSizer->AddGrowableRow( 0 );
	actionsSizer->SetFlexibleDirection( wxBOTH );
	actionsSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxBoxSizer* usedSizer;
	usedSizer = new wxBoxSizer( wxVERTICAL );
	
	m_staticText53 = new wxStaticText( m_pageActions, wxID_ANY, wxT("Used actions:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText53->Wrap( -1 );
	usedSizer->Add( m_staticText53, 0, wxALL, 5 );
	
	m_listUsed = new wxListBox( m_pageActions, IDC_USEDACTIONS, wxDefaultPosition, wxSize( -1,-1 ), 0, NULL, wxLB_MULTIPLE ); 
	m_listUsed->SetMinSize( wxSize( 150,-1 ) );
	
	m_menuUsed = new wxMenu();
	wxMenuItem* menuUsedSelectAll;
	menuUsedSelectAll = new wxMenuItem( m_menuUsed, IDM_TRANS_SELECTALL, wxString( wxT("Select all") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuUsed->Append( menuUsedSelectAll );
	
	wxMenuItem* menuUsedDeselectAll;
	menuUsedDeselectAll = new wxMenuItem( m_menuUsed, IDM_TRANS_DESELECTALL, wxString( wxT("Deselect all") ) , wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	menuUsedDeselectAll->SetBitmaps( wxNullBitmap );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	menuUsedDeselectAll->SetBitmap( wxNullBitmap );
	#endif
	m_menuUsed->Append( menuUsedDeselectAll );
	
	m_menuUsed->AppendSeparator();
	
	wxMenuItem* menuUsedClearAll;
	menuUsedClearAll = new wxMenuItem( m_menuUsed, IDM_TRANS_REMOVEALL, wxString( wxT("Remove all") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuUsed->Append( menuUsedClearAll );
	
	m_listUsed->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( _TransitionDialog::m_listUsedOnContextMenu ), NULL, this ); 
	
	usedSizer->Add( m_listUsed, 1, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	actionsSizer->Add( usedSizer, 1, wxEXPAND, 5 );
	
	wxBoxSizer* operationsSizer;
	operationsSizer = new wxBoxSizer( wxVERTICAL );
	
	
	operationsSizer->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_btnAdd = new wxButton( m_pageActions, wxID_ANY, wxT("<<"), wxDefaultPosition, wxDefaultSize, 0 );
	operationsSizer->Add( m_btnAdd, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_btnRemove = new wxButton( m_pageActions, wxID_ANY, wxT(">>"), wxDefaultPosition, wxDefaultSize, 0 );
	operationsSizer->Add( m_btnRemove, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_btnUp = new wxButton( m_pageActions, wxID_ANY, wxT("Up"), wxDefaultPosition, wxDefaultSize, 0 );
	operationsSizer->Add( m_btnUp, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_btnDown = new wxButton( m_pageActions, wxID_ANY, wxT("Down"), wxDefaultPosition, wxDefaultSize, 0 );
	operationsSizer->Add( m_btnDown, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	operationsSizer->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	actionsSizer->Add( operationsSizer, 1, wxEXPAND, 5 );
	
	wxBoxSizer* availableSizer;
	availableSizer = new wxBoxSizer( wxVERTICAL );
	
	m_staticText54 = new wxStaticText( m_pageActions, wxID_ANY, wxT("Available actions:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText54->Wrap( -1 );
	availableSizer->Add( m_staticText54, 0, wxALL, 5 );
	
	m_listAvailable = new wxListBox( m_pageActions, ICD_AVAILABLEACTIONS, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_MULTIPLE ); 
	m_listAvailable->SetMinSize( wxSize( 150,-1 ) );
	
	m_menuAvailable = new wxMenu();
	wxMenuItem* menuAvailableSelectAll;
	menuAvailableSelectAll = new wxMenuItem( m_menuAvailable, IDM_TRANS_SELECTALLAV, wxString( wxT("Select all") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuAvailable->Append( menuAvailableSelectAll );
	
	wxMenuItem* menuAvailableDeselectAll;
	menuAvailableDeselectAll = new wxMenuItem( m_menuAvailable, IDM_TRANS_DESELECTALLAV, wxString( wxT("Deselect all") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuAvailable->Append( menuAvailableDeselectAll );
	
	m_listAvailable->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( _TransitionDialog::m_listAvailableOnContextMenu ), NULL, this ); 
	
	availableSizer->Add( m_listAvailable, 1, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	actionsSizer->Add( availableSizer, 1, wxEXPAND, 5 );
	
	
	m_pageActions->SetSizer( actionsSizer );
	m_pageActions->Layout();
	actionsSizer->Fit( m_pageActions );
	m_pNotebook->AddPage( m_pageActions, wxT("Actions"), false );
	
	controlSizer->Add( m_pNotebook, wxGBPosition( 4, 0 ), wxGBSpan( 1, 2 ), wxEXPAND | wxALL, 5 );
	
	bntSizer = new wxStdDialogButtonSizer();
	bntSizerOK = new wxButton( this, wxID_OK );
	bntSizer->AddButton( bntSizerOK );
	bntSizerCancel = new wxButton( this, wxID_CANCEL );
	bntSizer->AddButton( bntSizerCancel );
	bntSizer->Realize();
	
	controlSizer->Add( bntSizer, wxGBPosition( 5, 0 ), wxGBSpan( 1, 2 ), wxALIGN_RIGHT|wxEXPAND|wxBOTTOM|wxRIGHT, 5 );
	
	
	controlSizer->AddGrowableCol( 0 );
	controlSizer->AddGrowableRow( 4 );
	
	mainSizer->Add( controlSizer, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( mainSizer );
	this->Layout();
	mainSizer->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _TransitionDialog::OnInit ) );
	m_eName->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( _TransitionDialog::OnNameChange ), NULL, this );
	m_cbMakeValid->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _TransitionDialog::OnMakeValid ), NULL, this );
	m_chConditions->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( _TransitionDialog::OnConditionChange ), NULL, this );
	this->Connect( menuUsedSelectAll->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _TransitionDialog::OnSelectAllUsed ) );
	this->Connect( menuUsedDeselectAll->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _TransitionDialog::OnDeselectAllUsed ) );
	this->Connect( menuUsedClearAll->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _TransitionDialog::OnRemoveAllUsed ) );
	m_btnAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _TransitionDialog::OnAdd ), NULL, this );
	m_btnAdd->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _TransitionDialog::OnUpdateAdd ), NULL, this );
	m_btnRemove->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _TransitionDialog::OnRemove ), NULL, this );
	m_btnRemove->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _TransitionDialog::OnUpdateRemove ), NULL, this );
	m_btnUp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _TransitionDialog::OnUp ), NULL, this );
	m_btnUp->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _TransitionDialog::OnUpdateUp ), NULL, this );
	m_btnDown->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _TransitionDialog::OnDown ), NULL, this );
	m_btnDown->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _TransitionDialog::OnUpdateDown ), NULL, this );
	this->Connect( menuAvailableSelectAll->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _TransitionDialog::OnSelectAllAvailable ) );
	this->Connect( menuAvailableDeselectAll->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _TransitionDialog::OnDeselectAllAvailable ) );
	bntSizerOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _TransitionDialog::OnOk ), NULL, this );
}

_TransitionDialog::~_TransitionDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _TransitionDialog::OnInit ) );
	m_eName->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( _TransitionDialog::OnNameChange ), NULL, this );
	m_cbMakeValid->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _TransitionDialog::OnMakeValid ), NULL, this );
	m_chConditions->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( _TransitionDialog::OnConditionChange ), NULL, this );
	this->Disconnect( IDM_TRANS_SELECTALL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _TransitionDialog::OnSelectAllUsed ) );
	this->Disconnect( IDM_TRANS_DESELECTALL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _TransitionDialog::OnDeselectAllUsed ) );
	this->Disconnect( IDM_TRANS_REMOVEALL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _TransitionDialog::OnRemoveAllUsed ) );
	m_btnAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _TransitionDialog::OnAdd ), NULL, this );
	m_btnAdd->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _TransitionDialog::OnUpdateAdd ), NULL, this );
	m_btnRemove->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _TransitionDialog::OnRemove ), NULL, this );
	m_btnRemove->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _TransitionDialog::OnUpdateRemove ), NULL, this );
	m_btnUp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _TransitionDialog::OnUp ), NULL, this );
	m_btnUp->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _TransitionDialog::OnUpdateUp ), NULL, this );
	m_btnDown->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _TransitionDialog::OnDown ), NULL, this );
	m_btnDown->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _TransitionDialog::OnUpdateDown ), NULL, this );
	this->Disconnect( IDM_TRANS_SELECTALLAV, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _TransitionDialog::OnSelectAllAvailable ) );
	this->Disconnect( IDM_TRANS_DESELECTALLAV, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _TransitionDialog::OnDeselectAllAvailable ) );
	bntSizerOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _TransitionDialog::OnOk ), NULL, this );
	
	delete m_menuUsed; 
	delete m_menuAvailable; 
}

_FinalStateDialog::_FinalStateDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 460,-1 ), wxDefaultSize );
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	wxGridBagSizer* controlSizer;
	controlSizer = new wxGridBagSizer( 0, 0 );
	controlSizer->SetFlexibleDirection( wxBOTH );
	controlSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Name (must be valid language identifier);"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	controlSizer->Add( m_staticText1, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxBoxSizer* nameSizer;
	nameSizer = new wxBoxSizer( wxHORIZONTAL );
	
	m_eName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_eName->SetMaxLength( 0 ); 
	nameSizer->Add( m_eName, 1, wxALL|wxEXPAND, 5 );
	
	m_cbMakeValid = new wxCheckBox( this, wxID_ANY, wxT("Make valid"), wxDefaultPosition, wxDefaultSize, 0 );
	nameSizer->Add( m_cbMakeValid, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	controlSizer->Add( nameSizer, wxGBPosition( 1, 0 ), wxGBSpan( 1, 2 ), wxEXPAND, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Description:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	controlSizer->Add( m_staticText2, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_eDescription = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 400,100 ), wxTE_MULTILINE );
	m_eDescription->SetMaxLength( 0 ); 
	m_eDescription->SetMinSize( wxSize( 400,100 ) );
	
	controlSizer->Add( m_eDescription, wxGBPosition( 3, 0 ), wxGBSpan( 1, 2 ), wxEXPAND|wxALL, 5 );
	
	m_pNotebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxSize( -1,150 ), 0 );
	m_pNotebook->SetMinSize( wxSize( -1,150 ) );
	
	m_pageAdv = new wxPanel( m_pNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* advSizer;
	advSizer = new wxBoxSizer( wxVERTICAL );
	
	m_staticText56 = new wxStaticText( m_pageAdv, wxID_ANY, wxT("Return value:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText56->Wrap( -1 );
	advSizer->Add( m_staticText56, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxBoxSizer* bSizer51;
	bSizer51 = new wxBoxSizer( wxHORIZONTAL );
	
	m_textRetValue = new wxTextCtrl( m_pageAdv, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textRetValue->SetMaxLength( 0 ); 
	bSizer51->Add( m_textRetValue, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_btnDefault = new wxButton( m_pageAdv, wxID_ANY, wxT("Default"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer51->Add( m_btnDefault, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	advSizer->Add( bSizer51, 0, wxEXPAND, 5 );
	
	
	m_pageAdv->SetSizer( advSizer );
	m_pageAdv->Layout();
	advSizer->Fit( m_pageAdv );
	m_pNotebook->AddPage( m_pageAdv, wxT("Advanced"), true );
	
	controlSizer->Add( m_pNotebook, wxGBPosition( 4, 0 ), wxGBSpan( 1, 2 ), wxEXPAND | wxALL, 5 );
	
	bntSizer = new wxStdDialogButtonSizer();
	bntSizerOK = new wxButton( this, wxID_OK );
	bntSizer->AddButton( bntSizerOK );
	bntSizerCancel = new wxButton( this, wxID_CANCEL );
	bntSizer->AddButton( bntSizerCancel );
	bntSizer->Realize();
	
	controlSizer->Add( bntSizer, wxGBPosition( 5, 0 ), wxGBSpan( 1, 2 ), wxALIGN_RIGHT|wxEXPAND|wxBOTTOM|wxRIGHT, 5 );
	
	
	controlSizer->AddGrowableCol( 0 );
	controlSizer->AddGrowableRow( 4 );
	
	mainSizer->Add( controlSizer, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( mainSizer );
	this->Layout();
	mainSizer->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _FinalStateDialog::OnInit ) );
	m_eName->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( _FinalStateDialog::OnNameChange ), NULL, this );
	m_cbMakeValid->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _FinalStateDialog::OnMakeValid ), NULL, this );
	m_btnDefault->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _FinalStateDialog::OnDefault ), NULL, this );
	bntSizerOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _FinalStateDialog::OnOk ), NULL, this );
}

_FinalStateDialog::~_FinalStateDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _FinalStateDialog::OnInit ) );
	m_eName->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( _FinalStateDialog::OnNameChange ), NULL, this );
	m_cbMakeValid->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _FinalStateDialog::OnMakeValid ), NULL, this );
	m_btnDefault->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _FinalStateDialog::OnDefault ), NULL, this );
	bntSizerOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _FinalStateDialog::OnOk ), NULL, this );
	
}

_CompStateDialog::_CompStateDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 460,500 ), wxDefaultSize );
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	wxGridBagSizer* controlSizer;
	controlSizer = new wxGridBagSizer( 0, 0 );
	controlSizer->SetFlexibleDirection( wxBOTH );
	controlSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Name (must be valid language identifier);"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	controlSizer->Add( m_staticText1, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxBoxSizer* nameSizer;
	nameSizer = new wxBoxSizer( wxHORIZONTAL );
	
	m_eName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_eName->SetMaxLength( 0 ); 
	nameSizer->Add( m_eName, 1, wxALL|wxEXPAND, 5 );
	
	m_cbMakeValid = new wxCheckBox( this, wxID_ANY, wxT("Make valid"), wxDefaultPosition, wxDefaultSize, 0 );
	nameSizer->Add( m_cbMakeValid, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	controlSizer->Add( nameSizer, wxGBPosition( 1, 0 ), wxGBSpan( 1, 2 ), wxEXPAND, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Description:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	controlSizer->Add( m_staticText2, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_eDescription = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 450,100 ), wxTE_MULTILINE );
	m_eDescription->SetMaxLength( 0 ); 
	m_eDescription->SetMinSize( wxSize( 450,100 ) );
	
	controlSizer->Add( m_eDescription, wxGBPosition( 3, 0 ), wxGBSpan( 1, 2 ), wxEXPAND|wxALL, 5 );
	
	m_pNotebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_pNotebook->SetMinSize( wxSize( -1,200 ) );
	
	m_pageActions = new wxPanel( m_pNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* actionsSizer;
	actionsSizer = new wxFlexGridSizer( 1, 3, 0, 0 );
	actionsSizer->AddGrowableCol( 0 );
	actionsSizer->AddGrowableCol( 2 );
	actionsSizer->AddGrowableRow( 0 );
	actionsSizer->SetFlexibleDirection( wxBOTH );
	actionsSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxBoxSizer* usedSizer;
	usedSizer = new wxBoxSizer( wxVERTICAL );
	
	m_notebookActions = new wxNotebook( m_pageActions, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_pageEntry = new wxPanel( m_notebookActions, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer64;
	bSizer64 = new wxBoxSizer( wxVERTICAL );
	
	m_listUsedEntry = new wxListBox( m_pageEntry, IDC_USEDACTIONS, wxDefaultPosition, wxSize( -1,-1 ), 0, NULL, wxLB_MULTIPLE ); 
	m_listUsedEntry->SetMinSize( wxSize( 150,-1 ) );
	
	m_menuUsed = new wxMenu();
	wxMenuItem* menuUsedSelectAll;
	menuUsedSelectAll = new wxMenuItem( m_menuUsed, IDM_TRANS_SELECTALL, wxString( wxT("Select all") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuUsed->Append( menuUsedSelectAll );
	
	wxMenuItem* menuUsedDeselectAll;
	menuUsedDeselectAll = new wxMenuItem( m_menuUsed, IDM_TRANS_DESELECTALL, wxString( wxT("Deselect all") ) , wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	menuUsedDeselectAll->SetBitmaps( wxNullBitmap );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	menuUsedDeselectAll->SetBitmap( wxNullBitmap );
	#endif
	m_menuUsed->Append( menuUsedDeselectAll );
	
	m_menuUsed->AppendSeparator();
	
	wxMenuItem* menuUsedClearAll;
	menuUsedClearAll = new wxMenuItem( m_menuUsed, IDM_TRANS_REMOVEALL, wxString( wxT("Remove all") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuUsed->Append( menuUsedClearAll );
	
	m_listUsedEntry->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( _CompStateDialog::m_listUsedEntryOnContextMenu ), NULL, this ); 
	
	bSizer64->Add( m_listUsedEntry, 1, wxEXPAND, 5 );
	
	
	m_pageEntry->SetSizer( bSizer64 );
	m_pageEntry->Layout();
	bSizer64->Fit( m_pageEntry );
	m_notebookActions->AddPage( m_pageEntry, wxT("Entry"), true );
	m_pageExit = new wxPanel( m_notebookActions, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer65;
	bSizer65 = new wxBoxSizer( wxVERTICAL );
	
	m_listUsedExit = new wxListBox( m_pageExit, IDC_USEDACTIONS, wxDefaultPosition, wxSize( -1,-1 ), 0, NULL, wxLB_MULTIPLE ); 
	m_listUsedExit->SetMinSize( wxSize( 150,-1 ) );
	
	m_menuUsedExit = new wxMenu();
	wxMenuItem* menuUsedSelectAllExit;
	menuUsedSelectAllExit = new wxMenuItem( m_menuUsedExit, IDM_TRANS_SELECTALL, wxString( wxT("Select all") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuUsedExit->Append( menuUsedSelectAllExit );
	
	wxMenuItem* menuUsedDeselectAllExit;
	menuUsedDeselectAllExit = new wxMenuItem( m_menuUsedExit, IDM_TRANS_DESELECTALL, wxString( wxT("Deselect all") ) , wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	menuUsedDeselectAllExit->SetBitmaps( wxNullBitmap );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	menuUsedDeselectAllExit->SetBitmap( wxNullBitmap );
	#endif
	m_menuUsedExit->Append( menuUsedDeselectAllExit );
	
	m_menuUsedExit->AppendSeparator();
	
	wxMenuItem* menuUsedClearAllExit;
	menuUsedClearAllExit = new wxMenuItem( m_menuUsedExit, IDM_TRANS_REMOVEALL, wxString( wxT("Remove all") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuUsedExit->Append( menuUsedClearAllExit );
	
	m_listUsedExit->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( _CompStateDialog::m_listUsedExitOnContextMenu ), NULL, this ); 
	
	bSizer65->Add( m_listUsedExit, 1, wxEXPAND, 5 );
	
	
	m_pageExit->SetSizer( bSizer65 );
	m_pageExit->Layout();
	bSizer65->Fit( m_pageExit );
	m_notebookActions->AddPage( m_pageExit, wxT("Exit"), false );
	
	usedSizer->Add( m_notebookActions, 1, wxEXPAND | wxALL, 5 );
	
	
	actionsSizer->Add( usedSizer, 1, wxEXPAND, 5 );
	
	wxBoxSizer* operationsSizer;
	operationsSizer = new wxBoxSizer( wxVERTICAL );
	
	
	operationsSizer->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_btnAdd = new wxButton( m_pageActions, wxID_ANY, wxT("<<"), wxDefaultPosition, wxDefaultSize, 0 );
	operationsSizer->Add( m_btnAdd, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_btnRemove = new wxButton( m_pageActions, wxID_ANY, wxT(">>"), wxDefaultPosition, wxDefaultSize, 0 );
	operationsSizer->Add( m_btnRemove, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_btnUp = new wxButton( m_pageActions, wxID_ANY, wxT("Up"), wxDefaultPosition, wxDefaultSize, 0 );
	operationsSizer->Add( m_btnUp, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_btnDown = new wxButton( m_pageActions, wxID_ANY, wxT("Down"), wxDefaultPosition, wxDefaultSize, 0 );
	operationsSizer->Add( m_btnDown, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	operationsSizer->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	actionsSizer->Add( operationsSizer, 1, wxEXPAND, 5 );
	
	wxBoxSizer* availableSizer;
	availableSizer = new wxBoxSizer( wxVERTICAL );
	
	m_staticText54 = new wxStaticText( m_pageActions, wxID_ANY, wxT("Available actions:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText54->Wrap( -1 );
	availableSizer->Add( m_staticText54, 0, wxALL, 5 );
	
	m_listAvailable = new wxListBox( m_pageActions, ICD_AVAILABLEACTIONS, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_MULTIPLE ); 
	m_listAvailable->SetMinSize( wxSize( 150,-1 ) );
	
	m_menuAvailable = new wxMenu();
	wxMenuItem* menuAvailableSelectAll;
	menuAvailableSelectAll = new wxMenuItem( m_menuAvailable, IDM_TRANS_SELECTALLAV, wxString( wxT("Select all") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuAvailable->Append( menuAvailableSelectAll );
	
	wxMenuItem* menuAvailableDeselectAll;
	menuAvailableDeselectAll = new wxMenuItem( m_menuAvailable, IDM_TRANS_DESELECTALLAV, wxString( wxT("Deselect all") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuAvailable->Append( menuAvailableDeselectAll );
	
	m_listAvailable->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( _CompStateDialog::m_listAvailableOnContextMenu ), NULL, this ); 
	
	availableSizer->Add( m_listAvailable, 1, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	actionsSizer->Add( availableSizer, 1, wxEXPAND, 5 );
	
	
	m_pageActions->SetSizer( actionsSizer );
	m_pageActions->Layout();
	actionsSizer->Fit( m_pageActions );
	m_pNotebook->AddPage( m_pageActions, wxT("Actions"), false );
	
	controlSizer->Add( m_pNotebook, wxGBPosition( 4, 0 ), wxGBSpan( 1, 2 ), wxEXPAND | wxALL, 5 );
	
	bntSizer = new wxStdDialogButtonSizer();
	bntSizerOK = new wxButton( this, wxID_OK );
	bntSizer->AddButton( bntSizerOK );
	bntSizerCancel = new wxButton( this, wxID_CANCEL );
	bntSizer->AddButton( bntSizerCancel );
	bntSizer->Realize();
	
	controlSizer->Add( bntSizer, wxGBPosition( 5, 0 ), wxGBSpan( 1, 2 ), wxALIGN_RIGHT|wxEXPAND|wxBOTTOM|wxRIGHT, 5 );
	
	
	controlSizer->AddGrowableCol( 0 );
	controlSizer->AddGrowableRow( 4 );
	
	mainSizer->Add( controlSizer, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( mainSizer );
	this->Layout();
	mainSizer->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _CompStateDialog::OnInit ) );
	m_eName->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( _CompStateDialog::OnNameChange ), NULL, this );
	m_cbMakeValid->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _CompStateDialog::OnMakeValid ), NULL, this );
	this->Connect( menuUsedSelectAll->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _CompStateDialog::OnSelectAllUsed ) );
	this->Connect( menuUsedDeselectAll->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _CompStateDialog::OnDeselectAllUsed ) );
	this->Connect( menuUsedClearAll->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _CompStateDialog::OnRemoveAllUsed ) );
	this->Connect( menuUsedSelectAllExit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _CompStateDialog::OnSelectAllUsed ) );
	this->Connect( menuUsedDeselectAllExit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _CompStateDialog::OnDeselectAllUsed ) );
	this->Connect( menuUsedClearAllExit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _CompStateDialog::OnRemoveAllUsed ) );
	m_btnAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _CompStateDialog::OnAdd ), NULL, this );
	m_btnAdd->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _CompStateDialog::OnUpdateAdd ), NULL, this );
	m_btnRemove->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _CompStateDialog::OnRemove ), NULL, this );
	m_btnRemove->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _CompStateDialog::OnUpdateRemove ), NULL, this );
	m_btnUp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _CompStateDialog::OnUp ), NULL, this );
	m_btnUp->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _CompStateDialog::OnUpdateUp ), NULL, this );
	m_btnDown->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _CompStateDialog::OnDown ), NULL, this );
	m_btnDown->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _CompStateDialog::OnUpdateDown ), NULL, this );
	this->Connect( menuAvailableSelectAll->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _CompStateDialog::OnSelectAllAvailable ) );
	this->Connect( menuAvailableDeselectAll->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _CompStateDialog::OnDeselectAllAvailable ) );
	bntSizerOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _CompStateDialog::OnOk ), NULL, this );
}

_CompStateDialog::~_CompStateDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _CompStateDialog::OnInit ) );
	m_eName->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( _CompStateDialog::OnNameChange ), NULL, this );
	m_cbMakeValid->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _CompStateDialog::OnMakeValid ), NULL, this );
	this->Disconnect( IDM_TRANS_SELECTALL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _CompStateDialog::OnSelectAllUsed ) );
	this->Disconnect( IDM_TRANS_DESELECTALL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _CompStateDialog::OnDeselectAllUsed ) );
	this->Disconnect( IDM_TRANS_REMOVEALL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _CompStateDialog::OnRemoveAllUsed ) );
	this->Disconnect( IDM_TRANS_SELECTALL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _CompStateDialog::OnSelectAllUsed ) );
	this->Disconnect( IDM_TRANS_DESELECTALL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _CompStateDialog::OnDeselectAllUsed ) );
	this->Disconnect( IDM_TRANS_REMOVEALL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _CompStateDialog::OnRemoveAllUsed ) );
	m_btnAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _CompStateDialog::OnAdd ), NULL, this );
	m_btnAdd->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _CompStateDialog::OnUpdateAdd ), NULL, this );
	m_btnRemove->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _CompStateDialog::OnRemove ), NULL, this );
	m_btnRemove->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _CompStateDialog::OnUpdateRemove ), NULL, this );
	m_btnUp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _CompStateDialog::OnUp ), NULL, this );
	m_btnUp->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _CompStateDialog::OnUpdateUp ), NULL, this );
	m_btnDown->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _CompStateDialog::OnDown ), NULL, this );
	m_btnDown->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _CompStateDialog::OnUpdateDown ), NULL, this );
	this->Disconnect( IDM_TRANS_SELECTALLAV, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _CompStateDialog::OnSelectAllAvailable ) );
	this->Disconnect( IDM_TRANS_DESELECTALLAV, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _CompStateDialog::OnDeselectAllAvailable ) );
	bntSizerOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _CompStateDialog::OnOk ), NULL, this );
	
	delete m_menuUsed; 
	delete m_menuUsedExit; 
	delete m_menuAvailable; 
}

_ConstructorDialog::_ConstructorDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 460,450 ), wxDefaultSize );
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	wxGridBagSizer* controlSizer;
	controlSizer = new wxGridBagSizer( 0, 0 );
	controlSizer->SetFlexibleDirection( wxBOTH );
	controlSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Name (must be valid language identifier):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	controlSizer->Add( m_staticText1, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxBoxSizer* nameSizer;
	nameSizer = new wxBoxSizer( wxHORIZONTAL );
	
	m_eName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_eName->SetMaxLength( 0 ); 
	nameSizer->Add( m_eName, 1, wxALL|wxEXPAND, 5 );
	
	m_cbMakeValid = new wxCheckBox( this, wxID_ANY, wxT("Make valid"), wxDefaultPosition, wxDefaultSize, 0 );
	nameSizer->Add( m_cbMakeValid, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	controlSizer->Add( nameSizer, wxGBPosition( 1, 0 ), wxGBSpan( 1, 2 ), wxEXPAND, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Description:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	controlSizer->Add( m_staticText2, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_eDescription = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 400,100 ), wxTE_MULTILINE );
	m_eDescription->SetMaxLength( 0 ); 
	m_eDescription->SetMinSize( wxSize( 400,100 ) );
	
	controlSizer->Add( m_eDescription, wxGBPosition( 3, 0 ), wxGBSpan( 1, 2 ), wxEXPAND|wxALL, 5 );
	
	m_pNotebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_pNotebook->SetMinSize( wxSize( -1,200 ) );
	
	m_pageAdv = new wxPanel( m_pNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* advSizer;
	advSizer = new wxFlexGridSizer( 3, 2, 0, 0 );
	advSizer->AddGrowableCol( 1 );
	advSizer->SetFlexibleDirection( wxBOTH );
	advSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText461 = new wxStaticText( m_pageAdv, wxID_ANY, wxT("Implementation:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText461->Wrap( -1 );
	advSizer->Add( m_staticText461, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_chImplementationChoices[] = { wxT("<user-defined-code>") };
	int m_chImplementationNChoices = sizeof( m_chImplementationChoices ) / sizeof( wxString );
	m_chImplementation = new wxChoice( m_pageAdv, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chImplementationNChoices, m_chImplementationChoices, 0 );
	m_chImplementation->SetSelection( 0 );
	advSizer->Add( m_chImplementation, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText431 = new wxStaticText( m_pageAdv, wxID_ANY, wxT("Function modifier:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText431->Wrap( -1 );
	advSizer->Add( m_staticText431, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	wxArrayString m_chFcnModifierChoices;
	m_chFcnModifier = new wxChoice( m_pageAdv, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chFcnModifierChoices, 0 );
	m_chFcnModifier->SetSelection( 0 );
	advSizer->Add( m_chFcnModifier, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	m_pageAdv->SetSizer( advSizer );
	m_pageAdv->Layout();
	advSizer->Fit( m_pageAdv );
	m_pNotebook->AddPage( m_pageAdv, wxT("Advanced"), true );
	m_pageParams = new wxPanel( m_pNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* paramsSizer;
	paramsSizer = new wxBoxSizer( wxVERTICAL );
	
	wxGridBagSizer* gbSizer;
	gbSizer = new wxGridBagSizer( 0, 0 );
	gbSizer->SetFlexibleDirection( wxBOTH );
	gbSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_lstParams = new wxListCtrl( m_pageParams, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	gbSizer->Add( m_lstParams, wxGBPosition( 0, 0 ), wxGBSpan( 5, 1 ), wxALL|wxEXPAND, 5 );
	
	m_btnAdd = new wxButton( m_pageParams, wxID_ANY, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer->Add( m_btnAdd, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	m_btnEdit = new wxButton( m_pageParams, wxID_ANY, wxT("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer->Add( m_btnEdit, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_btnRemove = new wxButton( m_pageParams, wxID_ANY, wxT("Remove"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer->Add( m_btnRemove, wxGBPosition( 2, 1 ), wxGBSpan( 1, 1 ), wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_btnMoveUp = new wxButton( m_pageParams, wxID_ANY, wxT("Move up"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer->Add( m_btnMoveUp, wxGBPosition( 3, 1 ), wxGBSpan( 1, 1 ), wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_btnMoveDown = new wxButton( m_pageParams, wxID_ANY, wxT("Move down"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer->Add( m_btnMoveDown, wxGBPosition( 4, 1 ), wxGBSpan( 1, 1 ), wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	gbSizer->AddGrowableCol( 0 );
	gbSizer->AddGrowableRow( 4 );
	
	paramsSizer->Add( gbSizer, 1, wxEXPAND, 5 );
	
	
	m_pageParams->SetSizer( paramsSizer );
	m_pageParams->Layout();
	paramsSizer->Fit( m_pageParams );
	m_pNotebook->AddPage( m_pageParams, wxT("Parameters"), false );
	m_pageBases = new wxPanel( m_pNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* basesSizer;
	basesSizer = new wxBoxSizer( wxHORIZONTAL );
	
	wxArrayString m_checkListBasesChoices;
	m_checkListBases = new wxCheckListBox( m_pageBases, wxID_ANY, wxDefaultPosition, wxSize( 150,-1 ), m_checkListBasesChoices, 0 );
	m_checkListBases->SetMinSize( wxSize( 150,-1 ) );
	
	basesSizer->Add( m_checkListBases, 0, wxEXPAND|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	wxBoxSizer* callParamsSizer;
	callParamsSizer = new wxBoxSizer( wxVERTICAL );
	
	m_staticText80 = new wxStaticText( m_pageBases, wxID_ANY, wxT("Call parameters for base constructor:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText80->Wrap( -1 );
	callParamsSizer->Add( m_staticText80, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxArrayString m_chBaseConstructorChoices;
	m_chBaseConstructor = new wxChoice( m_pageBases, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chBaseConstructorChoices, 0 );
	m_chBaseConstructor->SetSelection( 0 );
	callParamsSizer->Add( m_chBaseConstructor, 0, wxTOP|wxRIGHT|wxLEFT|wxEXPAND, 5 );
	
	m_pgParams = new wxPropertyGrid(m_pageBases, IDC_TRANSDLG_PROPGRID, wxDefaultPosition, wxDefaultSize, wxPG_BOLD_MODIFIED|wxPG_DEFAULT_STYLE);
	callParamsSizer->Add( m_pgParams, 1, wxEXPAND | wxALL, 5 );
	
	
	basesSizer->Add( callParamsSizer, 1, wxEXPAND, 5 );
	
	
	m_pageBases->SetSizer( basesSizer );
	m_pageBases->Layout();
	basesSizer->Fit( m_pageBases );
	m_pNotebook->AddPage( m_pageBases, wxT("Base classes"), false );
	m_pageEditor = new wxPanel( m_pNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* editorSizer;
	editorSizer = new wxBoxSizer( wxVERTICAL );
	
	m_sciEditor = new wxStyledTextCtrl( m_pageEditor, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), 0, wxEmptyString );
	m_sciEditor->SetUseTabs( true );
	m_sciEditor->SetTabWidth( 4 );
	m_sciEditor->SetIndent( 4 );
	m_sciEditor->SetTabIndents( true );
	m_sciEditor->SetBackSpaceUnIndents( true );
	m_sciEditor->SetViewEOL( false );
	m_sciEditor->SetViewWhiteSpace( false );
	m_sciEditor->SetMarginWidth( 2, 0 );
	m_sciEditor->SetIndentationGuides( true );
	m_sciEditor->SetMarginType( 1, wxSTC_MARGIN_SYMBOL );
	m_sciEditor->SetMarginMask( 1, wxSTC_MASK_FOLDERS );
	m_sciEditor->SetMarginWidth( 1, 16);
	m_sciEditor->SetMarginSensitive( 1, true );
	m_sciEditor->SetProperty( wxT("fold"), wxT("1") );
	m_sciEditor->SetFoldFlags( wxSTC_FOLDFLAG_LINEBEFORE_CONTRACTED | wxSTC_FOLDFLAG_LINEAFTER_CONTRACTED );
	m_sciEditor->SetMarginType( 0, wxSTC_MARGIN_NUMBER );
	m_sciEditor->SetMarginWidth( 0, m_sciEditor->TextWidth( wxSTC_STYLE_LINENUMBER, wxT("_99999") ) );
	{
		wxFont font = wxFont( 9, 70, 90, 90, false, wxEmptyString );
		m_sciEditor->StyleSetFont( wxSTC_STYLE_DEFAULT, font );
	}
	m_sciEditor->MarkerDefine( wxSTC_MARKNUM_FOLDER, wxSTC_MARK_BOXPLUS );
	m_sciEditor->MarkerSetBackground( wxSTC_MARKNUM_FOLDER, wxColour( wxT("BLACK") ) );
	m_sciEditor->MarkerSetForeground( wxSTC_MARKNUM_FOLDER, wxColour( wxT("WHITE") ) );
	m_sciEditor->MarkerDefine( wxSTC_MARKNUM_FOLDEROPEN, wxSTC_MARK_BOXMINUS );
	m_sciEditor->MarkerSetBackground( wxSTC_MARKNUM_FOLDEROPEN, wxColour( wxT("BLACK") ) );
	m_sciEditor->MarkerSetForeground( wxSTC_MARKNUM_FOLDEROPEN, wxColour( wxT("WHITE") ) );
	m_sciEditor->MarkerDefine( wxSTC_MARKNUM_FOLDERSUB, wxSTC_MARK_EMPTY );
	m_sciEditor->MarkerDefine( wxSTC_MARKNUM_FOLDEREND, wxSTC_MARK_BOXPLUS );
	m_sciEditor->MarkerSetBackground( wxSTC_MARKNUM_FOLDEREND, wxColour( wxT("BLACK") ) );
	m_sciEditor->MarkerSetForeground( wxSTC_MARKNUM_FOLDEREND, wxColour( wxT("WHITE") ) );
	m_sciEditor->MarkerDefine( wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_BOXMINUS );
	m_sciEditor->MarkerSetBackground( wxSTC_MARKNUM_FOLDEROPENMID, wxColour( wxT("BLACK") ) );
	m_sciEditor->MarkerSetForeground( wxSTC_MARKNUM_FOLDEROPENMID, wxColour( wxT("WHITE") ) );
	m_sciEditor->MarkerDefine( wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_EMPTY );
	m_sciEditor->MarkerDefine( wxSTC_MARKNUM_FOLDERTAIL, wxSTC_MARK_EMPTY );
	m_sciEditor->SetSelBackground( true, wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHT ) );
	m_sciEditor->SetSelForeground( true, wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHTTEXT ) );
	m_sciEditor->SetFont( wxFont( 9, 70, 90, 90, false, wxEmptyString ) );
	m_sciEditor->SetMinSize( wxSize( 400,100 ) );
	
	editorSizer->Add( m_sciEditor, 1, wxEXPAND | wxALL, 5 );
	
	
	m_pageEditor->SetSizer( editorSizer );
	m_pageEditor->Layout();
	editorSizer->Fit( m_pageEditor );
	m_pNotebook->AddPage( m_pageEditor, wxT("Editor"), false );
	
	controlSizer->Add( m_pNotebook, wxGBPosition( 4, 0 ), wxGBSpan( 1, 2 ), wxEXPAND | wxALL, 5 );
	
	bntSizer = new wxStdDialogButtonSizer();
	bntSizerOK = new wxButton( this, wxID_OK );
	bntSizer->AddButton( bntSizerOK );
	bntSizerCancel = new wxButton( this, wxID_CANCEL );
	bntSizer->AddButton( bntSizerCancel );
	bntSizer->Realize();
	
	controlSizer->Add( bntSizer, wxGBPosition( 5, 0 ), wxGBSpan( 1, 2 ), wxALIGN_RIGHT|wxEXPAND|wxBOTTOM|wxRIGHT, 5 );
	
	
	controlSizer->AddGrowableCol( 0 );
	controlSizer->AddGrowableRow( 4 );
	
	mainSizer->Add( controlSizer, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( mainSizer );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _ConstructorDialog::OnInit ) );
	m_eName->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( _ConstructorDialog::OnNameChange ), NULL, this );
	m_cbMakeValid->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _ConstructorDialog::OnMakeValid ), NULL, this );
	m_lstParams->Connect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( _ConstructorDialog::OnParamActivated ), NULL, this );
	m_btnAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ConstructorDialog::OnAddClick ), NULL, this );
	m_btnEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ConstructorDialog::OnEditClick ), NULL, this );
	m_btnEdit->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _ConstructorDialog::OnUpdateParamButtons ), NULL, this );
	m_btnRemove->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ConstructorDialog::OnRemoveClick ), NULL, this );
	m_btnRemove->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _ConstructorDialog::OnUpdateParamButtons ), NULL, this );
	m_btnMoveUp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ConstructorDialog::OnMoveUpClick ), NULL, this );
	m_btnMoveUp->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _ConstructorDialog::OnUpdateParamButtons ), NULL, this );
	m_btnMoveDown->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ConstructorDialog::OnMoveDownClick ), NULL, this );
	m_btnMoveDown->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _ConstructorDialog::OnUpdateParamButtons ), NULL, this );
	m_checkListBases->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( _ConstructorDialog::OnBaseClassSelected ), NULL, this );
	m_chBaseConstructor->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( _ConstructorDialog::OnBaseConstructorChange ), NULL, this );
	m_sciEditor->Connect( wxEVT_CHAR, wxKeyEventHandler( _ConstructorDialog::OnEditorTextChange ), NULL, this );
	m_sciEditor->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _ConstructorDialog::OnUpdateEditor ), NULL, this );
	bntSizerCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ConstructorDialog::OnCancel ), NULL, this );
	bntSizerOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ConstructorDialog::OnOk ), NULL, this );
}

_ConstructorDialog::~_ConstructorDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _ConstructorDialog::OnInit ) );
	m_eName->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( _ConstructorDialog::OnNameChange ), NULL, this );
	m_cbMakeValid->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _ConstructorDialog::OnMakeValid ), NULL, this );
	m_lstParams->Disconnect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( _ConstructorDialog::OnParamActivated ), NULL, this );
	m_btnAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ConstructorDialog::OnAddClick ), NULL, this );
	m_btnEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ConstructorDialog::OnEditClick ), NULL, this );
	m_btnEdit->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _ConstructorDialog::OnUpdateParamButtons ), NULL, this );
	m_btnRemove->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ConstructorDialog::OnRemoveClick ), NULL, this );
	m_btnRemove->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _ConstructorDialog::OnUpdateParamButtons ), NULL, this );
	m_btnMoveUp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ConstructorDialog::OnMoveUpClick ), NULL, this );
	m_btnMoveUp->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _ConstructorDialog::OnUpdateParamButtons ), NULL, this );
	m_btnMoveDown->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ConstructorDialog::OnMoveDownClick ), NULL, this );
	m_btnMoveDown->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _ConstructorDialog::OnUpdateParamButtons ), NULL, this );
	m_checkListBases->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( _ConstructorDialog::OnBaseClassSelected ), NULL, this );
	m_chBaseConstructor->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( _ConstructorDialog::OnBaseConstructorChange ), NULL, this );
	m_sciEditor->Disconnect( wxEVT_CHAR, wxKeyEventHandler( _ConstructorDialog::OnEditorTextChange ), NULL, this );
	m_sciEditor->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _ConstructorDialog::OnUpdateEditor ), NULL, this );
	bntSizerCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ConstructorDialog::OnCancel ), NULL, this );
	bntSizerOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ConstructorDialog::OnOk ), NULL, this );
	
}

_DestructorDialog::_DestructorDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 460,450 ), wxDefaultSize );
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	wxGridBagSizer* controlSizer;
	controlSizer = new wxGridBagSizer( 0, 0 );
	controlSizer->SetFlexibleDirection( wxBOTH );
	controlSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Name (must be valid language identifier):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	controlSizer->Add( m_staticText1, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxBoxSizer* nameSizer;
	nameSizer = new wxBoxSizer( wxHORIZONTAL );
	
	m_eName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_eName->SetMaxLength( 0 ); 
	nameSizer->Add( m_eName, 1, wxALL|wxEXPAND, 5 );
	
	m_cbMakeValid = new wxCheckBox( this, wxID_ANY, wxT("Make valid"), wxDefaultPosition, wxDefaultSize, 0 );
	nameSizer->Add( m_cbMakeValid, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	controlSizer->Add( nameSizer, wxGBPosition( 1, 0 ), wxGBSpan( 1, 2 ), wxEXPAND, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Description:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	controlSizer->Add( m_staticText2, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_eDescription = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 400,100 ), wxTE_MULTILINE );
	m_eDescription->SetMaxLength( 0 ); 
	m_eDescription->SetMinSize( wxSize( 400,100 ) );
	
	controlSizer->Add( m_eDescription, wxGBPosition( 3, 0 ), wxGBSpan( 1, 2 ), wxEXPAND|wxALL, 5 );
	
	m_pNotebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_pNotebook->SetMinSize( wxSize( -1,200 ) );
	
	m_pageAdv = new wxPanel( m_pNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* advSizer;
	advSizer = new wxFlexGridSizer( 3, 2, 0, 0 );
	advSizer->AddGrowableCol( 1 );
	advSizer->SetFlexibleDirection( wxBOTH );
	advSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText461 = new wxStaticText( m_pageAdv, wxID_ANY, wxT("Implementation:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText461->Wrap( -1 );
	advSizer->Add( m_staticText461, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_chImplementationChoices[] = { wxT("<user-defined-code>") };
	int m_chImplementationNChoices = sizeof( m_chImplementationChoices ) / sizeof( wxString );
	m_chImplementation = new wxChoice( m_pageAdv, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chImplementationNChoices, m_chImplementationChoices, 0 );
	m_chImplementation->SetSelection( 0 );
	advSizer->Add( m_chImplementation, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText431 = new wxStaticText( m_pageAdv, wxID_ANY, wxT("Function modifier:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText431->Wrap( -1 );
	advSizer->Add( m_staticText431, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	wxArrayString m_chFcnModifierChoices;
	m_chFcnModifier = new wxChoice( m_pageAdv, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chFcnModifierChoices, 0 );
	m_chFcnModifier->SetSelection( 0 );
	advSizer->Add( m_chFcnModifier, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	m_pageAdv->SetSizer( advSizer );
	m_pageAdv->Layout();
	advSizer->Fit( m_pageAdv );
	m_pNotebook->AddPage( m_pageAdv, wxT("Advanced"), true );
	m_pageEditor = new wxPanel( m_pNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* editorSizer;
	editorSizer = new wxBoxSizer( wxVERTICAL );
	
	m_sciEditor = new wxStyledTextCtrl( m_pageEditor, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, wxEmptyString );
	m_sciEditor->SetUseTabs( true );
	m_sciEditor->SetTabWidth( 4 );
	m_sciEditor->SetIndent( 4 );
	m_sciEditor->SetTabIndents( true );
	m_sciEditor->SetBackSpaceUnIndents( true );
	m_sciEditor->SetViewEOL( false );
	m_sciEditor->SetViewWhiteSpace( false );
	m_sciEditor->SetMarginWidth( 2, 0 );
	m_sciEditor->SetIndentationGuides( true );
	m_sciEditor->SetMarginType( 1, wxSTC_MARGIN_SYMBOL );
	m_sciEditor->SetMarginMask( 1, wxSTC_MASK_FOLDERS );
	m_sciEditor->SetMarginWidth( 1, 16);
	m_sciEditor->SetMarginSensitive( 1, true );
	m_sciEditor->SetProperty( wxT("fold"), wxT("1") );
	m_sciEditor->SetFoldFlags( wxSTC_FOLDFLAG_LINEBEFORE_CONTRACTED | wxSTC_FOLDFLAG_LINEAFTER_CONTRACTED );
	m_sciEditor->SetMarginType( 0, wxSTC_MARGIN_NUMBER );
	m_sciEditor->SetMarginWidth( 0, m_sciEditor->TextWidth( wxSTC_STYLE_LINENUMBER, wxT("_99999") ) );
	{
		wxFont font = wxFont( 9, 70, 90, 90, false, wxEmptyString );
		m_sciEditor->StyleSetFont( wxSTC_STYLE_DEFAULT, font );
	}
	m_sciEditor->MarkerDefine( wxSTC_MARKNUM_FOLDER, wxSTC_MARK_BOXPLUS );
	m_sciEditor->MarkerSetBackground( wxSTC_MARKNUM_FOLDER, wxColour( wxT("BLACK") ) );
	m_sciEditor->MarkerSetForeground( wxSTC_MARKNUM_FOLDER, wxColour( wxT("WHITE") ) );
	m_sciEditor->MarkerDefine( wxSTC_MARKNUM_FOLDEROPEN, wxSTC_MARK_BOXMINUS );
	m_sciEditor->MarkerSetBackground( wxSTC_MARKNUM_FOLDEROPEN, wxColour( wxT("BLACK") ) );
	m_sciEditor->MarkerSetForeground( wxSTC_MARKNUM_FOLDEROPEN, wxColour( wxT("WHITE") ) );
	m_sciEditor->MarkerDefine( wxSTC_MARKNUM_FOLDERSUB, wxSTC_MARK_EMPTY );
	m_sciEditor->MarkerDefine( wxSTC_MARKNUM_FOLDEREND, wxSTC_MARK_BOXPLUS );
	m_sciEditor->MarkerSetBackground( wxSTC_MARKNUM_FOLDEREND, wxColour( wxT("BLACK") ) );
	m_sciEditor->MarkerSetForeground( wxSTC_MARKNUM_FOLDEREND, wxColour( wxT("WHITE") ) );
	m_sciEditor->MarkerDefine( wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_BOXMINUS );
	m_sciEditor->MarkerSetBackground( wxSTC_MARKNUM_FOLDEROPENMID, wxColour( wxT("BLACK") ) );
	m_sciEditor->MarkerSetForeground( wxSTC_MARKNUM_FOLDEROPENMID, wxColour( wxT("WHITE") ) );
	m_sciEditor->MarkerDefine( wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_EMPTY );
	m_sciEditor->MarkerDefine( wxSTC_MARKNUM_FOLDERTAIL, wxSTC_MARK_EMPTY );
	m_sciEditor->SetSelBackground( true, wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHT ) );
	m_sciEditor->SetSelForeground( true, wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHTTEXT ) );
	m_sciEditor->SetFont( wxFont( 9, 70, 90, 90, false, wxEmptyString ) );
	m_sciEditor->SetMinSize( wxSize( 400,100 ) );
	
	editorSizer->Add( m_sciEditor, 1, wxEXPAND | wxALL, 5 );
	
	
	m_pageEditor->SetSizer( editorSizer );
	m_pageEditor->Layout();
	editorSizer->Fit( m_pageEditor );
	m_pNotebook->AddPage( m_pageEditor, wxT("Editor"), false );
	
	controlSizer->Add( m_pNotebook, wxGBPosition( 4, 0 ), wxGBSpan( 1, 2 ), wxEXPAND | wxALL, 5 );
	
	bntSizer = new wxStdDialogButtonSizer();
	bntSizerOK = new wxButton( this, wxID_OK );
	bntSizer->AddButton( bntSizerOK );
	bntSizerCancel = new wxButton( this, wxID_CANCEL );
	bntSizer->AddButton( bntSizerCancel );
	bntSizer->Realize();
	
	controlSizer->Add( bntSizer, wxGBPosition( 5, 0 ), wxGBSpan( 1, 2 ), wxALIGN_RIGHT|wxEXPAND|wxBOTTOM|wxRIGHT, 5 );
	
	
	controlSizer->AddGrowableCol( 0 );
	controlSizer->AddGrowableRow( 4 );
	
	mainSizer->Add( controlSizer, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( mainSizer );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _DestructorDialog::OnInit ) );
	m_eName->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( _DestructorDialog::OnNameChange ), NULL, this );
	m_cbMakeValid->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _DestructorDialog::OnMakeValid ), NULL, this );
	m_sciEditor->Connect( wxEVT_CHAR, wxKeyEventHandler( _DestructorDialog::OnEditorTextChange ), NULL, this );
	m_sciEditor->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _DestructorDialog::OnUpdateEditor ), NULL, this );
	bntSizerCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _DestructorDialog::OnCancel ), NULL, this );
	bntSizerOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _DestructorDialog::OnOk ), NULL, this );
}

_DestructorDialog::~_DestructorDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _DestructorDialog::OnInit ) );
	m_eName->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( _DestructorDialog::OnNameChange ), NULL, this );
	m_cbMakeValid->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _DestructorDialog::OnMakeValid ), NULL, this );
	m_sciEditor->Disconnect( wxEVT_CHAR, wxKeyEventHandler( _DestructorDialog::OnEditorTextChange ), NULL, this );
	m_sciEditor->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _DestructorDialog::OnUpdateEditor ), NULL, this );
	bntSizerCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _DestructorDialog::OnCancel ), NULL, this );
	bntSizerOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _DestructorDialog::OnOk ), NULL, this );
	
}

_RenameVirtualDialog::_RenameVirtualDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxFlexGridSizer* mainSizer;
	mainSizer = new wxFlexGridSizer( 4, 0, 0, 0 );
	mainSizer->AddGrowableCol( 0 );
	mainSizer->AddGrowableRow( 2 );
	mainSizer->SetFlexibleDirection( wxBOTH );
	mainSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText37 = new wxStaticText( this, wxID_ANY, wxT("New name (must be valid identifier):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText37->Wrap( -1 );
	mainSizer->Add( m_staticText37, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxBoxSizer* nameSizer;
	nameSizer = new wxBoxSizer( wxHORIZONTAL );
	
	m_textCtrlName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 300,-1 ), 0 );
	m_textCtrlName->SetMaxLength( 0 ); 
	m_textCtrlName->SetMinSize( wxSize( 300,-1 ) );
	
	nameSizer->Add( m_textCtrlName, 1, wxALL|wxEXPAND, 5 );
	
	m_chbMakeValid = new wxCheckBox( this, wxID_ANY, wxT("Make valid"), wxDefaultPosition, wxDefaultSize, 0 );
	nameSizer->Add( m_chbMakeValid, 0, wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	mainSizer->Add( nameSizer, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* renameSizer;
	renameSizer = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Rename also:") ), wxVERTICAL );
	
	wxArrayString m_checkListCandidatesChoices;
	m_checkListCandidates = new wxCheckListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_checkListCandidatesChoices, 0 );
	m_checkListCandidates->SetMinSize( wxSize( -1,100 ) );
	m_checkListCandidates->SetMaxSize( wxSize( -1,100 ) );
	
	m_menuCandidates = new wxMenu();
	wxMenuItem* menuSelectAll;
	menuSelectAll = new wxMenuItem( m_menuCandidates, IDM_CANDIDATES_SELECTALL, wxString( wxT("Select all") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuCandidates->Append( menuSelectAll );
	
	wxMenuItem* menuDeselectAll;
	menuDeselectAll = new wxMenuItem( m_menuCandidates, IDM_CANDIDATES_DESELECTALL, wxString( wxT("Deselect all") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuCandidates->Append( menuDeselectAll );
	
	m_checkListCandidates->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( _RenameVirtualDialog::m_checkListCandidatesOnContextMenu ), NULL, this ); 
	
	renameSizer->Add( m_checkListCandidates, 1, wxALL|wxEXPAND, 5 );
	
	
	mainSizer->Add( renameSizer, 0, wxEXPAND|wxALL, 5 );
	
	buttonSizer = new wxStdDialogButtonSizer();
	buttonSizerOK = new wxButton( this, wxID_OK );
	buttonSizer->AddButton( buttonSizerOK );
	buttonSizerCancel = new wxButton( this, wxID_CANCEL );
	buttonSizer->AddButton( buttonSizerCancel );
	buttonSizer->Realize();
	
	mainSizer->Add( buttonSizer, 1, wxEXPAND|wxBOTTOM|wxRIGHT, 5 );
	
	
	this->SetSizer( mainSizer );
	this->Layout();
	mainSizer->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_textCtrlName->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( _RenameVirtualDialog::OnNameChange ), NULL, this );
	m_chbMakeValid->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _RenameVirtualDialog::OnMakeValid ), NULL, this );
	this->Connect( menuSelectAll->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _RenameVirtualDialog::OnSelectAll ) );
	this->Connect( menuDeselectAll->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _RenameVirtualDialog::OnDeselectAll ) );
	buttonSizerOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _RenameVirtualDialog::OnOk ), NULL, this );
}

_RenameVirtualDialog::~_RenameVirtualDialog()
{
	// Disconnect Events
	m_textCtrlName->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( _RenameVirtualDialog::OnNameChange ), NULL, this );
	m_chbMakeValid->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _RenameVirtualDialog::OnMakeValid ), NULL, this );
	this->Disconnect( IDM_CANDIDATES_SELECTALL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _RenameVirtualDialog::OnSelectAll ) );
	this->Disconnect( IDM_CANDIDATES_DESELECTALL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _RenameVirtualDialog::OnDeselectAll ) );
	buttonSizerOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _RenameVirtualDialog::OnOk ), NULL, this );
	
	delete m_menuCandidates; 
}

_ClassTemplateDialog::_ClassTemplateDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 400,430 ), wxDefaultSize );
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	wxGridBagSizer* controlSizer;
	controlSizer = new wxGridBagSizer( 0, 0 );
	controlSizer->SetFlexibleDirection( wxBOTH );
	controlSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Name (must be valid language identifier);"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	controlSizer->Add( m_staticText1, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxBoxSizer* nameSizer;
	nameSizer = new wxBoxSizer( wxHORIZONTAL );
	
	m_eName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_eName->SetMaxLength( 0 ); 
	nameSizer->Add( m_eName, 1, wxALL|wxEXPAND, 5 );
	
	m_cbMakeValid = new wxCheckBox( this, wxID_ANY, wxT("Make valid"), wxDefaultPosition, wxDefaultSize, 0 );
	nameSizer->Add( m_cbMakeValid, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	controlSizer->Add( nameSizer, wxGBPosition( 1, 0 ), wxGBSpan( 1, 2 ), wxEXPAND, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Description:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	controlSizer->Add( m_staticText2, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_eDescription = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 400,100 ), wxTE_MULTILINE );
	m_eDescription->SetMaxLength( 0 ); 
	m_eDescription->SetMinSize( wxSize( 400,100 ) );
	
	controlSizer->Add( m_eDescription, wxGBPosition( 3, 0 ), wxGBSpan( 1, 2 ), wxEXPAND|wxALL, 5 );
	
	m_pNotebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_pNotebook->SetMinSize( wxSize( -1,200 ) );
	
	m_pageTempl = new wxPanel( m_pNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* advSizer;
	advSizer = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* templateSizer;
	templateSizer = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText43 = new wxStaticText( m_pageTempl, wxID_ANY, wxT("Typename:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText43->Wrap( -1 );
	templateSizer->Add( m_staticText43, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_txtTemplateName = new wxTextCtrl( m_pageTempl, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_txtTemplateName->SetMaxLength( 0 ); 
	templateSizer->Add( m_txtTemplateName, 1, wxALL, 5 );
	
	
	advSizer->Add( templateSizer, 0, wxEXPAND, 5 );
	
	
	m_pageTempl->SetSizer( advSizer );
	m_pageTempl->Layout();
	advSizer->Fit( m_pageTempl );
	m_pNotebook->AddPage( m_pageTempl, wxT("Template"), true );
	
	controlSizer->Add( m_pNotebook, wxGBPosition( 4, 0 ), wxGBSpan( 1, 2 ), wxEXPAND | wxALL, 5 );
	
	bntSizer = new wxStdDialogButtonSizer();
	bntSizerOK = new wxButton( this, wxID_OK );
	bntSizer->AddButton( bntSizerOK );
	bntSizerCancel = new wxButton( this, wxID_CANCEL );
	bntSizer->AddButton( bntSizerCancel );
	bntSizer->Realize();
	
	controlSizer->Add( bntSizer, wxGBPosition( 5, 0 ), wxGBSpan( 1, 2 ), wxALIGN_RIGHT|wxEXPAND|wxBOTTOM|wxRIGHT, 5 );
	
	
	controlSizer->AddGrowableCol( 0 );
	controlSizer->AddGrowableRow( 4 );
	
	mainSizer->Add( controlSizer, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( mainSizer );
	this->Layout();
	mainSizer->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _ClassTemplateDialog::OnInit ) );
	m_eName->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( _ClassTemplateDialog::OnNameChange ), NULL, this );
	m_cbMakeValid->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _ClassTemplateDialog::OnMakeValid ), NULL, this );
	bntSizerOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ClassTemplateDialog::OnOk ), NULL, this );
}

_ClassTemplateDialog::~_ClassTemplateDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _ClassTemplateDialog::OnInit ) );
	m_eName->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( _ClassTemplateDialog::OnNameChange ), NULL, this );
	m_cbMakeValid->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _ClassTemplateDialog::OnMakeValid ), NULL, this );
	bntSizerOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ClassTemplateDialog::OnOk ), NULL, this );
	
}

_ClassInstanceDialog::_ClassInstanceDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* itemSizer;
	itemSizer = new wxFlexGridSizer( 3, 2, 0, 0 );
	itemSizer->AddGrowableCol( 1 );
	itemSizer->SetFlexibleDirection( wxBOTH );
	itemSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText40 = new wxStaticText( this, wxID_ANY, wxT("Instance name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText40->Wrap( -1 );
	itemSizer->Add( m_staticText40, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_textInstName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 200,-1 ), 0 );
	m_textInstName->SetMaxLength( 0 ); 
	m_textInstName->SetMinSize( wxSize( 200,-1 ) );
	
	itemSizer->Add( m_textInstName, 0, wxTOP|wxRIGHT|wxLEFT|wxEXPAND, 5 );
	
	m_staticText41 = new wxStaticText( this, wxID_ANY, wxT("Parameters:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText41->Wrap( -1 );
	itemSizer->Add( m_staticText41, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_textParameters = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textParameters->SetMaxLength( 0 ); 
	itemSizer->Add( m_textParameters, 0, wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_staticText42 = new wxStaticText( this, wxID_ANY, wxT("Type:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText42->Wrap( -1 );
	itemSizer->Add( m_staticText42, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_choiceTypeChoices[] = { wxT("Static"), wxT("Dynamic") };
	int m_choiceTypeNChoices = sizeof( m_choiceTypeChoices ) / sizeof( wxString );
	m_choiceType = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceTypeNChoices, m_choiceTypeChoices, 0 );
	m_choiceType->SetSelection( 0 );
	itemSizer->Add( m_choiceType, 0, wxALL|wxEXPAND, 5 );
	
	
	mainSizer->Add( itemSizer, 1, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	mainSizer->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	m_sdbSizer13 = new wxStdDialogButtonSizer();
	m_sdbSizer13OK = new wxButton( this, wxID_OK );
	m_sdbSizer13->AddButton( m_sdbSizer13OK );
	m_sdbSizer13->Realize();
	
	mainSizer->Add( m_sdbSizer13, 0, wxEXPAND|wxTOP|wxBOTTOM|wxRIGHT, 5 );
	
	
	this->SetSizer( mainSizer );
	this->Layout();
	mainSizer->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _ClassInstanceDialog::OnInit ) );
	m_sdbSizer13OK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ClassInstanceDialog::OnOk ), NULL, this );
}

_ClassInstanceDialog::~_ClassInstanceDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _ClassInstanceDialog::OnInit ) );
	m_sdbSizer13OK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ClassInstanceDialog::OnOk ), NULL, this );
	
}

_EnumElementDialog::_EnumElementDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 400,350 ), wxDefaultSize );
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	wxGridBagSizer* controlSizer;
	controlSizer = new wxGridBagSizer( 0, 0 );
	controlSizer->SetFlexibleDirection( wxBOTH );
	controlSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Name (must be valid language identifier);"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	controlSizer->Add( m_staticText1, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxBoxSizer* nameSizer;
	nameSizer = new wxBoxSizer( wxHORIZONTAL );
	
	m_eName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_eName->SetMaxLength( 0 ); 
	nameSizer->Add( m_eName, 1, wxALL|wxEXPAND, 5 );
	
	m_cbMakeValid = new wxCheckBox( this, wxID_ANY, wxT("Make valid"), wxDefaultPosition, wxDefaultSize, 0 );
	nameSizer->Add( m_cbMakeValid, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	controlSizer->Add( nameSizer, wxGBPosition( 1, 0 ), wxGBSpan( 1, 2 ), wxEXPAND, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Description:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	controlSizer->Add( m_staticText2, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_eDescription = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 400,100 ), wxTE_MULTILINE );
	m_eDescription->SetMaxLength( 0 ); 
	m_eDescription->SetMinSize( wxSize( 400,100 ) );
	
	controlSizer->Add( m_eDescription, wxGBPosition( 3, 0 ), wxGBSpan( 1, 2 ), wxEXPAND|wxALL, 5 );
	
	m_pNotebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_pNotebook->SetMinSize( wxSize( -1,100 ) );
	
	m_pageAdv = new wxPanel( m_pNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* advSizer;
	advSizer = new wxBoxSizer( wxVERTICAL );
	
	m_staticText11 = new wxStaticText( m_pageAdv, wxID_ANY, wxT("Value:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	advSizer->Add( m_staticText11, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_eValue = new wxTextCtrl( m_pageAdv, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_eValue->SetMaxLength( 0 ); 
	advSizer->Add( m_eValue, 0, wxALL|wxEXPAND, 5 );
	
	
	m_pageAdv->SetSizer( advSizer );
	m_pageAdv->Layout();
	advSizer->Fit( m_pageAdv );
	m_pNotebook->AddPage( m_pageAdv, wxT("Advanced"), true );
	
	controlSizer->Add( m_pNotebook, wxGBPosition( 4, 0 ), wxGBSpan( 1, 2 ), wxEXPAND | wxALL, 5 );
	
	bntSizer = new wxStdDialogButtonSizer();
	bntSizerOK = new wxButton( this, wxID_OK );
	bntSizer->AddButton( bntSizerOK );
	bntSizerCancel = new wxButton( this, wxID_CANCEL );
	bntSizer->AddButton( bntSizerCancel );
	bntSizer->Realize();
	
	controlSizer->Add( bntSizer, wxGBPosition( 5, 0 ), wxGBSpan( 1, 2 ), wxALIGN_RIGHT|wxEXPAND|wxBOTTOM|wxRIGHT, 5 );
	
	
	controlSizer->AddGrowableCol( 0 );
	controlSizer->AddGrowableRow( 4 );
	
	mainSizer->Add( controlSizer, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( mainSizer );
	this->Layout();
	mainSizer->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _EnumElementDialog::OnInit ) );
	m_eName->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( _EnumElementDialog::OnNameChange ), NULL, this );
	m_cbMakeValid->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _EnumElementDialog::OnMakeValid ), NULL, this );
	bntSizerOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _EnumElementDialog::OnOk ), NULL, this );
}

_EnumElementDialog::~_EnumElementDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _EnumElementDialog::OnInit ) );
	m_eName->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( _EnumElementDialog::OnNameChange ), NULL, this );
	m_cbMakeValid->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _EnumElementDialog::OnMakeValid ), NULL, this );
	bntSizerOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _EnumElementDialog::OnOk ), NULL, this );
	
}

_EnumDialog::_EnumDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 400,350 ), wxDefaultSize );
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	wxGridBagSizer* controlSizer;
	controlSizer = new wxGridBagSizer( 0, 0 );
	controlSizer->SetFlexibleDirection( wxBOTH );
	controlSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Name (must be valid language identifier);"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	controlSizer->Add( m_staticText1, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxBoxSizer* nameSizer;
	nameSizer = new wxBoxSizer( wxHORIZONTAL );
	
	m_eName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_eName->SetMaxLength( 0 ); 
	nameSizer->Add( m_eName, 1, wxALL|wxEXPAND, 5 );
	
	m_cbMakeValid = new wxCheckBox( this, wxID_ANY, wxT("Make valid"), wxDefaultPosition, wxDefaultSize, 0 );
	nameSizer->Add( m_cbMakeValid, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	controlSizer->Add( nameSizer, wxGBPosition( 1, 0 ), wxGBSpan( 1, 2 ), wxEXPAND, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Description:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	controlSizer->Add( m_staticText2, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_eDescription = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 400,100 ), wxTE_MULTILINE );
	m_eDescription->SetMaxLength( 0 ); 
	m_eDescription->SetMinSize( wxSize( 400,100 ) );
	
	controlSizer->Add( m_eDescription, wxGBPosition( 3, 0 ), wxGBSpan( 1, 2 ), wxEXPAND|wxALL, 5 );
	
	m_pNotebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_pNotebook->SetMinSize( wxSize( -1,100 ) );
	
	m_pageAdv = new wxPanel( m_pNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* advSizer;
	advSizer = new wxBoxSizer( wxVERTICAL );
	
	m_staticText11 = new wxStaticText( m_pageAdv, wxID_ANY, wxT("Instance name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	advSizer->Add( m_staticText11, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_eInstName = new wxTextCtrl( m_pageAdv, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_eInstName->SetMaxLength( 0 ); 
	advSizer->Add( m_eInstName, 0, wxALL|wxEXPAND, 5 );
	
	
	m_pageAdv->SetSizer( advSizer );
	m_pageAdv->Layout();
	advSizer->Fit( m_pageAdv );
	m_pNotebook->AddPage( m_pageAdv, wxT("Advanced"), true );
	
	controlSizer->Add( m_pNotebook, wxGBPosition( 4, 0 ), wxGBSpan( 1, 2 ), wxEXPAND | wxALL, 5 );
	
	bntSizer = new wxStdDialogButtonSizer();
	bntSizerOK = new wxButton( this, wxID_OK );
	bntSizer->AddButton( bntSizerOK );
	bntSizerCancel = new wxButton( this, wxID_CANCEL );
	bntSizer->AddButton( bntSizerCancel );
	bntSizer->Realize();
	
	controlSizer->Add( bntSizer, wxGBPosition( 5, 0 ), wxGBSpan( 1, 2 ), wxALIGN_RIGHT|wxEXPAND|wxBOTTOM|wxRIGHT, 5 );
	
	
	controlSizer->AddGrowableCol( 0 );
	controlSizer->AddGrowableRow( 4 );
	
	mainSizer->Add( controlSizer, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( mainSizer );
	this->Layout();
	mainSizer->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _EnumDialog::OnInit ) );
	m_eName->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( _EnumDialog::OnNameChange ), NULL, this );
	m_cbMakeValid->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _EnumDialog::OnMakeValid ), NULL, this );
	bntSizerOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _EnumDialog::OnOk ), NULL, this );
}

_EnumDialog::~_EnumDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _EnumDialog::OnInit ) );
	m_eName->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( _EnumDialog::OnNameChange ), NULL, this );
	m_cbMakeValid->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _EnumDialog::OnMakeValid ), NULL, this );
	bntSizerOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _EnumDialog::OnOk ), NULL, this );
	
}

_ClassDialog::_ClassDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 400,350 ), wxDefaultSize );
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	wxGridBagSizer* controlSizer;
	controlSizer = new wxGridBagSizer( 0, 0 );
	controlSizer->SetFlexibleDirection( wxBOTH );
	controlSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Name (must be valid language identifier);"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	controlSizer->Add( m_staticText1, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxBoxSizer* nameSizer;
	nameSizer = new wxBoxSizer( wxHORIZONTAL );
	
	m_eName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_eName->SetMaxLength( 0 ); 
	nameSizer->Add( m_eName, 1, wxALL|wxEXPAND, 5 );
	
	m_cbMakeValid = new wxCheckBox( this, wxID_ANY, wxT("Make valid"), wxDefaultPosition, wxDefaultSize, 0 );
	nameSizer->Add( m_cbMakeValid, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	controlSizer->Add( nameSizer, wxGBPosition( 1, 0 ), wxGBSpan( 1, 2 ), wxEXPAND, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Description:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	controlSizer->Add( m_staticText2, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_eDescription = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 400,100 ), wxTE_MULTILINE );
	m_eDescription->SetMaxLength( 0 ); 
	m_eDescription->SetMinSize( wxSize( 400,100 ) );
	
	controlSizer->Add( m_eDescription, wxGBPosition( 3, 0 ), wxGBSpan( 1, 2 ), wxEXPAND|wxALL, 5 );
	
	m_pNotebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_pageAdv = new wxPanel( m_pNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* advSizer;
	advSizer = new wxBoxSizer( wxVERTICAL );
	
	m_chbGenerate = new wxCheckBox( m_pageAdv, wxID_ANY, wxT("Generate code"), wxDefaultPosition, wxDefaultSize, 0 );
	advSizer->Add( m_chbGenerate, 0, wxALL, 5 );
	
	
	m_pageAdv->SetSizer( advSizer );
	m_pageAdv->Layout();
	advSizer->Fit( m_pageAdv );
	m_pNotebook->AddPage( m_pageAdv, wxT("Advanced"), true );
	
	controlSizer->Add( m_pNotebook, wxGBPosition( 4, 0 ), wxGBSpan( 1, 2 ), wxEXPAND | wxALL, 5 );
	
	bntSizer = new wxStdDialogButtonSizer();
	bntSizerOK = new wxButton( this, wxID_OK );
	bntSizer->AddButton( bntSizerOK );
	bntSizerCancel = new wxButton( this, wxID_CANCEL );
	bntSizer->AddButton( bntSizerCancel );
	bntSizer->Realize();
	
	controlSizer->Add( bntSizer, wxGBPosition( 5, 0 ), wxGBSpan( 1, 2 ), wxALIGN_RIGHT|wxEXPAND|wxBOTTOM|wxRIGHT, 5 );
	
	
	controlSizer->AddGrowableCol( 0 );
	controlSizer->AddGrowableRow( 4 );
	
	mainSizer->Add( controlSizer, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( mainSizer );
	this->Layout();
	mainSizer->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _ClassDialog::OnInit ) );
	m_eName->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( _ClassDialog::OnNameChange ), NULL, this );
	m_cbMakeValid->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _ClassDialog::OnMakeValid ), NULL, this );
	bntSizerOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ClassDialog::OnOk ), NULL, this );
}

_ClassDialog::~_ClassDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _ClassDialog::OnInit ) );
	m_eName->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( _ClassDialog::OnNameChange ), NULL, this );
	m_cbMakeValid->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _ClassDialog::OnMakeValid ), NULL, this );
	bntSizerOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ClassDialog::OnOk ), NULL, this );
	
}

_SubStateDialog::_SubStateDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 400,350 ), wxDefaultSize );
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	wxGridBagSizer* controlSizer;
	controlSizer = new wxGridBagSizer( 0, 0 );
	controlSizer->SetFlexibleDirection( wxBOTH );
	controlSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Name (must be valid language identifier);"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	controlSizer->Add( m_staticText1, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxBoxSizer* nameSizer;
	nameSizer = new wxBoxSizer( wxHORIZONTAL );
	
	m_eName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_eName->SetMaxLength( 0 ); 
	nameSizer->Add( m_eName, 1, wxALL|wxEXPAND, 5 );
	
	m_cbMakeValid = new wxCheckBox( this, wxID_ANY, wxT("Make valid"), wxDefaultPosition, wxDefaultSize, 0 );
	nameSizer->Add( m_cbMakeValid, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	controlSizer->Add( nameSizer, wxGBPosition( 1, 0 ), wxGBSpan( 1, 2 ), wxEXPAND, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Description:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	controlSizer->Add( m_staticText2, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_eDescription = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 400,100 ), wxTE_MULTILINE );
	m_eDescription->SetMaxLength( 0 ); 
	m_eDescription->SetMinSize( wxSize( 400,100 ) );
	
	controlSizer->Add( m_eDescription, wxGBPosition( 3, 0 ), wxGBSpan( 1, 2 ), wxEXPAND|wxALL, 5 );
	
	m_pNotebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_pageAdv = new wxPanel( m_pNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* advSizer;
	advSizer = new wxBoxSizer( wxVERTICAL );
	
	m_chbStoreRetVal = new wxCheckBox( m_pageAdv, wxID_ANY, wxT("Store return value"), wxDefaultPosition, wxDefaultSize, 0 );
	m_chbStoreRetVal->SetToolTip( wxT("Store value returned from managed sub diagram") );
	
	advSizer->Add( m_chbStoreRetVal, 0, wxALL, 5 );
	
	
	m_pageAdv->SetSizer( advSizer );
	m_pageAdv->Layout();
	advSizer->Fit( m_pageAdv );
	m_pNotebook->AddPage( m_pageAdv, wxT("Advanced"), true );
	
	controlSizer->Add( m_pNotebook, wxGBPosition( 4, 0 ), wxGBSpan( 1, 2 ), wxEXPAND | wxALL, 5 );
	
	bntSizer = new wxStdDialogButtonSizer();
	bntSizerOK = new wxButton( this, wxID_OK );
	bntSizer->AddButton( bntSizerOK );
	bntSizerCancel = new wxButton( this, wxID_CANCEL );
	bntSizer->AddButton( bntSizerCancel );
	bntSizer->Realize();
	
	controlSizer->Add( bntSizer, wxGBPosition( 5, 0 ), wxGBSpan( 1, 2 ), wxALIGN_RIGHT|wxEXPAND|wxBOTTOM|wxRIGHT, 5 );
	
	
	controlSizer->AddGrowableCol( 0 );
	controlSizer->AddGrowableRow( 4 );
	
	mainSizer->Add( controlSizer, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( mainSizer );
	this->Layout();
	mainSizer->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _SubStateDialog::OnInit ) );
	m_eName->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( _SubStateDialog::OnNameChange ), NULL, this );
	m_cbMakeValid->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _SubStateDialog::OnMakeValid ), NULL, this );
	bntSizerOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _SubStateDialog::OnOk ), NULL, this );
}

_SubStateDialog::~_SubStateDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _SubStateDialog::OnInit ) );
	m_eName->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( _SubStateDialog::OnNameChange ), NULL, this );
	m_cbMakeValid->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _SubStateDialog::OnMakeValid ), NULL, this );
	bntSizerOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _SubStateDialog::OnOk ), NULL, this );
	
}

_AggregationDialog::_AggregationDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 400,350 ), wxDefaultSize );
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	wxGridBagSizer* controlSizer;
	controlSizer = new wxGridBagSizer( 0, 0 );
	controlSizer->SetFlexibleDirection( wxBOTH );
	controlSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Name (must be valid language identifier);"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	controlSizer->Add( m_staticText1, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxBoxSizer* nameSizer;
	nameSizer = new wxBoxSizer( wxHORIZONTAL );
	
	m_eName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_eName->SetMaxLength( 0 ); 
	nameSizer->Add( m_eName, 1, wxALL|wxEXPAND, 5 );
	
	m_cbMakeValid = new wxCheckBox( this, wxID_ANY, wxT("Make valid"), wxDefaultPosition, wxDefaultSize, 0 );
	nameSizer->Add( m_cbMakeValid, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	controlSizer->Add( nameSizer, wxGBPosition( 1, 0 ), wxGBSpan( 1, 2 ), wxEXPAND, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Description:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	controlSizer->Add( m_staticText2, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_eDescription = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 400,100 ), wxTE_MULTILINE );
	m_eDescription->SetMaxLength( 0 ); 
	m_eDescription->SetMinSize( wxSize( 400,100 ) );
	
	controlSizer->Add( m_eDescription, wxGBPosition( 3, 0 ), wxGBSpan( 1, 2 ), wxEXPAND|wxALL, 5 );
	
	m_pNotebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_pageAdv = new wxPanel( m_pNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* advSizer;
	advSizer = new wxBoxSizer( wxVERTICAL );
	
	m_chbIncludeClass = new wxCheckBox( m_pageAdv, wxID_ANY, wxT("Include target class"), wxDefaultPosition, wxDefaultSize, 0 );
	advSizer->Add( m_chbIncludeClass, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer63;
	bSizer63 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText55 = new wxStaticText( m_pageAdv, wxID_ANY, wxT("Access:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText55->Wrap( -1 );
	bSizer63->Add( m_staticText55, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_chAccessChoices;
	m_chAccess = new wxChoice( m_pageAdv, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chAccessChoices, 0 );
	m_chAccess->SetSelection( 0 );
	bSizer63->Add( m_chAccess, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	advSizer->Add( bSizer63, 1, wxEXPAND, 5 );
	
	
	m_pageAdv->SetSizer( advSizer );
	m_pageAdv->Layout();
	advSizer->Fit( m_pageAdv );
	m_pNotebook->AddPage( m_pageAdv, wxT("Advanced"), true );
	
	controlSizer->Add( m_pNotebook, wxGBPosition( 4, 0 ), wxGBSpan( 1, 2 ), wxEXPAND | wxALL, 5 );
	
	bntSizer = new wxStdDialogButtonSizer();
	bntSizerOK = new wxButton( this, wxID_OK );
	bntSizer->AddButton( bntSizerOK );
	bntSizerCancel = new wxButton( this, wxID_CANCEL );
	bntSizer->AddButton( bntSizerCancel );
	bntSizer->Realize();
	
	controlSizer->Add( bntSizer, wxGBPosition( 5, 0 ), wxGBSpan( 1, 2 ), wxALIGN_RIGHT|wxEXPAND|wxBOTTOM|wxRIGHT, 5 );
	
	
	controlSizer->AddGrowableCol( 0 );
	controlSizer->AddGrowableRow( 4 );
	
	mainSizer->Add( controlSizer, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( mainSizer );
	this->Layout();
	mainSizer->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _AggregationDialog::OnInit ) );
	m_eName->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( _AggregationDialog::OnNameChange ), NULL, this );
	m_cbMakeValid->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _AggregationDialog::OnMakeValid ), NULL, this );
	bntSizerOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _AggregationDialog::OnOk ), NULL, this );
}

_AggregationDialog::~_AggregationDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _AggregationDialog::OnInit ) );
	m_eName->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( _AggregationDialog::OnNameChange ), NULL, this );
	m_cbMakeValid->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _AggregationDialog::OnMakeValid ), NULL, this );
	bntSizerOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _AggregationDialog::OnOk ), NULL, this );
	
}
