#pragma once

#include "Vector.h"

constexpr float PLAYER_MOVE_INCREMENT = 0.25f;
constexpr float PLAYER_ROTATE_INCREMENT = PI<float> / 12.0f;

struct Player
{
	Vector<float, 2> position;
	float rotation;

	void MoveLocally(Vector<float, 2> move_by);
};