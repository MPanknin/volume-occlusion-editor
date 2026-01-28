#include "UIFrame.h"
#include "VolumeManager.h"
#include "wx\msw\dcclient.h"

bool UIFrame::m_dirty = false;

UIFrame::UIFrame( wxWindow* parent )
:
Frame( parent )
{
  m_sldInline->SetRange(1000);
  m_sldInline->SetThumbPosition(500);

  m_sldTimeline->SetRange(1000);
  m_sldTimeline->SetThumbPosition(500);

  m_sldCrossline->SetRange(1000);
  m_sldCrossline->SetThumbPosition(500);

  m_transfer = new osg::TransferFunction1D;
  m_transfer->allocate(256);
  m_transfer->clear(osg::Vec4(1.0, 1.0, 1.0, 1.0));
  m_histogram.LoadFile(wxT("temp/hist.bmp"), wxBITMAP_TYPE_ANY);
  m_bmpPreviewOpacity->SetBitmap(m_histogram);

  _getcwd(path, _MAX_PATH);

  m_dirty = true;
}

void UIFrame::OnIdle( wxIdleEvent& event )
{
  if(m_dirty == true)
  {
    draw(m_bmpPreviewOpacity);
    m_dirty = false;
  }
  if (!m_viewer->isRealized())
    return;
  m_viewer->frame();
  event.RequestMore();
}

void UIFrame::OnSpinCtrl( wxSpinEvent& event )
{
  switch (event.GetId())
  {
  case spinIntensityMult:
    m_technique->setIntensityMult(event.GetValue());
    break;

  case spinXMax:
    m_technique->setClipping(RayCastTechnique::XMAX, event.GetValue());
  	break;
  case spinXMin:
    m_technique->setClipping(RayCastTechnique::XMIN, event.GetValue());
    break;

  case spinYMax:
    m_technique->setClipping(RayCastTechnique::YMAX, event.GetValue());
    break;
  case spinYMin:
    m_technique->setClipping(RayCastTechnique::YMIN, event.GetValue());
    break;

  case spinZMax:
    m_technique->setClipping(RayCastTechnique::ZMAX, event.GetValue());
    break;
  case spinZMin:
    m_technique->setClipping(RayCastTechnique::ZMIN, event.GetValue());
    break;
  }
}

void UIFrame::OnCheckBox( wxCommandEvent& event )
{
  switch(event.GetId())
  {
  case chkOcclusion:
    m_technique->toggleOcc();
    break;
  case chkVolume:
    m_technique->toggleRenderer();
    break;
  case chkTransfer:
    m_technique->toggleTransferFunction();
    break;
  case chkPhong:
    m_technique->togglePhong();
    break;
  case chkOccSpectrum:
    if (event.IsChecked())
    {
      m_occGen = new UIFrameOccGen(0);
      m_occGen->setCrossplot(path);
      m_occGen->SetPosition(wxPoint(1000, 400));
      m_occGen->Show(true);
      m_occGen->m_technique = m_technique;
    }
    else
    {
      m_occGen->Destroy();
    }
    break;
  default:
    break;
  }
}

void UIFrame::OnColourChanged( wxColourPickerEvent& event )
{
  switch(event.GetId())
  {
  case clrPickerClrColor:
    wxColour c = event.GetColour();
    m_viewer->getCamera()->setClearColor(osg::Vec4(c.Red(), c.Green(), c.Blue(), c.Alpha()));
    break;
  }
}

void UIFrame::OnComboBox( wxCommandEvent& event )
{
  std::stringstream s;
  s << path << "\\..\\data\\images\\";
	std::string transfer = s.str();
	transfer = transfer.append(event.GetString());
	std::string prev = transfer;
	prev = prev.append("_preview.bmp");
	transfer = transfer.append(".tga");
	m_technique->updateTexture(RayCastTechnique::TRANSFER, osgDB::readImageFile(transfer));
	wxImage preview(prev.c_str(), wxBITMAP_TYPE_ANY);
	m_bmpPreviewTransfer->SetBitmap(preview);
}

void UIFrame::OnButtonClick( wxCommandEvent& event )
{
  switch(event.GetId())
  {
  case btnResetOpacity:
    m_bmpPreviewOpacity->DestroyChildren();
    m_points.clear();
    m_dirty = true;
    break;
  }
}

void UIFrame::OnLeftDown( wxMouseEvent& event )
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

void UIFrame::OnLeftUp( wxMouseEvent& event )
{
// TODO: Implement OnLeftUp
}

void UIFrame::OnMotion( wxMouseEvent& event )
{
// TODO: Implement OnMotion
}

void UIFrame::OnRightDown( wxMouseEvent& event )
{
// TODO: Implement OnRightDown
}

void UIFrame::OnRightUp( wxMouseEvent& event )
{
// TODO: Implement OnRightUp
}

void UIFrame::OnSlider( wxScrollEvent& event )
{
  switch(event.GetId())
  {
  case sldInline:
    m_technique->moveLine(VoxelSlice::INLINE, event.GetInt(), "");
    m_viewer->frame();
    break;
  case sldCrossline:
    m_technique->moveLine(VoxelSlice::CROSSLINE, event.GetInt(), "");
    m_viewer->frame();
    break;
  case sldTimeline:
    //m_technique->moveLine(VoxelSlice::TIMELINE, event.GetInt(), "");
    //m_viewer->frame();
    break;
  default:
    break;
  }
}

void UIFrame::RefreshControlPoint(UIControlPoint* point)
{
  m_points.erase(point);
  m_points.insert(point);

  m_dirty = true;
}

void UIFrame::draw(wxWindow* win)
{
  //printf(__FUNCTION__); printf("\n");
  win->ClearBackground();
  m_transfer->clear(osg::Vec4(1.0, 1.0, 1.0, 1.0));

  wxWindowDC dc(win);
  dc.DrawBitmap(m_histogram, 0, 0);

  wxPoint tmp(0, 2);
  std::set<UIControlPoint*, DereferenceLess>::iterator i;
  for (i = m_points.begin(); i != m_points.end(); ++i)
  {
    wxPoint t = (*i)->GetPosition() + wxPoint(6, 6);
    dc.DrawLine(tmp, t);
    tmp = t;
    if((*i))(*i)->Refresh();
    float idx = (float)(*i)->GetPosition().x;
    float val = (100.0f - (float)tmp.y) / 100.0f;
    m_transfer->setColor(idx, osg::Vec4(val, val, val, val));
  }
  dc.DrawLine(tmp, wxPoint(255, 2));
  m_technique->updateTexture(RayCastTechnique::OPACITY, m_transfer->getImage());
}

void UIFrame::RemoveControlPoint(UIControlPoint* point)
{
  m_points.erase(point);
  m_bmpPreviewOpacity->RemoveChild(point);
  m_dirty = true;
}
