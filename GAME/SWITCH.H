#ifndef SWITCH_H
#define SWITCH_H

extern unsigned char SequenceUsed[6];
extern unsigned char SequenceResults[3][3][3];
extern unsigned char Sequences[3];
extern unsigned char CurrentSequence;

extern void ProcessExplodingSwitchType8(struct ITEM_INFO *item);
extern void CrowDoveSwitchCollision(short item_num, struct ITEM_INFO *l, struct COLL_INFO *coll);
extern void CrowDoveSwitchControl(short item_number);
extern void CogSwitchCollision(short item_num, struct ITEM_INFO *l, struct COLL_INFO *coll);
extern void CogSwitchControl(short item_num);
extern void FullBlockSwitchCollision(short item_num, struct ITEM_INFO *l, struct COLL_INFO *coll);
extern void FullBlockSwitchControl(short item_number);
extern void CrowbarSwitchCollision(short item_num, struct ITEM_INFO *l, struct COLL_INFO *coll);
extern void JumpSwitchCollision(short item_num, struct ITEM_INFO *l, struct COLL_INFO *coll);
extern void RailSwitchCollision(short item_num, struct ITEM_INFO *l, struct COLL_INFO *coll);
extern void TurnSwitchCollision(short item_num, struct ITEM_INFO *l, struct COLL_INFO *coll);
extern void TurnSwitchControl(short item_num);
extern void PulleyCollision(short item_num, struct ITEM_INFO *l, struct COLL_INFO *coll);
extern void UnderwaterSwitchCollision(short item_num, struct ITEM_INFO *l, struct COLL_INFO *coll);
extern void SwitchCollision2(short item_num, struct ITEM_INFO *l, struct COLL_INFO *coll);
extern void SwitchCollision(short item_num, struct ITEM_INFO *l, struct COLL_INFO *coll);
extern void SwitchControl(short item_number);
extern void TestTriggersAtXYZ(long x, long y, long z, short room_number, int heavy, int flags);
extern int GetKeyTrigger(struct ITEM_INFO *item);
extern int GetSwitchTrigger(struct ITEM_INFO *item, short *ItemNos, long AttatchedToSwitch);
extern int SwitchTrigger(short item_num, short timer);

#endif