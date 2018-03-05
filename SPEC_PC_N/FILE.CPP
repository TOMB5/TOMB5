#include "SPECTYPES.H"
#include "SPECIFIC.H"
#include <cstdio>
#include <cstring>
#include "INCLUDE.H"

short* floor_data;
short* mesh_base;
int AnimFileLen;
char	cd_drive = 0;

#ifdef __cplusplus
extern "C" {
#endif

	int 		S_LoadLevelFile(int Name)
	{
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