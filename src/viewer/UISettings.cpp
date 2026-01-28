#pragma warning( disable : 4100 )

#include <osg/ref_ptr>

#include "UISettings.h"
#include "UIContainer.h"

#include "VolumeViewer.h"
#include "VolumeInfo.h"
#include "Logger.h"

//============================================================================
UISettings::UISettings( wxWindow* parent )
:
Settings( parent )
{
  FS();

  m_topView = 0;
  Init();
  
  FE();
}
//============================================================================
void UISettings::Init()
{
  FS();

  UIContainer* container = dynamic_cast<UIContainer*>(GetParent());
  if (container != 0)
  {
    m_topView = container->m_topView;
  }

  this->Enable(m_topView != 0);
  
  if(m_topView)
  {
    m_topView->ToggleLine(VoxelSlice::INLINE, false);
    m_topView->ToggleLine(VoxelSlice::CROSSLINE, false);
    m_topView->ToggleLine(VoxelSlice::TIMESLICE, false);

    m_checkBoxVolume->SetValue(false);
    m_checkBoxColorTable->SetValue(true);

    m_checkBoxCrossline->SetValue(false);
    m_checkBoxInline->SetValue(false);
    m_checkBoxTimeline->SetValue(false);

    m_spinCtrlInline->Enable(false);
    m_spinCtrlCrossline->Enable(false);
    m_spinCtrlTimeline->Enable(false);

    int xMax = m_topView->GetXs();
    int yMax = m_topView->GetYs();
    int zMax = m_topView->GetZs();

    m_topView->GetVolInfo()->Print();

    int inlineOffset =    m_topView->GetVolInfo()->inlineOffset;
    int crosslineOffset = m_topView->GetVolInfo()->crosslineOffset;
    int timeOffset =      m_topView->GetVolInfo()->timeOffset;

    int xHalf = xMax / 2 + crosslineOffset;
    int yHalf = yMax / 2 + inlineOffset;
    int zHalf = zMax / 2 + timeOffset;

    yMax += inlineOffset;
    xMax += crosslineOffset;
    zMax += timeOffset;

    m_spinCtrlInline->SetMax(yMax);
    m_spinCtrlInline->SetMin(inlineOffset);
    m_spinCtrlInline->SetValue(yHalf);

    m_spinCtrlCrossline->SetMax(xMax);
    m_spinCtrlCrossline->SetMin(crosslineOffset);
    m_spinCtrlCrossline->SetValue(xHalf);

    m_spinCtrlTimeline->SetMax(zMax);
    m_spinCtrlTimeline->SetMin(timeOffset);
    m_spinCtrlTimeline->SetValue(zHalf);

    char buff[256];
    sprintf(buff, "Inline: %i\n", yHalf);
    m_topView->MoveLine(VoxelSlice::INLINE, 0.5f, buff);

    sprintf(buff, "Crossline: %i\n", xHalf);
    m_topView->MoveLine(VoxelSlice::CROSSLINE, 0.5f, buff);
    
    sprintf(buff, "Timeslice: %i\n", zHalf);
    m_topView->MoveLine(VoxelSlice::TIMESLICE, 0.5f, buff);

    m_topView->ToggleTransferFunction(true);
  }
  
  SetPosition(wxPoint(820, 50));

  FE();
}
//============================================================================
void UISettings::OnPaint( wxPaintEvent& event )
{
}
//============================================================================
void UISettings::OnIdle( wxIdleEvent& event )
{
}
//============================================================================
void UISettings::OnUpdate( wxUpdateUIEvent& event )
{
}
//============================================================================
void UISettings::OnClose( wxCloseEvent& event )
{
  m_topView = 0;
  this->Destroy();
}
//============================================================================
void UISettings::OnComboBox( wxCommandEvent& event )
{
  switch(event.GetId())
  {
  case comboBoxInputCube:
    {
      wxString cube = m_comboBoxInputCube->GetValue();
      if(cube.IsSameAs("Seismic"))
        m_topView->ToggleOcclusion(false);
      else if(cube.IsSameAs("Occlusion"))
        m_topView->ToggleOcclusion(true);
      
      break;
    }
  case comboBoxBGColor:
    {
      wxString colorString = m_comboBoxBGColor->GetValue();
      osg::Vec4 color;
      if(colorString.IsSameAs("Black"))
        color = Vec4(0, 0, 0, 1);
      else if(colorString.IsSameAs("Gray"))
        color = Vec4(0.7, 0.7, 0.7, 1);
      else if(colorString.IsSameAs("Blue"))
        color = Vec4(0.0, 0.0, 0.7, 1);
      
      m_topView->SetClearColor(color);
      break;
    }
    break;
  default:
    break;
  }
}
//============================================================================
void UISettings::OnCheckBox( wxCommandEvent& event )
{
  switch(event.GetId())
  {
  case checkBoxVolume:
    {
      m_topView->ToggleRenderer(event.IsChecked());
      break;
    }
  case checkBoxColorTable:
    {
      m_topView->ToggleTransferFunction(event.IsChecked());
      break;
    }
  case checkBoxPhong:
    {
      m_topView->TogglePhong(event.IsChecked());
      break;
    }
  case checkBoxInline:
    m_spinCtrlInline->Enable(event.IsChecked());
    m_topView->ToggleLine(VoxelSlice::INLINE, event.IsChecked());
    break;
  case checkBoxCrossline:
    m_spinCtrlCrossline->Enable(event.IsChecked());
    m_topView->ToggleLine(VoxelSlice::CROSSLINE, event.IsChecked());
    break;
  case checkBoxTimeline:
    m_spinCtrlTimeline->Enable(event.IsChecked());
    m_topView->ToggleLine(VoxelSlice::TIMESLICE, event.IsChecked());
    break;
  case checkBoxIsoSurface:
    {
      m_spinCtrlIsoValue->Enable(event.IsChecked());
      m_topView->ToggleIso(event.IsChecked());
    }
    break;

  default:
    break;
  }
}
//============================================================================
void UISettings::OnSpinCtrl( wxSpinEvent& event )
{
  char buff[256];
  int num = event.GetValue();
  int inOff = m_topView->GetVolInfo()->inlineOffset;
  int crossOff = m_topView->GetVolInfo()->crosslineOffset;
  int timeOff = m_topView->GetVolInfo()->timeOffset;

  switch(event.GetId())
  {
  case spinCtrlInline:
    {
      sprintf(buff, "Inline: %i\n", num);
      float pos = (num - inOff) / m_topView->GetYs();
      m_topView->MoveLine(VoxelSlice::INLINE, pos, buff);
      break;
    }
  case spinCtrlCrossline:
    {
      sprintf(buff, "Crossline: %i\n", num);
      float pos = (num - crossOff) / m_topView->GetXs();
      m_topView->MoveLine(VoxelSlice::CROSSLINE, pos, buff);
      break;
    }
  case spinCtrlTimeline:
    {
      sprintf(buff, "Timeslice: %i\n", num);
      float pos = 1.0f - ((num - timeOff) / m_topView->GetZs());
      m_topView->MoveLine(VoxelSlice::TIMESLICE, pos, buff);
      break;
    }
    // ---
  case spinCtrXMin:
    m_topView->SetClipping(RayCastTechnique::XMIN, event.GetValue());
    break;
  case spinCtrYMin:
    m_topView->SetClipping(RayCastTechnique::YMIN, event.GetValue());
    break;
  case spinCtrZMin:
    m_topView->SetClipping(RayCastTechnique::ZMIN, event.GetValue());
    break;
    // ---
  case spinCtrXMax:
    m_topView->SetClipping(RayCastTechnique::XMAX, event.GetValue());
    break;
  case spinCtrYMax:
    m_topView->SetClipping(RayCastTechnique::YMAX, event.GetValue());
    break;
  case spinCtrZMax:
    m_topView->SetClipping(RayCastTechnique::ZMAX, event.GetValue());
    break;

  case spinCtrlIsoValue:
    m_topView->SetIsoValue(event.GetValue() / 10.0f);
    break;

    // ---
  default:
    break;
  }
}
//============================================================================
void UISettings::OnSetFocus( wxFocusEvent& event )
{
  wxSpinCtrl* spin = dynamic_cast<wxSpinCtrl*>(FindWindowById(event.GetId()));
  if (spin != 0)
  {
    spin->SetSelection(-1, -1);
  }
}
//============================================================================
//============================================================================
//============================================================================
//============================================================================
//============================================================================




