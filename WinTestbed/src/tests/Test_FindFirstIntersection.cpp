#include "Test_FindFirstIntersection.h"

#include <wx/dcbuffer.h>

void Test_FindFirstIntersection::OnPaint(wxPaintEvent& evt)
{
	wxBufferedPaintDC paint_dc = wxBufferedPaintDC(this);

	paint_dc.SetBackground(*wxWHITE_BRUSH);
	paint_dc.Clear();

	wxSize region_size = this->GetSize();
	float scale_x = static_cast<float>(region_size.GetX()) / 5.0f;
	float scale_y = static_cast<float>(region_size.GetY()) / 5.0f;

	//draw world
	{
		paint_dc.SetPen(*wxBLACK_PEN);

		for (int x = 0; x < 5; x++)
		{
			for (int y = 0; y < 5; y++)
			{
				fxcg::WorldRegion region = this->m_world[x][y];
				if (region == fxcg::WorldRegion::Air)
				{
					paint_dc.SetBrush(*wxWHITE_BRUSH);
				}
				else
				{
					paint_dc.SetBrush(*wxRED_BRUSH);
				}

				wxRect to_draw = wxRect(scale_x * x, scale_y * y, scale_x * (x + 1), scale_y * (y + 1));
				paint_dc.DrawRectangle(to_draw);
			}
		}
	}

	//draw player
	{
		wxSize region_size = this->GetSize();
		paint_dc.DrawCircle(wxPoint(this->m_position.GetX() * region_size.GetX() / 5.0f, this->m_position.GetY() * region_size.GetY() / 5.0f), 5);
	}

	//find final intersection
	{
		fxcg::WorldIntersection intersection = fxcg::FindFirstIntersection(this->m_world, this->m_position, this->m_angle);
		wxPoint int_point = wxPoint(intersection.position.GetX() * scale_x, intersection.position.GetY() * scale_y);
		paint_dc.DrawCircle(int_point, 5);

		paint_dc.DrawText("Angle: " + std::to_string((intersection.position - this->m_position).GetAngle()), wxPoint(4, 1));
	}
}

void Test_FindFirstIntersection::OnSize(wxSizeEvent& evt)
{
	this->Refresh();
}

void Test_FindFirstIntersection::OnMotion(wxMouseEvent& evt)
{
	if (evt.LeftIsDown())
	{
		wxSize win_size = this->GetSize();
		wxPoint mouse_pos = evt.GetPosition();
		this->m_position.GetX() = 5.0f * static_cast<float>(mouse_pos.x) / static_cast<float>(win_size.GetX());
		this->m_position.GetY() = 5.0f * static_cast<float>(mouse_pos.y) / static_cast<float>(win_size.GetY());

		this->Refresh();
	}

	if (evt.RightIsDown())
	{
		wxSize win_size = this->GetSize();
		wxPoint mouse_pos = evt.GetPosition();
		fxcg::Vector<float, 2> click_pos;
		click_pos.GetX() = 5.0f * static_cast<float>(mouse_pos.x) / static_cast<float>(win_size.GetX());
		click_pos.GetY() = 5.0f * static_cast<float>(mouse_pos.y) / static_cast<float>(win_size.GetY());

		fxcg::Vector<float, 2> angle_vec = click_pos - this->m_position;
		angle_vec *= angle_vec.InverseLength();
		this->m_angle = acos(angle_vec.GetX());
		if (angle_vec.GetY() < 0.0f)
		{
			this->m_angle = (2.0f * fxcg::PI<>) - this->m_angle;
		}

		this->Refresh();
	}

	evt.Skip();
}

Test_FindFirstIntersection::Test_FindFirstIntersection(wxWindow* parent) : wxPanel(parent)
{
	fxcg::GenerateWorld(this->m_world, fxcg::WORLD_GENERATOR);

	this->SetBackgroundColour(*wxWHITE);

	this->SetDoubleBuffered(true);

	this->Bind(wxEVT_PAINT, &Test_FindFirstIntersection::OnPaint, this);
	this->Bind(wxEVT_SIZE, &Test_FindFirstIntersection::OnSize, this);
	this->Bind(wxEVT_MOTION, &Test_FindFirstIntersection::OnMotion, this);

	this->Centre(wxBOTH);
	this->Layout();
}
