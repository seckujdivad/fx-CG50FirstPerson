#pragma once

#include <functional>

using SetPoint_Callback = std::function<void(int, int, int)>;
void AddCallback(SetPoint_Callback func);
void ClearCallbacks();