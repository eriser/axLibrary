#include "axSlider.h"

BEGIN_EVENT_TABLE(axSlider, wxPanel)
	EVT_PAINT(axSlider::OnPaint)
	EVT_LEFT_DOWN(axSlider::OnMouseLeftDown)
	EVT_LEFT_UP(axSlider::OnMouseLeftUp)
	EVT_MOTION(axSlider::OnMouseMotion)
	EVT_ENTER_WINDOW(axSlider::OnMouseEnter)
	EVT_LEAVE_WINDOW(axSlider::OnMouseLeave)
	EVT_BUTTON(wxID_ANY, axSlider::OnButtonClick)
END_EVENT_TABLE()

axSlider::axSlider(wxWindow* win, const axSliderID& id, const axSliderData& data, const wxPoint& pt, const wxSize& size, 
				   double value, double minValue, double maxValue)
		 : wxPanel(win, wxID_ANY, pt, size)
{
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);

	m_ID = id;
	m_data = data;
	m_value = value;
	m_minValue = minValue;
	m_maxValue = maxValue;

	m_currentImage = m_data.imgs.getBitmap(0);
	m_currentBgColor = m_data.bgColorNormal;
	m_currentSliderColor = m_data.sliderColorNormal;

	m_halfImgSize =  m_data.imgs.getImgSize().x * 0.5;
	m_sliderPos = size.x * m_value + m_halfImgSize;
	m_imgPos = m_sliderPos - m_halfImgSize;

	m_imgHover = false;

}

void axSlider::OnMouseLeftUp(wxMouseEvent& event)
{
	if(HasCapture())
	{
		ReleaseMouse();

		if(IsMouseInWindow())
		{
			m_currentImage = m_data.imgs.getBitmap(2);
			m_currentSliderColor = m_data.sliderColorHover;
			m_currentBgColor = m_data.bgColorHover;
		}
		else
		{
			m_currentImage = m_data.imgs.getBitmap(0);
			m_currentSliderColor = m_data.sliderColorNormal;
			m_currentBgColor = m_data.bgColorNormal;
		}

		Refresh();

		if(m_ID.leftUpID)
		{
			wxCommandEvent btnEvent(wxEVT_COMMAND_BUTTON_CLICKED, m_ID.leftUpID);
			wxPostEvent(this, btnEvent);
		}
	}
}

void axSlider::OnMouseLeftDown(wxMouseEvent& event)
{
	int x = event.GetX();

	if(x >= m_sliderPos - m_halfImgSize && x <= m_sliderPos + m_halfImgSize)
	{
		deltaClick_x = x - m_sliderPos;

		m_currentImage = m_data.imgs.getBitmap(2);
		m_currentSliderColor = m_data.sliderColorClicked;
		m_currentBgColor = m_data.bgColorClicked;
		
		CaptureMouse();
		Refresh();

		// Send event
		if(m_ID.leftDownID)
		{
			wxCommandEvent btnEvent(wxEVT_COMMAND_BUTTON_CLICKED, m_ID.leftDownID);
			wxPostEvent(this, btnEvent);
		}
	}
}

void axSlider::OnMouseMotion(wxMouseEvent& event)
{
	int x = event.GetX();
	if(event.Dragging() && HasCapture() && event.LeftIsDown())
	{
		m_sliderPos = x - deltaClick_x;
		m_imgPos = m_sliderPos - m_data.imgs.getImgSize().x * 0.5;
		
		m_currentImage = m_data.imgs.getBitmap(2);
		m_currentSliderColor = m_data.sliderColorClicked;
		m_currentBgColor = m_data.bgColorClicked;

		blockPosition();

		m_value = (m_sliderPos - m_halfImgSize) / double(GetSize().x - 2.0 * m_halfImgSize);

		//_DEBUG_ DSTREAM << "Value : " << m_value << endl;
		
		Refresh();

		if(m_ID.motionID)
		{
			wxCommandEvent btnEvent(wxEVT_COMMAND_BUTTON_CLICKED, m_ID.motionID);
			wxPostEvent(this, btnEvent);
		}
	}

	else if(x >= m_sliderPos - m_halfImgSize && x <= m_sliderPos + m_halfImgSize)
	{
		m_currentImage = m_data.imgs.getBitmap(1);
		m_imgHover = true;
		Refresh();
	}

	else if(m_imgHover)
	{
		m_currentImage = m_data.imgs.getBitmap(0);
		Refresh();
	}
}

void axSlider::OnMouseEnter(wxMouseEvent& event)
{
	m_currentSliderColor = m_data.sliderColorHover;
	m_currentBgColor = m_data.bgColorHover;
	Refresh();
}

void axSlider::OnMouseLeave(wxMouseEvent& event)
{
	if(!HasCapture())
	{
		m_currentImage = m_data.imgs.getBitmap(0);
		m_currentSliderColor = m_data.sliderColorNormal;
		m_currentBgColor = m_data.bgColorNormal;
		Refresh();
	}
}

void axSlider::OnButtonClick(wxCommandEvent& event)
{
	event.Skip();
}

void axSlider::setBackgroundImage(wxBitmap& bmp)
{

}
void axSlider::blockPosition()
{
	int x = GetSize().x;
	if(m_sliderPos < m_minValue * x + m_halfImgSize)
	{
		m_sliderPos = m_minValue * x + m_halfImgSize;
		m_imgPos = m_sliderPos - m_data.imgs.getImgSize().x * 0.5;
	}

	if(m_sliderPos > m_maxValue * x - m_halfImgSize)
	{
		m_sliderPos = m_maxValue * x - m_halfImgSize;
		m_imgPos = m_sliderPos - m_data.imgs.getImgSize().x * 0.5;
	}
}
void axSlider::OnPaint(wxPaintEvent& event)
{
	wxAutoBufferedPaintDC dc(this);
	wxSize size = this->GetSize();

	// Background
	dc.SetPen(wxPen(m_data.contourColor, 1, wxSOLID));
	dc.SetBrush(wxBrush(m_currentBgColor));
	dc.DrawRectangle(wxRect(0, 0, size.x, size.y));

	if(m_bgImage.IsOk()) dc.DrawBitmap(m_bgImage, 0, 0);

	// Slider
	dc.SetPen(wxPen(m_data.sliderContourColor, 1, wxSOLID));
	dc.SetBrush(wxBrush(m_currentSliderColor));

	int y = (size.y - m_data.sliderHeight) * 0.5;
	dc.DrawRectangle(wxRect(0, y, m_sliderPos, m_data.sliderHeight));

	y = (size.y -  m_data.imgs.getImgSize().y) * 0.5;
	dc.DrawBitmap(m_currentImage, m_imgPos, y);
}