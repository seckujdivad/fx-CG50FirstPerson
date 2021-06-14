#include "Maths.h"

float floor(float x)
{
	return static_cast<float>(static_cast<int>(x));
}

float ceil(float x)
{
	float floored = floor(x);
	return floored == x ? x : (ispositive(x) ? floored + 1.0f : floored - 1.0f);
}

float sin_inner(float x)
{
	return x - (pow(x, 3) / fact(3)) + (pow(x, 5) / fact(5));
}

float sin(float x)
{
	float x_looped = fmod(x, 2.0f * PI);
	if (x_looped <= 0.5f * PI)
	{
		return sin_inner(x_looped);
	}
	else if (x_looped < PI)
	{
		return sin(PI - x_looped);
	}
	else
	{
		return 0.0f - sin(x_looped - PI);
	}
}

float cos_inner(float x)
{
	return 1.0f - (pow(x, 2) / fact(2)) + (pow(x, 4) / fact(4));
}

float cos(float x)
{
	float x_looped = fmod(x, 2.0f * PI);
	if (x_looped <= 0.5f * PI)
	{
		return cos_inner(x_looped);
	}
	else if (x_looped < PI)
	{
		return 0.0f - cos(PI - x_looped);
	}
	else
	{
		return 0.0f - cos(x_looped - PI);
	}
}

float fmod(float x, float y)
{
	float transformed_x = ispositive(x) ? x : y + x;
	return (transformed_x - floor(transformed_x / y) * y);
}

bool ispositive(float x)
{
	return x >= 0.0f;
}

float fabs(float x)
{
	return ispositive(x) ? x : x * -1.0f;
}

float copysign(float x, float y)
{
	return ispositive(x) == ispositive(y) ? x : -1.0f * x;
}

float mix(float a, float b, float mixer)
{
	return a + ((b - a) * mixer);
}

float clamp_direction(float to_clamp, bool upwards)
{
	return (upwards != ispositive(to_clamp)) ? floor(to_clamp) : ceil(to_clamp);
}

float clamp_direction(float to_clamp, float reference, bool clamp_away_from_reference)
{
	return clamp_direction(to_clamp, (to_clamp < reference) != clamp_away_from_reference);
}
