#pragma once

#include <wx/frame.h>

class wxNotebook;
class wxGridBagSizer;

class Main : public wxFrame
{
private:
	wxGridBagSizer* m_sizer;
	wxNotebook* m_nb_tests;

public:
	Main();
};