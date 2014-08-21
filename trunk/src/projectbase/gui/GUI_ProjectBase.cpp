///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  6 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "GUI_ProjectBase.h"

///////////////////////////////////////////////////////////////////////////

_DiagramDialog::_DiagramDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 460,430 ), wxDefaultSize );
	
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
	wxBoxSizer* advSizer;
	advSizer = new wxBoxSizer( wxVERTICAL );
	
	m_cbGenerate = new wxCheckBox( m_pageAdv, wxID_ANY, wxT("Generate code from this diagram"), wxDefaultPosition, wxDefaultSize, 0 );
	advSizer->Add( m_cbGenerate, 0, wxALL, 5 );
	
	
	m_pageAdv->SetSizer( advSizer );
	m_pageAdv->Layout();
	advSizer->Fit( m_pageAdv );
	m_pNotebook->AddPage( m_pageAdv, wxT("Advanced"), true );
	m_pageGen = new wxPanel( m_pNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* genSizer;
	genSizer = new wxBoxSizer( wxVERTICAL );
	
	m_staticText14 = new wxStaticText( m_pageGen, wxID_ANY, wxT("Output file (without extension):"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText14->Wrap( -1 );
	genSizer->Add( m_staticText14, 0, wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxBoxSizer* fileSizer;
	fileSizer = new wxBoxSizer( wxHORIZONTAL );
	
	m_fpOutputFile = new wxFilePickerCtrl( m_pageGen, wxID_ANY, wxEmptyString, wxT("Select an output file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_SAVE|wxFLP_USE_TEXTCTRL );
	fileSizer->Add( m_fpOutputFile, 1, wxALL, 5 );
	
	m_btnReset = new wxButton( m_pageGen, wxID_ANY, wxT("Reset"), wxDefaultPosition, wxDefaultSize, 0 );
	fileSizer->Add( m_btnReset, 0, wxTOP|wxBOTTOM|wxRIGHT, 5 );
	
	
	genSizer->Add( fileSizer, 0, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer6;
	fgSizer6 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer6->AddGrowableCol( 0 );
	fgSizer6->AddGrowableCol( 1 );
	fgSizer6->SetFlexibleDirection( wxBOTH );
	fgSizer6->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText15 = new wxStaticText( m_pageGen, wxID_ANY, wxT("Generator:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText15->Wrap( -1 );
	fgSizer6->Add( m_staticText15, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_staticText16 = new wxStaticText( m_pageGen, wxID_ANY, wxT("Algorithm:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText16->Wrap( -1 );
	fgSizer6->Add( m_staticText16, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxArrayString m_chGeneratorChoices;
	m_chGenerator = new wxChoice( m_pageGen, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chGeneratorChoices, 0 );
	m_chGenerator->SetSelection( 0 );
	fgSizer6->Add( m_chGenerator, 0, wxALL|wxEXPAND, 5 );
	
	wxArrayString m_chAlgorithmChoices;
	m_chAlgorithm = new wxChoice( m_pageGen, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chAlgorithmChoices, 0 );
	m_chAlgorithm->SetSelection( 0 );
	fgSizer6->Add( m_chAlgorithm, 1, wxALL|wxEXPAND, 5 );
	
	
	genSizer->Add( fgSizer6, 0, wxEXPAND, 5 );
	
	
	m_pageGen->SetSizer( genSizer );
	m_pageGen->Layout();
	genSizer->Fit( m_pageGen );
	m_pNotebook->AddPage( m_pageGen, wxT("Generator"), false );
	
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
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _DiagramDialog::OnInit ) );
	m_eName->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( _DiagramDialog::OnNameChange ), NULL, this );
	m_cbMakeValid->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _DiagramDialog::OnMakeValid ), NULL, this );
	m_btnReset->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _DiagramDialog::OnReset ), NULL, this );
	m_chGenerator->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( _DiagramDialog::OnGeneratorChange ), NULL, this );
	bntSizerOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _DiagramDialog::OnOk ), NULL, this );
}

_DiagramDialog::~_DiagramDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _DiagramDialog::OnInit ) );
	m_eName->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( _DiagramDialog::OnNameChange ), NULL, this );
	m_cbMakeValid->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _DiagramDialog::OnMakeValid ), NULL, this );
	m_btnReset->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _DiagramDialog::OnReset ), NULL, this );
	m_chGenerator->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( _DiagramDialog::OnGeneratorChange ), NULL, this );
	bntSizerOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _DiagramDialog::OnOk ), NULL, this );
	
}

