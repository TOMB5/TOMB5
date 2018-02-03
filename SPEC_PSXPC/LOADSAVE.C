#include "LOADSAVE.H"

#include "DRAWPHAS.H"
#include "FXTRIG.H"
#include "GAMEFLOW.H"
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
	struct PACKEDNAME* pn = (struct PACKEDNAME*)&mcFileNames[0][0];

	if (Gameflow->Language - 1 & 7 < 4)
	{
		flags = 0x9001;
	}
	else
	{
		flags = 0x8000;
	}

	//loc_62E24
	n = mcNumFiles + (mcBlocksFree / 2);
	if (n > maxfiles)
	{
		n = maxfiles;
	}

	//loc_62768
	y = 120 - ((n * 2) + n) * 4;

	//s2 = 0x404040;

	//loc_6279C
	if (n > 0)
	{
		for (i = 0; i < n; i++, pn++, y += 24)
		{
			if (mcNumFiles < 0)
			{
				///@FIXME I have no idea what's going on here!!
				//a1 = BASLUS-01311@@@[]@@A so how on earth is sprintf working?

				//a1 = 0xA1F28//? - this points to SLUS string, confusing looks like static arr.
				//a3 = pn->Days & 0x3F;
				//t1 = gfStringOffset;
				//a2 = gfStringWad;
				//a2 = ;
				//v0 = &gfStringWad[gfStringOffset[STR_SECRETS_NUM]];
				//v1 = pn->Hours & 0x3F;
				//v0 = pn->Min & 0x3F;
				//v1 = pn->Sec & 0x3F;
				//sprintf(&buf[0], "" &gfStringWad[gfStringOffset[gfLevelNames[pn->Level & 0x3F]]], pn->Days & 0x3F, pn->Hours & 0x3F, pn->Min & 0x3F, pn->Sec & 0x3F);
			}
			else
			{
				//loc_62838
				strcpy(&buf[0], &gfStringWad[gfStringOffset[STR_RESUME]]);
			}

			//flags on stack_88
			if (i == cursor)
			{
				//loc_62870
				PrintString(256, (y + 15) & 0xFFFF, 1, &buf[0], 0);
			}
			else
			{
				PrintString(256, (y + 15) & 0xFFFF, 5, &buf[0], 0);
			}

			//DrawF4(32, y & 0xFFFF, 448, 23);
			/*DrawTPage(0, 0);
			DrawLineH(34, (y + 1) & 0xFFFF, 444, 0);
			DrawLineH(34, (y + 21) & 0xFFFF, 444, 0);
			DrawLineV(34, (y + 1) & 0xFFFF, 21, 0);
			DrawLineV(477, (y + 1) & 0xFFFF, 21, 0);
			DrawTPage(0, 1);*/
		}
	}

	return n;
}

int LoadGame()//6297C, 63060
{
	S_Warn("[LoadGame] - Unimplemented!\n");
	return 0;
}

int SaveGame()//62E3C, 63520
{
	S_Warn("[SaveGame] - Unimplemented!\n");
	return 0;
}