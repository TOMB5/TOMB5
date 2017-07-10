#ifndef HAIR_H
#define HAIR_H

#include "ITEMS.H"
#include "CAMERA.H"

struct HAIR_STRUCT
{
	struct PHD_3DPOS pos;
	struct PHD_VECTOR vel;
};

void InitialiseHair();

extern int hair_wind;
extern int hair_wind_angle;
extern int hair_dwind_angle;
extern int first_hair[2];
extern struct HAIR_STRUCT hairs[2][7];

#endif