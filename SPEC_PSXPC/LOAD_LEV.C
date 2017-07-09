#include "LOAD_LEV.H"

#include "GAMEWAD.H"
#include "GAMEFLOW.H"
#include "GPU.H"
#include "MALLOC.H"
#include "PROFILE.H"

#include <assert.h>

#if 0
#include <limits>
#endif

#ifndef SHRT_MAX
#define SHRT_MAX 32767
#endif

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

int dword_AD920 = 0;
int dword_A33F6 = 0;
char dword_A33F5 = 0;
int dword_A5EE0 = 0;

void LOAD_DrawEnable(unsigned char isEnabled)//5F2C8, 5FFA8
{
	LtLoadingBarEnabled = isEnabled;
}

void LOAD_Start(int file_number)//602AC, 60DEC(<)
{
#ifdef PSX
	//jal sub_6B144 //DrawSync(0);
	//jal sub_6A1FC //VSync(0);
	//jal sub_5F1C8 //GPU_UseOrderingTables(dword_AD920);
#endif

	db.draw[0].isbg = 0;
	db.draw[1].isbg = 0;
	db.draw[0].dtd = 0;
	db.draw[1].dtd = 0;

#ifdef PSX
	//jal sub_6B440 //PutDispEnv(&db.draw[0]);
#endif

	//?
	dword_A5EE0 = 0;

	char* gfx = game_malloc(LOADING_SCREEN_IMG_SIZE + LOADING_DISC_IMG_SIZE);
	if (dword_A33F6 == 0)
	{
		assert(0);
	}

	int fileSize = GAMEWAD_InitialiseFileEntry(UNKNOWN_41 + Gameflow->Language);

	GAMEWAD_Load(fileSize, gfx);
	GAMEWAD_InitialiseFileEntry(UNKNOWN_00);

	//Why?
	unsigned long* tmpptr = (unsigned long*) gfx;
	for (int i = 0; i < LOADING_SCREEN_IMG_SIZE / sizeof(unsigned long); i++)
	{
		tmpptr[i] |= (SHRT_MAX + 1) << 16 | (SHRT_MAX + 1);
	}

#ifdef PSX
	//jal sub_6B1C4 //StoreImage(); //frame buffer (gfx, LOADING_SCREEN_IMG_SIZE)
	//jal sub_6B144 //DrawSync();
#endif

	unsigned short* cdgfx = (unsigned short*)(gfx + LOADING_SCREEN_IMG_SIZE);
	unsigned short* gfx2 = (unsigned short*)gfx;
	
	//Why?
	for (int x = 0; x < LOADING_DISC_IMG_WIDTH; x++, gfx2 += ((LOADING_SCREEN_IMG_WIDTH + LOADING_DISC_IMG_WIDTH + 60) / 2))
	{
		for (int y = 0; y < LOADING_DISC_IMG_HEIGHT; y++, cdgfx++, gfx2++)
		{
			unsigned short dat = *cdgfx;

			if (dat == 0)
			{
				dat = (SHRT_MAX + 1);
			}

			if (dat == 0xFC1F)
			{
				*gfx2 = 0;
			}
		}
	}

	dump_game_malloc();

	int a0 = 0xA5FD0;//pScreenDimensions {shrt unk, shrt h, shrt w}
	//jal sub_6B1C4 //StoreImage(s2); frame buffer
	//sub_6B144 //DrawSync(0);

	game_free(LOADING_SCREEN_IMG_SIZE + LOADING_DISC_IMG_SIZE);

	LOAD_DrawEnable(1);

	dword_A33F5 = 1;
}

void LOAD_Stop()//60434, 60FB4
{
	LOAD_DrawEnable(0);

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