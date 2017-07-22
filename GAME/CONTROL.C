#include "CONTROL.H"

#include "DELTAPAK.H"
#include "GAMEFLOW.H"
#include "NEWINV2.H"
#include "LARA.H"
#include "LARA2GUN.H"
#include "PICKUP.H"
#include "PSXINPUT.H"
#include "SPECIFIC.H"
#include "SPOTCAM.H"

int flipeffect;
int fliptimer;
unsigned char ShatterSounds[18][10];
unsigned char WeaponDelay;
unsigned char KeyTriggerActive;
unsigned short GlobalCounter;
char TriggerTimer;
int reset_flag;
short SlowMotion;
short SlowMoFrameCount;
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

long ControlPhase(long nframes, int demo_mode)//1D538, 1D6CC
{
	int s0 = nframes;
	int v0 = SlowMotion;
	int a0 = SlowMotion;
	int s6 = demo_mode;

	if (v0 != 0)
	{
		//0x1D6FC(IB)
	}//0x1D748 (IB)

		
	v0 = SlowMoFrameCount;//FIXME 0x10
	int v1 = SlowMoFrameCount;//^

	if (v0 < 0x11)//1D754
	{
		v0 = v1 - 1;

	}//1D7AC

	v0 = v1 - 1;
	RegeneratePickups();

	if (s0 < 0xB)//0x!D7B8
	{

	}//0x1D7C4

	v0 = bTrackCamInit;

	if (v0 != 0)//0x1D7D0
	{

	}//0x1D7E0

	v0 = framecount;
	v1 = 1;
	SetDebounce = v1;

	v0 += s0;
	framecount = v0;

	if (v0 > 0)//0x1D7F4
	{
		v0 = -1;
		v1 = GLOBAL_enterinventory;//-1

		if (v1 == v0)//0x1D808
		{
			v0 = 0;
			int s4 = -1;
			int s3 = 1;
			v0 = GlobalCounter;//0
			v0++;
			GlobalCounter = v0;

			///UpdateSky(); //? external module
			S_UpdateInput();

			v0 = bDisableLaraControl;//1, 0x1D844
			if (v0 != 0)
			{
				v0 = gfCurrentLevel;
				if (v0 != 0)//0x1D858
				{

				}//0x1D868

				v0 = input;
				v0 &= 0x200;
				input = v0;

			}//0x1D880

			v0 = cutseq_trig;
			if (v0 != 0)//0x1D88C
			{

			}//0x1D89C

			SetDebounce = 0;

			v0 = 3;
			if (gfLevelComplete == 0)//0x1D8A8
			{
				v0 = reset_flag;
				if (v0 == 0)
				{
					struct lara_info* v00 = &lara;
					short a0 = lara.death_count;

					//s2 = v0;
					if (a0 < 0x5B)
					{
						///@LAST 0x001D8D8
					}//0x1D734

				}//j 0x1D728

			}//0x1E5D0

		}//0x1E5D0

		v0 = 0;

	}//0x1E5CC

	v0 = -1;

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