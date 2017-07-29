#ifndef LARA_H
#define LARA_H

#include "CAMERA.H"

#define LARA_DRAW_TYPE_NORMAL   1
#define LARA_DRAW_TYPE_YOUNG    2
#define LARA_DRAW_TYPE_BUNHEAD  3
#define LARA_DRAW_TYPE_OFFICE   4
#define LARA_DRAW_TYPE_ARTIC    5

struct lara_arm
{
	short *frame_base; // size=0, offset=0
	short frame_number; // size=0, offset=4
	short anim_number; // size=0, offset=6
	short lock; // size=0, offset=8
	short y_rot; // size=0, offset=10
	short x_rot; // size=0, offset=12
	short z_rot; // size=0, offset=14
	short flash_gun; // size=0, offset=16
};

struct lara_info
{
	short item_number;
	short gun_status;
	short gun_type;
	short request_gun_type;
	short last_gun_type;
	short calc_fallspeed;
	short water_status;
	short climb_status;
	short pose_count;
	short hit_frame;
	short hit_direction; // size=0, offset=20
	short air; // size=0, offset=22
	short dive_count; // size=0, offset=24
	short death_count; // size=0, offset=26
	short current_active; // size=0, offset=28
	short current_xvel; // size=0, offset=30
	short current_yvel; // size=0, offset=32
	short current_zvel; // size=0, offset=34
	short spaz_effect_count; // size=0, offset=36
	short flare_age; // size=0, offset=38
	short BurnCount; // size=0, offset=40
	short weapon_item; // size=0, offset=42
	short back_gun; // size=0, offset=44
	short flare_frame; // size=0, offset=46
	short poisoned; // size=0, offset=48
	short dpoisoned; // size=0, offset=50
	unsigned char Anxiety; // size=0, offset=52
	unsigned char wet[15]; // size=15, offset=53
	unsigned short flare_control_left : 1; // offset=68.0
	unsigned short Unused1 : 1; // offset=68.1
	unsigned short look : 1; // offset=68.2
	unsigned short burn : 1; // offset=68.3
	unsigned short keep_ducked : 1; // offset=68.4
	unsigned short IsMoving : 1; // offset=68.5
	unsigned short CanMonkeySwing : 1; // offset=68.6
	unsigned short BurnBlue : 2; // offset=68.7
	unsigned short Gassed : 1; // offset=69.1
	unsigned short BurnSmoke : 1; // offset=69.2
	unsigned short IsDucked : 1; // offset=69.3
	unsigned short has_fired : 1; // offset=69.4
	unsigned short Busy : 1; // offset=69.5
	unsigned short LitTorch : 1; // offset=69.6
	unsigned short IsClimbing : 1; // offset=69.7
	unsigned short Fired : 1; // offset=70.0
	long water_surface_dist; // size=0, offset=72
	struct PHD_VECTOR last_pos; // size=12, offset=76
	struct FX_INFO *spaz_effect; // size=44, offset=88
	int mesh_effects; // size=0, offset=92
	short *mesh_ptrs[15]; // size=60, offset=96
	struct ITEM_INFO *target; // size=144, offset=156
	short target_angles[2]; // size=4, offset=160
	short turn_rate; // size=0, offset=164
	short move_angle; // size=0, offset=166
	short head_y_rot; // size=0, offset=168
	short head_x_rot; // size=0, offset=170
	short head_z_rot; // size=0, offset=172
	short torso_y_rot; // size=0, offset=174
	short torso_x_rot; // size=0, offset=176
	short torso_z_rot; // size=0, offset=178
	struct lara_arm left_arm; // size=20, offset=180
	struct lara_arm right_arm; // size=20, offset=200
	unsigned short holster; // size=0, offset=220
	struct creature_info *creature; // size=228, offset=224
	long CornerX; // size=0, offset=228
	long CornerZ; // size=0, offset=232
	char RopeSegment; // size=0, offset=236
	char RopeDirection; // size=0, offset=237
	short RopeArcFront; // size=0, offset=238
	short RopeArcBack; // size=0, offset=240
	short RopeLastX; // size=0, offset=242
	short RopeMaxXForward; // size=0, offset=244
	short RopeMaxXBackward; // size=0, offset=246
	long RopeDFrame; // size=0, offset=248
	long RopeFrame; // size=0, offset=252
	unsigned short RopeFrameRate; // size=0, offset=256
	unsigned short RopeY; // size=0, offset=258
	long RopePtr; // size=0, offset=260
	void *GeneralPtr; // size=0, offset=264
	int RopeOffset; // size=0, offset=268
	unsigned long RopeDownVel; // size=0, offset=272
	char RopeFlag; // size=0, offset=276
	char MoveCount; // size=0, offset=277
	int RopeCount; // size=0, offset=280
	char skelebob; // size=0, offset=284
	char pistols_type_carried; // size=0, offset=285
	char uzis_type_carried; // size=0, offset=286
	char shotgun_type_carried; // size=0, offset=287
	char crossbow_type_carried; // size=0, offset=288
	char hk_type_carried; // size=0, offset=289
	char sixshooter_type_carried; // size=0, offset=290
	char lasersight; // size=0, offset=291
	char silencer; // size=0, offset=292
	char binoculars; // size=0, offset=293
	char crowbar; // size=0, offset=294
	char examine1; // size=0, offset=295
	char examine2; // size=0, offset=296
	char examine3; // size=0, offset=297
	char wetcloth; // size=0, offset=298
	char bottle; // size=0, offset=299
	char puzzleitems[12]; // size=12, offset=300
	unsigned short puzzleitemscombo; // size=0, offset=312
	unsigned short keyitems; // size=0, offset=314
	unsigned short keyitemscombo; // size=0, offset=316
	unsigned short pickupitems; // size=0, offset=318
	unsigned short pickupitemscombo; // size=0, offset=320
	short num_small_medipack; // size=0, offset=322
	short num_large_medipack; // size=0, offset=324
	short num_flares; // size=0, offset=326
	short num_pistols_ammo; // size=0, offset=328
	short num_uzi_ammo; // size=0, offset=330
	short num_revolver_ammo; // size=0, offset=332
	short num_shotgun_ammo1; // size=0, offset=334
	short num_shotgun_ammo2; // size=0, offset=336
	short num_hk_ammo1; // size=0, offset=338
	short num_crossbow_ammo1; // size=0, offset=340
	short num_crossbow_ammo2; // size=0, offset=342
	char location; // size=0, offset=344
	char highest_location;
	char locationPad;
	unsigned char TightRopeOnCount;
	unsigned char TightRopeOff;
	unsigned char TightRopeFall;
	unsigned char ChaffTimer;
};

struct STATS
{
	unsigned long Timer;
	unsigned long Distance;
	unsigned long AmmoUsed;
	unsigned long AmmoHits;
	unsigned short Kills;
	unsigned char Secrets;
	unsigned char HealthUsed;
};

extern short angle; // offset 0xA0650
extern short elevation; // offset 0xA0652
extern struct ITEM_INFO *lara_item; // offset 0xA2048
extern unsigned short DashTimer; // offset 0xA2044
extern struct lara_info lara; // offset 0xA57DC

#endif