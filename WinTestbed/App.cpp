#include "App.h"

#include "Main.h"

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
	this->m_frame_main = new Main();
	this->m_frame_main->Show();

	return true;
}

int App::OnExit()
{
	return 0;
}
