#include <fxcg/display.h>
#include <fxcg/keyboard.h>

#include "World.h"
#include "Renderer.h"
#include "Player.h"
#include "Maths.h"
#include "WorldLayout.h"
#include "DisplayWriting.h"

/* CPU: https://en.wikipedia.org/wiki/SuperH#SH-4_2
* PrizmSDK: https://prizm.cemetech.net/index.php?title=Prizm_Programming_Portal
*/

int main()
{
	constexpr float MOVE_INCREMENT = 0.25f;
	constexpr float ROTATE_INCREMENT = PI<float> / 12.0f;

	Bdisp_AllClr_VRAM();
	InitialiseVRAMAddress();

	{
		EnableStatusArea(0); //enable status area

		DefineStatusAreaFlags(3, SAF_BATTERY | SAF_TEXT, 0, 0);

		char status_message[] = "First Person Ray-Caster"; //30 chars max, centre is at the 15th char
		DefineStatusMessage(status_message, 0, TEXT_COLOR_BLACK, 0);

		DisplayStatusArea();
		EnableStatusArea(3); //disable status area so that it isn't continuously redrawn by GetKey
	}

	World<5, 5> world = {};
	GenerateWorld(world, WORLD_GENERATOR);

	Player player = PLAYER_INITIAL;

	bool use_getkey = true;

	while (true)
	{
		player.rotation = fmod(player.rotation, PI<float> * 2.0f);
		Render(world, player, SPRITES, NUM_SPRITES);

		{
			int rot_perc_x = LCD_WIDTH_PX * (player.rotation / (2.0f * PI<float>));
			for (int x = 0; x < LCD_WIDTH_PX; x += 2)
			{
				color_t colour = COLOR_WHITE;
				if (x < rot_perc_x)
				{
					colour = COLOR_BLACK;
				}
				WritePixelPair(x, LCD_HEIGHT_PX - 1, colour);
			}
		}

		Bdisp_PutDisp_DD();

		enum class ChosenOption
		{
			None,
			GoToGetKey,
			RotateLeft,
			RotateRight,
			MoveForward,
			MoveBack,
			MoveLeft,
			MoveRight,
			ResetPosition
		} chosen_option = ChosenOption::None;

		if (use_getkey)
		{
			int key;
			GetKey(&key);

			switch (key)
			{
			case KEY_CHAR_4: chosen_option = ChosenOption::RotateLeft; break;
			case KEY_CHAR_6: chosen_option = ChosenOption::RotateRight; break;
			case KEY_CHAR_8: chosen_option = ChosenOption::MoveForward; break;
			case KEY_CHAR_2: chosen_option = ChosenOption::MoveBack; break;
			case KEY_CHAR_7: chosen_option = ChosenOption::MoveLeft; break;
			case KEY_CHAR_9: chosen_option = ChosenOption::MoveRight; break;
			case KEY_CHAR_0: chosen_option = ChosenOption::ResetPosition; break;
			}

			use_getkey = false;
		}
		else
		{
			int column;
			int row;
			unsigned short discard;
			int event_type = GetKeyWait_OS(&column, &row, KEYWAIT_HALTOFF_TIMEROFF, 0, 0, &discard);

			if (event_type == KEYREP_KEYEVENT)
			{
				if (row == 0x04 && column == 0x07) //4
				{
					chosen_option = ChosenOption::RotateLeft;
				}
				else if (row == 0x04 && column == 0x05) //6
				{
					chosen_option = ChosenOption::RotateRight;
				}
				else if (row == 0x05 && column == 0x06) //8
				{
					chosen_option = ChosenOption::MoveForward;
				}
				else if (row == 0x03 && column == 0x06) //2
				{
					chosen_option = ChosenOption::MoveBack;
				}
				else if (row == 0x05 && column == 0x07) //7
				{
					chosen_option = ChosenOption::MoveLeft;
				}
				else if (row == 0x05 && column == 0x05) //9
				{
					chosen_option = ChosenOption::MoveRight;
				}
				else if (row == 0x02 && column == 0x07) //0
				{
					chosen_option = ChosenOption::ResetPosition;
				}
				else if (row == 0x09 && column == 0x04) //menu
				{
					chosen_option = ChosenOption::GoToGetKey;
				}
			}
			else if (event_type == KEYREP_TIMEREVENT || event_type == KEYREP_NOEVENT)
			{
				use_getkey = true;
			}
		}

		if (chosen_option == ChosenOption::RotateLeft)
		{
			player.rotation += ROTATE_INCREMENT;
		}
		else if (chosen_option == ChosenOption::RotateRight)
		{
			player.rotation -= ROTATE_INCREMENT;
		}
		else if ((chosen_option == ChosenOption::MoveForward) || (chosen_option == ChosenOption::MoveBack))
		{
			Vector<float, 2> increment = 0.0f;
			increment.GetX() = cos(player.rotation);
			increment.GetY() = sin(player.rotation);

			increment *= MOVE_INCREMENT;

			if (chosen_option == ChosenOption::MoveBack)
			{
				increment *= -1.0f;
			}

			player.position += increment;
		}
		else if ((chosen_option == ChosenOption::MoveLeft) || (chosen_option == ChosenOption::MoveRight))
		{
			Vector<float, 2> increment = 0.0f;
			if (chosen_option == ChosenOption::MoveLeft)
			{
				increment.GetX() = cos(player.rotation + (PI<float> / 2.0f));
				increment.GetY() = sin(player.rotation + (PI<float> / 2.0f));
			}
			else
			{
				increment.GetX() = cos(player.rotation - (PI<float> / 2.0f));
				increment.GetY() = sin(player.rotation - (PI<float> / 2.0f));
			}

			increment *= MOVE_INCREMENT;

			player.position += increment;
		}
		else if (chosen_option == ChosenOption::ResetPosition)
		{
			player = PLAYER_INITIAL;
		}
		else if (chosen_option == ChosenOption::GoToGetKey)
		{
			use_getkey = true;
		}
	}

	return 0;
}