_CodeLinkDialog::_CodeLinkDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
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
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _CodeLinkDialog::OnInit ) );
	btnEditOrig->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _CodeLinkDialog::OnEditOriginal ), NULL, this );
	bntSizerOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _CodeLinkDialog::OnOk ), NULL, this );
}

_CodeLinkDialog::~_CodeLinkDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _CodeLinkDialog::OnInit ) );
	btnEditOrig->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _CodeLinkDialog::OnEditOriginal ), NULL, this );
	bntSizerOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _CodeLinkDialog::OnOk ), NULL, this );
	
}

_FunctionLinkDialog::_FunctionLinkDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
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
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _FunctionLinkDialog::OnInit ) );
	btnEditOrig->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _FunctionLinkDialog::OnEditOriginal ), NULL, this );
	bntSizerOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _FunctionLinkDialog::OnOk ), NULL, this );
}

_FunctionLinkDialog::~_FunctionLinkDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _FunctionLinkDialog::OnInit ) );
	btnEditOrig->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _FunctionLinkDialog::OnEditOriginal ), NULL, this );
	bntSizerOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _FunctionLinkDialog::OnOk ), NULL, this );
	
}

_FunctionDialog::_FunctionDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
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
	
	m_chbInline = new wxCheckBox( m_pageAdv, wxID_ANY, wxT("Inline"), wxDefaultPosition, wxDefaultSize, 0 );
	advSizer->Add( m_chbInline, 0, wxALL, 5 );
	
	
	advSizer->Add( 0, 0, 1, wxEXPAND, 5 );
	
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
	m_pageRetVal = new wxPanel( m_pNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* dataTypeSizer;
	dataTypeSizer = new wxFlexGridSizer( 3, 2, 0, 0 );
	dataTypeSizer->AddGrowableCol( 1 );
	dataTypeSizer->SetFlexibleDirection( wxBOTH );
	dataTypeSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText43 = new wxStaticText( m_pageRetVal, wxID_ANY, wxT("Modifier:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText43->Wrap( -1 );
	dataTypeSizer->Add( m_staticText43, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	wxArrayString m_chModifierChoices;
	m_chModifier = new wxChoice( m_pageRetVal, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chModifierChoices, 0 );
	m_chModifier->SetSelection( 0 );
	dataTypeSizer->Add( m_chModifier, 0, wxEXPAND|wxALL, 5 );
	
	m_staticText44 = new wxStaticText( m_pageRetVal, wxID_ANY, wxT("Data type:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText44->Wrap( -1 );
	dataTypeSizer->Add( m_staticText44, 0, wxALL, 5 );
	
	wxArrayString m_chDataTypeChoices;
	m_chDataType = new wxChoice( m_pageRetVal, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chDataTypeChoices, 0 );
	m_chDataType->SetSelection( 0 );
	dataTypeSizer->Add( m_chDataType, 0, wxBOTTOM|wxRIGHT|wxLEFT|wxEXPAND, 5 );
	
	m_staticText45 = new wxStaticText( m_pageRetVal, wxID_ANY, wxT("Value type:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText45->Wrap( -1 );
	dataTypeSizer->Add( m_staticText45, 0, wxALL, 5 );
	
	wxArrayString m_chValueTypeChoices;
	m_chValueType = new wxChoice( m_pageRetVal, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chValueTypeChoices, 0 );
	m_chValueType->SetSelection( 0 );
	dataTypeSizer->Add( m_chValueType, 0, wxBOTTOM|wxRIGHT|wxLEFT|wxEXPAND, 5 );
	
	
	m_pageRetVal->SetSizer( dataTypeSizer );
	m_pageRetVal->Layout();
	dataTypeSizer->Fit( m_pageRetVal );
	m_pNotebook->AddPage( m_pageRetVal, wxT("Return value"), false );
	m_pageUserDataType = new wxPanel( m_pNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* userdataSizer;
	userdataSizer = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer10;
	fgSizer10 = new wxFlexGridSizer( 3, 2, 0, 0 );
	fgSizer10->AddGrowableCol( 1 );
	fgSizer10->SetFlexibleDirection( wxBOTH );
	fgSizer10->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText46 = new wxStaticText( m_pageUserDataType, wxID_ANY, wxT("Type name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText46->Wrap( -1 );
	fgSizer10->Add( m_staticText46, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_eTypeName = new wxTextCtrl( m_pageUserDataType, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_eTypeName->SetMaxLength( 0 ); 
	fgSizer10->Add( m_eTypeName, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText48 = new wxStaticText( m_pageUserDataType, wxID_ANY, wxT("Defined in:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText48->Wrap( -1 );
	fgSizer10->Add( m_staticText48, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	wxString m_chDefinitionPlaceChoices[] = { wxT("Built-in"), wxT("Editor"), wxT("Definition file") };
	int m_chDefinitionPlaceNChoices = sizeof( m_chDefinitionPlaceChoices ) / sizeof( wxString );
	m_chDefinitionPlace = new wxChoice( m_pageUserDataType, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chDefinitionPlaceNChoices, m_chDefinitionPlaceChoices, 0 );
	m_chDefinitionPlace->SetSelection( 0 );
	fgSizer10->Add( m_chDefinitionPlace, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_staticText47 = new wxStaticText( m_pageUserDataType, wxID_ANY, wxT("Definition file:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText47->Wrap( -1 );
	fgSizer10->Add( m_staticText47, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_fpDefinitionFile = new wxFilePickerCtrl( m_pageUserDataType, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE|wxFLP_USE_TEXTCTRL );
	fgSizer10->Add( m_fpDefinitionFile, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	userdataSizer->Add( fgSizer10, 1, wxEXPAND, 5 );
	
	
	m_pageUserDataType->SetSizer( userdataSizer );
	m_pageUserDataType->Layout();
	userdataSizer->Fit( m_pageUserDataType );
	m_pNotebook->AddPage( m_pageUserDataType, wxT("User return type"), false );
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
	m_pageEditor = new wxPanel( m_pNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* editorSizer;
	editorSizer = new wxBoxSizer( wxVERTICAL );
	
	wxString m_chEditedFieldChoices[] = { wxT("Function code"), wxT("User-defined return type") };
	int m_chEditedFieldNChoices = sizeof( m_chEditedFieldChoices ) / sizeof( wxString );
	m_chEditedField = new wxChoice( m_pageEditor, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chEditedFieldNChoices, m_chEditedFieldChoices, 0 );
	m_chEditedField->SetSelection( 0 );
	editorSizer->Add( m_chEditedField, 0, wxTOP|wxRIGHT|wxLEFT|wxEXPAND, 5 );
	
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
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _FunctionDialog::OnInit ) );
	m_eName->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( _FunctionDialog::OnNameChange ), NULL, this );
	m_cbMakeValid->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _FunctionDialog::OnMakeValid ), NULL, this );
	m_eTypeName->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _FunctionDialog::OnUpdateUserDataType ), NULL, this );
	m_chDefinitionPlace->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _FunctionDialog::OnUpdateUserDataType ), NULL, this );
	m_fpDefinitionFile->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _FunctionDialog::OnUpdateDefinitionFile ), NULL, this );
	m_lstParams->Connect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( _FunctionDialog::OnParamActivated ), NULL, this );
	m_btnAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _FunctionDialog::OnAddClick ), NULL, this );
	m_btnEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _FunctionDialog::OnEditClick ), NULL, this );
	m_btnEdit->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _FunctionDialog::OnUpdateParamButtons ), NULL, this );
	m_btnRemove->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _FunctionDialog::OnRemoveClick ), NULL, this );
	m_btnRemove->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _FunctionDialog::OnUpdateParamButtons ), NULL, this );
	m_btnMoveUp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _FunctionDialog::OnMoveUpClick ), NULL, this );
	m_btnMoveUp->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _FunctionDialog::OnUpdateParamButtons ), NULL, this );
	m_btnMoveDown->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _FunctionDialog::OnMoveDownClick ), NULL, this );
	m_btnMoveDown->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _FunctionDialog::OnUpdateParamButtons ), NULL, this );
	m_chEditedField->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( _FunctionDialog::OnEditorChoice ), NULL, this );
	m_sciEditor->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( _FunctionDialog::OnEditorKillFocus ), NULL, this );
	m_sciEditor->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _FunctionDialog::OnUpdateEditor ), NULL, this );
	bntSizerCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _FunctionDialog::OnCancel ), NULL, this );
	bntSizerOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _FunctionDialog::OnOk ), NULL, this );
}

