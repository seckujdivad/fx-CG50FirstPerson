#pragma once

#include "Sprite.h"
#include "Sprites.h"
#include "Vector.h"
#include "Player.h"

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

constexpr Player PLAYER_INITIAL = { Vector<float, 2>(2.5f, 2.5f), 0.0f };