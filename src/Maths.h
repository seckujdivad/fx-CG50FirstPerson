#pragma once

#include <math.h>

constexpr float PI = 3.14159265359f;

inline constexpr int fact(int x)
{
	return x == 0 ? 1 : x * fact(x - 1);
}

template<typename T>
inline T pow(T x, int y)
{
	for (int i = 1; i < y; i++)
	{
		x *= x;
	}
	return x;
}

template<typename T>
inline constexpr T pow_constexpr(T x, int y)
{
	return y == 0 ? 1 : x * pow_constexpr(x, y - 1);
}

inline constexpr float sin(float x)
{
	return x - (pow(x, 3) / fact(3)) + (pow(x, 5) / fact(5));
}

inline constexpr float cos(float x)
{
	return x - (pow(x, 2) / fact(2)) + (pow(x, 4) / fact(4));
}