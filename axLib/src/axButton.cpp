#include "axButton.h"

BEGIN_EVENT_TABLE(axButton, wxPanel)
	EVT_PAINT(axButton::OnPaint)
	EVT_LEFT_DOWN(axButton::OnMouseLeftDown)
	EVT_LEFT_UP(axButton::OnMouseLeftUp)
	EVT_ENTER_WINDOW(axButton::OnMouseEnter)
	EVT_LEAVE_WINDOW(axButton::OnMouseLeave)
	EVT_BUTTON(wxID_ANY, axButton::OnButtonClick)
END_EVENT_TABLE()

axButton::axButton(wxWindow* win, wxWindowID id, wxPoint pt, axMultipleBitmap& multiBitmap):
			  wxPanel(win, id, pt)
{
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
	
	m_id = id;

	m_images = multiBitmap;
	SetSize(m_images.getImgSize());

	currentImage = m_images.getBitmap(0);

	bgColor = GetParent()->GetBackgroundColour();
}

void axButton::OnMouseLeftUp(wxMouseEvent& event)
{
	if(HasCapture())
	{
		ReleaseMouse();

		if(event.GetX() > 0 && event.GetX() < GetSize().x &&
		   event.GetY() > 0 && event.GetY() < GetSize().y)
			currentImage = m_images.getBitmap(1);
		else
			currentImage = m_images.getBitmap(0);

		if(m_id != wxID_ANY)
		{
			wxCommandEvent btnEvent(wxEVT_COMMAND_BUTTON_CLICKED, m_id);
			wxPostEvent(this, btnEvent);
		}
		
		Refresh();
	}
}

void axButton::OnMouseLeftDown(wxMouseEvent& event)
{
	currentImage = m_images.getBitmap(2);
	CaptureMouse();
	Refresh();
}

void axButton::OnMouseEnter(wxMouseEvent& event)
{
	if(!HasCapture())
	{
		currentImage = m_images.getBitmap(1);
		Refresh();
	}
}

void axButton::OnMouseLeave(wxMouseEvent& event)
{
	if(!HasCapture())
	{
		currentImage = m_images.getBitmap(0);
		Refresh();
	}
}

void axButton::OnButtonClick(wxCommandEvent& event)
{
	event.Skip();
}

void axButton::setBackgroundImage(wxBitmap& bmp)
{
	m_bgImage = bmp;
	Refresh();
}

void axButton::OnPaint(wxPaintEvent& event)
{
	wxAutoBufferedPaintDC dc(this);
	wxSize size = this->GetSize();

	if(m_bgImage.IsOk())
		dc.DrawBitmap(m_bgImage, 0, 0);
    
	dc.SetPen(wxPen(wxColor(0, 0, 0), 1, wxSOLID));
    dc.SetBrush(wxBrush(bgColor));
    dc.DrawRectangle(wxRect(0, 0, size.x, size.y));


	dc.DrawBitmap(currentImage, wxPoint(0, 0));
}