#pragma once

#include <string.h>

#include "Vector.h"
#include "Maths.h"

#define ITERATIVE_TRACE 0

enum class WorldRegion
{
	Air,
	OutOfRange,
	Error,
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
	return SampleFromWorld(target, static_cast<int>(sample.GetX()), static_cast<int>(sample.GetY()));
}

template<unsigned int X, unsigned int Y>
inline WorldRegion SampleFromWorld(const World<X, Y>& target, int x, int y)
{
	if ((x < 0) || (x >= static_cast<int>(X)) || (y < 0) || (y >= static_cast<int>(Y)))
	{
		return WorldRegion::OutOfRange;
	}
	else
	{
		return target[x][y];
	}
}

struct BoxIntersection
{
	float entry_lambda = 0.0f;
	float exit_lambda = 0.0f;
	bool has_values = false;
};

BoxIntersection FindIntersection(Vector<float, 2> start_pos, Vector<float, 2> unit_direction, int box_x, int box_y);

struct WorldIntersection
{
	WorldIntersection(Vector<float, 2> position, WorldRegion region);

	Vector<float, 2> position;
	WorldRegion region;
};

template<unsigned int X, unsigned int Y>
inline WorldIntersection FindFirstIntersection(const World<X, Y>& world, Vector<float, 2> start_pos, float angle)
{
	Vector<float, 2> unit_direction;
	unit_direction.GetX() = cos(angle);
	unit_direction.GetY() = sin(angle);

#if ITERATIVE_TRACE == 1
	float lambda = 0.0f;
	constexpr float lambda_increment = 0.05f;
	constexpr float max_lambda = 10.0f;

	WorldRegion current_region = WorldRegion::Air;
	Vector<float, 2> current_pos = start_pos;

	while (lambda < max_lambda && current_region == WorldRegion::Air)
	{
		lambda += lambda_increment;

		current_pos = (unit_direction * lambda) + start_pos;
		current_region = SampleFromWorld(world, current_pos);
	}

	return WorldIntersection(current_pos, current_region);

#else

	const int major = (fabs(unit_direction.GetX()) > fabs(unit_direction.GetY())) ? 0 : 1;
	const int minor = (major + 1) % 2;

	constexpr int DIMENSIONS_TABLE[2] = { X, Y };

	const int inc_minor = ispositive(unit_direction[minor]) ? 1 : -1;
	const int inc_major = ispositive(unit_direction[major]) ? 1 : -1;

	const Comparison minor_comparison = ispositive(inc_minor) ? Comparison::LessThanEqual : Comparison::GreaterThanEqual;
	const Comparison major_comparison = ispositive(inc_major) ? Comparison::LessThanEqual : Comparison::GreaterThanEqual;

	const int start_minor = static_cast<int>(round_direction(start_pos[minor], !ispositive(inc_minor)));
	const int end_minor = ispositive(unit_direction[minor]) ? DIMENSIONS_TABLE[minor] - 1 : 0;

	int start_major = static_cast<int>(round_direction(start_pos[major], !ispositive(inc_major)));

	//adapted dda
	for (int current_minor = start_minor; compare(current_minor, end_minor, minor_comparison); current_minor += inc_minor)
	{
		const float end_lambda = (static_cast<float>(current_minor + inc_minor) - start_pos[minor]) / unit_direction[minor];
		const float end_major_fl = (end_lambda * unit_direction[major]) + start_pos[major];
		int end_major = static_cast<int>(round_direction(end_major_fl, ispositive(inc_major)));

		//clamp to range
		end_major = clamp(end_major, -1, DIMENSIONS_TABLE[major]);
		
		for (int current_major = start_major; compare(current_major, end_major, major_comparison); current_major += inc_major)
		{
			int sampler[2] = { 0, 0 };
			sampler[major] = current_major;
			sampler[minor] = current_minor;

			const WorldRegion current_region = SampleFromWorld(world, sampler[0], sampler[1]);

			if (current_region != WorldRegion::Air)
			{
				const BoxIntersection intersections = FindIntersection(start_pos, unit_direction, sampler[0], sampler[1]);
				if (intersections.has_values)
				{
					return WorldIntersection((unit_direction * intersections.entry_lambda) + start_pos, current_region);
				}
				else
				{
					Vector<float, 2> pos;
					pos.GetX() = static_cast<float>(sampler[0]);
					pos.GetY() = static_cast<float>(sampler[1]);
					return WorldIntersection(pos, WorldRegion::Error);
				}
			}
		}
		start_major = end_major;
	}

	return WorldIntersection(start_pos, WorldRegion::Air);
#endif
}