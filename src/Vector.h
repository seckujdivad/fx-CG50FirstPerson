#pragma once

#include "enable_if.h"

template<typename BaseType, unsigned int dimensions>
struct Vector
{
	BaseType values[dimensions];

	template<typename enable_if<(dimensions > 0), void>::type* = nullptr>
	inline BaseType& GetX()
	{
		return values[0];
	}

	template<typename enable_if<(dimensions > 1), void>::type* = nullptr>
	inline BaseType& GetY()
	{
		return values[1];
	}

	template<typename enable_if<(dimensions > 2), void>::type* = nullptr>
	inline BaseType& GetZ()
	{
		return values[2];
	}

	template<typename enable_if<(dimensions > 0), void>::type* = nullptr>
	inline const BaseType& GetX() const
	{
		return values[0];
	}

	template<typename enable_if<(dimensions > 1), void>::type* = nullptr>
	inline const BaseType& GetY() const
	{
		return values[1];
	}

	template<typename enable_if<(dimensions > 2), void>::type* = nullptr>
	inline const BaseType& GetZ() const
	{
		return values[2];
	}
};