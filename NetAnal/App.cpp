#include "App.h"

wxIMPLEMENT_APP(App);

App::App()
{

}

App::~App()
{

}

bool App::OnInit()
{

	frame = new NetAnal();
	frame->Show();
	return true;
}
