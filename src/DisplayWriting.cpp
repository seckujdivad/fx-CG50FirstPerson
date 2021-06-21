#include "DisplayWriting.h"

using two_col_t = unsigned int;
constexpr int ROW_WIDTH = LCD_WIDTH_PX / 2;

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

void WritePixelPair(int x, int y, color_t colour)
{
#if IS_TESTBED == 0
	two_col_t* VRAM_INTS = reinterpret_cast<two_col_t*>(VRAM_ADDRESS);
	VRAM_INTS[(y * ROW_WIDTH) + (x / 2)] = (static_cast<two_col_t>(colour) << 16) | static_cast<two_col_t>(colour);
#else
	WritePixelPair(x, y, colour, colour);
#endif
}

void WritePixelPair(int x, int y, color_t colour_first, color_t colour_second)
{
#if IS_TESTBED == 0
	two_col_t* VRAM_INTS = reinterpret_cast<two_col_t*>(VRAM_ADDRESS);
	VRAM_INTS[(y * ROW_WIDTH) + (x / 2)] = (static_cast<two_col_t>(colour_first) << 16) | static_cast<two_col_t>(colour_second);
#else
	int x_first = (x & 2 == 0) ? x : x - 1;
	Bdisp_SetPoint_VRAM(x_first, y, static_cast<int>(colour_first));
	Bdisp_SetPoint_VRAM(x_first + 1, y, static_cast<int>(colour_second));
#endif
}
