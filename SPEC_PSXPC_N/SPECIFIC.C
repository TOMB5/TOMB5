#include "SPECIFIC.H"

#include "3D_OBJ.H"
#include "BUBBLES.H"
#include "CAMERA.H"
#include "CD.H"
#include "CONTROL.H"
#include "EFFECTS.H"
#include "FXTRIG.H"
#include "GAMEFLOW.H"
#include "MEMCARD.H"
#include "MISC.H"
#include "GPU.H"
#include "LARA.H"
#include "LOADSAVE.H"
#include "PROFILE.H"
#include "PSXINPUT.H"
#include "REQUEST.H"
#include "SAVEGAME.H"
#include "SFX.H"
#include "SOUND.H"
#include "TEXT_S.H"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

//#include <SYS/TYPES.H>
#include <LIBSPU.H>
#include <LIBAPI.H>
#include <STRINGS.H>
static struct REQUESTER PauseReq = { STR_PAUSED,  8, 3, 0, 5, 0, 0, 0, 0, { STR_RESUME, STR_QUIT,  STR_GAME_SETTINGS, 0, 0 } };
static struct REQUESTER AdjustReq = { STR_USE_DIRECTIONAL_BUTTONS, 8, 0, 0, 0, 0, 0, 0, 0,{ 0, 0, 0, 0, 0 } };
static struct REQUESTER QuitReq = { STR_CONFIRM_QUIT, 8, 2, 1, 2, 0, 0, 0, 0,{ STR_YES, STR_NO, 0, 0, 0 } };
static struct REQUESTER StatisticsReq = { STR_STATISTICS, 8, 1, 1, 5, 0, 0, 0, 1,{ STR_ELLIPSIS_BIS, 0, 0, 0, 0 } };

static unsigned short PadStrings[5][8] =
{
	{ STR_ACTION, STR_JUMP, STR_DRAW_WEAPON, STR_ROLL, STR_LOOK, STR_DUCK, STR_WALK, STR_DASH },
	{ STR_JUMP, STR_DRAW_WEAPON, STR_ROLL, STR_ACTION, STR_DUCK, STR_LOOK, STR_DASH, STR_WALK },
	{ STR_DRAW_WEAPON, STR_ROLL, STR_JUMP, STR_ACTION, STR_WALK, STR_DASH, STR_LOOK, STR_DUCK },
	{ STR_ROLL, STR_ACTION, STR_LOOK, STR_JUMP, STR_DRAW_WEAPON, STR_DUCK, STR_WALK, STR_DASH },
	{ STR_WALK, STR_LOOK, STR_DASH, STR_DUCK, STR_JUMP, STR_ROLL, STR_ACTION, STR_DRAW_WEAPON }
};

static unsigned char PauseMenuNum;
unsigned short AnimComp;
short AnimatingTexturesVOffset;
struct REQUESTER SettingsReq = { STR_GAME_SETTINGS, 8, 5, 0, 5, 0, 3, 3, 0,{ STR_SFX_VOLUME, STR_MUSIC_VOLUME, STR_CONFIGURE_CONTROLS, STR_SCREEN_ADJUST, STR_MANUAL_TARGETING } };
struct REQUESTER ConfigReq = { STR_CONFIGURE_CONTROLS, 8, 3, 1, 5, 0, 0, 2, 1,{ STR_ELLIPSIS, STR_CONFIGURATION, STR_VIBRATION_ON, 0, 0 } };
unsigned char SoundFXVolume;
unsigned short nAnimTextureRanges;
unsigned short* AnimTextureRanges;
unsigned short nAnimUVRanges;
int GtSFXEnabled;
short AnimatingTexturesV[16][8][3];

static char byte_A1F40 = 0;
static char byte_A1F41 = 4;

