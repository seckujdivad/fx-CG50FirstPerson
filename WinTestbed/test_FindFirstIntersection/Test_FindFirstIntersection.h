#pragma once

#include <wx/panel.h>

class wxButton;
class wxGridBagSizer;

class Test_FindFirstIntersection : public wxPanel
{
private:
	wxGridBagSizer* m_sizer;
	wxButton* m_btn_run;

public:
	Test_FindFirstIntersection(wxWindow* parent);
};