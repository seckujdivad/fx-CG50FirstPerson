#pragma once

#include <wx/panel.h>

#include "../fxcg.h"

class wxGridBagSizer;

class Test_Renderer : public wxPanel
{
private:
	fxcg::World<5, 5> m_world;

	fxcg::Player m_player = fxcg::PLAYER_INITIAL;

	wxGridBagSizer* m_sizer;
	wxPanel* m_pnl_render;
	wxSlider* m_sld_player_rotation;
	wxSlider* m_sld_player_x;
	wxSlider* m_sld_player_y;

	void OnPaint(wxPaintEvent& evt);
	void OnSize(wxSizeEvent& evt);

	void sld_player_rotation_OnSlide(wxCommandEvent& evt);
	void sld_player_x_OnSlide(wxCommandEvent& evt);
	void sld_player_y_OnSlide(wxCommandEvent& evt);

public:
	Test_Renderer(wxWindow* parent);
};