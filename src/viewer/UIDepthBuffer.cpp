#pragma warning( disable : 4100 )

#include <osg/ref_ptr>

#include "UIDepthBuffer.h"
#include "UIContainer.h"

#include "Logger.h"
#include "ApplicationPaths.h"
#include "VolumeViewer.h"

//============================================================================
UIDepthBuffer::UIDepthBuffer( wxWindow* parent )
:
DepthBuffer(parent)
{
  FS();
  Init();
  FE();
}
//============================================================================
void UIDepthBuffer::Init()
{
  FS();
  UIContainer* container = dynamic_cast<UIContainer*>(GetParent());
  if (container != 0)
  {
    m_topView = container->m_topView;
  }

  ReloadDepthImage();

  m_dirty = false;

  FE();
}
//============================================================================
void UIDepthBuffer::OnIdle( wxIdleEvent& event)
{
  if (m_dirty)
  {
    m_dirty = false;
	  if(m_topView)
	  {
	    wxImage depth(DEPTH_IMAGE);
      depth.Rescale(512, 512);
	    m_bitmapDepthBuffer->SetBitmap(depth);
	  }
  }
}
//============================================================================
void UIDepthBuffer::OnPaint( wxPaintEvent& event)
{
}
//============================================================================
void UIDepthBuffer::OnUpdate( wxUpdateUIEvent& event )
{
}
//============================================================================
void UIDepthBuffer::ReloadDepthImage()
{
  m_dirty = true;
}
