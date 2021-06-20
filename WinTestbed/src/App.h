#pragma once

#include <wx/wx.h>

class Main;

class App : public wxApp
{
private:
	Main* m_frame_main = nullptr;

public:
	bool OnInit();
	int OnExit();
};