void S_control_screen_position()//6068C(<), 61204(<)
{
	if (input & 1)
	{
		savegame.ScreenY--;

		if ((savegame.ScreenY << 16) < 0)
		{
			savegame.ScreenY = 0;
		}
	}
	else if (input & 2)
	{
		//loc_606D0
		savegame.ScreenY++;

		if (savegame.ScreenY > 40)
		{
			savegame.ScreenY = 40;
		}
	}

	//loc_60708
	if (input & 4)
	{
		savegame.ScreenX--;

		if (savegame.ScreenX < -10)
		{
			savegame.ScreenX = -10;
		}

	}
	else if (input & 8)
	{
		//loc_60750
		savegame.ScreenX++;

		if (savegame.ScreenX > 32)
		{
			savegame.ScreenX = 32;
		}
	}

	//loc_60784
	GPU_SetScreenPosition(savegame.ScreenX, savegame.ScreenY);
}

long S_DumpScreen()//607A8(<), 61320(<) (F)
{
	return GPU_FlipNoIdle();
}

void S_ExitSystem(char* exit_message)//607C8, * (F)
{
	SetSp(0x801FFFE0);

	printf("\n Exit Message: %s\n", exit_message);

	while (1)
	{
		SetDispMask(0);
		SetDispMask(1);
	}
}

void DisplayConfig(int x, int y)//6080C(<), 61340(<) (F)
{
	unsigned short* wp;
	char buf[80];
	int seconds;

	if (PauseMenuNum == 20)
	{
		PrintString(112, y, 2, "\x14\x00\x00\x00", FF_CENTER);
		PrintString(112, y + 18, 2, "\x15\x00\x00\x00", FF_CENTER);
		PrintString(400, y, 2, "\x17\x00\x00\x00", FF_CENTER);
		PrintString(400, y + 18, 2, "\x16\x00\x00\x00", FF_CENTER);
		PrintString(112, y + 36, 2, "\x1E\x00\x00\x00", FF_CENTER);
		PrintString(112, y + 54, 2, "\x1F\x00\x00\x00", FF_CENTER);
		PrintString(400, y + 36, 2, "\x1C\x00\x00\x00", FF_CENTER);
		PrintString(400, y + 54, 2, "\x1D\x00\x00\x00", FF_CENTER);
		
		wp = &PadStrings[savegame.ControlOption][0];

		PrintString(140, y, 5, &gfStringWad[gfStringOffset[wp[0]]], FF_NONE);
		PrintString(140, y + 18, 5, &gfStringWad[gfStringOffset[wp[1]]], FF_NONE);
		PrintString(372, y, 5, &gfStringWad[gfStringOffset[wp[2]]], FF_R_JUSTIFY);
		PrintString(372, y + 18, 5, &gfStringWad[gfStringOffset[wp[3]]], FF_R_JUSTIFY);
		PrintString(140, y + 36, 5, &gfStringWad[gfStringOffset[wp[4]]], FF_NONE);
		PrintString(140, y + 54, 5, &gfStringWad[gfStringOffset[wp[5]]], FF_NONE);
		PrintString(372, y + 36, 5, &gfStringWad[gfStringOffset[wp[6]]], FF_R_JUSTIFY);
		PrintString(372, y + 54, 5, &gfStringWad[gfStringOffset[wp[7]]], FF_R_JUSTIFY);
	}
	else
	{
		//loc_60B2C
		PrintString(x, y, 5, &gfStringWad[gfStringOffset[STR_TIME_TAKEN]], FF_NONE);
		PrintString(x, y + 18, 5, &gfStringWad[gfStringOffset[STR_DISTANCE_TRAVELLED]], FF_NONE);
		PrintString(x, y + 36, 5, &gfStringWad[gfStringOffset[STR_AMMO_USED]], FF_NONE);
		PrintString(x, y + 54, 5, &gfStringWad[gfStringOffset[STR_HEALTH_PACKS_USED]], FF_NONE);
		PrintString(x, y + 72, 5, &gfStringWad[gfStringOffset[STR_SECRETS_FOUND]], FF_NONE);

		seconds = GameTimer / 30;

		sprintf(&buf[0], "%d %s %d:%.2d:%.2d", seconds / 86400, &gfStringWad[gfStringOffset[STR_DAYS]], seconds % 0x15180 / 0xE10, seconds / 0x3C, seconds % 0x3C);
		PrintString(SCREEN_WIDTH - x, y, 5, &buf[0], FF_R_JUSTIFY);

		sprintf(&buf[0], "%dm", savegame.Game.Distance / 0x1A3);
		PrintString(SCREEN_WIDTH - x, y + 18, 5, &buf[0], FF_R_JUSTIFY);

		sprintf(&buf[0], "%d", savegame.Game.AmmoUsed);
		PrintString(SCREEN_WIDTH - x, y + 36, 5, &buf[0], FF_R_JUSTIFY);

		sprintf(&buf[0], "%d", savegame.Game.HealthUsed);
		PrintString(SCREEN_WIDTH - x, y + 36, 5, &buf[0], FF_R_JUSTIFY);

		sprintf(&buf[0], "%d / 36", savegame.Game.Secrets);
		PrintString(SCREEN_WIDTH - x, y + 54, 5, &buf[0], FF_R_JUSTIFY);

		PrintString(SCREEN_WIDTH / 2, y + 98, 8, &gfStringWad[gfStringOffset[STR_CURRENT_LOCATION]], FF_CENTER);
		DrawLineH(x, (y + 100), ((256 - x) << 1) & 0xFFFE, 1, 0, 0xC0C0C0);
		DrawTPage(1, 1);
		PrintString(SCREEN_WIDTH / 2, y + 118, 5, &gfStringWad[gfStringOffset[gfLevelNames[gfCurrentLevel]]], FF_CENTER);
	}
}