_FunctionDialog::~_FunctionDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _FunctionDialog::OnInit ) );
	m_eName->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( _FunctionDialog::OnNameChange ), NULL, this );
	m_cbMakeValid->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _FunctionDialog::OnMakeValid ), NULL, this );
	m_eTypeName->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _FunctionDialog::OnUpdateUserDataType ), NULL, this );
	m_chDefinitionPlace->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _FunctionDialog::OnUpdateUserDataType ), NULL, this );
	m_fpDefinitionFile->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _FunctionDialog::OnUpdateDefinitionFile ), NULL, this );
	m_lstParams->Disconnect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( _FunctionDialog::OnParamActivated ), NULL, this );
	m_btnAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _FunctionDialog::OnAddClick ), NULL, this );
	m_btnEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _FunctionDialog::OnEditClick ), NULL, this );
	m_btnEdit->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _FunctionDialog::OnUpdateParamButtons ), NULL, this );
	m_btnRemove->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _FunctionDialog::OnRemoveClick ), NULL, this );
	m_btnRemove->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _FunctionDialog::OnUpdateParamButtons ), NULL, this );
	m_btnMoveUp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _FunctionDialog::OnMoveUpClick ), NULL, this );
	m_btnMoveUp->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _FunctionDialog::OnUpdateParamButtons ), NULL, this );
	m_btnMoveDown->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _FunctionDialog::OnMoveDownClick ), NULL, this );
	m_btnMoveDown->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _FunctionDialog::OnUpdateParamButtons ), NULL, this );
	m_chEditedField->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( _FunctionDialog::OnEditorChoice ), NULL, this );
	m_sciEditor->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( _FunctionDialog::OnEditorKillFocus ), NULL, this );
	m_sciEditor->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _FunctionDialog::OnUpdateEditor ), NULL, this );
	bntSizerCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _FunctionDialog::OnCancel ), NULL, this );
	bntSizerOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _FunctionDialog::OnOk ), NULL, this );
	
}

