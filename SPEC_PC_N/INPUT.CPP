#include "STANDARD.H"
#include "GLOBAL.H"
#include "WINMAIN.H"
//#include "console.h"
#include <math.h>
#include "TEMPLATE.H"
#include "INPUT.H"
#include "DI.H"
//#include "display.h"
//#include "frontend.h"
#include "INIT.H"
#include "SETUP.H"
#include "CONTROL.H"
#include "LARA.H"
#include "EFFECTS.H"
#include "SOUND.H"
#include "SAVEGAME.H"
#include "CAMERA.H"
#include "GAMEFLOW.H"
#include "DEBUG.H"

#define JOY_SENSITIVITY 8

sint32 input;
sint32 dbinput;
sint32 inputBusy;

short mouse_x;
short mouse_y;
int mouse_vkeys;
unsigned char keymap[256];
int32_t conflict[18];
int16_t layout[2][18] = 
{
	{ DIK_UP, DIK_DOWN, DIK_LEFT, DIK_RIGHT, DIK_PERIOD, DIK_SLASH, DIK_RSHIFT, DIK_RMENU, DIK_RCONTROL, DIK_SPACE, DIK_COMMA, DIK_NUMPAD0, DIK_END, DIK_ESCAPE, DIK_DELETE, DIK_NEXT, DIK_P, DIK_RETURN },
	{ DIK_UP, DIK_DOWN, DIK_LEFT, DIK_RIGHT, DIK_PERIOD, DIK_SLASH, DIK_RSHIFT, DIK_RMENU, DIK_RCONTROL, DIK_SPACE, DIK_COMMA, DIK_NUMPAD0, DIK_END, DIK_ESCAPE, DIK_DELETE, DIK_NEXT, DIK_P, DIK_RETURN }
};
int joy_x;
int joy_y;
int joy_fire;

int Key(int number)// (F)
{
	short key = layout[1][number];

	if (number >= 256)
		return joy_fire & (1 << number);

	if (keymap[key])
		return 1;

	switch(key)
	{
		case DIK_RCONTROL:
			return keymap[DIK_LCONTROL];
		case DIK_LCONTROL:
			return keymap[DIK_RCONTROL];
		case DIK_RSHIFT:
			return keymap[DIK_LSHIFT];
		case DIK_LSHIFT:
			return keymap[DIK_RSHIFT];
		case DIK_RMENU:
			return keymap[DIK_LMENU];
		case DIK_LMENU:
			return keymap[DIK_RMENU];
	}

	if (conflict[number])
		return 0;

	key = layout[0][number];

	if (keymap[key])
		return 1;

	switch (key)
	{
	case DIK_RCONTROL:
		return keymap[DIK_LCONTROL];
	case DIK_LCONTROL:
		return keymap[DIK_RCONTROL];
	case DIK_RSHIFT:
		return keymap[DIK_LSHIFT];
	case DIK_LSHIFT:
		return keymap[DIK_RSHIFT];
	case DIK_RMENU:
		return keymap[DIK_LMENU];
	case DIK_LMENU:
		return keymap[DIK_RMENU];
	}

	return 0;
}

