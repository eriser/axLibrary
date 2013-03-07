#ifndef _M_IMAGE_TOOGLE_H
#define _M_IMAGE_TOOGLE_H

#include "wx/wx.h"
#include "wx/dcbuffer.h"
#include "axMultipleBitmap.h"
#include "Windows.h"
#include "axDebug.h"

class axToggle : public wxPanel
{
public:
	axToggle(){}
	axToggle(wxWindow* win, wxWindowID id, wxPoint pt, axMultipleBitmap& multiBitmap, bool toggleValue = false);
	~axToggle(){}

	void setBackgroundImage(wxBitmap& bmp);
	bool getToggleValue() const
	{
		return m_toggleValue;
	}

private:
	void OnPaint(wxPaintEvent& event);
	void OnMouseLeftDown(wxMouseEvent& event);
	void OnMouseLeftUp(wxMouseEvent& event);
	void OnMouseEnter(wxMouseEvent& event);
	void OnMouseLeave(wxMouseEvent& event);
	void OnButtonClick(wxCommandEvent& event);

	axMultipleBitmap m_images;
	wxBitmap currentImage, m_bgImage;
	wxWindowID m_id;

	wxColor bgColor;
	
	bool m_toggleValue;

	DECLARE_EVENT_TABLE()
};

#endif