#ifndef TRAPS_H
#define TRAPS_H

#include "SPECTYPES.H"

extern short SPDETyoffs[8];
extern unsigned char Flame3xzoffs[16][2];
extern short SPyoffs[8];
extern short SPxzoffs[8];

extern void ControlExplosion(short item_number);
extern void ControlRaisingBlock(short item_number);
extern void ControlScaledSpike(short item_number);
extern int TestBoundsCollideTeethSpikes(struct ITEM_INFO* item);
extern void ControlTwoBlockPlatform(short item_number);
extern int OnTwoBlockPlatform(struct ITEM_INFO* item, long x, long z);
extern void TwoBlockPlatformCeiling(struct ITEM_INFO* item, long x, long y, long z, long* height);
extern void TwoBlockPlatformFloor(struct ITEM_INFO* item, long x, long y, long z, long* height);
extern void DrawScaledSpike(struct ITEM_INFO* item);
extern void RollingBallCollision(short item_number, struct ITEM_INFO* laraitem, struct COLL_INFO* coll);
extern void ControlRollingBall(short item_number);
extern void LavaBurn(struct ITEM_INFO* item);
extern void LaraBurn();
extern void FlameControl(short fx_number);
extern void FlameEmitter3Control(short item_number);
extern void FlameEmitter2Control(short item_number);
extern void FlameEmitterControl(short item_number);
extern void DartsControl(short item_num);
extern void DartEmitterControl(short item_num);
extern void FallingCeiling(short item_number);
extern void FallingBlockCeiling(struct ITEM_INFO* item, long x, long y, long z, long* height);
extern void FallingBlockFloor(struct ITEM_INFO* item, long x, long y, long z, long* height);
extern void FallingBlock(short item_number);
extern void FallingBlockCollision(short item_number, struct ITEM_INFO* l, struct COLL_INFO* coll);
extern void TrapDoorCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll);
extern void CeilingTrapDoorCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll);
extern void FloorTrapDoorCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll);
extern void TrapDoorControl(short item_number);
extern void CloseTrapDoor(struct ITEM_INFO* item);
extern void OpenTrapDoor(struct ITEM_INFO* item);

#endif