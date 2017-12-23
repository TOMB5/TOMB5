#ifndef HAIR_H
#define HAIR_H

#include "SPECTYPES.H"

extern void InitialiseHair();
extern void HairControl(short a0, short a1, short a2);

extern int hair_wind;
extern int hair_wind_angle;
extern int hair_dwind_angle;
extern int first_hair[2];
extern struct HAIR_STRUCT hairs[2][7];

#endif