#include "CD.H"

#include "FILE.H"
#include "GAMEWAD.H"
#include "SPECIFIC.H"

#include <stdio.h>
#include <assert.h>

//Number of XA files on disc (XA1-17.XA)
#define NUM_XA_FILES 17

#ifdef PSX
	#define XA_FILE_NAME "\XA%d.XA;1"
#else
	#define XA_FILE_NAME "XA%d.XA"
#endif

unsigned short XATrackClip[136];
short XAFadeRate;
int current_cd_mode;
int XACurPos;
int XAEndPos;
short XAVolume;
short XAReqVolume;
short XAMasterVolume;
short XATrack;
short XAReqTrack;
char XAFlag;
char XAWait;
static char XARepeat;
int XAStartPos;
static int XATrackList[17][2];

void /*$ra*/ cbvsync()
{ // line 2, offset 0x5d884
	//int ret; // $a1
	//unsigned char io[8]; // stack offset -16
	{ // line 86, offset 0x5daec
		//int cnt; // $v0
	} // line 93, offset 0x5db20
} // line 120, offset 0x5dc10

void InitNewCDSystem()//5DDE8, 5E264(<)
{
#ifdef PSX
	//jal sub_5E650 //DEL_ChangeCDMode(0);
	//jal sub_662F0 //CdSearchFile(&fp, GAMEWAD_FILENAME);
	//jal sub_6956C //CdControlF();
	//jal sub_69C4C //CdRead();
	//..
	//jal sub_5F6AC //memcpy(&gwHeader, sizeof(GAMEWAD_header);

#else
	FILE* fileHandle = fopen(GAMEWAD_FILENAME, "rb");
	assert(fileHandle);
	fread(&gwHeader, sizeof(GAMEWAD_header), 1, fileHandle);
	fclose(fileHandle);

	//FIXME: CdPosToInt(); returns LBA for GAMEWAD.OBJ on disc.
	gwLba = 24;

#ifdef PSX
	//jal sub_66270 //CdPosToInt();
#endif

	char buf[10];//FIXME
	for (int i = 0; i < NUM_XA_FILES; i++)
	{
		sprintf(buf, XA_FILE_NAME, i + 1);

#ifdef PSX
		//jal sub_662F0 //CdSearchFile(&fp, buf);
#endif
		FILE* fileHandle = fopen(buf, "rb");
		assert(fileHandle);
		fseek(fileHandle, 0, SEEK_END);

		XATrackList[i][0] = -1;//FIXME: This value is returned by CdPosToInt(); register is v0. It returns the LBA of the XA file on disc.
		XATrackList[i][1] = XATrackList[i][0] + ((ftell(fileHandle) + 0x7FF) / CD_SECTOR_SIZE);

		fclose(fileHandle);
	}

	XAFlag = 0;
	XAVolume = 0;
	XAReqTrack = -1;
	XATrack = -1;
#endif

}

//Play audio track
void S_CDPlay(short track, int mode)
{
	//unsigned char param[4];
	S_Warn("[S_CDPlay] - unimplemented!\n");
}

void S_CDStop()
{
	S_Warn("[S_CDStop] - unimplemented!\n");
}