_VariableDialog::_VariableDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 460,430 ), wxDefaultSize );
	
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
	wxFlexGridSizer* dataTypeSizer;
	dataTypeSizer = new wxFlexGridSizer( 4, 2, 0, 0 );
	dataTypeSizer->AddGrowableCol( 1 );
	dataTypeSizer->SetFlexibleDirection( wxBOTH );
	dataTypeSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText43 = new wxStaticText( m_pageAdv, wxID_ANY, wxT("Modifier:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText43->Wrap( -1 );
	dataTypeSizer->Add( m_staticText43, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_chModifierChoices;
	m_chModifier = new wxChoice( m_pageAdv, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chModifierChoices, 0 );
	m_chModifier->SetSelection( 0 );
	dataTypeSizer->Add( m_chModifier, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText44 = new wxStaticText( m_pageAdv, wxID_ANY, wxT("Data type:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText44->Wrap( -1 );
	dataTypeSizer->Add( m_staticText44, 0, wxALL, 5 );
	
	wxArrayString m_chDataTypeChoices;
	m_chDataType = new wxChoice( m_pageAdv, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chDataTypeChoices, 0 );
	m_chDataType->SetSelection( 0 );
	dataTypeSizer->Add( m_chDataType, 0, wxBOTTOM|wxRIGHT|wxLEFT|wxEXPAND, 5 );
	
	m_staticText45 = new wxStaticText( m_pageAdv, wxID_ANY, wxT("Value type:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText45->Wrap( -1 );
	dataTypeSizer->Add( m_staticText45, 0, wxALL, 5 );
	
	wxArrayString m_chValueTypeChoices;
	m_chValueType = new wxChoice( m_pageAdv, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chValueTypeChoices, 0 );
	m_chValueType->SetSelection( 0 );
	dataTypeSizer->Add( m_chValueType, 0, wxBOTTOM|wxRIGHT|wxLEFT|wxEXPAND, 5 );
	
	m_staticText431 = new wxStaticText( m_pageAdv, wxID_ANY, wxT("Default value:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText431->Wrap( -1 );
	dataTypeSizer->Add( m_staticText431, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_eDefVal = new wxTextCtrl( m_pageAdv, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_eDefVal->SetMaxLength( 0 ); 
	dataTypeSizer->Add( m_eDefVal, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	m_pageAdv->SetSizer( dataTypeSizer );
	m_pageAdv->Layout();
	dataTypeSizer->Fit( m_pageAdv );
	m_pNotebook->AddPage( m_pageAdv, wxT("Advanced"), true );
	m_pageUserDataType = new wxPanel( m_pNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* userdataSizer;
	userdataSizer = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer10;
	fgSizer10 = new wxFlexGridSizer( 3, 2, 0, 0 );
	fgSizer10->AddGrowableCol( 1 );
	fgSizer10->SetFlexibleDirection( wxBOTH );
	fgSizer10->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText46 = new wxStaticText( m_pageUserDataType, wxID_ANY, wxT("Type name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText46->Wrap( -1 );
	fgSizer10->Add( m_staticText46, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_eTypeName = new wxTextCtrl( m_pageUserDataType, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_eTypeName->SetMaxLength( 0 ); 
	fgSizer10->Add( m_eTypeName, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText48 = new wxStaticText( m_pageUserDataType, wxID_ANY, wxT("Defined in:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText48->Wrap( -1 );
	fgSizer10->Add( m_staticText48, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	wxString m_chDefinitionPlaceChoices[] = { wxT("Built-in"), wxT("Editor"), wxT("Definition file") };
	int m_chDefinitionPlaceNChoices = sizeof( m_chDefinitionPlaceChoices ) / sizeof( wxString );
	m_chDefinitionPlace = new wxChoice( m_pageUserDataType, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chDefinitionPlaceNChoices, m_chDefinitionPlaceChoices, 0 );
	m_chDefinitionPlace->SetSelection( 0 );
	fgSizer10->Add( m_chDefinitionPlace, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_staticText47 = new wxStaticText( m_pageUserDataType, wxID_ANY, wxT("Definition file:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText47->Wrap( -1 );
	fgSizer10->Add( m_staticText47, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_fpDefinitionFile = new wxFilePickerCtrl( m_pageUserDataType, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE|wxFLP_USE_TEXTCTRL );
	fgSizer10->Add( m_fpDefinitionFile, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	userdataSizer->Add( fgSizer10, 1, wxEXPAND, 5 );
	
	
	m_pageUserDataType->SetSizer( userdataSizer );
	m_pageUserDataType->Layout();
	userdataSizer->Fit( m_pageUserDataType );
	m_pNotebook->AddPage( m_pageUserDataType, wxT("User-define data type"), false );
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
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _VariableDialog::OnInit ) );
	m_eName->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( _VariableDialog::OnNameChange ), NULL, this );
	m_cbMakeValid->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _VariableDialog::OnMakeValid ), NULL, this );
	m_eTypeName->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _VariableDialog::OnUpdateUserDataType ), NULL, this );
	m_chDefinitionPlace->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _VariableDialog::OnUpdateUserDataType ), NULL, this );
	m_fpDefinitionFile->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _VariableDialog::OnUpdateDefinitionFile ), NULL, this );
	m_sciEditor->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _VariableDialog::OnUpdateEditor ), NULL, this );
	bntSizerOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _VariableDialog::OnOk ), NULL, this );
}

_VariableDialog::~_VariableDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _VariableDialog::OnInit ) );
	m_eName->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( _VariableDialog::OnNameChange ), NULL, this );
	m_cbMakeValid->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _VariableDialog::OnMakeValid ), NULL, this );
	m_eTypeName->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _VariableDialog::OnUpdateUserDataType ), NULL, this );
	m_chDefinitionPlace->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _VariableDialog::OnUpdateUserDataType ), NULL, this );
	m_fpDefinitionFile->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _VariableDialog::OnUpdateDefinitionFile ), NULL, this );
	m_sciEditor->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _VariableDialog::OnUpdateEditor ), NULL, this );
	bntSizerOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _VariableDialog::OnOk ), NULL, this );
	
}

