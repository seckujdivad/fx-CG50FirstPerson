#pragma once

#include "Sprite.h"
#include "Sprites.h"
#include "Vector.h"
#include "Player.h"

constexpr char WORLD_GENERATOR[] =
	"OOXOO"  //(-x, -y)    (x, -y)
	"OOOOO"
	"XOOOX"
	"OOOOO"
	"OOXOO"; //(-x, y)      (x, y)

constexpr Sprite SPRITES[] = {
	Sprite(Sprites::RedCross, Vector<float, 2>(0.5f, 0.5f))
};
constexpr size_t NUM_SPRITES = sizeof(SPRITES) / sizeof(Sprite);

constexpr Player PLAYER_INITIAL = { Vector<float, 2>(2.5f, 2.5f), 0.0f };