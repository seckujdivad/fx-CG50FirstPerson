#include "Renderer.h"

color_t GetColour(WorldRegion region)
{
	switch (region)
	{
	case WorldRegion::Black: return COLOR_BLACK;
	case WorldRegion::OutOfRange: return COLOR_ORANGE;
	default: return COLOR_PURPLE;
	}
}
