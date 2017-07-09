#ifndef GAMEWAD_H
#define GAMEWAD_H

#ifdef PSX
	#define GAMEWAD_FILENAME "\\GAMEWAD.OBJ;1"
#else
	#define GAMEWAD_FILENAME "GAMEWAD.OBJ"
#endif

int GAMEWAD_InitialiseFileEntry(int fileID);
void GAMEWAD_Load(int fileSize, char* ptr);

#pragma pack(push, 1)

struct GAMEWAD_entry
{
	int fileOffset;
	int fileSize;
};

struct GAMEWAD_header
{
	struct GAMEWAD_entry entries[64];
};

#pragma pack(pop)

extern struct GAMEWAD_header gwHeader;

extern int gwLba;
extern int dword_A563C;
extern int dword_A5620;

#endif