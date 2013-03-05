#include "axScrollBar.h"
#include <cmath>
#include "axDebug.h"

BEGIN_EVENT_TABLE(axScrollBar, wxPanel)
	EVT_PAINT(axScrollBar::OnPaint)
	EVT_LEFT_DOWN(axScrollBar::OnMouseLeftDown)
	EVT_MOTION(axScrollBar::OnMouseMotion)
	EVT_LEFT_UP(axScrollBar::OnMouseLeftUp)
	EVT_ENTER_WINDOW(axScrollBar::OnMouseEnter)
	EVT_LEAVE_WINDOW(axScrollBar::OnMouseLeave)
	EVT_BUTTON(wxID_ANY, axScrollBar::OnButtonClick)
END_EVENT_TABLE()

axScrollBar::axScrollBar(wxWindow* win, wxWindowID id, wxPoint pt, const int& height, 
						 axMultipleBitmap* upBitmap, axMultipleBitmap* downBitmap):
						 wxPanel(win, id, pt, wxSize(upBitmap->getImgSize().x, height))
{
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
	m_upBitmap = upBitmap;
	m_downBitmap = downBitmap;

	m_id = id;

	m_upButton = new axButton(this, wxID_ANY, wxPoint(0, 0), *m_upBitmap); 
	m_downButton = new axButton(this, wxID_ANY, wxPoint(0, GetSize().y - m_downBitmap->getImgSize().y),
								*m_downBitmap);

	m_imgHeight = m_upBitmap->getImgSize().y;
	m_sliderMaxHeight = height - 2 * m_imgHeight - 1;
	m_yClickDelta = 0;

	// A CHANGER
	m_inputFrameSize = 100;
	m_inputPanelSize = 800;
	m_inputTopDecay = 0;
	m_value = 0;
	m_sliderValue = 0;

	recalculateInputValue();
}

void axScrollBar::setInputInfo(int frameSize, int panelSize, int topDelta)
{
	m_inputFrameSize = frameSize;
	m_inputPanelSize = panelSize;
	m_inputTopDecay = topDelta;

	recalculateInputValue();
	Refresh();
}

void axScrollBar::setInputTopDelta(int y)
{
	m_inputTopDecay = y;

	recalculateInputValue();
	Refresh();
}

void axScrollBar::setInputFrameHeight(int y)
{
	m_inputFrameSize = y;
	
	recalculateInputValue();
	Refresh();
}

void axScrollBar::setInputPanelHeight(int y)
{
	m_inputPanelSize = y;

	recalculateInputValue();
	Refresh();
}

double axScrollBar::getSliderValue() const
{
	return m_value;
}

//void axScrollBar::setSliderValue(const double& sValue)
//{
//	m_value = sValue;
//
//
//}

inline void axScrollBar::recalculateInputValue()
{
	double diff = double(m_inputPanelSize) - m_inputFrameSize;
	
	if(diff <= 0) 
	{
		m_sliderHeight = m_sliderMaxHeight;
		m_sliderPosition = m_imgHeight;	
		m_sliderValue = 0;
		m_value = 0;
	}
	else
	{  
		m_sliderHeight = (m_inputFrameSize / double(m_inputPanelSize)) * m_sliderMaxHeight;

		m_sliderPosition = m_imgHeight + m_sliderValue * m_sliderMaxHeight;

		if(m_sliderPosition + m_sliderHeight > m_downButton->GetPosition().y - 1)
			m_sliderPosition = m_downButton->GetPosition().y - 1 - m_sliderHeight;

		if(m_sliderPosition < m_imgHeight)
			m_sliderPosition = m_imgHeight;

		m_sliderValue = (m_sliderPosition - m_imgHeight) / (m_sliderMaxHeight);
		
		if(m_sliderHeight < m_sliderMaxHeight)
		{
			double d = (m_sliderPosition - m_imgHeight) / (m_sliderMaxHeight - m_sliderHeight);
			m_value = ceil(d * (m_inputPanelSize - m_inputFrameSize));
		}
		else m_value = 0;
	}
}

void axScrollBar::OnMouseLeftUp(wxMouseEvent& event)
{
	if(HasCapture())
	{
		ReleaseMouse();
	}
}

void axScrollBar::OnMouseLeftDown(wxMouseEvent& event)
{
	if(event.GetY() > m_sliderPosition && event.GetY() < m_sliderPosition + m_sliderHeight)
	{
		CaptureMouse();
		m_yClickDelta = event.GetY() - m_sliderPosition;
	}
}

void axScrollBar::OnMouseMotion(wxMouseEvent& event)
{
	if(HasCapture() && event.LeftIsDown() && m_sliderHeight < m_sliderMaxHeight)
	{
		// m_sliderPosition move with mouse position.
		m_sliderPosition = event.GetY() - m_yClickDelta;

		// If m_sliderPosition reach bottom, clip m_sliderPosition.
		if(m_sliderPosition + m_sliderHeight > m_downButton->GetPosition().y - 1)
			m_sliderPosition = m_downButton->GetPosition().y - 1 - m_sliderHeight;

		// Clip top m_sliderPosition .
		if(m_sliderPosition < m_imgHeight)
			m_sliderPosition = m_imgHeight;

		// Slider position ratio.
		m_sliderValue = (m_sliderPosition - m_imgHeight) / (m_sliderMaxHeight);
	
		double d = (m_sliderPosition - m_imgHeight) / (m_sliderMaxHeight - m_sliderHeight);
		m_value = ceil(d * (m_inputPanelSize - m_inputFrameSize));
	
		Refresh();

		if(m_id != wxID_ANY)
		{
			wxCommandEvent btnEvent(wxEVT_COMMAND_BUTTON_CLICKED, m_id);
			wxPostEvent(this, btnEvent);
		}
	}
	else m_value = 0;
}

void axScrollBar::OnMouseEnter(wxMouseEvent& event)
{
}

void axScrollBar::OnMouseLeave(wxMouseEvent& event)
{
}

void axScrollBar::OnButtonClick(wxCommandEvent& event)
{
	event.Skip();
}

void axScrollBar::setBackgroundImage(wxBitmap& bmp)
{

}

void axScrollBar::OnPaint(wxPaintEvent& event)
{
	wxAutoBufferedPaintDC dc(this);
	wxSize size = this->GetSize();

	dc.SetPen(wxPen(wxColor(0, 0, 0)));

	dc.SetBrush(wxBrush(wxColor(60, 60, 60)));
	dc.DrawRectangle(wxPoint(0, 0), size);

	dc.SetBrush(wxBrush(wxColor(80, 80, 80), wxCROSSDIAG_HATCH));
	dc.DrawRectangle(wxPoint(0, 0), size);

	//dc.SetBrush(wxBrush(wxColor(120, 120, 120)));

	//dc.GradientFillLinear(wxRect(wxPoint(0, m_imgHeight), wxSize(m_imgHeight, 60)), 
	//					    wxColor(120, 120, 120), wxColor(150, 150, 150), wxEAST);

	//dc.SetBrush(wxBrush(*wxTRANSPARENT_BRUSH));
	
	wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
    if (gc)
    {		
		gc->SetPen(wxPen(wxColor(0, 0, 0)));
		gc->SetBrush(wxBrush(wxColor(169, 169, 169)));
		gc->DrawRoundedRectangle(1, m_sliderPosition, m_imgHeight - 3, m_sliderHeight, 3);
	
		delete gc;
	}
	//dc.DrawRoundedRectangle(wxPoint(0, m_imgHeight), wxSize(m_imgHeight, 60), 4);

	//dc.DrawBitmap(m_multiBitmap->getBitmap(0), 0, 0);
}