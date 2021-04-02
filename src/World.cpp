#include "World.h"

WorldRegion GetWorldRegion(char world_region)
{
	switch (world_region)
	{
	case 'X': return WorldRegion::Black;
	default: return WorldRegion::Air;
	}
}

WorldIntersection::WorldIntersection(Vector<float, 2> position, WorldRegion region) : position(position), region(region)
{
}
