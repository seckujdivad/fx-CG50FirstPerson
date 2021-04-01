#include <fxcg/display.h>
#include <fxcg/keyboard.h>

#include "World.h"

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
