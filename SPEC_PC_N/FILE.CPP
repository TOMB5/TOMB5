#include "FILE.H"
#include "SPECTYPES.H"
#include "SPECIFIC.H"
#include <cstdio>
#include <cstring>
#include "INCLUDE.H"
#include "GAMEFLOW.H"
#include "DRAWPRIMITIVE.H"
#include "HWINSERT.H"
#include "INIT.H"
#include "GLOBAL.H"
#include "CONTROL.H"

short* floor_data;
short* mesh_base;
int AnimFileLen;
char	cd_drive = 0;

int num_pages;
FILE* fp_level;
char* level_data;
char* level_data_orig;

#ifdef __cplusplus
extern "C" {
#endif

#define AllocT(d, s, nlv) d = (s*)game_malloc(sizeof(s) * (n))
#define AllocReadT(d, s, n) AllocT((d), s, (n));OnlyReadT((d), s, (n))
#define OnlyReadT(d, s, n) readBytes((d), sizeof(s) * (n))

#define Alloc(d, s, n) d = (struct s*)game_malloc(sizeof(struct s) * (n))
#define AllocRead(d, s, n) Alloc((d), s, (n));OnlyRead((d), s, (n))
#define OnlyRead(d, s, n) readBytes((d), sizeof(struct s) * (n))

#define AddPtr(p, t, n) p = (t*)((char*)(p) + (ptrdiff_t)(n));

	//#define LogCurPos() Log(2, "current pos: %08x", 0x319af7 + (int)(level_data - level_data_orig))

	inline uint8_t readByte()
	{
		const uint8_t ret = *(uint8_t*)level_data;
		level_data += 1;
		return ret;
	}

	inline uint16_t readWord()
	{
		const uint16_t ret = *(uint16_t*)level_data;
		level_data += 2;
		return ret;
	}

	inline uint32_t readDword()
	{
		const uint32_t ret = *(uint32_t*)level_data;
		level_data += 4;
		return ret;
	}

	inline uint16_t freadWord()
	{
		uint16_t ret;
		fread(&ret, 2, 1, fp_level);
		return ret;
	}

	inline uint32_t freadDword()
	{
		uint32_t ret;
		fread(&ret, 4, 1, fp_level);
		return ret;
	}

	inline void readBytes(void* dst, unsigned int count)
	{
		memcpy(dst, level_data, count);
		level_data += count;
	}

	inline void freadBytes(unsigned int count)
	{
		void* buf = malloc(count);
		fread(buf, 1, count, fp_level);
		free(buf);
	}


	void FreeTextures()
	{
		DX_TRY(App.lpD3DDevice->SetTexture(0, nullptr));
		DX_TRY(App.lpD3D->EvictManagedTextures());

		Unimpl();
	}

	void FreeD3DLights()
	{
		;
	}

	void DXFreeSounds()
	{
		Unimpl();
	}

	void FreeLevel()
	{
		Log(LT_Enter, "FreeLevel");

		// todo meshes

		Log(LT_Info, "Free Textures");
		FreeTextures();

		Log(LT_Info, "Free Lights");
		FreeD3DLights();

		DXFreeSounds();

		malloc_ptr = malloc_buffer;
		malloc_free = malloc_size;
	}

	void MakeCutsceneResident(int r1, int r2, int r3, int r4)
	{
		Unimpl();
	}

	void ClearFX()
	{
		Unimpl();
	}

	void InitMatrix()
	{
		Unimpl();
	}

	void InitWater()
	{
		Unimpl();
	}

	void BuildGlobalFogBulbList()
	{
		Unimpl();
	}

	void RoomInit()
	{
		BuildGlobalFogBulbList();
	}

	void Init()
	{
		InitWater();
		RoomInit();
	}

	void LoadTextures(int room, int obj, int bump)
	{
		Unimpl();
	}
	void LoadRooms()
	{
		Unimpl();
	}
	void LoadObjects()
	{
		Unimpl();
	}
	void LoadSprites()
	{
		Unimpl();
	}
	void LoadCameras()
	{
		Unimpl();
	}
	void LoadSoundEffects()
	{
		Unimpl();
	}
	void LoadBoxes()
	{
		Unimpl();
	}
	void LoadAnimatedTextures()
	{
		Unimpl();
	}
	void LoadTextureInfos()
	{
		Unimpl();
	}

	unsigned __stdcall LoadLevel(char* filename)
	{
		Log(LT_Info, "Begin LoadLevel");

		FreeLevel();

		num_pages = 1;
		//
		fp_level = FileOpen(filename);

		if (fp_level)
		{
			int version = freadDword();
			int numRoomTex = freadWord();
			int numObjTex = freadWord();
			int numBumpTex = freadWord();

			S_InitLoadBar(numObjTex + numBumpTex + numRoomTex + 20);
			S_LoadBar();

			Log(LT_Status, "Process Level Data");
			LoadTextures(numRoomTex, numObjTex, numBumpTex);

			LaraDrawType = freadWord() + 1;
			WeatherType = freadWord();

			freadBytes(28); // padding

			int uncompSize = freadDword();
			int compSize = freadDword();

			level_data = (char*)malloc(uncompSize);
			level_data_orig = level_data;

			fread(level_data, uncompSize, 1, fp_level);

			Log(LT_Info, "Rooms");
			LoadRooms();
			S_LoadBar();

			Log(LT_Info, "Objects");
			LoadObjects();
			S_LoadBar();

			LoadSprites();
			S_LoadBar();

			LoadCameras();
			S_LoadBar();

			LoadSoundEffects();
			S_LoadBar();

			LoadBoxes();
			S_LoadBar();

			LoadAnimatedTextures();
			S_LoadBar();

			LoadTextureInfos();
			S_LoadBar();

			FileClose(fp_level);
			Init();
			InitMatrix();
			ClearFX();
		}

		MakeCutsceneResident(gfResidentCut[0], gfResidentCut[1], gfResidentCut[2], gfResidentCut[3]);
		//
		return true;
	}

	int 		S_LoadLevelFile(int Name)
	{
		Log(LT_Enter, "S_LoadLevelFile");

		// todo

		char filename[80];
		strcpy(filename, &gfFilenameWad[gfFilenameOffset[Name]]);
		//
		strcat(filename, ".TRC");

		for (int i = 0; i < 4; i++)
		{
			BeginScene();
			InitBuckets();
			/*InitialiseSortList();
			DrawLoadingScreen();
			SortPolyList(dword_BA4384, &dword_BA4390);
			RestoreFPCW();
			DrawSortList(word_878654);
			MungeFPCW(&word_878654);*/
			S_DumpScreenFrame();
		}

		// todo thread

		LoadLevel(filename);

		Unimpl();
		return 0;
	}

	FILE* FileOpen(const char *filename)
	{
		FILE* fp;
		char fn[80];

		memset(&fn, 0, 80u);
		fn[0] = 0;
		fn[1] = 0;
		fn[2] = 0;
		strcat(fn, filename);

		Log(5, "FileOpen - %s", fn);

		fp = fopen(fn, "rb");

		if (!fp)
			Log(1, "Unable To Open %s", fn);

		return fp;
	}

	int FileClose(FILE* fp)
	{
		Log(2, "FileClose");

		return fclose(fp);
	}

	unsigned long FileLength(FILE* nHandle)
	{
		unsigned long ret;

		fseek(nHandle, 0, SEEK_END);
		ret = ftell(nHandle);
		fseek(nHandle, 0, SEEK_SET);

		return ret;
	}

	int LoadFile(char* szFileName, void** pDest)
	{
		FILE* fp;
		int len, read;

		Log(2, "LoadFile");
		Log(5, "File - %s", szFileName);

		fp = FileOpen(szFileName);
		if (!fp)
			return 0;

		len = FileLength(fp);

		if (!*pDest)
			*pDest = malloc(len);

		read = fread(*pDest, 1, len, fp);

		Log(5, "Read - %d FileSize - %d", read, len);

		if (read != len)
		{
			Log(1, "Error Reading File");
			FileClose(fp);
			free(*pDest);
			return 0;
		}

		FileClose(fp);
		return len;
	}

	int FindCdDrive(void)
	{
		unsigned int type;
		char root[5];
		char file_check[] = "C:\\script.dat";

		DWORD drives;
		HANDLE file;

		// WIN95: Bit mask of which drives available
		drives = GetLogicalDrives();

		cd_drive = 'A';
		lstrcpy(root, "A:\\");
		while (drives)
		{
			// WIN95: If drive letter exists, check out if it is a CD drive
			if (drives & 1)
			{
				root[0] = cd_drive;

				type = GetDriveType(root);
				if (type == DRIVE_CDROM)
				{
					// NOTE: user may have more than one CD drive, so need to check this has Tomb 2 in it
					file_check[0] = cd_drive;
					file = CreateFile(file_check, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
					if (file != INVALID_HANDLE_VALUE)
					{
						CloseHandle(file);
						return 1;
					}
				}
			}

			// Go on to next drive letter
			cd_drive++;
			drives >>= 1;
		}

		return (0);
	}

#ifdef __cplusplus
}
#endif