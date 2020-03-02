#include "NetAnal.h"

wxBEGIN_EVENT_TABLE(NetAnal, wxMDIParentFrame)
EVT_MENU(10001, NetAnal::onMenuNew)
EVT_MENU(10002, NetAnal::onMenuOpen)
EVT_MENU(10003, NetAnal::onMenuSave)
EVT_MENU(10004, NetAnal::onMenuExit)
wxEND_EVENT_TABLE()

NetAnal::NetAnal() : wxMDIParentFrame(nullptr, wxID_ANY, "Network Editor", wxPoint(30, 30), wxSize(800, 600))
{

	// add a menu bar
	menubar = new wxMenuBar();
	this->SetMenuBar(menubar);

	// add menu for file operations
	wxMenu* menuFile = new wxMenu();
	menuFile->Append(10001, "New");
	menuFile->Append(10002, "Open");
	menuFile->Append(10003, "Save");
	menuFile->Append(10004, "Exit");

	// add file menu to menu bar
	menubar->Append(menuFile, "File");

	// add a toolbar for pallette
	toolbar = this->CreateToolBar(wxTB_HORIZONTAL, wxID_ANY);
	
	// adding buttons
	wxButton* nodebutton = new wxButton(toolbar, 10100, "Node", wxDefaultPosition, wxSize(40, 24), 0);
	nodebutton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NetAnal::onSelectTool), nullptr, this);
	toolbar->AddControl(nodebutton);

	wxButton* linkbutton = new wxButton(toolbar, 10101, "Link", wxDefaultPosition, wxSize(40, 24), 0);
	linkbutton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NetAnal::onSelectTool), nullptr, this);
	toolbar->AddControl(linkbutton);

	toolbar->Realize();
}

NetAnal::~NetAnal()
{

}

void NetAnal::onMenuNew(wxCommandEvent& evt)
{
	Editor* f = new Editor(this, "test");
	f->Show();
	evt.Skip();
}

void NetAnal::onMenuOpen(wxCommandEvent& evt)
{
	wxFileDialog dlg(this, "Open Network File", "", "", ".netanal Files (*.netanal)|*.netanal", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (dlg.ShowModal() == wxID_OK)
	{
		Editor* f = new Editor(this, dlg.GetPath());
		f->open(dlg.GetPath());
		f->Show();
	}
	evt.Skip();
}

void NetAnal::onMenuSave(wxCommandEvent& evt)
{
	if (GetActiveChild() != nullptr)
	{
		wxFileDialog dlg(this, "Save Network File", "", "", ".netanal Files (*.netanal)|*.netanal", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
		if (dlg.ShowModal() == wxID_OK)
		{
			((Editor*)GetActiveChild())->save(dlg.GetPath());
		}
	}
}

void NetAnal::onMenuExit(wxCommandEvent& evt)
{
	Close();
	evt.Skip();
}

void NetAnal::onSelectTool(wxCommandEvent& evt)
{
	int tool = evt.GetId() - 10100;
	if (GetActiveChild() != nullptr)
	{
		((Editor*)GetActiveChild())->setTool(tool);
	}
}
