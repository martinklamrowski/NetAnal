#include "Canvas.h"
#include "wx/dcclient.h"
#include "wx/dcmemory.h"
#include "wx/dcbuffer.h"

wxBEGIN_EVENT_TABLE(Canvas, wxHVScrolledWindow)
EVT_PAINT(Canvas::OnPaint)
EVT_LEFT_DOWN(Canvas::onMouseLeftDown)
//EVT_RIGHT_DOWN(Canvas::OnMouseRightDown)
wxEND_EVENT_TABLE()

Canvas::Canvas(wxWindow* parent) : wxHVScrolledWindow(parent, wxID_ANY)
{
	SetRowColumnCount(400, 400);
	SetBackgroundStyle(wxBG_STYLE_PAINT);
}

Canvas::~Canvas()
{
}

void Canvas::setTool(int t)
{
	tool = t;
}

void Canvas::setPixelSize(int n)
{
	pixelsize = n;
	wxVarHScrollHelper::RefreshAll();
	wxVarVScrollHelper::RefreshAll();
	Refresh();
}

void Canvas::setNetworkData(std::unordered_map<char, Node> nodes, std::vector<std::pair<wxPoint, wxPoint>> linkPoints)
{
	this->nodes = nodes;
	this->linkPoints = linkPoints;
}

std::unordered_map<char, Node> Canvas::getNetworkNodeData()
{
	return nodes;
}

std::vector<std::pair<wxPoint, wxPoint>> Canvas::getNetworkLinkData()
{
	return linkPoints;
}

wxCoord Canvas::OnGetRowHeight(size_t row) const
{
	return wxCoord(pixelsize);
}

wxCoord Canvas::OnGetColumnWidth(size_t col) const
{
	return wxCoord(pixelsize);
}

void Canvas::OnDraw(wxDC& dc)
{
	dc.Clear();		// erase the whole screen (no flickering)

	wxBrush brush = dc.GetBrush();
	wxPen pen = dc.GetPen();

	wxPosition start = GetVisibleBegin();
	wxPosition end = GetVisibleEnd();

	pen.SetStyle(wxPENSTYLE_SOLID);
	pen.SetColour(wxColour(255, 0, 0));
	dc.SetPen(pen);

	// LINE DRAWING
	if (pixelsize <= 4) dc.SetPen(*wxTRANSPARENT_PEN);	

	for (std::vector<std::pair<wxPoint, wxPoint>>::const_iterator it = linkPoints.begin(); it != linkPoints.end(); it++)
	{
		dc.DrawLine(it->first, it->second);
	}

	pen.SetStyle(wxPENSTYLE_SOLID);
	pen.SetColour(wxColour(0, 0, 255));
	dc.SetPen(pen);

	// NODE DRAWING
	if (pixelsize <= 4) dc.SetPen(*wxTRANSPARENT_PEN);

	for (std::unordered_map<char, Node>::const_iterator it = nodes.begin(); it != nodes.end(); it++)
	{
		Node currentNode = it->second;
		if (currentNode.selected) {
			pen.SetColour(wxColour(255, 128, 0));
			dc.SetPen(pen);
			dc.DrawCircle(currentNode.posx, currentNode.posy, 32);
		}
		pen.SetColour(wxColour(0, 0, 255));
		dc.SetPen(pen);
		dc.DrawCircle(currentNode.posx, currentNode.posy, 30);
		dc.DrawText(wxString(currentNode.name), wxPoint(currentNode.posx - 7, currentNode.posy - 7));
	}
}

void Canvas::OnPaint(wxPaintEvent& evt)
{
	wxBufferedPaintDC dc(this);
	this->PrepareDC(dc);
	this->OnDraw(dc);
}

void Canvas::onMouseLeftDown(wxMouseEvent& evt)
{
	int x = evt.GetX();
	int y = evt.GetY();
	

	if (tool)
	{ // link selected
		bool goodClick = false;

		for (std::unordered_map<char, Node>::iterator it = nodes.begin(); it != nodes.end(); it++)
		{ 
			Node currentNode = it->second;
			
			if (sqrt(pow(x - currentNode.posx, 2) + pow(y - currentNode.posy, 2)) < 30)
			{ // click was in a node

				if (sourceSelected)
				{ // a source node was selected in a previous iteration
					
					if (sqrt(pow(x - sourcex, 2) + pow(y - sourcey, 2)) >= 30)
					{ // click was not in source node						
						if (!(currentNode.neighbours.count(selectedNode->name))) {
							std::pair<wxPoint, wxPoint> newPoints = std::pair<wxPoint, wxPoint>(wxPoint(currentNode.posx, currentNode.posy), wxPoint(sourcex, sourcey));
							linkPoints.push_back(newPoints);

							// add nodes to each others neighbours map
							currentNode.addNeighbour(selectedNode->name, 0);
							selectedNode->addNeighbour(currentNode.name, 0);
						}				
					}
				}
				else
				{ // no source node was selected previously					
					sourcex = currentNode.posx;
					sourcey = currentNode.posy;
					currentNode.selected = true;
					sourceSelected = true;	
					selectedNode = &currentNode;
					goodClick = true;
				}				
				break;
			}
		}
		if (!goodClick)
		{
			selectedNode->selected = false;
			sourcex = -1;
			sourcey = -1;
			sourceSelected = false;
		}		
	}
	else
	{
		// checking bounds for new Node add
		for (std::unordered_map<char, Node>::const_iterator it = nodes.begin(); it != nodes.end(); it++)
		{
			Node currentNode = it->second;
			if (sqrt(pow(x - currentNode.posx, 2) + pow(y - currentNode.posy, 2)) < 60)
			{
				return;
			}
		}
		Node newNode = Node(static_cast<char>(lastNodeName++), x, y, 0, 0);
		nodes.emplace(newNode.name, newNode);
	}
		
	this->Refresh(false);
	evt.Skip();
}

//void Canvas::OnMouseRightDown(wxMouseEvent& evt)
//{
//	int x = evt.GetX();
//	int y = evt.GetY();
//
//	// need to check all the nodes on the canvas
//	// for every node check if the event is within the node
//	// if a source has already been selected
//	//		check that its not the same node
//	//		check that next click is within another node
//	// else a source has not been selectedd
//	//		check that next click is within another node
//	
//	
//
//	for (std::vector<Node>::iterator it = nodes.begin(); it != nodes.end(); it++)
//	{
//		if (sqrt(pow(x - it->posx, 2) + pow(y - it->posy, 2)) < 30)
//		{
//			it->selected = true;
//			if (sourceSelected)
//			{
//				if (sqrt(pow(x - sourcey, 2) + pow(y - sourcey, 2)) < 30) return;
//
//				std::pair<wxPoint, wxPoint> newPoints = std::pair<wxPoint, wxPoint>(wxPoint(it->posx, it->posy), wxPoint(sourcex, sourcey));
//				linkPoints.push_back(newPoints);
//				sourcex = -1;
//				sourcey = -1;
//				sourceSelected = false;
//				this->Refresh(false);
//			}
//			else
//			{
//				sourcex = it->posx;
//				sourcey = it->posy;
//				sourceSelected = true;				
//			}				
//		}
//	}
//	evt.Skip();
//}
