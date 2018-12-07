#include "HEALTH.H"

#include "DELTAPAK.H"
#include "DRAW.H"
#if PSXENGINE
#include "GPU.H"
#include "DRAWPHAS.H"
#include "FXTRIG.H"
#include "SHADOWS.H"
#endif

#if PSX_VERSION
#include "PSXINPUT.H"
#endif
#if PSXPC_VERSION
#include "PSXPCINPUT.H"
#endif

#include "GAMEFLOW.H"
#include "LARA.H"
#include "SPOTCAM.H"
#include "SAVEGAME.H"

#include <stdio.h>
#include "SPECIFIC.H"
#include "OBJECTS.H"
#include "NEWINV2.H"
#include "TEXT.H"

int health_bar_timer = 0;
char PoisonFlag = 0;
struct DISPLAYPU pickups[8];
short PickupX = 0;
short PickupY = 0;
short PickupVel = 0;
short CurrentPickup = 0;

void AddDisplayPickup(short object_number)//3B6F4, ? (F)
{
	struct DISPLAYPU* pu = &pickups[0];
	long lp;
	if (gfCurrentLevel == LVL5_SUBMARINE && object_number == PUZZLE_ITEM1 ||
		gfCurrentLevel == LVL5_OLD_MILL && object_number == PUZZLE_ITEM3)
	{
		object_number = CROWBAR_ITEM;
	}

	for(lp = 0; lp < 8; lp++, pu++)
	{
		if (pu->life < 0)
		{
			pu->life = 45;
			pu->object_number = object_number;
			break;
		}
	}

	DEL_picked_up_object(object_number);
}

void DrawPickups(int timed)// (F)
{
	struct DISPLAYPU* pu = &pickups[CurrentPickup];
	long lp;

	if (pu->life > 0)
	{
		if (PickupX > 0)
		{
			PickupX += (-PickupX >> 3);
		}
		else
		{
			pu->life--;
		}
	}
	else if (pu->life == 0)
	{
		if (PickupX < 128)
		{
			if (PickupVel < 16)
				PickupX += ++PickupVel;
		}
		else
		{
			pu->life = -1;
			PickupVel = 0;
		}
	}
	else
	{
		for (lp = 0; lp < 8; lp++)
		{
			if (pickups[(CurrentPickup + lp) % 8].life > 0)
				break;
		}

		if (lp == 8)
		{
			CurrentPickup = 0;
			return;
		}

		CurrentPickup = (CurrentPickup + lp) % 8;
	}

	S_DrawPickup(pu->object_number);
}

void InitialisePickUpDisplay()//3B580, 3B9DC (F)
{
	int i;
	for (i = 7; i > -1; i--)
	{
		pickups[i].life = -1;
	}

	PickupY = 128;
	PickupX = 128;
	PickupVel = 0;
	CurrentPickup = 0;
}

void DrawAirBar(int flash_state)//3B3CC
{
#if PC_VERSION
	if (lara.air == 1800 || lara_item->hit_points <= 0)
		return;

	short val = CLAMP(lara.air, 0, 1800);

	if (val > 450 || flash_state)
	{
		S_DrawAirBar(100 * val / 1800);
	}
	else
	{
		S_DrawAirBar(0);
	}

	if (lara.Gassed)
	{
		if (lara.dpoisoned < 2048)
			lara.dpoisoned += 2;

		lara.Gassed = FALSE;
	}
#elif PSX_VERSION

	int air;

	if (lara.air == 1800 || lara_item->hit_points <= 0)
	{
		//loc_3B570
		return;
	}

	air = lara.air;

	//clamp
	if (air < 0)
	{
		air = 0;
	}//loc_3B424
	else if (air > 1080)
	{
		air = 1080;
	}//loc_3B434

	if (air > 450)
	{
		if (flash_state != 0)
		{
			S_DrawGouraudBar(343, 32, 133, ((((((((air * 0x38E38E39) >> 2) - (air >> 31) >> 5) + ((air * 0x38E38E39) >> 2) - (air >> 31)) << 2) + ((air * 0x38E38E39) >> 2) - (air >> 31)) * 0x51EB851F) >> 5) - (((((((air * 0x38E38E39) >> 2) - (air >> 31) >> 5) + ((air * 0x38E38E39) >> 2) - (air >> 31)) << 2) + ((air * 0x38E38E39) >> 2) - (air >> 31)) >> 31), &airBarColourSet);
		}
		else
		{
			//loc_3B4A8
			S_DrawGouraudBar(343, 32, 133, 0, &airBarColourSet);
		}
	}
	else
	{
		//loc_3B4D0
		S_DrawGouraudBar(343, 32, 133, ((((((((air * 0x38E38E39) >> 2) - (air >> 31) << 5) + ((air * 0x38E38E39) >> 2) - (air >> 31)) << 2) + ((air * 0x38E38E39) >> 2) - (air >> 31)) * 0x51EB851F) >> 5) - (((((((air * 0x38E38E39) >> 2) - (air >> 31) << 5) + ((air * 0x38E38E39) >> 2) - (air >> 31)) << 2) + ((air * 0x38E38E39) >> 2) - (air >> 31)) >> 31), &airBarColourSet);
	}

	//loc_3B534
	if (lara.Gassed)
	{
		if (lara.dpoisoned < 2048)
		{
			lara.dpoisoned += 2;
		}
		//loc_3B560
		lara.Gassed = 0;

	}//loc_3B570
#endif
}

