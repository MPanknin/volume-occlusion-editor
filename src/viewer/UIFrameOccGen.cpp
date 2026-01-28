#include "UIFrameOccGen.h"
#include "VolumeManager.h"
#include "wx\msw\dcclient.h"

bool g_redraw = false;

UIFrameOccGen::UIFrameOccGen( wxWindow* parent )
:
FrameOccGen( parent )
{
  wxPoint occPos = m_bmpSpectrum->GetPosition();

  // ==============================
  // polygon 1
  UIPolyPoint* cp = new UIPolyPoint(this, m_bmpSpectrum);
  wxPoint tmp(10, 250);
  tmp += occPos;
  cp->SetPosition(tmp);
  m_poly1.push_back(cp);

  cp = new UIPolyPoint(this, m_bmpSpectrum);
  tmp = wxPoint(10, 500);
  tmp += occPos;
  cp->SetPosition(tmp);
  m_poly1.push_back(cp);

  cp = new UIPolyPoint(this, m_bmpSpectrum);
  tmp = wxPoint(150, 500);
  tmp += occPos;
  cp->SetPosition(tmp);
  m_poly1.push_back(cp);

  cp = new UIPolyPoint(this, m_bmpSpectrum);
  tmp = wxPoint(150, 250);
  tmp += occPos;
  cp->SetPosition(tmp);
  m_poly1.push_back(cp);

  // ==============================
  // polygon 2
  cp = new UIPolyPoint(this, m_bmpSpectrum);
  tmp = wxPoint(350, 250);
  tmp += occPos;
  cp->SetPosition(tmp);
  m_poly2.push_back(cp);

  cp = new UIPolyPoint(this, m_bmpSpectrum);
  tmp = wxPoint(350, 500);
  tmp += occPos;
  cp->SetPosition(tmp);
  m_poly2.push_back(cp);

  cp = new UIPolyPoint(this, m_bmpSpectrum);
  tmp = wxPoint(500, 500);
  tmp += occPos;
  cp->SetPosition(tmp);
  m_poly2.push_back(cp);

  cp = new UIPolyPoint(this, m_bmpSpectrum);
  tmp = wxPoint(500, 250);
  tmp += occPos;
  cp->SetPosition(tmp);
  m_poly2.push_back(cp);

  // ==============================
  // polygon 3
  cp = new UIPolyPoint(this, m_bmpSpectrum);
  tmp = wxPoint(230, 350);
  tmp += occPos;
  cp->SetPosition(tmp);
  m_poly3.push_back(cp);

  cp = new UIPolyPoint(this, m_bmpSpectrum);
  tmp = wxPoint(280, 350);
  tmp += occPos;
  cp->SetPosition(tmp);
  m_poly3.push_back(cp);

  cp = new UIPolyPoint(this, m_bmpSpectrum);
  tmp = wxPoint(280, 370);
  tmp += occPos;
  cp->SetPosition(tmp);
  m_poly3.push_back(cp);

  cp = new UIPolyPoint(this, m_bmpSpectrum);
  tmp = wxPoint(230, 370);
  tmp += occPos;
  cp->SetPosition(tmp);
  m_poly3.push_back(cp);

  // ==============================
  // pick indicator
  m_selection = new UIPolyPoint(m_bmpSpectrum);
  m_selection->SetBackgroundColour(wxColor(255, 0, 0, 255));
  tmp = wxPoint(128, 128);
  m_selection->SetPosition(tmp);

  m_x = GetPosition().x;
  m_y = GetPosition().y;
  m_drag1 = false;
  m_drag2 = false;
  m_drag3 = false;

  g_redraw = true;
  m_swapBytes = false;
}

void UIFrameOccGen::OnIdle( wxIdleEvent& event )
{
  if(VolumeManager::i()->isSelectionDirty())
  {
    g_redraw = true;
  }
  if(g_redraw == true)
  {
    draw(m_bmpSpectrum);
    g_redraw = false;
  }
  event.RequestMore();
}

