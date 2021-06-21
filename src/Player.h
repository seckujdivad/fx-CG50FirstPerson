#pragma once

#include "Vector.h"

struct Player
{
	Vector<float, 2> position;
	float rotation;

	void MoveLocally(Vector<float, 2> move_by);
};