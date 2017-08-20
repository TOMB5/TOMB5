#include "OBJLIGHT.H"
#include "SPECIFIC.H"

struct FOOTPRINT FootPrint[32];
int FootPrintNum;

void ControlBlinker(short item_number)//5D660, 5DADC
{
	S_Warn("[ControlBlinker] - Unimplemented!\n");
}

void ControlElectricalLight(short item_number)//5D3F8, 5D874
{
	S_Warn("[ControlElectricalLight] - Unimplemented!\n");
}

void ControlColouredLight(short item_number)//5D368, 5D7E4
{
	S_Warn("[ControlColouredLight] - Unimplemented!\n");
}

void ControlPulseLight(short item_number)//5D254, 5D6D0
{
	S_Warn("[ControlPulseLight] - Unimplemented!\n");
}

void ControlStrobeLight(short item_number)//5D118, 5D594
{
	S_Warn("[ControlStrobeLight] - Unimplemented!\n");
}

void TriggerAlertLight(long x, long y, long z, long r, long g, long b, long angle, int room_no, int falloff)//5D018, 5D494
{
	S_Warn("[TriggerAlertLight] - Unimplemented!\n");
}
