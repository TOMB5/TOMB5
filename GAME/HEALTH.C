#include "HEALTH.H"

#include "DELTAPAK.H"
#include "DRAW.H"
#include "DRAWPHAS.H"
#include "GAMEFLOW.H"
#include "LARA.H"
#include "SPOTCAM.H"

#include <stdio.h>
#include "SPECIFIC.H"

int health_bar_timer = 0;
char PoisonFlag = 0;
struct DISPLAYPU pickups[8];
short PickupX = 0;
short PickupY = 0;
short PickupVel = 0;
short CurrentPickup = 0;

void AddDisplayPickup(short object_number)//3B6F4, ?
{
	struct DISPLAYPU *pu; // $v1
	long lp; // $a1


	//a1 = gfCurrentLevel
	if (gfCurrentLevel == LVL5_SUBMARINE)
	{

	}//loc_3B728

	
	S_Warn("[AddDisplayPickup] - Unimplemented!\n");
}

void DrawPickups(int timed)
{
	S_Warn("[DrawPickups] - Unimplemented!\n");
}

void InitialisePickUpDisplay()//3B580, 3B9DC
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

void DrawGameInfo(int timed)//3AD68(<), 
{ // line 2, offset 0x3ad68
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
	PrintString(256, 24, 0, sbuf);///@FIXME check arg 3

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



