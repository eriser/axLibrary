#ifndef _M_IMAGE_BUTTON_H
#define _M_IMAGE_BUTTON_H

#include "wx/wx.h"
#include "wx/dcbuffer.h"
#include "axMultipleBitmap.h"
#include "Windows.h"
#include "axDebug.h"

class axButton : public wxPanel
{
public:
	axButton(){}
	axButton(wxWindow* win, wxWindowID id, wxPoint pt, axMultipleBitmap& multiBitmap);
	~axButton(){}

	void setBackgroundImage(wxBitmap& bmp);

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

	DECLARE_EVENT_TABLE()
};

#endif