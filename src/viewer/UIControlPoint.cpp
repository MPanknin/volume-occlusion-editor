#pragma warning( disable : 4100 )

#include <wx\msw\dcclient.h>

#include "UIControlPoint.h"
#include "UIControlPointInterface.h"

#include "Logger.h"
//============================================================================
UIControlPoint::UIControlPoint( wxWindow* parent, UIControlPointInterface* color)
:
ControlPoint(parent)
{
  m_parent = color;
  m_x = GetPosition().x;
  m_y = GetPosition().y;
  m_drag = false;

  wxString posstr = wxString::Format(wxT("%i : %i"), m_x, m_y);
  this->SetToolTip(posstr);
}
//============================================================================
bool UIControlPoint::operator<( const UIControlPoint& p )
{
  return GetPosition().x < p.GetPosition().x;
}
//============================================================================
void UIControlPoint::OnLeftDown( wxMouseEvent& event )
{
  CaptureMouse();
  m_x = event.GetX();
  m_y = event.GetY();
  m_drag = true;
}
//============================================================================
void UIControlPoint::OnLeftUp( wxMouseEvent& event )
{
  ReleaseMouse();
  m_drag = false;
}
//============================================================================
void UIControlPoint::OnMotion(wxMouseEvent& event )
{
  if(m_drag)
  {
    wxPoint mouseOnScreen = wxGetMousePosition();
    int newx = mouseOnScreen.x - m_x;
    int newy = mouseOnScreen.y - m_y;

    if (m_parent != 0)
    {
      wxPoint dest = GetParent()->ScreenToClient(wxPoint(newx, newy));
      if(dest.x < -5) dest.x = -5;
      if(dest.x > 250) dest.x = 250;
      if(dest.y < -5) dest.y = -5;
      if(dest.y > 95) dest.y = 95;

      Move(dest);
      m_parent->RefreshControlPoint(this);  	

      wxString posstr = wxString::Format(wxT("%i : %i"), dest.x + 5, 100 - dest.y - 5);
      this->SetToolTip(posstr);
      this->GetToolTip()->SetMaxWidth(0);
      this->GetToolTip()->SetDelay(0);
    }
  }
}
//============================================================================
void UIControlPoint::OnRightUp( wxMouseEvent& event )
{
  m_parent->RemoveControlPoint(this);  	
  this->Destroy();
}
