/***************************************************************
 * Name:      winchat_core_wxwidgetsApp.h
 * Purpose:   Defines Application Class
 * Author:    JongBin. Park (jongbin@devbin.kr)
 * Created:   2020-07-22
 * Copyright: JongBin. Park (devbin.kr)
 * License:
 **************************************************************/

#ifndef WINCHAT_CORE_WXWIDGETSAPP_H
#define WINCHAT_CORE_WXWIDGETSAPP_H

#include <wx/app.h>

class winchat_core_wxwidgetsApp : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // WINCHAT_CORE_WXWIDGETSAPP_H
