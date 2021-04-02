#pragma once

#include <string.h>

#include "Vector.h"
#include "Maths.h"

#define TRACE_MODE_ITERATIVE 0

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
	const size_t generator_len = strlen(generator);
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

template<unsigned int X, unsigned int Y>
inline Vector<float, 2> FindFirstIntersection(const World<X, Y>& world, Vector<float, 2> start_pos, float angle)
{
	Vector<float, 2> unit_direction;
	unit_direction.GetX() = cos(angle);
	unit_direction.GetY() = sin(angle);

#if TRACE_MODE_ITERATIVE == 1
	float unit_direction_scale = 0.4f;
	Vector<float, 2> unit_direction_scaled = unit_direction * 0.1f;
#endif

	Vector<float, 2> current_pos = start_pos;
	WorldRegion current_region = SampleFromWorld(world, current_pos);
	while (current_region == WorldRegion::Air)
	{
#if TRACE_MODE_ITERATIVE == 1
		current_pos += unit_direction_scaled;
		current_region = SampleFromWorld(world, current_pos);

		if ((current_region != WorldRegion::Air) && (unit_direction_scale > 0.005f))
		{
			current_pos -= unit_direction_scaled;
			unit_direction_scale /= 2.0f;
			unit_direction_scaled = unit_direction * unit_direction_scale;
			current_region = SampleFromWorld(world, current_pos);
		}
#else
		/*
		* calculate end positions if moving one cell in X or Y
		* find the shorter segment and keep that one
		*/

		bool move_is_valid[2] = { false, false };
		Vector<float, 2> move_position[2] = { 0.0f, 0.0f };

		for (int i = 0; i < 2; i++)
		{
			int other_index = (i + 1) % 2;
			if (unit_direction[i] == 0.0f)
			{
				move_is_valid[i] = false;
			}
			else
			{
				move_is_valid[i] = true;

				float move_increment = unit_direction[i];
				move_position[i][i] = floor(current_pos[i] + copysign(1.0f, move_increment));

				float lambda = (move_position[i][i] - start_pos[i]) / unit_direction[i];
				move_position[i][other_index] = (lambda * unit_direction[other_index]) + start_pos[other_index];
			}
		}

		if (!move_is_valid[0])
		{
			current_pos = move_position[1];
		}
		else if (!move_is_valid[1])
		{
			current_pos = move_position[0];
		}
		else
		{
			Vector<float, 2> move_vecs[2];
			move_vecs[0] = move_position[0] - current_pos;
			move_vecs[1] = move_position[1] - current_pos;
			if (move_vecs[0].Length() > move_vecs[1].Length()) //TODO: switch to more performant inverse length
			{
				current_pos = move_position[1];
			}
			else
			{
				current_pos = move_position[0];
			}
		}

		current_region = SampleFromWorld(world, current_pos);
#endif
	}

	return current_pos;
}