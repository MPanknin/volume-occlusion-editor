///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 30 2011)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __UI_BASE_H__
#define __UI_BASE_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/clrpicker.h>
#include <wx/string.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/checkbox.h>
#include <wx/statbox.h>
#include <wx/combobox.h>
#include <wx/button.h>
#include <wx/spinctrl.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/statbmp.h>
#include <wx/scrolbar.h>
#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/filepicker.h>
#include <wx/textctrl.h>
#include <wx/menu.h>
#include <wx/splitter.h>
#include <wx/radiobut.h>

///////////////////////////////////////////////////////////////////////////

#define clrPickerClrColor 1000
#define chkVolume 1001
#define chkOcclusion 1002
#define chkTransfer 1003
#define chkPhong 1004
#define chkOccSpectrum 1005
#define btnResetOpacity 1006
#define spinIntensityMult 1007
#define bmpPreviewOpacity 1008
#define sldInline 1009
#define sldCrossline 1010
#define sldTimeline 1011
#define btnResetSlices 1012
#define spinXMax 1013
#define spinXMin 1014
#define spinYMax 1015
#define spinYMin 1016
#define spinZMax 1017
#define spinZMin 1018
#define bmpSpectrum 1019
#define pickerInputVolume 1020
#define comboVoxelSize 1021
#define comboEndian 1022
#define txtInputWidth 1023
#define txtInputHeight 1024
#define txtInputDepth 1025
#define txtInputHeader 1026
#define pickerOutputVolume 1027
#define txtOutputHeight 1028
#define txtOutputDepth 1029
#define txtXOff 1030
#define txtYOff 1031
#define txtZOff 1032
#define btnExtract 1033
#define bmpVisMapping 1034
#define txtPointCoords 1035
#define btnReset 1036
#define sizerOcclusion 1037
#define txtRadius 1038
#define txtScale 1039
#define btnLaunch 1040
#define menuItemOpen 1041
#define menuItemImportRaw 1042
#define menuItemExportRaw 1043
#define menuItemImportSegY 1044
#define menuItemExportSegY 1045
#define menuItemExit 1046
#define menuItemColorTable 1047
#define menuItemOcclusionGeneration 1048
#define menuItemOcclusionSpectrum 1049
#define menuItemDepthBuffer 1050
#define windowDepthBuffer 1051
#define bitmapDepthBuffer 1052
#define windowImporter 1053
#define staticTextSourceFile 1054
#define comboBoxDataType 1055
#define comboBoxByteOrder 1056
#define spinCtrlHeaderSkip 1057
#define spinCtrlDimX 1058
#define spinCtrlDimY 1059
#define spinCtrlDimZ 1060
#define spinCtrlSpaceX 1061
#define spinCtrlSpaceY 1062
#define spinCtrlSpaceZ 1063
#define checkBoxExtractSubVolume 1064
#define spinCtrlSubX 1065
#define spinCtrlSubY 1066
#define spinCtrlSubZ 1067
#define spinCtrlOffX 1068
#define spinCtrlOffY 1069
#define spinCtrlOffZ 1070
#define buttonLoadRaw 1071
#define buttonCancelRaw 1072
#define windowSegy 1073
#define textDataType 1074
#define textSampleInterval 1075
#define textBytesPerVoxel 1076
#define textTraceLength 1077
#define textSizeOfFile 1078
#define textSizeOfSlice 1079
#define textSamplesPerTrace 1080
#define textNumberTraces 1081
#define textNumberSlices 1082
#define textDimensions 1083
#define buttonLoadSegy 1084
#define buttonCancelSegy 1085
#define windowOcclusionGeneration 1086
#define txtPointCoordsX 1087
#define txtPointCoordsY 1088
#define buttonResetVisMapping 1089
#define radioBtnSamplingCube 1090
#define radioBtnSamplingSphere 1091
#define radioBtnSamplingEllipse 1092
#define spinCtrlSamplingRadius 1093
#define spinCtrlOccScaling 1094
#define buttonLaunchOccGen 1095
#define buttonCancelOccGen 1096
#define windowSettings 1097
#define comboBoxInputCube 1098
#define comboBoxBGColor 1099
#define checkBoxVolume 1100
#define checkBoxColorTable 1101
#define checkBoxIsoSurface 1102
#define spinCtrlIsoValue 1103
#define checkBoxPhong 1104
#define checkBoxInline 1105
#define spinCtrlInline 1106
#define checkBoxCrossline 1107
#define spinCtrlCrossline 1108
#define checkBoxTimeline 1109
#define spinCtrlTimeline 1110
#define spinCtrXMin 1111
#define spinCtrXMax 1112
#define spinCtrYMin 1113
#define spinCtrYMax 1114
#define spinCtrZMin 1115
#define spinCtrZMax 1116
#define windowColorTable 1117
#define comboTransfer 1118
#define buttonResetColorTable 1119
#define spinCtrIntensityMult 1120
#define windowOcclusionSpectrum 1121
#define bmpOcclusionSpectrum 1122
#define checkBoxPolygon1 1123
#define checkBoxPolygon2 1124
#define checkBoxPolygon3 1125
#define checkBoxSinglePoint 1126
#define buttonResetPolygons 1127

