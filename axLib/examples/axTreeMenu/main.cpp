#include <iostream>
#include "wx/wx.h"
#include "axLib.h"

using namespace std;

class MyApp: public wxApp
{
public:
	axTreeMenu* menu;

private:
    virtual bool OnInit();
	
	void OnButtonTest(wxCommandEvent& event);

	DECLARE_EVENT_TABLE()
};

IMPLEMENT_APP(MyApp);

#define ID_BUTTON_TEST	(8000)
#define ID_UI			(8001)
#define ID_PANEL		(8002)
#define ID_M_TREE_MENU  (8003) // ID 8003 to 8030 are reserved to axTreeMenu

BEGIN_EVENT_TABLE(MyApp, wxApp)
	EVT_BUTTON(ID_BUTTON_TEST, MyApp::OnButtonTest)
END_EVENT_TABLE()

void MyApp::OnButtonTest(wxCommandEvent& event)
{

}

bool MyApp::OnInit()
{
	// -------------------------------------------------------------------------------------------------
	wxFrame* frame = new wxFrame(NULL, wxID_ANY, wxT("Mainframe"), wxPoint(30, 30), wxSize(400, 400));
	frame->SetBackgroundColour(wxColor(100, 100, 100));
	
	wxPanel* panel = new wxPanel(frame, wxID_ANY, wxPoint(0, 0), wxSize(400, 400));
	panel->SetBackgroundColour(wxColor(150, 150, 150));
	// -------------------------------------------------------------------------------------------------

	axMultipleBitmap scrollBarImg(wxT("scrollSmall.png"), 2, wxSize(11, 33));

	wxPanel* menuPanel = new wxPanel(panel, wxID_ANY, wxPoint(10, 10), wxSize(150, 250));
	axTreeMenu* menu = new axTreeMenu(menuPanel, wxID_ANY, wxPoint(0, 0), wxSize(150, 250), &scrollBarImg);

	axMultipleBitmap* mainNodeImg = new axMultipleBitmap(wxT("MainNode.png"),  2, wxSize(12, 12));
	axMultipleBitmap* subNodeImg  = new axMultipleBitmap(wxT("SubNode.png"),   2, wxSize(12, 12));
	axMultipleBitmap* subNodeImg2 = new axMultipleBitmap(wxT("NodeBlack.png"), 2, wxSize(12, 12));
	
	axTreeMenuData mainNodeData;
	mainNodeData.nodeColorNormal		= wxColor(130, 130, 130);
	mainNodeData.nodeColorHover			= wxColor(135, 135, 135);
	mainNodeData.nodeColorSelected		= wxColor(125, 125, 125);
	mainNodeData.nodeTxtColorNormal		= wxColor(180, 180, 180);
	mainNodeData.nodeTxtColorHover		= wxColor(200, 200, 200);
	mainNodeData.nodeTxtColorSelected	= wxColor(160, 160, 160);
	mainNodeData.nodeContourColor		= wxColor(120, 120, 120);
	mainNodeData.height = 25;
	mainNodeData.nodeID = 0;

	axTreeMenuData subNodeData;
	subNodeData.nodeColorNormal			= wxColor(140, 140, 140);
	subNodeData.nodeColorHover			= wxColor(145, 145, 145);
	subNodeData.nodeColorSelected		= wxColor(135, 135, 135);
	subNodeData.nodeTxtColorNormal		= wxColor(0, 0, 0);
	subNodeData.nodeTxtColorHover		= wxColor(200, 200, 200);
	subNodeData.nodeTxtColorSelected	= wxColor(70, 70, 70);
	subNodeData.nodeContourColor		= wxColor(120, 120, 120);
	subNodeData.height = 25;
	subNodeData.nodeID = 1;

	axTreeMenuNode* root = new axTreeMenuNode(menu, wxID_ANY, wxT("Song List Menu"), mainNodeData, mainNodeImg);
	menu->addRootNode(root);
	menu->hideRoot(mainNodeData.height);
	root->selectNode();

	axTreeMenuNode* s1 = new axTreeMenuNode(root, wxID_ANY, wxT("Song 1"), mainNodeData, mainNodeImg);
	root->addSubNode(s1);
	s1->selectNode();

	axTreeMenuNode* s1_s1 = new axTreeMenuNode(s1, wxID_ANY, wxT("Lesson 1"), subNodeData, subNodeImg, SELECT_ONLY_THIS_ID);
	s1->addSubNode(s1_s1);

	s1_s1->addSubNode( wxID_ANY, wxT("test 1"), subNodeData, subNodeImg2);
	s1_s1->addSubNode( wxID_ANY, wxT("test 2"), subNodeData, subNodeImg2);
	s1_s1->addSubNode( wxID_ANY, wxT("test 3"), subNodeData, subNodeImg2);
	s1_s1->addSubNode( wxID_ANY, wxT("test 4"), subNodeData, subNodeImg2);
	s1_s1->addSubNode( wxID_ANY, wxT("test 5"), subNodeData, subNodeImg2);
	s1_s1->addSubNode( wxID_ANY, wxT("test 6"), subNodeData, subNodeImg2);
	s1_s1->addSubNode( wxID_ANY, wxT("test 7"), subNodeData, subNodeImg2);

	s1->addSubNode( wxID_ANY, wxT("Lesson 2"), subNodeData, subNodeImg, SELECT_ONLY_THIS_ID);
	s1->addSubNode( wxID_ANY, wxT("Lesson 3"), subNodeData, subNodeImg, SELECT_ONLY_THIS_ID);
	s1->addSubNode( wxID_ANY, wxT("Lesson 4"), subNodeData, subNodeImg, SELECT_ONLY_THIS_ID);
	s1->addSubNode( wxID_ANY, wxT("Lesson 5"), subNodeData, subNodeImg, SELECT_ONLY_THIS_ID);
	s1->addSubNode( wxID_ANY, wxT("Lesson 6"), subNodeData, subNodeImg, SELECT_ONLY_THIS_ID);
	s1->addSubNode( wxID_ANY, wxT("Lesson 7"), subNodeData, subNodeImg, SELECT_ONLY_THIS_ID);
	
	axTreeMenuNode* s2 = new axTreeMenuNode(root, wxID_ANY, wxT("Song 2"), mainNodeData, mainNodeImg);
	root->addSubNode(s2);

	s2->addSubNode( wxID_ANY, wxT("Lesson 1"), subNodeData, subNodeImg, SELECT_ONLY_THIS_ID);
	s2->addSubNode( wxID_ANY, wxT("Lesson 2"), subNodeData, subNodeImg, SELECT_ONLY_THIS_ID);
	s2->addSubNode( wxID_ANY, wxT("Lesson 3"), subNodeData, subNodeImg, SELECT_ONLY_THIS_ID);
	s2->addSubNode( wxID_ANY, wxT("Lesson 4"), subNodeData, subNodeImg, SELECT_ONLY_THIS_ID);
	s2->addSubNode( wxID_ANY, wxT("Lesson 5"), subNodeData, subNodeImg, SELECT_ONLY_THIS_ID);
	s2->addSubNode( wxID_ANY, wxT("Lesson 6"), subNodeData, subNodeImg, SELECT_ONLY_THIS_ID);
	s2->addSubNode( wxID_ANY, wxT("Lesson 7"), subNodeData, subNodeImg, SELECT_ONLY_THIS_ID);
	s2->addSubNode( wxID_ANY, wxT("Lesson 8"), subNodeData, subNodeImg, SELECT_ONLY_THIS_ID);

	frame->Show();
	SetTopWindow(frame);

	return true;
}