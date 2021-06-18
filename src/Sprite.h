#pragma once

#include <stddef.h>

#include <fxcg/display.h>

#include "Vector.h"

enum class Sprites;

class Sprite
{
private:
	Sprites m_sprite;

public:
	constexpr Sprite(Sprites sprite) : m_sprite(sprite) {};

	const Vector<int, 2>& GetDimensions() const;
	const color_t* GetRawData() const;
	const bool* GetAlphaMask() const;
};