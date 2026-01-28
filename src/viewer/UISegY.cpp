#include <osgDB\WriteFile>

#include <wx\dcclient.h>

#include "UISegY.h"
#include "UIContainer.h"

#include "SegyManager.h"
#include "Helper.h"
#include "VolumeInfo.h"
#include "ApplicationPaths.h"
#include "Logger.h"

UISegY::UISegY( wxWindow* parent )
:
SegY( parent )
{
}
//============================================================================
void UISegY::OnButton( wxCommandEvent& event )
{
  FS();
  switch(event.GetId())
  {
  case buttonLoadSegy:
    {
      SegyManager loader;
      loader.Open(m_staticTextSourceFile->GetLabel());

      // build result volume
      osg::ref_ptr<osg::Image> resImg;
      resImg = loader.GetImage();

      // write subvolume to disc
      Logger::Log("Writing image");
      osgDB::writeImageFile(*resImg, VOL_IMAGE);

      osg::ref_ptr<osg::Image> hist = Helper::CreateLocalHistogram(resImg, 256, 100);
      osgDB::writeImageFile(*hist, HIST_IMAGE);

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

      volInfo->dimX = resImg->s();
      volInfo->dimY = resImg->t();
      volInfo->dimZ = resImg->r();

      volInfo->distX = 1;
      volInfo->distY = 1;
      volInfo->distZ = 1;
        
      volInfo->inlineOffset = loader.GetInlineOffset();
      volInfo->crosslineOffset = loader.GetCrosslineOffset();
      volInfo->timeOffset = loader.GetTimeOffset();

      volInfo->sampleInterval = loader.GetSampleInterval();

      loader.Close();

      UIContainer* container = dynamic_cast<UIContainer*>(GetParent());
      if (container != 0)
      {
        container->m_fileToLoad = volInfo;
        container->m_sceneDirty = true;
        volInfo->Save(VOL_META_FILE);
      }

      break;
    }
  case buttonCancelSegy:
    this->Close(true);
    break;
  default:
    break;
  }
  FE();
}
//============================================================================
void UISegY::SetFileName( const char* filename )
{
  FS();
  m_staticTextSourceFile->SetLabel(filename);

  SegyManager loader;
  loader.Open(m_staticTextSourceFile->GetLabel());
  
  m_textDataType->SetValue("---------");
  m_textSampleInterval->SetValue(wxString::Format(wxT("%.3f"), loader.GetSampleInterval()));
  m_textBytesPerVoxel->SetValue(wxString::Format(wxT("%i"), loader.GetBytesPerVoxel()));
  m_textTraceLength->SetValue(wxString::Format(wxT("%i"), loader.GetTraceLength()));
  m_textSizeOfFile->SetValue(wxString::Format(wxT("%i"), loader.GetFileSize()));
  m_textSizeOfSlice->SetValue(wxString::Format(wxT("%i"), loader.GetSliceSize()));
  m_textSamplesPerTrace->SetValue(wxString::Format(wxT("%i"), loader.GetSamplesPerTrace()));
  m_textNumberTraces->SetValue(wxString::Format(wxT("%i"), loader.GetNumTraces()));
  m_textNumberSlices->SetValue(wxString::Format(wxT("%i"), loader.GetNumSlices()));
  m_textDimensions->SetValue(wxString::Format(wxT("%ix%ix%i"), loader.GetNumTraces() / loader.GetNumSlices(), 
                                                               loader.GetNumSlices(), loader.GetSamplesPerTrace()));

  loader.Close();

  FE();
}