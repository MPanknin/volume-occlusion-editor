///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 30 2011)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "UI_Base.h"

///////////////////////////////////////////////////////////////////////////

Frame::Frame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DLIGHT ) );
	
	wxFlexGridSizer* mainSizer;
	mainSizer = new wxFlexGridSizer( 4, 3, 0, 0 );
	mainSizer->SetFlexibleDirection( wxBOTH );
	mainSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxStaticBoxSizer* sizerRendering;
	sizerRendering = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Rendering") ), wxVERTICAL );
	
	wxBoxSizer* m_sizerRendering;
	m_sizerRendering = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* m_sizerTogglePreview;
	m_sizerTogglePreview = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* m_sizerClearColor;
	m_sizerClearColor = new wxBoxSizer( wxHORIZONTAL );
	
	m_clrPickerClearColor = new wxColourPickerCtrl( this, clrPickerClrColor, *wxBLACK, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_sizerClearColor->Add( m_clrPickerClearColor, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText5 = new wxStaticText( this, wxID_ANY, wxT("Background"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	m_sizerClearColor->Add( m_staticText5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_sizerTogglePreview->Add( m_sizerClearColor, 0, 0, 5 );
	
	m_sizerRendering->Add( m_sizerTogglePreview, 0, 0, 5 );
	
	sizerRendering->Add( m_sizerRendering, 1, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	sizerRendering->Add( m_staticline1, 0, wxALL|wxEXPAND, 5 );
	
	m_chkVolume = new wxCheckBox( this, chkVolume, wxT("Render Volume"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerRendering->Add( m_chkVolume, 0, wxALL, 5 );
	
	m_chkOcclusion = new wxCheckBox( this, chkOcclusion, wxT("Occlusion Volume"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerRendering->Add( m_chkOcclusion, 0, wxALL, 5 );
	
	m_staticline4 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	sizerRendering->Add( m_staticline4, 0, wxEXPAND | wxALL, 5 );
	
	m_chkTransfer = new wxCheckBox( this, chkTransfer, wxT("Transfer Function"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerRendering->Add( m_chkTransfer, 0, wxALL, 5 );
	
	m_chkPhong = new wxCheckBox( this, chkPhong, wxT("Phong Illumination"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerRendering->Add( m_chkPhong, 0, wxALL, 5 );
	
	m_staticline3 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	sizerRendering->Add( m_staticline3, 0, wxEXPAND | wxALL, 5 );
	
	m_chkToggleOccSpectrum = new wxCheckBox( this, chkOccSpectrum, wxT("Occlusion Spectrum"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerRendering->Add( m_chkToggleOccSpectrum, 0, wxALL, 5 );
	
	
	sizerRendering->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	sizerRendering->Add( 0, 0, 1, wxEXPAND, 5 );
	
	mainSizer->Add( sizerRendering, 1, wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sizerTransfer;
	sizerTransfer = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Transfer Function") ), wxVERTICAL );
	
	wxBoxSizer* m_sizerComboTransfer;
	m_sizerComboTransfer = new wxBoxSizer( wxHORIZONTAL );
	
	m_comboTransfer = new wxComboBox( this, wxID_ANY, wxT("Magic"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	m_comboTransfer->Append( wxT("AI") );
	m_comboTransfer->Append( wxT("Altimetric") );
	m_comboTransfer->Append( wxT("Chimney") );
	m_comboTransfer->Append( wxT("Depth") );
	m_comboTransfer->Append( wxT("DHI") );
	m_comboTransfer->Append( wxT("Extremes") );
	m_comboTransfer->Append( wxT("Faults") );
	m_comboTransfer->Append( wxT("Faults 2") );
	m_comboTransfer->Append( wxT("Flames") );
	m_comboTransfer->Append( wxT("Forest") );
	m_comboTransfer->Append( wxT("Grey scales") );
	m_comboTransfer->Append( wxT("Ice") );
	m_comboTransfer->Append( wxT("Pastel") );
	m_comboTransfer->Append( wxT("Rainbow") );
	m_comboTransfer->Append( wxT("Red-White-Black") );
	m_comboTransfer->Append( wxT("Red-White-Blue") );
	m_comboTransfer->Append( wxT("Seismics") );
	m_comboTransfer->Append( wxT("Sky") );
	m_comboTransfer->Append( wxT("Experimental") );
	m_comboTransfer->Append( wxT("Magic") );
	m_comboTransfer->Append( wxT("Brown 4grades") );
	m_comboTransfer->Append( wxT("Curvature") );
	m_sizerComboTransfer->Add( m_comboTransfer, 0, wxALL, 5 );
	
	m_btnResetOpacity = new wxButton( this, btnResetOpacity, wxT("Reset Opacity"), wxDefaultPosition, wxDefaultSize, 0 );
	m_sizerComboTransfer->Add( m_btnResetOpacity, 0, wxALL, 5 );
	
	sizerTransfer->Add( m_sizerComboTransfer, 1, wxEXPAND, 5 );
	
	m_staticline12 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	sizerTransfer->Add( m_staticline12, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer30;
	bSizer30 = new wxBoxSizer( wxHORIZONTAL );
	
	m_spinIntensityMult = new wxSpinCtrl( this, spinIntensityMult, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxSP_ARROW_KEYS, 1, 20, 1 );
	bSizer30->Add( m_spinIntensityMult, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText26 = new wxStaticText( this, wxID_ANY, wxT("Intensity Multiplier"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText26->Wrap( -1 );
	bSizer30->Add( m_staticText26, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sizerTransfer->Add( bSizer30, 1, wxEXPAND, 5 );
	
	m_bmpPreviewTransfer = new wxStaticBitmap( this, wxID_ANY, wxBitmap( wxT("data/images/Magic_preview.bmp"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER );
	sizerTransfer->Add( m_bmpPreviewTransfer, 0, wxALL, 5 );
	
	m_staticline6 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	sizerTransfer->Add( m_staticline6, 0, wxEXPAND | wxALL, 5 );
	
	m_staticText4 = new wxStaticText( this, wxID_ANY, wxT("Amplitude Histogram"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	sizerTransfer->Add( m_staticText4, 0, wxALL, 5 );
	
	m_bmpPreviewOpacity = new wxStaticBitmap( this, bmpPreviewOpacity, wxNullBitmap, wxDefaultPosition, wxSize( 256,100 ), wxSIMPLE_BORDER );
	sizerTransfer->Add( m_bmpPreviewOpacity, 0, wxALL, 5 );
	
	mainSizer->Add( sizerTransfer, 1, wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sizerSlices;
	sizerSlices = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Slices") ), wxVERTICAL );
	
	wxBoxSizer* m_sizerSldInline;
	m_sizerSldInline = new wxBoxSizer( wxHORIZONTAL );
	
	m_chkInline = new wxCheckBox( this, wxID_ANY, wxT("Inline"), wxDefaultPosition, wxDefaultSize, 0 );
	m_chkInline->SetValue(true); 
	m_sizerSldInline->Add( m_chkInline, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_sldInline = new wxScrollBar( this, sldInline, wxDefaultPosition, wxDefaultSize, wxSB_HORIZONTAL );
	m_sizerSldInline->Add( m_sldInline, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sizerSlices->Add( m_sizerSldInline, 0, wxEXPAND, 5 );
	
	wxBoxSizer* m_sizerSldCrossline;
	m_sizerSldCrossline = new wxBoxSizer( wxHORIZONTAL );
	
	m_chkCrossline = new wxCheckBox( this, wxID_ANY, wxT("Crossline"), wxDefaultPosition, wxDefaultSize, 0 );
	m_chkCrossline->SetValue(true); 
	m_sizerSldCrossline->Add( m_chkCrossline, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_sldCrossline = new wxScrollBar( this, sldCrossline, wxDefaultPosition, wxDefaultSize, wxSB_HORIZONTAL );
	m_sizerSldCrossline->Add( m_sldCrossline, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sizerSlices->Add( m_sizerSldCrossline, 0, wxEXPAND, 5 );
	
	wxBoxSizer* m_sizerSldTimeline;
	m_sizerSldTimeline = new wxBoxSizer( wxHORIZONTAL );
	
	m_chkTimeline = new wxCheckBox( this, wxID_ANY, wxT("Timeline"), wxDefaultPosition, wxDefaultSize, 0 );
	m_chkTimeline->SetValue(true); 
	m_sizerSldTimeline->Add( m_chkTimeline, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_sldTimeline = new wxScrollBar( this, sldTimeline, wxDefaultPosition, wxDefaultSize, wxSB_HORIZONTAL );
	m_sizerSldTimeline->Add( m_sldTimeline, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sizerSlices->Add( m_sizerSldTimeline, 0, wxEXPAND, 5 );
	
	wxBoxSizer* m_sizerBtnResetSlices;
	m_sizerBtnResetSlices = new wxBoxSizer( wxHORIZONTAL );
	
	
	m_sizerBtnResetSlices->Add( 0, 0, 1, wxALIGN_CENTER_VERTICAL, 5 );
	
	m_btnResetSlices = new wxButton( this, btnResetSlices, wxT("Reset"), wxDefaultPosition, wxDefaultSize, 0 );
	m_sizerBtnResetSlices->Add( m_btnResetSlices, 0, wxALL, 5 );
	
	sizerSlices->Add( m_sizerBtnResetSlices, 1, wxEXPAND, 5 );
	
	m_staticline11 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	sizerSlices->Add( m_staticline11, 0, wxEXPAND | wxALL, 5 );
	
	m_staticText18 = new wxStaticText( this, wxID_ANY, wxT("Clipping"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText18->Wrap( -1 );
	sizerSlices->Add( m_staticText18, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer202;
	bSizer202 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText192 = new wxStaticText( this, wxID_ANY, wxT("x"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText192->Wrap( -1 );
	bSizer202->Add( m_staticText192, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_spinXMax = new wxSpinCtrl( this, spinXMax, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxSP_ARROW_KEYS, 0, 100, 100 );
	bSizer202->Add( m_spinXMax, 0, wxALL, 5 );
	
	m_spinXMin = new wxSpinCtrl( this, spinXMin, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxSP_ARROW_KEYS, 0, 100, 0 );
	bSizer202->Add( m_spinXMin, 0, wxALL, 5 );
	
	sizerSlices->Add( bSizer202, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer201;
	bSizer201 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText191 = new wxStaticText( this, wxID_ANY, wxT("y"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText191->Wrap( -1 );
	bSizer201->Add( m_staticText191, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_spinYMax = new wxSpinCtrl( this, spinYMax, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxSP_ARROW_KEYS, 0, 100, 100 );
	bSizer201->Add( m_spinYMax, 0, wxALL, 5 );
	
	m_spinYMin = new wxSpinCtrl( this, spinYMin, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxSP_ARROW_KEYS, 0, 100, 0 );
	bSizer201->Add( m_spinYMin, 0, wxALL, 5 );
	
	sizerSlices->Add( bSizer201, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText19 = new wxStaticText( this, wxID_ANY, wxT("z"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText19->Wrap( -1 );
	bSizer20->Add( m_staticText19, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_spinZMax = new wxSpinCtrl( this, spinZMax, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxSP_ARROW_KEYS, 0, 100, 100 );
	bSizer20->Add( m_spinZMax, 0, wxALL, 5 );
	
	m_spinZMin = new wxSpinCtrl( this, spinZMin, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxSP_ARROW_KEYS, 0, 100, 0 );
	bSizer20->Add( m_spinZMin, 0, wxALL, 5 );
	
	sizerSlices->Add( bSizer20, 1, wxEXPAND, 5 );
	
	mainSizer->Add( sizerSlices, 1, wxALL|wxEXPAND, 5 );
	
	this->SetSizer( mainSizer );
	this->Layout();
	mainSizer->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_IDLE, wxIdleEventHandler( Frame::OnIdle ) );
	m_clrPickerClearColor->Connect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( Frame::OnColourChanged ), NULL, this );
	m_chkVolume->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Frame::OnCheckBox ), NULL, this );
	m_chkOcclusion->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Frame::OnCheckBox ), NULL, this );
	m_chkTransfer->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Frame::OnCheckBox ), NULL, this );
	m_chkPhong->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Frame::OnCheckBox ), NULL, this );
	m_chkToggleOccSpectrum->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Frame::OnCheckBox ), NULL, this );
	m_comboTransfer->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( Frame::OnComboBox ), NULL, this );
	m_btnResetOpacity->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Frame::OnButtonClick ), NULL, this );
	m_spinIntensityMult->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Frame::OnSpinCtrl ), NULL, this );
	m_spinIntensityMult->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Frame::OnSpinCtrl ), NULL, this );
	m_bmpPreviewOpacity->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( Frame::OnLeftDown ), NULL, this );
	m_bmpPreviewOpacity->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( Frame::OnLeftUp ), NULL, this );
	m_bmpPreviewOpacity->Connect( wxEVT_MOTION, wxMouseEventHandler( Frame::OnMotion ), NULL, this );
	m_bmpPreviewOpacity->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( Frame::OnRightDown ), NULL, this );
	m_bmpPreviewOpacity->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( Frame::OnRightUp ), NULL, this );
	m_chkInline->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Frame::OnCheckBox ), NULL, this );
	m_sldInline->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldInline->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldInline->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldInline->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldInline->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldInline->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldInline->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldInline->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldInline->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldInline->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_chkCrossline->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Frame::OnCheckBox ), NULL, this );
	m_sldCrossline->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldCrossline->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldCrossline->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldCrossline->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldCrossline->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldCrossline->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldCrossline->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldCrossline->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldCrossline->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_chkTimeline->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Frame::OnCheckBox ), NULL, this );
	m_sldTimeline->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldTimeline->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldTimeline->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldTimeline->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldTimeline->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldTimeline->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldTimeline->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldTimeline->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldTimeline->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldTimeline->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_spinXMax->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Frame::OnSpinCtrl ), NULL, this );
	m_spinXMin->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Frame::OnSpinCtrl ), NULL, this );
	m_spinXMin->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Frame::OnSpinCtrl ), NULL, this );
	m_spinYMax->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Frame::OnSpinCtrl ), NULL, this );
	m_spinYMax->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Frame::OnSpinCtrl ), NULL, this );
	m_spinYMin->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Frame::OnSpinCtrl ), NULL, this );
	m_spinYMin->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Frame::OnSpinCtrl ), NULL, this );
	m_spinZMax->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Frame::OnSpinCtrl ), NULL, this );
	m_spinZMax->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Frame::OnSpinCtrl ), NULL, this );
	m_spinZMin->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Frame::OnSpinCtrl ), NULL, this );
	m_spinZMin->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Frame::OnSpinCtrl ), NULL, this );
}

