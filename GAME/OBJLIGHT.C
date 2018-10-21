#include "OBJLIGHT.H"

#include "SPECIFIC.H"

struct FOOTPRINT FootPrint[32];
int FootPrintNum;


void TriggerAlertLight(long x, long y, long z, long r, long g, long b, long angle, int room_no, int falloff)//5D018, 5D494
{
}

void ControlBlinker(short item_number)//5D660, 5DADC
{
	UNIMPLEMENTED();
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