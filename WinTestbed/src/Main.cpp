#include "Main.h"

#include <wx/gbsizer.h>
#include <wx/notebook.h>

#include "tests/Test_FindFirstIntersection.h"

Main::Main() : wxFrame(nullptr, wxID_ANY, "fx-CG50FirstPerson tests")
{
	this->m_sizer = new wxGridBagSizer(0, 0);
	this->m_sizer->SetFlexibleDirection(wxBOTH);
	this->m_sizer->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	this->m_nb_tests = new wxNotebook(this, wxID_ANY);
	this->m_sizer->Add(this->m_nb_tests, wxGBPosition(0, 0), wxGBSpan(1, 1), wxEXPAND | wxALL);

	this->m_nb_tests->AddPage(new Test_FindFirstIntersection(this->m_nb_tests), "FindFirstIntersection", true);

	this->m_sizer->AddGrowableCol(0);
	this->m_sizer->AddGrowableRow(0);

	this->SetSizer(this->m_sizer);
	this->Centre(wxBOTH);
	this->Layout();
}
