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

		int key;
		GetKey(&key);

		if (key == KEY_CHAR_4)
		{
			player.rotation -= 0.25f;
			Print_OS("-", 0, 0);
		}
		else if (key == KEY_CHAR_6)
		{
			player.rotation += 0.25f;
			Print_OS("+", 0, 0);
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
	}

	return 0;
}
