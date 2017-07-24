#include "CONTROL.H"

#include "DELTAPAK.H"
#include "DRAWPHAS.H"
#include "GAMEFLOW.H"
#include "GPU.H"
#include "NEWINV2.H"
#include "LARA.H"
#include "LARA2GUN.H"
#include "PICKUP.H"
#include "PSXINPUT.H"
#include "SPECIFIC.H"
#include "SPOTCAM.H"
#include "TOMB4FX.H"

#include <stdio.h>
#include <assert.h>

int flipeffect;
int fliptimer;
unsigned char ShatterSounds[18][10];
unsigned char WeaponDelay;
unsigned char KeyTriggerActive;
unsigned short GlobalCounter;
char TriggerTimer;
int reset_flag;
short SlowMotion;
short SlowMoFrameCount = 16;
unsigned char InItemControlLoop;
short ItemNewRoomNo;
short SmashedMeshCount;
char richcutfrigflag;
int nRope;
char GetLaraOnLOS;
int NoInput;
int number_los_rooms;
int framecount;
struct ITEM_INFO* items;
int flip_status;
int flipmap[10];
int flip_stats[10];
int height_type;
int tiltxoff;
int tiltyoff;
unsigned long _CutSceneTriggered1;
unsigned long _CutSceneTriggered2;
unsigned long FmvSceneTriggered;
unsigned char CurrentAtmosphere;
unsigned char IsAtmospherePlaying;
char* OutsideRoomTable;
short* OutsideRoomOffsets;
short IsRoomOutsideNo;
short FXType;
int OnObject;
short* trigger_index;
char cd_flags[136];
unsigned char InGameCnt;
struct RAT_STRUCT* Rats;
struct BAT_STRUCT* Bats;
struct SPIDER_STRUCT* Spiders;
struct TWOGUN_INFO twogun[4];
int SetDebounce;
short WB_room;
struct ITEM_INFO* WB_item;
unsigned char HeavyTriggered;
struct MESH_INFO* SmashedMesh[16];
short SmashedMeshRoom[16];
struct PENDULUM CurrentPendulum;
char LaraDrawType;
char WeatherType;
char RoomDrawType;
struct PHD_VECTOR ClosestCoord;
int ClosestItem;
int ClosestDist;
short XSoff1;
short YSoff1;
short ZSoff1;
short XSoff2;
short YSoff2;
short ZSoff2;
short los_rooms[20];
char globoncuttrig;
short ItemNewRooms[256][2];
struct CHARDEF CharDef[106];

