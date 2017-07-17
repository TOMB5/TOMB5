#include "CONTROL.H"

#include "LARA2GUN.H"
#include "SPECIFIC.H"

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
long rand_1;
int framecount;
long rand_2;
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

long ControlPhase(long nframes, int demo_mode)
{
	S_Warn("[ControlPhase] - Unimplemented!\n");
	return -1;
}