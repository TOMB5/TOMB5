#include "LOAD_LEV.H"

#include "GPU.H"
#include "PROFILE.H"

unsigned char LtLoadingBarEnabled;
unsigned char LoadingBarEnabled;
unsigned char _first_time_ever;
short DelRotAng;
//struct STASHEDOBJ* cur_stashed_object;
//struct STASHEDDAT* cur_stashed_matrix;
int num_objects_stashed;
//struct STASHEDOBJ stashed_objects_list[128];
//struct STASHEDDAT stashed_matrix_list[240];
unsigned char char_anim;
unsigned char OurSqrt[1024];
//struct WATERTAB WaterTable[22][64];
//struct MATRIX3D* Matrix;
unsigned short SqrtTable[210];
unsigned short ScalarTable[198];
//struct MATRIX3D iMatrixStack[32];
//struct SVECTOR CamRot;
//struct MATRIX3D* iMatrix;
unsigned short MatrixSP;
//struct MATRIX3D MatrixStack[32];
long iFrac;
long iRate;
long iAmbientR;
long iAmbientG;
long iAmbientB;
long atanOctantTab[8];
short atanTab[2050];

void LOAD_DrawEnable()//5F2C8, 5FFA8
{
	LtLoadingBarEnabled = 0;
}

void LOAD_Stop()//60434, 60FB4
{
	LOAD_DrawEnable();

	LoadingBarEnabled = 0;

	db.draw[1].isbg = 1;
	db.draw[0].isbg = 1;

	db.draw[1].dtd = 1;

#ifdef PSX
	GPU_UseOrderingTables();
#endif

	//FIXME: v1 (1) May be changed in GPU_UseOrderingTables, must clarify
	db.draw[0].dtd = 1;

#ifdef PSX
	GPU_SyncBothScreens();//5F374, 60054
#endif

	db.current_buffer = 0;
	db.current_buffer = 1;

#if _DEBUG
	//Internal Beta
	ProfileDraw = 1;
#endif

	_first_time_ever = 0;
}