_ChoiceDialog::_ChoiceDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	m_stextComment = new wxStaticText( this, wxID_ANY, wxT("Comment"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stextComment->Wrap( -1 );
	mainSizer->Add( m_stextComment, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxArrayString m_chChoiceChoices;
	m_chChoice = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxSize( 300,-1 ), m_chChoiceChoices, 0 );
	m_chChoice->SetSelection( 0 );
	m_chChoice->SetMinSize( wxSize( 300,-1 ) );
	
	mainSizer->Add( m_chChoice, 0, wxALL, 5 );
	
	btnSizer = new wxStdDialogButtonSizer();
	btnSizerOK = new wxButton( this, wxID_OK );
	btnSizer->AddButton( btnSizerOK );
	btnSizer->Realize();
	
	mainSizer->Add( btnSizer, 1, wxALIGN_RIGHT|wxBOTTOM|wxRIGHT, 5 );
	
	
	this->SetSizer( mainSizer );
	this->Layout();
	mainSizer->Fit( this );
	
	this->Centre( wxBOTH );
}

_ChoiceDialog::~_ChoiceDialog()
{
}

_ElementDialog::_ElementDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
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
	mainSizer->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _ElementDialog::OnInit ) );
	m_eName->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( _ElementDialog::OnNameChange ), NULL, this );
	m_cbMakeValid->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _ElementDialog::OnMakeValid ), NULL, this );
	bntSizerOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ElementDialog::OnOk ), NULL, this );
}

