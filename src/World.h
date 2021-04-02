#pragma once

#include <string.h>

#include "Vector.h"
#include "Maths.h"

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

	Vector<float, 2> current_pos = start_pos;
	WorldRegion current_region = SampleFromWorld(world, current_pos);
	while (current_region == WorldRegion::Air)
	{
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
			float target_x = ceil(current_pos.GetX());
			if (unit_direction.GetX() > 0.0f)
			{
				target_x += 1.0f;
			}
			else
			{
				target_x -= 1.0f;
			}

			float lambda = (target_x - start_pos.GetX()) / unit_direction.GetX();
			float target_y = (lambda * unit_direction.GetY()) + start_pos.GetY();

			current_pos.GetX() = target_x;
			current_pos.GetY() = target_y;
		}
		else
		{
			float target_y = ceil(current_pos.GetY());
			if (unit_direction.GetY() > 0.0f)
			{
				target_y += 1.0f;
			}
			else
			{
				target_y -= 1.0f;
			}

			float lambda = (target_y - start_pos.GetY()) / unit_direction.GetY();
			float target_x = (lambda * unit_direction.GetX()) + start_pos.GetX();
			
			current_pos.GetX() = target_x;
			current_pos.GetY() = target_y;
		}

		current_region = SampleFromWorld(world, current_pos);
	}

	return current_pos;
}