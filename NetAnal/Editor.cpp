#include "Editor.h"

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
	std::wstring file = fileName.wc_str();
	FILE* f = nullptr;
	_wfopen_s(&f, file.c_str(), L"wb");
	if (f == nullptr)
		return false;

	fwrite(&canvas->getNetworkNodeData(), sizeof(std::vector<Node>), 1, f);
	fwrite(&canvas->getNetworkLinkData(), sizeof(std::vector<std::pair<wxPoint, wxPoint>>), 1, f);

	fclose(f);
	return true;
}

bool Editor::open(wxString fileName)
{
	std::wstring file = fileName.wc_str();
	FILE* f = nullptr;
	_wfopen_s(&f, file.c_str(), L"rb");
	if (f == nullptr)
		return false;

	std::fread(&width, sizeof(int), 1, f);
	std::fread(&height, sizeof(int), 1, f);

	std::fclose(f);
	return true;
}

void Editor::OnZoomChange(wxCommandEvent& evt)
{
	statusbar->SetStatusText(wxString("Zoom: ") << zoomer->GetValue(), 1);
	canvas->setPixelSize(zoomer->GetValue());
	evt.Skip();
}
