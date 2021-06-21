#include "Player.h"

#include "MakeConst.h"
#include "Maths.h"

void Player::MoveLocally(Vector<float, 2> move_by)
{
	if (move_by.GetY() != 0.0f)
	{
		Vector<float, 2> increment = 0.0f;
		increment.GetX() = cos(this->rotation);
		increment.GetY() = sin(this->rotation);
		this->position += increment * MakeConst(move_by).GetY();
	}

	if (move_by.GetX() != 0.0f)
	{
		Vector<float, 2> increment = 0.0f;
		increment.GetX() = cos(this->rotation - (PI<float> / 2.0f));
		increment.GetY() = sin(this->rotation - (PI<float> / 2.0f));
		this->position += increment * MakeConst(move_by).GetX();
	}
}
