#pragma once

#ifdef _WIN32
#include <display.h>
#else
#include <fxcg/display.h>
#endif

#include "World.h"
#include "WorldTracing.h"
#include "Player.h"
#include "Maths.h"
#include "Sprite.h"

color_t GetColour(WorldRegion region);

template<unsigned int X, unsigned int Y>
inline void Render(const World<X, Y>& world, const Player& player, const Sprite* sprites, size_t num_sprites)
{
	constexpr int BORDER_X = 20;
	constexpr int BORDER_Y = 20;

	constexpr int SCREEN_HEIGHT = LCD_HEIGHT_PX - (2 * BORDER_Y);
	constexpr int SCREEN_WIDTH = LCD_WIDTH_PX - (2 * BORDER_X);
	
	constexpr float SCREEN_HEIGHT_FL = static_cast<float>(SCREEN_HEIGHT);

	constexpr float FOV = PI<float> * 0.5f;
	constexpr float FOV_HALF = FOV * 0.5f;

	float screen_inv_distances[SCREEN_WIDTH] = {};

	//anticlockwise
	float view_angle_start = player.rotation + FOV_HALF;
	float view_angle_end = player.rotation - FOV_HALF;

	for (int x = BORDER_X; x < LCD_WIDTH_PX - BORDER_X; x++)
	{
		const float view_angle_frac = static_cast<float>(x - BORDER_X) / static_cast<float>(LCD_WIDTH_PX - (2 * BORDER_X));
		const float view_angle = mix(view_angle_start, view_angle_end, view_angle_frac);

		const WorldIntersection intersection = FindFirstIntersection(world, player.position, view_angle);
		const Vector<float, 2> view_ray = intersection.position - player.position;

		const color_t wall_colour = GetColour(intersection.region);

		const float inverse_distance = ((fabs(view_ray.GetX()) < 0.01f) && (fabs(view_ray.GetY()) < 0.01f))
			? (1.0f / 0.01f)
			: view_ray.InverseLength();
		screen_inv_distances[x - BORDER_X] = inverse_distance;
		
		const int wall_inset = static_cast<int>((1.0f - inverse_distance) * SCREEN_HEIGHT_FL * 0.5f);

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

	for (size_t i = 0; i < num_sprites; i++)
	{
		const Sprite& sprite = sprites[i];

		const Vector<float, 2> sprite_diff = sprite.GetPosition() - player.position;
		const float inverse_distance = sprite_diff.InverseLength();

		const int sprite_width = sprite.GetScale().GetX() * sprite.GetDimensions().GetX();
		const float sprite_angle_width_half = static_cast<float>(sprite_width) * inverse_distance * FOV_HALF;

		const float sprite_angle = sprite_diff.GetAngle();
		const float sprite_angle_diff = sprite_angle - player.rotation;

		const float sprite_start_angle = sprite_angle_diff - sprite_angle_width_half;
		const float sprite_end_angle = sprite_angle_diff + sprite_angle_width_half;

		const float sprite_view_frac_start = (sprite_start_angle + FOV_HALF) / FOV;
		const float sprite_view_frac_end = (sprite_end_angle + FOV_HALF) / FOV;

		const int start_x = BORDER_X + static_cast<int>(sprite_view_frac_start * (LCD_WIDTH_PX - (2 * BORDER_X)));
		const int end_x = BORDER_X + static_cast<int>(sprite_view_frac_end * (LCD_WIDTH_PX - (2 * BORDER_X)));

		if ((end_x > BORDER_X) && (start_x < LCD_WIDTH_PX - BORDER_X))
		{
			const int sprite_height = sprite.GetScale().GetY() * sprite.GetDimensions().GetY();
			const float sprite_angle_height_half = static_cast<float>(sprite_height) * inverse_distance * FOV_HALF;
			const int sprite_px_height = static_cast<int>(sprite_angle_height_half * (LCD_HEIGHT_PX - (2 * BORDER_Y)));
			const int sprite_height_extra_padding = min((LCD_HEIGHT_PX - (2 * BORDER_Y) - sprite_px_height) / 2, ((LCD_HEIGHT_PX - (2 * BORDER_Y)) / 2) - 1);

			const int start_x_iteration = max(start_x, BORDER_X);
			const int end_x_iteration = min(end_x, LCD_WIDTH_PX - BORDER_X);

			const int start_y = BORDER_Y + sprite_height_extra_padding;
			const int end_y = LCD_HEIGHT_PX - BORDER_Y - sprite_height_extra_padding;

			if ((end_y > BORDER_Y) && (start_y < LCD_HEIGHT_PX - BORDER_Y))
			{
				const int start_y_iteration = max(start_y, BORDER_Y);
				const int end_y_iteration = min(end_y, LCD_HEIGHT_PX - BORDER_Y);

				for (int x = start_x_iteration; x < end_x_iteration; x++)
				{
					if (screen_inv_distances[x - BORDER_X] < inverse_distance)
					{
						screen_inv_distances[x - BORDER_X] = inverse_distance;

						Vector<int, 2> sprite_texel = Vector<int, 2>(0, 0);

						float sprite_frac_x = static_cast<float>(x - start_x) / static_cast<float>(end_x - start_x);
						sprite_texel.GetX() = static_cast<int>(sprite_frac_x * sprite.GetDimensions().GetX());
						for (int y = start_y_iteration; y < end_y_iteration; y++)
						{
							float sprite_frac_y = static_cast<float>(y - start_y) / static_cast<float>(end_y - start_y);
							sprite_texel.GetY() = static_cast<int>(sprite_frac_y * sprite.GetDimensions().GetY());

							if (AccessMatrix(sprite_texel, sprite.GetAlphaMask(), sprite.GetDimensions().GetY()))
							{
								color_t pixel_colour = AccessMatrix(sprite_texel, sprite.GetRawData(), sprite.GetDimensions().GetY());
								Bdisp_SetPoint_VRAM(x, y, pixel_colour);
							}
						}
					}
				}
			}
		}
	}
}