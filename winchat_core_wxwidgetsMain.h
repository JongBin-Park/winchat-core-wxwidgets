/***************************************************************
 * Name:      winchat_core_wxwidgetsMain.h
 * Purpose:   Defines Application Frame
 * Author:    JongBin. Park (jongbin@devbin.kr)
 * Created:   2020-07-22
 * Copyright: JongBin. Park (devbin.kr)
 * License:
 **************************************************************/

#ifndef WINCHAT_CORE_WXWIDGETSMAIN_H
#define WINCHAT_CORE_WXWIDGETSMAIN_H

#include <wx/wx.h>
#include "common.h"
#include "chat.h"

#include "winchat_core_wxwidgetsApp.h"


#include "GUIFrame.h"

class winchat_core_wxwidgetsFrame: public GUIFrame
{
    public:
        winchat_core_wxwidgetsFrame(wxFrame *frame);
        ~winchat_core_wxwidgetsFrame();

    private:
        Server *svr;
        Client *cnt;

        virtual void OnClose(wxCloseEvent& event);
        virtual void OnQuit(wxCommandEvent& event);
        virtual void OnAbout(wxCommandEvent& event);
        virtual void m_tool4OnToolClicked( wxCommandEvent& event );
		virtual void m_tool5OnToolClicked( wxCommandEvent& event );
		virtual void m_tool6OnToolClicked( wxCommandEvent& event );
};

#endif // WINCHAT_CORE_WXWIDGETSMAIN_H
