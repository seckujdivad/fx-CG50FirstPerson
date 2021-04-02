#pragma once

#include <string.h>

#include "Vector.h"
#include "Maths.h"

#define TRACE_MODE_ITERATIVE 1

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
		enum class Direction
		{
			Dir_X,
			Dir_Y
		} direction = Direction::Dir_X;
		if (unit_direction.GetX() == 0.0f)
		{
			direction = Direction::Dir_Y;
		}
		else if (unit_direction.GetY() == 0.0f)
		{
			direction = Direction::Dir_X;
		}
		else
		{
			float target_x = ceil(current_pos.GetX());
			float target_y = ceil(current_pos.GetY());

			float x_lambda_increment = fabs(target_x / unit_direction.GetX());
			float y_lambda_increment = fabs(target_y / unit_direction.GetY());

			if (x_lambda_increment > y_lambda_increment)
			{
				direction = Direction::Dir_Y;
			}
			else
			{
				direction = Direction::Dir_X;
			}
		}

		if (direction == Direction::Dir_X)
		{
			float target_x = floor(current_pos.GetX());
			if (target_x == current_pos.GetX())
			{
				target_x += ispositive(target_x) ? -1.0f : 1.0f;
			}

			float increment = (ispositive(unit_direction.GetX()) == ispositive(current_pos.GetX())) ? 1.0f : 0.0f;

			if (unit_direction.GetX() > 0.0f)
			{
				target_x += increment;
			}
			else
			{
				target_x -= increment;
			}

			float lambda = (target_x - start_pos.GetX()) / unit_direction.GetX();
			float target_y = (lambda * unit_direction.GetY()) + start_pos.GetY();

			current_pos.GetX() = target_x;
			current_pos.GetY() = target_y;
		}
		else
		{
			float target_y = floor(current_pos.GetY());
			if (target_y == current_pos.GetY())
			{
				target_y += ispositive(target_y) ? -1.0f : 1.0f;
			}

			float increment = (ispositive(unit_direction.GetY()) == ispositive(current_pos.GetY())) ? 1.0f : 0.0f;
			if (unit_direction.GetY() > 0.0f)
			{
				target_y += increment;
			}
			else
			{
				target_y -= increment;
			}

			float lambda = (target_y - start_pos.GetY()) / unit_direction.GetY();
			float target_x = (lambda * unit_direction.GetX()) + start_pos.GetX();
			
			current_pos.GetX() = target_x;
			current_pos.GetY() = target_y;
		}

		current_region = SampleFromWorld(world, current_pos);
#endif
	}

	return current_pos;
}