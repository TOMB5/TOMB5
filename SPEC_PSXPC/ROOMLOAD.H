#ifndef ROOMLOAD_H
#define ROOMLOAD_H

#include "SPECTYPES.H"

extern long AnimFilePos;
extern long AnimFileLen;
extern short* floor_data;
extern unsigned long* SetupPtr;
extern unsigned short ClutStartY;
extern struct SVECTOR* RoomBBoxes;
extern short* mesh_base;
extern struct PSXSPRITESTRUCT* GLOBAL_default_sprites_ptr;
extern struct PSXTEXTI* AnimatingWaterfalls[6];
extern int AnimatingWaterfallsV[6];
extern unsigned long envmap_data[6];
extern unsigned long* RelocPtr[128];

extern void ReloadAnims(int name, long len);
extern void S_LoadLevelFile(int Name);

#endif