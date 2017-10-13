#ifndef OBJLIGHT_H
#define OBJLIGHT_H

#include "SPECTYPES.H"

enum light_type
{
	LT_SUN,
	LT_LIGHT,
	LT_SPOT,
	LT_SHADOW,
	LT_FOG_BULB,

	NUM_LIGHT_TYPES
};

extern FOOTPRINT FootPrint[32];
extern int FootPrintNum;

extern void ControlBlinker(short item_number);
extern void ControlElectricalLight(short item_number);
extern void ControlColouredLight(short item_number);
extern void ControlPulseLight(short item_number);
extern void ControlStrobeLight(short item_number);
extern void TriggerAlertLight(long x, long y, long z, long r, long g, long b, long angle, int room_no, int falloff);

#endif