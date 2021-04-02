#include <fxcg/display.h>
#include <fxcg/keyboard.h>

#include "World.h"
#include "Renderer.h"
#include "Player.h"
#include "Maths.h"

int main()
{
	Bdisp_AllClr_VRAM();

	World<5, 5> world = {};
	GenerateWorld(world,
		"OOXOO"
		"OOOOO"
		"XOOOX"
		"OOOOO"
		"OOXOO"
	);

	Player player;
	player.position = Vector<float, 2>(2.5f);
	player.rotation = 0.0f;

	while (true)
	{
		Render(world, player);

		{
			int rot_perc_x = LCD_WIDTH_PX * (player.rotation / (2.0f * PI));
			for (int x = 0; x < LCD_WIDTH_PX; x++)
			{
				color_t colour = COLOR_WHITE;
				if (x < rot_perc_x)
				{
					colour = COLOR_BLACK;
				}
				Bdisp_SetPoint_VRAM(x, LCD_HEIGHT_PX - 5, colour);
			}
		}

		Bdisp_PutDisp_DD();

		int key;
		GetKey(&key);

		if (key == KEY_CHAR_4)
		{
			player.rotation += 0.25f;
		}
		else if (key == KEY_CHAR_6)
		{
			player.rotation -= 0.25f;
		}
		else if ((key == KEY_CHAR_8) || (key == KEY_CHAR_2))
		{
			Vector<float, 2> increment = 0.0f;
			increment.GetX() = cos(player.rotation);
			increment.GetY() = sin(player.rotation);

			increment *= 0.25f;

			if (key == KEY_CHAR_2)
			{
				increment *= -1.0f;
			}

			player.position += increment;
		}
		else if (key == KEY_CHAR_0)
		{
			player.position = Vector<float, 2>(2.5f);
			player.rotation = 0.0f;
		}

		player.rotation = fmod(player.rotation, PI * 2.0f);
	}

	return 0;
}
