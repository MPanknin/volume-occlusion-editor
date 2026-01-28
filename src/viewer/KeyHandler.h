#ifndef KeyHandler_h__
#define KeyHandler_h__

#include "osgGA/GUIEventHandler"

#include "RayCastTechnique.h"
#include "VolumeViewer.h"

class KeyHandler : public osgGA::GUIEventHandler
{
public:
  KeyHandler(RayCastTechnique* technique, VolumeViewer* viewer)
  { 
    m_technique = technique;
    m_topView = viewer;
  }
  virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter&);
  virtual void accept(osgGA::GUIEventHandlerVisitor& v)   { v.visit(*this); };
protected:
  RayCastTechnique* m_technique;
  VolumeViewer* m_topView;
};

bool KeyHandler::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa)
{
  switch(ea.getEventType())
  {
    // ======================================================
  case(osgGA::GUIEventAdapter::KEYDOWN):
    {
      switch (ea.getKey())
      {
      case osgGA::GUIEventAdapter::KEY_F1:
        printf("F1 \n");
        m_topView->Refresh();
        return false;
        break;
      default:
        return false;
        break;
      }
      break;
    }
  default:
    return false;
  }
}
#endif // KeyHandler_h__
