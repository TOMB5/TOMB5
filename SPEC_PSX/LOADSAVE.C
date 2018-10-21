#include "LOADSAVE.H"

#include "GAMEFLOW.H"
#include "GPU.H"
#include "MEMCARD.H"
#include "MISC.H"
#include "SPECIFIC.H"

#include <stdio.h>
#include <string.h>

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

int LoadGame()//6297C, 63060
{
	UNIMPLEMENTED();
	return 0;
}

int SaveGame()//62E3C, 63520
{
	UNIMPLEMENTED();
	return 0;
}