#pragma once

#include <fxcg/display.h>

#include "World.h"
#include "Player.h"

template<unsigned int X, unsigned int Y>
inline void Render(const World<X, Y>& world, const Player& player)
{
	for (int x = 10; x < 50; x++)
	{
		for (int y = 10; y < 50; y++)
		{
			Bdisp_SetPoint_VRAM(x, y, COLOR_BLACK);
		}
	}
	
	Bdisp_PutDisp_DD();
}