#pragma once

#include "Vector.h"
#include "World.h"
#include "Maths.h"

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

struct Intersection
{
	Vector<float, 2> point = 0.0f;
	float lambda = 0.0f;
};

Intersection CalculateIntersection(Vector<float, 2> start_pos, Vector<float, 2> unit_direction, float pinned_value, bool pinned_is_x);

bool FindNextAxisIntersection(Intersection& next_intersection, float& current, Vector<float, 2> start_pos, Vector<float, 2> unit_direction, float start, float end, bool inc_is_x);

template<unsigned int X, unsigned int Y>
inline WorldIntersection FindFirstIntersection(const World<X, Y>& world, Vector<float, 2> start_pos, float angle)
{
	Vector<float, 2> unit_direction;
	unit_direction.GetX() = cos(angle);
	unit_direction.GetY() = sin(angle);

	//set up loop bounds and loop data
	float start_x = clamp_direction(start_pos.GetX(), !ispositive(unit_direction.GetX()));
	float end_x = ispositive(unit_direction.GetX()) ? X : 0.0f;
	float current_x = start_x;
	Intersection intersection_x = CalculateIntersection(start_pos, unit_direction, current_x, true);
	bool valid_x = true;

	float start_y = clamp_direction(start_pos.GetY(), !ispositive(unit_direction.GetY()));
	float end_y = ispositive(unit_direction.GetY()) ? Y : 0.0f;
	float current_y = start_y;
	Intersection intersection_y = CalculateIntersection(start_pos, unit_direction, current_y, false);
	bool valid_y = true;

	//ensure lambda > 0
	if (intersection_x.lambda <= 0.0f)
	{
		valid_x = FindNextAxisIntersection(intersection_x, current_x, start_pos, unit_direction, start_x, end_x, true);
	}

	if (intersection_y.lambda <= 0.0f)
	{
		valid_y = FindNextAxisIntersection(intersection_y, current_y, start_pos, unit_direction, start_y, end_y, false);
	}

	while (valid_x || valid_y)
	{
		bool choose_x = true;
		if (valid_x && valid_y)
		{
			choose_x = intersection_x.lambda < intersection_y.lambda;
		}
		else
		{
			choose_x = valid_x && (!valid_y);
		}

		Intersection intersection;
		if (choose_x)
		{
			intersection = intersection_x;
		}
		else
		{
			intersection = intersection_y;
		}

		WorldRegion region = SampleFromWorld(world, intersection.point);

		if (region != WorldRegion::Air)
		{
			return WorldIntersection(intersection.point, region);
		}

		if (choose_x)
		{
			valid_x = FindNextAxisIntersection(intersection_x, current_x, start_pos, unit_direction, start_x, end_x, true);
		}
		else
		{
			valid_y = FindNextAxisIntersection(intersection_y, current_y, start_pos, unit_direction, start_y, end_y, false);
		}
	}

	return WorldIntersection(start_pos, WorldRegion::OutOfRange);
}