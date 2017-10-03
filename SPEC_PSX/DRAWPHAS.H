#ifndef DRAWPHAS_H
#define DRAWPHAS_H

#include "SPECTYPES.H"

extern long DrawPhaseGame();
extern void UpdateSky();
extern void mQuickW2VMatrix();
extern void DrawRooms(short current_room);
extern void PrintString(long x, long y, long unk, char* string);

extern long StoreBoxes;
extern struct GAME_VECTOR LaraPos;
extern struct PSXTEXTI* MonitorScreenTI;
extern unsigned char MonitorScreenU0;
extern unsigned char MonitorHold;
extern short MonitorOff;
extern short MonitorOff2;

#endif