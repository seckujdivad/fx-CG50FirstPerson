#include "WorldTracing.h"

BoxIntersection FindIntersection(Vector<float, 2> start_pos, Vector<float, 2> unit_direction, int box_x, int box_y)
{
	float lambdas[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	bool valid_lambdas[4] = { false, false, false, false };
	const float pinned_values[4] = {
		static_cast<float>(box_x),
		static_cast<float>(box_x + 1),
		static_cast<float>(box_y),
		static_cast<float>(box_y + 1)
	};

	for (int i = 0; i < 4; i++)
	{
		const float pinned_value = pinned_values[i];

		const int pinned_axis_index = i / 2;
		const int other_axis_index = (pinned_axis_index + 1) % 2;

		if (unit_direction[pinned_axis_index] != 0.0f)
		{
			lambdas[i] = (pinned_value - start_pos[pinned_axis_index]) / unit_direction[pinned_axis_index];
			const float other_value = (lambdas[i] * unit_direction[other_axis_index]) + start_pos[other_axis_index];
			if ((pinned_values[other_axis_index * 2] <= other_value) && (other_value <= pinned_values[(other_axis_index * 2) + 1]))
			{
				valid_lambdas[i] = true;
			}
		}
	}

	BoxIntersection result;
	result.has_values = false;
	for (int i = 0; i < 4; i++)
	{
		if (valid_lambdas[i])
		{
			if (result.has_values)
			{
				if (result.entry_lambda > lambdas[i])
				{
					result.entry_lambda = lambdas[i];
				}

				if (result.exit_lambda < lambdas[i])
				{
					result.exit_lambda = lambdas[i];
				}
			}
			else
			{
				result.entry_lambda = lambdas[i];
				result.exit_lambda = lambdas[i];
				result.has_values = true;
			}
		}
	}

	return result;
}

Intersection CalculateIntersection(Vector<float, 2> start_pos, Vector<float, 2> unit_direction, float pinned_value, bool pinned_is_x)
{
	const int PINNED = pinned_is_x ? 0 : 1;
	const int UNPINNED = pinned_is_x ? 1 : 0;

	float lambda = (pinned_value - start_pos[PINNED]) / unit_direction[PINNED];
	lambda += 0.01f;

	Vector<float, 2> vec;
	vec[PINNED] = (lambda * unit_direction[PINNED]) + start_pos[PINNED];
	vec[UNPINNED] = (lambda * unit_direction[UNPINNED]) + start_pos[UNPINNED];

	return { vec, lambda };
}

bool FindNextAxisIntersection(Intersection& next_intersection, float& current, Vector<float, 2> start_pos, Vector<float, 2> unit_direction, float start, float end, bool inc_is_x)
{
	float inc = (end > start) ? 1.0f : -1.0f;
	Comparison comp = (end > start) ? Comparison::LessThanEqual : Comparison::GreaterThanEqual;

	current += inc;
	if (compare(current, end, comp))
	{
		next_intersection = CalculateIntersection(start_pos, unit_direction, current, inc_is_x);
		if (next_intersection.lambda > 0.0f)
		{
			return true;
		}
		else
		{
			return FindNextAxisIntersection(next_intersection, current, start_pos, unit_direction, start, end, inc_is_x);
		}
	}
	else
	{
		return false;
	}
}

WorldIntersection::WorldIntersection(Vector<float, 2> position, WorldRegion region) : position(position), region(region)
{
}