_ElementDialog::~_ElementDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _ElementDialog::OnInit ) );
	m_eName->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( _ElementDialog::OnNameChange ), NULL, this );
	m_cbMakeValid->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _ElementDialog::OnMakeValid ), NULL, this );
	bntSizerOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ElementDialog::OnOk ), NULL, this );
	
}

_UpdateCodeDialog::_UpdateCodeDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 400,380 ), wxDefaultSize );
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	m_staticText = new wxStaticText( this, wxID_ANY, wxT("Reference to '' has been found in:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText->Wrap( -1 );
	mainSizer->Add( m_staticText, 0, wxALL|wxEXPAND, 5 );
	
	wxArrayString m_checkListCodeItemsChoices;
	m_checkListCodeItems = new wxCheckListBox( this, wxID_ANY, wxDefaultPosition, wxSize( -1,100 ), m_checkListCodeItemsChoices, wxLB_SORT );
	m_checkListCodeItems->SetMinSize( wxSize( -1,100 ) );
	
	m_menuChecklist = new wxMenu();
	wxMenuItem* menuSelectAll;
	menuSelectAll = new wxMenuItem( m_menuChecklist, IDM_SELECT_ALL, wxString( wxT("SelectAll") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuChecklist->Append( menuSelectAll );
	
	wxMenuItem* menuDeselectAll;
	menuDeselectAll = new wxMenuItem( m_menuChecklist, IDM_DESELECT_ALL, wxString( wxT("Deselect all") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuChecklist->Append( menuDeselectAll );
	
	m_checkListCodeItems->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( _UpdateCodeDialog::m_checkListCodeItemsOnContextMenu ), NULL, this ); 
	
	mainSizer->Add( m_checkListCodeItems, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText33 = new wxStaticText( this, wxID_ANY, wxT("Pattern occurences:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText33->Wrap( -1 );
	mainSizer->Add( m_staticText33, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxBoxSizer* previewSizer;
	previewSizer = new wxBoxSizer( wxHORIZONTAL );
	
	m_scintillaCode = new wxStyledTextCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, wxEmptyString );
	m_scintillaCode->SetUseTabs( true );
	m_scintillaCode->SetTabWidth( 4 );
	m_scintillaCode->SetIndent( 4 );
	m_scintillaCode->SetTabIndents( true );
	m_scintillaCode->SetBackSpaceUnIndents( true );
	m_scintillaCode->SetViewEOL( false );
	m_scintillaCode->SetViewWhiteSpace( false );
	m_scintillaCode->SetMarginWidth( 2, 0 );
	m_scintillaCode->SetIndentationGuides( true );
	m_scintillaCode->SetMarginType( 1, wxSTC_MARGIN_SYMBOL );
	m_scintillaCode->SetMarginMask( 1, wxSTC_MASK_FOLDERS );
	m_scintillaCode->SetMarginWidth( 1, 16);
	m_scintillaCode->SetMarginSensitive( 1, true );
	m_scintillaCode->SetProperty( wxT("fold"), wxT("1") );
	m_scintillaCode->SetFoldFlags( wxSTC_FOLDFLAG_LINEBEFORE_CONTRACTED | wxSTC_FOLDFLAG_LINEAFTER_CONTRACTED );
	m_scintillaCode->SetMarginType( 0, wxSTC_MARGIN_NUMBER );
	m_scintillaCode->SetMarginWidth( 0, m_scintillaCode->TextWidth( wxSTC_STYLE_LINENUMBER, wxT("_99999") ) );
	{
		wxFont font = wxFont( 9, 70, 90, 90, false, wxEmptyString );
		m_scintillaCode->StyleSetFont( wxSTC_STYLE_DEFAULT, font );
	}
	m_scintillaCode->MarkerDefine( wxSTC_MARKNUM_FOLDER, wxSTC_MARK_BOXPLUS );
	m_scintillaCode->MarkerSetBackground( wxSTC_MARKNUM_FOLDER, wxColour( wxT("BLACK") ) );
	m_scintillaCode->MarkerSetForeground( wxSTC_MARKNUM_FOLDER, wxColour( wxT("WHITE") ) );
	m_scintillaCode->MarkerDefine( wxSTC_MARKNUM_FOLDEROPEN, wxSTC_MARK_BOXMINUS );
	m_scintillaCode->MarkerSetBackground( wxSTC_MARKNUM_FOLDEROPEN, wxColour( wxT("BLACK") ) );
	m_scintillaCode->MarkerSetForeground( wxSTC_MARKNUM_FOLDEROPEN, wxColour( wxT("WHITE") ) );
	m_scintillaCode->MarkerDefine( wxSTC_MARKNUM_FOLDERSUB, wxSTC_MARK_EMPTY );
	m_scintillaCode->MarkerDefine( wxSTC_MARKNUM_FOLDEREND, wxSTC_MARK_BOXPLUS );
	m_scintillaCode->MarkerSetBackground( wxSTC_MARKNUM_FOLDEREND, wxColour( wxT("BLACK") ) );
	m_scintillaCode->MarkerSetForeground( wxSTC_MARKNUM_FOLDEREND, wxColour( wxT("WHITE") ) );
	m_scintillaCode->MarkerDefine( wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_BOXMINUS );
	m_scintillaCode->MarkerSetBackground( wxSTC_MARKNUM_FOLDEROPENMID, wxColour( wxT("BLACK") ) );
	m_scintillaCode->MarkerSetForeground( wxSTC_MARKNUM_FOLDEROPENMID, wxColour( wxT("WHITE") ) );
	m_scintillaCode->MarkerDefine( wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_EMPTY );
	m_scintillaCode->MarkerDefine( wxSTC_MARKNUM_FOLDERTAIL, wxSTC_MARK_EMPTY );
	m_scintillaCode->SetSelBackground( true, wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHT ) );
	m_scintillaCode->SetSelForeground( true, wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHTTEXT ) );
	m_scintillaCode->SetFont( wxFont( 9, 70, 90, 90, false, wxEmptyString ) );
	m_scintillaCode->SetMinSize( wxSize( 280,150 ) );
	
	previewSizer->Add( m_scintillaCode, 1, wxEXPAND|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	wxBoxSizer* searchSizer;
	searchSizer = new wxBoxSizer( wxVERTICAL );
	
	m_btnPrev = new wxButton( this, wxID_ANY, wxT("Previous"), wxDefaultPosition, wxDefaultSize, 0 );
	searchSizer->Add( m_btnPrev, 0, wxALL, 5 );
	
	m_btnNext = new wxButton( this, wxID_ANY, wxT("Next"), wxDefaultPosition, wxDefaultSize, 0 );
	searchSizer->Add( m_btnNext, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	previewSizer->Add( searchSizer, 0, wxEXPAND, 5 );
	
	
	mainSizer->Add( previewSizer, 1, wxEXPAND, 5 );
	
	wxBoxSizer* buttonSizer;
	buttonSizer = new wxBoxSizer( wxHORIZONTAL );
	
	m_btnCancel = new wxButton( this, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	buttonSizer->Add( m_btnCancel, 0, wxALL, 5 );
	
	m_btnUpdate = new wxButton( this, wxID_OK, wxT("Update selected"), wxDefaultPosition, wxDefaultSize, 0 );
	buttonSizer->Add( m_btnUpdate, 0, wxTOP|wxBOTTOM|wxRIGHT, 5 );
	
	
	mainSizer->Add( buttonSizer, 0, wxALIGN_RIGHT, 5 );
	
	
	this->SetSizer( mainSizer );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _UpdateCodeDialog::OnInit ) );
	m_checkListCodeItems->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( _UpdateCodeDialog::OnChangeCodeitem ), NULL, this );
	this->Connect( menuSelectAll->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _UpdateCodeDialog::OnSelectAll ) );
	this->Connect( menuDeselectAll->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _UpdateCodeDialog::OnDeselectAll ) );
	m_btnPrev->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _UpdateCodeDialog::OnPrevious ), NULL, this );
	m_btnNext->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _UpdateCodeDialog::OnNext ), NULL, this );
	m_btnCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _UpdateCodeDialog::OnCancel ), NULL, this );
	m_btnUpdate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _UpdateCodeDialog::OnUpdate ), NULL, this );
}

