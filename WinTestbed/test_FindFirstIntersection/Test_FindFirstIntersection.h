#pragma once

#include <wx/panel.h>

namespace fxcg
{
#include "World.h"
#include "WorldTracing.h"
#include "Maths.h"
}

class Test_FindFirstIntersection : public wxPanel
{
private:
	fxcg::World<5, 5> m_world;

	fxcg::Vector<float, 2> m_position;
	float m_angle = 0.0f;
	
	void OnPaint(wxPaintEvent& evt);
	void OnSize(wxSizeEvent& evt);
	void OnMotion(wxMouseEvent& evt);

public:
	Test_FindFirstIntersection(wxWindow* parent);
};