long ControlPhase(long nframes, int demo_mode)//1D538(<), 1D6CC
{
	int s0 = nframes;
	int v0 = SlowMotion;
	int a0 = SlowMotion;
	int s6 = demo_mode;

	if (SlowMotion == 0)
	{
		//******************** VERIFIED v

		if (SlowMoFrameCount > 16)
		{
			SlowMoFrameCount--;
		}

		RegeneratePickups();

		if (nframes > 11)
		{
			nframes = 10;
		}

		if (bTrackCamInit != 0)
		{
			bUseSpotCam = 0;
		}
		//******************** VERIFIED ^
	}
	else
	{
		//******************** NOT VERIFIED v
		SlowMotion--;

		if (SlowMoFrameCount > 39)
		{
			SlowMoFrameCount = 1;
		}
		
		//loc_1D5CC
		if (!(((SlowMoFrameCount << 16) >> 19) < nframes))
		{
			while (((SlowMoFrameCount << 16) >> 19) < nframes)
			{
#ifdef PSX
				VSync(0);
#endif
				nframes++;
			}
		}

		//loc_1D60C
		nframes = 2;
		GnLastFrameCount = 0;

		//What?
		if (nframes > 10)
		{
			nframes = 10;
		}//loc_1D630


		//loc_1D618
		RegeneratePickups();

		if (bTrackCamInit != 0)
		{
			bUseSpotCam = 0;
		}

		//******************** NOT VERIFIED^
	}

	//loc_1D64C
	//******************** VERIFIED v
	framecount += nframes;
	SetDebounce = 1;

	if (framecount <= 0)
	{
		//loc_1E3B8
		return -1;
	}

	if (GLOBAL_enterinventory != -1)
	{
		return 0;
	}

	//******************** VERIFIED ^

	//loc_1D684
	GlobalCounter++;
	UpdateSky();
	S_UpdateInput();

	assert(0);//temporary
	if (bDisableLaraControl != 0)
	{
		//Not title
		if (gfCurrentLevel != 0)
		{
			dbinput = 0;
		}

		//loc_1D6D4
		input &= 0x200;
	}

	//loc_1D6EC
	//Cutseq playing? lock controls to 0?
	if (cutseq_trig != 0)
	{
		input = 0;
	}

	//loc_1D708
	SetDebounce = 0;

	if (gfLevelComplete)
	{
		return 3;
	}

	if (reset_flag != 0)
	{
		reset_flag = 0;
		return 1;
	}

	if (lara.death_count > 91)
	{
		//loc_1D5A0
		reset_flag = 0;
		//S_Death();
		assert(0);//find ret val.
		return -1;//FIXME, s2?
	}

	if (demo_mode != 0)
	{
		if (PadConnected != 0 && ScreenFading == 0)
		{
			int x = 256;
			int y = 230;

			char* str = &gfStringWad[gfStringOffset[176]];///@TODO retail ver.
			printf("%s\n", str);
			//PrintString(x, y, str); //TODO IDA didn't dump me :-)
		}

		//loc_1D7A0
		if (input == -1)
		{
			input = 0;
			Motors[0] = 0;
			Motors[1] = 0;
		}

	}//loc_1D7D4
	else
	{
		if (gfGameMode != 1 && Gameflow->CheatEnabled)
		{
			if (input == 0)
			{
				if (Gameflow->InputTimeout > NoInput)//bad check
				{
					NoInput++;
					return 1;
				}

				NoInput++;

			}//1D844
			else
			{
				input = 0;
			}
		}//loc_1D848
	}

	//1D848
	if (InGameCnt < 4)
	{
		InGameCnt++;
	}

	//loc_1D860
	if ((input & 0x200) == 0 && SniperCamActive != 0 && bUseSpotCam != 0 && bTrackCamInit != 0 && lara_item->current_anim_state != 2 || lara.hit_direction == 0x67 && lara.LitTorch == 0 && input & 0x2000 != 0 && lara_item->anim_number != 0xDE && lara_item->goal_anim_state != 0x47)
	{
		//loc_1D9D0
		input |= 0x200;

		if (BinocularRange == 0)
		{
			//loc_1DA80
			if (SniperCamActive == 0 || bUseSpotCam == 0)
			{
				input &= 0xFFFFFDFF;
			}//loc_1DABC
		}
		else if (LaserSight != 0)
		{
			BinocularRange = 0;
			LaserSight = 0;

			AlterFOV(16380);

			lara_item->mesh_bits = -1;
			camera.type = (enum camera_type)BinocularOldCamera;

			lara.head_x_rot = 0;
			lara.head_y_rot = 0;
			lara.torso_x_rot = 0;
			lara.torso_y_rot = 0;

			BinocularOn = -8;
			camera.bounce = 0;
			input &= 0xFFFFFDFF;
			lara.look = 0;//check
		}

		v0 = BinocularRange;
	}
	else
	{
		//loc_1D920
		if (BinocularRange == 0)
		{
			if (lara.gun_type != 5 && (lara.gun_type > 6 && lara.gun_type != 6) || (lara.gun_type == 2 && (lara.sixshooter_type_carried & 4)) == 0 || lara.gun_status != 4)
			{
				v0 = BinocularRange;

			}//0x1D990
			else //loc_1D990
			{
				lara.has_fired = 1;
				BinocularRange = 128;
				LaserSight = 1;
				BinocularOldCamera = camera.old_type;
			}
		}
	}

	//loc_1DAD0 ****************
	int v1 = 0;
	if (BinocularRange != 0)
	{
		if (LaserSight != 0)
		{
			//loc_1DB28
			if ((gfLevelFlags & 0x80) == 0)
			{
				v1 = 1;
			}
			//loc_1DB40
		}
		
		if ((gfLevelFlags & 0x80) != 0)
		{
			if ((inputBusy & 0x40) != 0)
			{
				//loc_1DB40
				v1 = 1;
			}
		}//1DB44

	}//loc_1DB44

	InfraRed = v1;

	//lui	$s5, 0x1F
	//ClearDynamics();	
	//ClearFires();

	int a1 = next_item_active;
	//GotLaraSpheres = 0;
	//InItemControlLoop = s3;
	//lui	$v0, 0x1F
	
	///beq	$a1, $s4, loc_1DBE8	
	///addiu	$s1, $v0, 0x2490
	///sll	$v0, $a1, 3

	//end loc_1E3BC
	S_Warn("[ControlPhase] - Unimplemented!\n");
	return -1;
}