_UpdateCodeDialog::~_UpdateCodeDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _UpdateCodeDialog::OnInit ) );
	m_checkListCodeItems->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( _UpdateCodeDialog::OnChangeCodeitem ), NULL, this );
	this->Disconnect( IDM_SELECT_ALL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _UpdateCodeDialog::OnSelectAll ) );
	this->Disconnect( IDM_DESELECT_ALL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _UpdateCodeDialog::OnDeselectAll ) );
	m_btnPrev->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _UpdateCodeDialog::OnPrevious ), NULL, this );
	m_btnNext->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _UpdateCodeDialog::OnNext ), NULL, this );
	m_btnCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _UpdateCodeDialog::OnCancel ), NULL, this );
	m_btnUpdate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _UpdateCodeDialog::OnUpdate ), NULL, this );
	
	delete m_menuChecklist; 
}

_ScopedElementDialog::_ScopedElementDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 460,330 ), wxDefaultSize );
	
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
	m_pageAdv = new wxPanel( m_pNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* dataTypeSizer;
	dataTypeSizer = new wxFlexGridSizer( 3, 2, 0, 0 );
	dataTypeSizer->AddGrowableCol( 1 );
	dataTypeSizer->SetFlexibleDirection( wxBOTH );
	dataTypeSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText43 = new wxStaticText( m_pageAdv, wxID_ANY, wxT("Access:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText43->Wrap( -1 );
	dataTypeSizer->Add( m_staticText43, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_chAccessChoices;
	m_chAccess = new wxChoice( m_pageAdv, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_chAccessChoices, 0 );
	m_chAccess->SetSelection( 0 );
	dataTypeSizer->Add( m_chAccess, 0, wxALL|wxEXPAND, 5 );
	
	
	m_pageAdv->SetSizer( dataTypeSizer );
	m_pageAdv->Layout();
	dataTypeSizer->Fit( m_pageAdv );
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
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _ScopedElementDialog::OnInit ) );
	m_eName->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( _ScopedElementDialog::OnNameChange ), NULL, this );
	m_cbMakeValid->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _ScopedElementDialog::OnMakeValid ), NULL, this );
	bntSizerOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ScopedElementDialog::OnOk ), NULL, this );
}

_ScopedElementDialog::~_ScopedElementDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _ScopedElementDialog::OnInit ) );
	m_eName->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( _ScopedElementDialog::OnNameChange ), NULL, this );
	m_cbMakeValid->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( _ScopedElementDialog::OnMakeValid ), NULL, this );
	bntSizerOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ScopedElementDialog::OnOk ), NULL, this );
	
}

_ProgressDialog::_ProgressDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	m_stLabel = new wxStaticText( this, wxID_ANY, wxT("Text"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stLabel->Wrap( -1 );
	m_stLabel->SetFont( wxFont( 9, 74, 90, 92, false, wxT("sans") ) );
	
	mainSizer->Add( m_stLabel, 1, wxALL|wxEXPAND, 5 );
	
	m_gaProgress = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxSize( 350,-1 ), wxGA_HORIZONTAL );
	mainSizer->Add( m_gaProgress, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	this->SetSizer( mainSizer );
	this->Layout();
	mainSizer->Fit( this );
	
	this->Centre( wxBOTH );
}

_ProgressDialog::~_ProgressDialog()
{
}
