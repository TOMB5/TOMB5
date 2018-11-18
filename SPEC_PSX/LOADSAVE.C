#include "LOADSAVE.H"

#include "CD.H"
#include "EFFECTS.H"
#include "FXTRIG.H"
#include "GAMEFLOW.H"
#include "GPU.H"
#include "MEMCARD.H"
#include "MISC.H"
#include "PSXINPUT.H"
#include "REQUEST.H"
#include "SAVEGAME.H"
#include "SPECIFIC.H"

#include <STDIO.h>
#include <STRING.h>
#include <LIBMCRD.H>

static struct REQUESTER InsertReq;
static struct REQUESTER CheckingReq;
static struct REQUESTER FormatReq;
static struct REQUESTER OverwriteReq;
static struct REQUESTER LoadingReq;
static struct REQUESTER SavingReq;
static struct REQUESTER FormattingReq;
static struct REQUESTER LoadOkReq;
static struct REQUESTER LoadErrorReq;
static struct REQUESTER SaveOkReq;
static struct REQUESTER SaveErrorReq;
static struct REQUESTER FormatErrorReq;
static struct REQUESTER NotFormatReq;
static struct REQUESTER NoSpaceReq;
static struct REQUESTER NoGamesReq;

int DisplayFiles(int cursor, int maxfiles)//626E4(<), 62DC8(<)
{
	int i;
	int n;
	int y;
	unsigned short flags;
    char buf[80];
	struct PACKEDNAME* pn;
	
	if(Gameflow->Language - 1 < 4)
	{
		flags = 0x9001;
	}
	else
	{
		flags = 0x8000;
	}

	//loc_62740:
	if(mcNumFiles + (mcBlocksFree >> 1) < maxfiles)
	{
		n = mcNumFiles + (mcBlocksFree >> 1);
	}
	else
	{
		n = maxfiles;
	}
	
	//loc_62768:
	y = (SCREEN_HEIGHT/2) - ((n << 1) + n) << 2;
	
	if(n > 1)
	{
		//loc_6279C
		for(i = 0; i < n; i++, y += 24)
		{
			if(i < mcNumFiles)
			{
				pn = (struct PACKEDNAME*)&mcFileNames[0][i];
				sprintf(&buf, "%s - %d %s %d:%.2d:%.2d", &gfStringWad[gfStringOffset[gfLevelNames[pn->Level & 0x3F]]], pn->Days & 0x3F, &gfStringWad[gfStringOffset[0xB9]], pn->Hours & 0x3F, pn->Min & 0x3F, pn->Sec & 0x3F);
			}
			else
			{
				//loc_62838
				strcpy(&buf, &gfStringWad[gfStringOffset[0xDC]]);
			}
			
			//loc_62858:
			if(i == cursor)
			{
				PrintString(256, (y & 0xF) & 0xFFFF, 5, &buf, flags);
			}
			else
			{
				PrintString(256, (y & 0xF) & 0xFFFF, 1, &buf, flags);
			}

			//loc_62870:
			DrawF4(0x20, y & 0xFFFF, 0x1C0, 0x17, 0, 0x2A80);
			/*DrawTPage(0, 0);
			
			DrawLineH(0x22, (y + 1) & 0xFFFF, 0x1BC, 0, 0x404040, 0);
			DrawLineH(0x22, (y + 15) & 0xFFFF, 0x1BC, 0, 0x404040, 0);
			
			DrawLineV(0x22, (y + 1) & 0xFFFF, 0x15, 0, 0x404040, 0);
			DrawLineV(0x1DD, (y + 1) & 0xFFFF, 0x15, 0, 0x404040, 0);

			DrawTPage(0, 1);*/
		}
	}
	
	//loc_62948
	return n;
}

