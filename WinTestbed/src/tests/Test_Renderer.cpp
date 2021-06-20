#include "Test_Renderer.h"

#include <stdexcept>

#include <wx/dcbuffer.h>

#include "../fxcg_impl.h"

void Test_Renderer::OnPaint(wxPaintEvent& evt)
{
	wxBufferedPaintDC paint_dc = wxBufferedPaintDC(this);
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

Test_Renderer::Test_Renderer(wxWindow* parent) : wxPanel(parent)
{
	fxcg::GenerateWorld(this->m_world, fxcg::WORLD_GENERATOR);

	this->SetBackgroundColour(*wxWHITE);

	this->SetDoubleBuffered(true);

	this->Bind(wxEVT_PAINT, &Test_Renderer::OnPaint, this);
	this->Bind(wxEVT_SIZE, &Test_Renderer::OnSize, this);

	this->Centre(wxBOTH);
	this->Layout();
}
