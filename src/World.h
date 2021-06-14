#pragma once

#include <string.h>

#include "Vector.h"
#include "Maths.h"
#include "List.h"

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

	return SampleFromWorld(target, static_cast<int>(clamp_direction(sample.GetX(), false)), static_cast<int>(clamp_direction(sample.GetY(), false)));
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

	struct Intersection
	{
		Vector<float, 2> point;
		float lambda = 0.0f;
	};

	List<Intersection> intersections_x;
	{
		float start_x = clamp_direction(start_pos.GetX(), !ispositive(unit_direction.GetX()));
		float end_x = ispositive(unit_direction.GetX()) ? X : 0.0f;
		float inc_x = (end_x > start_x) ? 1.0f : -1.0f;
		Comparison comp = (end_x > start_x) ? Comparison::LessThanEqual : Comparison::GreaterThanEqual;
		if (fabs(unit_direction.GetX()) > 0.001)
		{
			for (float x = start_x; compare(x, end_x, comp); x += inc_x)
			{
				float lambda = (x - start_pos.GetX()) / unit_direction.GetX();
				if (lambda > 0.0f)
				{
					lambda += 0.01f;

					Vector<float, 2> vec;
					vec.GetX() = (lambda * unit_direction.GetX()) + start_pos.GetX();
					vec.GetY() = (lambda * unit_direction.GetY()) + start_pos.GetY();

					intersections_x.Append({ vec, lambda });
				}
			}
		}
	}
	
	List<Intersection> intersections_y;
	{
		float start_y = clamp_direction(start_pos.GetY(), !ispositive(unit_direction.GetY()));
		float end_y = ispositive(unit_direction.GetY()) ? Y : 0.0f;
		float inc_y = (end_y > start_y) ? 1.0f : -1.0f;
		Comparison comp = (end_y > start_y) ? Comparison::LessThanEqual : Comparison::GreaterThanEqual;
		if (fabs(unit_direction.GetY()) > 0.001)
		{
			for (float y = start_y; compare(y, end_y, comp); y += inc_y)
			{
				float lambda = (y - start_pos.GetY()) / unit_direction.GetY();
				if (lambda > 0.0f)
				{
					lambda += 0.01f;

					Vector<float, 2> vec;
					vec.GetX() = (lambda * unit_direction.GetX()) + start_pos.GetX();
					vec.GetY() = (lambda * unit_direction.GetY()) + start_pos.GetY();

					intersections_y.Append({ vec, lambda });
				}
			}
		}
	}

	ListNode<Intersection>* node_x = intersections_x.GetChild();
	ListNode<Intersection>* node_y = intersections_y.GetChild();
	while ((node_x != nullptr) || (node_y != nullptr))
	{
		//find next intersection along line
		ListNode<Intersection>* node = nullptr;
		if ((node_x != nullptr) && (node_y != nullptr))
		{
			if (node_x->GetValue().lambda < node_y->GetValue().lambda)
			{
				node = node_x;

				//select next node
				node_x = node_x->GetChild();
			}
			else
			{
				node = node_y;
				node_y = node_y->GetChild();
			}
		}
		else if (node_x != nullptr)
		{
			node = node_x;
			node_x = node_x->GetChild();
		}
		else
		{
			node = node_y;
			node_y = node_y->GetChild();
		}

		Intersection intersection = node->GetValue();

		WorldRegion region = SampleFromWorld(world, intersection.point);

		if (region != WorldRegion::Air)
		{
			return WorldIntersection(intersection.point, region);
		}
	}

	return WorldIntersection(start_pos, WorldRegion::OutOfRange);
}