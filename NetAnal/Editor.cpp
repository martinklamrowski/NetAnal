#include "Editor.h"
#include "fstream"

wxBEGIN_EVENT_TABLE(Editor, wxMDIChildFrame)
EVT_SLIDER(20001, Editor::OnZoomChange)
wxEND_EVENT_TABLE()

Editor::Editor(wxMDIParentFrame* parent, wxString name) : wxMDIChildFrame(parent, wxID_ANY, name)
{
	canvas = new Canvas(this);

	statusbar = this->CreateStatusBar(2, wxSTB_DEFAULT_STYLE, wxID_ANY);
	zoomer = new wxSlider(statusbar, 20001, 8, 1, 32);
}

Editor::~Editor()
{
}

void Editor::setTool(int t)
{
	canvas->setTool(t);
}

bool Editor::save(wxString fileName)
{
	std::ofstream outstream(fileName.ToStdString());
	
	std::unordered_map<char, Node> writeNodes = canvas->getNetworkNodeData();
	std::vector<std::pair<wxPoint, wxPoint>> writeLinkPoints = canvas->getNetworkLinkData();

	for (std::unordered_map<char, Node>::const_iterator nodeit = writeNodes.begin(); nodeit != writeNodes.end(); nodeit++)
	{
		std::unordered_map<char, double> neighbours = nodeit->second.neighbours;
		outstream << nodeit->second.name << " " << nodeit->second.posx << " " << nodeit->second.posy << " " << nodeit->second.beg << " " << nodeit->second.end << " " << nodeit->second.neighbours.size() << std::endl;

		for (std::unordered_map<char, double>::const_iterator neighbourit = neighbours.begin(); neighbourit != neighbours.end(); neighbourit++) 
		{
			outstream << neighbourit->first << " " << neighbourit->second << std::endl;
		}
	}

	return true;
}

bool Editor::open(wxString fileName)
{
	char name, neighbourName;
	int posx, posy, beg, end, numNeighbours;
	double dist;
	
	std::ifstream instream(fileName.ToStdString());	

	std::unordered_map<char, Node> readNodes;
	std::vector<std::pair<wxPoint, wxPoint>> readLinkPoints;
	
	while (instream >> name >> posx >> posy >> beg >> end >> numNeighbours) 
	{
		Node readNode = Node(name, posx, posy, beg, end);		
		
		for (int n = 0; n < numNeighbours; n++) 
		{
			instream >> neighbourName >> dist;
			readNode.addNeighbour(neighbourName, dist);
		}
		readNodes.emplace(name, readNode);
	}
	canvas->setNetworkData(readNodes, readLinkPoints);

	instream.close();

	return true;
}

void Editor::OnZoomChange(wxCommandEvent& evt)
{
	statusbar->SetStatusText(wxString("Zoom: ") << zoomer->GetValue(), 1);
	canvas->setPixelSize(zoomer->GetValue());
	evt.Skip();
}
