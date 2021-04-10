#include "Test_FindFirstIntersection.h"

#include <wx/gbsizer.h>
#include <wx/button.h>

Test_FindFirstIntersection::Test_FindFirstIntersection(wxWindow* parent) : wxPanel(parent)
{
	this->m_sizer = new wxGridBagSizer(0, 0);
	this->m_sizer->SetFlexibleDirection(wxBOTH);
	this->m_sizer->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	this->m_btn_run = new wxButton(this, wxID_ANY, "Run");
	this->m_sizer->Add(this->m_btn_run, wxGBPosition(0, 0), wxGBSpan(1, 1), wxEXPAND | wxALL);

	this->m_sizer->AddGrowableCol(0);
	this->m_sizer->AddGrowableRow(0);

	this->SetSizer(this->m_sizer);
	this->Centre(wxBOTH);
	this->Layout();
}
