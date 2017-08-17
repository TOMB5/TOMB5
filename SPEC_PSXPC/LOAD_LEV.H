#ifndef LOAD_LEV_H
#define LOAD_LEV_H

#include "PSXTYPES.H"

extern void LOAD_DrawEnable(unsigned char isEnabled);
extern void LOAD_Stop();
extern void LOAD_Start(int file_number);
extern void LOAD_VSyncHandler();

extern unsigned char LtLoadingBarEnabled;
extern unsigned char LoadingBarEnabled;
extern unsigned char _first_time_ever;
extern short DelRotAng;
extern struct STASHEDOBJ* cur_stashed_object;
extern struct STASHEDDAT* cur_stashed_matrix;
extern int num_objects_stashed;
extern struct STASHEDOBJ stashed_objects_list[128];
extern struct STASHEDDAT stashed_matrix_list[240];
extern unsigned char char_anim;
extern unsigned char OurSqrt[1024];
extern struct WATERTAB WaterTable[22][64];
extern struct MATRIX3D* Matrix;
extern unsigned short SqrtTable[210];
extern unsigned short ScalarTable[198];
extern struct MATRIX3D iMatrixStack[32];
extern struct SVECTOR CamRot;
extern struct MATRIX3D* iMatrix;
extern unsigned short MatrixSP;
extern struct MATRIX3D MatrixStack[32];
extern long iFrac;
extern long iRate;
extern long iAmbientR;
extern long iAmbientG;
extern long iAmbientB;
extern long atanOctantTab[8];
extern short atanTab[2050];

#endif