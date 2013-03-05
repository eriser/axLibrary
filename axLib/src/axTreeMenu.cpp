#include "axTreeMenu.h"

#define SCROLL_BAR_ID		  9000
#define SCROLL_BAR_UNCLICK_ID 9001

BEGIN_EVENT_TABLE(axTreeMenu, wxPanel)
	EVT_BUTTON(wxID_ANY, axTreeMenu::OnButtonDClick)
	EVT_BUTTON(SCROLL_BAR_ID, axTreeMenu::OnScrollBar)
	EVT_MOUSEWHEEL(axTreeMenu::OnMouseWheel)
END_EVENT_TABLE()

axTreeMenu::axTreeMenu(wxWindow* win, wxWindowID id, wxPoint pt, wxSize size, axMultipleBitmap* scrollBarImage) : wxPanel(win, id, pt, size)
{
	SetBackgroundColour(wxColor(100, 100, 100));
	m_rootNode = NULL;
	m_id = id;
	
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// A CHANGER
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	axMultipleBitmap upBmp(scrollBarImage->getBitmap(0), 3, 
							wxSize(scrollBarImage->getBitmap(0).GetWidth(), 
							scrollBarImage->getBitmap(0).GetHeight() / 3));

	axMultipleBitmap downBmp(scrollBarImage->getBitmap(1), 3, 
							wxSize(scrollBarImage->getBitmap(1).GetWidth(), 
							scrollBarImage->getBitmap(1).GetHeight() / 3));
	
	// Create scrollBar
	scrollBar = new axScrollBar(this, SCROLL_BAR_ID, wxPoint(size.x - scrollBarImage->getImgSize().x, 0),
								size.y, &upBmp, &downBmp);
	
	// Set scrool bar default position
	scrollBar->setInputInfo(10, 10, 0);

	m_hiddenRoot = false;
	m_scrollDecay = 0;
	m_rootSize_hidden = 0;
}

axTreeMenu::~axTreeMenu()
{

}

bool axTreeMenu::addRootNode(axTreeMenuNode* node)
{
	// If not main node
	if(!m_rootNode)
	{
		// If scroll bar exist
		if(scrollBar != NULL)
		{	
			// Resize new node added with scrollbar.
			node->SetSize(node->GetSize() + wxSize(GetSize().x - INIT_WIDTH - scrollBar->GetSize().x, 0));
		}
		else
		{
			// Resize new node added.
			node->SetSize(node->GetSize() + wxSize(GetSize().x - INIT_WIDTH, 0));
		}

		m_rootNode = node;

		return 1;
	}
	else return 0;
}

void axTreeMenu::hideRoot(int height)
{
	// If rootNode exist and is not already hidden.
	if(m_rootNode && !m_hiddenRoot)
	{
		// Decay root node.
		m_rootNode->SetPosition(wxPoint(0, 0 - height));
		m_hiddenRoot = true;
		m_rootSize_hidden = height;
	}
}

// Is called from axTreeMenuNode.
void axTreeMenu::OnButtonDClick(wxCommandEvent& event)
{
	DSTREAM << "EVENT : OnButtonDClick from axTreeMenu" << endl;

	// If root node exist.
	if(m_rootNode)
	{
		scrollBar->setInputInfo(GetSize().y, m_rootNode->GetSize().y - m_rootSize_hidden, 0);

		int y = 0 - m_rootSize_hidden - ( scrollBar->getSliderValue() );
		m_rootNode->SetPosition(wxPoint(0, y));
	}

	event.Skip();
}

void axTreeMenu::OnScrollBar(wxCommandEvent& event)
{
	DSTREAM << "EVENT : OnScrollBar from axTreeMenu" << endl;

	int y = 0 - m_rootSize_hidden - ( scrollBar->getSliderValue() );
	m_rootNode->SetPosition(wxPoint(0, y));

	event.Skip();
}

void axTreeMenu::OnMouseWheel(wxMouseEvent& event)
{
	if( IsMouseInWindow() )
	{
		DSTREAM << "EVENT : OnMouseWheel from axTreeMenu" << endl;

		// UP
		if(event.GetWheelRotation() > 0)
		{

		}

		// DOWN 
		else
		{

		}
	}
}
//----------------------------------------------------------------------------------------------------------------------
// axTreeMenuNode
//----------------------------------------------------------------------------------------------------------------------
BEGIN_EVENT_TABLE(axTreeMenuNode, wxPanel)
	EVT_PAINT(axTreeMenuNode::OnPaint)
	EVT_ENTER_WINDOW(axTreeMenuNode::OnMouseEnter)
	EVT_LEAVE_WINDOW(axTreeMenuNode::OnMouseLeave)
	EVT_LEFT_DCLICK(axTreeMenuNode::OnMouseDClick)
	EVT_BUTTON(wxID_ANY, axTreeMenuNode::OnButtonDClick)
