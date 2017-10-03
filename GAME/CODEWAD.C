#include "CODEWAD.H"
#include "CONTROL.H"
#include "DELTAPAK.H"
#include "SPECIFIC.H"
#include "TYPES.H"

void RelocFunc_006()
{
	S_Warn("[RelocFunc_006] - Unimplemented!\n");
}

void RelocFunc_010()
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

	S_Warn("[RelocFunc_28] - Unimplemented!\n");
}

void RelocFunc_015()
{
	S_Warn("[RelocFunc_015] - Unimplemented!\n");
}

void RelocFunc_016()
{
	S_Warn("[RelocFunc_016] - Unimplemented!\n");
}

void RelocFunc_017()
{
	S_Warn("[RelocFunc_017] - Unimplemented!\n");
}

void RelocFunc_018()
{
	S_Warn("[RelocFunc_018] - Unimplemented!\n");
}

void RelocFunc_019()
{
	S_Warn("[RelocFunc_019] - Unimplemented!\n");
}

void RelocFunc_020()
{
	S_Warn("[RelocFunc_020] - Unimplemented!\n");
}

void RelocFunc_021()
{
	S_Warn("[RelocFunc_021] - Unimplemented!\n");
}

void RelocFunc_022()
{
	S_Warn("[RelocFunc_022] - Unimplemented!\n");
}

void RelocFunc_023()
{
	S_Warn("[RelocFunc_023] - Unimplemented!\n");
}

void RelocFunc_024()
{
	S_Warn("[RelocFunc_024] - Unimplemented!\n");
}

void RelocFunc_025()
{
	S_Warn("[RelocFunc_025] - Unimplemented!\n");
}

void RelocFunc_026()
{
	S_Warn("[RelocFunc_026] - Unimplemented!\n");
}

long sub_1BE988()
{
	S_Warn("[sub_1BE988] - Unimplemented!\n");
	return 0;
}

long sub_1BDF88(long levelID)
{
	S_Warn("[sub_1BDF88] - Unimplemented!\n");
	return 0;
}

