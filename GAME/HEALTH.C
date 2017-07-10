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

#if 0//Illegal pointer ($gp+0x548)
	int v0 = 0x548;

	if (v0 != 0)
	{
		addiu	$v0, -1
			sw	$v0, 0x548($gp)
			j	loc_3AD5C
			nop
	}
	else
	{
	loc_3AD48:
		lw	$v0, 0x544($gp)
			li	$v1, 5
			sw	$v1, 0x548($gp)
			xori	$v0, 1
			sw	$v0, 0x544($gp)
	}

	loc_3AD5C :
	lw	$v0, 0x544($gp)
		jr	$ra
		nop
#endif
		return -1;
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
