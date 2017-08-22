#ifndef DELSTUFF_H
#define DELSTUFF_H

#include "SPECTYPES.H"

extern struct MATRIX3D lara_joint_matrices[15];
extern struct MATRIX3D lara_matrices[15];
extern struct CVECTOR LaraNodeAmbient[2];
extern short *GLaraShadowframe;
extern unsigned char LaraNodeUnderwater[15];
extern long LaraGlobalClipFlag;
extern char lara_underwater_skin_sweetness_table[15];
extern int lara_mesh_sweetness_table[15];
extern unsigned char SkinUseMatrix[14][2];
extern char NodesToStashToScratch[14][2];
extern char NodesToStashFromScratch[15][4];
extern char HairRotScratchVertNums[5][12];

extern void CalcLaraMatrices(int flag);

#endif