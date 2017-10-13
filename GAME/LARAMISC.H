#ifndef LARAMISC_H
#define LARAMISC_H

#include "SPECTYPES.H"

extern char* states[131];
extern char* quadrant_names[4];
extern char* gunstates[6];
extern char* waterstates[5];
extern char* guntypes[9];
extern char* coll_typess[8];
extern char* htypes[4];
extern short SubsuitAir;
extern COLL_INFO mycoll;
extern short cheat_hit_points;

extern void GetLaraDeadlyBounds();
extern void DelAlignLaraToRope(ITEM_INFO* item);
extern void InitialiseLaraAnims(ITEM_INFO* item);
extern void InitialiseLaraLoad(short item_num);
extern void LaraControl(short item_number);
extern void LaraCheat(ITEM_INFO* item, COLL_INFO* coll);
extern void LaraInitialiseMeshes();

#endif