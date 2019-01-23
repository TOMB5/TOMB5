#include "ROOMLETB.H"

#include "CAMERA.H"
#include "DRAW.H"
#include "SPECIFIC.H"
#include "SPECTYPES.H"

void DrawRoomsAsm()//0x1BC380
{
	DrawRoomletListAsm(0, &room[camera.pos.room_number]);
}

#ifndef USE_ASM
void DrawRoomletListAsmBinocular(long underwater, struct room_info* r)//roomletb
{
	S_Warn("[DrawRoomletListAsmBinocular] - Unimplemented!\n");
}

void DrawRoomletListAsm(long unk, struct room_info* r)//0x1BC4D0
{
	S_Warn("[DrawRooms] - Unimplemented!\n");
}
#endif