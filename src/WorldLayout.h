#pragma once

#include "Sprite.h"
#include "Sprites.h"
#include "Vector.h"

constexpr char WORLD_GENERATOR[] =
	"OOXOO"
	"OOOOO"
	"XOOOX"
	"OOOOO"
	"OOXOO";

constexpr Sprite SPRITES[] = {
	Sprite(Sprites::RedCross, Vector<float, 2>(0.5f, 0.5f))
};
constexpr size_t NUM_SPRITES = sizeof(SPRITES) / sizeof(Sprite);