#pragma once

#include <stddef.h>

#if IS_TESTBED == 1
#include <display.h>
#else
#include <fxcg/display.h>
#endif

#include "Vector.h"
#include "MakeConst.h"

enum class Sprites;

class Sprite
{
private:
	Sprites m_sprite;
	Vector<float, 2> m_position;

public:
	constexpr Sprite(Sprites sprite, Vector<float, 2> position) : m_sprite(sprite), m_position(position) {};

	//sprite data is stored in column major format (i.e. array[x][y])
	const Vector<int, 2>& GetDimensions() const;
	const color_t* GetRawData() const;
	const bool* GetAlphaMask() const;

	const Vector<int, 2>& GetScale() const;

	constexpr Vector<float, 2>& GetPosition() { return this->m_position; };
	constexpr const Vector<float, 2>& GetPosition() const { return this->m_position; };
};

//access a matrix stored in column major format
template<typename T>
constexpr const T& AccessMatrix(const Vector<int, 2> access, const T* matrix, int height)
{
	return matrix[(access.GetX() * height) + access.GetY()];
}

template<typename T>
constexpr const T& AccessMatrix(Vector<int, 2> access, const T* matrix, const Vector<int, 2> dimensions)
{
	return AccessMatrix(access, matrix, dimensions.GetY());
}

template<typename T>
constexpr const T& AccessSpriteMatrix(const Vector<int, 2> access, const T* matrix, const Sprite sprite)
{
	return AccessMatrix(access, matrix, sprite.GetDimensions().GetY());
}