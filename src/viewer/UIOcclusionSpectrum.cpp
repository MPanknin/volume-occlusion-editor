#pragma warning( disable : 4100 )

#include <osg/ref_ptr>

#include <wx\dcclient.h>

#include "UIOcclusionSpectrum.h"
#include "UIPolyPoint.h"
#include "UIContainer.h"

#include "Helper.h"
#include "Logger.h"
#include "VolumeViewer.h"
#include "ApplicationPaths.h"

UIOcclusionSpectrum::UIOcclusionSpectrum( wxWindow* parent )
:
OcclusionSpectrum( parent )
{
  FS();
  Init();
  FE();
}
//============================================================================
void UIOcclusionSpectrum::Init()
{
  FS();

  UIContainer* container = dynamic_cast<UIContainer*>(GetParent());
  if (container != 0)
  {
    m_topView = container->m_topView;
  }

  m_spectrum.LoadFile(OCC_SPECTRUM, wxBITMAP_TYPE_ANY);
  m_bmpOcclusionSpectrum->SetBitmap(m_spectrum);

  wxPoint occPos = m_bmpOcclusionSpectrum->GetPosition();

  m_bmpOcclusionSpectrum->DestroyChildren();
  m_poly1.clear();
  m_poly2.clear();
  m_poly3.clear();

  // ==============================
  // polygon 1
  UIPolyPoint* cp = new UIPolyPoint(this, m_bmpOcclusionSpectrum);
  wxPoint tmp(0, 0);
  tmp += occPos;
  cp->SetPosition(tmp);
  m_poly1.push_back(cp);

  cp = new UIPolyPoint(this, m_bmpOcclusionSpectrum);
  tmp = wxPoint(0, 512);
  tmp += occPos;
  cp->SetPosition(tmp);
  m_poly1.push_back(cp);

  cp = new UIPolyPoint(this, m_bmpOcclusionSpectrum);
  tmp = wxPoint(512, 512);
  tmp += occPos;
  cp->SetPosition(tmp);
  m_poly1.push_back(cp);

  cp = new UIPolyPoint(this, m_bmpOcclusionSpectrum);
  tmp = wxPoint(512, 0);
  tmp += occPos;
  cp->SetPosition(tmp);
  m_poly1.push_back(cp);

  // ==============================
  // polygon 2
  cp = new UIPolyPoint(this, m_bmpOcclusionSpectrum);
  tmp = wxPoint(350, 250);
  tmp += occPos;
  cp->SetPosition(tmp);
  m_poly2.push_back(cp);

  cp = new UIPolyPoint(this, m_bmpOcclusionSpectrum);
  tmp = wxPoint(350, 500);
  tmp += occPos;
  cp->SetPosition(tmp);
  m_poly2.push_back(cp);

  cp = new UIPolyPoint(this, m_bmpOcclusionSpectrum);
  tmp = wxPoint(500, 500);
  tmp += occPos;
  cp->SetPosition(tmp);
  m_poly2.push_back(cp);

  cp = new UIPolyPoint(this, m_bmpOcclusionSpectrum);
  tmp = wxPoint(500, 250);
  tmp += occPos;
  cp->SetPosition(tmp);
  m_poly2.push_back(cp);

  // ==============================
  // polygon 3
  cp = new UIPolyPoint(this, m_bmpOcclusionSpectrum);
  tmp = wxPoint(230, 350);
  tmp += occPos;
  cp->SetPosition(tmp);
  m_poly3.push_back(cp);

  cp = new UIPolyPoint(this, m_bmpOcclusionSpectrum);
  tmp = wxPoint(280, 350);
  tmp += occPos;
  cp->SetPosition(tmp);
  m_poly3.push_back(cp);

  cp = new UIPolyPoint(this, m_bmpOcclusionSpectrum);
  tmp = wxPoint(280, 370);
  tmp += occPos;
  cp->SetPosition(tmp);
  m_poly3.push_back(cp);

  cp = new UIPolyPoint(this, m_bmpOcclusionSpectrum);
  tmp = wxPoint(230, 370);
  tmp += occPos;
  cp->SetPosition(tmp);
  m_poly3.push_back(cp);

  m_selection = new UIPolyPoint(m_bmpOcclusionSpectrum);
  m_selection->SetBackgroundColour(wxColor(255, 0, 0, 255));
  tmp = wxPoint(128, 128);
  m_selection->SetPosition(tmp);

  m_x = GetPosition().x;
  m_y = GetPosition().y;
  
  m_drag1 = false;
  m_drag2 = false;
  m_drag3 = false;

  m_active1 = true;
  m_active2 = false;
  m_active3 = false;

  m_checkBoxPolygon1->SetValue(m_active1);
  m_checkBoxPolygon2->SetValue(m_active2);
  m_checkBoxPolygon3->SetValue(m_active3);

  // ==============================
  // pick indicator / single point indicator
  m_selection = new UIPolyPoint(m_bmpOcclusionSpectrum);
  m_selection->SetBackgroundColour(wxColor(255, 0, 0, 255));
  tmp = wxPoint(128, 128);
  m_selection->SetPosition(tmp);

  // ==============================
  // trigger redraw
  m_dirty = true;

  m_bmpOcclusionSpectrum->GetToolTip()->SetMaxWidth(-1);
  wxString posstr = wxString(wxT("Occlusion Spectrum"));
  m_bmpOcclusionSpectrum->SetToolTip(posstr);
  m_bmpOcclusionSpectrum->GetToolTip()->SetMaxWidth(-1);
  m_bmpOcclusionSpectrum->GetToolTip()->SetDelay(1000);

  FE();
}
//============================================================================
void UIOcclusionSpectrum::OnIdle( wxIdleEvent& event )
{
  if(m_dirty == true || m_topView->IsSelectionDirty())
  {
    Draw(m_bmpOcclusionSpectrum);
    m_dirty = false;
  }
  event.RequestMore();
}
//============================================================================
void UIOcclusionSpectrum::OnClose( wxCloseEvent& event )
{
  FS();

  // need to reset selection points on close
  int num = m_poly1.size();
  float* px = new float[num];
  float* py = new float[num];

  wxPoint points1[15];
  
  px[0] = 0;
  px[1] = 0;
  px[2] = 256;
  px[3] = 256;

  py[0] = 0;
  py[1] = 256;
  py[2] = 256;
  py[3] = 0;

  if(m_topView)
  {
    m_topView->UpdatePoly(1, num, px, py);
    m_topView->UpdatePoly(2, num, px, py);
    m_topView->UpdatePoly(3, num, px, py);
  }
  delete px;
  delete py;

  this->Destroy();
  FE();
}
//============================================================================
void UIOcclusionSpectrum::Draw(wxWindow* win)
{
  win->ClearBackground();
  wxWindowDC dc(win);
  dc.DrawBitmap(m_spectrum, 0, 0);

  int num = m_poly1.size();
  float* px1 = new float[num];
  float* py1 = new float[num];

  float* px2 = new float[num];
  float* py2 = new float[num];

  float* px3 = new float[num];
  float* py3 = new float[num];

  wxPoint points1[15];
  wxPoint points2[15];
  wxPoint points3[15];

  for(int i = 0; i < num; i++)
  {
    wxPoint tmp;
    if(m_active1)
    {
      tmp = m_poly1[i]->GetPosition() - m_bmpOcclusionSpectrum->GetPosition();
      px1[i] = tmp.x / 2.0f;
      py1[i] = (512.0f - tmp.y) / 2;
      points1[i] = tmp;
    }
    if(m_active2)
    {
      tmp = m_poly2[i]->GetPosition() - m_bmpOcclusionSpectrum->GetPosition();
      px2[i] = tmp.x / 2.0f;
      py2[i] = (512.0f - tmp.y) / 2;
      points2[i] = tmp;
    }
    if(m_active3)
    {
      tmp = m_poly3[i]->GetPosition() - m_bmpOcclusionSpectrum->GetPosition();
      px3[i] = tmp.x / 2.0f;
      py3[i] = (512.0f - tmp.y) / 2;
      points3[i] = tmp;
    }
  }

  if(m_topView)
  {
    m_topView->UpdatePoly(1, num, px1, py1);
    m_topView->UpdatePoly(2, num, px2, py2);
    m_topView->UpdatePoly(3, num, px3, py3);
  }
  delete px1;
  delete py1;

  delete px2;
  delete py2;

  delete px3;
  delete py3;

  dc.SetBrush(wxBrush(wxColor(100, 0, 0, 10), wxTRANSPARENT));
  if(m_active1)
    dc.DrawPolygon(num, points1);
  if(m_active2)
    dc.DrawPolygon(num, points2);
  if(m_active3)
    dc.DrawPolygon(num, points3);

  for(int i = 0; i < num; i++)
  {
    if(m_active1)
      m_poly1[i]->Refresh();
    if(m_active2)
      m_poly2[i]->Refresh();
    if(m_active3)
      m_poly3[i]->Refresh();
  }

  // update pick indicator
  osg::Vec2 sel = *m_topView->GetSelectedVoxel();
  m_selection->SetPosition(wxPoint(sel.x() * 2, 512 - sel.y() * 2));
  m_selection->Refresh();
}