int DoPauseMenu()//60F34(<), 61A68(<) (F)
{
	char* s;
	long result;
	int prompt;
	unsigned short* vol;
	short level;
	/* ??? */
	static int cursor;
	struct REQUESTER* AutoRequester;
	static unsigned char AutoTime;
	static unsigned char AutoFunc;
	/* ??? */

	s = &gfStringWad[gfStringOffset[STR_CONFIGURATION]];

	prompt = 0;
	s[strlen(s) - 1] = savegame.ControlOption + 0x31;

	switch (PauseMenuNum)
	{
	case 0:
		//loc_60FBC
		result = Requester(&PauseReq);

		if (result)
		{
			QuitReq.CursorPos = 1;
			SettingsReq.CursorPos = 0;

			if (savegame.AutoTarget)
			{
				SettingsReq.OptionTxt[4] = STR_AUTOMATIC_TARGETING;
			}
			else
			{
				//loc_61B40
				SettingsReq.OptionTxt[4] = STR_MANUAL_TARGETING;
			}

			//loc_61B40
			if (savegame.VibrateOn)
			{
				ConfigReq.OptionTxt[2] = STR_VIBRATION_ON;
			}
			else
			{
				ConfigReq.OptionTxt[2] = STR_VIBRATION_OFF;
			}

			PauseMenuNum = result + 1;

		}//loc_61B68
		prompt = 2;
		break;
	case 1:
		//loc_6103C
		PauseMenuNum = 0;
		PauseReq.CursorPos = 0;
		return 1;
		break;
	case 2:
		//loc_6105C
		result = Requester(&QuitReq);
		if (result)
		{
			if (result == 0x8000)
			{
				reset_flag = 1;
				return 1;
			}

			PauseMenuNum = 0;

		}//loc_61090

		PrintString(SCREEN_WIDTH, 232, 5, &gfStringWad[gfStringOffset[STR_SELECT]], FF_CENTER);
		break;
	case 3:
		//loc_610C8
		result = Requester(&SettingsReq);

		if (result == 0x8002)
		{
			PauseMenuNum = 20;
			ConfigReq.CursorPos = 1;
			prompt = 3;
		}
		else if (result == 0x8003)
		{
			PauseMenuNum = 10;
			prompt = 3;
		}
		else if (result == 0x8004)
		{
			if (savegame.AutoTarget)
			{
				SettingsReq.OptionTxt[4] = STR_AUTOMATIC_TARGETING;
			}
			else
			{
				SettingsReq.OptionTxt[4] = STR_MANUAL_TARGETING;
			}
			//loc_61144
			savegame.AutoTarget ^= 1;

			//loc_61160
			if (SettingsReq.CursorPos < 2)
			{
				if (SettingsReq.CursorPos != 0)
				{
					vol = &savegame.VolumeCD;
				}
				else
				{
					vol = &savegame.VolumeFX;
				}

				//loc_61198
				level = *vol;
				if ((input & IN_LEFT))
				{
					level -= 10;

					if (level < 0)
					{
						level = 0;
					}
				}//loc_611C8

				if ((input & IN_RIGHT))
				{
					level = *vol + 10;

					if (level > 255)
					{
						level = 255;
					}
				}
				//loc_611EC
				*vol = level;

				if (SettingsReq.CursorPos == 0)
				{
					SoundFXVolume = level;
					SoundEffect(SFX_TICK_TOCK, NULL, 2);
				}
				else
				{
					CDDA_SetMasterVolume(level);
				}
			}//loc_61224
			prompt = 3;
		}
		break;
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
	case 18:
	case 19:
		//loc_614BC
		if (prompt != 0)
		{
			if (prompt == 3)
			{
				PrintString(SCREEN_WIDTH / 2, 232, 5, &gfStringWad[gfStringOffset[STR_SELECT]], FF_CENTER);
				PrintString(496, 232, 5, &gfStringWad[gfStringOffset[STR_BACK]], FF_R_JUSTIFY);
			}
			else if (prompt == 2)
			{
				//61520
				PrintString(SCREEN_WIDTH / 2, 232, 5, &gfStringWad[gfStringOffset[STR_SELECT]], FF_CENTER);
			}
			else
			{
				PrintString(SCREEN_WIDTH / 2, 232, 5, &gfStringWad[gfStringOffset[STR_CANCEL]], FF_CENTER);
			}

			if ((RawEdge & IN_TRIANGLE))
			{
				SoundEffect(SFX_MENU_CHOOSE, NULL, 2);
				PauseMenuNum = 0;
			}
		}
		break;
	case 10:
		//loc_6122C
		Requester(&AdjustReq);

		PrintString(SCREEN_WIDTH / 2, 232, 5, &gfStringWad[gfStringOffset[STR_OK]], FF_CENTER);
		DrawLineV(16, 16, 209, 0, 0x404040, 0);
		DrawLineV(496, 16, 209, 0, 0x404040, 0);
		DrawLineH(16, 16, 481, 0, 0x404040, 0);
		DrawLineH(16, 224, 481, 0, 0x404040, 0);

		S_control_screen_position();

		if ((RawEdge & IN_CROSS))
		{
			SoundEffect(SFX_MENU_CHOOSE, NULL, 2);
		}

		PauseMenuNum = 3;

		break;
	case 20:
		//loc_612F4
		if (DualShock)
		{
			ConfigReq.nOptions = 3;
		}
		else
		{
			//loc_6130C
			ConfigReq.nOptions = 2;
		}

		if (Requester(&ConfigReq) == 0x8002)
		{
			if (ConfigReq.OptionTxt[2] == STR_VIBRATION_OFF)
			{
				savegame.VibrateOn = 1;
				ConfigReq.OptionTxt[2] = STR_VIBRATION_ON;
			}
			else
			{
				//loc_61368
				savegame.VibrateOn = 0;
				ConfigReq.OptionTxt[2] = STR_VIBRATION_OFF;
			}
		}//lov_63170

		if (ConfigReq.CursorPos == 1)
		{
			if ((RawEdge & IN_DPAD_LEFT) && savegame.ControlOption != 0)
			{
				SoundEffect(SFX_MENU_SELECT, NULL, 2);

				if (savegame.ControlOption != 0)
				{
					savegame.ControlOption--;
				}
				else
				{
					savegame.ControlOption = 4;
				}
			}
			else if ((RawEdge & IN_DPAD_RIGHT))
			{
				//613E4
				if (savegame.ControlOption < 4)
				{
					SoundEffect(SFX_MENU_SELECT, NULL, 2);

					if (savegame.ControlOption < 4)
					{
						savegame.ControlOption++;
					}
					else
					{
						//6142C
						savegame.ControlOption = 0;
					}
				}
			}
		}
		else
		{
			//loc_61434
			PrintString(256, 232, 5, &gfStringWad[gfStringOffset[STR_SELECT]], FF_CENTER);
		}

		//61460
		PrintString(496, 232, 5, &gfStringWad[gfStringOffset[STR_BACK]], FF_R_JUSTIFY);

		if ((RawEdge & IN_TRIANGLE))
		{
			SoundEffect(SFX_MENU_CHOOSE, NULL, 0);
			PauseMenuNum = 3;
		}//614BC

		break;
	case 21:
		//loc_62AE0
		if (mcNumFiles == 0)
		{
			Requester(&NoGamesReq);
		}
		else
		{
			PrintString(SCREEN_WIDTH / 2, 32, 8, &gfStringWad[gfStringOffset[STR_SELECT_GAME_TO_LOAD]], FF_CENTER);

			DisplayFiles(cursor, mcNumFiles);

			if ((RawEdge & IN_DPAD_UP) && cursor != 0)
			{
				SoundEffect(SFX_MENU_SELECT, NULL, 0);
				cursor--;
			}//62B9C
			else if ((RawEdge & IN_DPAD_DOWN) && cursor < mcNumFiles)
			{
				SoundEffect(SFX_MENU_SELECT, NULL, 0);
				cursor++;
			}//62BEC
			else if ((RawEdge & IN_CROSS))
			{
				SoundEffect(SFX_MENU_CHOOSE, NULL, 0);

				byte_A1F41 = 7;
				AutoRequester = &LoadingReq;
				AutoTime = 3;
				AutoFunc = 11;
				prompt = 0;

				Requester(AutoRequester);

				if (AutoTime == 0)
				{
					if (AutoFunc == 255)
					{
						//62DC0
						prompt = 0;

						if (prompt != 0)
						{
							PrintString(SCREEN_WIDTH / 2, 232, 5, &gfStringWad[gfStringOffset[STR_CANCEL]], FF_CENTER);

							if ((RawEdge & IN_TRIANGLE))
							{
								byte_A1F40 = 0;
								return -1;
							}

						}//62E14

						return 1;
					}
				}
				//62c6c
			}
		}
		//62DC0
		prompt = 0;

		if (prompt != 0)
		{
			PrintString(SCREEN_WIDTH / 2, 232, 5, &gfStringWad[gfStringOffset[STR_CANCEL]], FF_CENTER);

			if ((RawEdge & IN_TRIANGLE))
			{
				byte_A1F40 = 0;
				return -1;
			}
		}
		//62E14
		break;
	}

	return 0;
}

