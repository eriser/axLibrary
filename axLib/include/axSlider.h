#ifndef _M_IMAGE_SLIDER_H
#define _M_IMAGE_SLIDER_H

#include "wx/wx.h"
#include "wx/dcbuffer.h"
#include "axMultipleBitmap.h"
#include "Windows.h"
#include "axDebug.h"

struct axSliderID
{
	int leftDownID, leftUpID, motionID;
};

struct axSliderData
{
	axMultipleBitmap imgs;
	wxColor bgColorNormal, bgColorHover, bgColorClicked;
	wxColor sliderColorNormal, sliderColorHover, sliderColorClicked;
	wxColor sliderContourColor, contourColor;
	int sliderHeight;
};

class axSlider : public wxPanel
{
public:
	axSlider(){}
	axSlider(wxWindow* win, 
			 const axSliderID& id,
			 const axSliderData& data,
			 const wxPoint& pt, 
			 const wxSize& size, 
			 double value = 0, 
			 double minValue = 0, 
			 double maxValue = 1);
	~axSlider(){}

    double getValue() const;
	void setBackgroundImage(wxBitmap& bmp);

private:
	void OnPaint(wxPaintEvent& event);
	void OnMouseLeftDown(wxMouseEvent& event);
	void OnMouseLeftUp(wxMouseEvent& event);
	void OnMouseMotion(wxMouseEvent& event);
	void OnMouseEnter(wxMouseEvent& event);
	void OnMouseLeave(wxMouseEvent& event);
	void OnButtonClick(wxCommandEvent& event);

	void blockPosition();

	axSliderData m_data;
	axSliderID m_ID;
	int m_sliderPos, m_imgPos;

	double m_value, m_minValue, m_maxValue;
	wxBitmap m_currentImage, m_bgImage;
	wxColor m_currentBgColor, m_currentSliderColor;

	int deltaClick_x;
	int m_halfImgSize;
	bool m_imgHover;

	DECLARE_EVENT_TABLE()
};

//class SliderBar: public wxPanel
//{
//public:
//	SliderBar(wxWindow* win, wxWindowID winid, wxWindowID winid2, wxWindowID winid3, wxPoint pt, wxSize size, wxString imgPath, 
//			  wxString imgHoverPath = _T(""), wxString imgClickPath = _T(""));
//	//void mSize();
//	void mSize(int x);
//	double getSliderValue();
//	void setSliderValue(double v);
//	void setBackgroundBitamp(wxBitmap bg);
//
//private:
//	wxWindowID id, id2, id3;
//	wxWindow* parent;
//	wxBitmap bmp, bmpHover, bmpClick, bgBmp, currentBmp;
//	bool bgImage;
//	wxColor contour, contourHover, currentContour;
//	bool bHover, bClick, sliderCtrlSelected;//, contourSelected;
//	int sliderPos, deltaClickPos;
//	double sliderValue;
//	static const int SLIDER_LENGHT = 12;
//
//	void limitSliderPosition(int size_x);
//	void OnPaint(wxPaintEvent& event);
//	void OnMouseEnter(wxMouseEvent& event);
//	void OnMouseLeave(wxMouseEvent& event);
//	void OnMouseLeftUp(wxMouseEvent& event);
//	void OnMouseLeftDown(wxMouseEvent& event);
//	void OnMouseMotion(wxMouseEvent& event);
//	void OnClickEvent(wxCommandEvent& event);
//	void OnClickDownEvent(wxCommandEvent& event);
//	void OnClickMotionEvent(wxCommandEvent& event);
//	
//	DECLARE_EVENT_TABLE()
//};

#endif