Frame::~Frame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_IDLE, wxIdleEventHandler( Frame::OnIdle ) );
	m_clrPickerClearColor->Disconnect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( Frame::OnColourChanged ), NULL, this );
	m_chkVolume->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Frame::OnCheckBox ), NULL, this );
	m_chkOcclusion->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Frame::OnCheckBox ), NULL, this );
	m_chkTransfer->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Frame::OnCheckBox ), NULL, this );
	m_chkPhong->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Frame::OnCheckBox ), NULL, this );
	m_chkToggleOccSpectrum->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Frame::OnCheckBox ), NULL, this );
	m_comboTransfer->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( Frame::OnComboBox ), NULL, this );
	m_btnResetOpacity->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Frame::OnButtonClick ), NULL, this );
	m_spinIntensityMult->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Frame::OnSpinCtrl ), NULL, this );
	m_spinIntensityMult->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Frame::OnSpinCtrl ), NULL, this );
	m_bmpPreviewOpacity->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( Frame::OnLeftDown ), NULL, this );
	m_bmpPreviewOpacity->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( Frame::OnLeftUp ), NULL, this );
	m_bmpPreviewOpacity->Disconnect( wxEVT_MOTION, wxMouseEventHandler( Frame::OnMotion ), NULL, this );
	m_bmpPreviewOpacity->Disconnect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( Frame::OnRightDown ), NULL, this );
	m_bmpPreviewOpacity->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( Frame::OnRightUp ), NULL, this );
	m_chkInline->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Frame::OnCheckBox ), NULL, this );
	m_sldInline->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldInline->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldInline->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldInline->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldInline->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldInline->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldInline->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldInline->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldInline->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldInline->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_chkCrossline->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Frame::OnCheckBox ), NULL, this );
	m_sldCrossline->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldCrossline->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldCrossline->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldCrossline->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldCrossline->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldCrossline->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldCrossline->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldCrossline->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldCrossline->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_chkTimeline->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Frame::OnCheckBox ), NULL, this );
	m_sldTimeline->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldTimeline->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldTimeline->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldTimeline->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldTimeline->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldTimeline->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldTimeline->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldTimeline->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldTimeline->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_sldTimeline->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( Frame::OnSlider ), NULL, this );
	m_spinXMax->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Frame::OnSpinCtrl ), NULL, this );
	m_spinXMin->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Frame::OnSpinCtrl ), NULL, this );
	m_spinXMin->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Frame::OnSpinCtrl ), NULL, this );
	m_spinYMax->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Frame::OnSpinCtrl ), NULL, this );
	m_spinYMax->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Frame::OnSpinCtrl ), NULL, this );
	m_spinYMin->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Frame::OnSpinCtrl ), NULL, this );
	m_spinYMin->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Frame::OnSpinCtrl ), NULL, this );
	m_spinZMax->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Frame::OnSpinCtrl ), NULL, this );
	m_spinZMax->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Frame::OnSpinCtrl ), NULL, this );
	m_spinZMin->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Frame::OnSpinCtrl ), NULL, this );
	m_spinZMin->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Frame::OnSpinCtrl ), NULL, this );
	
}

FrameOccGen::FrameOccGen( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DLIGHT ) );
	
	wxFlexGridSizer* sizerOccGen;
	sizerOccGen = new wxFlexGridSizer( 2, 2, 0, 0 );
	sizerOccGen->SetFlexibleDirection( wxBOTH );
	sizerOccGen->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxStaticBoxSizer* m_sizerSpectrum;
	m_sizerSpectrum = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Crossplot") ), wxVERTICAL );
	
	m_bmpSpectrum = new wxStaticBitmap( this, bmpSpectrum, wxNullBitmap, wxDefaultPosition, wxSize( 512,512 ), wxFULL_REPAINT_ON_RESIZE|wxSIMPLE_BORDER );
	m_bmpSpectrum->Enable( false );
	
	m_sizerSpectrum->Add( m_bmpSpectrum, 0, wxALL, 10 );
	
	sizerOccGen->Add( m_sizerSpectrum, 1, wxEXPAND|wxALL, 5 );
	
	this->SetSizer( sizerOccGen );
	this->Layout();
	sizerOccGen->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_IDLE, wxIdleEventHandler( FrameOccGen::OnIdle ) );
	this->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( FrameOccGen::OnLeftDown ) );
	this->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( FrameOccGen::OnLeftUp ) );
	this->Connect( wxEVT_MOTION, wxMouseEventHandler( FrameOccGen::OnMotion ) );
	this->Connect( wxEVT_PAINT, wxPaintEventHandler( FrameOccGen::OnPaint ) );
}

FrameOccGen::~FrameOccGen()
{
	// Disconnect Events
	this->Disconnect( wxEVT_IDLE, wxIdleEventHandler( FrameOccGen::OnIdle ) );
	this->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( FrameOccGen::OnLeftDown ) );
	this->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( FrameOccGen::OnLeftUp ) );
	this->Disconnect( wxEVT_MOTION, wxMouseEventHandler( FrameOccGen::OnMotion ) );
	this->Disconnect( wxEVT_PAINT, wxPaintEventHandler( FrameOccGen::OnPaint ) );
	
}

ControlPoint::ControlPoint( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	this->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHT ) );
	this->SetBackgroundColour( wxColour( 51, 153, 255 ) );
	
	
	// Connect Events
	this->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( ControlPoint::OnLeftDown ) );
	this->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( ControlPoint::OnLeftUp ) );
	this->Connect( wxEVT_MOTION, wxMouseEventHandler( ControlPoint::OnMotion ) );
	this->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( ControlPoint::OnRightUp ) );
}

ControlPoint::~ControlPoint()
{
	// Disconnect Events
	this->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( ControlPoint::OnLeftDown ) );
	this->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( ControlPoint::OnLeftUp ) );
	this->Disconnect( wxEVT_MOTION, wxMouseEventHandler( ControlPoint::OnMotion ) );
	this->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( ControlPoint::OnRightUp ) );
	
}

PolyPoint::PolyPoint( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	this->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHT ) );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHT ) );
	this->SetToolTip( wxT("x : y") );
	
	
	// Connect Events
	this->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( PolyPoint::OnLeftDown ) );
	this->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( PolyPoint::OnLeftUp ) );
	this->Connect( wxEVT_MOTION, wxMouseEventHandler( PolyPoint::OnMotion ) );
	this->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( PolyPoint::OnRightUp ) );
}

PolyPoint::~PolyPoint()
{
	// Disconnect Events
	this->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( PolyPoint::OnLeftDown ) );
	this->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( PolyPoint::OnLeftUp ) );
	this->Disconnect( wxEVT_MOTION, wxMouseEventHandler( PolyPoint::OnMotion ) );
	this->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( PolyPoint::OnRightUp ) );
	
}

PolyPoint_back::PolyPoint_back( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	this->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHT ) );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHT ) );
	
	
	// Connect Events
	this->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( PolyPoint_back::OnLeftDown ) );
	this->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( PolyPoint_back::OnLeftUp ) );
	this->Connect( wxEVT_MOTION, wxMouseEventHandler( PolyPoint_back::OnMotion ) );
	this->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( PolyPoint_back::OnRightUp ) );
}

PolyPoint_back::~PolyPoint_back()
{
	// Disconnect Events
	this->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( PolyPoint_back::OnLeftDown ) );
	this->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( PolyPoint_back::OnLeftUp ) );
	this->Disconnect( wxEVT_MOTION, wxMouseEventHandler( PolyPoint_back::OnMotion ) );
	this->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( PolyPoint_back::OnRightUp ) );
	
}

