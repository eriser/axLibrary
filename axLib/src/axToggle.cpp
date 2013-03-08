#include "axToggle.h"

BEGIN_EVENT_TABLE(axToggle, wxPanel)
	EVT_PAINT(axToggle::OnPaint)
	EVT_LEFT_DOWN(axToggle::OnMouseLeftDown)
	EVT_LEFT_UP(axToggle::OnMouseLeftUp)
	EVT_ENTER_WINDOW(axToggle::OnMouseEnter)
	EVT_LEAVE_WINDOW(axToggle::OnMouseLeave)
	EVT_BUTTON(wxID_ANY, axToggle::OnButtonClick)
END_EVENT_TABLE()

axToggle::axToggle(wxWindow* win, wxWindowID id, wxPoint pt, axMultipleBitmap& multiBitmap, bool toggleVal):
			  wxPanel(win, id, pt)
{
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
	
	m_id = id;

	m_images = multiBitmap;
	SetSize(m_images.getImgSize());

	m_toggleValue = toggleVal;
	if(m_toggleValue)
		 currentImage = m_images.getBitmap(3);
	else currentImage = m_images.getBitmap(0);

	bgColor = GetParent()->GetBackgroundColour();
}

void axToggle::setToggleValue(bool value)
{
    m_toggleValue = value;
	if(m_toggleValue)
		 currentImage = m_images.getBitmap(3);
	else currentImage = m_images.getBitmap(0);
    Refresh();

}

void axToggle::OnMouseLeftUp(wxMouseEvent& event)
{
	if(HasCapture())
	{
		ReleaseMouse();

		if(event.GetX() > 0 && event.GetX() < GetSize().x &&
		   event.GetY() > 0 && event.GetY() < GetSize().y)
		{
			if(m_toggleValue)
			{
				 m_toggleValue = false;
				 currentImage = m_images.getBitmap(1);
			}
			else 
			{
				m_toggleValue = true;
				currentImage = m_images.getBitmap(4);	
			}
		}
		else
		{
			if(m_toggleValue)
				 currentImage = m_images.getBitmap(3);
			else currentImage = m_images.getBitmap(0);
		}

		if(m_id != wxID_ANY)
		{
			wxCommandEvent btnEvent(wxEVT_COMMAND_BUTTON_CLICKED, m_id);
			wxPostEvent(this, btnEvent);
		}
		
		Refresh();
	}
}

void axToggle::OnMouseLeftDown(wxMouseEvent& event)
{
	if(m_toggleValue)
		 currentImage = m_images.getBitmap(5);
	else currentImage = m_images.getBitmap(2);

	CaptureMouse();
	Refresh();
}

void axToggle::OnMouseEnter(wxMouseEvent& event)
{
	if(!HasCapture())
	{
		if(m_toggleValue)
			 currentImage = m_images.getBitmap(4);
		else currentImage = m_images.getBitmap(1);
		Refresh();
	}
}

void axToggle::OnMouseLeave(wxMouseEvent& event)
{
	if(!HasCapture())
	{
		if(m_toggleValue)
			 currentImage = m_images.getBitmap(3);
		else currentImage = m_images.getBitmap(0);
		Refresh();
	}
}

void axToggle::OnButtonClick(wxCommandEvent& event)
{
	event.Skip();
}

void axToggle::setBackgroundImage(wxBitmap& bmp)
{
	m_bgImage = bmp;
	Refresh();
}

void axToggle::OnPaint(wxPaintEvent& event)
{
	wxAutoBufferedPaintDC dc(this);
	wxSize size = this->GetSize();

	if(m_bgImage.IsOk())
		dc.DrawBitmap(m_bgImage, 0, 0);
   
	dc.SetPen(wxPen(bgColor, 1, wxSOLID));
    dc.SetBrush(wxBrush(bgColor));
    dc.DrawRectangle(wxRect(0, 0, size.x, size.y));

	dc.DrawBitmap(currentImage, wxPoint(0, 0));
}