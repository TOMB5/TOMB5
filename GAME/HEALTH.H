#ifndef HEALTH_H
#define HEALTH_H

#include "PSXTYPES.H"

extern void AddDisplayPickup(short object_number);
extern void DrawPickups(int timed);
extern void InitialisePickUpDisplay();
extern void DrawAirBar(int flash_state);
extern void DrawHealthBar(int flash_state);
extern void DrawGameInfo(int timed);
extern int FlashIt();

extern int health_bar_timer;
extern char PoisonFlag;
extern struct DISPLAYPU pickups[8];
extern short PickupX;
extern short PickupY;
extern short PickupVel;
extern short CurrentPickup;

#endif