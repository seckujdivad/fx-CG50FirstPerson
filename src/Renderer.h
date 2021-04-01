#pragma once

#include <fxcg/display.h>

#include "World.h"
#include "Player.h"

color_t GetColour(WorldRegion region);

template<unsigned int X, unsigned int Y>
inline void Render(const World<X, Y>& world, const Player& player)
{
	constexpr int BORDER_X = 20;
	constexpr int BORDER_Y = 20;
	constexpr int SCREEN_HEIGHT = LCD_HEIGHT_PX - (2 * BORDER_Y);
	constexpr float SCREEN_HEIGHT_FL = static_cast<float>(SCREEN_HEIGHT);

	for (int x = BORDER_X; x < LCD_WIDTH_PX - BORDER_X; x++)
	{
		float line_height = 0.5f;

		WorldRegion final_hit = WorldRegion::Black;
		color_t wall_colour = GetColour(final_hit);

		float casted_distance = 10.0f; //placeholder
		float resultant_height = 1.0f / casted_distance;
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
	
	Bdisp_PutDisp_DD();
}