void DrawHealthBar(int flash_state)
{
#if PC_VERSION
	static short old_val = 0;
	short val = CLAMP(lara_item->hit_points, 0, 1000);

	if (old_val != val)
	{
		old_val = val;
		health_bar_timer = 40;
	}

	if (health_bar_timer < 0)
		health_bar_timer = 0;

	if (val <= 250)
	{
		if (BinocularRange)
		{
			if (flash_state)
				S_DrawHealthBar2(val / 10);
			else
				S_DrawHealthBar2(0);
		}
		else
		{
			if (flash_state)
				S_DrawHealthBar(val / 10);
			else
				S_DrawHealthBar(0);
		}
	}

	if (health_bar_timer > 0 
		|| val <= 0 
		|| lara.gun_status == LG_READY && lara.gun_type == WEAPON_FLARE_2 
		|| lara.poisoned >= 256)
	{
		if (BinocularRange || SniperOverlay)
		{
			S_DrawHealthBar2(val / 10);
		}
		else
		{
			S_DrawHealthBar(val / 10);
		}
	}

	if (PoisonFlag)
		PoisonFlag--;
#else
	UNIMPLEMENTED();
#endif
}

void DrawGameInfo(int timed)//3AD68(<), 3B268(<)
{
	int flash_state;
	char sbuf[80];
	char buf[80];
	int seconds;

#if PC_VERSION
	if (GLOBAL_playing_cutseq == 0 &&
		!bDisableLaraControl &&
		gfGameMode != 1)
	{
		int flash_state = FlashIt();
		DrawHealthBar(flash_state);
		DrawAirBar(flash_state);
		DrawPickups(timed);
		/*if (DashTimer < 120)
			s_drawdas*/
	}
#elif /*PSXPC_VERSION ||*/ PSX_VERSION

	if (GLOBAL_playing_cutseq == 0 && !bDisableLaraControl)
	{
#if DEBUG_VERSION
		sprintf(&sbuf[0], "Room:%d X:%d Y:%d Z:%d", lara_item->room_number, (lara_item->pos.z_pos - room[lara_item->room_number].z) >> 10, (lara_item->pos.y_pos - room[lara_item->room_number].minfloor) >> 8, (lara_item->pos.x_pos - room[lara_item->room_number].x) >> 10);
		PrintString(SCREEN_WIDTH / 2, 24, 0, &sbuf[0], 0x8000);
#endif
		if (gfGameMode != 1)
		{

			flash_state = FlashIt();
			DrawHealthBar(flash_state);
			DrawAirBar(flash_state);
			DrawPickups(timed);

			if (DashTimer < 120)
			{
				S_DrawGouraudBar(0x2E, 0x85, 0x157, (((((((((((((DashTimer << 1) + DashTimer) << 3) + DashTimer) << 2) * 0x88888889) + (((((DashTimer << 1) + DashTimer) << 3) + DashTimer) << 2)) >> 6) - (((((DashTimer << 1) + DashTimer) << 3) + DashTimer) << 2) >> 31) << 5) + (((((((((DashTimer << 1) + DashTimer) << 3) + DashTimer) << 2) * 0x88888889) + (((((DashTimer << 1) + DashTimer) << 3) + DashTimer) << 2)) >> 6) - (((((DashTimer << 1) + DashTimer) << 3) + DashTimer) << 2) >> 31)) << 2) + (((((((((DashTimer << 1) + DashTimer) << 3) + DashTimer) << 2) * 0x88888889) + (((((DashTimer << 1) + DashTimer) << 3) + DashTimer) << 2)) >> 6) - (((((DashTimer << 1) + DashTimer) << 3) + DashTimer) << 2) >> 31) * 0x51EB851F) >> 5 - (((((((((((((DashTimer << 1) + DashTimer) << 3) + DashTimer) << 2) * 0x88888889) + (((((DashTimer << 1) + DashTimer) << 3) + DashTimer) << 2)) >> 6) - (((((DashTimer << 1) + DashTimer) << 3) + DashTimer) << 2) >> 31) << 5) + (((((((((DashTimer << 1) + DashTimer) << 3) + DashTimer) << 2) * 0x88888889) + (((((DashTimer << 1) + DashTimer) << 3) + DashTimer) << 2)) >> 6) - (((((DashTimer << 1) + DashTimer) << 3) + DashTimer) << 2) >> 31)) << 2) + (((((((((DashTimer << 1) + DashTimer) << 3) + DashTimer) << 2) * 0x88888889) + (((((DashTimer << 1) + DashTimer) << 3) + DashTimer) << 2)) >> 6) - (((((DashTimer << 1) + DashTimer) << 3) + DashTimer) << 2) >> 31)) >> 31, &dashBarColourSet);
			}//loc_3AF14

			if ((gfLevelFlags & GF_LVOP_TIMER) && savegame.Level.Timer != 0 && 0x1A5E0 > savegame.Level.Timer)
			{
				seconds = (savegame.Level.Timer * 0x88888889) >> 4;

				sprintf(&buf[0], "%.2d", (((savegame.Level.Timer * 0x88888889) >> 4) * 0x88888889) + (seconds >> 31) >> 5 - 0x1A5DF);
				PrintString(0x28, 0x18, 0, &buf[0], 0);
				PrintString(0x3C, 0x18, 0, ":", 0);

				sprintf(&buf[0], "%.2d", seconds - ((((savegame.Level.Timer * 0x88888889) >> 4) * 0x88888889) + (seconds >> 31) >> 5 - 0x1A5DF) << 4) - ((((savegame.Level.Timer * 0x88888889) >> 4) * 0x88888889) + (seconds >> 31) >> 5 - 0x1A5DF) << 2;
				PrintString(0x42, 0x18, 0, &buf[0], 0);
				PrintString(0x56, 0x18, 0, ":", 0);

				sprintf(&buf[0], "%.2d", ((((((((((savegame.Level.Timer - ((((savegame.Level.Timer * 0x88888889) >> 4) << 4) - ((savegame.Level.Timer * 0x88888889) >> 4)) << 1) << 2) + savegame.Level.Timer - ((((savegame.Level.Timer * 0x88888889) >> 4) << 4) - ((savegame.Level.Timer * 0x88888889) >> 4)) << 1) << 2) + savegame.Level.Timer - ((((savegame.Level.Timer * 0x88888889) >> 4) << 4) - ((savegame.Level.Timer * 0x88888889) >> 4)) << 1) << 3) - savegame.Level.Timer - ((((savegame.Level.Timer * 0x88888889) >> 4) << 4) - ((savegame.Level.Timer * 0x88888889) >> 4)) << 1) << 1) * 0x51EB851F) >> 5) - (((((((((savegame.Level.Timer - ((((savegame.Level.Timer * 0x88888889) >> 4) << 4) - ((savegame.Level.Timer * 0x88888889) >> 4)) << 1) << 2) + savegame.Level.Timer - ((((savegame.Level.Timer * 0x88888889) >> 4) << 4) - ((savegame.Level.Timer * 0x88888889) >> 4)) << 1) << 2) + savegame.Level.Timer - ((((savegame.Level.Timer * 0x88888889) >> 4) << 4) - ((savegame.Level.Timer * 0x88888889) >> 4)) << 1) << 3) - savegame.Level.Timer - ((((savegame.Level.Timer * 0x88888889) >> 4) << 4) - ((savegame.Level.Timer * 0x88888889) >> 4)) << 1) << 1) >> 31));
				PrintString(0x5C, 0x18, 0, &buf[0], 0);
			}//loc_3B0A0
		}//loc_3B0A0
	}//loc_3B0A0

#endif
}

int FlashIt()//3AD2C, 3B22C (F)
{
	static int flash_state;
	static int flash_count;

	if (--flash_count != 0)
	{
		flash_count = 5;
		flash_state ^= 1;
	}

	return flash_state;
}



