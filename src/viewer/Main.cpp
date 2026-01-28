//#include "wx/wxprec.h"
//#ifndef WX_PRECOMP
//#include "wx/wx.h"
//#endif
//
////=========================================================================================
//// resources
//#if !defined(__WXMSW__) && !defined(__WXPM__)
//#include "../sample.xpm"
//#endif
//#include <osgViewer/Viewer>
//
//#include "UIColorTable.h"
//#include "UIContainer.h"
//#include "UIRaw.h"
//#include "UIOcclusionGeneration.h"
//#include "UISegY.h"
//#include "UISettings.h"
//
////=========================================================================================
//// base app
//class MainApplication : public wxApp
//{
//public:
//  virtual bool OnInit();
//};
////=========================================================================================
//IMPLEMENT_APP_CONSOLE(MainApplication)
////=========================================================================================
//// entry point
//bool MainApplication::OnInit()
//{
//  if (!wxApp::OnInit())
//    return false;
//
//  UIContainer* container = new UIContainer(0);
//  container->Show(true);
//  container->Maximize(true);
//
//  SetTopWindow(container);
//  SetWindowPos(GetConsoleWindow(), HWND_TOPMOST, 1, 1, 0, 0, SWP_NOMOVE | SWP_NOSIZE | WS_EX_TOPMOST);
//
//  return true;
//}
//
