#include <iostream>
#include "wx/wx.h"
#include "axLib.h"

using namespace std;

enum SLIDER_ID
{
	MOUSE_LEFT_UP = 10000,
	MOUSE_LEFT_DOWN,
	MOUSE_MOTION
};

class MyApp: public wxApp
{
public:
	axSlider* slider;

private:
    virtual bool OnInit();
	
	void OnLeftUp(wxCommandEvent& event);
	void OnLeftDown(wxCommandEvent& event);
	void OnMotion(wxCommandEvent& event);

	DECLARE_EVENT_TABLE()
};

IMPLEMENT_APP(MyApp);


BEGIN_EVENT_TABLE(MyApp, wxApp)
	EVT_BUTTON(MOUSE_LEFT_UP, MyApp::OnLeftUp)
	EVT_BUTTON(MOUSE_LEFT_DOWN, MyApp::OnLeftDown)
	EVT_BUTTON(MOUSE_MOTION, MyApp::OnMotion)
END_EVENT_TABLE()


bool MyApp::OnInit()
{
	// -------------------------------------------------------------------------------------------------
	wxFrame* frame = new wxFrame(NULL, wxID_ANY, wxT("Mainframe"), wxPoint(30, 30), wxSize(400, 400));
	frame->SetBackgroundColour(wxColor(100, 100, 100));
	
	wxPanel* panel = new wxPanel(frame, wxID_ANY, wxPoint(0, 0), wxSize(400, 400));
	panel->SetBackgroundColour(wxColor(150, 150, 150));
	// -------------------------------------------------------------------------------------------------

	axSliderID sliderID;
	sliderID.leftDownID = MOUSE_LEFT_DOWN; 
	sliderID.leftUpID = MOUSE_LEFT_UP;
	sliderID.motionID = MOUSE_MOTION;

	axSliderData sliderData;
	sliderData.imgs = axMultipleBitmap(wxT("sliderCtrl.png"), 3, wxSize(12, 12), UP_TO_DOWN);
	sliderData.bgColorNormal		= wxColor(50, 50, 50); 
	sliderData.bgColorHover			= wxColor(70, 70, 70); 
	sliderData.bgColorClicked		= wxColor(100, 100, 100);
	sliderData.sliderColorNormal	= wxColor(200, 0, 0); 
	sliderData.sliderColorHover		= wxColor(240, 0, 0);
	sliderData.sliderColorClicked	= wxColor(230, 0, 0);
	sliderData.sliderContourColor	= wxColor(0, 0, 0);
	sliderData.contourColor			= wxColor(50, 50, 50);
	sliderData.sliderHeight			= 8;

	slider = new axSlider(panel, sliderID, sliderData, wxPoint(10, 10), wxSize(300, 16), 0.5);

	frame->Show();
	SetTopWindow(frame);

	return true;
}

void MyApp::OnLeftUp(wxCommandEvent& event)
{
	_DEBUG_ DSTREAM << "UP" << endl;
}

void MyApp::OnLeftDown(wxCommandEvent& event)
{
	_DEBUG_ DSTREAM << "DOWN" << endl;
}

void MyApp::OnMotion(wxCommandEvent& event)
{
	_DEBUG_ DSTREAM << "MOTION" << endl;
}

