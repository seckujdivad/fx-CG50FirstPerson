#include "World.h"

WorldRegion GetWorldRegion(char world_region)
{
	switch (world_region)
	{
	case 'X': return WorldRegion::Black;
	default: return WorldRegion::Air;
	}
}

BoxIntersection FindIntersection(Vector<float, 2> start_pos, Vector<float, 2> unit_direction, int box_x, int box_y)
{
	float lambdas[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	bool valid_lambdas[4] = { false, false, false, false };
	float pinned_values[4] = {
		static_cast<float>(box_x),
		static_cast<float>(box_x + 1),
		static_cast<float>(box_y),
		static_cast<float>(box_y + 1)
	};

	for (int i = 0; i < 4; i++)
	{
		float pinned_value = pinned_values[i];

		int pinned_axis_index = i / 2;
		int other_axis_index = (pinned_axis_index + 1) % 2;

		if (fabs(unit_direction[pinned_axis_index]) > 0.0f)
		{
			lambdas[i] = (pinned_value - start_pos[pinned_axis_index]) / unit_direction[pinned_axis_index];
			float other_value = (lambdas[i] * unit_direction[other_axis_index]) + start_pos[other_axis_index];
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

WorldIntersection::WorldIntersection(Vector<float, 2> position, WorldRegion region) : position(position), region(region)
{
}
