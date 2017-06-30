#ifndef CAMERA_H
#define CAMERA_H

#include "ITEMS.H"
#include "SPHERE.H"

struct PHD_VECTOR
{
	long x;
	long y;
	long z;
};

enum camera_type 
{
	CHASE_CAMERA = 0,
	FIXED_CAMERA = 1,
	LOOK_CAMERA = 2,
	COMBAT_CAMERA = 3,
	CINEMATIC_CAMERA = 4,
	HEAVY_CAMERA = 5
};

struct GAME_VECTOR
{
	long x;
	long y;
	long z;
	short room_number;
	short box_number;
};

struct OBJECT_VECTOR
{
	long x;
	long y;
	long z;
	short data;
	short flags;
};

struct OLD_CAMERA
{
	short current_anim_state;
	short goal_anim_state;
	long target_distance;
	short target_angle;
	short target_elevation;
	short actual_elevation;
	struct PHD_3DPOS pos;
	struct PHD_3DPOS pos2;
	struct PHD_VECTOR t;
};

struct SHATTER_ITEM
{
	struct SPHERE Sphere;
	struct ITEM_LIGHT* il;
	short* meshp;
	long Bit;
	short YRot;
	short Flags;
};

struct CAMERA_INFO
{
	struct GAME_VECTOR pos;
	struct GAME_VECTOR target;
	enum camera_type type;
	enum camera_type old_type;
	long shift;
	long flags;
	long fixed_camera;
	long number_frames;
	long bounce;
	long underwater;
	long target_distance;
	short target_angle;
	short target_elevation;
	short actual_elevation;
	short actual_angle;
	short lara_node;
	short box;
	short number;
	short last;
	short timer;
	short speed;
	short targetspeed;
	struct ITEM_INFO* item;
	struct ITEM_INFO* last_item;
	struct OBJECT_VECTOR* fixed;
	int mike_at_lara;
	struct PHD_VECTOR mike_pos;
};

extern long BinocularRange;
extern long BinocularOn;
extern long BinocularOldCamera;
extern long LaserSight;
extern long InfraRed;
extern char SniperCount;
extern char SniperCamActive;
extern long ExittingBinos;
extern long TooFarCount;
extern long CombatShift;
extern unsigned char camerasnaps;
extern unsigned char TargetSnaps;
extern char TLFlag;
extern char LSHKShotsFired;
extern char LSHKTimer;
extern struct CAMERA_INFO camera;
extern char UseForcedFixedCamera;
extern struct GAME_VECTOR ForcedFixedCamera;
extern long NumFixedCameras;
extern int number_cameras;
extern struct PHD_VECTOR CamOldPos;
extern struct SHATTER_ITEM ShatterItem;
extern struct GAME_VECTOR static_lookcamp;
extern struct GAME_VECTOR static_lookcamt;
extern struct OLD_CAMERA old_cam;
extern struct GAME_VECTOR last_ideal;
extern struct GAME_VECTOR last_target;
extern short rcossin_tbl[];

void InitialiseCamera();
void AlterFOV(short fov);

#endif