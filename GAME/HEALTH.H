#ifndef HEALTH_H
#define HEALTH_H

#include "STYPES.H"

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

#define BAR_W 133

#if PSXENGINE
#define S_DrawHealthBar(val) S_DrawGouraudBar(343, 18, BAR_W, (val * BAR_W) / 100, PoisonFlag ? &poisonBarColourSet : &healthBarColourSet)
#define S_DrawHealthBar2(val) S_DrawGouraudBar(189, 40, BAR_W, (val * BAR_W) / 100, PoisonFlag ? &poisonBarColourSet : &healthBarColourSet)
#define S_DrawAirBar(val) S_DrawGouraudBar(343, 32, BAR_W, (val * BAR_W) / 100, &airBarColourSet)
#define S_DrawDashBar(val) S_DrawGouraudBar(343, 46, BAR_W, (val * BAR_W) / 100, &dashBarColourSet)
#endif


#endif