END_EVENT_TABLE()

// Root node
axTreeMenuNode::axTreeMenuNode(wxWindow* win, 
							   const wxWindowID& id, 
							   const wxString& label,  
							   const axTreeMenuData& data, 
							   axMultipleBitmap* multiBitmap, 
							   NodeSelectionMode mode): 
							   wxPanel(win),
							   m_label(label)
{
	m_parentNode = NULL;
	m_id = id;
	m_selectMode = mode;
	init(label, data, multiBitmap);
}

// Sub node
axTreeMenuNode::axTreeMenuNode(axTreeMenuNode* win, 
							   const wxWindowID& id, 
							   const wxString& label,  
							   const axTreeMenuData& data, 
							   axMultipleBitmap* multiBitmap, 
							   NodeSelectionMode mode):
						       wxPanel((wxWindow*)win, wxID_ANY),
							   m_label(label)
{
	m_parentNode = win;
	m_id = id;
	m_selectMode = mode;

	init(label, data, multiBitmap);
}

void axTreeMenuNode::init(const wxString& label, const axTreeMenuData& data, axMultipleBitmap* multiBitmap)
{
	// Needed to use wxAutoBufferedPaintDC.
	SetBackgroundStyle(wxBG_STYLE_CUSTOM); 	

	// Menu UI information.
	m_data = data;
	m_multiBitmap = multiBitmap;

	// ???
	m_currentImageID = IMAGE_NORMAL;

	// Set current background and text color
	m_bgColor = &m_data.nodeColorNormal;
	m_txtColor = &m_data.nodeTxtColorNormal;

	// Init number of sub node and sub sub array.
	m_nSubNode = 0;
	m_nSubNodeMax = INIT_ARRAY_SIZE;
	m_nodes = new axTreeMenuNode* [m_nSubNodeMax];

	// Set default node size.
	SetSize(wxSize(INIT_WIDTH, m_data.height));
}

void axTreeMenuNode::addSubNode(axTreeMenuNode* node)
{
	if(node)
	{
		// Resize node to parent size.
		node->SetSize(wxSize(GetParent()->GetSize().x, m_data.height));

		// If is not the fisrt one to be added.
		if(m_nSubNode)
		{
			node->SetPosition(m_nodes[m_nSubNode - 1]->getButtomPosition());
		}
		else // First added.
		{
			node->SetPosition(wxPoint(0, m_data.height));
		}

		// Add node.
		m_nodes[m_nSubNode++] = node;

		resize();
	}
}

void axTreeMenuNode::addSubNode(const wxWindowID& id, 
								const wxString name, 
								const axTreeMenuData& data, 
								axMultipleBitmap* multiBitmap, 
								NodeSelectionMode mode)
{
	axTreeMenuNode* node = new axTreeMenuNode(this, id, name, data, multiBitmap, mode);
	// Resize node to parent size.
	node->SetSize(wxSize(GetParent()->GetSize().x, m_data.height));

	// If is not the fisrt one to be added.
	if(m_nSubNode)
	{
		node->SetPosition(m_nodes[m_nSubNode - 1]->getButtomPosition());
	}
	else // First added.
	{
		node->SetPosition(wxPoint(0, m_data.height));
	}

	// Add node.
	m_nodes[m_nSubNode++] = node;

	resize();
}

void axTreeMenuNode::selectNode()
{
	if(m_currentImageID != IMAGE_SELECTED)
	{
		m_currentImageID = IMAGE_SELECTED;
		m_bgColor = &m_data.nodeColorSelected;
		m_txtColor = &m_data.nodeTxtColorSelected;

		resize();
		Refresh();
	}
}

void axTreeMenuNode::unselectNode()
{
	if(m_currentImageID != IMAGE_NORMAL)
	{
		m_currentImageID = IMAGE_NORMAL;
		m_bgColor = &m_data.nodeColorNormal;
		m_txtColor = &m_data.nodeTxtColorNormal;

		resize();
		Refresh();
	}
}

