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

/* tan values generator
#include <iostream>
#include <cmath>
#include <string>

int main()
{
    constexpr int NUM_VALUES = 20;
    for (int i = 0; i < NUM_VALUES; i++)
    {
        const float x = (static_cast<float>(i) / NUM_VALUES) * (M_PI / 2.0);
        std::cout << std::to_string(tan(x)) << ',' << std::endl;
    }
}
*/

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
    1.631851,
    1.962610,
    2.414214,
    3.077684,
    4.165301,
    6.313751,
    12.706207,
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
        int nearest_index = FindNearestIndex(x);
        float best_frac_unnormalised = 0.0f;
        if ((nearest_index > 0) && (nearest_index < NUM_TAN_VALUES - 1)) //linearly interpolate between two values if possible (not possible if the best value is an end value)
        {
            int index_below = 0;
            int index_above = 0;
            if (TAN_VALUES[nearest_index] < x)
            {
                index_below = nearest_index;
                index_above = nearest_index + 1;
            }
            else
            {
                index_below = nearest_index - 1;
                index_above = nearest_index;
            }

            float value_below = TAN_VALUES[index_below];
            float value_above = TAN_VALUES[index_above];

            best_frac_unnormalised = static_cast<float>(index_below) + ((x - value_below) / (value_above - value_below));
        }
        else
        {
            best_frac_unnormalised = static_cast<float>(nearest_index);
        }
        float tan_frac = best_frac_unnormalised / static_cast<float>(NUM_TAN_VALUES);
        return tan_frac * 0.5f * PI<float>;
    }
}