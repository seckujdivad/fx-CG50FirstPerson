#include "fxcg_impl.h"

std::vector<SetPoint_Callback> global_callbacks_setone;
std::vector<SetTwo_Callback> global_callbacks_settwo;

void Bdisp_SetPoint_VRAM_Inner(int x, int y, int colour)
{
	for (const SetPoint_Callback& callback : global_callbacks_setone)
	{
		callback(x, y, colour);
	}
}

extern "C" {
	void Bdisp_SetPoint_VRAM(int x, int y, int colour)
	{
		Bdisp_SetPoint_VRAM_Inner(x, y, colour);
	}
}

namespace fxcg
{
	void WritePixelPair(int x, int y, unsigned short colour_first, unsigned short colour_second)
	{
		for (const SetTwo_Callback& callback : global_callbacks_settwo)
		{
			callback(x, y, colour_first, colour_second);
		}
	}
}

void AddCallback(SetPoint_Callback func)
{
	global_callbacks_setone.push_back(func);
}

void AddCallback(SetTwo_Callback func)
{
	global_callbacks_settwo.push_back(func);
}

void ClearCallbacks()
{
	global_callbacks_setone.clear();
	global_callbacks_settwo.clear();
}