void gInit()//615CC(<), 6210C(<) (F)
{
	SOUND_Stop();
	XAFadeRate = 32;
	XAReqVolume = 0;

#if DEBUG_VERSION
	ProfileDraw = 0;
#endif
	CreateMonoScreen();

	if (XAVolume != 0)
	{
		do
		{
			XAReqVolume = 0;
		} while (XAVolume != 0);
	}

	S_CDPause();
	S_SetReverbType(1);
	camera.number_frames = 2;

	return;
}

short S_Death()//61658(<), 622C8(<) (F)
{
	short ret;
	unsigned char flag;
	unsigned char Cursor;

	ret = 0;
	flag = 0;
	Cursor = 0;

	gInit();
	mcOpen(0);

	//loc_6169C, loc_63230C
	while (ret == 0)
	{

#if !BETA_VERSION
		Motors[1] = 0;
		Motors[0] = 0;
#endif

		XAReqVolume = 0;

		GPU_BeginScene();
		SetDebounce = 1;
		S_UpdateInput();
		UpdatePulseColour();
		lara.death_count++;


		if (!PadConnected)
		{
			PrintString(SCREEN_WIDTH / 2, 0x40, 3, &gfStringWad[gfStringOffset[STR_CONTROLLER_REMOVED]], (FF_CENTER | FF_UNK13));
		}
		else
		{
			if (flag == 0)
			{
				//loc_6171C
				if (mcGetStatus() == 0 && mcNumFiles != 0)
				{
					if (Cursor != 0)
					{
						PrintString(SCREEN_WIDTH / 2, 0xC0, 2, &gfStringWad[gfStringOffset[STR_LOAD_GAME_BIS]], FF_CENTER);
					}
					else
					{
						PrintString(SCREEN_WIDTH / 2, 0xC0, 1, &gfStringWad[gfStringOffset[STR_LOAD_GAME_BIS]], FF_CENTER);
					}

					if (Cursor != 0)
					{
						PrintString(SCREEN_WIDTH / 2, 0xD0, 1, &gfStringWad[gfStringOffset[STR_EXIT_TO_TITLE]], FF_CENTER);
					}
					else
					{
						PrintString(SCREEN_WIDTH / 2, 0xD0, 2, &gfStringWad[gfStringOffset[STR_EXIT_TO_TITLE]], FF_CENTER);
					}

					if (Cursor != 0)
					{
						if ((RawEdge & IN_DPAD_UP))
						{
							SoundEffect(SFX_MENU_SELECT, NULL, 2);
							Cursor = 0;
						}
						else if ((RawEdge & IN_CROSS))
						{
							//loc_617E0
							SoundEffect(SFX_MENU_CHOOSE, NULL, 2);
							ret = 1;
						}
					}
					else
					{
						//loc_61800
						if ((RawEdge & IN_DPAD_DOWN))
						{
							SoundEffect(SFX_MENU_SELECT, NULL, 2);
							Cursor = 1;
						}
						else if ((RawEdge & IN_CROSS))
						{
							//loc_617E0
							SoundEffect(SFX_MENU_CHOOSE, NULL, 2);
							flag = 1;
						}
					}
				}
				else
				{
					//loc_6184C
					if (lara.death_count > 300)
					{
						ret = 1;
					}
				}

				//loc_61888
				PrintString(SCREEN_WIDTH / 2, 0x78, 3, &gfStringWad[gfStringOffset[STR_GAME_OVER]], FF_CENTER);
			}
			else if (flag == 1)
			{
				//loc_6189C
				ret = LoadGame();

				if (ret != 0)
				{
					if (ret > 0)
					{
						ret = 2;
					}
					else
					{
						flag = 0;
						ret = 0;
					}
				}
			}
		}

		//loc_618C4
		SOUND_EndScene();
		DrawMonoScreen(0x203040);
		GPU_EndScene();
		camera.number_frames = S_DumpScreen();
	}

	mcClose();
	return ret;
}

void DisplayStatsUCunt()//61928(<), 625A8(<) (F)
{
	Requester(&StatisticsReq);
}

/*
void S_Warn(const char* warning_message)
{
	printf(warning_message);
#ifndef NDEBUG
	//assert(0);
#endif
}*/

void S_CalculateLight(long x, long y, long z, short room, struct ITEM_LIGHT* light)
{
	UNIMPLEMENTED();
}
