#pragma once
#include "wx/wx.h"
#include "Canvas.h"
#include "olcSprite.h"

class Editor : public wxMDIChildFrame
{
public:
	Editor(wxMDIParentFrame* parent, wxString name);
	~Editor();

	void setTool(int c);
	bool save(wxString sFileName);
	bool open(wxString sFileName);

private:
	Canvas* canvas = nullptr;
	wxStatusBar* statusbar = nullptr;
	wxSlider* zoomer = nullptr;

	void OnZoomChange(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

