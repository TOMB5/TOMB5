#include "OBJLIGHT.H"

#include "CAMERA.H"
#include "CONTROL.H"
#include "SPECIFIC.H"
#include "EFFECT2.H"

#if PSX_VERSION || PSXPC_VERSION || SAT_VERSION
#include "SPHERES.H"
#include "BUBBLES.H"
#endif

struct FOOTPRINT FootPrint[32];
int FootPrintNum;

//void /*$ra*/ TriggerAlertLight(long x /*$s2*/, long y /*$s3*/, long z /*$s1*/, long r /*$s5*/, long g /*stack 16*/, long b /*stack 20*/, long angle /*stack 24*/, int room_no /*stack 28*/, int falloff /*stack 32*/)
void TriggerAlertLight(long x, long y, long z, long r, long g, long b, long angle, int room_no, int falloff)//5D018, 5D494
{
	UNIMPLEMENTED();
}

void ControlStrobeLight(short item_number)//5D118(<), 5D594 ///@FIXME im not sure this is correct redo this
{
	struct ITEM_INFO* item;
	long angle;
	long sin;
	long cos;
	long r;
	long g;
	long b;

	item = &items[item_number];

	if (!TriggerActive(item))
		return;

	angle = item->pos.y_rot + 2912;

	r = (item->trigger_flags) & 0x1F << 3;
	b = (item->trigger_flags << 16) >> 17 & 0xF8;
	g = (item->trigger_flags << 16) >> 12 & 0xF8;
	
	item->pos.y_rot = angle;

	angle += 22528;
	angle >>= 4;
	angle &= 0xFFF;

	TriggerAlertLight(item->box_number, item->pos.y_pos - 512, item->pos.z_pos, r, g, b, angle, 12, item->room_number);

	sin = rcossin_tbl[angle];
	cos = rcossin_tbl[angle | 1];

	TriggerDynamic(item->pos.x_pos + ((sin << 16) >> 14), item->pos.y_pos - 768, (item->pos.z_pos + (cos << 16) >> 14), 12, r, g ,b);
}

void ControlPulseLight(short item_number)//5D254(<), 5D6D0 (F)
{
	struct ITEM_INFO* item;
	long sin;
	long r;
	long g;
	long b;

	item = &items[item_number];

	if (!TriggerActive(item))
		return;

	item->item_flags[0] -= 1024;
	sin = ABS(SIN((item->pos.y_pos & 0x3FFF) << 2) << 16 >> 14);

	if (sin > 255)
	{
		sin = 255;
	}//5D2F0

	r = sin * ((item->trigger_flags & 0x1F) << 3) >> 9;
	g = sin * ((item->trigger_flags << 16) >> 18) & 0xF8 >> 9;
	b = sin * ((item->trigger_flags >> 23) & 0xF8) >> 9;

	TriggerDynamic(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, 24, r, g, b);
}

void ControlColouredLight(short item_number)//5D368(<), 5D7E4 (F)
{
	struct ITEM_INFO* item;
	long r;
	long g;
	long b;

	item = &items[item_number];

	if (!TriggerActive(item))
		return;

	r = (item->trigger_flags & 0x1F) << 3;
	g = (item->trigger_flags << 16) >> 18 & 0xF8;
	b = (item->trigger_flags << 23) >> 17 & 0xF8;

	TriggerDynamic(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, 24, r, g, b);

	UNIMPLEMENTED();
}

void ControlElectricalLight(short item_number)//5D3F8, 5D874
{
	UNIMPLEMENTED();
}

void ControlBlinker(short item_number)//5D660(<), 5DADC (F)
{
	struct ITEM_INFO* item;
	struct PHD_VECTOR pos;
	long r;
	long g;
	long b;

	item = &items[item_number];

	if (!TriggerActive(item))
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