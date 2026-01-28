#pragma warning( disable : 4100 )

#include <sstream>

#include <osg\ref_ptr>
#include <osgDB\ReadFile>
#include <osgDB\WriteFile>

#include <wx\dcclient.h>

#include "UIOcclusionGeneration.h"
#include "UIControlPoint.h"
#include "UIContainer.h"

#include "Helper.h"
#include "ApplicationPaths.h"
#include "VolumeViewer.h"
#include "VolumeInfo.h"
#include "Logger.h"

//============================================================================
UIOcclusionGeneration::UIOcclusionGeneration( wxWindow* parent )
:
OcclusionGeneration( parent )
{
  FS();
  Init();
  FE();
}
//============================================================================
void UIOcclusionGeneration::Init()
{
  FS();
  UIContainer* container = dynamic_cast<UIContainer*>(GetParent());
  if (container != 0)
  {
    m_topView = container->m_topView;
  }
  m_histogram.LoadFile(HIST_IMAGE, wxBITMAP_TYPE_ANY);
  m_bmpVisMapping->SetBitmap(m_histogram);

  m_bmpVisMapping->DestroyChildren();
  m_points.clear();

  m_bmpVisMapping->GetToolTip()->SetMaxWidth(-1);
  wxString posstr = wxString(wxT("Amplitude histogram"));
  m_bmpVisMapping->SetToolTip(posstr);
  m_bmpVisMapping->GetToolTip()->SetMaxWidth(-1);
  m_bmpVisMapping->GetToolTip()->SetDelay(1000);

  m_cancel = false;

  SetPosition(wxPoint(1080, 50));

  m_radioBtnSamplingCube->Enable(false);
  m_radioBtnSamplingSphere->Enable(false);
  m_radioBtnSamplingEllipse->Enable(false);

  m_dirty = true;

  FE();
}
//============================================================================
void UIOcclusionGeneration::OnIdle( wxIdleEvent& event )
{
  if(m_dirty == true)
  {
    Draw(m_bmpVisMapping);
    m_dirty = false;
  }

  event.RequestMore();
}
//============================================================================
void UIOcclusionGeneration::OnLeftDown( wxMouseEvent& event )
{
  switch(event.GetId())
  {
  case bmpVisMapping:
    int x = event.GetPosition().x;
    int y = event.GetPosition().y;

    UIControlPoint* cp = new UIControlPoint(m_bmpVisMapping, this);
    cp->SetPosition(wxPoint(x, y));

    m_points.insert(cp);
    m_dirty = true;

    break;
  }
}
//============================================================================
void UIOcclusionGeneration::Draw(wxWindow* win)
{
  win->ClearBackground();

  wxWindowDC dc(win);
  dc.DrawBitmap(m_histogram, 0, 0);

  wxPoint tmp(0, 0);
  std::set<UIControlPoint*, DereferenceLess>::iterator i;
  for (i = m_points.begin(); i != m_points.end(); ++i)
  {
    UIControlPoint* point = *i;

    wxPoint pos = point->GetPosition() + wxPoint(6, 6);
    dc.DrawLine(tmp, pos);
    tmp = pos;

    point->Refresh();
  }
  dc.DrawLine(tmp, wxPoint(255, 0));
}

