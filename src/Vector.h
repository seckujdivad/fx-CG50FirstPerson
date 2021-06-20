#pragma once

#include "Q_rsqrt.h"
#include "Maths.h"

#include "enable_if.h"

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

	template<typename ...T, typename = enable_if_t<sizeof...(T) == dimensions>>
	constexpr Vector(T... values) : values { values... } {};

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

	constexpr const BaseType& operator[](int index) const
	{
		return this->values[index];
	}

	template<typename T>
	inline Vector<T, dimensions>&& Cast() const
	{
		return Vector<T, dimensions>(*this);
	}

	inline float GetAngle() const
	{
		if (fabs(this->GetY()) < 0.01f)
		{
			return (this->GetX() > 0.0f) ? 0.0f : PI<float>;
		}
		else if (fabs(this->GetX()) < 0.01f)
		{
			return (this->GetY() > 0.0f) ? (PI<float> * 0.5f) : (PI<float> * 1.5f);
		}
		else
		{
			float angle = atan(this->GetY() / this->GetX());
			if (this->GetX() < 0.0f)
			{
				angle += PI<float>;
			}

			return fmod(angle, PI<float> * 2.0f);
		}
	}
};