#pragma warning( disable : 4100 )

#ifdef _WIN32
#include <wx/msw/dcclient.h>

#include "UIPolyPoint.h"
#include "UIOcclusionSpectrum.h"

//============================================================================
UIPolyPoint::UIPolyPoint( wxWindow* parent )
:
PolyPoint(parent)
{
  m_parent = static_cast<UIOcclusionSpectrum*>(GetParent());
  m_x = GetPosition().x;
  m_y = GetPosition().y;
  m_drag = false;

  wxString posstr = wxString::Format(wxT("%i : %i"), m_x, m_y);
  this->SetToolTip(posstr);
}
//============================================================================
UIPolyPoint::UIPolyPoint( wxWindow* parent, wxStaticBitmap* spectrum  )
:
PolyPoint(parent)
{
  m_parent = static_cast<UIOcclusionSpectrum*>(GetParent());
  m_x = GetPosition().x;
  m_y = GetPosition().y;
  m_drag = false;
  m_bmpSpectrum = spectrum;
}
//============================================================================
void UIPolyPoint::OnLeftDown( wxMouseEvent& event )
{
  CaptureMouse();
  m_x = event.GetX();
  m_y = event.GetY();
  m_drag = true;
}
//============================================================================
void UIPolyPoint::OnLeftUp( wxMouseEvent& event )
{
  ReleaseMouse();
  m_drag = false;
}
//============================================================================
void UIPolyPoint::OnMotion( wxMouseEvent& event )
{
  if(m_drag)
  {
    wxPoint mouseOnScreen = wxGetMousePosition();
    int newx = mouseOnScreen.x - m_x;
    int newy = mouseOnScreen.y - m_y;

    if(m_parent)
    {
      wxPoint dest = m_parent->ScreenToClient(wxPoint(newx, newy));
      int x = m_bmpSpectrum->GetPosition().x;
      int y = m_bmpSpectrum->GetPosition().y;

      if(dest.x < x) dest.x = x;
      if(dest.x > x+512) dest.x = x+512;
      if(dest.y < y) dest.y = y;
      if(dest.y > y+512) dest.y = y+512;

      Move(dest);
      m_parent->RefreshControlPoint(this);  

      wxString posstr = wxString::Format(wxT("%i : %i"), dest.x, dest.y);
      this->SetToolTip(posstr);
      this->GetToolTip()->SetMaxWidth(0);
      this->GetToolTip()->SetDelay(0);
    }
  }
}
//============================================================================
void UIPolyPoint::OnRightUp( wxMouseEvent& event )
{
}
