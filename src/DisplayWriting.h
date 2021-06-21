#pragma once

#if IS_TESTBED == 1
#include <display.h>
#else
#include <fxcg/display.h>
#endif

extern color_t* VRAM_ADDRESS;

void InitialiseVRAMAddress();

void WriteToDisplay(int x, int y, color_t colour);