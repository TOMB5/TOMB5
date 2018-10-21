#include "CODEWAD.H"
#include "CONTROL.H"
#include "DELTAPAK.H"
#include "SPECIFIC.H"
#include "TYPES.H"
#include "OBJECTS.H"
#include "LARA.H"
#include "GAMEFLOW.H"

void TriggerEngineEffects_CUT()
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

	UNIMPLEMENTED();
}

long sub_1BE988()
{
	UNIMPLEMENTED();
	return 0;
}

long sub_1BDF88(long levelID)
{
	UNIMPLEMENTED();
	return 0;
}



