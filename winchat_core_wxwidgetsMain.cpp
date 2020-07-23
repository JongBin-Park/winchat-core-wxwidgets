/***************************************************************
 * Name:      winchat_core_wxwidgetsMain.cpp
 * Purpose:   Code for Application Frame
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

#include "winchat_core_wxwidgetsMain.h"

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}


winchat_core_wxwidgetsFrame::winchat_core_wxwidgetsFrame(wxFrame *frame)
    : GUIFrame(frame)
{
    statusBar->SetStatusText("Winchat is ready", 0);
    statusBar->SetStatusText("made by jongbin. P", 1);
}

winchat_core_wxwidgetsFrame::~winchat_core_wxwidgetsFrame()
{
}

void winchat_core_wxwidgetsFrame::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void winchat_core_wxwidgetsFrame::OnQuit(wxCommandEvent &event)
{
    Destroy();
}

void winchat_core_wxwidgetsFrame::OnAbout(wxCommandEvent &event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}
