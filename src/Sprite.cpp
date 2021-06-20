#include "Sprite.h"

#include "Sprites.h"

/*
* Sprite data is transposed when rendered to better utilise the cache
*/

constexpr Vector<int, 2> SPRITE_DIMENSIONS[] = {
	Vector<int, 2>(6, 6),
	Vector<int, 2>(5, 5)
};

constexpr Vector<int, 2> SPRITE_SCALES[] = {
	Vector<int, 2>(1, 1),
	Vector<int, 2>(25, 25)
};

constexpr color_t SPRITE_DATA_Error[SPRITE_DIMENSIONS[0].GetX() * SPRITE_DIMENSIONS[0].GetY()] = {
	COLOR_BLACK, COLOR_PURPLE, COLOR_BLACK, COLOR_PURPLE, COLOR_BLACK, COLOR_PURPLE,
	COLOR_PURPLE, COLOR_BLACK, COLOR_PURPLE, COLOR_BLACK, COLOR_PURPLE, COLOR_BLACK,
	COLOR_BLACK, COLOR_PURPLE, COLOR_BLACK, COLOR_PURPLE, COLOR_BLACK, COLOR_PURPLE,
	COLOR_PURPLE, COLOR_BLACK, COLOR_PURPLE, COLOR_BLACK, COLOR_PURPLE, COLOR_BLACK,
	COLOR_BLACK, COLOR_PURPLE, COLOR_BLACK, COLOR_PURPLE, COLOR_BLACK, COLOR_PURPLE,
	COLOR_PURPLE, COLOR_BLACK, COLOR_PURPLE, COLOR_BLACK, COLOR_PURPLE, COLOR_BLACK,
};

constexpr bool SPRITE_ALPHAMASK_Error[SPRITE_DIMENSIONS[0].GetX() * SPRITE_DIMENSIONS[0].GetY()] = {
	true, true, true, true, true, true,
	true, true, true, true, true, true,
	true, true, true, true, true, true,
	true, true, true, true, true, true,
	true, true, true, true, true, true,
	true, true, true, true, true, true
};

constexpr color_t SPRITE_DATA_RedCross[SPRITE_DIMENSIONS[1].GetX() * SPRITE_DIMENSIONS[1].GetY()] = {
	COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED,
	COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_RED, COLOR_BLACK,
	COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK,
	COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_RED, COLOR_BLACK,
	COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED
};

constexpr bool SPRITE_ALPHAMASK_RedCross[SPRITE_DIMENSIONS[1].GetX() * SPRITE_DIMENSIONS[1].GetY()] = {
	true, false, false, false, true,
	false, true, false, true, false,
	false, false, true, false, false,
	false, true, false, true, false,
	true, false, false, false, true
};

const Vector<int, 2>& Sprite::GetDimensions() const
{
	return SPRITE_DIMENSIONS[static_cast<size_t>(this->m_sprite)];
}

const color_t* Sprite::GetRawData() const
{
	if (this->m_sprite == Sprites::Error)
	{
		return SPRITE_DATA_Error;
	}
	else if (this->m_sprite == Sprites::RedCross)
	{
		return SPRITE_DATA_RedCross;
	}
	else
	{
		return SPRITE_DATA_Error;
	}
}

const bool* Sprite::GetAlphaMask() const
{
	if (this->m_sprite == Sprites::Error)
	{
		return SPRITE_ALPHAMASK_Error;
	}
	else if (this->m_sprite == Sprites::RedCross)
	{
		return SPRITE_ALPHAMASK_RedCross;
	}
	else
	{
		return SPRITE_ALPHAMASK_Error;
	}
}

const Vector<int, 2>& Sprite::GetScale() const
{
	return SPRITE_SCALES[static_cast<size_t>(this->m_sprite)];
}