///////////////////////////////////////////////////////////////////////////////
/// Class Frame
///////////////////////////////////////////////////////////////////////////////
class Frame : public wxFrame 
{
	private:
	
	protected:
		wxColourPickerCtrl* m_clrPickerClearColor;
		wxStaticText* m_staticText5;
		wxStaticLine* m_staticline1;
		wxCheckBox* m_chkVolume;
		wxCheckBox* m_chkOcclusion;
		wxStaticLine* m_staticline4;
		wxCheckBox* m_chkTransfer;
		wxCheckBox* m_chkPhong;
		wxStaticLine* m_staticline3;
		wxCheckBox* m_chkToggleOccSpectrum;
		wxComboBox* m_comboTransfer;
		wxButton* m_btnResetOpacity;
		wxStaticLine* m_staticline12;
		wxSpinCtrl* m_spinIntensityMult;
		wxStaticText* m_staticText26;
		wxStaticBitmap* m_bmpPreviewTransfer;
		wxStaticLine* m_staticline6;
		wxStaticText* m_staticText4;
		wxStaticBitmap* m_bmpPreviewOpacity;
		wxCheckBox* m_chkInline;
		wxScrollBar* m_sldInline;
		wxCheckBox* m_chkCrossline;
		wxScrollBar* m_sldCrossline;
		wxCheckBox* m_chkTimeline;
		wxScrollBar* m_sldTimeline;
		wxButton* m_btnResetSlices;
		wxStaticLine* m_staticline11;
		wxStaticText* m_staticText18;
		wxStaticText* m_staticText192;
		wxSpinCtrl* m_spinXMax;
		wxSpinCtrl* m_spinXMin;
		wxStaticText* m_staticText191;
		wxSpinCtrl* m_spinYMax;
		wxSpinCtrl* m_spinYMin;
		wxStaticText* m_staticText19;
		wxSpinCtrl* m_spinZMax;
		wxSpinCtrl* m_spinZMin;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnIdle( wxIdleEvent& event ) { event.Skip(); }
		virtual void OnColourChanged( wxColourPickerEvent& event ) { event.Skip(); }
		virtual void OnCheckBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnComboBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSpinCtrl( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnSpinCtrl( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLeftDown( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnLeftUp( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnMotion( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnRightDown( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnRightUp( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnSlider( wxScrollEvent& event ) { event.Skip(); }
		
	
	public:
		
		Frame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Settings"), const wxPoint& pos = wxPoint( -1,-1 ), const wxSize& size = wxSize( -1,-1 ), long style = wxCAPTION|wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~Frame();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class FrameOccGen
///////////////////////////////////////////////////////////////////////////////
class FrameOccGen : public wxFrame 
{
	private:
	
	protected:
		wxStaticBitmap* m_bmpSpectrum;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnIdle( wxIdleEvent& event ) { event.Skip(); }
		virtual void OnLeftDown( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnLeftUp( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnMotion( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnPaint( wxPaintEvent& event ) { event.Skip(); }
		
	
	public:
		
		FrameOccGen( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Occlusion Spectrum"), const wxPoint& pos = wxPoint( -1,-1 ), const wxSize& size = wxSize( -1,-1 ), long style = wxCAPTION|wxSTAY_ON_TOP|wxTAB_TRAVERSAL );
		
		~FrameOccGen();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class ControlPoint
///////////////////////////////////////////////////////////////////////////////
class ControlPoint : public wxPanel 
{
	private:
	
	protected:
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnLeftDown( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnLeftUp( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnMotion( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnRightUp( wxMouseEvent& event ) { event.Skip(); }
		
	
	public:
		
		ControlPoint( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 10,10 ), long style = wxSIMPLE_BORDER|wxTAB_TRAVERSAL|wxTRANSPARENT_WINDOW ); 
		~ControlPoint();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class PolyPoint
///////////////////////////////////////////////////////////////////////////////
class PolyPoint : public wxPanel 
{
	private:
	
	protected:
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnLeftDown( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnLeftUp( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnMotion( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnRightUp( wxMouseEvent& event ) { event.Skip(); }
		
	
	public:
		
		PolyPoint( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 10,10 ), long style = wxSIMPLE_BORDER|wxTAB_TRAVERSAL|wxTRANSPARENT_WINDOW ); 
		~PolyPoint();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class PolyPoint_back
///////////////////////////////////////////////////////////////////////////////
class PolyPoint_back : public wxPanel 
{
	private:
	
	protected:
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnLeftDown( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnLeftUp( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnMotion( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnRightUp( wxMouseEvent& event ) { event.Skip(); }
		
	
	public:
		
		PolyPoint_back( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 10,10 ), long style = wxSIMPLE_BORDER|wxTAB_TRAVERSAL ); 
		~PolyPoint_back();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class Extractor
///////////////////////////////////////////////////////////////////////////////
class Extractor : public wxFrame 
{
	private:
	
	protected:
		wxFilePickerCtrl* m_pickerInputVolume;
		wxComboBox* m_comboVoxelSize;
		wxComboBox* m_comboEndian;
		wxStaticLine* m_staticline13;
		wxStaticText* m_staticText25;
		wxTextCtrl* m_txtInputWidth;
		wxStaticText* m_staticText14;
		wxTextCtrl* m_txtInputHeight;
		wxStaticText* m_staticText141;
		wxTextCtrl* m_txtInputDepth;
		wxStaticText* m_staticText142;
		wxTextCtrl* m_txtInputHeader;
		wxStaticText* m_staticText1423;
		wxFilePickerCtrl* m_pickerOutputVolume;
		wxStaticLine* m_staticline14;
		wxStaticText* m_staticText26;
		wxTextCtrl* m_txtOutputWidth;
		wxStaticText* m_staticText143;
		wxTextCtrl* m_txtOutputHeight;
		wxStaticText* m_staticText1411;
		wxTextCtrl* m_txtOutputDepth;
		wxStaticText* m_staticText1421;
		wxStaticLine* m_staticline10;
		wxStaticText* m_staticText27;
		wxTextCtrl* m_txtXOff;
		wxStaticText* m_staticText144;
		wxTextCtrl* m_txtYOff;
		wxStaticText* m_staticText1412;
		wxTextCtrl* m_txtZOff;
		wxStaticText* m_staticText1422;
		wxStaticLine* m_staticline16;
		wxButton* m_btnExtract;
		wxStaticBitmap* m_bmpVisMapping;
		wxTextCtrl* m_txtPointCoords;
		wxButton* m_btnReset;
		wxTextCtrl* m_txtRadius;
		wxStaticText* m_staticText1431;
		wxTextCtrl* m_txtScale;
		wxStaticText* m_staticText14111;
		wxButton* m_btnLaunch;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnIdle( wxIdleEvent& event ) { event.Skip(); }
		virtual void OnPaint( wxPaintEvent& event ) { event.Skip(); }
		virtual void OnFileChanged( wxFileDirPickerEvent& event ) { event.Skip(); }
		virtual void OnComboBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLeftDown( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnLeftUp( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnMotion( wxMouseEvent& event ) { event.Skip(); }
		
	public:
		
		Extractor( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Occlusion Generation"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~Extractor();
};

///////////////////////////////////////////////////////////////////////////////
/// Class Plotter
///////////////////////////////////////////////////////////////////////////////
class Plotter : public wxFrame 
{
	private:
	
	protected:
		wxStaticBitmap* m_bitmap4;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnLeftDOwn( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnLeftUp( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnMotion( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnRightDown( wxMouseEvent& event ) { event.Skip(); }
		
	
	public:
		
		Plotter( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Occlusion Spectrum"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 556,582 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~Plotter();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class Container
///////////////////////////////////////////////////////////////////////////////
class Container : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* m_menubar1;
		wxMenu* m_menuFile;
		wxMenu* m_menuView;
		wxSplitterWindow* m_splitterMain;
		wxPanel* m_panel3;
		wxPanel* m_panel4;
		wxTextCtrl* m_textLogOut;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnIdle( wxIdleEvent& event ) { event.Skip(); }
		virtual void OnMenu( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		Container( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Occlusion Editor"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1024,768 ), long style = wxDEFAULT_FRAME_STYLE|wxMAXIMIZE|wxMAXIMIZE_BOX|wxTAB_TRAVERSAL );
		
		~Container();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class DepthBuffer
///////////////////////////////////////////////////////////////////////////////
class DepthBuffer : public wxFrame 
{
	private:
	
	protected:
		wxStaticBitmap* m_bitmapDepthBuffer;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnIdle( wxIdleEvent& event ) { event.Skip(); }
		virtual void OnPaint( wxPaintEvent& event ) { event.Skip(); }
		virtual void OnUpdate( wxUpdateUIEvent& event ) { event.Skip(); }
		
	
	public:
		
		DepthBuffer( wxWindow* parent, wxWindowID id = windowDepthBuffer, const wxString& title = wxT("Depth Buffer"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_FRAME_STYLE|wxFRAME_FLOAT_ON_PARENT|wxFRAME_NO_TASKBAR|wxTAB_TRAVERSAL );
		
		~DepthBuffer();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class Importer
///////////////////////////////////////////////////////////////////////////////
class Importer : public wxFrame 
{
	private:
	
	protected:
		wxStaticText* m_staticTextSourceFile;
		wxComboBox* m_comboBoxDataType;
		wxComboBox* m_comboBoxByteOrder;
		wxSpinCtrl* m_spinCtrlHeaderSkip;
		wxSpinCtrl* m_spinCtrlDimX;
		wxStaticText* m_staticText23;
		wxSpinCtrl* m_spinCtrlDimY;
		wxStaticText* m_staticText231;
		wxSpinCtrl* m_spinCtrlDimZ;
		wxStaticText* m_staticText232;
		wxSpinCtrlDouble* m_spinCtrlSpaceX;
		wxStaticText* m_staticText234;
		wxSpinCtrlDouble* m_spinCtrlSpaceY;
		wxStaticText* m_staticText2312;
		wxSpinCtrlDouble* m_spinCtrlSpaceZ;
		wxStaticText* m_staticText2322;
		wxStaticLine* m_staticline11;
		wxCheckBox* m_checkBoxExtractSubVolume;
		wxSpinCtrl* m_spinCtrlSubX;
		wxStaticText* m_staticTextSubX;
		wxSpinCtrl* m_spinCtrlSubY;
		wxStaticText* m_staticTextSubY;
		wxSpinCtrl* m_spinCtrlSubZ;
		wxStaticText* m_staticTextSubZ;
		wxSpinCtrl* m_spinCtrlOffX;
		wxStaticText* m_staticTextOffX;
		wxSpinCtrl* m_spinCtrlOffY;
		wxStaticText* m_staticTextOffY;
		wxSpinCtrl* m_spinCtrlOffZ;
		wxStaticText* m_staticTextOffZ;
		wxStaticLine* m_staticline111;
		wxButton* m_buttonLoadRaw;
		wxButton* m_buttonCancelRaw;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnComboBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSpinCtrl( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnSetFocus( wxFocusEvent& event ) { event.Skip(); }
		virtual void OnCheckBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButton( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		Importer( wxWindow* parent, wxWindowID id = windowImporter, const wxString& title = wxT("Raw Volume Information"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_FRAME_STYLE|wxFRAME_FLOAT_ON_PARENT|wxFRAME_NO_TASKBAR|wxTAB_TRAVERSAL );
		
		~Importer();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class SegY
///////////////////////////////////////////////////////////////////////////////
class SegY : public wxFrame 
{
	private:
	
	protected:
		wxStaticText* m_staticTextSourceFile;
		wxStaticText* m_staticText47;
		wxTextCtrl* m_textDataType;
		wxStaticText* m_staticText471;
		wxTextCtrl* m_textSampleInterval;
		wxStaticText* m_staticText472;
		wxTextCtrl* m_textBytesPerVoxel;
		wxStaticText* m_staticText473;
		wxTextCtrl* m_textTraceLength;
		wxStaticText* m_staticText474;
		wxTextCtrl* m_textSizeOfFile;
		wxStaticText* m_staticText475;
		wxTextCtrl* m_textSizeOfSlice;
		wxStaticText* m_staticText476;
		wxTextCtrl* m_textSamplesPerTrace;
		wxStaticText* m_staticText477;
		wxTextCtrl* m_textNumberTraces;
		wxStaticText* m_staticText478;
		wxTextCtrl* m_textNumberSlices;
		wxStaticText* m_staticText479;
		wxTextCtrl* m_textDimensions;
		wxButton* m_buttonLoadSegy;
		wxButton* m_buttonCancelSegy;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnButton( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		SegY( wxWindow* parent, wxWindowID id = windowSegy, const wxString& title = wxT("SegY Info"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_FRAME_STYLE|wxFRAME_FLOAT_ON_PARENT|wxFRAME_NO_TASKBAR|wxTAB_TRAVERSAL );
		
		~SegY();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class OcclusionGeneration
///////////////////////////////////////////////////////////////////////////////
class OcclusionGeneration : public wxFrame 
{
	private:
	
	protected:
		wxStaticBitmap* m_bmpVisMapping;
		wxTextCtrl* m_txtPointCoordsX;
		wxStaticText* m_staticText55;
		wxTextCtrl* m_txtPointCoordsY;
		wxStaticText* m_staticText56;
		wxButton* m_buttonResetVisMapping;
		wxRadioButton* m_radioBtnSamplingCube;
		wxRadioButton* m_radioBtnSamplingSphere;
		wxRadioButton* m_radioBtnSamplingEllipse;
		wxSpinCtrl* m_spinCtrlSamplingRadius1;
		wxStaticText* m_staticText531;
		wxSpinCtrl* m_spinCtrlOccScaling1;
		wxStaticText* m_staticText541;
		wxButton* m_buttonLaunchOccGen;
		wxButton* m_buttonCancelOccGen;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnIdle( wxIdleEvent& event ) { event.Skip(); }
		virtual void OnLeftDown( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnLeftUp( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnMotion( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRadio( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSpinCtrl( wxSpinEvent& event ) { event.Skip(); }
		
	
	public:
		
		OcclusionGeneration( wxWindow* parent, wxWindowID id = windowOcclusionGeneration, const wxString& title = wxT("OcclusionGeneration"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_FRAME_STYLE|wxFRAME_FLOAT_ON_PARENT|wxFRAME_NO_TASKBAR|wxTAB_TRAVERSAL );
		
		~OcclusionGeneration();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class Settings
///////////////////////////////////////////////////////////////////////////////
class Settings : public wxFrame 
{
	private:
	
	protected:
		wxComboBox* m_comboBoxInputCube;
		wxStaticText* m_staticText5;
		wxComboBox* m_comboBoxBGColor;
		wxCheckBox* m_checkBoxVolume;
		wxCheckBox* m_checkBoxColorTable;
		wxStaticLine* m_staticline17;
		wxCheckBox* m_checkBoxIsoSurface;
		wxSpinCtrl* m_spinCtrlIsoValue;
		wxStaticLine* m_staticline171;
		wxCheckBox* m_checkBoxPhong;
		wxCheckBox* m_checkBoxInline;
		wxSpinCtrl* m_spinCtrlInline;
		wxCheckBox* m_checkBoxCrossline;
		wxSpinCtrl* m_spinCtrlCrossline;
		wxCheckBox* m_checkBoxTimeline;
		wxSpinCtrl* m_spinCtrlTimeline;
		wxStaticText* m_staticText65;
		wxSpinCtrl* m_spinCtrXMin;
		wxStaticText* m_staticText653;
		wxSpinCtrl* m_spinCtrXMax;
		wxStaticText* m_staticText651;
		wxSpinCtrl* m_spinCtrYMin;
		wxStaticText* m_staticText6531;
		wxSpinCtrl* m_spinCtrYMax;
		wxStaticText* m_staticText652;
		wxSpinCtrl* m_spinCtrZMin;
		wxStaticText* m_staticText6532;
		wxSpinCtrl* m_spinCtrZMax;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnIdle( wxIdleEvent& event ) { event.Skip(); }
		virtual void OnPaint( wxPaintEvent& event ) { event.Skip(); }
		virtual void OnUpdate( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnComboBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCheckBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSpinCtrl( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnSetFocus( wxFocusEvent& event ) { event.Skip(); }
		
	
	public:
		
		Settings( wxWindow* parent, wxWindowID id = windowSettings, const wxString& title = wxT("Settings"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxCAPTION|wxFRAME_FLOAT_ON_PARENT|wxFRAME_NO_TASKBAR|wxCLIP_CHILDREN|wxTAB_TRAVERSAL );
		
		~Settings();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class ColorTable
///////////////////////////////////////////////////////////////////////////////
class ColorTable : public wxFrame 
{
	private:
	
	protected:
		wxComboBox* m_comboTransfer;
		wxButton* m_buttonResetColorTable;
		wxStaticLine* m_staticline6;
		wxStaticText* m_staticText4;
		wxStaticLine* m_staticline17;
		wxSpinCtrl* m_spinCtrIntensityMult;
		wxStaticText* m_staticText41;
		wxStaticBitmap* m_bmpPreviewOpacity;
		wxStaticBitmap* m_bmpPreviewTransfer;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnIdle( wxIdleEvent& event ) { event.Skip(); }
		virtual void OnComboBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSpinCtrl( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnLeftDown( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnLeftUp( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnMotion( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnRightDown( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnRightup( wxMouseEvent& event ) { event.Skip(); }
		
	
	public:
		
		ColorTable( wxWindow* parent, wxWindowID id = windowColorTable, const wxString& title = wxT("Color Table Editor"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_FRAME_STYLE|wxFRAME_FLOAT_ON_PARENT|wxFRAME_NO_TASKBAR|wxTAB_TRAVERSAL );
		
		~ColorTable();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class OcclusionSpectrum
///////////////////////////////////////////////////////////////////////////////
class OcclusionSpectrum : public wxFrame 
{
	private:
	
	protected:
		wxStaticBitmap* m_bmpOcclusionSpectrum;
		wxCheckBox* m_checkBoxPolygon1;
		wxCheckBox* m_checkBoxPolygon2;
		wxCheckBox* m_checkBoxPolygon3;
		wxStaticLine* m_staticline15;
		wxCheckBox* m_checkBoxSinglePoint;
		wxStaticLine* m_staticline19;
		wxButton* m_buttonResetPolygons;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnIdle( wxIdleEvent& event ) { event.Skip(); }
		virtual void OnLeftDown( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnLeftUp( wxMouseEvent& event ) { event.Skip(); }
    virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnMotion( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnLeftup( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnCheckBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButton( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		OcclusionSpectrum( wxWindow* parent, wxWindowID id = windowOcclusionSpectrum, const wxString& title = wxT("OcclusionSpectrum"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_FRAME_STYLE|wxFRAME_FLOAT_ON_PARENT|wxFRAME_NO_TASKBAR|wxMINIMIZE_BOX|wxTAB_TRAVERSAL );
		
		~OcclusionSpectrum();
	
};

#endif //__UI_BASE_H__