//============================================================================
void UIOcclusionGeneration::OnLeftUp( wxMouseEvent& event )
{
}
//============================================================================
void UIOcclusionGeneration::OnMotion( wxMouseEvent& event )
{
}
//============================================================================
void UIOcclusionGeneration::OnButton( wxCommandEvent& event )
{
  switch(event.GetId())
  {
  case buttonResetVisMapping:
    {
      m_bmpVisMapping->DestroyChildren();
      m_points.clear();
      m_dirty = true;
      break;
    }
  case buttonLaunchOccGen:
    if(m_points.size() > 0)
    {
      WriteVisibilityMapping(VIS_MAPPING);
      GenerateOcclusion();
    }
    else
    {
      Logger::Log("No visibility mapping defined!");
    }
    break;
  case buttonCancelOccGen:
    this->Close(true);
    break;
  default:
    break;
  }
}
//============================================================================
void UIOcclusionGeneration::OnRadio( wxCommandEvent& event )
{
  switch(event.GetId())
  {
  case radioBtnSamplingCube:
    printf("Radio radioBtnSamplingCube \n");
    break;
  case radioBtnSamplingSphere:
    printf("Radio radioBtnSamplingSphere \n");
    break;
  case radioBtnSamplingEllipse:
    printf("Radio radioBtnSamplingEllipse \n");
    break;
  default:
    break;
  }
}
//============================================================================
void UIOcclusionGeneration::OnSpinCtrl( wxSpinEvent& event )
{
  switch(event.GetId())
  {
  case spinCtrlSamplingRadius:
    printf("Spin spinCtrlSamplingRadius \n");
    break;
  case spinCtrlOccScaling:
    printf("Spin spinCtrlOccScaling \n");
    break;
  default:
    break;
  }
}
//============================================================================
void UIOcclusionGeneration::RefreshControlPoint(UIControlPoint* point)
{
  m_points.erase(point);
  m_points.insert(point);

  wxPoint pos = point->GetPosition();

  int ix = pos.x + 5;
  int iy = 100 - pos.y - 5;

  float x = (float)ix / 255;
  float y = (float)iy / 100;

  std::stringstream sx;
  sx << x;
  m_txtPointCoordsX->SetValue(sx.str().c_str());

  std::stringstream sy;
  sy << y;
  m_txtPointCoordsY->SetValue(sy.str().c_str());

  m_dirty = true;
}
//============================================================================
void UIOcclusionGeneration::RemoveControlPoint(UIControlPoint* point)
{
  m_points.erase(point);
  m_bmpVisMapping->RemoveChild(point);

  m_dirty = true;
}
//============================================================================
void UIOcclusionGeneration::WriteVisibilityMapping(const char* path)
{
  FS();
  std::ofstream outfile;
  outfile.open(path);

  std::set<UIControlPoint*, DereferenceLess>::iterator i;
  for (i = m_points.begin(); i != m_points.end(); ++i)
  {
    UIControlPoint* point = *i;

    wxPoint pos = point->GetPosition();

    int ix = pos.x + 5;
    int iy = 100 - pos.y - 5;

    float x = (float)ix / 255;
    float y = (float)iy / 100;

    outfile << "point(" << x << "; " << y << ")\n";
  }
  outfile.close();
  FE();
}
//============================================================================
void UIOcclusionGeneration::GenerateOcclusion()
{
  FS();

  // output radius and scale for kernel launch
  int radius = m_spinCtrlSamplingRadius1->GetValue();
  int scale = m_spinCtrlOccScaling1->GetValue();

  // ===============================================
  // kernel setup
  std::stringstream command;
  if (m_topView->GetNumBytes() == 1)
  {
    command << "occgen8.exe ";
  }
  else if (m_topView->GetNumBytes() == 2)
  {
    command << "occgen16.exe ";
  }

  command << "-in " << VOL_IMAGE << " -out " << WORK_IMAGE << " ";
  command << "-rad " << radius << " -scale " << scale;
  command << "\n";

  Logger::Log(command.str().c_str());

  // launch
  system(command.str().c_str());

  // ===============================================
  // crossplot setup
  osg::Image* hist = Helper::CreateCrossPlot(osgDB::readImageFile(WORK_IMAGE));
  osgDB::writeImageFile(*hist, OCC_SPECTRUM);
  
  ref_ptr<VolumeInfo> volInfo = m_topView->GetVolInfo();
  volInfo->file = WORK_IMAGE;

  UIContainer* container = dynamic_cast<UIContainer*>(GetParent());
  if (container != 0)
  {
    container->m_fileToLoad = volInfo;
    container->m_sceneDirty = true;
  }

  FE();
}
