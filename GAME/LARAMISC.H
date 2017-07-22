#ifndef LARAMISC_H
#define LARAMISC_H

#include "CAMERA.H"

struct COLL_INFO
{
	long mid_floor;
	long mid_ceiling;
	long mid_type;
	long front_floor;
	long front_ceiling;
	long front_type;
	long left_floor;
	long left_ceiling;
	long left_type;
	long right_floor;
	long right_ceiling;
	long right_type;
	long left_floor2;
	long left_ceiling2;
	long left_type2;
	long right_floor2;
	long right_ceiling2;
	long right_type2;
	long radius;
	long bad_pos;
	long bad_neg;
	long bad_ceiling;
	struct PHD_VECTOR shift;
	struct PHD_VECTOR old;
	short old_anim_state;
	short old_anim_number;
	short old_frame_number;
	short facing;
	short quadrant;
	short coll_type;
	short* trigger;
	char tilt_x;
	char tilt_z;
	char hit_by_baddie;
	char hit_static;
	unsigned short slopes_are_walls : 2;
	unsigned short slopes_are_pits : 1;
	unsigned short lava_is_pit : 1;
	unsigned short enable_baddie_push : 1;
	unsigned short enable_spaz : 1;
	unsigned short hit_ceiling : 1;
};

extern char* states[131];
extern char* quadrant_names[4];
extern char* gunstates[6];
extern char* waterstates[5];
extern char* guntypes[9];
extern char* coll_typess[8];
extern char* htypes[4];
extern short SubsuitAir;
extern struct COLL_INFO mycoll;
extern short cheat_hit_points;

#endif