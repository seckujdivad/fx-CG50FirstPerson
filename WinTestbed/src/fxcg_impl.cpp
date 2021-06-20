#include "fxcg_impl.h"

std::vector<SetPoint_Callback> global_callbacks;

void Bdisp_SetPoint_VRAM_Inner(int x, int y, int colour)
{
	for (const SetPoint_Callback& callback : global_callbacks)
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

void AddCallback(SetPoint_Callback func)
{
	global_callbacks.push_back(func);
}

void ClearCallbacks()
{
	global_callbacks.clear();
}
