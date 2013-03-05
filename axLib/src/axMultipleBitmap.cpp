#include "axMultipleBitmap.h"

axMultipleBitmap::axMultipleBitmap()
{
	m_nImage = 0;
	m_imgSize = wxSize(0, 0);
	m_images = NULL;
}

axMultipleBitmap::axMultipleBitmap(wxString path, int nImage, 
								 wxSize imgSize, ImageDirection direction)
{
	wxImage::AddHandler(new wxPNGHandler);
	wxImage::AddHandler(new wxGIFHandler);

	m_nImage = nImage;
	m_imgSize = imgSize;
	m_images = new wxBitmap[m_nImage];

	wxImage img(path, wxBITMAP_TYPE_PNG);
	//wxImage img(path, wxBITMAP_TYPE_GIF);

	if (direction == UP_TO_DOWN)
		for(int i = 0; i < m_nImage; i++) {
			m_images[i] = wxBitmap(img.GetSubImage(wxRect(wxPoint(0, i * m_imgSize.y), m_imgSize))); 
		}
	else // LEFT_TO_RIGHT
		for(int i = 0; i < m_nImage; i++) {
			m_images[i] = wxBitmap(img.GetSubImage(wxRect(wxPoint(i * m_imgSize.x, 0), m_imgSize))); 
		}
}
axMultipleBitmap::axMultipleBitmap(wxBitmap& bmp, int nImage, wxSize imgSize, ImageDirection direction)
{
	wxImage::AddHandler(new wxPNGHandler);

	m_nImage = nImage;
	m_imgSize = imgSize;
	m_images = new wxBitmap[m_nImage];

	wxImage img = bmp.ConvertToImage();

	if (direction == UP_TO_DOWN)
		for(int i = 0; i < m_nImage; i++) {
			m_images[i] = wxBitmap(img.GetSubImage(wxRect(wxPoint(0, i * m_imgSize.y), m_imgSize))); 
		}
	else // LEFT_TO_RIGHT
		for(int i = 0; i < m_nImage; i++) {
			m_images[i] = wxBitmap(img.GetSubImage(wxRect(wxPoint(i * m_imgSize.x, 0), m_imgSize))); 
		}
}
axMultipleBitmap::~axMultipleBitmap()
{
	if(m_nImage && m_images != NULL)
		delete[] m_images;
}

axMultipleBitmap &axMultipleBitmap::operator=(const axMultipleBitmap &source)
{
	m_nImage = source.m_nImage;
	m_imgSize = source.m_imgSize;

	if(m_images != NULL)
		delete[] m_images;

	m_images = new wxBitmap[m_nImage];
	for(int i = 0; i < m_nImage; i++)
		m_images[i] = source.getBitmap(i);

	return *this;
}

wxBitmap axMultipleBitmap::getBitmap(int nImage) const
{
	return m_images[nImage];
}