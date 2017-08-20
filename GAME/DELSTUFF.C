#include "DELSTUFF.H"
#include "SPECIFIC.H"

struct MATRIX3D lara_joint_matrices[15];
struct MATRIX3D lara_matrices[15];
struct CVECTOR LaraNodeAmbient[2];
short *GLaraShadowframe;
unsigned char LaraNodeUnderwater[15];
long LaraGlobalClipFlag;
char lara_underwater_skin_sweetness_table[15];
int lara_mesh_sweetness_table[15];
unsigned char SkinUseMatrix[14][2];
char NodesToStashToScratch[14][2];
char NodesToStashFromScratch[15][4];
char HairRotScratchVertNums[5][12];

void CalcLaraMatrices(int flag)//2C1DC, 2C504
{
	S_Warn("[CalcLaraMatrices] - Unimplemented!\n");
}
