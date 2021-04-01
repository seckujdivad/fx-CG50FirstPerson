#pragma once

#include <math.h>

constexpr float PI = 3.14159265359f;

float floor(float x);
float ceil(float x);

float sin(float x);
float cos(float x);

inline constexpr int fact(int x)
{
	return x == 0 ? 1 : x * fact(x - 1);
}

template<typename T>
inline T pow(T x, int y) //y must be > 0
{
	for (int i = 1; i < y; i++)
	{
		x *= x;
	}
	return x;
}

template<typename T>
inline constexpr T pow_constexpr(T x, int y) //y must be >= 0
{
	return y == 0 ? 1 : x * pow_constexpr(x, y - 1);
}

inline constexpr float sin_constexpr(float x)
{
	return x - (pow_constexpr(x, 3) / fact(3)) + (pow_constexpr(x, 5) / fact(5));
}

inline constexpr float cos_constexpr(float x)
{
	return x - (pow_constexpr(x, 2) / fact(2)) + (pow_constexpr(x, 4) / fact(4));
}