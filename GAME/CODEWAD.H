#ifndef CODEWAD_H
#define CODEWAD_H

#include "TYPES.H"

extern void TriggerEngineEffects_CUT(); // 0x10 (RelocPtr + 0x18)
extern void RelocFunc_34_08(); // special1_init
extern void RelocFunc_34_0C(); // special1_control
extern void RelocFunc_34_10(); // special1_end
extern void RelocFunc_34_14(); // special2_init
extern void RelocFunc_34_18(); // special2_control
extern void RelocFunc_34_1C(); // special2_end
extern void RelocFunc_34_20(); // special3_init
extern void RelocFunc_34_24(); // special3_control
extern void RelocFunc_34_28(); // special3_end
extern void RelocFunc_34_2C(); // special4_init
extern void RelocFunc_34_30(); // special4_control
extern void RelocFunc_34_34(); // special4_end
extern long sub_1BE988();
extern long sub_1BDF88(long levelID);
extern void triggerwindowsmash(int item_num);

#endif