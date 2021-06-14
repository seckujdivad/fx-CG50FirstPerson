#include "World.h"

WorldRegion GetWorldRegion(char world_region)
{
	switch (world_region)
	{
	case 'X': return WorldRegion::Black;
	default: return WorldRegion::Air;
	}
}