// ====================================================
int pnpoly(int nvert, float* vertx, float* verty, float testx, float testy)
{
  int i, j, c = 0;
  for (i = 0, j = nvert-1; i < nvert; j = i++) {
    if ( ((verty[i]>testy) != (verty[j]>testy)) &&
      (testx < (vertx[j]-vertx[i]) * (testy-verty[i]) / (verty[j]-verty[i]) + vertx[i]) )
      c = !c;
  }
  return c;
}

void UIFrameOccGen::setCrossplot(const char* file)
{
  std::stringstream s;
  s << file << "\\temp\\occ_spectrum.bmp";
  m_spectrum.LoadFile(s.str().c_str(), wxBITMAP_TYPE_ANY);
  m_bmpSpectrum->Enable(false);
  m_bmpSpectrum->SetBitmap(m_spectrum);
}


void UIFrameOccGen::OnLeftDown( wxMouseEvent& event )
{
  printf(__FUNCTION__); printf("\n");
  
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

  if(pnpoly(num, px1, py1, p.x, p.y) == 1)
  {
    CaptureMouse();
    m_x = event.GetX();
    m_y = event.GetY();
    m_drag1 = true;
  }
  else if(pnpoly(num, px2, py2, p.x, p.y) == 1)
  {
    CaptureMouse();
    m_x = event.GetX();
    m_y = event.GetY();
    m_drag2 = true;
  }
  else if(pnpoly(num, px3, py3, p.x, p.y) == 1)
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
}

void UIFrameOccGen::OnLeftUp( wxMouseEvent& event )
{
  ReleaseMouse();
  m_drag1 = false;
  m_drag2 = false;
  m_drag3 = false;
}

void UIFrameOccGen::OnMotion( wxMouseEvent& event )
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
    g_redraw = true;
    m_x = p.x;
    m_y = p.y;
  }
}

void UIFrameOccGen::OnPaint( wxPaintEvent& event )
{
  g_redraw = true;
}

void UIFrameOccGen::OnCheckBox( wxCommandEvent& event )
{
  //printf(__FUNCTION__); printf("\n");
}

// ===============================================================
void UIFrameOccGen::draw(wxWindow* win)
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
    wxPoint tmp = m_poly1[i]->GetPosition() - m_bmpSpectrum->GetPosition();
    px1[i] = tmp.x / 2.0f;
    py1[i] = (512.0f - tmp.y) / 2;
    points1[i] = tmp;
  
    tmp = m_poly2[i]->GetPosition() - m_bmpSpectrum->GetPosition();
    px2[i] = tmp.x / 2.0f;
    py2[i] = (512.0f - tmp.y) / 2;
    points2[i] = tmp;

    tmp = m_poly3[i]->GetPosition() - m_bmpSpectrum->GetPosition();
    px3[i] = tmp.x / 2.0f;
    py3[i] = (512.0f - tmp.y) / 2;
    points3[i] = tmp;
  }

  if(m_technique)
  {
    m_technique->updatePoly(1, num, px1, py1);
    m_technique->updatePoly(2, num, px2, py2);
    m_technique->updatePoly(3, num, px3, py3);
  }
  delete px1;
  delete py1;
  
  delete px2;
  delete py2;

  delete px3;
  delete py3;

  dc.SetBrush(wxBrush(wxColor(100, 0, 0, 10), wxTRANSPARENT));
  dc.DrawPolygon(num, points1);
  dc.DrawPolygon(num, points2);
  dc.DrawPolygon(num, points3);

  for(unsigned int i = 0; i < num; i++)
  {
    m_poly1[i]->Refresh();
    m_poly2[i]->Refresh();
    m_poly3[i]->Refresh();
  }

  // update pick indicator
  osg::Vec2 sel = VolumeManager::i()->getSelectedVoxel();
  m_selection->SetPosition(wxPoint(sel.x() * 2, 512 - sel.y() * 2));
  m_selection->Refresh();
}
// ===============================================================
void UIFrameOccGen::RefreshControlPoint(UIPolyPoint* point)
{
  g_redraw = true;
}
