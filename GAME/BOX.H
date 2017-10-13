#ifndef BOX_H
#define BOX_H

#include "SPECTYPES.H"

#define BOX_BLOCKED (1 << 14) // unpassable for other enemies, always set for movable blocks & closed doors
#define BOX_LAST    (1 << 15) // unpassable by large enemies (T-Rex, Centaur, etc), always set behind doors

extern int number_boxes;
extern box_info* boxes;
extern unsigned short* overlap;
extern short* ground_zone[5][2];
extern unsigned short testclip;
extern unsigned short loops;

extern void DropBaddyPickups(ITEM_INFO* item);
extern int MoveCreature3DPos(PHD_3DPOS* srcpos, PHD_3DPOS* destpos, int velocity, short angdif, int angadd);
extern void CreatureYRot(PHD_3DPOS* srcpos, short angle, short angadd);
extern short SameZone(creature_info* creature, ITEM_INFO* target_item);
extern void FindAITargetObject(creature_info* creature, short obj_num);
extern void GetAITarget(creature_info* creature);
extern short AIGuard(creature_info* creature);
extern void AlertNearbyGuards(ITEM_INFO* item);
extern void AlertAllGuards(short item_number);
extern void CreatureKill(ITEM_INFO* item, int kill_anim, int kill_state, short lara_anim);
extern int CreatureVault(short item_number, short angle, int vault, int shift);
extern short CreatureEffectT(ITEM_INFO* item, BITE_INFO* bite, short damage, short angle, short* generate);
extern short CreatureEffect(ITEM_INFO* item, BITE_INFO* bite, short* generate);
extern void CreatureUnderwater(ITEM_INFO* item, long depth);
extern void CreatureFloat(short item_number);
extern void CreatureJoint(ITEM_INFO* item, short joint, short required);
extern void CreatureTilt(ITEM_INFO* item, short angle);
extern short CreatureTurn(ITEM_INFO* item, short maximum_turn);
extern int CreatureAnimation(short item_number, short angle, short tilt);
extern void CreatureDie(short item_number, int explode);
extern int BadFloor(long x, long y, long z, long box_height, long next_height, int room_number, lot_info* LOT);
extern int CreatureCreature(short item_number);
extern enum target_type CalculateTarget(PHD_VECTOR* target, ITEM_INFO* item, lot_info* LOT);
extern void CreatureMood(ITEM_INFO* item, AI_info* info, int violent);
extern void GetCreatureMood(ITEM_INFO* item, AI_info* info, int violent);
extern int ValidBox(ITEM_INFO* item, short zone_number, short box_number);
extern int EscapeBox(ITEM_INFO* item, ITEM_INFO* enemy, short box_number);
extern void TargetBox(lot_info* LOT, short box_number);
extern int UpdateLOT(lot_info* LOT, int expansion);
extern int SearchLOT(lot_info* LOT, int expansion);
extern void CreatureAIInfo(ITEM_INFO* item, AI_info* info);
extern int CreatureActive(short item_number);
extern void InitialiseCreature(short item_number);
extern int StalkBox(ITEM_INFO* item, ITEM_INFO* enemy, short box_number);

#endif