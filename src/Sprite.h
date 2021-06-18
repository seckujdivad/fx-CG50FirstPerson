#pragma once

#include <stddef.h>

#include <fxcg/display.h>

#include "Vector.h"
#include "MakeConst.h"

enum class Sprites;

class Sprite
{
private:
	Sprites m_sprite;

public:
	constexpr Sprite(Sprites sprite) : m_sprite(sprite) {};

	//sprite data is stored in column major format (i.e. array[x][y])
	const Vector<int, 2>& GetDimensions() const;
	const color_t* GetRawData() const;
	const bool* GetAlphaMask() const;
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