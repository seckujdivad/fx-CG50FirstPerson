#pragma once

#include <wx/panel.h>

#include "../fxcg.h"

class Test_Renderer : public wxPanel
{
private:
	fxcg::World<5, 5> m_world;

	fxcg::Player m_player = fxcg::PLAYER_INITIAL;

	void OnPaint(wxPaintEvent& evt);
	void OnSize(wxSizeEvent& evt);

public:
	Test_Renderer(wxWindow* parent);
};