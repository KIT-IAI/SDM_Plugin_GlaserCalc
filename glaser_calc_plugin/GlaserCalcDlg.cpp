///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "GlaserCalcDlg.h"

///////////////////////////////////////////////////////////////////////////

GlaserCalcDlg::GlaserCalcDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer_1;
	bSizer_1 = new wxBoxSizer( wxVERTICAL );

	wxFlexGridSizer* fgSizer1_1;
	fgSizer1_1 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer1_1->AddGrowableCol( 1 );
	fgSizer1_1->AddGrowableRow( 0 );
	fgSizer1_1->SetFlexibleDirection( wxBOTH );
	fgSizer1_1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_ElementNameText = new wxStaticText( this, wxID_ANY, wxT("Building Element Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_ElementNameText->Wrap( -1 );
	fgSizer1_1->Add( m_ElementNameText, 0, wxALL, 5 );

	m_ElementNameCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	fgSizer1_1->Add( m_ElementNameCtrl, 0, wxALL|wxEXPAND, 5 );

	m_ElementTypeText = new wxStaticText( this, wxID_ANY, wxT("Building Element Type"), wxDefaultPosition, wxDefaultSize, 0 );
	m_ElementTypeText->Wrap( -1 );
	fgSizer1_1->Add( m_ElementTypeText, 0, wxALL, 5 );

	m_ElementTypeCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	fgSizer1_1->Add( m_ElementTypeCtrl, 0, wxALL|wxEXPAND, 5 );


	bSizer_1->Add( fgSizer1_1, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );

	m_grid = new wxGrid( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	m_grid->CreateGrid( 3, 7 );
	m_grid->EnableEditing( true );
	m_grid->EnableGridLines( true );
	m_grid->EnableDragGridSize( false );
	m_grid->SetMargins( 0, 0 );

	// Columns
	m_grid->SetColSize( 0, 84 );
	m_grid->SetColSize( 1, 95 );
	m_grid->SetColSize( 2, 28 );
	m_grid->SetColSize( 3, 59 );
	m_grid->SetColSize( 4, 85 );
	m_grid->SetColSize( 5, 21 );
	m_grid->SetColSize( 6, 29 );
	m_grid->AutoSizeColumns();
	m_grid->EnableDragColMove( false );
	m_grid->EnableDragColSize( true );
	m_grid->SetColLabelValue( 0, wxT("Layer Name") );
	m_grid->SetColLabelValue( 1, wxT("Width [m]") );
	m_grid->SetColLabelValue( 2, wxT("μ") );
	m_grid->SetColLabelValue( 3, wxT("sD [m]") );
	m_grid->SetColLabelValue( 4, wxT("λ [W/(m*K)]") );
	m_grid->SetColLabelValue( 5, wxT("θ [°C]") );
	m_grid->SetColLabelValue( 6, wxT("Ps [Pa]") );
	m_grid->SetColLabelSize( wxGRID_AUTOSIZE );
	m_grid->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Rows
	m_grid->EnableDragRowSize( true );
	m_grid->SetRowLabelSize( 0 );
	m_grid->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance

	// Cell Defaults
	m_grid->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	bSizer2->Add( m_grid, 0, wxALL|wxEXPAND, 5 );

	m_GlaserDiagram = new GlaserDiagram(this);
	bSizer2->Add( m_GlaserDiagram, 1, wxALL|wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer1_2;
	fgSizer1_2 = new wxFlexGridSizer( 1, 2, 0, 0 );
	fgSizer1_2->AddGrowableCol( 1 );
	fgSizer1_2->SetFlexibleDirection( wxBOTH );
	fgSizer1_2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_UValueText = new wxStaticText( this, wxID_ANY, wxT("U-Value"), wxDefaultPosition, wxDefaultSize, 0 );
	m_UValueText->Wrap( -1 );
	fgSizer1_2->Add( m_UValueText, 0, wxALL, 5 );

	m_UValueCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	fgSizer1_2->Add( m_UValueCtrl, 0, wxALL|wxEXPAND, 5 );


	bSizer2->Add( fgSizer1_2, 0, wxEXPAND, 5 );


	bSizer_1->Add( bSizer2, 1, wxEXPAND, 5 );

	m_collapsiblePaneParameter = new wxCollapsiblePane( this, wxID_ANY, wxT("Parameter"), wxDefaultPosition, wxDefaultSize, wxCP_DEFAULT_STYLE );
	m_collapsiblePaneParameter->Collapse( true );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );

	wxString m_ParameterChoiceChoices[] = { wxT("Dew Period"), wxT("Evaporation Period"), wxT("User Defined Period") };
	int m_ParameterChoiceNChoices = sizeof( m_ParameterChoiceChoices ) / sizeof( wxString );
	m_ParameterChoice = new wxChoice( m_collapsiblePaneParameter->GetPane(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_ParameterChoiceNChoices, m_ParameterChoiceChoices, 0 );
	m_ParameterChoice->SetSelection( 0 );
	bSizer3->Add( m_ParameterChoice, 0, wxALL|wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer1_3;
	fgSizer1_3 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer1_3->AddGrowableCol( 1 );
	fgSizer1_3->SetFlexibleDirection( wxBOTH );
	fgSizer1_3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_PhiInsideText = new wxStaticText( m_collapsiblePaneParameter->GetPane(), wxID_ANY, wxT("Φ Inside"), wxDefaultPosition, wxDefaultSize, 0 );
	m_PhiInsideText->Wrap( -1 );
	fgSizer1_3->Add( m_PhiInsideText, 0, wxALL, 5 );

	m_PhiInsideCtrl = new wxTextCtrl( m_collapsiblePaneParameter->GetPane(), wxID_ANY, wxT("0.0"), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizer1_3->Add( m_PhiInsideCtrl, 0, wxALL|wxEXPAND, 5 );

	m_PhiOutsideText = new wxStaticText( m_collapsiblePaneParameter->GetPane(), wxID_ANY, wxT("Φ Outside"), wxDefaultPosition, wxDefaultSize, 0 );
	m_PhiOutsideText->Wrap( -1 );
	fgSizer1_3->Add( m_PhiOutsideText, 0, wxALL, 5 );

	m_PhiOutsideCtrl = new wxTextCtrl( m_collapsiblePaneParameter->GetPane(), wxID_ANY, wxT("0.0"), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizer1_3->Add( m_PhiOutsideCtrl, 0, wxALL|wxEXPAND, 5 );

	m_ThetaInsideText = new wxStaticText( m_collapsiblePaneParameter->GetPane(), wxID_ANY, wxT("θ Inside"), wxDefaultPosition, wxDefaultSize, 0 );
	m_ThetaInsideText->Wrap( -1 );
	fgSizer1_3->Add( m_ThetaInsideText, 0, wxALL, 5 );

	m_ThetaInsideCtrl = new wxTextCtrl( m_collapsiblePaneParameter->GetPane(), wxID_ANY, wxT("0.0"), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizer1_3->Add( m_ThetaInsideCtrl, 0, wxALL|wxEXPAND, 5 );

	m_ThetaOutsideText = new wxStaticText( m_collapsiblePaneParameter->GetPane(), wxID_ANY, wxT("θ Outside"), wxDefaultPosition, wxDefaultSize, 0 );
	m_ThetaOutsideText->Wrap( -1 );
	fgSizer1_3->Add( m_ThetaOutsideText, 0, wxALL, 5 );

	m_ThetaOutsideCtrl = new wxTextCtrl( m_collapsiblePaneParameter->GetPane(), wxID_ANY, wxT("0.0"), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizer1_3->Add( m_ThetaOutsideCtrl, 0, wxALL|wxEXPAND, 5 );

	m_PsInsideText = new wxStaticText( m_collapsiblePaneParameter->GetPane(), wxID_ANY, wxT("Ps Inside"), wxDefaultPosition, wxDefaultSize, 0 );
	m_PsInsideText->Wrap( -1 );
	fgSizer1_3->Add( m_PsInsideText, 0, wxALL, 5 );

	m_PsInsideCtrl = new wxTextCtrl( m_collapsiblePaneParameter->GetPane(), wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizer1_3->Add( m_PsInsideCtrl, 0, wxALL|wxEXPAND, 5 );

	m_PsOutsideText = new wxStaticText( m_collapsiblePaneParameter->GetPane(), wxID_ANY, wxT("Ps Outside"), wxDefaultPosition, wxDefaultSize, 0 );
	m_PsOutsideText->Wrap( -1 );
	fgSizer1_3->Add( m_PsOutsideText, 0, wxALL, 5 );

	m_PsOutsideCtrl = new wxTextCtrl( m_collapsiblePaneParameter->GetPane(), wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizer1_3->Add( m_PsOutsideCtrl, 0, wxALL|wxEXPAND, 5 );


	bSizer3->Add( fgSizer1_3, 1, wxEXPAND, 5 );


	m_collapsiblePaneParameter->GetPane()->SetSizer( bSizer3 );
	m_collapsiblePaneParameter->GetPane()->Layout();
	bSizer3->Fit( m_collapsiblePaneParameter->GetPane() );
	bSizer_1->Add( m_collapsiblePaneParameter, 0, wxEXPAND | wxALL, 5 );


	this->SetSizer( bSizer_1 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_grid->Connect( wxEVT_GRID_CELL_CHANGED, wxGridEventHandler( GlaserCalcDlg::OnGridCmdCellChanged ), NULL, this );
	m_ParameterChoice->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GlaserCalcDlg::OnParameterChoice ), NULL, this );
	m_PhiInsideCtrl->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GlaserCalcDlg::OnPhiInsideKillFocus ), NULL, this );
	m_PhiOutsideCtrl->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GlaserCalcDlg::OnPhiOutsideKillFocus ), NULL, this );
	m_ThetaInsideCtrl->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GlaserCalcDlg::OnThetaInsideKillFocus ), NULL, this );
	m_ThetaOutsideCtrl->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GlaserCalcDlg::OnThetaOutsideKillFocus ), NULL, this );
	m_PsInsideCtrl->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GlaserCalcDlg::OnPsInsideKillFocus ), NULL, this );
	m_PsOutsideCtrl->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GlaserCalcDlg::OnPsOutsideKillFocus ), NULL, this );
}

GlaserCalcDlg::~GlaserCalcDlg()
{
	// Disconnect Events
	m_grid->Disconnect( wxEVT_GRID_CELL_CHANGED, wxGridEventHandler( GlaserCalcDlg::OnGridCmdCellChanged ), NULL, this );
	m_ParameterChoice->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GlaserCalcDlg::OnParameterChoice ), NULL, this );
	m_PhiInsideCtrl->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GlaserCalcDlg::OnPhiInsideKillFocus ), NULL, this );
	m_PhiOutsideCtrl->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GlaserCalcDlg::OnPhiOutsideKillFocus ), NULL, this );
	m_ThetaInsideCtrl->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GlaserCalcDlg::OnThetaInsideKillFocus ), NULL, this );
	m_ThetaOutsideCtrl->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GlaserCalcDlg::OnThetaOutsideKillFocus ), NULL, this );
	m_PsInsideCtrl->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GlaserCalcDlg::OnPsInsideKillFocus ), NULL, this );
	m_PsOutsideCtrl->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GlaserCalcDlg::OnPsOutsideKillFocus ), NULL, this );

}
