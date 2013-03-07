#include "mTreeMenu.h"

mTreeMenu::mTreeMenu(wxWindow* win, wxWindowID id, wxPoint pt, wxSize size) : wxPanel(win, id, pt, size)
{
	SetBackgroundColour(wxColor(80, 80, 80));
	m_rootNode = NULL;
}
mTreeMenu::~mTreeMenu()
{

}
bool mTreeMenu::addRootNode(mTreeMenuNode* node)
{
	if(!m_rootNode)
	{
		node->SetSize(node->GetSize() + wxSize(GetSize().x - 5, 0));
		m_rootNode = node;
		return 1;
	}
	else return 0;
}
void mTreeMenu::hideRoot(int height)
{
	if(m_rootNode)
		m_rootNode->SetPosition(wxPoint(0, 0 - height));
}
//----------------------------------------------------------------------------------------------------------------------
// mTreeMenuNode
//----------------------------------------------------------------------------------------------------------------------
BEGIN_EVENT_TABLE(mTreeMenuNode, wxPanel)
	EVT_PAINT(mTreeMenuNode::OnPaint)
	EVT_ENTER_WINDOW(mTreeMenuNode::OnMouseEnter)
	EVT_LEAVE_WINDOW(mTreeMenuNode::OnMouseLeave)
	EVT_LEFT_DCLICK(mTreeMenuNode::OnMouseDClick)
	EVT_BUTTON(wxID_ANY, mTreeMenuNode::OnButtonDClick)
END_EVENT_TABLE()

// Root node
mTreeMenuNode::mTreeMenuNode(wxWindow* win, const wxWindowID& id, const wxString& label,  
							 const mTreeMenuData& data, mMultipleBitmap* multiBitmap, NodeSelectionMode mode): wxPanel(win),
							 m_label(label)
{
	m_parentNode = NULL;
	m_id = id;
	m_selectMode = mode;
	init(label, data, multiBitmap);
}
mTreeMenuNode::mTreeMenuNode(mTreeMenuNode* win, const wxWindowID& id, const wxString& label,  
							 const mTreeMenuData& data, mMultipleBitmap* multiBitmap, NodeSelectionMode mode):
						     wxPanel((wxWindow*)win, wxID_ANY),
							 m_label(label)
{
	m_parentNode = win;
	m_id = id;
	m_selectMode = mode;
	init(label, data, multiBitmap);
}
void mTreeMenuNode::init(const wxString& label, const mTreeMenuData& data, mMultipleBitmap* multiBitmap)
{
	SetBackgroundStyle(wxBG_STYLE_CUSTOM); 		
	wxImage::AddHandler(new wxPNGHandler);

	m_data = data;
	m_multiBitmap = multiBitmap;

	m_currentImageID = IMAGE_NORMAL;

	m_bgColor = &m_data.nodeColorNormal;
	m_txtColor = &m_data.nodeTxtColorNormal;

	m_nSubNode = 0;
	m_nSubNodeMax = INIT_ARRAY_SIZE;
	m_nodes = new mTreeMenuNode* [m_nSubNodeMax];

	SetSize(wxSize(INIT_WIDTH, m_data.height));
}
void mTreeMenuNode::addSubNode(mTreeMenuNode* node)
{
	if(node)
	{
		node->SetSize(wxSize(GetParent()->GetSize().x, m_data.height));

		if(m_nSubNode)
		{
			node->SetPosition(m_nodes[m_nSubNode - 1]->getButtomPosition());
		}
		else // First Added
		{
			node->SetPosition(wxPoint(0, m_data.height));
		}

		//if(m_nSubNode < m_nSubNodeMax)
		//{
			m_nodes[m_nSubNode++] = node;
		//}

		resize();
	}
}
void mTreeMenuNode::selectNode()
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
void mTreeMenuNode::unselectNode()
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
void mTreeMenuNode::resize()
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
wxPoint mTreeMenuNode::getButtomPosition() const
{
	return wxPoint( GetPosition().x, GetPosition().y + GetSize().y );
}
void mTreeMenuNode::unselectAll(int id)
{
	if(m_data.nodeID == id)
		unselectNode();

	if(m_nSubNode)
	{
		for(int i = 0; i < m_nSubNode; ++i)
			m_nodes[i]->unselectAll(id);
	}
}
void mTreeMenuNode::setSelectionMode(NodeSelectionMode mode)
{
	m_selectMode = mode;
}
void mTreeMenuNode::OnMouseEnter(wxMouseEvent& event)
{
	if(m_currentImageID != IMAGE_SELECTED)
	{
		m_bgColor = &m_data.nodeColorHover;
		m_txtColor = &m_data.nodeTxtColorHover;
		Refresh();
	}
}
void mTreeMenuNode::OnMouseLeave(wxMouseEvent& event)
{
	if(m_currentImageID != IMAGE_SELECTED)
	{
		m_bgColor = &m_data.nodeColorNormal;
		m_txtColor = &m_data.nodeTxtColorNormal;
		Refresh();
	}
}
void mTreeMenuNode::OnMouseDClick(wxMouseEvent& event)
{
	if(m_currentImageID == IMAGE_SELECTED)
	{
		m_currentImageID = IMAGE_NORMAL;
		m_bgColor = &m_data.nodeColorNormal;
		m_txtColor = &m_data.nodeTxtColorNormal;
	}
	else // 
	{
		if(m_selectMode == SELECT_ONLY_THIS_ID)
		{
			mTreeMenuNode* node = this;

			// Get to root node
			while(node->m_parentNode)
				node = node->m_parentNode;

			node->unselectAll(m_data.nodeID);
		}

		m_currentImageID = IMAGE_SELECTED;
		m_bgColor = &m_data.nodeColorSelected;
		m_txtColor = &m_data.nodeTxtColorSelected;

		if(m_id != wxID_ANY)
		{
			wxCommandEvent btnEvent(wxEVT_COMMAND_BUTTON_CLICKED, m_id);
			wxPostEvent(this, btnEvent);
		}
	}

	resize();
	Refresh();
}
void mTreeMenuNode::OnButtonDClick(wxCommandEvent& event)
{
	event.Skip();
}
void mTreeMenuNode::OnPaint(wxPaintEvent& event)
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
		//dc.SetTextForeground(*m_txtColor);
		//dc.DrawText(m_label, m_xDecay + 30, (m_data.height - dc.GetCharHeight()) * 0.5);
	}
	
	dc.DrawBitmap(m_multiBitmap->getBitmap(m_currentImageID), 
				  /*m_xDecay*/ 10, (m_data.height - m_multiBitmap->getImgSize().y) * 0.5);
}



