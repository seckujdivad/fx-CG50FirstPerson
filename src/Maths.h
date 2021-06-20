#pragma once

template<typename T = double>
constexpr T PI = static_cast<T>(3.1415926535897932384626433832795); //3.14159265359f;

template<typename T>
constexpr bool ispositive(T x)
{
	return x >= static_cast<T>(0.0);
}

template<typename T>
constexpr T floor(T x)
{
	return static_cast<T>(static_cast<int>(x));
}

template<typename T>
inline T ceil(T x)
{
	T floored = floor(x);
	return floored == x ? x : (ispositive(x) ? floored + static_cast<T>(1.0) : floored - static_cast<T>(1.0));
}

template<typename T>
inline T fmod(T x, T y)
{
	T transformed_x = ispositive(x) ? x : y + x;
	return (transformed_x - floor(transformed_x / y) * y);
}

template<typename T>
constexpr T fabs(T x)
{
	return ispositive(x) ? x : x * static_cast<T>(-1.0);
}

template<typename T>
constexpr T copysign(T x, T y)
{
	return ispositive(x) == ispositive(y) ? x : static_cast<T>(-1.0) * x;
}

template<typename T>
constexpr T mix(T a, T b, T mixer)
{
	return a + ((b - a) * mixer);
}

template<typename T>
inline T clamp_direction(T to_clamp, bool upwards)
{
	return (upwards != ispositive(to_clamp)) ? floor(to_clamp) : ceil(to_clamp);
}

template<typename T>
inline T clamp_direction(T to_clamp, T reference, bool clamp_away_from_reference)
{
	return clamp_direction(to_clamp, (to_clamp < reference) != clamp_away_from_reference);
}

double sin(double x);
double cos(double x);

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
constexpr T max(T x, T y)
{
	return (x > y) ? x : y;
}

template<typename T>
constexpr T min(T x, T y)
{
	return (x < y) ? x : y;
}

template<typename T>
constexpr T clamp(T value, T smallest, T greatest)
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

float atan(float x);