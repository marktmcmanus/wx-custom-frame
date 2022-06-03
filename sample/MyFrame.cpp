#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "MyFrame.h"

wxBEGIN_EVENT_TABLE( MyFrame, wx::custom::CustomFrame )
EVT_MENU( wxID_EXIT, MyFrame::OnExit )
EVT_MENU( wxID_ABOUT, MyFrame::OnAbout )
wxEND_EVENT_TABLE()

MyFrame::MyFrame( const wxString& title, const wxPoint& pos, const wxSize& size )
    : wx::custom::CustomFrame()
{
    wx::custom::CustomFrame::Create( NULL, wxID_ANY, title, pos, size );
    SetBackgroundColour( *wxBLACK );
}

wxSizer* MyFrame::GetTitleBar()
{
    wxBoxSizer* titleBarSizer = new wxBoxSizer( wxHORIZONTAL );
    titleBarSizer->Add( 1, GetMatrix().title_bar_height, 1 );
    return titleBarSizer;
}

wxPanel* MyFrame::GetContent()
{
    auto contentPanel = new wxPanel( this );
    contentPanel->SetBackgroundColour( wxColour( 20, 20 , 20 )  );
    return contentPanel;
}

wx::custom::CustomFrameMatrix MyFrame::GetMatrix() const
{
    return m_MyMatrix;
}

void MyFrame::OnExit( wxCommandEvent& event )
{
    Close( true );
}

void MyFrame::OnAbout( wxCommandEvent& event )
{
    wxMessageBox( "This is a wxWidgets' Hello world sample",
        "About Hello World", wxOK | wxICON_INFORMATION );
}
