#include "UIExtractor.h"
#include "UIExtractor.h"
#include <sstream>
#include <set>
#include "wx/dcclient.h"
#include <iostream>
#include <fstream>
#include <osgDB/ReadFile>
#include <osgDB/ObjectWrapper>
#include "VolumeManager.h"

bool UIExtractor::m_dirty = true;

UIExtractor::UIExtractor( wxWindow* parent )
:
Extractor( parent )
{
  _getcwd(path, _MAX_PATH);

  m_hist.LoadFile(wxT("temp/hist.bmp"), wxBITMAP_TYPE_ANY);
  m_bmpVisMapping->SetBitmap(m_hist);

  m_dirty = true;
  m_voxelSize = 1;
  m_swapBytes = false;
}

void UIExtractor::OnIdle( wxIdleEvent& event )
{
  if(m_dirty == true)
  {
    draw(m_bmpVisMapping);
    m_dirty = false;
  }

  event.RequestMore();
}

void UIExtractor::OnPaint( wxPaintEvent& event )
{
// TODO: Implement OnPaint
}

void UIExtractor::OnFileChanged( wxFileDirPickerEvent& event )
{
	if(event.GetId() == pickerInputVolume)
		m_inputVolume = event.GetPath();
	else if(event.GetId() == pickerOutputVolume)
		m_outputVolume = event.GetPath();
}

void UIExtractor::OnComboBox( wxCommandEvent& event )
{
  wxString value;
  switch(event.GetId())
  {
  case comboEndian:
    value = m_comboEndian->GetValue();
    if(value.compare("Little-endian") == 1)
    {
      m_swapBytes = false;
    }
    else if(value.compare("Big-endian") == 0)
    {
      m_swapBytes = true;
    }
    break;
  case comboVoxelSize:
    value = m_comboVoxelSize->GetValue();
    int len = value.Len();
    m_voxelSize = atoi(value.SubString(0, len - 5)) / 8;
    break;
  }
}

void UIExtractor::OnButtonClick( wxCommandEvent& event )
{
  switch(event.GetId())
  {
  case btnExtract:
	  readInput();
    break;
  case btnReset:
    m_bmpVisMapping->DestroyChildren();
    m_points.clear();
    m_dirty = true;
    break;
  case btnLaunch:
    genOcclusion();
    break;
  }
}

void UIExtractor::OnLeftDown( wxMouseEvent& event )
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

void UIExtractor::OnLeftUp( wxMouseEvent& event )
{
// TODO: Implement OnLeftUp
}

void UIExtractor::OnMotion( wxMouseEvent& event )
{
// TODO: Implement OnMotion
}

void UIExtractor::RefreshControlPoint(UIControlPoint* point)
{
  m_points.erase(point);
  m_points.insert(point);

  float x = (float)point->GetPosition().x / (float)245;
  float y = (float)(90 - point->GetPosition().y) / (float)90;

  std::stringstream s;
  s << x << " " << y;
  m_txtPointCoords->SetValue(s.str().c_str());
  m_dirty = true;
}

void UIExtractor::RemoveControlPoint(UIControlPoint* point)
{
}

void UIExtractor::draw(wxWindow* win)
{
  //printf(__FUNCTION__); printf("\n");
  win->ClearBackground();

  wxWindowDC dc(win);
  dc.DrawBitmap(m_hist, 0, 0);

  wxPoint tmp(0, 2);
  std::set<UIControlPoint*, DereferenceLess>::iterator i;
  for (i = m_points.begin(); i != m_points.end(); ++i)
  {
    wxPoint t = (*i)->GetPosition() + wxPoint(6, 6);
    dc.DrawLine(tmp, t);
    tmp = t;
    if((*i))(*i)->Refresh();
  }
  dc.DrawLine(tmp, wxPoint(255, 2));
}

