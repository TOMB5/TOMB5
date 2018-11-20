#ifndef LARAMISC_H
#define LARAMISC_H

#include "SPECTYPES.H"

#if DEBUG_VERSION
extern char* states[131];
extern char* quadrant_names[4];
extern char* gunstates[6];
extern char* waterstates[5];
extern char* guntypes[9];
extern char* coll_typess[8];
extern char* htypes[4];
#endif

extern short SubsuitAir;
extern struct COLL_INFO mycoll;
extern short cheat_hit_points;

extern void GetLaraDeadlyBounds();
extern void DelAlignLaraToRope(struct ITEM_INFO* item);
extern void InitialiseLaraAnims(struct ITEM_INFO* item);
extern void InitialiseLaraLoad(short item_num);
extern void InitialiseLara(int restore);
extern void LaraControl(short item_number);
extern void LaraCheat(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void LaraInitialiseMeshes();

#endif