#ifndef DRAWPHAS_H
#define DRAWPHAS_H

#include "SPECTYPES.H"

extern long DrawPhaseGame();
extern void UpdateSky();
extern void mQuickW2VMatrix();
extern void DrawRooms(short current_room);
extern void PrintString(long x, long y, long unk, char* string);
extern void DrawBinoculars();
extern void DrawFlash();
extern void SortOutWreckingBallDraw();
extern void MGDrawSprite(int x, int y, int def, int z, int xs, int ys, long rgb);
extern void CalcClipWindow_ONGTE(short room_number, long unknown);
extern void DrawAllFx();
extern void InitObjGTE();
#define WANK3 InitObjGTE
extern void DrawCutSeqActors();
extern void DrawRoomletListAsmBinocular(long underwater, struct room_info* r);
extern void GetRoomBoundsAsm(short room_number);
extern void SetGunFlash(short gun_type);

extern long StoreBoxes;
extern struct GAME_VECTOR LaraPos;
extern struct PSXTEXTI* MonitorScreenTI;
extern unsigned char MonitorScreenU0;
extern unsigned char MonitorHold;
extern short MonitorOff;
extern short MonitorOff2;

#endif