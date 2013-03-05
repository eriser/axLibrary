#ifndef _AX_SCROLL_BAR_H_
#define _AX_SCROLL_BAR_H_

#include "wx/wx.h"
#include "wx/dcbuffer.h"
#include "wx/graphics.h"

#include "axDebug.h"
#include "axMultipleBitmap.h"
#include "axButton.h"
#include "Windows.h"


class axScrollBar : public wxPanel
{
public:
	axScrollBar(){}
	axScrollBar(wxWindow* win, wxWindowID id, wxPoint pt, const int& height, 
				axMultipleBitmap* upBitmap, axMultipleBitmap* downBitmap);
	~axScrollBar(){}

	void setBackgroundImage(wxBitmap& bmp);
	void setInputTopDelta(int y);
	void setInputFrameHeight(int y);
	void setInputPanelHeight(int y);
	void setInputInfo(int frameSize, int panelSize, int topDelta);
	double getSliderValue() const;
	inline void recalculateInputValue();

private:
	void OnPaint(wxPaintEvent& event);
	void OnMouseLeftDown(wxMouseEvent& event);
	void OnMouseMotion(wxMouseEvent& event);
	void OnMouseLeftUp(wxMouseEvent& event);
	void OnMouseEnter(wxMouseEvent& event);
	void OnMouseLeave(wxMouseEvent& event);
	void OnButtonClick(wxCommandEvent& event);

	axMultipleBitmap *m_upBitmap, *m_downBitmap;
	wxBitmap currentImage, m_bgImage;
	wxWindowID m_id;

	axButton *m_upButton, *m_downButton;

	int m_imgHeight, m_sliderHeight, m_sliderMaxHeight;
	int m_inputFrameSize, m_inputPanelSize, m_inputTopDecay;
	int m_yClickDelta;
	
	double m_value;
	double m_sliderPosition, m_sliderValue;
	int m_sliderPositionPixel;

	DECLARE_EVENT_TABLE()
};

#endif