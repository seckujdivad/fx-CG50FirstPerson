#pragma once

constexpr float PI = 3.14159265359f;

float floor(float x);
float ceil(float x);

float sin(float x);
float cos(float x);

float fmod(float x, float y);
bool ispositive(float x);
float fabs(float x);
float copysign(float x, float y);

float mix(float a, float b, float mixer);

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