int S_UpdateInput()// (F)
{
	DI_UpdateJoystick();
	DI_ReadKeyboard(keymap);

	if (opt_ControlMethod == CM_JOYSTICK)
		joy_fire = DI_ReadJoystick(&joy_x, &joy_y);

	static int linput = 0;

	if (opt_ControlMethod == CM_JOYSTICK)
	{
		if (joy_x < -JOY_SENSITIVITY)
			linput |= IN_LEFT;
		else if (joy_x > JOY_SENSITIVITY)
			linput |= IN_RIGHT;

		if (joy_y > JOY_SENSITIVITY)
			linput |= IN_BACK;
		else if (joy_y < -JOY_SENSITIVITY)
			linput |= IN_FORWARD;
	}

	if (Key(KEY_FORWARD))
		linput |= IN_FORWARD;
	if (Key(KEY_BACK))
		linput |= IN_BACK;
	if (Key(KEY_LEFT))
		linput |= IN_LEFT;
	if (Key(KEY_RIGHT))
		linput |= IN_RIGHT;
	if (Key(KEY_DUCK))
		linput |= IN_DUCK;
	if (Key(KEY_SPRINT))
		linput |= IN_SPRINT;
	if (Key(KEY_WALK))
		linput |= IN_WALK;
	if (Key(KEY_JUMP))
		linput |= IN_JUMP;
	if (Key(KEY_ACTION))
		linput |= IN_ACTION | IN_SELECT;
	if (Key(KEY_DRAW))
		linput |= IN_DRAW;

	bool flare = false;
	static bool flare_no = false;

	if (opt_ControlMethod == CM_JOYSTICK)
	{
		if (Key(opt_JJmp + 256))
			linput |= IN_JUMP;
		if (Key(opt_JAct + 256))
			linput |= IN_ACTION | IN_SELECT;
		if (Key(opt_JDrw + 256))
			linput |= IN_DRAW;
		if (Key(opt_JDsh + 256))
			linput |= IN_SPRINT;
		if (Key(opt_JWlk + 256))
			linput |= IN_WALK;
		if (Key(opt_JDck + 256))
			linput |= IN_DUCK;			
		if (Key(opt_JFlr + 256))
			flare = true;
	}

	if (Key(KEY_FLARE) || flare)
	{
		if (!flare_no)
		{
			if (lara_item->current_anim_state == STATE_LARA_CRAWL_IDLE ||
				lara_item->current_anim_state == STATE_LARA_CRAWL_FORWARD ||
				lara_item->current_anim_state == STATE_LARA_CRAWL_TURN_LEFT ||
				lara_item->current_anim_state == STATE_LARA_CRAWL_TURN_RIGHT ||
				lara_item->current_anim_state == STATE_LARA_CRAWL_BACK ||
				lara_item->current_anim_state == STATE_LARA_CRAWL_TO_CLIMB)
			{
				SoundEffect(SFX_LARA_NO, nullptr, 2);
				flare_no = true;
			}
			else
			{
				flare_no = false;
				linput |= IN_FLARE;
			}
		}
	}
	else
	{
		flare_no = false;
	}

	if (Key(KEY_LOOK))
		linput |= IN_LOOK;
	if (Key(KEY_ROLL))
		linput |= IN_ROLL;
	if (Key(KEY_OPTION))
		linput |= IN_OPTION;
	if (Key(KEY_STEPL))
		linput |= IN_WALK | IN_LEFT;
	if (Key(KEY_STEPR))
		linput |= IN_WALK | IN_RIGHT;
	if (Key(KEY_PAUSE))
		linput |= IN_PAUSE;
	if (Key(KEY_SELECT))
		linput |= IN_SELECT;

	if (opt_ControlMethod == CM_JOYSTICK)
	{
		if (Key(opt_JLok + 256))
			linput |= IN_LOOK;
		if (Key(opt_JRol + 256))
			linput |= IN_ROLL;
		if (Key(opt_JInv + 256))
			linput |= IN_OPTION;
	}

	if (keymap[DIK_ESCAPE])
		linput |= IN_OPTION | IN_DESELECT;

	static int look_timeout;

	if (lara.gun_status == LG_READY)
	{
		savegame.AutoTarget = App.tAutoTarget;

		if (linput & IN_LOOK)
		{
			if (look_timeout >= 6)
			{
				look_timeout = 100;
			}
			else
			{
				linput &= ~IN_LOOK;
				look_timeout++;
			}
		}
		else
		{
			if (look_timeout != 0 && look_timeout != 100)
			{
				linput |= IN_UNK31;
			}

			look_timeout = 0;
		}
	}

	static int medipack_timeout;

	if (keymap[DIK_0])
	{
		if (medipack_timeout == 0)
		{
			if (lara_item->hit_points > 0 && lara_item->hit_points < 1000 || lara.poisoned)
			{
				if (lara.num_small_medipack != 0)
				{
					if (lara.num_small_medipack != -1)
						lara.num_small_medipack--;

					lara.dpoisoned = 0;
					lara_item->hit_points += 500;

					if (lara_item->hit_points > 1000)
					{
						lara_item->hit_points = 1000;
						SoundEffect(SFX_MENU_MEDI, nullptr, 2);
						savegame.Game.HealthUsed++;
					}
				}

				medipack_timeout = 15;
			}
		}
	}
	else if(keymap[DIK_9])
	{
		if (medipack_timeout == 0)
		{
			if (lara_item->hit_points > 0 && lara_item->hit_points < 1000 || lara.poisoned)
			{
				if (lara.num_large_medipack != 0)
				{
					if (lara.num_large_medipack != -1)
						lara.num_large_medipack--;

					lara.dpoisoned = 0;
					lara_item->hit_points += 1000;

					if (lara_item->hit_points > 1000)
					{
						lara_item->hit_points = 1000;
						SoundEffect(SFX_MENU_MEDI, nullptr, 2);
						savegame.Game.HealthUsed++;
					}
				}

				medipack_timeout = 15;
			}
		}
	}
	else if (medipack_timeout != 0)
	{
		medipack_timeout--;
	}

	if (keymap[DIK_F10])
		linput |= IN_E;

	if (linput & IN_WALK && !(linput & IN_FORWARD) && !(linput & IN_BACK))
	{
		if (linput & IN_LEFT)
		{
			linput &= ~IN_LEFT;
			linput |= IN_LSTEP;
		}
		else if (linput & IN_RIGHT)
		{
			linput &= ~IN_RIGHT;
			linput |= IN_RSTEP;
		}
	}

	if (linput & IN_FORWARD && linput & IN_BACK)
		linput |= IN_ROLL;

	if (linput & IN_ROLL && BinocularRange)
		linput &= ~IN_ROLL;

	if (linput & IN_LEFT && linput & IN_RIGHT)
		linput &= ~(IN_LEFT | IN_RIGHT);

	if (SetDebounce)
		dbinput = inputBusy;

	if (gfGameMode == 0 && Gameflow->LoadSaveEnabled)
	{
		if (keymap[DIK_F5])
			linput |= IN_SAVE;
		if (keymap[DIK_F6])
			linput |= IN_LOAD;
	}

	if (Gameflow->CheatEnabled)
	{
		static int cheat_code = 0;

		if (linput != 0)
			cheat_code = 0;

		switch(cheat_code)
		{
		case 0:
			if (Key(DIK_D))
				cheat_code = 1;
			break;
		case 1:
			if (Key(DIK_O))
				cheat_code = 2;
			break;
		case 2:
			if (Key(DIK_Z))
				cheat_code = 3;
			break;
		case 3:
			if (Key(DIK_Y))
				linput = IN_CHEAT;
			break;
		}
	}

	inputBusy = linput;
	input = linput;

	if (lara.Busy)
	{
		linput &= (IN_FORWARD | IN_BACK | IN_LEFT | IN_RIGHT | IN_OPTION | IN_LOOK | IN_PAUSE);

		if (linput & IN_FORWARD && linput & IN_BACK)
			linput &= ~IN_BACK;
	}

	if (SetDebounce)
		dbinput = input & (dbinput ^ input);

	if (keymap[DIK_F])
		linput |= IN_FORWARD;
	else
		linput = IN_NONE;

	dbginput = input;

	return true;
}