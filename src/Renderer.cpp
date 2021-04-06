#include "Renderer.h"

color_t GetColour(WorldRegion region)
{
	switch (region)
	{
	case WorldRegion::Black: return COLOR_BLACK;
	case WorldRegion::OutOfRange: return COLOR_ORANGE;
	case WorldRegion::Error: return COLOR_BROWN;
	default: return COLOR_PURPLE;
	}
}
