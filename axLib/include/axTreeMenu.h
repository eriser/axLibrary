/********************************************************************************//**
 * @file			axTreeMenu.h
 * @author			Alexandre Arsenault <alexandre.arsenault@polymtl.ca>
 * @brief			class axTreeMenu and class axTreeMenu
 * @details			
 * @date			Creation 28/01/2013
 ***********************************************************************************/
#ifndef _M_TREE_MENU_H_
#define _M_TREE_MENU_H_

#include "wx/wx.h"
#include "wx/dcbuffer.h"
#include "wx/graphics.h"

#include "axDebug.h"
#include "axMultipleBitmap.h"
#include "axScrollBar.h"

enum NodeSelectionMode
{
	SELECT_ANY = 0,
	SELECT_ONLY_THIS_ID
};

struct axTreeMenuData
{
	int nodeID, height;
	wxColor nodeColorNormal, 
			nodeColorSelected, 
			nodeColorHover, 
			nodeContourColor,
			nodeTxtColorNormal,
			nodeTxtColorHover,
			nodeTxtColorSelected;
};

class axTreeMenu;

class axTreeMenuNode: public wxPanel
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
	axTreeMenuNode(axTreeMenuNode* win, 
				   const wxWindowID& id, 
				   const wxString& label,  
				   const axTreeMenuData& data, 
				   axMultipleBitmap* multiBitmap, 
				   NodeSelectionMode mode = SELECT_ANY);
	
	/********************************************************************************//**
	 * @brief  Constructor for root node
	 * @param win wxWindow parent
	 ***********************************************************************************/
	axTreeMenuNode(wxWindow* win, 
				   const wxWindowID& id, 
				   const wxString& label,  
				   const axTreeMenuData& data, 
				   axMultipleBitmap* multiBitmap, 
				   NodeSelectionMode mode = SELECT_ANY);

	/********************************************************************************//**
	 * @brief Init params.
	 * @param label			Label
	 * @param data			Information on UI
	 * @param multiBitmap	Images of the node (img 0 = img_normal, img 1 = img_selected)
	 ***********************************************************************************/
	void init(const wxString& label, 
			  const axTreeMenuData& data, 
			  axMultipleBitmap* multiBitmap);

	/********************************************************************************//**
	 * @brief  Return buttom left position of the last node. 
	 *         Is used to place new node.
	 *
	 * @return buttom left position of the last node
	 ***********************************************************************************/
	wxPoint getButtomPosition() const;

	/********************************************************************************//**
	 * @brief Add sub node
	 * @param id			Id for wxWidget
	 * @param label			Label
	 * @param data			Information on UI
	 * @param multiBitmap	Images of the node (img 0 = img_normal, img 1 = img_selected)
	 ***********************************************************************************/
	void addSubNode(const wxWindowID& id, 
					const wxString name, 
					const axTreeMenuData& data, 
					axMultipleBitmap* multiBitmap, 
					NodeSelectionMode mode = SELECT_ANY);

	/********************************************************************************//**
	 * @brief  Add a node to a parent node 
	 * !IMPORTANT! Always add parent node to his parent before adding child node
	 * EX:
	 * @code
	 * axTreeMenu* menu = new axTreeMenu(panel, wxID_ANY, wxPoint(0, 0), wxSize(150, 450));
	 * axTreeMenuNode* root = new axTreeMenuNode(menu, wxID_ANY, wxT("ROOT"), nodeData, nodeImg);
	 * menu->addRootNode(root);
	 *
	 * axTreeMenuNode* n1 = new axTreeMenuNode(root, wxID_ANY, wxT("Node 1"), nodeData, nodeImg);
	 * root->addSubNode( n1 );
	 * s1->addSubNode( new axTreeMenuNode(n1, wxID_ANY, wxT("Sub Node 1"), nodeData, nodeImg));
	 * @endcode
	 *
	 * @param node Node to be added
	 ***********************************************************************************/
	void addSubNode(axTreeMenuNode* node);

	/// @todo Write Doc.
	void unselectAll(int id);

	/// @todo Write Doc.
	void selectNode();

	/// @todo Write Doc.
	void unselectNode();

	/// @todo Write Doc.
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
	axTreeMenuData m_data;
	axMultipleBitmap* m_multiBitmap;
	wxColor *m_bgColor, *m_txtColor;
	int m_currentImageID;
	wxString m_label;
	
	// Sub Node Params
	int m_nSubNode, m_nSubNodeMax;
	axTreeMenuNode** m_nodes;

	// Parent 
	axTreeMenuNode* m_parentNode;

	static const int INIT_WIDTH = 5;
	static const int INIT_ARRAY_SIZE = 5;
	
	enum ImageID
	{
		IMAGE_NORMAL = 0,
		IMAGE_SELECTED
	};

	DECLARE_EVENT_TABLE()
};

/********************************************************************************//**
* @brief 
 ***********************************************************************************/
class axTreeMenu: public wxPanel
{
public:
	axTreeMenu(){}
	axTreeMenu(wxWindow* win, wxWindowID id, wxPoint pt, wxSize size, axMultipleBitmap* scrollBarImage); 
	~axTreeMenu();

	bool addRootNode(axTreeMenuNode* node);
	void hideRoot(int height);
	
private:
	void OnPaint(wxPaintEvent& event);
	void OnButtonDClick(wxCommandEvent& event);
	void OnScrollBar(wxCommandEvent& event);
	void OnMouseWheel(wxMouseEvent& event);

	wxWindowID m_id;
	axScrollBar* scrollBar;
	axTreeMenuNode* m_rootNode;
	bool m_hiddenRoot;
	int m_scrollDecay, m_rootSize_hidden;

	static const int INIT_WIDTH = 5;

	DECLARE_EVENT_TABLE()
};
#endif