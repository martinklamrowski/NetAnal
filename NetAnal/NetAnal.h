#pragma once

#include "wx/wx.h"
#include "Editor.h"

class NetAnal : public wxMDIParentFrame
{
public:
	NetAnal();
	~NetAnal();

private:
	wxToolBar* toolbar = nullptr;
	wxMenuBar* menubar = nullptr;

	void onMenuNew(wxCommandEvent& evt);
	void onMenuOpen(wxCommandEvent& evt);
	void onMenuSave(wxCommandEvent& evt);
	void onMenuExit(wxCommandEvent& evt);

	void onSelectTool(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};