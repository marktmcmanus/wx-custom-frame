#pragma once

#include <wx/frame.h>
#include <wx/panel.h>

namespace wx
{
namespace custom
{
struct CustomFrameMatrix
{
	int title_bar_height;
	int border_thickness;
	int corner_offset;
};

class CustomFrame : public wxFrame
{
public:
	CustomFrame() = default;
	virtual ~CustomFrame() = default;

	bool Create( wxWindow* parent,
		wxWindowID id,
		const wxString& title,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxDEFAULT_FRAME_STYLE,
		const wxString& name = wxFrameNameStr );

	virtual WXLRESULT MSWWindowProc( WXUINT message, WXWPARAM wParam, WXLPARAM lParam ) override;
	virtual WXLRESULT HitTestNCA();

	virtual wxSizer* GetTitleBar() = 0;
	virtual wxPanel* GetContent() = 0;
	virtual CustomFrameMatrix GetMatrix() const = 0;

protected:
	virtual bool NCLeftButtonDown( WXWPARAM wParam, WXLPARAM lParam ) { return false; }
	virtual bool NCLeftButtonUp( WXWPARAM wParam, WXLPARAM lParam ) { return false; }
	virtual bool NCLeftButtonDoubleClick( WXWPARAM wParam, WXLPARAM lParam ) { return false; }
	virtual bool NCMouseLeave() { return false; }
	virtual bool NCMouseHover( WXWPARAM wParam, WXLPARAM lParam ) { return false; }
	virtual bool NCMouseMove( WXWPARAM wParam, WXLPARAM lParam ) { return false; }


private:
	void OnCloseButton( wxCommandEvent& event );

	
	bool InTopBorder( const wxRect& windowRect, const wxPoint& mousePos ) const;
	bool InBottomBorder( const wxRect& windowRect, const wxPoint& mousePos ) const;
	bool InLeftBorder( const wxRect& windowRect, const wxPoint& mousePos ) const;
	bool InRightBorder( const wxRect& windowRect, const wxPoint& mousePos ) const;

	bool NearTopBorder( const wxRect& windowRect, const wxPoint& mousePos ) const;
	bool NearBottomBorder( const wxRect& windowRect, const wxPoint& mousePos ) const;
	bool NearLeftBorder( const wxRect& windowRect, const wxPoint& mousePos ) const;
	bool NearRightBorder( const wxRect& windowRect, const wxPoint& mousePos ) const;
};
}
}