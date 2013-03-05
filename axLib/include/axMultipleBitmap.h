#ifndef _M_MULTIPLE_BITMAP_H
#define _M_MULTIPLE_BITMAP_H

#include "wx/wx.h"

enum ImageDirection { UP_TO_DOWN = 0, LEFT_TO_RIGHT };

class axMultipleBitmap
{
public:
	axMultipleBitmap();
	axMultipleBitmap(wxString path, int nImage, wxSize imgSize, ImageDirection direction = UP_TO_DOWN);
	axMultipleBitmap(wxBitmap& bmp, int nImage, wxSize imgSize, ImageDirection direction = UP_TO_DOWN);
	~axMultipleBitmap();

	axMultipleBitmap &axMultipleBitmap::operator= (const axMultipleBitmap &source);

	wxBitmap getBitmap(int nImage) const;

	wxSize getImgSize() const
	{
		return m_imgSize;
	}

	int getNbImg() const
	{
		return m_nImage;
	}

private:
	wxBitmap* m_images;
	int m_nImage;
	wxSize m_imgSize;
};

#endif