void axTreeMenuNode::resize()
{
	int y = m_data.height;

	if(m_nSubNode && m_currentImageID == IMAGE_SELECTED)
	{
		for(int i = 0; i < m_nSubNode; ++i)
			y += m_nodes[i]->GetSize().y;

		m_nodes[0]->SetPosition(wxPoint(0, m_data.height));

		for(int i = 1; i < m_nSubNode; ++i)
			m_nodes[i]->SetPosition(m_nodes[i - 1]->getButtomPosition());		
	}

	SetSize(GetSize().x, y);

	if(m_parentNode) m_parentNode->resize();
}

wxPoint axTreeMenuNode::getButtomPosition() const
{
	return wxPoint( GetPosition().x, GetPosition().y + GetSize().y );
}

void axTreeMenuNode::unselectAll(int id)
{
	if(m_data.nodeID == id)
		unselectNode();

	if(m_nSubNode)
	{
		for(int i = 0; i < m_nSubNode; ++i)
			m_nodes[i]->unselectAll(id);
	}
}

void axTreeMenuNode::setSelectionMode(NodeSelectionMode mode)
{
	m_selectMode = mode;
}

void axTreeMenuNode::OnMouseEnter(wxMouseEvent& event)
{
	if(m_currentImageID != IMAGE_SELECTED)
	{
		m_bgColor = &m_data.nodeColorHover;
		m_txtColor = &m_data.nodeTxtColorHover;
		Refresh();
	}
}

void axTreeMenuNode::OnMouseLeave(wxMouseEvent& event)
{
	if(m_currentImageID != IMAGE_SELECTED)
	{
		m_bgColor = &m_data.nodeColorNormal;
		m_txtColor = &m_data.nodeTxtColorNormal;
		Refresh();
	}
}

void axTreeMenuNode::OnMouseDClick(wxMouseEvent& event)
{
	// If node is already selected.
	if(m_currentImageID == IMAGE_SELECTED)
	{
		// Set node UI info to unselected.
		m_currentImageID = IMAGE_NORMAL;
		m_bgColor = &m_data.nodeColorNormal;
		m_txtColor = &m_data.nodeTxtColorNormal;
	}

	else // Node if unselected.
	{
		// Unselect all other selected node.
		if(m_selectMode == SELECT_ONLY_THIS_ID)
		{
			axTreeMenuNode* node = this;

			// Get to root node
			while(node->m_parentNode)
				node = node->m_parentNode;

			// Unselect every node selected with this id.
			node->unselectAll(m_data.nodeID);
		}

		// Set node UI info to selected.
		m_currentImageID = IMAGE_SELECTED;
		m_bgColor = &m_data.nodeColorSelected;
		m_txtColor = &m_data.nodeTxtColorSelected;
	}

	// Send event.
	wxCommandEvent btnEvent(wxEVT_COMMAND_BUTTON_CLICKED, m_id);
	wxPostEvent(this, btnEvent);

	resize();
	Refresh();
}

void axTreeMenuNode::OnButtonDClick(wxCommandEvent& event)
{
	event.Skip();
}

void axTreeMenuNode::OnPaint(wxPaintEvent& event)
{
	wxAutoBufferedPaintDC dc(this);
	wxSize size = this->GetSize();

	dc.SetPen(wxPen(m_data.nodeContourColor, 1, wxSOLID));
	dc.SetBrush(wxBrush(*m_bgColor));
	dc.DrawRectangle(wxRect(0, 0, size.x, m_data.height));
	
	wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
    if (gc)
    {		
        gc->SetPen(wxPen(m_data.nodeContourColor, 1, wxSOLID));
		gc->SetBrush(wxBrush(*m_bgColor, wxSOLID));
		gc->DrawRoundedRectangle(0, 0, size.x, m_data.height, 2);

		gc->SetFont(wxFont(wxFont(9, wxDEFAULT, wxNORMAL, wxBOLD, false, _T("") )), 
					wxColor(*m_txtColor) );
								     
		gc->DrawText(m_label, /*m_xDecay*/  30, (m_data.height - dc.GetCharHeight()) * 0.5);

		delete gc;
	}
	else // No Graphic Context
	{
		// TODO
	}
	
	dc.DrawBitmap(m_multiBitmap->getBitmap(m_currentImageID), 
				  /*m_xDecay*/ 10, (m_data.height - m_multiBitmap->getImgSize().y) * 0.5);
}



