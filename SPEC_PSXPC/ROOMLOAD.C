#include "ROOMLOAD.H"

#include "GAMEWAD.H"
#include "GPU.H"
#include "LOAD_LEV.H"
#include "SETUP.H"

#include <assert.h>

#include <stdio.h>
#include <string.h>

long AnimFilePos;
long AnimFileLen;
short* floor_data;
unsigned long* SetupPtr;
unsigned short ClutStartY;
struct SVECTOR* RoomBBoxes;
short* mesh_base;
struct PSXSPRITESTRUCT* GLOBAL_default_sprites_ptr;
struct PSXTEXTI* AnimatingWaterfalls[6];
int AnimatingWaterfallsV[6];
unsigned long envmap_data[6];
unsigned long* RelocPtr[128];

//FIXME (Retail)
int dword_800A5F04 = 0;
int dword_800AD724 = 0;
int dword_800A60D8 = 0;

void S_LoadLevelFile(int Name)//60188, 60D54(<)
{
#ifdef INTERNAL
	char buf[80];
	unsigned long* mod;
	FILE* file;

	int a0 = 0;//FIXME
	int s3 = a0;
	a0 = 0;

	//DrawSync();
	init_game_malloc();
	int s0 = 10;
	//LOAD_Start();//loads loading pic right after script file?
	a0 = s3 + 2;
	int v0 = 10;

	char* s00 = "DATA\\SETUP.MOD";

	unsigned long* s1 = db.poly_buffer[0]; //critical unknown var, probably db, db_struct
	///v0 = s1 + 0x1008;
	//	SetupPtr = v0;//&OurSqrt[968]

	int len = FILE_Length("DATA\\SETUP.MOD");

	char* a00 = s00;
	a00 = s00;
	int a1 = 0;
	int a2 = 0;

#ifdef PSX
	PCOpen();
#else
	file = fopen("DATA\\SETUP.MOD", "rb");
#endif

	///s2 = v0;
	///a0 = s1 + 0x1000;
	a1 = 1;
	///	a2 = s2;
	//	s00 = v0;

	//	FILE_Read();
	///a3 = s00;

#ifdef PSX
	PCclose();
#else
	fclose(file);
#endif

	a0 = s0;
	//a0 = SetupPtr;

	///a1 = s1[0x1000];

	//	RelocateModule();

	a1 = a0;
	s3 <<= 1;

	unsigned short* v00 = gfFilenameOffset;
	char* a11 = gfFilenameWad;

	s3 = v0;

	///v1 = *(unsigned short*)s3;
	///a1 += v1;
	strcpy(buf, a11);


	a1 = 10;

	strcat(buf, ".PSX");

	len = FILE_Load(buf, malloc_ptr);//PSX file

	a1 = 0;

#ifdef PSX
	PCopen();
#else
	file = fopen((const char*)file, buf);
	assert(file);
	fclose(file);
#endif

	a2 = 0;

	///v1 = SetupPtr;

	///a1 = v1[0x14];
	//Appears to execute code within SETUP.mod to serialise the level file?

	RelocateLevel();

	a0 = v0;
	LOAD_Stop();
#else

	int a0 = Name;
	int s0 = a0 + 2;//+2 because first entry is setup.mod and second is cutseq.jiz
	
	//TITLE is the base file entry index for levels, simply as a result, we must add gameflow level id to this.
	GAMEWAD_InitialiseReaderPosition(Name + TITLE);
	
	a0 = 0;
	//jal sub_6B144 //ResetCallback();
	
	init_game_malloc();
	
	a0 = s0;
	LOAD_Start(Name);//FIXME incorRECTTRC ptr returning

	int v0 = 0x000A0000;
	int v1 = 0x000B0000;

	unsigned long* s00 = db.poly_buffer[0];
	int a1 = dword_800AD724;//illegal value
	v0 = s0 + 0x1008;//OurSqrt?
	//SetupPtr = v0;///@FIXME illegal ptr

	//addiu	$a0, $s0, 0x1000 //looks like the ptr?
	
	//FIXME should switch offset 0x6E5
	GAMEWAD_Read(SETUP_MOD_FILE_SIZE, setupBuff); //jal sub_5E414 //Loads setup.mod to ptr 0xB2940
	
	//a0 = SetupPtr;
	//lw	$a1, 0x1000($s0)
	a1 += a0;
	//jal	sub_5F430 RelocateModule(); setup.mod?
	
	//lw	$v0, 0x38C4($gp)
	//lw	$v1, 0x14($v0)
	//jalr	$v1
	RelocateLevel();
	//a0 = s1;

	LOAD_Stop();
#endif
}