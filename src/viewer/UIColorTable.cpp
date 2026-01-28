#pragma warning( disable : 4100 )

#include <iosfwd>

#include <osg/ref_ptr>
#include <osgDB/ReadFile>
#include <osg/TransferFunction>

#ifdef _WIN32
#include <wx/msw/dcclient.h>

#include "UIColorTable.h"
#include "UIContainer.h"
#include "UIControlPoint.h"

#include "Logger.h"
#include "VolumeViewer.h"
#include "ApplicationPaths.h"

//============================================================================
UIColorTable::UIColorTable( wxWindow* parent )
:
ColorTable(parent)
{
  FS();
  Init();
  FE();
}
//============================================================================
void UIColorTable::Init()
{
  FS();
  UIContainer* container = dynamic_cast<UIContainer*>(GetParent());
  if (container != 0)
  {
    m_topView = container->m_topView;
  }

  m_transfer = new osg::TransferFunction1D;
  m_transfer->allocate(256);
  m_transfer->clear(osg::Vec4(1.0, 1.0, 1.0, 1.0));
  m_topView->UpdateTexture(RayCastTechnique::OPACITY, m_transfer->getImage());

  m_histogram.LoadFile(HIST_IMAGE, wxBITMAP_TYPE_ANY);
  m_bmpPreviewOpacity->SetBitmap(m_histogram);

  m_bmpPreviewOpacity->DestroyChildren();
  m_points.clear();

  m_bmpPreviewOpacity->GetToolTip()->SetMaxWidth(-1);
  wxString posstr = wxString(wxT("Amplitude histogram"));
  m_bmpPreviewOpacity->SetToolTip(posstr);
  m_bmpPreviewOpacity->GetToolTip()->SetMaxWidth(-1);
  m_bmpPreviewOpacity->GetToolTip()->SetDelay(1000);

  SetPosition(wxPoint(1080, 432));

  std::string prev = INITIAL_COLOR_TABLE_PREVIEW;
  std::string path = PATH_COLOR_TABLES;

  prev.insert(0, path);

  wxImage preview(prev.c_str(), wxBITMAP_TYPE_ANY);
  m_bmpPreviewTransfer->SetBitmap(preview);

  m_dirty = true;

  FE();
}
//============================================================================
void UIColorTable::OnComboBox( wxCommandEvent& event )
{
  switch(event.GetId())
  {
  case comboTransfer:
    {
      std::string file = event.GetString().Append(".tga");
      std::string prev = event.GetString().Append("_preview.bmp");
      std::string path = PATH_COLOR_TABLES;
      
      file.insert(0, path);
      prev.insert(0, path);

      m_topView->UpdateTexture(RayCastTechnique::TRANSFER, osgDB::readImageFile(file.c_str()));
      wxImage preview(prev.c_str(), wxBITMAP_TYPE_ANY);
      m_bmpPreviewTransfer->SetBitmap(preview);

      break;
    }
  default:
    break;
  }
}
//============================================================================
void UIColorTable::OnSpinCtrl( wxSpinEvent& event )
{
  switch(event.GetId())
  {
  case spinCtrIntensityMult:
    {
      m_topView->SetIntensityMult(event.GetValue());
      break;
    }
  default:
    break;
  }
}
//============================================================================
void UIColorTable::OnButton( wxCommandEvent& event )
{
  switch(event.GetId())
  {
  case buttonResetColorTable:
    {
      m_bmpPreviewOpacity->DestroyChildren();
      m_points.clear();

      m_dirty = true;
      break;
    }
  default:
    break;
  }
}
//============================================================================
void UIColorTable::OnLeftDown( wxMouseEvent& event )
{
  switch(event.GetId())
  {
  case bmpPreviewOpacity:
    int x = event.GetPosition().x;
    int y = event.GetPosition().y;

    UIControlPoint* cp = new UIControlPoint(m_bmpPreviewOpacity, this);
    cp->SetPosition(wxPoint(x, y));
    m_points.insert(cp);

    m_dirty = true;
    break;
  }
}
//============================================================================
void UIColorTable::OnIdle( wxIdleEvent& event )
{
  if(m_dirty == true)
  {
    Draw(m_bmpPreviewOpacity);
    m_dirty = false;
  }
}
//============================================================================
void UIColorTable::Draw(wxWindow* win)
{
  win->ClearBackground();
  m_transfer->clear(osg::Vec4(1.0, 1.0, 1.0, 1.0));

  wxWindowDC dc(win);
  dc.DrawBitmap(m_histogram, 0, 0);

  wxPoint tmp(0, 0);
  std::set<UIControlPoint*, DereferenceLess>::iterator i;

  for (i = m_points.begin(); i != m_points.end(); ++i)
  {
    UIControlPoint* point = *i;

    wxPoint pos = point->GetPosition() + wxPoint (6, 6);
    dc.DrawLine(tmp, pos);
    tmp = pos;
    int x = point->GetPosition().x + 5;
    float val = (101 - tmp.y) / 100.0f;

    // update transfer function
    m_transfer->setColor(x, osg::Vec4(val, val, val, val));
    m_transfer->setColor(255, osg::Vec4(val, val, val, val));
  }

  dc.DrawLine(tmp, wxPoint(255, tmp.y));
  m_topView->UpdateTexture(RayCastTechnique::OPACITY, m_transfer->getImage());

  for (i = m_points.begin(); i != m_points.end(); ++i)
  {
    UIControlPoint* point = *i;
    point->Refresh();
  }
}
//============================================================================
void UIColorTable::RefreshControlPoint(UIControlPoint* point)
{
  m_points.erase(point);
  m_points.insert(point);

  m_dirty = true;
}
//============================================================================
void UIColorTable::RemoveControlPoint(UIControlPoint* point)
{
  m_points.erase(point);
  m_bmpPreviewOpacity->RemoveChild(point);

  m_dirty = true;
}
//============================================================================
void UIColorTable::OnLeftUp( wxMouseEvent& event )
{
  //printf("OnLeftUp \n");
}
//============================================================================
void UIColorTable::OnMotion( wxMouseEvent& event )
{
  // printf("OnMotion \n");
}
//============================================================================
void UIColorTable::OnRightDown( wxMouseEvent& event )
{
  // TODO: Implement OnRightDown
}
//============================================================================
void UIColorTable::OnRightUp( wxMouseEvent& event )
{
  // TODO: Implement OnRightUp
