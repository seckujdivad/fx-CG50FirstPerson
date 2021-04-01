#pragma once

#include "enable_if.h"

template<typename BaseType, unsigned int dimensions>
struct Vector
{
	inline Vector(BaseType value)
	{
		for (unsigned int i = 0; i < dimensions; i++)
		{
			this->values[i] = value;
		}
	}

	inline Vector(BaseType values[dimensions])
	{
		for (unsigned int i = 0; i < dimensions; i++)
		{
			this->values[i] = values[i];
		}
	}

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

	Vector<BaseType, dimensions> operator+(const Vector<BaseType, dimensions>& rhs)
	{
		Vector<BaseType, dimensions> result = *this;
		for (unsigned int i = 0; i < dimensions; i++)
		{
			result.values[i] += rhs.values[i];
		}
		return result;
	}

	Vector<BaseType, dimensions> operator-(const Vector<BaseType, dimensions>& rhs)
	{
		Vector<BaseType, dimensions> result = *this;
		for (unsigned int i = 0; i < dimensions; i++)
		{
			result.values[i] -= rhs.values[i];
		}
		return result;
	}

	Vector<BaseType, dimensions> operator*(const Vector<BaseType, dimensions>& rhs)
	{
		Vector<BaseType, dimensions> result = *this;
		for (unsigned int i = 0; i < dimensions; i++)
		{
			result.values[i] *= rhs.values[i];
		}
		return result;
	}

	Vector<BaseType, dimensions> operator/(const Vector<BaseType, dimensions>& rhs)
	{
		Vector<BaseType, dimensions> result = *this;
		for (unsigned int i = 0; i < dimensions; i++)
		{
			result.values[i] /= rhs.values[i];
		}
		return result;
	}
};