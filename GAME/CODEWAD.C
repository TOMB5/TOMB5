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

	S_Warn("[RelocFunc_28] - Unimplemented!\n");
}

void RelocFunc_34_08() // (F)
{
	lara_item->mesh_bits = -1;
	Chris_Menu = 0;
}

void RelocFunc_34_0C()
{
	S_Warn("[RelocFunc_016] - Unimplemented!\n");
}

void RelocFunc_34_10()
{
	S_Warn("[RelocFunc_017] - Unimplemented!\n");
}

void RelocFunc_34_14()
{
	S_Warn("[RelocFunc_018] - Unimplemented!\n");
}

void RelocFunc_34_18()
{
	S_Warn("[RelocFunc_019] - Unimplemented!\n");
}

void RelocFunc_34_1C()
{
	S_Warn("[RelocFunc_020] - Unimplemented!\n");
}

void RelocFunc_34_20()
{
	S_Warn("[RelocFunc_021] - Unimplemented!\n");
}

void RelocFunc_34_24()
{
	S_Warn("[RelocFunc_022] - Unimplemented!\n");
}

void RelocFunc_34_28()
{
	S_Warn("[RelocFunc_023] - Unimplemented!\n");
}

void RelocFunc_34_2C()
{
	S_Warn("[RelocFunc_024] - Unimplemented!\n");
}

void RelocFunc_34_30()
{
	S_Warn("[RelocFunc_025] - Unimplemented!\n");
}

void RelocFunc_34_34()
{
#if PC_VERSION && 0
	ResetCutanimate(STROBE_LIGHT);
	if (!bDoCredits)
	{
		trigger_title_spotcam(1);
		lara_item->mesh_bits = 0;
}
	BYTE2(dels_cutseq_player) = 0;
	title_controls_locked_out = 0;
#else
	S_Warn("[RelocFunc_026] - Unimplemented!\n");
#endif
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



void triggerwindowsmash(int item_num) // (F)
{
	struct ITEM_INFO* item = find_a_fucking_item(item_num);
	ExplodeItemNode(item, 0, 0, 64);
	item->mesh_bits = 2;
}