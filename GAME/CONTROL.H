#ifndef CONTROL_H
#define CONTROL_H

#include "CAMERA.H"

struct CHARDEF
{
	unsigned char u;
	unsigned char v;
	unsigned char w;
	unsigned char h;
	char YOffset;
	unsigned char TopShade;
	unsigned char BottomShade;
};

struct ROPE_STRUCT
{
	struct PHD_VECTOR Segment[24];
	struct PHD_VECTOR Velocity[24];
	struct PHD_VECTOR NormalisedSegment[24];
	struct PHD_VECTOR MeshSegment[24];
	struct PHD_VECTOR Position;
	long SegmentLength;
	short Active;
	short Coiled;
};

struct PENDULUM
{
	struct PHD_VECTOR Position;
	struct PHD_VECTOR Velocity;
	int node;
	struct ROPE_STRUCT* Rope;
};

extern int flipeffect;
extern int fliptimer;
extern unsigned char ShatterSounds[18][10];
extern unsigned char WeaponDelay;
extern unsigned char KeyTriggerActive;
extern unsigned short GlobalCounter;
extern char TriggerTimer;
extern int reset_flag;
extern short SlowMotion;
extern short SlowMoFrameCount;
extern unsigned char InItemControlLoop;
extern short ItemNewRoomNo;
extern short SmashedMeshCount;
extern char richcutfrigflag;
extern int nRope;
extern char GetLaraOnLOS;
extern int NoInput;
extern int number_los_rooms;
extern long rand_1;
extern int framecount;
extern long rand_2;
extern struct ITEM_INFO* items;
extern int flip_status;
extern int flipmap[10];
extern int flip_stats[10];
extern int height_type;
extern int tiltxoff;
extern int tiltyoff;
extern unsigned long _CutSceneTriggered1;
extern unsigned long _CutSceneTriggered2;
extern unsigned long FmvSceneTriggered;
extern unsigned char CurrentAtmosphere;
extern unsigned char IsAtmospherePlaying;
extern char* OutsideRoomTable;
extern short* OutsideRoomOffsets;
extern short IsRoomOutsideNo;
extern short FXType;
extern int OnObject;
extern short* trigger_index;
extern char cd_flags[136];
extern unsigned char InGameCnt;
extern struct RAT_STRUCT* Rats;
extern struct BAT_STRUCT* Bats;
extern struct SPIDER_STRUCT* Spiders;
extern struct TWOGUN_INFO twogun[4];
extern int SetDebounce;
extern short WB_room;
extern struct ITEM_INFO* WB_item;
extern unsigned char HeavyTriggered;
extern struct MESH_INFO* SmashedMesh[16];
extern short SmashedMeshRoom[16];
extern struct PENDULUM CurrentPendulum;
extern char LaraDrawType;
extern char WeatherType;
extern char RoomDrawType;
extern struct PHD_VECTOR ClosestCoord;
extern int ClosestItem;
extern int ClosestDist;
extern short XSoff1;
extern short YSoff1;
extern short ZSoff1;
extern short XSoff2;
extern short YSoff2;
extern short ZSoff2;
extern short los_rooms[20];
extern char globoncuttrig;
extern short ItemNewRooms[256][2];
extern struct CHARDEF CharDef[106];

extern long ControlPhase(long nframes, int demo_mode);
extern long GetRandomControl();
extern long GetRandomDraw();
extern void AddRoomFlipItems(struct room_info* r);
extern void KillMoveItems();
extern void KillMoveEffects();
extern void KillEverything();

#endif