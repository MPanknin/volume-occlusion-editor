#include <osgDB/WriteFile>

#include "UIRaw.h"
#include "UIContainer.h"

#include "RawManager.h"
#include "Helper.h"
#include "Logger.h"
#include "ApplicationPaths.h"
#include "VolumeInfo.h"

UIRaw::UIRaw( wxWindow* parent )
:
Importer( parent )
{
  bool active = false;
  m_spinCtrlSubX->Enable(active);
  m_spinCtrlSubY->Enable(active);
  m_spinCtrlSubZ->Enable(active);
  m_spinCtrlOffX->Enable(active);
  m_spinCtrlOffY->Enable(active);
  m_spinCtrlOffZ->Enable(active);
  // --
  m_staticTextSubX->Enable(active);
  m_staticTextSubY->Enable(active);
  m_staticTextSubZ->Enable(active);
  m_staticTextOffX->Enable(active);
  m_staticTextOffY->Enable(active);
  m_staticTextOffZ->Enable(active);

  //
  m_spinCtrlSpaceX->SetValue(1);
  m_spinCtrlSpaceY->SetValue(1);
  m_spinCtrlSpaceZ->SetValue(1);
}
//============================================================================
void UIRaw::OnComboBox( wxCommandEvent& event )
{
  switch(event.GetId())
  {
  case comboBoxDataType:
    break;
  case comboBoxByteOrder:
    break;
  default:
    break;
  }
}
//============================================================================
void UIRaw::OnSpinCtrl( wxSpinEvent& event )
{
  switch(event.GetId())
  {
    // header bytes
  case spinCtrlHeaderSkip:
    break;

    // dimensions
  case spinCtrlDimX:
    break;
  case spinCtrlDimY:
    break;
  case spinCtrlDimZ:
    break;

    // spacing
  case spinCtrlSpaceX:
    break;
  case spinCtrlSpaceY:
    break;
  case spinCtrlSpaceZ:
    break;

    // subvolume
  case spinCtrlSubX:
    break;
  case spinCtrlSubY:
    break;
  case spinCtrlSubZ:
    break;

    // offset
  case spinCtrlOffX:
    break;
  case spinCtrlOffY:
    break;
  case spinCtrlOffZ:
    break;

  default:
    break;
  }
}
//============================================================================
void UIRaw::OnSetFocus( wxFocusEvent& event )
{
  wxSpinCtrl* spin = dynamic_cast<wxSpinCtrl*>(FindWindowById(event.GetId()));
  if (spin != 0)
  {
    spin->SetSelection(-1, -1);
  }
}
//============================================================================
void UIRaw::OnCheckBox( wxCommandEvent& event )
{
  switch(event.GetId())
  {
  case checkBoxExtractSubVolume:
    {
      printf("CheckBox checkBoxExtractSubVolume \n");
      bool active = event.IsChecked();
      m_spinCtrlSubX->Enable(active);
      m_spinCtrlSubY->Enable(active);
      m_spinCtrlSubZ->Enable(active);
      m_spinCtrlOffX->Enable(active);
      m_spinCtrlOffY->Enable(active);
      m_spinCtrlOffZ->Enable(active);
      // --
      m_staticTextSubX->Enable(active);
      m_staticTextSubY->Enable(active);
      m_staticTextSubZ->Enable(active);
      m_staticTextOffX->Enable(active);
      m_staticTextOffY->Enable(active);
      m_staticTextOffZ->Enable(active);
      break;
    }
  default:
    break;
  }
}
//============================================================================
void UIRaw::OnButton( wxCommandEvent& event )
{
  switch(event.GetId())
  {
  case buttonLoadRaw:
    LoadRawFile();
    break;
  case buttonCancelRaw:
    this->Close(true);
    break;
  default:
    break;
  }
}
//============================================================================
void UIRaw::SetFileName(const char* filename)
{
  m_staticTextSourceFile->SetLabel(filename);
  wxString path(filename);
  int start = 0;

  start = path.find("_", 0);
  Logger::Log("start", start);

}
//============================================================================
void UIRaw::LoadRawFile()
{
  // tmp variables
  int inX, inY, inZ;
  float spX, spY, spZ;
  int outX, outY, outZ;
  int offX, offY, offZ;
  
  // parse gui inputs
  int skip = m_spinCtrlHeaderSkip->GetValue();
  bool sub = m_checkBoxExtractSubVolume->IsChecked();

  wxString path = m_staticTextSourceFile->GetLabel();
  wxString dataType = m_comboBoxDataType->GetValue();
  wxString byteOrder = m_comboBoxByteOrder->GetValue();
  
  int voxelSize = 0;

  inX = m_spinCtrlDimX->GetValue();
  inY = m_spinCtrlDimY->GetValue();
  inZ = m_spinCtrlDimZ->GetValue();

  spX = m_spinCtrlSpaceX->GetValue();
  spY = m_spinCtrlSpaceY->GetValue();
  spZ = m_spinCtrlSpaceZ->GetValue();

  Logger::Log("-------------------");
  Logger::Log("%f %f %f \n", spX, spY, spZ);
  Logger::Log("-------------------");

  // extract subvolume checkbox?
  if(!sub)
  {
    outX = inX;
    outY = inY;
    outZ = inZ;

    offX = offY = offZ = 0;
  }
  else
  {
    outX = m_spinCtrlSubX->GetValue();
    outY = m_spinCtrlSubY->GetValue();
    outZ = m_spinCtrlSubZ->GetValue();

    offX = m_spinCtrlOffX->GetValue();
    offY = m_spinCtrlOffY->GetValue();
    offZ = m_spinCtrlOffZ->GetValue();
  }
  // get data type
  if(dataType.IsSameAs("Unsigned Byte"))
  {
    voxelSize = 1;
  }
  else if(dataType.IsSameAs("Unsigned Short"))
  {
    voxelSize = 2;
  }

  // load raw file with given entered parameters
  osg::ref_ptr<osg::Image> resImg = RawManager::LoadRawFile(path, skip, voxelSize,
                                                           inX, inY, inZ, 
                                                           outX, outY, outZ, 
                                                           offX, offY, offZ); 

  // check result
  if(resImg == 0)
  {
    Logger::Log("Could not load raw file");
    return;
  }

  // write to disc
  osgDB::writeImageFile(*resImg, VOL_IMAGE);

  // create intensity histogram
  osg::ref_ptr<osg::Image> hist = Helper::CreateLocalHistogram(resImg, 256, 100);
  osgDB::writeImageFile(*hist, HIST_IMAGE);

  // update current volume file
  osg::ref_ptr<VolumeInfo> volInfo = new VolumeInfo;
  volInfo->file = VOL_IMAGE;

  // number of bytes per component
  switch (resImg->getDataType())
  {
  case GL_UNSIGNED_BYTE: 
    volInfo->numBytes = 1;	
    break;
  case GL_UNSIGNED_SHORT: 
    volInfo->numBytes = 2;	
    break;
  }

  volInfo->dimX = outX;
  volInfo->dimY = outY;
  volInfo->dimZ = outZ;

  volInfo->distX = spX;
  volInfo->distY = spY;
  volInfo->distZ = spZ;

  volInfo->inlineOffset = offY;
  volInfo->crosslineOffset = offX;
  volInfo->timeOffset = offZ;

  // no sampling interval information in raw format
  volInfo->sampleInterval = 1;

  UIContainer* container = dynamic_cast<UIContainer*>(GetParent());
  if (container != 0)
  {
    // set new file
    container->m_fileToLoad = volInfo;
    // set scene dirty
    container->m_sceneDirty = true;
    volInfo->Print();
    volInfo->Save(VOL_META_FILE);
  }
}

