#ifndef HEALTH_H
#define HEALTH_H

struct DISPLAYPU
{
	short life;
	short object_number;
};

int FlashIt();
void InitialisePickUpDisplay();

extern int health_bar_timer;
extern char PoisonFlag;
extern struct DISPLAYPU pickups[8];
extern short PickupX;
extern short PickupY;
extern short PickupVel;
extern short CurrentPickup;

#endif