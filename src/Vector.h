#pragma once

#include "enable_if.h"

template<typename BaseType, unsigned int dimensions>
struct Vector
{
	BaseType values[dimensions];

	inline BaseType& GetX()
	{
		static_assert(dimensions > 0);
		return this->values[0];
	}

	inline BaseType& GetY()
	{
		static_assert(dimensions > 1);
		return this->values[1];
	}

	inline BaseType& GetZ()
	{
		static_assert(dimensions > 2);
		return this->values[2];
	}

	inline const BaseType& GetX() const
	{
		static_assert(dimensions > 0);
		return this->values[0];
	}

	inline const BaseType& GetY() const
	{
		static_assert(dimensions > 1);
		return this->values[1];
	}

	inline const BaseType& GetZ() const
	{
		static_assert(dimensions > 2);
		return this->values[2];
	}
};