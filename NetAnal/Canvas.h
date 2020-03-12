#pragma once

#include "wx/wx.h"
#include "wx/vscroll.h"
#include "vector"
#include "Node.h"

class Canvas : wxHVScrolledWindow
{
public:
	Canvas(wxWindow* parent);
	~Canvas();

private:
	int pixelsize = 8;
	char lastNodeName = 'A';
	int tool = 0;										// node 0, link 1
	bool sourceSelected = false;						// has a source node been selected for a link
	int sourcex = -1;
	int sourcey = -1;
	Node* selectedNode = nullptr;						// dummy node to start

	std::unordered_map<char, Node> nodes;
	std::vector<std::pair<wxPoint, wxPoint>> linkPoints;

	unsigned char* sprite = nullptr;
	

public:
	void setPixelSize(int n);
	void setNetworkData(std::unordered_map<char, Node> nodes, std::vector<std::pair<wxPoint, wxPoint>> linkPoints);
	void setTool(int t);
	std::unordered_map<char, Node> getNetworkNodeData();
	std::vector<std::pair<wxPoint, wxPoint>> getNetworkLinkData();

private:
	virtual wxCoord OnGetRowHeight(size_t row) const;
	virtual wxCoord OnGetColumnWidth(size_t col) const;

	void OnDraw(wxDC& dc);
	void OnPaint(wxPaintEvent& evt);

	void onMouseLeftDown(wxMouseEvent& evt);
	void OnMouseRightDown(wxMouseEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

