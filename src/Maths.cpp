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

constexpr float TAN_VALUES[] = {
    0.000000,
    0.078702,
    0.158384,
    0.240079,
    0.324920,
    0.414214,
    0.509525,
    0.612801,
    0.726543,
    0.854081,
    1.000000,
    1.170850,
    1.376382,
    1.631852,
    1.962610,
    2.414214,
    3.077684,
    4.165300,
    6.313750,
    12.706202
};
constexpr int NUM_TAN_VALUES = sizeof(TAN_VALUES) / sizeof(float);

int FindNearestIndex(float ref, int min, int max)
{
    if (min + 1 >= max)
    {
        return min;
    }
    else
    {
        int middle = min + ((max - min) / 2);
        if (TAN_VALUES[middle] < ref)
        {
            if (TAN_VALUES[middle + 1] > ref)
            {
                return middle;
            }
            else
            {
                return FindNearestIndex(ref, middle + 1, max);
            }
        }
        else
        {
            if (TAN_VALUES[middle - 1] < ref)
            {
                return middle - 1;
            }
            else
            {
                return FindNearestIndex(ref, min, middle - 1);
            }
        }
    }
}

int FindNearestIndex(float ref)
{
    if (ref < TAN_VALUES[0])
    {
        return 0;
    }
    else if (ref > TAN_VALUES[NUM_TAN_VALUES - 1])
    {
        return NUM_TAN_VALUES - 1;
    }
    else
    {
        return FindNearestIndex(ref, 1, NUM_TAN_VALUES - 1);
    }
}

float atan(float x)
{
    if (x < 0.0f)
    {
        return 0.0f - atan(0.0f - x);
    }
    else
    {
        float tan_frac = static_cast<float>(FindNearestIndex(x)) / static_cast<float>(NUM_TAN_VALUES);
        return tan_frac * 0.5f * PI<float>;
    }
}