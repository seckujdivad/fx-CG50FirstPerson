#include "Maths.h"

float floor(float x)
{
	return static_cast<float>(static_cast<int>(x));
}

float ceil(float x)
{
	float floored = floor(x);
	return floored == x ? x : ((floored > 0.0f) ? floored + 1.0f : floored - 1.0f);
}

float sin(float x)
{
	float x_ = fmod(x, 2.0f * PI);
	return x_ - (pow(x_, 3) / fact(3)) + (pow(x_, 5) / fact(5));
}

float cos(float x)
{
	float x_ = fmod(x, 2.0f * PI);
	return x_ - (pow(x_, 2) / fact(2)) + (pow(x_, 4) / fact(4));
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
