#pragma once

#include "Q_rsqrt.h"

template<typename BaseType, unsigned int dimensions>
struct Vector
{
	inline Vector() : Vector(BaseType(0)) {};

	inline Vector(BaseType value)
	{
		for (unsigned int i = 0; i < dimensions; i++)
		{
			this->values[i] = value;
		}
	}

	template<typename ...T>
	constexpr Vector(BaseType value, T... values) : values { value, values... } {};

	inline Vector(BaseType values[dimensions])
	{
		for (unsigned int i = 0; i < dimensions; i++)
		{
			this->values[i] = values[i];
		}
	}

	template<typename T>
	inline Vector(const Vector<T, dimensions>& copy_from)
	{
		for (unsigned int i = 0; i < dimensions; i++)
		{
			this->values[i] = static_cast<BaseType>(copy_from.values[i]);
		}
	}

	BaseType values[dimensions];

	inline BaseType& GetX()
	{
		static_assert(dimensions > 0, "Dimensions must be greater than 0 to use GetX");
		return this->values[0];
	}

	inline BaseType& GetY()
	{
		static_assert(dimensions > 1, "Dimensions must be greater than 1 to use GetY");
		return this->values[1];
	}

	inline BaseType& GetZ()
	{
		static_assert(dimensions > 2, "Dimensions must be greater than 2 to use GetZ");
		return this->values[2];
	}

	constexpr const BaseType& GetX() const
	{
		static_assert(dimensions > 0, "Dimensions must be greater than 0 to use GetX");
		return this->values[0];
	}

	constexpr const BaseType& GetY() const
	{
		static_assert(dimensions > 1, "Dimensions must be greater than 1 to use GetY");
		return this->values[1];
	}

	constexpr const BaseType& GetZ() const
	{
		static_assert(dimensions > 2, "Dimensions must be greater than 2 to use GetZ");
		return this->values[2];
	}

	inline BaseType InverseLength() const
	{
		BaseType square_sum = BaseType(0);
		for (unsigned int i = 0; i < dimensions; i++)
		{
			square_sum += this->values[i] * this->values[i];
		}
		return Q_rsqrt(square_sum);
	}

	inline BaseType Length() const
	{
		return BaseType(1) / this->InverseLength();
	}

	inline Vector<BaseType, dimensions> operator+(const Vector<BaseType, dimensions>& rhs) const
	{
		Vector<BaseType, dimensions> result = *this;
		for (unsigned int i = 0; i < dimensions; i++)
		{
			result.values[i] += rhs.values[i];
		}
		return result;
	}

	inline Vector<BaseType, dimensions> operator+=(const Vector<BaseType, dimensions>& rhs)
	{
		for (unsigned int i = 0; i < dimensions; i++)
		{
			this->values[i] += rhs.values[i];
		}
		return *this;
	}

	inline Vector<BaseType, dimensions> operator-(const Vector<BaseType, dimensions>& rhs) const
	{
		Vector<BaseType, dimensions> result = *this;
		for (unsigned int i = 0; i < dimensions; i++)
		{
			result.values[i] -= rhs.values[i];
		}
		return result;
	}

	inline Vector<BaseType, dimensions> operator-=(const Vector<BaseType, dimensions>& rhs)
	{
		for (unsigned int i = 0; i < dimensions; i++)
		{
			this->values[i] -= rhs.values[i];
		}
		return *this;
	}

	inline Vector<BaseType, dimensions> operator*(const Vector<BaseType, dimensions>& rhs) const
	{
		Vector<BaseType, dimensions> result = *this;
		for (unsigned int i = 0; i < dimensions; i++)
		{
			result.values[i] *= rhs.values[i];
		}
		return result;
	}

	inline Vector<BaseType, dimensions> operator*=(const Vector<BaseType, dimensions>& rhs)
	{
		for (unsigned int i = 0; i < dimensions; i++)
		{
			this->values[i] *= rhs.values[i];
		}
		return *this;
	}

	inline Vector<BaseType, dimensions> operator/(const Vector<BaseType, dimensions>& rhs) const
	{
		Vector<BaseType, dimensions> result = *this;
		for (unsigned int i = 0; i < dimensions; i++)
		{
			result.values[i] /= rhs.values[i];
		}
		return result;
	}

	inline Vector<BaseType, dimensions> operator/=(const Vector<BaseType, dimensions>& rhs)
	{
		for (unsigned int i = 0; i < dimensions; i++)
		{
			this->values[i] /= rhs.values[i];
		}
		return *this;
	}

	inline BaseType& operator[](int index)
	{
		return this->values[index];
	}

	inline const BaseType& operator[](int index) const
	{
		return this->values[index];
	}
};