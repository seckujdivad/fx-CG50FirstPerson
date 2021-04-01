#pragma once

#include <string.h>

#include "Vector.h"

enum class WorldRegion
{
	Air,
	OutOfRange,
	Black
};

WorldRegion GetWorldRegion(char world_region);

template<unsigned int X, unsigned int Y>
using World = WorldRegion[X][Y];

template<unsigned int X, unsigned int Y>
inline void GenerateWorld(World<X, Y>& target, const char* generator)
{
	size_t generator_len = strlen(generator);
	if (generator_len < (X * Y)) //generator not long enough - do not attempt
	{
		for (size_t x = 0; x < X; x++)
		{
			for (size_t y = 0; y < Y; y++)
			{
				target[x][y] = WorldRegion::Air;
			}
		}
	}
	else
	{
		for (size_t x = 0; x < X; x++)
		{
			for (size_t y = 0; y < Y; y++)
			{
				target[x][y] = GetWorldRegion(generator[(y * X) + x]);
			}
		}
	}

template<unsigned int X, unsigned int Y, typename T>
inline WorldRegion SampleFromWorld(const World<X, Y>& target, Vector<T, 2> sample)
{
	Vector<int, 2> position = 0;
	position.GetX() = static_cast<int>(sample.GetX());
	position.GetY() = static_cast<int>(sample.GetY());

	if ((position.GetX() < 0) || (position.GetX() >= static_cast<int>(X)) || (position.GetY() < 0) || (position.GetY() >= static_cast<int>(Y)))
	{
		return WorldRegion::OutOfRange;
	}
	else
	{
		return target[position.GetX()][position.GetY()];
	}
}
}