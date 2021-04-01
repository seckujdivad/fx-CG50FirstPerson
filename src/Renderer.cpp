#include "Renderer.h"

color_t GetColour(WorldRegion region)
{
	switch (region)
	{
	case WorldRegion::Black: return COLOR_BLACK;
	default: return COLOR_PURPLE;
	}
}
