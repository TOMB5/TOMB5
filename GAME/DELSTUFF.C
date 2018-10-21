#include "DELSTUFF.H"

#include "SPECIFIC.H"

struct MATRIX3D lara_joint_matrices[15];
struct MATRIX3D lara_matrices[15];
struct CVECTOR LaraNodeAmbient[2];
short* GLaraShadowframe;
unsigned char LaraNodeUnderwater[15];
long LaraGlobalClipFlag = -1;

char lara_underwater_skin_sweetness_table[15] =
{
	0, 2, 3, 0, 5, 6, 7, 9, 0xA, 0xB, 0xC, 0xD, 0xE, 8, 0
};

int lara_mesh_sweetness_table[15] =
{
	0, 1, 2, 3, 4, 5, 6, 7, 0xE, 8, 9, 0xA, 0xB, 0xC, 0xD
};

unsigned char SkinUseMatrix[14][2] =
{
	{ 0xFF, 0xFF },
	{ 1, 2 },
	{ 0xFF, 0xFF },
	{ 0xFF, 0xFF },
	{ 4, 5 },
	{ 0xFF, 0xFF },
	{ 0xFF, 0xFF },
	{ 0xFF, 0xFF },
	{ 9, 0xA },
	{ 0xFF, 0xFF },
	{ 0xFF, 0xFF },
	{ 0xC, 0xD },
	{ 0xFF, 0xFF },
	{ 0xFF, 0xFF }
};

char NodesToStashToScratch[14][2] =
{
	{ 1, 3 },
	{ 4, 5 },
	{ 6, 7 },
	{ 2, 8 },
	{ 9, 0xA },
	{ 0xB, 0xC },
	{ 0, 0xD },
	{ 0xE, 0x11 },
	{ 0x12, 0x13 },
	{ 0x14, 0x15 },
	{ 0xF, 0x16 },
	{ 0x17, 0x18 },
	{ 0x19, 0x1A },
	{ 0x10, 0x1B }
};

char NodesToStashFromScratch[15][4] =
{
	{ 0, 1, 2, -1 },
	{ 3, 4, -1, 0 },
	{ 5, 6, -1, 0 },
	{ 7, -1, 0, 0 },
	{ 8, 9, -1, 0 },
	{ 0xA, 0xB, -1, 0 },
	{ 0xC, -1, 0, 0 },
	{ 0xD, 0x10, 0xE, 0xF },
	{ 0x1B, 0x1C, 0x22, -1 },
	{ 0x11, 0x12, -1, 0 },
	{ 0x13, 0x14, -1, 0 },
	{ 0x15, -1, 0, 0 },
	{ 0x16, 0x17, -1, 0 },
	{ 0x18, 0x19, -1, 0 },
	{ 0x1A, -1, 0, 0 }
};

char HairRotScratchVertNums[5][12] =
{
	{ 4, 5, 6, 7, -1, 0, 0, 0, 0, 0, 0, 0 },
	{ 5, 6, 7, 4, -1, 0, 0, 0, 0, 0, 0, 0 },
	{ 6, 7, 4, 5, -1, 0, 0, 0, 0, 0, 0, 0 },
	{ 7, 4, 5, 6, -1, 0, 0, 0, 0, 0, 0, 0 },
	{ 4, 5, 6, 7, -1, 0, 0, 0, 0, 0, 0, 0 }
};

void CalcLaraMatrices(int flag)//2C1DC, 2C504
{
	UNIMPLEMENTED();
}