Extractor::Extractor( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DLIGHT ) );
	
	wxGridSizer* m_sizerExtractorMain;
	m_sizerExtractorMain = new wxGridSizer( 1, 1, 0, 0 );
	
	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxStaticBoxSizer* m_sizerInputVolume;
	m_sizerInputVolume = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Input Volume") ), wxVERTICAL );
	
	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxVERTICAL );
	
	m_pickerInputVolume = new wxFilePickerCtrl( this, pickerInputVolume, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_CHANGE_DIR|wxFLP_DEFAULT_STYLE|wxFLP_FILE_MUST_EXIST );
	bSizer19->Add( m_pickerInputVolume, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer22;
	bSizer22 = new wxBoxSizer( wxHORIZONTAL );
	
	m_comboVoxelSize = new wxComboBox( this, comboVoxelSize, wxT("8 bit"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	m_comboVoxelSize->Append( wxT("8 bit ") );
	m_comboVoxelSize->Append( wxT("16 bit") );
	bSizer22->Add( m_comboVoxelSize, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_comboEndian = new wxComboBox( this, comboEndian, wxT("Little-endian"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	m_comboEndian->Append( wxT("Big-endian") );
	m_comboEndian->Append( wxT("Little-endian") );
	bSizer22->Add( m_comboEndian, 0, wxALL, 5 );
	
	bSizer19->Add( bSizer22, 1, wxEXPAND, 5 );
	
	m_sizerInputVolume->Add( bSizer19, 1, wxEXPAND, 5 );
	
	wxBoxSizer* m_sizerHeader;
	m_sizerHeader = new wxBoxSizer( wxHORIZONTAL );
	
	
	m_sizerHeader->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	m_sizerHeader->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_sizerInputVolume->Add( m_sizerHeader, 0, wxEXPAND, 5 );
	
	m_staticline13 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	m_sizerInputVolume->Add( m_staticline13, 0, wxEXPAND | wxALL, 5 );
	
	m_staticText25 = new wxStaticText( this, wxID_ANY, wxT("Dimensions"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText25->Wrap( -1 );
	m_sizerInputVolume->Add( m_staticText25, 0, wxALL, 5 );
	
	wxBoxSizer* m_sizerInputDimensions;
	m_sizerInputDimensions = new wxBoxSizer( wxHORIZONTAL );
	
	m_txtInputWidth = new wxTextCtrl( this, txtInputWidth, wxT("0"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	m_sizerInputDimensions->Add( m_txtInputWidth, 1, wxALL, 5 );
	
	m_staticText14 = new wxStaticText( this, wxID_ANY, wxT("x"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText14->Wrap( -1 );
	m_sizerInputDimensions->Add( m_staticText14, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_txtInputHeight = new wxTextCtrl( this, txtInputHeight, wxT("0"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	m_sizerInputDimensions->Add( m_txtInputHeight, 1, wxALL, 5 );
	
	m_staticText141 = new wxStaticText( this, wxID_ANY, wxT("y"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText141->Wrap( -1 );
	m_sizerInputDimensions->Add( m_staticText141, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_txtInputDepth = new wxTextCtrl( this, txtInputDepth, wxT("0"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	m_sizerInputDimensions->Add( m_txtInputDepth, 1, wxALL, 5 );
	
	m_staticText142 = new wxStaticText( this, wxID_ANY, wxT("z"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText142->Wrap( -1 );
	m_sizerInputDimensions->Add( m_staticText142, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_txtInputHeader = new wxTextCtrl( this, txtInputHeader, wxT("0"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	m_sizerInputDimensions->Add( m_txtInputHeader, 0, wxALL, 5 );
	
	m_staticText1423 = new wxStaticText( this, wxID_ANY, wxT("Header"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1423->Wrap( -1 );
	m_sizerInputDimensions->Add( m_staticText1423, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_sizerInputVolume->Add( m_sizerInputDimensions, 0, wxEXPAND, 5 );
	
	fgSizer3->Add( m_sizerInputVolume, 1, wxEXPAND|wxALL, 5 );
	
	wxStaticBoxSizer* m_sizerOutputVolume;
	m_sizerOutputVolume = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Output Volume") ), wxVERTICAL );
	
	m_pickerOutputVolume = new wxFilePickerCtrl( this, pickerOutputVolume, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_CHANGE_DIR|wxFLP_DEFAULT_STYLE|wxFLP_SAVE );
	m_sizerOutputVolume->Add( m_pickerOutputVolume, 0, wxALL, 5 );
	
	m_staticline14 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	m_sizerOutputVolume->Add( m_staticline14, 0, wxEXPAND | wxALL, 5 );
	
	m_staticText26 = new wxStaticText( this, wxID_ANY, wxT("Dimensions"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText26->Wrap( -1 );
	m_sizerOutputVolume->Add( m_staticText26, 0, wxALL, 5 );
	
	wxBoxSizer* m_sizerOutputDimensions;
	m_sizerOutputDimensions = new wxBoxSizer( wxHORIZONTAL );
	
	m_txtOutputWidth = new wxTextCtrl( this, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	m_sizerOutputDimensions->Add( m_txtOutputWidth, 0, wxALL, 5 );
	
	m_staticText143 = new wxStaticText( this, wxID_ANY, wxT("x"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText143->Wrap( -1 );
	m_sizerOutputDimensions->Add( m_staticText143, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_txtOutputHeight = new wxTextCtrl( this, txtOutputHeight, wxT("0"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	m_sizerOutputDimensions->Add( m_txtOutputHeight, 0, wxALL, 5 );
	
	m_staticText1411 = new wxStaticText( this, wxID_ANY, wxT("y"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1411->Wrap( -1 );
	m_sizerOutputDimensions->Add( m_staticText1411, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_txtOutputDepth = new wxTextCtrl( this, txtOutputDepth, wxT("0"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	m_sizerOutputDimensions->Add( m_txtOutputDepth, 0, wxALL, 5 );
	
	m_staticText1421 = new wxStaticText( this, wxID_ANY, wxT("z"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1421->Wrap( -1 );
	m_sizerOutputDimensions->Add( m_staticText1421, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_sizerOutputVolume->Add( m_sizerOutputDimensions, 0, wxEXPAND, 5 );
	
	m_staticline10 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	m_sizerOutputVolume->Add( m_staticline10, 0, wxEXPAND | wxALL, 5 );
	
	m_staticText27 = new wxStaticText( this, wxID_ANY, wxT("Offset"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText27->Wrap( -1 );
	m_sizerOutputVolume->Add( m_staticText27, 0, wxALL, 5 );
	
	wxBoxSizer* m_sizerOffsets;
	m_sizerOffsets = new wxBoxSizer( wxHORIZONTAL );
	
	m_txtXOff = new wxTextCtrl( this, txtXOff, wxT("0"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	m_sizerOffsets->Add( m_txtXOff, 0, wxALL, 5 );
	
	m_staticText144 = new wxStaticText( this, wxID_ANY, wxT("x Off"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText144->Wrap( -1 );
	m_sizerOffsets->Add( m_staticText144, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_txtYOff = new wxTextCtrl( this, txtYOff, wxT("0"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	m_sizerOffsets->Add( m_txtYOff, 0, wxALL, 5 );
	
	m_staticText1412 = new wxStaticText( this, wxID_ANY, wxT("y Off"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1412->Wrap( -1 );
	m_sizerOffsets->Add( m_staticText1412, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_txtZOff = new wxTextCtrl( this, txtZOff, wxT("0"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	m_sizerOffsets->Add( m_txtZOff, 0, wxALL, 5 );
	
	m_staticText1422 = new wxStaticText( this, wxID_ANY, wxT("z Off"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1422->Wrap( -1 );
	m_sizerOffsets->Add( m_staticText1422, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_sizerOutputVolume->Add( m_sizerOffsets, 0, wxEXPAND, 5 );
	
	m_staticline16 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	m_sizerOutputVolume->Add( m_staticline16, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* m_sizerBtnExtract;
	m_sizerBtnExtract = new wxBoxSizer( wxHORIZONTAL );
	
	m_btnExtract = new wxButton( this, btnExtract, wxT("Extract"), wxDefaultPosition, wxDefaultSize, 0 );
	m_sizerBtnExtract->Add( m_btnExtract, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_sizerOutputVolume->Add( m_sizerBtnExtract, 0, wxEXPAND, 5 );
	
	fgSizer3->Add( m_sizerOutputVolume, 0, wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* m_sizerVisMapping;
	m_sizerVisMapping = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Visibility Mapping") ), wxVERTICAL );
	
	m_bmpVisMapping = new wxStaticBitmap( this, bmpVisMapping, wxNullBitmap, wxDefaultPosition, wxSize( 256,100 ), wxSIMPLE_BORDER );
	m_sizerVisMapping->Add( m_bmpVisMapping, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer( wxHORIZONTAL );
	
	m_txtPointCoords = new wxTextCtrl( this, txtPointCoords, wxEmptyString, wxDefaultPosition, wxSize( 150,-1 ), 0 );
	m_txtPointCoords->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DLIGHT ) );
	
	bSizer18->Add( m_txtPointCoords, 0, wxALL, 5 );
	
	m_btnReset = new wxButton( this, btnReset, wxT("Reset"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer18->Add( m_btnReset, 0, wxALL, 5 );
	
	m_sizerVisMapping->Add( bSizer18, 1, wxEXPAND, 5 );
	
	fgSizer3->Add( m_sizerVisMapping, 1, wxEXPAND|wxALL, 5 );
	
	wxStaticBoxSizer* m_sizerOcclusion;
	m_sizerOcclusion = new wxStaticBoxSizer( new wxStaticBox( this, sizerOcclusion, wxT("Occlusion ") ), wxVERTICAL );
	
	wxBoxSizer* m_sizerOutputDimensions1;
	m_sizerOutputDimensions1 = new wxBoxSizer( wxHORIZONTAL );
	
	m_txtRadius = new wxTextCtrl( this, txtRadius, wxT("5"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	m_sizerOutputDimensions1->Add( m_txtRadius, 0, wxALL, 5 );
	
	m_staticText1431 = new wxStaticText( this, wxID_ANY, wxT("Radius"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1431->Wrap( -1 );
	m_sizerOutputDimensions1->Add( m_staticText1431, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_txtScale = new wxTextCtrl( this, txtScale, wxT("1"), wxDefaultPosition, wxSize( 35,-1 ), 0 );
	m_sizerOutputDimensions1->Add( m_txtScale, 0, wxALL, 5 );
	
	m_staticText14111 = new wxStaticText( this, wxID_ANY, wxT("Scale"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText14111->Wrap( -1 );
	m_sizerOutputDimensions1->Add( m_staticText14111, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_sizerOcclusion->Add( m_sizerOutputDimensions1, 1, wxEXPAND, 5 );
	
	wxBoxSizer* m_sizerBtnExtract1;
	m_sizerBtnExtract1 = new wxBoxSizer( wxHORIZONTAL );
	
	m_btnLaunch = new wxButton( this, btnLaunch, wxT("Launch"), wxDefaultPosition, wxDefaultSize, 0 );
	m_sizerBtnExtract1->Add( m_btnLaunch, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_sizerOcclusion->Add( m_sizerBtnExtract1, 1, wxEXPAND, 5 );
	
	fgSizer3->Add( m_sizerOcclusion, 1, wxEXPAND|wxALL, 5 );
	
	m_sizerExtractorMain->Add( fgSizer3, 1, wxEXPAND, 5 );
	
	this->SetSizer( m_sizerExtractorMain );
	this->Layout();
	m_sizerExtractorMain->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_IDLE, wxIdleEventHandler( Extractor::OnIdle ) );
	this->Connect( wxEVT_PAINT, wxPaintEventHandler( Extractor::OnPaint ) );
	m_pickerInputVolume->Connect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( Extractor::OnFileChanged ), NULL, this );
	m_comboVoxelSize->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( Extractor::OnComboBox ), NULL, this );
	m_comboEndian->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( Extractor::OnComboBox ), NULL, this );
	m_pickerOutputVolume->Connect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( Extractor::OnFileChanged ), NULL, this );
	m_btnExtract->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Extractor::OnButtonClick ), NULL, this );
	m_bmpVisMapping->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( Extractor::OnLeftDown ), NULL, this );
	m_bmpVisMapping->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( Extractor::OnLeftUp ), NULL, this );
	m_bmpVisMapping->Connect( wxEVT_MOTION, wxMouseEventHandler( Extractor::OnMotion ), NULL, this );
	m_btnReset->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Extractor::OnButtonClick ), NULL, this );
	m_btnLaunch->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Extractor::OnButtonClick ), NULL, this );
}

Extractor::~Extractor()
{
	// Disconnect Events
	this->Disconnect( wxEVT_IDLE, wxIdleEventHandler( Extractor::OnIdle ) );
	this->Disconnect( wxEVT_PAINT, wxPaintEventHandler( Extractor::OnPaint ) );
	m_pickerInputVolume->Disconnect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( Extractor::OnFileChanged ), NULL, this );
	m_comboVoxelSize->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( Extractor::OnComboBox ), NULL, this );
	m_comboEndian->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( Extractor::OnComboBox ), NULL, this );
	m_pickerOutputVolume->Disconnect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( Extractor::OnFileChanged ), NULL, this );
	m_btnExtract->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Extractor::OnButtonClick ), NULL, this );
	m_bmpVisMapping->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( Extractor::OnLeftDown ), NULL, this );
	m_bmpVisMapping->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( Extractor::OnLeftUp ), NULL, this );
	m_bmpVisMapping->Disconnect( wxEVT_MOTION, wxMouseEventHandler( Extractor::OnMotion ), NULL, this );
	m_btnReset->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Extractor::OnButtonClick ), NULL, this );
	m_btnLaunch->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Extractor::OnButtonClick ), NULL, this );
	
}

Plotter::Plotter( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxGridSizer* gSizer2;
	gSizer2 = new wxGridSizer( 1, 1, 0, 0 );
	
	wxStaticBoxSizer* sbSizer7;
	sbSizer7 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Crossplot") ), wxVERTICAL );
	
	m_bitmap4 = new wxStaticBitmap( this, wxID_ANY, wxBitmap( wxT("data/images/occ_spectrum.bmp"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER );
	sbSizer7->Add( m_bitmap4, 0, wxALL, 5 );
	
	gSizer2->Add( sbSizer7, 1, wxEXPAND|wxALL, 5 );
	
	this->SetSizer( gSizer2 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( Plotter::OnLeftDOwn ) );
	this->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( Plotter::OnLeftUp ) );
	this->Connect( wxEVT_MOTION, wxMouseEventHandler( Plotter::OnMotion ) );
	this->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( Plotter::OnRightDown ) );
}

Plotter::~Plotter()
{
	// Disconnect Events
	this->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( Plotter::OnLeftDOwn ) );
	this->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( Plotter::OnLeftUp ) );
	this->Disconnect( wxEVT_MOTION, wxMouseEventHandler( Plotter::OnMotion ) );
	this->Disconnect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( Plotter::OnRightDown ) );
	
}

Container::Container( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	m_menubar1 = new wxMenuBar( 0 );
	m_menuFile = new wxMenu();
	wxMenuItem* m_menuItemOpen;
	m_menuItemOpen = new wxMenuItem( m_menuFile, menuItemOpen, wxString( wxT("Open") ) + wxT('\t') + wxT("ctrl+o"), wxEmptyString, wxITEM_NORMAL );
	m_menuFile->Append( m_menuItemOpen );
	
	wxMenuItem* m_separator2;
	m_separator2 = m_menuFile->AppendSeparator();
	
	wxMenuItem* m_menuItemImportRaw;
	m_menuItemImportRaw = new wxMenuItem( m_menuFile, menuItemImportRaw, wxString( wxT("Import Raw") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuFile->Append( m_menuItemImportRaw );
	
	wxMenuItem* m_menuItemExportRaw;
	m_menuItemExportRaw = new wxMenuItem( m_menuFile, menuItemExportRaw, wxString( wxT("Export Raw") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuFile->Append( m_menuItemExportRaw );
	
	wxMenuItem* m_separator21;
	m_separator21 = m_menuFile->AppendSeparator();
	
	wxMenuItem* m_menuItemImportSegY;
	m_menuItemImportSegY = new wxMenuItem( m_menuFile, menuItemImportSegY, wxString( wxT("Import SegY") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuFile->Append( m_menuItemImportSegY );
	
	wxMenuItem* m_menuItemExportSegY;
	m_menuItemExportSegY = new wxMenuItem( m_menuFile, menuItemExportSegY, wxString( wxT("Export SegY") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuFile->Append( m_menuItemExportSegY );
	
	wxMenuItem* m_separator1;
	m_separator1 = m_menuFile->AppendSeparator();
	
	wxMenuItem* m_menuItemExit;
	m_menuItemExit = new wxMenuItem( m_menuFile, menuItemExit, wxString( wxT("Exit") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuFile->Append( m_menuItemExit );
	
	m_menubar1->Append( m_menuFile, wxT("File") ); 
	
	m_menuView = new wxMenu();
	wxMenuItem* m_menuItemColorTable;
	m_menuItemColorTable = new wxMenuItem( m_menuView, menuItemColorTable, wxString( wxT("Color Table Editor") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuView->Append( m_menuItemColorTable );
	
	wxMenuItem* m_separator3;
	m_separator3 = m_menuView->AppendSeparator();
	
	wxMenuItem* m_menuItemOcclusionGeneration;
	m_menuItemOcclusionGeneration = new wxMenuItem( m_menuView, menuItemOcclusionGeneration, wxString( wxT("Occlusion Generation") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuView->Append( m_menuItemOcclusionGeneration );
	
	wxMenuItem* m_menuItemOcclusionSpectrum;
	m_menuItemOcclusionSpectrum = new wxMenuItem( m_menuView, menuItemOcclusionSpectrum, wxString( wxT("Occlusion Spectrum") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuView->Append( m_menuItemOcclusionSpectrum );
	
	wxMenuItem* m_separator31;
	m_separator31 = m_menuView->AppendSeparator();
	
	wxMenuItem* m_menuItemDepthBuffer;
	m_menuItemDepthBuffer = new wxMenuItem( m_menuView, menuItemDepthBuffer, wxString( wxT("Depth Buffer") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuView->Append( m_menuItemDepthBuffer );
	
	m_menubar1->Append( m_menuView, wxT("View") ); 
	
	this->SetMenuBar( m_menubar1 );
	
	wxBoxSizer* bSizer56;
	bSizer56 = new wxBoxSizer( wxVERTICAL );
	
	m_splitterMain = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D|wxSP_NO_XP_THEME );
	m_splitterMain->SetSashGravity( 0 );
	m_splitterMain->SetMinimumPaneSize( 1 );
	
	m_panel3 = new wxPanel( m_splitterMain, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel3->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_APPWORKSPACE ) );
	
	m_panel4 = new wxPanel( m_splitterMain, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer57;
	bSizer57 = new wxBoxSizer( wxVERTICAL );
	
	m_textLogOut = new wxTextCtrl( m_panel4, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTE_MULTILINE|wxTE_READONLY|wxTE_WORDWRAP );
	bSizer57->Add( m_textLogOut, 1, wxALL|wxEXPAND, 5 );
	
	m_panel4->SetSizer( bSizer57 );
	m_panel4->Layout();
	bSizer57->Fit( m_panel4 );
	m_splitterMain->SplitHorizontally( m_panel3, m_panel4, -1 );
	bSizer56->Add( m_splitterMain, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer56 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_IDLE, wxIdleEventHandler( Container::OnIdle ) );
	this->Connect( m_menuItemOpen->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( Container::OnMenu ) );
	this->Connect( m_menuItemImportRaw->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( Container::OnMenu ) );
	this->Connect( m_menuItemExportRaw->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( Container::OnMenu ) );
	this->Connect( m_menuItemImportSegY->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( Container::OnMenu ) );
	this->Connect( m_menuItemExportSegY->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( Container::OnMenu ) );
	this->Connect( m_menuItemExit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( Container::OnMenu ) );
	this->Connect( m_menuItemColorTable->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( Container::OnMenu ) );
	this->Connect( m_menuItemOcclusionGeneration->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( Container::OnMenu ) );
	this->Connect( m_menuItemOcclusionSpectrum->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( Container::OnMenu ) );
	this->Connect( m_menuItemDepthBuffer->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( Container::OnMenu ) );
}

Container::~Container()
{
	// Disconnect Events
	this->Disconnect( wxEVT_IDLE, wxIdleEventHandler( Container::OnIdle ) );
	this->Disconnect( menuItemOpen, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( Container::OnMenu ) );
	this->Disconnect( menuItemImportRaw, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( Container::OnMenu ) );
	this->Disconnect( menuItemExportRaw, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( Container::OnMenu ) );
	this->Disconnect( menuItemImportSegY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( Container::OnMenu ) );
	this->Disconnect( menuItemExportSegY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( Container::OnMenu ) );
	this->Disconnect( menuItemExit, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( Container::OnMenu ) );
	this->Disconnect( menuItemColorTable, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( Container::OnMenu ) );
	this->Disconnect( menuItemOcclusionGeneration, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( Container::OnMenu ) );
	this->Disconnect( menuItemOcclusionSpectrum, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( Container::OnMenu ) );
	this->Disconnect( menuItemDepthBuffer, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( Container::OnMenu ) );
	
}

DepthBuffer::DepthBuffer( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer55;
	bSizer55 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer31;
	sbSizer31 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Depth Image") ), wxVERTICAL );
	
	m_bitmapDepthBuffer = new wxStaticBitmap( this, bitmapDepthBuffer, wxNullBitmap, wxDefaultPosition, wxSize( 512,512 ), 0 );
	sbSizer31->Add( m_bitmapDepthBuffer, 1, wxALL|wxEXPAND, 5 );
	
	bSizer55->Add( sbSizer31, 1, wxALL|wxEXPAND, 5 );
	
	this->SetSizer( bSizer55 );
	this->Layout();
	bSizer55->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_IDLE, wxIdleEventHandler( DepthBuffer::OnIdle ) );
	this->Connect( wxEVT_PAINT, wxPaintEventHandler( DepthBuffer::OnPaint ) );
	this->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( DepthBuffer::OnUpdate ) );
}

DepthBuffer::~DepthBuffer()
{
	// Disconnect Events
	this->Disconnect( wxEVT_IDLE, wxIdleEventHandler( DepthBuffer::OnIdle ) );
	this->Disconnect( wxEVT_PAINT, wxPaintEventHandler( DepthBuffer::OnPaint ) );
	this->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( DepthBuffer::OnUpdate ) );
	
}

Importer::Importer( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxFlexGridSizer* fgSizer4;
	fgSizer4 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer4->SetFlexibleDirection( wxBOTH );
	fgSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxStaticBoxSizer* sbSizer28;
	sbSizer28 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Source File") ), wxVERTICAL );
	
	m_staticTextSourceFile = new wxStaticText( this, staticTextSourceFile, wxT("#UNKNOWN"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextSourceFile->Wrap( -1 );
	sbSizer28->Add( m_staticTextSourceFile, 0, wxALL, 5 );
	
	fgSizer4->Add( sbSizer28, 1, wxEXPAND|wxALL, 5 );
	
	wxBoxSizer* bSizer23;
	bSizer23 = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticBoxSizer* sbSizer14;
	sbSizer14 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Data Type") ), wxVERTICAL );
	
	m_comboBoxDataType = new wxComboBox( this, comboBoxDataType, wxT("Unsigned Byte"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	m_comboBoxDataType->Append( wxT("Unsigned Byte") );
	m_comboBoxDataType->Append( wxT("Unsigned Short") );
	sbSizer14->Add( m_comboBoxDataType, 1, wxALL, 5 );
	
	bSizer23->Add( sbSizer14, 1, wxEXPAND|wxALL, 5 );
	
	wxStaticBoxSizer* sbSizer15;
	sbSizer15 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Byte Order") ), wxVERTICAL );
	
	m_comboBoxByteOrder = new wxComboBox( this, comboBoxByteOrder, wxT("Little Endian"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	m_comboBoxByteOrder->Append( wxT("Little Endian") );
	m_comboBoxByteOrder->Append( wxT("Big Endian") );
	m_comboBoxByteOrder->Enable( false );
	
	sbSizer15->Add( m_comboBoxByteOrder, 0, wxALL, 5 );
	
	bSizer23->Add( sbSizer15, 1, wxEXPAND|wxALL, 5 );
	
	wxStaticBoxSizer* sbSizer16;
	sbSizer16 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Header Skip") ), wxVERTICAL );
	
	m_spinCtrlHeaderSkip = new wxSpinCtrl( this, spinCtrlHeaderSkip, wxEmptyString, wxDefaultPosition, wxSize( 60,-1 ), wxSP_ARROW_KEYS, 0, 10000, 0 );
	sbSizer16->Add( m_spinCtrlHeaderSkip, 0, wxALL, 5 );
	
	bSizer23->Add( sbSizer16, 1, wxEXPAND|wxALL, 5 );
	
	fgSizer4->Add( bSizer23, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer17;
	sbSizer17 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Original Dimensions") ), wxHORIZONTAL );
	
	m_spinCtrlDimX = new wxSpinCtrl( this, spinCtrlDimX, wxEmptyString, wxDefaultPosition, wxSize( 90,-1 ), wxSP_ARROW_KEYS|wxSP_WRAP|wxTAB_TRAVERSAL, 0, 10000, 0 );
	sbSizer17->Add( m_spinCtrlDimX, 0, wxALL, 5 );
	
	m_staticText23 = new wxStaticText( this, wxID_ANY, wxT("x"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText23->Wrap( -1 );
	sbSizer17->Add( m_staticText23, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_spinCtrlDimY = new wxSpinCtrl( this, spinCtrlDimY, wxEmptyString, wxDefaultPosition, wxSize( 90,-1 ), wxSP_ARROW_KEYS, 0, 10000, 0 );
	sbSizer17->Add( m_spinCtrlDimY, 0, wxALL, 5 );
	
	m_staticText231 = new wxStaticText( this, wxID_ANY, wxT("y"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText231->Wrap( -1 );
	sbSizer17->Add( m_staticText231, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_spinCtrlDimZ = new wxSpinCtrl( this, spinCtrlDimZ, wxEmptyString, wxDefaultPosition, wxSize( 90,-1 ), wxSP_ARROW_KEYS, 0, 10000, 0 );
	sbSizer17->Add( m_spinCtrlDimZ, 0, wxALL, 5 );
	
	m_staticText232 = new wxStaticText( this, wxID_ANY, wxT("z"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText232->Wrap( -1 );
	sbSizer17->Add( m_staticText232, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	fgSizer4->Add( sbSizer17, 1, wxEXPAND|wxALL, 5 );
	
	wxStaticBoxSizer* sbSizer172;
	sbSizer172 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Spacing") ), wxHORIZONTAL );
	
  // =====================================================
	m_spinCtrlSpaceX = new wxSpinCtrlDouble( this, spinCtrlSpaceX, wxString("1.000"), wxDefaultPosition, wxSize( 90,-1 ), wxSP_ARROW_KEYS, 0.0, 10.0, 0.001 );
	sbSizer172->Add( m_spinCtrlSpaceX, 0, wxALL, 5 );
	
	m_staticText234 = new wxStaticText( this, wxID_ANY, wxT("x"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText234->Wrap( -1 );
	sbSizer172->Add( m_staticText234, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_spinCtrlSpaceY = new wxSpinCtrlDouble( this, spinCtrlSpaceY, wxString("1.000"), wxDefaultPosition, wxSize( 90,-1 ), wxSP_ARROW_KEYS, 0.0, 10.0, 0.001 );
	sbSizer172->Add( m_spinCtrlSpaceY, 0, wxALL, 5 );
	
	m_staticText2312 = new wxStaticText( this, wxID_ANY, wxT("y"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2312->Wrap( -1 );
	sbSizer172->Add( m_staticText2312, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_spinCtrlSpaceZ = new wxSpinCtrlDouble( this, spinCtrlSpaceZ, wxString("1.000"), wxDefaultPosition, wxSize( 90,-1 ), wxSP_ARROW_KEYS, 0.0, 10.0, 0.001 );
	sbSizer172->Add( m_spinCtrlSpaceZ, 0, wxALL, 5 );
	
  // =====================================================
	m_staticText2322 = new wxStaticText( this, wxID_ANY, wxT("z"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2322->Wrap( -1 );
	sbSizer172->Add( m_staticText2322, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	fgSizer4->Add( sbSizer172, 1, wxEXPAND|wxALL, 5 );
	
	m_staticline11 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	fgSizer4->Add( m_staticline11, 0, wxEXPAND|wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_checkBoxExtractSubVolume = new wxCheckBox( this, checkBoxExtractSubVolume, wxT("Extract Subvolume"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( m_checkBoxExtractSubVolume, 0, wxALL, 5 );
	
	wxStaticBoxSizer* sbSizer171;
	sbSizer171 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Subvolume Dimensions") ), wxHORIZONTAL );
	
	m_spinCtrlSubX = new wxSpinCtrl( this, spinCtrlSubX, wxEmptyString, wxDefaultPosition, wxSize( 90,-1 ), wxSP_ARROW_KEYS, 0, 10000, 0 );
	sbSizer171->Add( m_spinCtrlSubX, 0, wxALL, 5 );
	
	m_staticTextSubX = new wxStaticText( this, wxID_ANY, wxT("x"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextSubX->Wrap( -1 );
	sbSizer171->Add( m_staticTextSubX, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_spinCtrlSubY = new wxSpinCtrl( this, spinCtrlSubY, wxEmptyString, wxDefaultPosition, wxSize( 90,-1 ), wxSP_ARROW_KEYS, 0, 10000, 0 );
	sbSizer171->Add( m_spinCtrlSubY, 0, wxALL, 5 );
	
	m_staticTextSubY = new wxStaticText( this, wxID_ANY, wxT("y"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextSubY->Wrap( -1 );
	sbSizer171->Add( m_staticTextSubY, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_spinCtrlSubZ = new wxSpinCtrl( this, spinCtrlSubZ, wxEmptyString, wxDefaultPosition, wxSize( 90,-1 ), wxSP_ARROW_KEYS, 0, 10000, 0 );
	sbSizer171->Add( m_spinCtrlSubZ, 0, wxALL, 5 );
	
	m_staticTextSubZ = new wxStaticText( this, wxID_ANY, wxT("z"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextSubZ->Wrap( -1 );
	sbSizer171->Add( m_staticTextSubZ, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	fgSizer4->Add( sbSizer171, 1, wxEXPAND|wxALL, 5 );
	
	wxStaticBoxSizer* sbSizer1711;
	sbSizer1711 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Subvolume Offset") ), wxHORIZONTAL );
	
	m_spinCtrlOffX = new wxSpinCtrl( this, spinCtrlOffX, wxEmptyString, wxDefaultPosition, wxSize( 90,-1 ), wxSP_ARROW_KEYS, 0, 10000, 0 );
	sbSizer1711->Add( m_spinCtrlOffX, 0, wxALL, 5 );
	
	m_staticTextOffX = new wxStaticText( this, wxID_ANY, wxT("x"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextOffX->Wrap( -1 );
	sbSizer1711->Add( m_staticTextOffX, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_spinCtrlOffY = new wxSpinCtrl( this, spinCtrlOffY, wxEmptyString, wxDefaultPosition, wxSize( 90,-1 ), wxSP_ARROW_KEYS, 0, 10000, 0 );
	sbSizer1711->Add( m_spinCtrlOffY, 0, wxALL, 5 );
	
	m_staticTextOffY = new wxStaticText( this, wxID_ANY, wxT("y"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextOffY->Wrap( -1 );
	sbSizer1711->Add( m_staticTextOffY, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_spinCtrlOffZ = new wxSpinCtrl( this, spinCtrlOffZ, wxEmptyString, wxDefaultPosition, wxSize( 90,-1 ), wxSP_ARROW_KEYS, 0, 10000, 0 );
	sbSizer1711->Add( m_spinCtrlOffZ, 0, wxALL, 5 );
	
	m_staticTextOffZ = new wxStaticText( this, wxID_ANY, wxT("z"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextOffZ->Wrap( -1 );
	sbSizer1711->Add( m_staticTextOffZ, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	fgSizer4->Add( sbSizer1711, 1, wxEXPAND|wxALL, 5 );
	
	m_staticline111 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	fgSizer4->Add( m_staticline111, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer25;
	bSizer25 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer25->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonLoadRaw = new wxButton( this, buttonLoadRaw, wxT("Load Volume"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer25->Add( m_buttonLoadRaw, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonCancelRaw = new wxButton( this, buttonCancelRaw, wxT("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer25->Add( m_buttonCancelRaw, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	fgSizer4->Add( bSizer25, 1, wxEXPAND|wxALL, 5 );
	
	this->SetSizer( fgSizer4 );
	this->Layout();
	fgSizer4->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_comboBoxDataType->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( Importer::OnComboBox ), NULL, this );
	m_comboBoxByteOrder->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( Importer::OnComboBox ), NULL, this );
	m_spinCtrlHeaderSkip->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Importer::OnSpinCtrl ), NULL, this );
	m_spinCtrlDimX->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( Importer::OnSetFocus ), NULL, this );
	m_spinCtrlDimX->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Importer::OnSpinCtrl ), NULL, this );
	m_spinCtrlDimY->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( Importer::OnSetFocus ), NULL, this );
	m_spinCtrlDimY->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Importer::OnSpinCtrl ), NULL, this );
	m_spinCtrlDimZ->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( Importer::OnSetFocus ), NULL, this );
	m_spinCtrlDimZ->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Importer::OnSpinCtrl ), NULL, this );
	m_spinCtrlSpaceX->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( Importer::OnSetFocus ), NULL, this );
	m_spinCtrlSpaceX->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Importer::OnSpinCtrl ), NULL, this );
	m_spinCtrlSpaceY->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( Importer::OnSetFocus ), NULL, this );
	m_spinCtrlSpaceY->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Importer::OnSpinCtrl ), NULL, this );
	m_spinCtrlSpaceZ->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( Importer::OnSetFocus ), NULL, this );
	m_spinCtrlSpaceZ->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Importer::OnSpinCtrl ), NULL, this );
	m_checkBoxExtractSubVolume->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Importer::OnCheckBox ), NULL, this );
	m_spinCtrlSubX->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( Importer::OnSetFocus ), NULL, this );
	m_spinCtrlSubX->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Importer::OnSpinCtrl ), NULL, this );
	m_spinCtrlSubY->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( Importer::OnSetFocus ), NULL, this );
	m_spinCtrlSubY->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Importer::OnSpinCtrl ), NULL, this );
	m_spinCtrlSubZ->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( Importer::OnSetFocus ), NULL, this );
	m_spinCtrlSubZ->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Importer::OnSpinCtrl ), NULL, this );
	m_spinCtrlOffX->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( Importer::OnSetFocus ), NULL, this );
	m_spinCtrlOffX->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Importer::OnSpinCtrl ), NULL, this );
	m_spinCtrlOffY->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( Importer::OnSetFocus ), NULL, this );
	m_spinCtrlOffY->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Importer::OnSpinCtrl ), NULL, this );
	m_spinCtrlOffZ->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( Importer::OnSetFocus ), NULL, this );
	m_spinCtrlOffZ->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Importer::OnSpinCtrl ), NULL, this );
	m_buttonLoadRaw->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Importer::OnButton ), NULL, this );
	m_buttonCancelRaw->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Importer::OnButton ), NULL, this );
}

Importer::~Importer()
{
	// Disconnect Events
	m_comboBoxDataType->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( Importer::OnComboBox ), NULL, this );
	m_comboBoxByteOrder->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( Importer::OnComboBox ), NULL, this );
	m_spinCtrlHeaderSkip->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Importer::OnSpinCtrl ), NULL, this );
	m_spinCtrlDimX->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( Importer::OnSetFocus ), NULL, this );
	m_spinCtrlDimX->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Importer::OnSpinCtrl ), NULL, this );
	m_spinCtrlDimY->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( Importer::OnSetFocus ), NULL, this );
	m_spinCtrlDimY->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Importer::OnSpinCtrl ), NULL, this );
	m_spinCtrlDimZ->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( Importer::OnSetFocus ), NULL, this );
	m_spinCtrlDimZ->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Importer::OnSpinCtrl ), NULL, this );
	m_spinCtrlSpaceX->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( Importer::OnSetFocus ), NULL, this );
	m_spinCtrlSpaceX->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Importer::OnSpinCtrl ), NULL, this );
	m_spinCtrlSpaceY->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( Importer::OnSetFocus ), NULL, this );
	m_spinCtrlSpaceY->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Importer::OnSpinCtrl ), NULL, this );
	m_spinCtrlSpaceZ->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( Importer::OnSetFocus ), NULL, this );
	m_spinCtrlSpaceZ->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Importer::OnSpinCtrl ), NULL, this );
	m_checkBoxExtractSubVolume->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Importer::OnCheckBox ), NULL, this );
	m_spinCtrlSubX->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( Importer::OnSetFocus ), NULL, this );
	m_spinCtrlSubX->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Importer::OnSpinCtrl ), NULL, this );
	m_spinCtrlSubY->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( Importer::OnSetFocus ), NULL, this );
	m_spinCtrlSubY->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Importer::OnSpinCtrl ), NULL, this );
	m_spinCtrlSubZ->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( Importer::OnSetFocus ), NULL, this );
	m_spinCtrlSubZ->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Importer::OnSpinCtrl ), NULL, this );
	m_spinCtrlOffX->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( Importer::OnSetFocus ), NULL, this );
	m_spinCtrlOffX->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Importer::OnSpinCtrl ), NULL, this );
	m_spinCtrlOffY->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( Importer::OnSetFocus ), NULL, this );
	m_spinCtrlOffY->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Importer::OnSpinCtrl ), NULL, this );
	m_spinCtrlOffZ->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( Importer::OnSetFocus ), NULL, this );
	m_spinCtrlOffZ->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Importer::OnSpinCtrl ), NULL, this );
	m_buttonLoadRaw->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Importer::OnButton ), NULL, this );
	m_buttonCancelRaw->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Importer::OnButton ), NULL, this );
	
}

SegY::SegY( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxFlexGridSizer* fgSizer4;
	fgSizer4 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer4->SetFlexibleDirection( wxBOTH );
	fgSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxStaticBoxSizer* sbSizer28;
	sbSizer28 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Source File") ), wxVERTICAL );
	
	m_staticTextSourceFile = new wxStaticText( this, staticTextSourceFile, wxT("#UNKNOWN"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextSourceFile->Wrap( -1 );
	sbSizer28->Add( m_staticTextSourceFile, 0, wxALL, 5 );
	
	fgSizer4->Add( sbSizer28, 1, wxEXPAND|wxALL, 5 );
	
	wxStaticBoxSizer* sbSizer26;
	sbSizer26 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Volume Information") ), wxVERTICAL );
	
	wxBoxSizer* bSizer36;
	bSizer36 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText47 = new wxStaticText( this, wxID_ANY, wxT("Data Type"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText47->Wrap( -1 );
	bSizer36->Add( m_staticText47, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textDataType = new wxTextCtrl( this, textDataType, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer36->Add( m_textDataType, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer26->Add( bSizer36, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer361;
	bSizer361 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText471 = new wxStaticText( this, wxID_ANY, wxT("Sample Interval"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText471->Wrap( -1 );
	bSizer361->Add( m_staticText471, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textSampleInterval = new wxTextCtrl( this, textSampleInterval, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer361->Add( m_textSampleInterval, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer26->Add( bSizer361, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer362;
	bSizer362 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText472 = new wxStaticText( this, wxID_ANY, wxT("Bytes per Voxel"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText472->Wrap( -1 );
	bSizer362->Add( m_staticText472, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textBytesPerVoxel = new wxTextCtrl( this, textBytesPerVoxel, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer362->Add( m_textBytesPerVoxel, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer26->Add( bSizer362, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer363;
	bSizer363 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText473 = new wxStaticText( this, wxID_ANY, wxT("Trace Length"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText473->Wrap( -1 );
	bSizer363->Add( m_staticText473, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textTraceLength = new wxTextCtrl( this, textTraceLength, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer363->Add( m_textTraceLength, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer26->Add( bSizer363, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer364;
	bSizer364 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText474 = new wxStaticText( this, wxID_ANY, wxT("Size of File"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText474->Wrap( -1 );
	bSizer364->Add( m_staticText474, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textSizeOfFile = new wxTextCtrl( this, textSizeOfFile, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer364->Add( m_textSizeOfFile, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer26->Add( bSizer364, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer365;
	bSizer365 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText475 = new wxStaticText( this, wxID_ANY, wxT("Size of one Slice"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText475->Wrap( -1 );
	bSizer365->Add( m_staticText475, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textSizeOfSlice = new wxTextCtrl( this, textSizeOfSlice, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer365->Add( m_textSizeOfSlice, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer26->Add( bSizer365, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer366;
	bSizer366 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText476 = new wxStaticText( this, wxID_ANY, wxT("Samples per Trace"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText476->Wrap( -1 );
	bSizer366->Add( m_staticText476, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textSamplesPerTrace = new wxTextCtrl( this, textSamplesPerTrace, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer366->Add( m_textSamplesPerTrace, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer26->Add( bSizer366, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer367;
	bSizer367 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText477 = new wxStaticText( this, wxID_ANY, wxT("Number of Traces"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText477->Wrap( -1 );
	bSizer367->Add( m_staticText477, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textNumberTraces = new wxTextCtrl( this, textNumberTraces, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer367->Add( m_textNumberTraces, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer26->Add( bSizer367, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer368;
	bSizer368 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText478 = new wxStaticText( this, wxID_ANY, wxT("Number of Slices"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText478->Wrap( -1 );
	bSizer368->Add( m_staticText478, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textNumberSlices = new wxTextCtrl( this, textNumberSlices, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer368->Add( m_textNumberSlices, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer26->Add( bSizer368, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer369;
	bSizer369 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText479 = new wxStaticText( this, wxID_ANY, wxT("Dimensions"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText479->Wrap( -1 );
	bSizer369->Add( m_staticText479, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textDimensions = new wxTextCtrl( this, textDimensions, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer369->Add( m_textDimensions, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer26->Add( bSizer369, 1, wxEXPAND, 5 );
	
	fgSizer4->Add( sbSizer26, 1, wxEXPAND|wxALL, 5 );
	
	wxBoxSizer* bSizer25;
	bSizer25 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonLoadSegy = new wxButton( this, buttonLoadSegy, wxT("Load Volume"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer25->Add( m_buttonLoadSegy, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonCancelSegy = new wxButton( this, buttonCancelSegy, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer25->Add( m_buttonCancelSegy, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	fgSizer4->Add( bSizer25, 1, wxEXPAND|wxALL, 5 );
	
	this->SetSizer( fgSizer4 );
	this->Layout();
	fgSizer4->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_buttonLoadSegy->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SegY::OnButton ), NULL, this );
	m_buttonCancelSegy->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SegY::OnButton ), NULL, this );
}

SegY::~SegY()
{
	// Disconnect Events
	m_buttonLoadSegy->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SegY::OnButton ), NULL, this );
	m_buttonCancelSegy->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SegY::OnButton ), NULL, this );
	
}

OcclusionGeneration::OcclusionGeneration( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxFlexGridSizer* fgSizer5;
	fgSizer5 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer5->SetFlexibleDirection( wxBOTH );
	fgSizer5->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxStaticBoxSizer* m_sizerVisMapping;
	m_sizerVisMapping = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Visibility Mapping") ), wxVERTICAL );
	
	m_bmpVisMapping = new wxStaticBitmap( this, bmpVisMapping, wxBitmap( wxT("temp/hist.bmp"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxSize( 256,100 ), wxSIMPLE_BORDER );
	m_sizerVisMapping->Add( m_bmpVisMapping, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer( wxHORIZONTAL );
	
	m_txtPointCoordsX = new wxTextCtrl( this, txtPointCoordsX, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxTE_READONLY );
	m_txtPointCoordsX->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DLIGHT ) );
	
	bSizer18->Add( m_txtPointCoordsX, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText55 = new wxStaticText( this, wxID_ANY, wxT("x"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText55->Wrap( -1 );
	bSizer18->Add( m_staticText55, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_txtPointCoordsY = new wxTextCtrl( this, txtPointCoordsY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxTE_READONLY );
	m_txtPointCoordsY->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DLIGHT ) );
	
	bSizer18->Add( m_txtPointCoordsY, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText56 = new wxStaticText( this, wxID_ANY, wxT("y"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText56->Wrap( -1 );
	bSizer18->Add( m_staticText56, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonResetVisMapping = new wxButton( this, buttonResetVisMapping, wxT("Reset"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer18->Add( m_buttonResetVisMapping, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_sizerVisMapping->Add( bSizer18, 0, wxEXPAND, 5 );
	
	fgSizer5->Add( m_sizerVisMapping, 1, wxEXPAND|wxALL, 5 );
	
	wxBoxSizer* bSizer55;
	bSizer55 = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticBoxSizer* sbSizer27;
	sbSizer27 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Sampling Shape") ), wxVERTICAL );
	
	m_radioBtnSamplingCube = new wxRadioButton( this, radioBtnSamplingCube, wxT("Cube"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer27->Add( m_radioBtnSamplingCube, 0, wxALL, 5 );
	
	m_radioBtnSamplingSphere = new wxRadioButton( this, radioBtnSamplingSphere, wxT("Sphere"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer27->Add( m_radioBtnSamplingSphere, 0, wxALL, 5 );
	
	m_radioBtnSamplingEllipse = new wxRadioButton( this, radioBtnSamplingEllipse, wxT("Ellipse"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer27->Add( m_radioBtnSamplingEllipse, 0, wxALL, 5 );
	
	bSizer55->Add( sbSizer27, 1, wxEXPAND|wxALL, 5 );
	
	wxStaticBoxSizer* sbSizer35;
	sbSizer35 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Sampling Information") ), wxVERTICAL );
	
	wxBoxSizer* bSizer51;
	bSizer51 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer301;
	bSizer301 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer56;
	bSizer56 = new wxBoxSizer( wxHORIZONTAL );
	
	m_spinCtrlSamplingRadius1 = new wxSpinCtrl( this, spinCtrlSamplingRadius, wxEmptyString, wxDefaultPosition, wxSize( 70,-1 ), wxSP_ARROW_KEYS, 1, 60, 5 );
	bSizer56->Add( m_spinCtrlSamplingRadius1, 0, wxALL, 5 );
	
	m_staticText531 = new wxStaticText( this, wxID_ANY, wxT("Radius"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText531->Wrap( -1 );
	bSizer56->Add( m_staticText531, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer301->Add( bSizer56, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer57;
	bSizer57 = new wxBoxSizer( wxHORIZONTAL );
	
	m_spinCtrlOccScaling1 = new wxSpinCtrl( this, spinCtrlOccScaling, wxEmptyString, wxDefaultPosition, wxSize( 70,-1 ), wxSP_ARROW_KEYS, 1, 20, 1 );
	bSizer57->Add( m_spinCtrlOccScaling1, 0, wxALL, 5 );
	
	m_staticText541 = new wxStaticText( this, wxID_ANY, wxT("Scaling"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText541->Wrap( -1 );
	bSizer57->Add( m_staticText541, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer301->Add( bSizer57, 1, wxEXPAND, 5 );
	
	bSizer51->Add( bSizer301, 1, wxEXPAND, 5 );
	
	sbSizer35->Add( bSizer51, 1, wxEXPAND, 5 );
	
	bSizer55->Add( sbSizer35, 1, wxEXPAND|wxALL, 5 );
	
	fgSizer5->Add( bSizer55, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer31;
	bSizer31 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer31->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonLaunchOccGen = new wxButton( this, buttonLaunchOccGen, wxT("Launch"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer31->Add( m_buttonLaunchOccGen, 0, wxALL, 5 );
	
	m_buttonCancelOccGen = new wxButton( this, buttonCancelOccGen, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer31->Add( m_buttonCancelOccGen, 0, wxALL, 5 );
	
	fgSizer5->Add( bSizer31, 1, wxEXPAND|wxALL, 5 );
	
	this->SetSizer( fgSizer5 );
	this->Layout();
	fgSizer5->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_IDLE, wxIdleEventHandler( OcclusionGeneration::OnIdle ) );
	m_bmpVisMapping->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( OcclusionGeneration::OnLeftDown ), NULL, this );
	m_bmpVisMapping->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( OcclusionGeneration::OnLeftUp ), NULL, this );
	m_bmpVisMapping->Connect( wxEVT_MOTION, wxMouseEventHandler( OcclusionGeneration::OnMotion ), NULL, this );
	m_buttonResetVisMapping->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( OcclusionGeneration::OnButton ), NULL, this );
	m_radioBtnSamplingCube->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( OcclusionGeneration::OnRadio ), NULL, this );
	m_radioBtnSamplingSphere->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( OcclusionGeneration::OnRadio ), NULL, this );
	m_radioBtnSamplingEllipse->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( OcclusionGeneration::OnRadio ), NULL, this );
	m_spinCtrlSamplingRadius1->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( OcclusionGeneration::OnSpinCtrl ), NULL, this );
	m_spinCtrlOccScaling1->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( OcclusionGeneration::OnSpinCtrl ), NULL, this );
	m_buttonLaunchOccGen->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( OcclusionGeneration::OnButton ), NULL, this );
	m_buttonCancelOccGen->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( OcclusionGeneration::OnButton ), NULL, this );
}

OcclusionGeneration::~OcclusionGeneration()
{
	// Disconnect Events
	this->Disconnect( wxEVT_IDLE, wxIdleEventHandler( OcclusionGeneration::OnIdle ) );
	m_bmpVisMapping->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( OcclusionGeneration::OnLeftDown ), NULL, this );
	m_bmpVisMapping->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( OcclusionGeneration::OnLeftUp ), NULL, this );
	m_bmpVisMapping->Disconnect( wxEVT_MOTION, wxMouseEventHandler( OcclusionGeneration::OnMotion ), NULL, this );
	m_buttonResetVisMapping->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( OcclusionGeneration::OnButton ), NULL, this );
	m_radioBtnSamplingCube->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( OcclusionGeneration::OnRadio ), NULL, this );
	m_radioBtnSamplingSphere->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( OcclusionGeneration::OnRadio ), NULL, this );
	m_radioBtnSamplingEllipse->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( OcclusionGeneration::OnRadio ), NULL, this );
	m_spinCtrlSamplingRadius1->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( OcclusionGeneration::OnSpinCtrl ), NULL, this );
	m_spinCtrlOccScaling1->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( OcclusionGeneration::OnSpinCtrl ), NULL, this );
	m_buttonLaunchOccGen->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( OcclusionGeneration::OnButton ), NULL, this );
	m_buttonCancelOccGen->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( OcclusionGeneration::OnButton ), NULL, this );
	
}

Settings::Settings( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxFlexGridSizer* fgSizer6;
	fgSizer6 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer6->SetFlexibleDirection( wxBOTH );
	fgSizer6->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxStaticBoxSizer* sbSizer40;
	sbSizer40 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Input Cube") ), wxVERTICAL );
	
	wxBoxSizer* bSizer57;
	bSizer57 = new wxBoxSizer( wxHORIZONTAL );
	
	m_comboBoxInputCube = new wxComboBox( this, comboBoxInputCube, wxT("Seismic"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	m_comboBoxInputCube->Append( wxT("Seismic") );
	m_comboBoxInputCube->Append( wxT("Occlusion") );
	bSizer57->Add( m_comboBoxInputCube, 0, wxALL, 5 );
	
	m_staticText5 = new wxStaticText( this, wxID_ANY, wxT("BG Color"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	bSizer57->Add( m_staticText5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_comboBoxBGColor = new wxComboBox( this, comboBoxBGColor, wxT("Black"), wxDefaultPosition, wxSize( 50,-1 ), 0, NULL, 0 );
	m_comboBoxBGColor->Append( wxT("Black") );
	m_comboBoxBGColor->Append( wxT("Blue") );
	m_comboBoxBGColor->Append( wxT("Gray") );
	bSizer57->Add( m_comboBoxBGColor, 0, wxALL, 5 );
	
	sbSizer40->Add( bSizer57, 1, wxEXPAND, 5 );
	
	fgSizer6->Add( sbSizer40, 1, wxEXPAND|wxALL, 5 );
	
	wxStaticBoxSizer* sbSizer401;
	sbSizer401 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Rendering") ), wxHORIZONTAL );
	
	wxBoxSizer* bSizer58;
	bSizer58 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer56;
	bSizer56 = new wxBoxSizer( wxHORIZONTAL );
	
	m_checkBoxVolume = new wxCheckBox( this, checkBoxVolume, wxT("Volume"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer56->Add( m_checkBoxVolume, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_checkBoxColorTable = new wxCheckBox( this, checkBoxColorTable, wxT("Color Table"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer56->Add( m_checkBoxColorTable, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer58->Add( bSizer56, 0, wxALL|wxEXPAND, 5 );
	
	m_staticline17 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer58->Add( m_staticline17, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer50;
	bSizer50 = new wxBoxSizer( wxHORIZONTAL );
	
	m_checkBoxIsoSurface = new wxCheckBox( this, checkBoxIsoSurface, wxT("Surface"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer50->Add( m_checkBoxIsoSurface, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_spinCtrlIsoValue = new wxSpinCtrl( this, spinCtrlIsoValue, wxEmptyString, wxDefaultPosition, wxSize( 40,-1 ), wxSP_ARROW_KEYS, 0, 10, 0 );
	bSizer50->Add( m_spinCtrlIsoValue, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticline171 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	bSizer50->Add( m_staticline171, 0, wxEXPAND|wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_checkBoxPhong = new wxCheckBox( this, checkBoxPhong, wxT("Phong"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer50->Add( m_checkBoxPhong, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer58->Add( bSizer50, 1, wxALL|wxEXPAND, 5 );
	
	sbSizer401->Add( bSizer58, 1, wxEXPAND, 5 );
	
	fgSizer6->Add( sbSizer401, 1, wxEXPAND|wxALL, 5 );
	
	wxStaticBoxSizer* sizerSlices;
	sizerSlices = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Slices") ), wxVERTICAL );
	
	wxBoxSizer* m_sizerSldInline;
	m_sizerSldInline = new wxBoxSizer( wxHORIZONTAL );
	
	m_checkBoxInline = new wxCheckBox( this, checkBoxInline, wxT("Inline"), wxDefaultPosition, wxDefaultSize, 0 );
	m_sizerSldInline->Add( m_checkBoxInline, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_spinCtrlInline = new wxSpinCtrl( this, spinCtrlInline, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0 );
	m_sizerSldInline->Add( m_spinCtrlInline, 0, wxALL, 5 );
	
	sizerSlices->Add( m_sizerSldInline, 0, wxEXPAND, 5 );
	
	wxBoxSizer* m_sizerSldCrossline;
	m_sizerSldCrossline = new wxBoxSizer( wxHORIZONTAL );
	
	m_checkBoxCrossline = new wxCheckBox( this, checkBoxCrossline, wxT("Crossline"), wxDefaultPosition, wxDefaultSize, 0 );
	m_sizerSldCrossline->Add( m_checkBoxCrossline, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_spinCtrlCrossline = new wxSpinCtrl( this, spinCtrlCrossline, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0 );
	m_sizerSldCrossline->Add( m_spinCtrlCrossline, 0, wxALL, 5 );
	
	sizerSlices->Add( m_sizerSldCrossline, 0, wxEXPAND, 5 );
	
	wxBoxSizer* m_sizerSldTimeline;
	m_sizerSldTimeline = new wxBoxSizer( wxHORIZONTAL );
	
	m_checkBoxTimeline = new wxCheckBox( this, checkBoxTimeline, wxT("Timeline"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBoxTimeline->SetValue(true); 
	m_sizerSldTimeline->Add( m_checkBoxTimeline, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_spinCtrlTimeline = new wxSpinCtrl( this, spinCtrlTimeline, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0 );
	m_sizerSldTimeline->Add( m_spinCtrlTimeline, 0, wxALL, 5 );
	
	sizerSlices->Add( m_sizerSldTimeline, 0, wxEXPAND, 5 );
	
	fgSizer6->Add( sizerSlices, 1, wxEXPAND|wxALL, 5 );
	
	wxStaticBoxSizer* sbSizer39;
	sbSizer39 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Clipping") ), wxVERTICAL );
	
	wxBoxSizer* bSizer46;
	bSizer46 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText65 = new wxStaticText( this, wxID_ANY, wxT("x min"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText65->Wrap( -1 );
	bSizer46->Add( m_staticText65, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_spinCtrXMin = new wxSpinCtrl( this, spinCtrXMin, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxSP_ARROW_KEYS, 0, 100, 0 );
	bSizer46->Add( m_spinCtrXMin, 0, wxALL, 5 );
	
	m_staticText653 = new wxStaticText( this, wxID_ANY, wxT("x max"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText653->Wrap( -1 );
	bSizer46->Add( m_staticText653, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_spinCtrXMax = new wxSpinCtrl( this, spinCtrXMax, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxSP_ARROW_KEYS, 0, 100, 100 );
	bSizer46->Add( m_spinCtrXMax, 0, wxALL, 5 );
	
	sbSizer39->Add( bSizer46, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer461;
	bSizer461 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText651 = new wxStaticText( this, wxID_ANY, wxT("y min"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText651->Wrap( -1 );
	bSizer461->Add( m_staticText651, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_spinCtrYMin = new wxSpinCtrl( this, spinCtrYMin, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxSP_ARROW_KEYS, 0, 100, 0 );
	bSizer461->Add( m_spinCtrYMin, 0, wxALL, 5 );
	
	m_staticText6531 = new wxStaticText( this, wxID_ANY, wxT("y max"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6531->Wrap( -1 );
	bSizer461->Add( m_staticText6531, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_spinCtrYMax = new wxSpinCtrl( this, spinCtrYMax, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxSP_ARROW_KEYS, 0, 100, 100 );
	bSizer461->Add( m_spinCtrYMax, 0, wxALL, 5 );
	
	sbSizer39->Add( bSizer461, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer462;
	bSizer462 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText652 = new wxStaticText( this, wxID_ANY, wxT("z min"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText652->Wrap( -1 );
	bSizer462->Add( m_staticText652, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_spinCtrZMin = new wxSpinCtrl( this, spinCtrZMin, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxSP_ARROW_KEYS, 0, 100, 0 );
	bSizer462->Add( m_spinCtrZMin, 0, wxALL, 5 );
	
	m_staticText6532 = new wxStaticText( this, wxID_ANY, wxT("z max"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6532->Wrap( -1 );
	bSizer462->Add( m_staticText6532, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_spinCtrZMax = new wxSpinCtrl( this, spinCtrZMax, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxSP_ARROW_KEYS, 0, 100, 100 );
	bSizer462->Add( m_spinCtrZMax, 0, wxALL, 5 );
	
	sbSizer39->Add( bSizer462, 1, wxEXPAND, 5 );
	
	fgSizer6->Add( sbSizer39, 1, wxEXPAND|wxALL, 5 );
	
	this->SetSizer( fgSizer6 );
	this->Layout();
	fgSizer6->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( Settings::OnClose ) );
	this->Connect( wxEVT_IDLE, wxIdleEventHandler( Settings::OnIdle ) );
	this->Connect( wxEVT_PAINT, wxPaintEventHandler( Settings::OnPaint ) );
	this->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( Settings::OnUpdate ) );
	m_comboBoxInputCube->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( Settings::OnComboBox ), NULL, this );
	m_comboBoxBGColor->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( Settings::OnComboBox ), NULL, this );
	m_checkBoxVolume->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Settings::OnCheckBox ), NULL, this );
	m_checkBoxColorTable->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Settings::OnCheckBox ), NULL, this );
	m_checkBoxIsoSurface->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Settings::OnCheckBox ), NULL, this );
	m_spinCtrlIsoValue->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Settings::OnSpinCtrl ), NULL, this );
	m_checkBoxPhong->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Settings::OnCheckBox ), NULL, this );
	m_checkBoxInline->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Settings::OnCheckBox ), NULL, this );
	m_spinCtrlInline->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( Settings::OnSetFocus ), NULL, this );
	m_spinCtrlInline->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Settings::OnSpinCtrl ), NULL, this );
	m_checkBoxCrossline->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Settings::OnCheckBox ), NULL, this );
	m_spinCtrlCrossline->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( Settings::OnSetFocus ), NULL, this );
	m_spinCtrlCrossline->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Settings::OnSpinCtrl ), NULL, this );
	m_checkBoxTimeline->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Settings::OnCheckBox ), NULL, this );
	m_spinCtrlTimeline->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( Settings::OnSetFocus ), NULL, this );
	m_spinCtrlTimeline->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Settings::OnSpinCtrl ), NULL, this );
	m_spinCtrXMin->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( Settings::OnSetFocus ), NULL, this );
	m_spinCtrXMin->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Settings::OnSpinCtrl ), NULL, this );
	m_spinCtrXMax->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( Settings::OnSetFocus ), NULL, this );
	m_spinCtrXMax->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Settings::OnSpinCtrl ), NULL, this );
	m_spinCtrYMin->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( Settings::OnSetFocus ), NULL, this );
	m_spinCtrYMin->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Settings::OnSpinCtrl ), NULL, this );
	m_spinCtrYMax->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( Settings::OnSetFocus ), NULL, this );
	m_spinCtrYMax->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Settings::OnSpinCtrl ), NULL, this );
	m_spinCtrZMin->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( Settings::OnSetFocus ), NULL, this );
	m_spinCtrZMin->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Settings::OnSpinCtrl ), NULL, this );
	m_spinCtrZMax->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( Settings::OnSetFocus ), NULL, this );
	m_spinCtrZMax->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Settings::OnSpinCtrl ), NULL, this );
}

Settings::~Settings()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( Settings::OnClose ) );
	this->Disconnect( wxEVT_IDLE, wxIdleEventHandler( Settings::OnIdle ) );
	this->Disconnect( wxEVT_PAINT, wxPaintEventHandler( Settings::OnPaint ) );
	this->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( Settings::OnUpdate ) );
	m_comboBoxInputCube->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( Settings::OnComboBox ), NULL, this );
	m_comboBoxBGColor->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( Settings::OnComboBox ), NULL, this );
	m_checkBoxVolume->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Settings::OnCheckBox ), NULL, this );
	m_checkBoxColorTable->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Settings::OnCheckBox ), NULL, this );
	m_checkBoxIsoSurface->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Settings::OnCheckBox ), NULL, this );
	m_spinCtrlIsoValue->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Settings::OnSpinCtrl ), NULL, this );
	m_checkBoxPhong->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Settings::OnCheckBox ), NULL, this );
	m_checkBoxInline->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Settings::OnCheckBox ), NULL, this );
	m_spinCtrlInline->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( Settings::OnSetFocus ), NULL, this );
	m_spinCtrlInline->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Settings::OnSpinCtrl ), NULL, this );
	m_checkBoxCrossline->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Settings::OnCheckBox ), NULL, this );
	m_spinCtrlCrossline->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( Settings::OnSetFocus ), NULL, this );
	m_spinCtrlCrossline->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Settings::OnSpinCtrl ), NULL, this );
	m_checkBoxTimeline->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Settings::OnCheckBox ), NULL, this );
	m_spinCtrlTimeline->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( Settings::OnSetFocus ), NULL, this );
	m_spinCtrlTimeline->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Settings::OnSpinCtrl ), NULL, this );
	m_spinCtrXMin->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( Settings::OnSetFocus ), NULL, this );
	m_spinCtrXMin->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Settings::OnSpinCtrl ), NULL, this );
	m_spinCtrXMax->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( Settings::OnSetFocus ), NULL, this );
	m_spinCtrXMax->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Settings::OnSpinCtrl ), NULL, this );
	m_spinCtrYMin->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( Settings::OnSetFocus ), NULL, this );
	m_spinCtrYMin->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Settings::OnSpinCtrl ), NULL, this );
	m_spinCtrYMax->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( Settings::OnSetFocus ), NULL, this );
	m_spinCtrYMax->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Settings::OnSpinCtrl ), NULL, this );
	m_spinCtrZMin->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( Settings::OnSetFocus ), NULL, this );
	m_spinCtrZMin->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Settings::OnSpinCtrl ), NULL, this );
	m_spinCtrZMax->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( Settings::OnSetFocus ), NULL, this );
	m_spinCtrZMax->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Settings::OnSpinCtrl ), NULL, this );
	
}

ColorTable::ColorTable( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxFlexGridSizer* fgSizer9;
	fgSizer9 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer9->SetFlexibleDirection( wxBOTH );
	fgSizer9->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxStaticBoxSizer* sizerTransfer;
	sizerTransfer = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Transfer Function") ), wxVERTICAL );
	
	wxBoxSizer* m_sizerComboTransfer;
	m_sizerComboTransfer = new wxBoxSizer( wxHORIZONTAL );
	
	m_comboTransfer = new wxComboBox( this, comboTransfer, wxT("Magic"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	m_comboTransfer->Append( wxT("AI") );
	m_comboTransfer->Append( wxT("Altimetric") );
	m_comboTransfer->Append( wxT("Chimney") );
	m_comboTransfer->Append( wxT("Depth") );
	m_comboTransfer->Append( wxT("DHI") );
	m_comboTransfer->Append( wxT("Extremes") );
	m_comboTransfer->Append( wxT("Faults") );
	m_comboTransfer->Append( wxT("Faults 2") );
	m_comboTransfer->Append( wxT("Flames") );
	m_comboTransfer->Append( wxT("Forest") );
	m_comboTransfer->Append( wxT("Grey scales") );
	m_comboTransfer->Append( wxT("Ice") );
	m_comboTransfer->Append( wxT("Pastel") );
	m_comboTransfer->Append( wxT("Rainbow") );
	m_comboTransfer->Append( wxT("Red-White-Black") );
	m_comboTransfer->Append( wxT("Red-White-Blue") );
	m_comboTransfer->Append( wxT("Seismics") );
	m_comboTransfer->Append( wxT("Sky") );
	m_comboTransfer->Append( wxT("Experimental") );
	m_comboTransfer->Append( wxT("Magic") );
	m_comboTransfer->Append( wxT("Brown 4grades") );
	m_comboTransfer->Append( wxT("Curvature") );
	m_sizerComboTransfer->Add( m_comboTransfer, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonResetColorTable = new wxButton( this, buttonResetColorTable, wxT("Reset"), wxDefaultPosition, wxDefaultSize, 0 );
	m_sizerComboTransfer->Add( m_buttonResetColorTable, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sizerTransfer->Add( m_sizerComboTransfer, 1, wxEXPAND, 5 );
	
	m_staticline6 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	sizerTransfer->Add( m_staticline6, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer58;
	bSizer58 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText4 = new wxStaticText( this, wxID_ANY, wxT("Histogram"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	bSizer58->Add( m_staticText4, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticline17 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	bSizer58->Add( m_staticline17, 0, wxEXPAND|wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_spinCtrIntensityMult = new wxSpinCtrl( this, spinCtrIntensityMult, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxSP_ARROW_KEYS, 1, 50, 1 );
	bSizer58->Add( m_spinCtrIntensityMult, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText41 = new wxStaticText( this, wxID_ANY, wxT("Intensity Mult"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText41->Wrap( -1 );
	bSizer58->Add( m_staticText41, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sizerTransfer->Add( bSizer58, 1, wxEXPAND|wxALL, 5 );
	
	m_bmpPreviewOpacity = new wxStaticBitmap( this, bmpPreviewOpacity, wxBitmap( wxT("temp/hist.bmp"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxSize( 256,100 ), wxSIMPLE_BORDER );
	sizerTransfer->Add( m_bmpPreviewOpacity, 0, wxALL, 5 );
	
	m_bmpPreviewTransfer = new wxStaticBitmap( this, wxID_ANY, wxBitmap( wxT("data/images/AI_preview.bmp"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxSize( 256,-1 ), wxSIMPLE_BORDER );
	sizerTransfer->Add( m_bmpPreviewTransfer, 0, wxALL, 5 );
	
	fgSizer9->Add( sizerTransfer, 1, wxEXPAND|wxALL, 5 );
	
	this->SetSizer( fgSizer9 );
	this->Layout();
	fgSizer9->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_IDLE, wxIdleEventHandler( ColorTable::OnIdle ) );
	m_comboTransfer->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( ColorTable::OnComboBox ), NULL, this );
	m_buttonResetColorTable->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ColorTable::OnButton ), NULL, this );
	m_spinCtrIntensityMult->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( ColorTable::OnSpinCtrl ), NULL, this );
	m_bmpPreviewOpacity->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( ColorTable::OnLeftDown ), NULL, this );
	m_bmpPreviewOpacity->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( ColorTable::OnLeftUp ), NULL, this );
	m_bmpPreviewOpacity->Connect( wxEVT_MOTION, wxMouseEventHandler( ColorTable::OnMotion ), NULL, this );
	m_bmpPreviewOpacity->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( ColorTable::OnRightDown ), NULL, this );
	m_bmpPreviewOpacity->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( ColorTable::OnRightup ), NULL, this );
}

ColorTable::~ColorTable()
{
	// Disconnect Events
	this->Disconnect( wxEVT_IDLE, wxIdleEventHandler( ColorTable::OnIdle ) );
	m_comboTransfer->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( ColorTable::OnComboBox ), NULL, this );
	m_buttonResetColorTable->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ColorTable::OnButton ), NULL, this );
	m_spinCtrIntensityMult->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( ColorTable::OnSpinCtrl ), NULL, this );
	m_bmpPreviewOpacity->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( ColorTable::OnLeftDown ), NULL, this );
	m_bmpPreviewOpacity->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( ColorTable::OnLeftUp ), NULL, this );
	m_bmpPreviewOpacity->Disconnect( wxEVT_MOTION, wxMouseEventHandler( ColorTable::OnMotion ), NULL, this );
	m_bmpPreviewOpacity->Disconnect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( ColorTable::OnRightDown ), NULL, this );
	m_bmpPreviewOpacity->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( ColorTable::OnRightup ), NULL, this );
	
}

OcclusionSpectrum::OcclusionSpectrum( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxFlexGridSizer* sizerOccGen;
	sizerOccGen = new wxFlexGridSizer( 2, 1, 0, 0 );
	sizerOccGen->SetFlexibleDirection( wxBOTH );
	sizerOccGen->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxStaticBoxSizer* m_sizerSpectrum;
	m_sizerSpectrum = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Crossplot") ), wxVERTICAL );
	
	m_bmpOcclusionSpectrum = new wxStaticBitmap( this, bmpOcclusionSpectrum, wxNullBitmap, wxDefaultPosition, wxSize( 512,512 ), wxFULL_REPAINT_ON_RESIZE|wxSIMPLE_BORDER );
	m_bmpOcclusionSpectrum->Enable( false );
	
	m_sizerSpectrum->Add( m_bmpOcclusionSpectrum, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 10 );
	
	sizerOccGen->Add( m_sizerSpectrum, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer26;
	sbSizer26 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Settings") ), wxVERTICAL );
	
	wxBoxSizer* bSizer49;
	bSizer49 = new wxBoxSizer( wxHORIZONTAL );
	
	m_checkBoxPolygon1 = new wxCheckBox( this, checkBoxPolygon1, wxT("Polygon 1"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBoxPolygon1->SetValue(true); 
	bSizer49->Add( m_checkBoxPolygon1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_checkBoxPolygon2 = new wxCheckBox( this, checkBoxPolygon2, wxT("Polygon 2"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer49->Add( m_checkBoxPolygon2, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_checkBoxPolygon3 = new wxCheckBox( this, checkBoxPolygon3, wxT("Polygon 3"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer49->Add( m_checkBoxPolygon3, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticline15 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	bSizer49->Add( m_staticline15, 0, wxEXPAND|wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_checkBoxSinglePoint = new wxCheckBox( this, checkBoxSinglePoint, wxT("Single Point"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer49->Add( m_checkBoxSinglePoint, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticline19 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	bSizer49->Add( m_staticline19, 0, wxEXPAND | wxALL, 5 );
	
	
	bSizer49->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonResetPolygons = new wxButton( this, buttonResetPolygons, wxT("Reset Polygons"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer49->Add( m_buttonResetPolygons, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer26->Add( bSizer49, 1, wxEXPAND|wxALL, 5 );
	
	sizerOccGen->Add( sbSizer26, 1, wxEXPAND|wxALL, 5 );
	
	this->SetSizer( sizerOccGen );
	this->Layout();
	sizerOccGen->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
  this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( OcclusionSpectrum::OnClose ) );
	this->Connect( wxEVT_IDLE, wxIdleEventHandler( OcclusionSpectrum::OnIdle ) );
	this->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( OcclusionSpectrum::OnLeftDown ) );
	this->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( OcclusionSpectrum::OnLeftUp ) );
	this->Connect( wxEVT_MOTION, wxMouseEventHandler( OcclusionSpectrum::OnMotion ) );
	m_bmpOcclusionSpectrum->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( OcclusionSpectrum::OnLeftDown ), NULL, this );
	m_bmpOcclusionSpectrum->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( OcclusionSpectrum::OnLeftup ), NULL, this );
	m_bmpOcclusionSpectrum->Connect( wxEVT_MOTION, wxMouseEventHandler( OcclusionSpectrum::OnMotion ), NULL, this );
	m_checkBoxPolygon1->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( OcclusionSpectrum::OnCheckBox ), NULL, this );
	m_checkBoxPolygon2->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( OcclusionSpectrum::OnCheckBox ), NULL, this );
	m_checkBoxPolygon3->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( OcclusionSpectrum::OnCheckBox ), NULL, this );
	m_checkBoxSinglePoint->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( OcclusionSpectrum::OnCheckBox ), NULL, this );
	m_buttonResetPolygons->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( OcclusionSpectrum::OnButton ), NULL, this );
}

OcclusionSpectrum::~OcclusionSpectrum()
{
	// Disconnect Events
  this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( OcclusionSpectrum::OnClose ) );
	this->Disconnect( wxEVT_IDLE, wxIdleEventHandler( OcclusionSpectrum::OnIdle ) );
	this->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( OcclusionSpectrum::OnLeftDown ) );
	this->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( OcclusionSpectrum::OnLeftUp ) );
	this->Disconnect( wxEVT_MOTION, wxMouseEventHandler( OcclusionSpectrum::OnMotion ) );
	m_bmpOcclusionSpectrum->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( OcclusionSpectrum::OnLeftDown ), NULL, this );
	m_bmpOcclusionSpectrum->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( OcclusionSpectrum::OnLeftup ), NULL, this );
	m_bmpOcclusionSpectrum->Disconnect( wxEVT_MOTION, wxMouseEventHandler( OcclusionSpectrum::OnMotion ), NULL, this );
	m_checkBoxPolygon1->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( OcclusionSpectrum::OnCheckBox ), NULL, this );
	m_checkBoxPolygon2->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( OcclusionSpectrum::OnCheckBox ), NULL, this );
	m_checkBoxPolygon3->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( OcclusionSpectrum::OnCheckBox ), NULL, this );
	m_checkBoxSinglePoint->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( OcclusionSpectrum::OnCheckBox ), NULL, this );
	m_buttonResetPolygons->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( OcclusionSpectrum::OnButton ), NULL, this );
	
}
