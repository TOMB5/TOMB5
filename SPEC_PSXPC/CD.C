#include "CD.H"

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

#ifdef PSX
	#include <sys/types.h>
	#include <LIBCD.H>
	#include <LIBSPU.H>
#endif

void cbvsync()//5D884(<), 5DD00(<)
{
	int ret;//$a1
	unsigned char io[8];//$sp-16
	int cnt;//$v0

	switch (XAFlag - 1)
	{
	case 0:
	{
		if (XAVolume == 0)
		{
			XAFlag++;
		}

		goto dflt;
		break;
	}
	case 1:
	{
		cnt = XATrack = XAReqTrack;
		if (XAReqTrack < 0)
		{
			cnt += 7;
		}

		//loc_5D8F8
		io[0] = 1;
		io[1] = XATrack & 7;

		XAStartPos = XATrackList[cnt][0];
		XAEndPos = XATrackList[cnt][1] + XATrackClip[XAReqTrack];
		XACurPos = XAStartPos;

#ifdef PSX
		CdControlF(0xD, &io);
#endif
		XAFlag++;

		//loc_5D8D8
		goto dflt;

		break;
	}
	case 2:
	{
		//loc_5D980
		XAReplay();
		XAReqVolume = XAMasterVolume;
		XAFlag++;

		goto dflt;

		break;
	}
	case 3:
	{
		//loc_5D9AC
		if (XAVolume == XAMasterVolume)
		{
			XAFlag++;
			XAWait = 60;
		}

		goto dflt;

		break;
	}
	case 4:
	{
		//loc_5D9E0
		if (XAWait == 0)
		{
			XAFlag++;
		}

		XAWait--;

		goto dflt;

		break;
	}
	case 5:
	{
		//loc_5DA18
#ifdef PSX
		VSync(-1);
#endif
		if (XAFlag & 7)
		{
#ifdef PSX
			ret = CdSync(0, &io[0]);
			if (ret == 5)
			{
				XAReplay();
			}
			else if (ret == 2)
			{
				if (XACurPos < XAEndPos)
				{
					//loc_5DAEC
					if (CdLastCom() == 0x11);
					{
						cnt = CdPosToInt(&io[5]);

						if (cnt > 0)
						{
							XACurPos = cnt;
						}

						CdControlF(&io[5], 0);
					}
				}
				else if (XARepeat == 0)
				{
					//loc_5DA84
					if (CurrentAtmosphere == 0)
					{
						CdControlB(9, 0, 0);
						XAFlag = 7;
					}
					else
					{
						//loc_5DAB8
						XAVolume = 0;
						XARepeat = 1;
						XAFlag = ret;
						XAReqTrack = CurrentAtmosphere;
						CDDA_SetVolume(0);
						IsAtmospherePlaying = 1;
					}
				}
				else
				{
					XAReplay();
				}
			}

			goto dflt;
#endif
		}

		break;
	}
	default:

	dflt:
		//def_5D8B8
		if (XAVolume < XAReqVolume)
		{
			XAVolume += XAFadeRate;
			if (XAVolume < XAReqVolume)
			{
				XAVolume = XAReqVolume;
			}//loc_5DB78

			CDDA_SetVolume(XAVolume);
		}
		else
		{
			//loc_5DB94
			if (XAReqVolume < XAVolume)
			{
				XAVolume -= XAFadeRate;
				if (!(XAReqVolume < XAVolume))
				{
					XAVolume = XAReqVolume;
				}

				//loc_5DBEC
				CDDA_SetVolume(XAVolume);

			}//loc_5DC00
		}

		//loc_5DC00
		break;
	}

	//loc_5DC00
	return;
}

void InitNewCDSystem()//5DDE8, 5E264(<)
{
#ifdef PSX
	struct CdlFILE fp;
	int test;
	unsigned char param[8];//FIXME incorrect
	DEL_ChangeCDMode(0);
	
	if (CdSearchFile(&fp, GAMEWAD_FILENAME))
	{
		printf("FOUND:%s\n", GAMEWAD_FILENAME);
	}
	
	CdControlB(CdlSetloc, &param, 0);//6956C
	CdRead(1, &gwHeader, 0x80); //69C4C
	//..
	//jal sub_5F6AC //memcpy(&gwHeader, sizeof(GAMEWAD_header);

	test = 0xDEAD;
	test++;
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

void DEL_ChangeCDMode(int mode)//5DEB0(<), ?
{
	unsigned char param[4];

	if (mode == 0 && current_cd_mode != 0)
	{
		current_cd_mode = 0;
		//param[0] = 0x80;
		//CdControlB(0xE, &param[0], 0);
		//VSync(3);
	}
	else if (mode == 1 && current_cd_mode != mode)
	{
		//loc_5DEF8
		current_cd_mode = mode;
	}
	else if (mode == 2 && current_cd_mode != mode)
	{
		//loc_5DF20
		current_cd_mode = mode;
		//param[0] = 0x80;
		//CdControlB(0xE, &param[0], 0);
		//VSync(3);
	}

	//loc_5DF58
	return;
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

void CDDA_SetMasterVolume(int nVolume)//5DDC4(<), 5E240(<) (F)
{
	XAMasterVolume = nVolume;
	CDDA_SetVolume(nVolume);
}

void CDDA_SetVolume(int nVolume)//5D7FC(<), 5DC78(<) (F)
{
	struct SpuCommonAttr attr;
	
	attr.cd.volume.left = nVolume * 64;
	attr.cd.volume.right = nVolume * 64;

#ifdef PSX
	attr.mask = SPU_COMMON_CDVOLL | SPU_COMMON_CDVOLR | SPU_COMMON_CDMIX;
	attr.cd.mix = SPU_ON;
	SpuSetCommonAttr(&attr);
#endif
}

void XAReplay()//5D838, ?
{
	struct CdlLOC loc;
	S_Warn("[XAReplay] - unimplemented!\n");
}