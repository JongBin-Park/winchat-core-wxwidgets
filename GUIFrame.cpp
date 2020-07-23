///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif //WX_PRECOMP

#include "GUIFrame.h"

///////////////////////////////////////////////////////////////////////////

GUIFrame::GUIFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_MENU ) );

	mbar = new wxMenuBar( 0 );
	fileMenu = new wxMenu();
	wxMenuItem* menuFileQuit;
	menuFileQuit = new wxMenuItem( fileMenu, idMenuQuit, wxString( wxT("&Quit") ) + wxT('\t') + wxT("Alt+F4"), wxT("Quit the application"), wxITEM_NORMAL );
	fileMenu->Append( menuFileQuit );

	mbar->Append( fileMenu, wxT("&File") );

	helpMenu = new wxMenu();
	wxMenuItem* menuHelpAbout;
	menuHelpAbout = new wxMenuItem( helpMenu, idMenuAbout, wxString( wxT("&About") ) + wxT('\t') + wxT("F1"), wxT("Show info about this application"), wxITEM_NORMAL );
	helpMenu->Append( menuHelpAbout );

	mbar->Append( helpMenu, wxT("&Help") );

	this->SetMenuBar( mbar );

	m_toolBar1 = this->CreateToolBar( wxTB_HORIZONTAL, wxID_ANY );
	m_tool4 = m_toolBar1->AddTool( wxID_ANY, wxT("tool"), wxArtProvider::GetBitmap( wxART_GO_HOME, wxART_TOOLBAR ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxT("서버 모드로 실행합니다."), NULL );

	m_toolBar1->AddSeparator();

	m_textCtrl1 = new wxTextCtrl( m_toolBar1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_toolBar1->AddControl( m_textCtrl1 );
	m_tool5 = m_toolBar1->AddTool( wxID_ANY, wxT("tool"), wxArtProvider::GetBitmap( wxART_TICK_MARK, wxART_TOOLBAR ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxT("해당 IP로 접속합니다."), NULL );

	m_tool6 = m_toolBar1->AddTool( wxID_ANY, wxT("tool"), wxArtProvider::GetBitmap( wxART_CROSS_MARK, wxART_TOOLBAR ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxT("연결을 해제합니다."), NULL );

	m_toolBar1->Realize();

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );

	bSizer6->SetMinSize( wxSize( -1,20 ) );
	m_textCtrl3 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrl3->SetBackgroundColour( wxColour( 242, 239, 193 ) );

	bSizer6->Add( m_textCtrl3, 1, wxALL|wxEXPAND, 5 );


	bSizer1->Add( bSizer6, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxHORIZONTAL );

	bSizer8->SetMinSize( wxSize( -1,20 ) );
	m_textCtrl41 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer8->Add( m_textCtrl41, 0, wxALL, 5 );

	m_textCtrl4 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrl4->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );
	m_textCtrl4->SetForegroundColour( wxColour( 0, 0, 0 ) );
	m_textCtrl4->SetBackgroundColour( wxColour( 191, 221, 251 ) );

	bSizer8->Add( m_textCtrl4, 1, wxALL|wxEXPAND, 5 );


	bSizer1->Add( bSizer8, 0, wxEXPAND, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();
	statusBar = this->CreateStatusBar( 2, wxSTB_SIZEGRIP, wxID_ANY );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	fileMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnQuit ), this, menuFileQuit->GetId());
	helpMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnAbout ), this, menuHelpAbout->GetId());
	this->Connect( m_tool4->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::m_tool4OnToolClicked ) );
	this->Connect( m_tool5->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::m_tool5OnToolClicked ) );
	this->Connect( m_tool6->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::m_tool6OnToolClicked ) );
}

GUIFrame::~GUIFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	this->Disconnect( m_tool4->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::m_tool4OnToolClicked ) );
	this->Disconnect( m_tool5->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::m_tool5OnToolClicked ) );
	this->Disconnect( m_tool6->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::m_tool6OnToolClicked ) );

}
