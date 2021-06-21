#pragma once

#if IS_TESTBED == 1
#include <display.h>
#else
#include <fxcg/display.h>
#endif

extern color_t* VRAM_ADDRESS;

void InitialiseVRAMAddress();

void WriteToDisplay(int x, int y, color_t colour);

//write to two x-adjacent pixels. first pixel must be aligned to a multiple of 2 in x
//the calculator is 32-bit, so this should write to VRAM just as fast as writing one pixel on its own (or as close to just as fast as makes no difference)
//this gives a potential 2x speed increase to fill rate
void WritePixelPair(int x, int y, color_t colour);
void WritePixelPair(int x, int y, color_t colour_first, color_t colour_second);