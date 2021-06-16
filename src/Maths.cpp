#include "Maths.h"

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
	double x_looped = fmod(x, 2.0 * PI<>);
	if (x_looped <= 0.5 * PI<>)
	{
		return sin_inner(x_looped);
	}
	else if (x_looped < PI<>)
	{
		return sin(PI<> - x_looped);
	}
	else
	{
		return 0.0 - sin(x_looped - PI<>);
	}
}

double cos(double x)
{
	return sin(x + (PI<> / 2.0));
}