#ifndef EFFECTS_H
#define EFFECTS_H

#include "CAMERA.H"
#include "ITEMS.H"

struct FX_INFO
{
	struct PHD_3DPOS pos;
	short room_number;
	short object_number;
	short next_fx;
	short next_active;
	short speed;
	short fallspeed;
	short frame_number;
	short counter;
	short shade;
	short flag1;
	short flag2;
};

extern long wf;
extern short next_fx_free;
extern short next_fx_active;
extern int number_sound_effects;
extern struct OBJECT_VECTOR* sound_effects;
extern struct FX_INFO* effects;

#endif