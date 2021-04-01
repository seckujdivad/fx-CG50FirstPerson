#include <fxcg/display.h>
#include <fxcg/keyboard.h>

#include "World.h"
#include "Renderer.h"
#include "Player.h"

int main()
{
	Bdisp_AllClr_VRAM();
	Print_OS("Press EXE to exit", 0, 0);

	World<5, 5> world = {};
	GenerateWorld(world,
		"OOOOO"
		"OOXOO"
		"OXOXO"
		"OOOOO"
		"OOXOO"
	);

	Player player = { Vector<float, 2>(2.5f), 0.0f };

	Render(world, player);

	while (true)
	{
		int key;
		GetKey(&key);

		if (key == KEY_CTRL_EXE) {
			break;
		}
	}

	return 0;
}
