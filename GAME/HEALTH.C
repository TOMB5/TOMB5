#include "HEALTH.H"

#include "DELTAPAK.H"
#include "DRAW.H"
#include "DRAWPHAS.H"
#include "GAMEFLOW.H"
#include "LARA.H"
#include "NEWINV2.H"
#include "OBJECTS.H"
#include "SPECIFIC.H"
#include "SPOTCAM.H"

#include <stdio.h>

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

void DrawAirBar(int flash_state)
{
	S_Warn("[DrawAirBar] - Unimplemented!\n");
}

void DrawHealthBar(int flash_state)
{
	S_Warn("[DrawHealthBar] - Unimplemented!\n");
}

void DrawGameInfo(int timed)//3AD68(<), 3B268(!)
{ 
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
#else
	// line 2, offset 0x3ad68
	int flash_state; // $s0
					 //{ // line 17, offset 0x3adac
	char sbuf[80]; // stack offset -192
				   //} // line 19, offset 0x3adac
	{ // line 53, offset 0x3af50
		char buf[80]; // stack offset -112
		int seconds; // $s3
	} // line 77, offset 0x3b0a0

	if (GLOBAL_playing_cutseq != 0 || bDisableLaraControl != 0)
	{
		return;
	}
	
	sprintf(sbuf, "Room:%d X:%d Y:%d Z:%d", lara_item->room_number, (lara_item->pos.x_pos - room[lara_item->room_number].x) / SECTOR(1), (lara_item->pos.y_pos - room[lara_item->room_number].minfloor) / CLICK, (lara_item->pos.z_pos - room[lara_item->room_number].z) / SECTOR(1));
	PrintString(256, 24, 0, sbuf, 0);

	//^Not verified for retail/internal split

	if (gfGameMode == 1)
	{
		//loc_3B0A0
		return;
	}

	flash_state = FlashIt();
	DrawHealthBar(flash_state);
	DrawAirBar(flash_state);
	DrawPickups(timed);//Arg does not seem right imo

	if (DashTimer < 120)
	{
		//TODO
	}//loc_3AF14
	

	return;
#endif
} // line 79, offset 0x3b0a0

int FlashIt()//3AD2C, 3B22C
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

void AddDisplayPickup(short object_number)//3B6F4(<), 3BB50(<) (F)
{
	struct DISPLAYPU* pu = &pickups[0];
	long lp = 0;

	if (gfCurrentLevel == LVL5_SUBMARINE && object_number == PUZZLE_ITEM1)
	{
		object_number = CROWBAR_ITEM;
	}

	if (gfCurrentLevel == LVL5_OLD_MILL && object_number == PUZZLE_ITEM3)
	{
		object_number = CROWBAR_ITEM;
	}

	if (pu->life < 0)
	{
		pu->life = 45;
		pu->object_number = object_number;
	}
	else
	{
		//loc_3B764
		lp++;

		//loc_3B768
		do
		{
			if (lp > 7)
			{
				DEL_picked_up_object(object_number);
				return;
			}
		} while (++pu->life >= 0, lp++);

		pu->life = 45;
		pu->object_number = object_number;
	}

	//loc_3B790
	DEL_picked_up_object(object_number);

	return;
}