void UIExtractor::genOcclusion()
{
  std::ofstream outfile;
  outfile.open("vis.cfg");

  std::set<UIControlPoint*, DereferenceLess>::iterator i;
  for (i = m_points.begin(); i != m_points.end(); ++i)
  {
    wxPoint t = (*i)->GetPosition();
    float x = (float)t.x / (float)245;
    float y = (float)(90 - t.y) / (float)90;
    outfile << "point(" << x << "; " << y << ")\n";
  }
  outfile.close();

  // output radius and scale for kernel launch
  long radius;
  long scale;
  m_txtRadius->GetValue().ToLong(&radius);
  m_txtScale->GetValue().ToLong(&scale);

  // kernel setup
  std::stringstream s;
  s << path << "\\";

  if(m_voxelSize == 1)
    s << "occgen8.exe ";
  else if(m_voxelSize == 2)
    s << "occgen16.exe ";

  s << "-in " << m_outputVolume.c_str() << " -out " << path << "/temp/vol.dds ";
  s << "-rad " << (int) radius << " -scale " << (int) scale;
  s << "\n";

  std::cout << s.str().c_str();
  system(s.str().c_str());

  std::stringstream load;
  load << path << "\\" << "temp\\vol.dds";

  std::stringstream plot;
  plot << path << "\\";
  plot << "plotgen.exe -in " << path << "\\" << "temp\\vol.dds ";
  plot << "-out " << path << "\\" << "temp\\occ_spectrum.bmp ";

  std::cout << plot.str().c_str() << std::endl;

  system(plot.str().c_str());
  
  VolumeManager::i()->RefreshVolumeTexture(load.str().c_str());
}

void UIExtractor::readInput()
{
	long inWidth;
	long inHeight;
	long inDepth;

	long skip;

	long outWidth;
	long outHeight;
	long outDepth;

	long xOff;
	long yOff;
	long zOff;

	m_txtInputWidth->GetValue().ToLong(&inWidth);
	m_txtInputHeight->GetValue().ToLong(&inHeight);
	m_txtInputDepth->GetValue().ToLong(&inDepth);

	m_txtInputHeader->GetValue().ToLong(&skip);

	m_txtOutputWidth->GetValue().ToLong(&outWidth);
	m_txtOutputHeight->GetValue().ToLong(&outHeight);
	m_txtOutputDepth->GetValue().ToLong(&outDepth);

	m_txtXOff->GetValue().ToLong(&xOff);
	m_txtYOff->GetValue().ToLong(&yOff);
	m_txtZOff->GetValue().ToLong(&zOff);

	std::stringstream s;
	s << path << "\\";
	s << "loader.exe ";
	s << "-in " << m_inputVolume.c_str() << " ";
	s << "-out " << m_outputVolume.c_str() << " ";
	s << "-skip " << skip << " ";
  s << "-numBytes " << m_voxelSize << " ";
  if(m_swapBytes == true)
    s << "-swapBytes " << "true" << " ";
  else if(m_swapBytes == false)
    s << "-swapBytes " << "false" << " ";
	s << "-srcX " << inWidth << " ";
	s << "-srcY " << inHeight << " ";
	s << "-srcZ " << inDepth << " ";
	s << "-dstX " << outWidth << " ";
	s << "-dstY " << outHeight << " ";
	s << "-dstZ " << outDepth << " ";
	s << "-offX " << xOff << " ";
	s << "-offY " << yOff << " ";
	s << "-offZ " << zOff << " ";

  std::cout << s.str().c_str() << std::endl;

	system(s.str().c_str());

  std::stringstream hpath;
  hpath << path << "/temp/hist.bmp";

  m_hist.LoadFile(hpath.str().c_str(), wxBITMAP_TYPE_ANY);
  m_bmpVisMapping->SetBitmap(m_hist);

  std::stringstream volume;
  volume << path << m_outputVolume.c_str();
  std::cout << volume.str().c_str() << std::endl;
  VolumeManager::i()->RefreshVolumeTexture(volume.str().c_str());
}

