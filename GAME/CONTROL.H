#ifndef CONTROL_H
#define CONTROL_H

#include "SPECTYPES.H"

// guessed, some may be wrong on PSX
enum input_buttons
{
	IN_NONE = 0,
	IN_UP = (1 << 0),
	IN_DOWN = (1 << 1),
	IN_LEFT = (1 << 2),
	IN_RIGHT = (1 << 3),
	IN_JUMP = (1 << 4),
	IN_DRAW = (1 << 5), // Space / Triangle
	IN_ACTION = (1 << 6), // Ctrl / X
	IN_WALK = (1 << 7), // Shift / R1
	IN_OPTION = (1 << 8),
	IN_LOOK = (1 << 9),
	IN_LSTEP = (1 << 10),
	IN_RSTEP = (1 << 11),
	IN_ROLL = (1 << 12), // End / O
	IN_PAUSE = (1 << 13),
	IN_SAVE = (1 << 22), // F5
	IN_LOAD = (1 << 23)  // F6
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
extern void TestTriggers(short* data, int heavy, int HeavyFlags);
extern void ClearFires();

extern int is_object_in_room(int roomnumber, int objnumber);
extern void NeatAndTidyTriggerCutscene(int value, int timer);
extern int CheckCutPlayed(int num);
extern void SetCutNotPlayed(int num);
extern void SetCutPlayed(int num);
extern void InitCutPlayed();
extern void ResetGuards();
extern void InterpolateAngle(short dest, short *src, short *diff, short speed);
extern int CheckGuardOnTrigger();
extern int ExplodeItemNode(struct ITEM_INFO *item, int Node, int NoXZVel, long bits);
extern int GetTargetOnLOS(struct GAME_VECTOR *src, struct GAME_VECTOR *dest, int DrawTarget, int firing);
extern void FireCrossBowFromLaserSight(struct GAME_VECTOR *src, struct GAME_VECTOR *target);
extern void TriggerNormalCDTrack(short value, short flags, short type);
extern void TriggerCDTrack(short value, short flags, short type);
extern void RemoveRoomFlipItems(struct room_info *r);
extern void FlipMap(int FlipNumber);
extern void _TestTriggers(short *data, int heavy, int HeavyFlags);
extern void RefreshCamera(short type, short *data);
extern long GetWaterHeight(long x, long y, long z, short room_number);
extern void AlterFloorHeight(struct ITEM_INFO *item, int height);
extern short GetHeight(struct FLOOR_INFO *floor, int x, int y, int z);
extern struct FLOOR_INFO *GetFloor(int x, int y, int z, short *room_number);
extern short GetCeiling(struct FLOOR_INFO *floor, int x, int y, int z);

#endif