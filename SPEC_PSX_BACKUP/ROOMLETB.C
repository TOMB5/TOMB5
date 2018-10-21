#include "ROOMLETB.H"

#include "CAMERA.H"
#include "DRAW.H"
#include "SPECIFIC.H"
#include "SPECTYPES.H"

int QuadVertTables[] = { 0x000749F0, 0x000749BC, 0x00074988, 0x00074954 };
int TriVertTables[] = { 0x00074AE8, 0x00074ABC, 0x00074A90, 0x00074A64 };

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