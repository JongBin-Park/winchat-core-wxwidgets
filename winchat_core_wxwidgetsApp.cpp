/***************************************************************
 * Name:      winchat_core_wxwidgetsApp.cpp
 * Purpose:   Code for Application Class
 * Author:    JongBin. Park (jongbin@devbin.kr)
 * Created:   2020-07-22
 * Copyright: JongBin. Park (devbin.kr)
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "winchat_core_wxwidgetsApp.h"
#include "winchat_core_wxwidgetsMain.h"

IMPLEMENT_APP(winchat_core_wxwidgetsApp);

bool winchat_core_wxwidgetsApp::OnInit()
{
    winchat_core_wxwidgetsFrame* frame = new winchat_core_wxwidgetsFrame(0L);
    frame->SetIcon(wxICON(aaaa)); // To Set App Icon
    frame->Show();
    
    return true;
}
