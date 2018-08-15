#ifndef CONTROL_H
#define CONTROL_H

#include "SPECTYPES.H"

// guessed, some may be wrong on PSX
enum input_buttons
{
	IN_NONE = 0,								// 0x00000000
	IN_UP = (1 << 0),							// 0x00000001
	IN_DOWN = (1 << 1),							// 0x00000002
	IN_LEFT = (1 << 2),							// 0x00000004
	IN_RIGHT = (1 << 3),						// 0x00000008
	IN_JUMP = (1 << 4),							// 0x00000010
	IN_DRAW = (1 << 5), // Space / Triangle		// 0x00000020
	IN_ACTION = (1 << 6), // Ctrl / X			// 0x00000040
	IN_WALK = (1 << 7), // Shift / R1			// 0x00000080
	IN_OPTION = (1 << 8),						// 0x00000100
	IN_LOOK = (1 << 9),							// 0x00000200
	IN_LSTEP = (1 << 10),						// 0x00000400
	IN_RSTEP = (1 << 11),						// 0x00000800
	IN_ROLL = (1 << 12), // End / O				// 0x00001000
	IN_PAUSE = (1 << 13),						// 0x00002000
	IN_UNK19 = (1 << 19),						// 0x00080000
	IN_UNK20 = (1 << 20),						// 0x00100000
	IN_UNK21 = (1 << 21),						// 0x00200000
	IN_SAVE = (1 << 22), // F5					// 0x00400000
	IN_LOAD = (1 << 23),  // F6					// 0x00800000
	IN_CROUCH = (1 << 29),						// 0x20000000
	IN_SPRINT = (1 << 30),						// 0x40000000
};

enum flipeffects
{
	FE_ROTATE_180 = 0,
	FE_FLOOR_SHAKE = 1,
	FE_FLOOD_FX = 2,
	FE_LARA_BUBBLES = 3,
	FE_FINISH_LEVEL = 4,

	FE_ACTIVATE_CAMERA = 5,
	FE_ACTIVATE_KEY = 6,

	FE_RUBBLE_FX = 7,
	FE_SWAP_CROWBAR = 8,

	FE_TIMER_FIELD_FX = 10,
	FE_EXPLOSION_FX = 11,
	FE_LARA_HANDSFREE = 12,

	FE_SHOOT_RIGHTGUN = 16,
	FE_SHOOT_LEFTGUN = 17,

	FE_INV_ON = 21,
	FE_INV_OFF = 22,

	FE_RESET_HAIR = 26,
	FE_SETFOG = 28,
	FE_LARALOCATION = 30,
	FE_RESET_TEST = 31,
	FE_FOOTPRINT_FX = 32,
	FE_CLEAR_SPIDERS_PATCH = 33,
	FE_LARALOCATIONPAD = 45,
	FE_KILLACTIVEBADDIES = 46,

	FE_TUT_HINT_1 = 47,
	FE_TUT_HINT_2 = 48,
	FE_TUT_HINT_3 = 49,
	FE_TUT_HINT_4 = 50,
	FE_TUT_HINT_5 = 51,
	FE_TUT_HINT_6 = 52,
	FE_TUT_HINT_7 = 53,
	FE_TUT_HINT_8 = 54,
	FE_TUT_HINT_9 = 55,
	FE_TUT_HINT_10 = 56,
	FE_TUT_HINT_11 = 57,
	FE_TUT_HINT_12 = 58,

	NUM_FLIPEFFECTS
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
#if PC_VERSION
extern int flipmap[255];
extern int flip_stats[255];
#else
extern int flipmap[10];
extern int flip_stats[10];
#endif
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
extern struct ROPE_STRUCT Ropes[12];

extern long ControlPhase(long nframes, int demo_mode);
extern long GetRandomControl();
extern void SeedRandomControl(long seed);
extern long GetRandomDraw();
extern void SeedRandomDraw(long seed);
extern void AddRoomFlipItems(struct room_info* r);
extern void KillMoveItems();
extern void KillMoveEffects();
extern void TestTriggers(short* data, int heavy, int HeavyFlags);
extern void ClearFires();
extern void ClearDynamics();
extern int is_object_in_room(int roomnumber, int objnumber);
extern void NeatAndTidyTriggerCutscene(int value, int timer);
extern int CheckCutPlayed(int num);
extern void SetCutNotPlayed(int num);
extern void SetCutPlayed(int num);
extern void InitCutPlayed();
extern void ResetGuards();
extern void InterpolateAngle(short dest, short* src, short* diff, short speed);
extern int CheckGuardOnTrigger();
extern int ExplodeItemNode(struct ITEM_INFO* item, int Node, int NoXZVel, long bits);
extern int GetTargetOnLOS(struct GAME_VECTOR* src, struct GAME_VECTOR* dest, int DrawTarget, int firing);
extern void FireCrossBowFromLaserSight(struct GAME_VECTOR* src, struct GAME_VECTOR* target);
extern void TriggerNormalCDTrack(short value, short flags, short type);
extern void TriggerCDTrack(short value, short flags, short type);
extern void RemoveRoomFlipItems(struct room_info* r);
extern void FlipMap(int FlipNumber);
extern void _TestTriggers(short* data, int heavy, int HeavyFlags);
extern void RefreshCamera(short type, short* data);
extern long GetWaterHeight(long x, long y, long z, short room_number);
extern void AlterFloorHeight(struct ITEM_INFO* item, int height);
extern short GetHeight(struct FLOOR_INFO* floor, int x, int y, int z);
extern struct FLOOR_INFO* GetFloor(int x, int y, int z, short* room_number);
extern short GetCeiling(struct FLOOR_INFO* floor, int x, int y, int z);
extern int TriggerActive(struct ITEM_INFO* item);
extern void AddRoomFlipItems(struct room_info* r);
extern int IsRoomOutside(long x, long y, long z);
extern short GetDoor(struct FLOOR_INFO* floor);
extern int LOS(struct GAME_VECTOR* start, struct GAME_VECTOR* target);
extern int xLOS(struct GAME_VECTOR* start, struct GAME_VECTOR* target);
extern int zLOS(struct GAME_VECTOR* start, struct GAME_VECTOR* target);
extern int CheckNoColCeilingTriangle(struct FLOOR_INFO* floor, int x, int z);
extern int CheckNoColFloorTriangle(struct FLOOR_INFO* floor, int x, int z);
extern int ClipTarget(struct GAME_VECTOR* start, struct GAME_VECTOR* target, struct FLOOR_INFO* floor);
#ifndef PSX_VERSION || PSXPC_VERSION///@FIXME @pc
extern void GetJointAbsPosition(struct ITEM_INFO* item, struct PHD_VECTOR* pos, int joint);
#endif
extern void AddFire(int x, int y, int z, char size, short room_num, short on);
extern int ObjectOnLOS2(struct GAME_VECTOR* start, struct GAME_VECTOR* target, struct PHD_VECTOR* a3, struct MESH_INFO** a4);
extern int check_xray_machine_trigger();
extern void AnimateItem(struct ITEM_INFO* item);
extern void UpdateSpiders();

#endif