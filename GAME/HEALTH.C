#include "HEALTH.H"

int health_bar_timer = 0;
char PoisonFlag = 0;
struct DISPLAYPU pickups[8];
short PickupX = 0;
short PickupY = 0;
short PickupVel = 0;
short CurrentPickup = 0;

int FlashIt()//3AD2C, 3B22C
{
	static int flash_state;
	static int flash_count;

	flash_count--;

	if (flash_count != 0)
	{
		flash_count = 5;
		flash_state ^= 1;
	}

	return flash_state;
}

void InitialisePickUpDisplay()//3B580, 3B9DC
{ 
	for (int i = 7; i > -1; i--)
	{
		pickups[i].life = -1;
	}

	PickupY = 128;
	PickupX = 128;
	PickupVel = 0;
	CurrentPickup = 0;
}
