#include "DisplayWriting.h"

color_t* VRAM_ADDRESS;

void InitialiseVRAMAddress()
{
#if IS_TESTBED == 0
	VRAM_ADDRESS = reinterpret_cast<color_t*>(GetVRAMAddress());
#endif
}

void WriteToDisplay(int x, int y, color_t colour)
{
#if IS_TESTBED == 0
	VRAM_ADDRESS[(y * LCD_WIDTH_PX) + x] = colour;
#else
	Bdisp_SetPoint_VRAM(x, y, static_cast<int>(colour));
#endif
}
