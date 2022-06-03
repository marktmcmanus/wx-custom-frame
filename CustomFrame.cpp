#include "CustomFrame.h"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

bool wx::custom::CustomFrame::Create( 
	wxWindow* parent,
	wxWindowID id,
	const wxString &title,
	const wxPoint &pos,
	const wxSize &size,
	long style,
	const wxString &name )
{
	bool ret = wxFrame::Create( parent, id, title, pos, size, style, name );

	if ( ret )
	{
		wxBoxSizer* mainSizer = new wxBoxSizer( wxVERTICAL );
		mainSizer->AddSpacer( this->GetMatrix().border_thickness );
		mainSizer->Add( GetTitleBar(), 0, wxEXPAND );
		mainSizer->Add( GetContent(), 1, wxEXPAND | wxLEFT | wxBOTTOM | wxRIGHT, GetMatrix().border_thickness );

		SetSizer( mainSizer );
		Layout();
	}

	return ret;
}

WXLRESULT wx::custom::CustomFrame::MSWWindowProc( WXUINT message, WXWPARAM wParam, WXLPARAM lParam )
{
	switch ( message )
	{
		case WM_NCCALCSIZE:
		{
			return 0;
			break;
		}
		case WM_NCLBUTTONDOWN:
		{
			if( NCLeftButtonDown( wParam, lParam ) )
			{ 
				return 0; 
			}

			break;
		}
		case WM_NCLBUTTONUP:
		{
			if ( NCLeftButtonUp( wParam, lParam ) )
			{
				return 0;
			}

			break;
		}
		case WM_NCLBUTTONDBLCLK:
		{
			if ( NCLeftButtonDoubleClick( wParam, lParam ) )
			{
				return 0;
			}

			break;
		}
		case WM_NCMOUSELEAVE:
		{
			if ( NCMouseLeave() )
			{
				return 0;
			}

			break;
		}
		case WM_NCMOUSEHOVER:
		{
			if ( NCMouseHover( wParam, lParam ) )
			{
				return 0;
			}

			break;
		}
		case WM_NCMOUSEMOVE:
		{
			if ( NCMouseMove( wParam, lParam ) )
			{
				return 0;
			}

			break;
		}
		case WM_NCHITTEST:
		{
			return HitTestNCA();
			break;
		}
	}
	return wxFrame::MSWWindowProc( message, wParam, lParam );
}

WXLRESULT wx::custom::CustomFrame::HitTestNCA()
{
	wxPoint mousePos = wxGetMousePosition();
	wxRect windowRect = GetRect();

	WXLRESULT result = HTNOWHERE;

	if ( InTopBorder( windowRect, mousePos ) )
	{
		if ( NearLeftBorder( windowRect, mousePos ) )
			result = HTTOPLEFT;
		else if ( NearRightBorder( windowRect, mousePos ) )
			result = HTTOPRIGHT;
		else
			result = HTTOP;
	}
	else if ( InBottomBorder( windowRect, mousePos ) )
	{
		if ( NearLeftBorder( windowRect, mousePos ) )
			result = HTBOTTOMLEFT;
		else if ( NearRightBorder( windowRect, mousePos ) )
			result = HTBOTTOMRIGHT;
		else
			result = HTBOTTOM;
	}
	else if ( InLeftBorder( windowRect, mousePos ) )
	{
		if ( NearTopBorder( windowRect, mousePos ) )
			result = HTTOPLEFT;
		else if ( NearBottomBorder( windowRect, mousePos ) )
			result = HTBOTTOMLEFT;
		else
			result = HTLEFT;
	}
	else if ( InRightBorder( windowRect, mousePos ) )
	{
		if ( NearTopBorder( windowRect, mousePos ) )
			result = HTTOPRIGHT;
		else if ( NearBottomBorder( windowRect, mousePos ) )
			result = HTBOTTOMRIGHT;
		else
			result = HTRIGHT;
	}
	else if ( mousePos.y >= windowRect.GetTop() && mousePos.y <= windowRect.GetTop() + GetMatrix().title_bar_height + GetMatrix().border_thickness )
	{
		result = HTCAPTION;
	}


	return result;
}

void wx::custom::CustomFrame::OnCloseButton( wxCommandEvent& event )
{
	Close();
}

bool wx::custom::CustomFrame::InTopBorder( const wxRect& windowRect, const wxPoint& mousePos ) const
{
	return mousePos.y >= windowRect.GetTop() && 
		mousePos.y < windowRect.GetTop() + GetMatrix().border_thickness;
}

bool wx::custom::CustomFrame::InBottomBorder( const wxRect& windowRect, const wxPoint& mousePos ) const
{
	return mousePos.y < windowRect.GetBottom() && 
		mousePos.y >= windowRect.GetBottom() - GetMatrix().border_thickness;
}

bool wx::custom::CustomFrame::InLeftBorder( const wxRect& windowRect, const wxPoint& mousePos ) const
{
	return mousePos.x >= windowRect.GetLeft() &&
		mousePos.x < windowRect.GetLeft() + GetMatrix().border_thickness;
}

bool wx::custom::CustomFrame::InRightBorder( const wxRect& windowRect, const wxPoint& mousePos ) const
{
	return mousePos.x < windowRect.GetRight() && 
		mousePos.x >= windowRect.GetRight() - GetMatrix().border_thickness;
}

bool wx::custom::CustomFrame::NearTopBorder( const wxRect& windowRect, const wxPoint& mousePos ) const
{
	return mousePos.y >= windowRect.GetTop() && 
		mousePos.y < windowRect.GetTop() + GetMatrix().corner_offset;
}

bool wx::custom::CustomFrame::NearBottomBorder( const wxRect& windowRect, const wxPoint& mousePos ) const
{
	return mousePos.y < windowRect.GetBottom() && 
		mousePos.y >= windowRect.GetBottom() - GetMatrix().corner_offset;
}

bool wx::custom::CustomFrame::NearLeftBorder( const wxRect& windowRect, const wxPoint& mousePos ) const
{
	return mousePos.x >= windowRect.GetLeft() && 
		mousePos.x < windowRect.GetLeft() + GetMatrix().corner_offset;
}

bool wx::custom::CustomFrame::NearRightBorder( const wxRect& windowRect, const wxPoint& mousePos ) const
{
	return mousePos.x < windowRect.GetRight() && 
		mousePos.x >= windowRect.GetRight() - GetMatrix().corner_offset;
}

