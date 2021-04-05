#include "Maths.h"

float floor(float x)
{
	return static_cast<float>(static_cast<int>(x));
}

float ceil(float x)
{
	float floored = floor(x);
	return floored == x ? x : (ispositive(floored) ? floored + 1.0f : floored - 1.0f);
}

float sin(float x)
{
	float x_ = fmod(x, 2.0f * PI);
	if (x_ <= 0.5f * PI)
	{
		return x_ - (pow(x_, 3) / fact(3)) + (pow(x_, 5) / fact(5)) - (pow(x_, 7) / fact(7));
	}
	else if (x_ < PI)
	{
		return sin(PI - x_);
	}
	else
	{
		return 0.0f - sin(x_ - PI);
	}
}

float cos(float x)
{
	float x_ = fmod(x, 2.0f * PI);
	if (x_ <= 0.5f * PI)
	{
		return 1 - (pow(x_, 2) / fact(2)) + (pow(x_, 4) / fact(4)) - (pow(x_, 6) / fact(6));
	}
	else if (x_ < PI)
	{
		return 0.0f - cos(PI - x_);
	}
	else// if (x_ <= 2.0f * PI)
	{
		return 0.0f - cos(x_ - PI);
	}
}

float fmod(float x, float y)
{
	float div = x / y;
	float z = x > 0.0f ? floor(div) : ceil(div);
	return x - (z * y);
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
