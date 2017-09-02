#include "CODEWAD.H"

#include "TYPES.H"
#include "DELTAPAK.H"
#include "CONTROL.H"
#include "SPECIFIC.H"

void RelocFunc_28()
{
#if 0
	struct PHD_VECTOR pos1, pos2;
	int n;

	for (n = 0; n < 2; n++)
	{
		pos1.x = -80;
		pos1.y = -128;
		pos1.z = -144;
		GetActorJointAbsPosition(1, 7, &pos1);
		word_51D032 = 512;
		pos2.x = -80;
		pos2.y = 320;
		pos2.z = -144;
		pos2.x = -80 + GetRandomControl() % 128 - 64;
		pos2.z = pos2.z + GetRandomControl() % 128 - 64;
		GetActorJointAbsPosition(1, 7, &pos2);
		sub_402B85((int)&pos1, (int)&pos2, word_51D032 >> 8);
		pos2.x = -80;
		pos2.y = 320;
		pos2.z = -144;
		pos2.x = -80 + GetRandomControl() % 128 - 64;
		pos2.z = pos2.z + GetRandomControl() % 128 - 64;
		GetActorJointAbsPosition(1, 7, &pos2);
		sub_402B85((int)&pos1, (int)&pos2, -(word_51D032 >> 8));
	}
#endif

	S_Warn("[RelocFunc_28] - Unimplemented!\\n");
}
