#include "DRAWOBJ.H"

#include "SPECIFIC.H"
#include "LIBGPU.H"
#include "EMULATOR.H"
#include "GPU.H"

void MakeMono(unsigned short* s, unsigned char* d)//7F9E4, 81A28
{
	//at = 0x421
#if 0
	ctc2    $at, $29
	lw      $t0, 0($a0)
	li      $v0, 0x3FFF
	li      $v1, 0xD371F947
	li      $t4, 0x41C64E6D

	 loc_7FA04:
			 mult    $v1, $t4
				 srl     $t3, $t0, 26
				 srl     $t2, $t0, 21
				 srl     $t1, $t0, 16
				 andi    $t3, 0x1F
				 andi    $t2, 0x1F
				 andi    $t1, 0x1F
				 mtc2    $t3, $17
				 mtc2    $t2, $18
				 mtc2    $t1, $19
				 addi    $a0, 4
				 cop2    0x158002D
				 srl     $t2, $t0, 10
				 srl     $t1, $t0, 5
				 andi    $t2, 0x1F
				 andi    $t1, 0x1F
				 andi    $t0, 0x1F
				 mtc2    $t2, $17
				 mtc2    $t1, $18
				 mtc2    $t0, $19
				 mfc2    $t1, $7
				 cop2    0x158002D
				 mflo    $v1
				 addiu   $v1, 0x3039
				 lw      $t0, 0($a0)
				 mfc2    $at, $7
				 srl     $t3, $v1, 16
				 srl     $t5, $v1, 24
				 andi    $t3, 1
				 andi    $t5, 1
				 sltiu   $t2, $t1, 0xF
				 bnez    $t2, loc_7FA8C
				 sltiu   $t2, $at, 0xF
				 li      $t1, 0xF

				 loc_7FA8C:
			 bnez    $t2, loc_7FA98
				 sub     $t1, $t3
				 li      $at, 0xF

				 loc_7FA98 :
				 bgez    $t1, loc_7FAA4
				 sub     $at, $t5
				 move    $t1, $zero

				 loc_7FAA4 :
			 bgez    $at, loc_7FAB0
				 sll     $t1, 4
				 move    $at, $zero

				 loc_7FAB0 :
			 or $t1, $at
				 sb      $t1, 0($a1)
				 addi    $a1, 1
				 bnez    $v0, loc_7FA04
				 addi    $v0, -1
				 li      $v0, 0xAA
				 ctc2    $v0, $29
				 jr      $ra
				 nop
#endif
	S_Warn("[MakeMono] - Unimplemented!\n");
}

void InitObjGTE()
{
	S_Warn("[InitObjGTE] - Unimplemented!\n");
}

void DrawClippedMesh(int vertcache, short* mesh, MMTEXTURE* text, char* ot, char* prim, char* prim_lim, long fp, long prim_len, long num_tri)
{
	UNIMPLEMENTED();
}

void DrawSubDivMesh()
{
	UNIMPLEMENTED();
}

void initialise_light_matrix()
{
	UNIMPLEMENTED();
}

void phd_PutPolygons_normal(short* mesh, short clip)
{
	initialise_light_matrix();

	mesh_header* mptr = (mesh_header*)mesh;

#if GLTEST
	Emulator_TestDrawVertices(mesh, RoomTextInfo);
#endif
	UNIMPLEMENTED();
}

void phd_PutPolygons_pickup(short* mesh, short clip)
{
	UNIMPLEMENTED();
}

void phd_PutPolygons_seethrough(short* mesh, short clip)
{
	UNIMPLEMENTED();
}

void phd_PutPolygons_train(short* mesh, short clip)
{
	UNIMPLEMENTED();
}

void phd_PutPolygons(short* mesh, short clip)
{
	phd_PutPolygons_normal(mesh, clip);
}

void phd_PutPolygons_pickup(short* meshp, long unk)
{
	UNIMPLEMENTED();
}

void phd_PutPolygons_seethrough(short* meshp, long unk)
{
	UNIMPLEMENTED();
}