//============================================================================
void UIOcclusionSpectrum::OnLeftDown( wxMouseEvent& event )
{
  FS();
  wxPoint p = event.GetPosition();

  int num = m_poly1.size();
  float* px1 = new float[num];
  float* py1 = new float[num];
  for (int i = 0; i < num; i++)
  {
    wxPoint tmp = m_poly1[i]->GetPosition();
    px1[i] = tmp.x;
    py1[i] = tmp.y;
  }

  num = m_poly2.size();
  float* px2 = new float[num];
  float* py2 = new float[num];
  for (int i = 0; i < num; i++)
  {
    wxPoint tmp = m_poly2[i]->GetPosition();
    px2[i] = tmp.x;
    py2[i] = tmp.y;
  }

  num = m_poly3.size();
  float* px3 = new float[num];
  float* py3 = new float[num];
  for (int i = 0; i < num; i++)
  {
    wxPoint tmp = m_poly3[i]->GetPosition();
    px3[i] = tmp.x;
    py3[i] = tmp.y;
  }

  if(m_active1 && Helper::PointInPoly(num, px1, py1, p.x, p.y))
  {
    CaptureMouse();
    m_x = event.GetX();
    m_y = event.GetY();
    m_drag1 = true;
  }
  else if(m_active2 && Helper::PointInPoly(num, px2, py2, p.x, p.y))
  {
    CaptureMouse();
    m_x = event.GetX();
    m_y = event.GetY();
    m_drag2 = true;
  }
  else if(m_active3 && Helper::PointInPoly(num, px3, py3, p.x, p.y))
  {
    CaptureMouse();
    m_x = event.GetX();
    m_y = event.GetY();
    m_drag3 = true;
  }
  else 
  {
    m_drag1 = false;
    m_drag2 = false;
    m_drag3 = false;
  }

  delete px1;
  delete py1;

  FE();
}
//============================================================================
void UIOcclusionSpectrum::OnLeftUp( wxMouseEvent& event )
{
  ReleaseMouse();
  m_drag1 = false;
  m_drag2 = false;
  m_drag3 = false;
}
//============================================================================
void UIOcclusionSpectrum::OnMotion( wxMouseEvent& event )
{
  std::vector<UIPolyPoint*> target;
  if(m_drag1)
  {
    target = m_poly1;
  }
  else if(m_drag2)
  {
    target = m_poly2;
  }
  else if(m_drag3)
  {
    target = m_poly3;
  }

  if(m_drag1 || m_drag2 || m_drag3)
  {
    wxPoint p = event.GetPosition();
    int newx = p.x - m_x;
    int newy = p.y - m_y;
    for (int i = 0; i < target.size(); i++)
    {
      wxPoint dest = target[i]->GetPosition() + wxPoint(newx, newy);
      target[i]->Move(dest);
    }
    m_x = p.x;
    m_y = p.y;

    m_dirty = true;
  }
}
//============================================================================
void UIOcclusionSpectrum::OnCheckBox( wxCommandEvent& event )
{
  switch(event.GetId())
  {
  case checkBoxPolygon1:
    m_active1 = event.IsChecked();
    m_dirty = true;
    break;
  case checkBoxPolygon2:
    m_active2 = event.IsChecked();
    m_dirty = true;
    break;
  case checkBoxPolygon3:
    m_active3 = event.IsChecked();
    m_dirty = true;
    break;
  case checkBoxSinglePoint:
    printf("CheckBox checkBoxSinglePoint \n");
    break;
  default:
    break;
  }
}

//============================================================================
void UIOcclusionSpectrum::OnButton( wxCommandEvent& event )
{
  switch(event.GetId())
  {
  case buttonResetPolygons:
    Init();
    printf("Button buttonResetPolygons \n");
    break;
  default:
    break;
  }
}

//============================================================================
void UIOcclusionSpectrum::RefreshControlPoint(UIPolyPoint* point)
{
  m_dirty = true;
}
//============================================================================
void UIOcclusionSpectrum::RemoveControlPoint(UIPolyPoint* point)
{
}
