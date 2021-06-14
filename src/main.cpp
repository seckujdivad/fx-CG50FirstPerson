#include <fxcg/display.h>
#include <fxcg/keyboard.h>

#include "World.h"
#include "Renderer.h"
#include "Player.h"
#include "Maths.h"

/* CPU: https://en.wikipedia.org/wiki/SuperH#SH-4_2
* PrizmSDK: https://prizm.cemetech.net/index.php?title=Prizm_Programming_Portal
*/

int main()
{
	Bdisp_AllClr_VRAM();

	World<5, 5> world = {};
	GenerateWorld(world,
		"OOXOO"
		"OOOOO"
		"XOOOX"
		"OOOOO"
		"OOXOO"
	);

	Player player;
	player.position = Vector<float, 2>(2.5f);
	player.rotation = 0.0f;

	bool use_getkey = true;

	while (true)
	{
		player.rotation = fmod(player.rotation, PI * 2.0f);
		Render(world, player);

		{
			int rot_perc_x = LCD_WIDTH_PX * (player.rotation / (2.0f * PI));
			for (int x = 0; x < LCD_WIDTH_PX; x++)
			{
				color_t colour = COLOR_WHITE;
				if (x < rot_perc_x)
				{
					colour = COLOR_BLACK;
				}
				Bdisp_SetPoint_VRAM(x, LCD_HEIGHT_PX - 5, colour);
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
			player.rotation += 0.25f;
		}
		else if (chosen_option == ChosenOption::RotateRight)
		{
			player.rotation -= 0.25f;
		}
		else if ((chosen_option == ChosenOption::MoveForward) || (chosen_option == ChosenOption::MoveBack))
		{
			Vector<float, 2> increment = 0.0f;
			increment.GetX() = cos(player.rotation);
			increment.GetY() = sin(player.rotation);

			increment *= 0.25f;

			if (chosen_option == ChosenOption::MoveBack)
			{
				increment *= -1.0f;
			}

			player.position += increment;
		}
		else if (chosen_option == ChosenOption::ResetPosition)
		{
			player.position = Vector<float, 2>(2.5f);
			player.rotation = 0.0f;
		}
		else if (chosen_option == ChosenOption::GoToGetKey)
		{
			use_getkey = true;
		}
	}

	return 0;
}
