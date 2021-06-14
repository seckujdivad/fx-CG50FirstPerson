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

// https://en.wikipedia.org/wiki/Horner%27s_method to evaluate maclaurins series
double sin_inner(double x) // x->[0..PI/2]
{
#if 1 //use double precision as it works better for small angles
	double x2 = pow(x, 2.0);
	double approximation = x * (1 + x2 * ((-1.0 / fact(3)) + x2 * ((1.0 / fact(5)) + x2 * ((-1.0 / fact(7))))));
#else
	float x2 = pow(x, 2.0f);
	float approximation = x * (1 + x2 * ((-1.0f / fact(3)) + x2 * ((1.0f / fact(5)) + x2 * ((-1.0f / fact(7))))));
#endif

	return clamp(approximation, 0.0, 1.0);
}

double sin(double x)
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

double cos(double x)
{
	return sin(x + (PI / 2.0f));
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
