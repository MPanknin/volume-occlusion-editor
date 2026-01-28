#include <osg/ref_ptr>
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>
#include <osgViewer/api/Win32/GraphicsWindowWin32>

#include <wx/filename.h>

#include "UIColorTable.h"
#include "UIContainer.h"
#include "UIDepthBuffer.h"
#include "UIRaw.h"
#include "UIOcclusionGeneration.h"
#include "UIOcclusionSpectrum.h"
#include "UISegY.h"
#include "UISettings.h"

#include "ApplicationPaths.h"
#include "Logger.h"
#include "SegyManager.h"
#include "VolumeInfo.h"
#include "VolumeViewer.h"
#include "Helper.h"
#include "RawManager.h"

//============================================================================
const wxChar* FILES_DDS   = _T("DDS files|*.dds|All files|*.*");
const wxChar* FILES_SEGY  = _T("SEG Y files|*.seg;*.sgy;*.segy|All files|*.*");
const wxChar* FILES_RAW   = _T("RAW files|*.raw;*.vol|All files|*.*");

//============================================================================
UIContainer::UIContainer( wxWindow* parent )
  :
Container( parent )
{
  Logger::SetLogTarget(m_textLogOut);
  
  wxMenuItem* menuOpen = m_menubar1->FindItem(menuItemOpen);
  menuOpen->Enable(false);

  m_topView = 0;
  m_sceneDirty = false;

  m_splitterMain->SetSashPosition(650);
  m_splitterMain->SetSashGravity(0.0f);

  m_topView = new VolumeViewer(this);
  ref_ptr<VolumeInfo> info = new VolumeInfo;
  info->Open(VOL_META_FILE);
  m_topView->Init(info);

  osg::ref_ptr<osg::Image> hist = Helper::CreateLocalHistogram(m_topView->GetVolImage(), 256, 100);
  osgDB::writeImageFile(*hist, HIST_IMAGE);

  OpenWindow(windowSettings);
}
//============================================================================
void UIContainer::OnIdle(wxIdleEvent& event)
{
  if (m_topView == 0 || !m_topView->IsRealized())
  {
    return;
  }
  else
  {
    if(m_sceneDirty == true)
    {
      m_sceneDirty = false;
      m_topView->Init(m_fileToLoad);
      RefreshChildren();
    }
    m_topView->Frame();

    UIDepthBuffer* win = dynamic_cast<UIDepthBuffer*>(FindWindowById(windowDepthBuffer));
    if(win != 0)
    {
      win->ReloadDepthImage();
    }
  }

  event.RequestMore();
}
//============================================================================
void UIContainer::RefreshChildren()
{
  UISettings* win = dynamic_cast<UISettings*>(FindWindowById(windowSettings));
  if(win != 0)
  {
    win->Init();
  }
  UIColorTable* color = dynamic_cast<UIColorTable*>(FindWindowById(windowColorTable));
  if(color != 0)
  {
    color->Init();
  }
  UIOcclusionGeneration* occGen = dynamic_cast<UIOcclusionGeneration*>(FindWindowById(windowOcclusionGeneration));
  if(occGen != 0)
  {
    occGen->Init();
  }
}
//============================================================================
wxWindow* UIContainer::OpenWindow( int id )
{
  wxWindow* win = FindWindowById(id);
  if(win == 0)
  {
    switch (id)
    {
    case windowSettings:
      win = new UISettings(this);
    	break;
    case windowColorTable:
      win = new UIColorTable(this);
      break;
    case windowDepthBuffer:
      win = new UIDepthBuffer(this);
      break;
    case windowImporter:
      win = new UIRaw(this);
      break;
    case windowSegy:
      win = new UISegY(this);
      break;
    case windowOcclusionGeneration:
      win = new UIOcclusionGeneration(this);
      break;
    case windowOcclusionSpectrum:
      win = new UIOcclusionSpectrum(this);
      break;
    default:
      break;
    }
    win->Show();
  }
  return win;
}
//============================================================================
void UIContainer::OnMenu( wxCommandEvent& event )
{
  FS();
  switch(event.GetId())
  {
    // color table editor
  case menuItemColorTable:
    {
      OpenWindow(windowColorTable);
      break;
    }
    // depth buffer window
  case menuItemDepthBuffer:
    {
      OpenWindow(windowDepthBuffer);
      break;
    }
    // occlusion generation window
  case menuItemOcclusionGeneration:
    {
      OpenWindow(windowOcclusionGeneration);
      break;
    }
    // occlusion spectrum window
  case menuItemOcclusionSpectrum:
    {
      OpenWindow(windowOcclusionSpectrum);
      break;
    }

    // raw importer window
  case menuItemImportRaw:
    {
      wxFileDialog fileDialog(this, _("Import RAW file"), "", "", FILES_RAW, wxFD_OPEN);
      if (fileDialog.ShowModal() == wxID_OK)
      {
        UIRaw* importer = dynamic_cast<UIRaw*>(OpenWindow(windowImporter));      
        if (importer != 0)
        {
          importer->SetFileName(fileDialog.GetPath());
        }
      }
      break;
    }
    // export raw dialog
  case menuItemExportRaw:
    {
      wxFileDialog fileDialog(this, _("Export RAW file"), "", "", FILES_RAW, wxFD_SAVE);

      if (fileDialog.ShowModal() == wxID_OK)
      {
        std::string path = fileDialog.GetPath();
        RawManager::Save(m_topView->GetVolImage(), path.c_str());
      }
      break;
    }

    // segy importer window
  case menuItemImportSegY:
    {
      wxFileDialog fileDialog(this, _("Import SEG Y file"), "", "", FILES_SEGY, wxFD_OPEN);
      if (fileDialog.ShowModal() == wxID_OK)
      {
        UISegY* segy = dynamic_cast<UISegY*>(OpenWindow(windowSegy));      
        if (segy != 0)
        {
          segy->SetFileName(fileDialog.GetPath());
        }
      }
      break;
    }

    // open file dialog
  case menuItemExportSegY:
    {
      wxFileDialog fileDialog(this, _("Export SEG Y file"), "", "", FILES_SEGY, wxFD_SAVE);

      if (fileDialog.ShowModal() == wxID_OK)
      {
        std::string path = fileDialog.GetPath();

        SegyManager loader;
        loader.Save(m_topView->GetVolImage(), path.c_str(), m_topView->GetVolInfo());
        loader.Close();
      }
      break;
    }
    // close application
  case menuItemExit:
    this->Close(true);
    break;
  default:
    break;
  }

  FE();
}
