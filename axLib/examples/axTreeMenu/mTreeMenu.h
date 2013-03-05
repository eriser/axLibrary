/********************************************************************************//**
 * @file			mTreeMenu.h
 * @author			Alexandre Arsenault <alexandre.arsenault@polymtl.ca>
 * @brief			class mTreeMenu and class mTreeMenu
 * @details			
 *
 * @date			Creation 28/01/2013
 ***********************************************************************************/
#ifndef _M_TREE_MENU_H_
#define _M_TREE_MENU_H_

#include "wx/wx.h"
#include "wx/dcbuffer.h"
#include "wx/graphics.h"

#include "mMultipleBitmap.h"

enum ImageID
{
	IMAGE_NORMAL = 0,
	IMAGE_SELECTED
};

enum NodeSelectionMode
{
	SELECT_ANY = 0,
	SELECT_ONLY_THIS_ID
};

class mTreeMenu;

struct mTreeMenuData
{
	wxColor nodeColorNormal, 
			nodeColorSelected, 
			nodeColorHover, 
			nodeContourColor,
			nodeTxtColorNormal,
			nodeTxtColorHover,
			nodeTxtColorSelected;
	int height;
	int nodeID;
};

class mTreeMenuNode: public wxPanel
{
public:
	/********************************************************************************//**
	 * @brief  Constructor
	 * @param win			Parent node
	 * @param id			Id for wxWidget
	 * @param label			Label
	 * @param data			Information on UI
	 * @param multiBitmap	Images of the node (img 0 = img_normal, img 1 = img_selected)
	 ***********************************************************************************/
	mTreeMenuNode(mTreeMenuNode* win, const wxWindowID& id, const wxString& label,  
				  const mTreeMenuData& data, mMultipleBitmap* multiBitmap, NodeSelectionMode mode = SELECT_ANY);
	
	/********************************************************************************//**
	 * @brief  Constructor for root node
	 * @param win wxWindow parent
	 ***********************************************************************************/
	mTreeMenuNode(wxWindow* win, const wxWindowID& id, const wxString& label,  
				  const mTreeMenuData& data, mMultipleBitmap* multiBitmap, NodeSelectionMode mode = SELECT_ANY);

	void init(const wxString& label, const mTreeMenuData& data, mMultipleBitmap* multiBitmap);
	/********************************************************************************//**
	 * @brief  Return buttom left position of the last node for positioning the next node
	 * @return buttom left position of the last node
	 ***********************************************************************************/
	wxPoint getButtomPosition() const;

	/********************************************************************************//**
	 * @brief  Add a node to a parent node 
	 * !IMPORTANT! Always add parent node to his parent before adding child node
	 * EX:
	 * @code
	 * mTreeMenu* menu = new mTreeMenu(panel, wxID_ANY, wxPoint(0, 0), wxSize(150, 450));
	 * mTreeMenuNode* root = new mTreeMenuNode(menu, wxID_ANY, wxT("ROOT"), nodeData, nodeImg);
	 * menu->addRootNode(root);
	 *
	 * mTreeMenuNode* n1 = new mTreeMenuNode(root, wxID_ANY, wxT("Node 1"), nodeData, nodeImg);
	 * root->addSubNode( n1 );
	 * s1->addSubNode( new mTreeMenuNode(n1, wxID_ANY, wxT("Sub Node 1"), nodeData, nodeImg));
	 * @endcode
	 *
	 * @param node Node to be added
	 ***********************************************************************************/
	void addSubNode(mTreeMenuNode* node);

	void unselectAll(int id);
	void selectNode();
	void unselectNode();
	void setSelectionMode(NodeSelectionMode mode);

private:
	void OnPaint(wxPaintEvent& event);
	void OnMouseEnter(wxMouseEvent& event);
	void OnMouseLeave(wxMouseEvent& event);
	void OnMouseDClick(wxMouseEvent& event);
	void OnButtonDClick(wxCommandEvent& event);

	void resize();
	
	wxWindowID m_id;
	NodeSelectionMode m_selectMode;

	// GUI Params
	mTreeMenuData m_data;
	mMultipleBitmap* m_multiBitmap;
	wxString m_label;
	int m_currentImageID;
	wxColor *m_bgColor, *m_txtColor;
	
	// Sub Node Params
	int m_nSubNode, m_nSubNodeMax;
	mTreeMenuNode** m_nodes;

	// Parent 
	mTreeMenuNode* m_parentNode;

	static const int INIT_WIDTH = 5;
	static const int INIT_ARRAY_SIZE = 5;
	
	DECLARE_EVENT_TABLE()
};

class mTreeMenu: public wxPanel
{
public:
	mTreeMenu(){}
	mTreeMenu(wxWindow* win, wxWindowID id, wxPoint pt, wxSize size); 
	~mTreeMenu();

	bool addRootNode(mTreeMenuNode* node);
	void hideRoot(int height);
	
private:
	void OnPaint(wxPaintEvent& event);
	
	mTreeMenuNode* m_rootNode;
};
#endif