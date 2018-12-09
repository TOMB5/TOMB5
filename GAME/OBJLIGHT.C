#include "OBJLIGHT.H"

#include "CONTROL.H"
#include "SPECIFIC.H"

#if PSX_VERSION || PSXPC_VERSION
#include "SPHERES.H"
#endif

struct FOOTPRINT FootPrint[32];
int FootPrintNum;

void TriggerAlertLight(long x, long y, long z, long r, long g, long b, long angle, int room_no, int falloff)//5D018, 5D494
{
}

void ControlBlinker(short item_number)//5D660(<), 5DADC (F)
{
	struct ITEM_INFO* item;
	struct PHD_VECTOR pos;
	long r;
	long g;
	long b;

	item = &items[item_number];

	if (TriggerActive(item) == 0)
		return;

	if (--item->item_flags[0] < 3)
	{
		pos.z = 0;
		pos.y = 0;
		pos.z = 0;
		GetJointAbsPosition(item, &pos, 0);

		r = (item->trigger_flags & 0x1F) << 3;
		g = (item->trigger_flags >> 4) & 0xF8;
		b = (item->trigger_flags >> 1) & 0xF8;

		TriggerDynamic(pos.x, pos.y, pos.z, 16, r, g, b);

		item->mesh_bits = 2;
		if (item->item_flags[0] < 0)
		{
			item->item_flags[0] = 30;
		}//5D73C
	}
	else
	{
		//5D734
		item->mesh_bits = 1;
	}
}

void ControlElectricalLight(short item_number)//5D3F8, 5D874
{
	UNIMPLEMENTED();
}

void ControlColouredLight(short item_number)//5D368, 5D7E4
{
	UNIMPLEMENTED();
}

void ControlPulseLight(short item_number)//5D254, 5D6D0
{
	UNIMPLEMENTED();
}

void ControlStrobeLight(short item_number)//5D118, 5D594
{
	UNIMPLEMENTED();
}