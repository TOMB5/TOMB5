#ifndef PICKUP_H
#define PICKUP_H

#include "STYPES.H"

extern short SearchCollectFrames[4];
extern short SearchAnims[4];
extern short SearchOffsets[4];
extern unsigned char NumRPickups; // offset 0xA390C
extern unsigned char RPickups[16];
extern struct PHD_VECTOR OldPickupPos;

extern void MonitorScreenCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll);
extern void CollectCarriedItems(struct ITEM_INFO* item);
extern void SearchObjectCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll);
extern void SearchObjectControl(short item_number);
extern int PickupTrigger(short item_num);
extern int KeyTrigger(short item_num);
extern void PuzzleHoleCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll);
extern void PuzzleDoneCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll);
extern void KeyHoleCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll);
extern void PickUpCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll);
extern void RegeneratePickups();
extern void AnimatingPickUp(short item_number);
extern short* FindPlinth(struct ITEM_INFO* item);
extern void PuzzleDone(struct ITEM_INFO* item, short item_num);

#endif