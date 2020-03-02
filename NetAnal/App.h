#pragma once

#include "wx/wx.h"
#include "NetAnal.h"

class App : public wxApp
{

public:
	App();
	~App();

private:
	NetAnal* frame = nullptr;

public:
	virtual bool OnInit();
};
