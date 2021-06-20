#include "Test_Renderer.h"

#include <stdexcept>

#include <wx/dcbuffer.h>
#include <wx/gbsizer.h>
#include <wx/slider.h>

#include "../fxcg_impl.h"

constexpr float SliderToValue(int x)
{
	return static_cast<float>(x) / 100.0f;
}

constexpr int ValueToSlider(float x)
{
	return static_cast<int>(x * 100.0f);
}

void Test_Renderer::OnPaint(wxPaintEvent& evt)
{
	wxBufferedPaintDC paint_dc = wxBufferedPaintDC(this->m_pnl_render);
	paint_dc.SetBackground(*wxWHITE_BRUSH);
	paint_dc.Clear();

	paint_dc.SetPen(*wxTRANSPARENT_PEN);

	AddCallback([&paint_dc](int x, int y, int colour)
		{
			using color_t = fxcg::color_t;

#ifdef COLOUR_ADDER
#error Macro already defined
#endif

#define COLOUR_ADDER(name) case COLOR_ ## name: paint_dc.SetBrush(*wx ## name ## _BRUSH); break;

			switch (colour)
			{
				COLOUR_ADDER(RED)
				COLOUR_ADDER(GREEN)
				COLOUR_ADDER(BLUE)
				COLOUR_ADDER(BLACK)
			case COLOR_ORANGE: paint_dc.SetBrush(*wxYELLOW_BRUSH); break;
			case COLOR_BROWN: paint_dc.SetBrush(*wxMEDIUM_GREY_BRUSH); break;
			case COLOR_PURPLE: paint_dc.SetBrush(*wxCYAN_BRUSH); break;
			default: throw std::runtime_error("Unknown colour");
			};

			paint_dc.DrawRectangle(wxRect(x, y, 1, 1));
		});

#undef COLOUR_ADDER

	fxcg::Render(this->m_world, this->m_player, fxcg::SPRITES, fxcg::NUM_SPRITES);

	ClearCallbacks();
}

void Test_Renderer::OnSize(wxSizeEvent& evt)
{
	this->Refresh();
}

void Test_Renderer::sld_player_rotation_OnSlide(wxCommandEvent& evt)
{
	this->m_player.rotation = fxcg::degtorad(static_cast<float>(evt.GetInt()));
	this->Refresh();
}

void Test_Renderer::sld_player_x_OnSlide(wxCommandEvent& evt)
{
	this->m_player.position.GetX() = SliderToValue(evt.GetInt());
	this->Refresh();
}

void Test_Renderer::sld_player_y_OnSlide(wxCommandEvent& evt)
{
	this->m_player.position.GetY() = SliderToValue(evt.GetInt());
	this->Refresh();
}

Test_Renderer::Test_Renderer(wxWindow* parent) : wxPanel(parent)
{
	fxcg::GenerateWorld(this->m_world, fxcg::WORLD_GENERATOR);

	this->m_sizer = new wxGridBagSizer(0, 0);
	this->m_sizer->SetFlexibleDirection(wxBOTH);
	this->m_sizer->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	this->SetBackgroundColour(*wxWHITE);

	this->m_pnl_render = new wxPanel(this, wxID_ANY);
	this->m_pnl_render->Bind(wxEVT_PAINT, &Test_Renderer::OnPaint, this);
	this->m_pnl_render->Bind(wxEVT_SIZE, &Test_Renderer::OnSize, this);
	this->m_pnl_render->SetDoubleBuffered(true);
	this->m_sizer->Add(this->m_pnl_render, wxGBPosition(0, 0), wxGBSpan(1, 1), wxEXPAND | wxALL);
	
	this->m_sld_player_rotation = new wxSlider(this, wxID_ANY, static_cast<int>(fxcg::radtodeg(this->m_player.rotation)), 0, 360);
	this->m_sld_player_rotation->Bind(wxEVT_SLIDER, &Test_Renderer::sld_player_rotation_OnSlide, this);
	this->m_sizer->Add(this->m_sld_player_rotation, wxGBPosition(1, 0), wxGBSpan(1, 1), wxEXPAND | wxALL);

	this->m_sld_player_x = new wxSlider(this, wxID_ANY, ValueToSlider(this->m_player.position.GetX()), ValueToSlider(-1.0f), ValueToSlider(6.0f));
	this->m_sld_player_x->Bind(wxEVT_SLIDER, &Test_Renderer::sld_player_x_OnSlide, this);
	this->m_sizer->Add(this->m_sld_player_x, wxGBPosition(2, 0), wxGBSpan(1, 1), wxEXPAND | wxALL);

	this->m_sld_player_y = new wxSlider(this, wxID_ANY, ValueToSlider(this->m_player.position.GetY()), ValueToSlider(-1.0f), ValueToSlider(6.0f));
	this->m_sld_player_y->Bind(wxEVT_SLIDER, &Test_Renderer::sld_player_y_OnSlide, this);
	this->m_sizer->Add(this->m_sld_player_y, wxGBPosition(3, 0), wxGBSpan(1, 1), wxEXPAND | wxALL);

	this->m_sizer->AddGrowableCol(0);
	this->m_sizer->AddGrowableRow(0);

	this->SetSizer(this->m_sizer);
	this->Centre(wxBOTH);
	this->Layout();
}
