#ifndef HEALTH_H
#define HEALTH_H

#include "PSXTYPES.H"

extern int FlashIt();
extern void InitialisePickUpDisplay();
extern void DrawGameInfo(int timed);

extern int health_bar_timer;
extern char PoisonFlag;
extern struct DISPLAYPU pickups[8];
extern short PickupX;
extern short PickupY;
extern short PickupVel;
extern short CurrentPickup;

#endif