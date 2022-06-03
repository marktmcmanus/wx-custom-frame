#include "../CustomFrame.h"

class MyFrame : public wx::custom::CustomFrame
{
public:
    MyFrame( const wxString& title, const wxPoint& pos, const wxSize& size );

    virtual wxSizer* GetTitleBar() override;
    virtual wxPanel* GetContent() override;
    virtual wx::custom::CustomFrameMatrix GetMatrix() const override;

private:
    void OnExit( wxCommandEvent& event );
    void OnAbout( wxCommandEvent& event );

    wx::custom::CustomFrameMatrix m_MyMatrix{ 34, 4, 10 };

    wxDECLARE_EVENT_TABLE();
};