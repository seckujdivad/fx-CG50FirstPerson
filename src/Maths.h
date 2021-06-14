#pragma once

constexpr float PI = 3.14159265359f;

float floor(float x);
float ceil(float x);

double sin(double x);
double cos(double x);

float fmod(float x, float y);
bool ispositive(float x);
float fabs(float x);
float copysign(float x, float y);

float mix(float a, float b, float mixer);

float clamp_direction(float to_clamp, bool upwards);
float clamp_direction(float to_clamp, float reference, bool clamp_away_from_reference);

enum class Comparison
{
	LessThan,
	GreaterThan,
	LessThanEqual,
	GreaterThanEqual,
};

template<typename T>
inline bool compare(T first, T second, Comparison comparison)
{
	switch (comparison)
	{
	case Comparison::LessThan: return first < second;
	case Comparison::GreaterThan: return first > second;
	case Comparison::LessThanEqual: return first <= second;
	case Comparison::GreaterThanEqual: return first >= second;
	default: return false;
	}
}

template<typename T>
inline T clamp(T value, T smallest, T greatest)
{
	if (smallest > value)
	{
		return smallest;
	}
	else if (value > greatest)
	{
		return greatest;
	}
	else
	{
		return value;
	}
}

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
