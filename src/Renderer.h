#pragma once

#include "DisplayWriting.h"
#include "World.h"
#include "WorldTracing.h"
#include "Player.h"
#include "Maths.h"
#include "Sprite.h"

color_t GetColour(WorldRegion region);

template<unsigned int X, unsigned int Y>
inline void Render(const World<X, Y>& world, const Player& player, const Sprite* sprites, size_t num_sprites)
{
	constexpr int BORDER_X[] = { 0, 0 };
	constexpr int BORDER_Y[] = { 23 + 5, 1 }; //23 px for the status bar plus a 5 px border

	constexpr int SCREEN_HEIGHT = LCD_HEIGHT_PX - (BORDER_Y[0] + BORDER_Y[1]);
	constexpr int SCREEN_WIDTH = LCD_WIDTH_PX - (BORDER_X[0] + BORDER_X[1]);
	
	constexpr float SCREEN_HEIGHT_FL = static_cast<float>(SCREEN_HEIGHT);

	constexpr float FOV = PI<float> * 0.5f;
	constexpr float FOV_HALF = FOV * 0.5f;
	constexpr float VIEW_ANGLE_INCREMENT = FOV / static_cast<float>(SCREEN_WIDTH);

	float screen_inv_distances[SCREEN_WIDTH] = {};
	color_t wall_colours[SCREEN_WIDTH] = {};

	float view_angle = player.rotation + FOV_HALF;
	for (int x = BORDER_X[0]; x < LCD_WIDTH_PX - BORDER_X[1]; x++)
	{
		const WorldIntersection intersection = FindFirstIntersection(world, player.position, view_angle);
		const Vector<float, 2> view_ray = intersection.position - player.position;

		wall_colours[x - BORDER_X[0]] = GetColour(intersection.region);

		screen_inv_distances[x - BORDER_X[0]] = ((fabs(view_ray.GetX()) < 0.01f) && (fabs(view_ray.GetY()) < 0.01f))
			? (1.0f / 0.01f)
			: view_ray.InverseLength();

		view_angle -= VIEW_ANGLE_INCREMENT;
	}

	for (int x = BORDER_X[0]; x < LCD_WIDTH_PX - BORDER_X[1]; x += 2)
	{
		const int wall_inset_first = static_cast<int>((1.0f - screen_inv_distances[x - BORDER_X[0]]) * SCREEN_HEIGHT_FL * 0.5f);
		const int wall_inset_second = static_cast<int>((1.0f - screen_inv_distances[x - BORDER_X[0] + 1]) * SCREEN_HEIGHT_FL * 0.5f);

		const color_t wall_colour_first = wall_colours[x - BORDER_X[0]];
		const color_t wall_colour_second = wall_colours[x - BORDER_X[0] + 1];

		for (int y = BORDER_Y[0]; y < LCD_HEIGHT_PX - BORDER_Y[1]; y++)
		{
			const color_t colour_first = (y < BORDER_Y[0] + wall_inset_first) ? COLOR_GREEN
				: ((y > LCD_HEIGHT_PX - BORDER_Y[1] - wall_inset_first) ? COLOR_BLUE : wall_colour_first);
			
			const color_t colour_second = (y < BORDER_Y[0] + wall_inset_second) ? COLOR_GREEN
				: ((y > LCD_HEIGHT_PX - BORDER_Y[1] - wall_inset_second) ? COLOR_BLUE : wall_colour_second);

			WritePixelPair(x, y, colour_first, colour_second);
		}
	}

	for (size_t i = 0; i < num_sprites; i++)
	{
		const Sprite& sprite = sprites[i];

		const Vector<float, 2> sprite_diff = sprite.GetPosition() - player.position;
		const float inverse_distance = sprite_diff.InverseLength();

		const int sprite_width = sprite.GetScale().GetX() * sprite.GetDimensions().GetX();
		const float sprite_angle_width_half = static_cast<float>(sprite_width) * inverse_distance * (FOV_HALF / LCD_WIDTH_PX);

		const float sprite_angle = sprite_diff.GetAngle();
		const float sprite_angle_diff = player.rotation - sprite_angle;

		const float sprite_start_angle = sprite_angle_diff - sprite_angle_width_half;
		const float sprite_end_angle = sprite_angle_diff + sprite_angle_width_half;

		const float sprite_view_frac_start = (sprite_start_angle + FOV_HALF) / FOV;
		const float sprite_view_frac_end = (sprite_end_angle + FOV_HALF) / FOV;

		const int start_x = BORDER_X[0] + static_cast<int>(sprite_view_frac_start * SCREEN_WIDTH);
		const int end_x = BORDER_X[0] + static_cast<int>(sprite_view_frac_end * SCREEN_WIDTH);

		if ((end_x > BORDER_X[0]) && (start_x < LCD_WIDTH_PX - BORDER_X[1]))
		{
			const int sprite_height = sprite.GetScale().GetY() * sprite.GetDimensions().GetY();
			const float sprite_angle_height_half = static_cast<float>(sprite_height) * inverse_distance * (FOV_HALF / LCD_HEIGHT_PX);
			const int sprite_px_height = static_cast<int>(sprite_angle_height_half * SCREEN_HEIGHT);
			const int sprite_height_extra_padding = min((SCREEN_HEIGHT - sprite_px_height) / 2, (SCREEN_HEIGHT / 2) - 1);

			const int start_x_iteration = max(start_x, BORDER_X[0]);
			const int end_x_iteration = min(end_x, LCD_WIDTH_PX - BORDER_X[1]);

			const int start_y = BORDER_Y[0] + sprite_height_extra_padding;
			const int end_y = LCD_HEIGHT_PX - BORDER_Y[1] - sprite_height_extra_padding;

			if ((end_y > BORDER_Y[0]) && (start_y < LCD_HEIGHT_PX - BORDER_Y[1]))
			{
				const int start_y_iteration = max(start_y, BORDER_Y[0]);
				const int end_y_iteration = min(end_y, LCD_HEIGHT_PX - BORDER_Y[1]);

				for (int x = start_x_iteration; x < end_x_iteration; x++)
				{
					if (screen_inv_distances[x - BORDER_X[0]] < inverse_distance)
					{
						screen_inv_distances[x - BORDER_X[0]] = inverse_distance;

						Vector<int, 2> sprite_texel = Vector<int, 2>(0, 0);

						const float sprite_frac_x = static_cast<float>(x - start_x) / static_cast<float>(end_x - start_x);
						sprite_texel.GetX() = static_cast<int>(sprite_frac_x * sprite.GetDimensions().GetX());
						for (int y = start_y_iteration; y < end_y_iteration; y++)
						{
							const float sprite_frac_y = static_cast<float>(y - start_y) / static_cast<float>(end_y - start_y);
							sprite_texel.GetY() = static_cast<int>(sprite_frac_y * sprite.GetDimensions().GetY());

							if (AccessMatrix(sprite_texel, sprite.GetAlphaMask(), sprite.GetDimensions().GetY()))
							{
								WriteToDisplay(x, y, AccessMatrix(sprite_texel, sprite.GetRawData(), sprite.GetDimensions().GetY()));
							}
						}
					}
				}
			}
		}
	}
}