int LoadGame()//6297C(<), 63060
{
	unsigned char stat;
	int ret;
	unsigned char cancel;
	static int cursor;
	static unsigned char init; // offset 0x144
	static unsigned char func; // offset 0x145
	long cmd;
	long result;
	static unsigned char AutoTime;
	static unsigned char AutoFunc;
	static struct REQUESTER* AutoRequester;
	int nfiles;

	ret = 0;
	cancel = 1;

	if (PadConnected == 0)
	{
		mcClose();
		init = 0;
		return 0;
	}

	//loc_629BC
	if (init == 0)
	{
		if (mcInit != 0)
		{
			mcClose();
		}
		//loc_629E8
		mcOpen(0);
		func = 4;
		cursor = 0;
		init = cancel;
	}
	//loc_62A00
	reset_count = 0;
	stat = mcGetStatus();

	switch (func)
	{
	case 0:
		//loc_62AE0:
		AutoRequester = &InsertReq;
		func = stat;

		if (mcNumFiles == 0)
		{
			Requester(&NoGamesReq);
		}
		else
		{
			//loc_62B10
			PrintString(SCREEN_WIDTH / 2, 0x20, 8, &gfStringWad[gfStringOffset[STR_SELECT_GAME_TO_LOAD]], 0x8000);
			nfiles = DisplayFiles(cursor, mcNumFiles);

			if ((RawEdge & 0x10) && cursor != 0)
			{
				SoundEffect(0x6D, 0, 2);
				--cursor;
			}
			//loc_62B9C
			else if ((RawEdge & 0x40) && cursor < nfiles - 1)
			{
				SoundEffect(0x6D, 0, 2);
				++cursor;
			}
			//loc_62BEC
			else if ((RawEdge & 0x4000))
			{
				SoundEffect(0x6F, 0, 2);
				func = 7;
				AutoRequester = &LoadingReq;
				AutoTime = 3;
				AutoFunc = 0xB;
				cancel = 0;
			}
		}
		break;
	case 1:
		//loc_62A40
		Requester(&InsertReq);
		AutoRequester = &InsertReq;
		func = stat;
		break;
	case 2:
		//loc_62AC8
		Requester(&NotFormatReq);
		func = stat;
		break;
	case 3:
		//loc_62A60
		Requester(AutoRequester);

		if (AutoTime == 0)
		{
			func = stat;
			cancel = 0;
		}
		else
		{
			//loc_62A88
			--AutoTime;
			cancel = 0;
		}
		break;
	case 4:
		//loc_62A94
		AutoRequester = &InsertReq;
		if (func == 4)
		{
			Requester(&CheckingReq);
		}
		//loc_62AB8
		func = stat;
		cursor = 0;
		break;
	case 5:
	case 6:
	case 8:
	case 9:
	case 10:
		///@TODO loc_62dc0
		break;
	case 7:
		//loc_62C2C
		Requester(AutoRequester);

		if (AutoTime == 0)
		{
			if (AutoFunc == -1)
			{
				ret = 1;
				//loc_62DBC
				cancel = 0;
			}
			else
			{
				//loc_62C60
				func = AutoFunc;
				cancel = 0;
			}
		}
		else
		{
			//loc_62C6C
			--AutoTime;
			cancel = 0;
		}
		break;
	case 11:
		//loc_62C78:
		AutoRequester = &LoadErrorReq;
		AutoTime = 60;
		func = 3;

		if (mcFileLengths[cursor] != 0)
		{
			MemCardSync(0, &cmd, &result);
			if (MemCardOpen(0, &mcFileNames[cursor][0], 1) == 0)
			{
				S_MemSet(MGSaveGamePtr, 0, 0x2000);
				if (MemCardReadData((unsigned long*)MGSaveGamePtr, 0x200, 0x1E00) != 0)
				{
					MemCardSync(0, &cmd, &result);

					if (result == 0)
					{
						if (CheckSumValid(MGSaveGamePtr) != 0)
						{
							memcpy(&savegame, MGSaveGamePtr, sizeof(struct savegame_info));
							GPU_SetScreenPosition(savegame.ScreenX, savegame.ScreenY);
							CDDA_SetMasterVolume(savegame.VolumeCD);

							AutoRequester = &LoadOkReq;
							AutoFunc = -1;
							AutoTime = 30;
							func = 7;
							SoundFXVolume = savegame.VolumeFX;
						}//loc_62DB4
					}//loc_62DB4

					MemCardClose();
					cancel = 0;
				}//def_62A38
			}//def_62A38
		}//def_62A38 end
		break;
	case 12:
		///@TODO loc_63124?
		break;
	}

	//def_62A38
	if (cancel != 0)
	{
		PrintString(SCREEN_WIDTH / 2, 0xE8, 5, &gfStringWad[gfStringOffset[STR_CANCEL]], 0x8000);
		if ((RawEdge & 0x1000))
		{
			init = 0;
			ret = -1;
		}
	}
	//loc_62E14
	if (ret != 0)
	{
		init = 0;
		return ret;
	}//loc_62E20

	return 0;
}

int SaveGame()//62E3C, 63520
{
	UNIMPLEMENTED();
	return 0;
}