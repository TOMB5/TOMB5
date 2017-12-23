#ifndef BOX_H
#define BOX_H

#include "SPECTYPES.H"

#define BOX_BLOCKED (1 << 14) // unpassable for other enemies, always set for movable blocks & closed doors
#define BOX_LAST    (1 << 15) // unpassable by large enemies (T-Rex, Centaur, etc), always set behind doors

extern int number_boxes;
extern struct box_info* boxes;
extern unsigned short* overlap;
extern short* ground_zone[5][2];
extern unsigned short testclip;
extern unsigned short loops;

extern void DropBaddyPickups(struct ITEM_INFO* item);
extern int MoveCreature3DPos(struct PHD_3DPOS* srcpos, struct PHD_3DPOS* destpos, int velocity, short angdif, int angadd);
extern void CreatureYRot(struct PHD_3DPOS* srcpos, short angle, short angadd);
extern short SameZone(struct creature_info* creature, struct ITEM_INFO* target_item);
extern void FindAITargetObject(struct creature_info* creature, short obj_num);
extern void GetAITarget(struct creature_info* creature);
extern short AIGuard(struct creature_info* creature);
extern void AlertNearbyGuards(struct ITEM_INFO* item);
extern void AlertAllGuards(short item_number);
extern void CreatureKill(struct ITEM_INFO* item, int kill_anim, int kill_state, short lara_anim);
extern int CreatureVault(short item_number, short angle, int vault, int shift);
extern short CreatureEffectT(struct ITEM_INFO* item, struct BITE_INFO* bite, short damage, short angle, short (*generate)(
	                             long x, long y, long z, short speed, short yrot, short room_number));
extern short CreatureEffect(struct ITEM_INFO* item, struct BITE_INFO* bite, short (*generate)(long x, long y, long z, short speed, short yrot,
                                                                                              short room_number));
extern void CreatureUnderwater(struct ITEM_INFO* item, long depth);
extern void CreatureFloat(short item_number);
extern void CreatureJoint(struct ITEM_INFO* item, short joint, short required);
extern void CreatureTilt(struct ITEM_INFO* item, short angle);
extern short CreatureTurn(struct ITEM_INFO* item, short maximum_turn);
extern int CreatureAnimation(short item_number, short angle, short tilt);
extern void CreatureDie(short item_number, int explode);
extern int BadFloor(long x, long y, long z, long box_height, long next_height, int room_number, struct lot_info* LOT);
extern int CreatureCreature(short item_number);
extern enum target_type CalculateTarget(struct PHD_VECTOR* target, struct ITEM_INFO* item, struct lot_info* LOT);
extern void CreatureMood(struct ITEM_INFO* item, struct AI_info* info, int violent);
extern void GetCreatureMood(struct ITEM_INFO* item, struct AI_info* info, int violent);
extern int ValidBox(struct ITEM_INFO* item, short zone_number, short box_number);
extern int EscapeBox(struct ITEM_INFO* item, struct ITEM_INFO* enemy, short box_number);
extern void TargetBox(struct lot_info* LOT, short box_number);
extern int UpdateLOT(struct lot_info* LOT, int expansion);
extern int SearchLOT(struct lot_info* LOT, int expansion);
extern void CreatureAIInfo(struct ITEM_INFO* item, struct AI_info* info);
extern int CreatureActive(short item_number);
extern void InitialiseCreature(short item_number);
extern int StalkBox(struct ITEM_INFO* item, struct ITEM_INFO* enemy, short box_number);

#endif