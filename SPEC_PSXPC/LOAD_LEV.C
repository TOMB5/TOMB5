#include "LOAD_LEV.H"

#include "GAMEWAD.H"
#include "GAMEFLOW.H"
#include "GPU.H"
#include "MALLOC.H"

#include <stddef.h>
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
struct STASHEDOBJ* cur_stashed_object;
struct STASHEDDAT* cur_stashed_matrix;
int num_objects_stashed;
struct STASHEDOBJ stashed_objects_list[128];
struct STASHEDDAT stashed_matrix_list[240];
unsigned char char_anim;
unsigned char OurSqrt[1024];
struct WATERTAB WaterTable[22][64];
struct MATRIX3D* Matrix;
unsigned short SqrtTable[210];
unsigned short ScalarTable[198];
struct MATRIX3D iMatrixStack[32];
struct SVECTOR CamRot;
struct MATRIX3D* iMatrix;
unsigned short MatrixSP;
struct MATRIX3D MatrixStack[32];
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

void LOAD_VSyncHandler()//5F074(<), 5FD54(<)
{
	int a0, a1, a2;
	if (LtLoadingBarEnabled != 0)
	{
		//loc_5F08C
		GPU_BeginScene();

		a0 = 0x1B8;
		a1 = 0xC8;
		a2 = 0x40;

		if (_first_time_ever)
		{
			a0 += 0x18;
			a1 += 8;
			a2 = 0x30;
		}

		//loc_5F0B4
		//draw_rotate_sprite(a0, a1, a2);
		db.current_buffer ^= 1;
		GnLastFrameCount = 0;
		//DrawOTagEnv(&db.ot[db.nOTSize - 1], &db.draw[0]);
	}

	return;
}

void LOAD_DrawEnable(unsigned char isEnabled)//5F2C8, 5FFA8
{
	LtLoadingBarEnabled = isEnabled;
}

void LOAD_Start(int file_number)//602AC, 60DEC(<)
{
	unsigned long* tmpptr = NULL;
	char* gfx = NULL;
	unsigned short* cdgfx = NULL;
	unsigned short* gfx2 = NULL;
	int fileSize, x, y, i;
	unsigned short dat;

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

	//We're going to allocate enough memory for the loading screen background picture and loading disc image
	//The result pointer is later used as the base to read the loading screen/disc bitmap from GAMEWAD.OBJ on disk.
	gfx = game_malloc(LOADING_SCREEN_IMG_SIZE + LOADING_CD_IMG_SIZE);
	if (dword_A33F6 == 0)
	{
		//assert(0);
	}

	//UNKNOWN_41 is the first loading screen image, simply add Gameflow->Language to the base to load language specific load screens.
	fileSize = GAMEWAD_InitialiseReaderPosition(UNKNOWN_41 + Gameflow->Language);

	//Request the loading screen/disc bitmaps to be read into gfx ptr.
	//We don't actually pass the file ID or offset since this is already cached by the previous GAMEWAD_InitialiseFileEntry call.
	GAMEWAD_Read(fileSize, gfx);

	//TITLE is the base file entry index for levels, simply as a result, we must add gameflow level id to this.
	GAMEWAD_InitialiseReaderPosition(file_number + TITLE);

	//We will skip past the loading screen and disc image data so on the next read call we're ready to read SETUP.MOD
	GAMEWAD_Seek(LOADING_SCREEN_IMG_SIZE + LOADING_CD_IMG_SIZE);

	//Why?
	tmpptr = (unsigned long*) gfx;
	for (i = 0; i < LOADING_SCREEN_IMG_SIZE / sizeof(unsigned long); i++)
	{
		tmpptr[i] |= (SHRT_MAX + 1) << 16 | (SHRT_MAX + 1);
	}

#ifdef PSX
	//jal sub_6B1C4 //StoreImage(); //frame buffer (gfx, LOADING_SCREEN_IMG_SIZE)
	//jal sub_6B144 //DrawSync();
#endif

	cdgfx = (unsigned short*)(gfx + LOADING_SCREEN_IMG_SIZE);
	gfx2 = (unsigned short*)gfx;

	//Why?
	for (x = 0; x < LOADING_CD_IMG_WIDTH; x++, gfx2 += (LOADING_SCREEN_IMG_WIDTH + LOADING_CD_IMG_WIDTH + 60) / sizeof(unsigned short))
	{
		for (y = 0; y < LOADING_CD_IMG_HEIGHT; y++, cdgfx++, gfx2++)
		{
			dat = *cdgfx;

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

	//int a0 = 0xA5FD0;//pScreenDimensions {shrt unk, shrt h, shrt w}
	//jal sub_6B1C4 //StoreImage(s2); frame buffer
	//sub_6B144 //DrawSync(0);

	game_free(LOADING_SCREEN_IMG_SIZE + LOADING_CD_IMG_SIZE);

	LOAD_DrawEnable(1);

	dword_A33F5 = 1;
}

void LOAD_Stop()//60434, 60FB4
{
	LOAD_DrawEnable(0);

	db.draw[1].isbg = 1;
	db.draw[0].isbg = 1;

	db.draw[1].dtd = 1;

#if 0//def PSX
	GPU_UseOrderingTables();
#endif

	//FIXME: v1 (1) May be changed in GPU_UseOrderingTables, must clarify
	db.draw[0].dtd = 1;

#ifdef PSX
	GPU_SyncBothScreens();//5F374, 60054
#endif

	db.current_buffer = 0;
	db.current_buffer = 1;

#ifdef INTERNAL
	ProfileDraw = 1;
#endif

	_first_time_ever = 0;
}
