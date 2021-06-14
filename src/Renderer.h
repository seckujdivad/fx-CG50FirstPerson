#pragma once

#include <fxcg/display.h>

#include "World.h"
#include "WorldTracing.h"
#include "Player.h"
#include "Maths.h"

color_t GetColour(WorldRegion region);

template<unsigned int X, unsigned int Y>
inline void Render(const World<X, Y>& world, const Player& player)
{
	constexpr int BORDER_X = 20;
	constexpr int BORDER_Y = 20;
	constexpr int SCREEN_HEIGHT = LCD_HEIGHT_PX - (2 * BORDER_Y);
	constexpr float SCREEN_HEIGHT_FL = static_cast<float>(SCREEN_HEIGHT);

	constexpr float FOV = PI * 0.5f;
	constexpr float FOV_HALF = FOV * 0.5f;

	//anticlockwise
	float view_angle_start = player.rotation + FOV_HALF;
	float view_angle_end = player.rotation - FOV_HALF;

	for (int x = BORDER_X; x < LCD_WIDTH_PX - BORDER_X; x++)
	{
		float view_angle_frac = static_cast<float>(x - BORDER_X) / static_cast<float>(LCD_WIDTH_PX - (2 * BORDER_X));
		float view_angle = mix(view_angle_start, view_angle_end, view_angle_frac);

		WorldIntersection intersection = FindFirstIntersection(world, player.position, view_angle);
		Vector<float, 2> view_ray = intersection.position - player.position;

		color_t wall_colour = GetColour(intersection.region);

		float resultant_height;
		if ((fabs(view_ray.GetX()) < 0.01f) && (fabs(view_ray.GetY()) < 0.01f))
		{
			resultant_height = 1.0f;
		}
		else
		{
			resultant_height = view_ray.InverseLength();
		}
		
		int wall_inset = static_cast<int>((1.0f - resultant_height) * SCREEN_HEIGHT_FL * 0.5f);

		for (int y = BORDER_Y; y < LCD_HEIGHT_PX - BORDER_Y; y++)
		{
			color_t colour = COLOR_RED;
			if (y < BORDER_Y + wall_inset)
			{
				colour = COLOR_GREEN;
			}
			else if (y > LCD_HEIGHT_PX - BORDER_Y - wall_inset)
			{
				colour = COLOR_BLUE;
			}
			else
			{
				colour = wall_colour;
			}
			Bdisp_SetPoint_VRAM(x, y, colour);
		}
	}
}