long rand_1 = 0xD371F947;

long GetRandomControl()//5E9F0, 926F8
{
	rand_1 = (rand_1 * 0x41C64E6D) + 0x3039;
	return (rand_1 >> 16) & 0x7FFF;
}

long rand_2 = 0xD371F947;

long GetRandomDraw()//5EA18, 5F6F8
{
	rand_2 = (rand_2 * 0x41C64E6D) + 0x3039;
	return (rand_2 >> 16) * 0x7FFF;
#if 0//?
		jr	$ra
		sw	$a0, 0x188($gp)
		jr	$ra
		sw	$a0, 0x18C($gp)
#endif
}

void AddRoomFlipItems(struct room_info *r /*$a0*/)//1FA0C, 
{
#if 0

sub_1FA0C:

			 lh	$s1, 0x48($a0)
			 li	$v0, 0xFFFFFFFF
			 beq	$s1, $v0, loc_1FAB8
			 li	$s3, 0x86

			 loc_1FA34:
		 sll	$a1, $s1, 3
			 addu	$v0, $a1, $s1
			 lw	$v1, 0x1B38($gp)
			 sll	$v0, 4
			 addu	$s0, $v1, $v0
			 lh	$a0, 0xC($s0)
			 nop
			 bne	$a0, $s3, loc_1FA70
			 move	$s2, $a1
			 lh	$v0, 0x36($s0)
			 nop
			 beqz	$v0, loc_1FA70
			 move	$a0, $s0
			 jal	sub_1E3E4
			 li	$a1, 0xFFFFFC00

			 loc_1FA70:
		 lh	$v1, 0xC($s0)
			 li	$v0, 0x87
			 bne	$v1, $v0, loc_1FA9C
			 addu	$v0, $s2, $s1
			 lh	$v0, 0x36($s0)
			 nop
			 beqz	$v0, loc_1FA98
			 move	$a0, $s0
			 jal	sub_1E3E4
			 li	$a1, 0xFFFFF800

			 loc_1FA98:
		 addu	$v0, $s2, $s1

			 loc_1FA9C :
		 lw	$v1, 0x1B38($gp)
			 sll	$v0, 4
			 addu	$v0, $v1
			 lh	$s1, 0x1A($v0)
			 li	$v1, 0xFFFFFFFF
			 bne	$s1, $v1, loc_1FA34
			 nop

			 loc_1FAB8 :
		 lw	$ra, 0x28 + var_8($sp)
			 lw	$s3, 0x28 + var_C($sp)
			 lw	$s2, 0x28 + var_10($sp)
			 lw	$s1, 0x28 + var_14($sp)
			 lw	$s0, 0x28 + var_18($sp)
			 jr	$ra
			 addiu	$sp, 0x28
			 # End of function sub_1FA0C

#endif
			 }