#include "SWITCH.H"

#include "CONTROL.H"
#include "SPECIFIC.H"

void TestTriggersAtXYZ(long x, long y, long z, short room_number, int heavy, int flags)//561A8(<), 56648(<)
{
	int s4 = x;
	int s3 = y;
	int s2 = z;

	int s1 = heavy;
	int s0 = flags;
	int a3 = room_number;

#if 0
	jal	sub_78954//GetFloor();
	nop
	move	$a0, $v0
	move	$a1, $s4
	move	$a2, $s3
	move	$a3, $s2
	jal	sub_78C74//GetHeight($v0@GetFloor();, x, y, z);
#endif


	TestTriggers(trigger_index, heavy, flags);
	S_Warn("[TestTriggersAtXYZ] - Unimplemented!\n");
	return;
}
