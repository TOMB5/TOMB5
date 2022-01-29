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
#include "SOUND.H"
#include "TEXT_S.H"

#if PSXPC_TEST
#include <stdio.h>
#include <string.h>
#elif PSX_VERSION
#include <STDIO.H>
#include <STRING.H>
#endif
#include <LIBMCRD.H>
#include "CONTROL.H"
#include "SOUND.H"

static struct REQUESTER InsertReq = { STR_INSERT_MEMCARD_INTO_SLOT_1, 8, 0, 0, 0, 0, 0, 0, 0,{ 0, 0, 0, 0, 0 } };
static struct REQUESTER CheckingReq = { STR_CHECKING_MEMORY_CARD, 8, 0, 0, 0, 0, 0, 0, 0,{ 0, 0, 0, 0, 0 } };
static struct REQUESTER FormatReq = { STR_MEMCARD_UNFORMATTED_FORMAT_IT, 8, 2, 1, 2, 0, 0, 0, 0,{ STR_YES, STR_NO, 0, 0, 0 } };
static struct REQUESTER OverwriteReq = { STR_OVERWRITE_ON_MEMCARD, 8, 2, 1, 2, 0, 0, 0, 0,{ STR_YES, STR_NO, 0, 0, 0 } };
struct REQUESTER LoadingReq = { STR_LOADING_DATA_DO_NOT_REMOVE, 8, 0, 0, 0, 0, 0, 0, 0,{ 0, 0, 0, 0, 0 } };
static struct REQUESTER SavingReq = { STR_SAVING_DATA_DO_NOT_REMOVE, 8, 0, 0, 0, 0, 0, 0, 0,{ 0, 0, 0, 0, 0 } };
static struct REQUESTER FormattingReq = { STR_FORMATTING_MEMCARD_DO_NOT_REMOVE, 8, 0, 0, 0, 0, 0, 0, 0,{ 0, 0, 0, 0, 0 } };
static struct REQUESTER LoadOkReq = { STR_LOAD_OK, 8, 0, 0, 0, 0, 0, 0, 0,{ 0, 0, 0, 0, 0 } };
static struct REQUESTER LoadErrorReq = { STR_LOAD_FAILED, 8, 0, 0, 0, 0, 0, 0, 0,{ 0, 0, 0, 0, 0 } };
static struct REQUESTER SaveOkReq = { STR_SAVED_OK, 8, 0, 0, 0, 0, 0, 0, 0,{ 0, 0, 0, 0, 0 } };
static struct REQUESTER SaveErrorReq = { STR_SAVE_FAILED, 8, 0, 0, 0, 0, 0, 0, 0,{ 0, 0, 0, 0, 0 } };
static struct REQUESTER FormatErrorReq = { STR_FORMAT_FAILED, 8, 0, 0, 0, 0, 0, 0, 0,{ 0, 0, 0, 0, 0 } };
static struct REQUESTER NotFormatReq = { STR_MEMCARD_IS_UNFORMATTED_INSERT_FORMATTED, 8, 0, 0, 0, 0, 0, 0, 0,{ 0, 0, 0, 0, 0 } };
static struct REQUESTER NoSpaceReq = { STR_MEMCARD_INSUFFICIENT_FREE_BLOCKS, 8, 0, 0, 0, 0, 0, 0, 0,{ 0, 0, 0, 0, 0 } };
struct REQUESTER NoGamesReq = { STR_THERE_ARE_NO_SAVEGAMES, 8, 0, 0, 0, 0, 0, 0, 0,{ 0, 0, 0, 0, 0 } };

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
	y = (SCREEN_HEIGHT/2) - (((n << 1) + n) << 2);
	
	if(n >= 1)
	{
		//loc_6279C
		for(i = 0; i < n; i++, y += 24)
		{
			if(i < mcNumFiles)
			{
				pn = (struct PACKEDNAME*)&mcFileNames[i][0];
				sprintf(&buf[0], "%s - %d %s %d:%.2d:%.2d", &gfStringWad[gfStringOffset[gfLevelNames[pn->Level & 0x3F]]], pn->Days & 0x3F, &gfStringWad[gfStringOffset[STR_DAYS]], pn->Hours & 0x3F, pn->Min & 0x3F, pn->Sec & 0x3F);
			}
			else
			{
				//loc_62838
				strcpy(&buf[0], &gfStringWad[gfStringOffset[STR_EMPTY]]);
			}
			
			//loc_62858:
			if(i == cursor)
			{
				PrintString(256, (y + 15), 1, &buf[0], flags);
			}
			else
			{
				PrintString(256, (y + 15), 5, &buf[0], flags);
			}

			//loc_62870:
			DrawF4(0x20, y, 0x1C0, 0x17, 0, 0x2A800000);
			DrawTPage(0, 0);
			
			DrawLineH(0x22, (y + 1), 0x1BC, 0, 0x404040, 0);
			DrawLineH(0x22, (y + 21), 0x1BC, 0, 0x404040, 0);
			
			DrawLineV(0x22, (y + 1), 0x15, 0, 0x404040, 0);
			DrawLineV(0x1DD, (y + 1), 0x15, 0, 0x404040, 0);

			DrawTPage(0, 1);
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
			PrintString(SCREEN_WIDTH / 2, 32, 8, &gfStringWad[gfStringOffset[STR_SELECT_GAME_TO_LOAD]], FF_CENTER);
			nfiles = DisplayFiles(cursor, mcNumFiles);

			if ((RawEdge & IN_DPAD_UP) && cursor != 0)
			{
				SoundEffect(SFX_MENU_SELECT, 0, 2);
				--cursor;
			}
			//loc_62B9C
			else if ((RawEdge & IN_DPAD_DOWN) && cursor < nfiles - 1)
			{
				SoundEffect(SFX_MENU_SELECT, 0, 2);
				++cursor;
			}
			//loc_62BEC
			else if ((RawEdge & IN_CROSS))
			{
				SoundEffect(SFX_MENU_CHOOSE, 0, 2);
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
			if (AutoFunc == 255)
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
		PrintString(SCREEN_WIDTH / 2, 232, 5, &gfStringWad[gfStringOffset[STR_CANCEL]], FF_CENTER);
		if ((RawEdge & IN_TRIANGLE))
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
	unsigned char cancel; // $s2
	unsigned char stat; // $s0
	int ret; // $s3
	static int cursor; // offset 0xc
	static unsigned char init; // 0x198E($gp) A1F42
	static struct PACKEDNAME pn; // offset 0x10
	static unsigned char func; //0x198F($gp) A1F43
	//{ // line 14, offset 0x62e68
		int seconds; // $s0
	//} // line 41, offset 0x62ff4
	//{ // line 51, offset 0x63034
		int i; // $a1
		int nfiles; // $a1
		long cmd; // stack offset -32
		long result; // stack offset -28
		static unsigned char AutoTime; // offset 0x24
		static unsigned char AutoFunc; // offset 0x25
		static struct REQUESTER *AutoRequester; // offset 0x28
		//{ // line 151, offset 0x63268
			char slots[7]; // stack offset -40
			struct PACKEDNAME *p; // $v0
		//} // line 175, offset 0x63340
		//{ // line 354, offset 0x63568
			//int i; // $v1
		//} // line 358, offset 0x63598
	//} // line 393, offset 0x63690

	cancel = 1;
	ret = 0;

	if (init == 0)
	{
		//v0 = GameTimer
		//v1 = 0x88888889
		//a0 = mcInit
		seconds = GameTimer / 30;
		if (mcInit != 0)
		{
			mcClose();
		}
		//loc_62E98
		mcOpen(0);

		//a0 = &pn
		//v1 = gfStringOffset
		//a1 = gfStringWad
		func = 4;
		init = 1;
		//v0 = gfStringOffset[STR_CHECKING_MEMORY_CARD]
		//a2 = 0xC
		cursor = 0;
		//strncpy(&pn[0], &gfStringWad[gfStringOffset[STR_CHECKING_MEMORY_CARD]], 12);

		/*DAT_000a5528 = 0x4040;
		DAT_000a552b = 0;
		DAT_000a552a = gfCurrentLevel | 0x40;
		cVar2 = (char)((int)uVar12 / 0x3c);
		DAT_000a5527 = (char)uVar12 + cVar2 * -0x3c | 0x40;
		DAT_000a5524 = (char)((int)uVar12 / 0x15180) + (char)(((int)uVar12 / 0x15180) / 0x3e) * -0x3e |
			0x40;
		DAT_000a5525 = (byte)(((int)uVar12 % 0x15180) / 0xe10) | 0x40;
		DAT_000a5526 = cVar2 + (char)(((int)uVar12 / 0x3c) / 0x3c) * -0x3c | 0x40;*/



	}
	//loc_62FF4
	reset_count = 0;

	stat = mcGetStatus();

	switch (func)
	{
	case 0:
	{
		AutoRequester = &InsertReq;

		if (mcNumFiles == 0 && mcBlocksFree < 2)
		{
			Requester(&NoSpaceReq);
		}
		//loc_63168
		PrintString(0x100, 0x20, 8, &gfStringWad[gfStringOffset[STR_SELECT_GAME_TO_SAVE]], 0x8000);
		nfiles = DisplayFiles(cursor, 7);

		if ((RawEdge & IN_DPAD_UP) && cursor != 0)
		{
			SoundEffect(SFX_MENU_SELECT, NULL, 2);
			cursor--;
			break;
		}//loc_631EC
		else if ((RawEdge & IN_DPAD_DOWN) && cursor < nfiles - 1)
		{
			SoundEffect(SFX_MENU_CHOOSE, NULL, 2);
			cursor++;
		}
		else if ((RawEdge & IN_CROSS))
		{
			//loc_6323C
			SoundEffect(SFX_MENU_CHOOSE, NULL, 2);

			if (mcNumFiles != 0)
			{
				//loc_63274
				for (i = 0; i < 6; i++)
				{
					slots[0] = 0;
				}

				//a1 = 0
				if (mcNumFiles != 0)
				{
					//t0 = t1
					p = (struct PACKEDNAME*) & mcFileNames[0];
					//a2 = v0 + 0x10

					//loc_632A8
					do
					{
						p++;
						i++;
						slots[p->Slot & 0x3F]++;
					} while (i < mcNumFiles);
				}
				//loc_632D0

				if (slots[cursor] >= 2 || cursor >= mcNumFiles)
				{
					do
					{
						//v0 = mcNumFiles;
						//v0 = cursor < mcNumFiles ? 1 : 0
						//v0 = slots[0];
						//a0 = &slots[0]

						if (i >= 7)
						{

						}

					} while (i++ < 7);
				}//loc_63340
			}//loc_63340

			//v0 = cursor
			//a0 = mcNumFiles
			//v1 = a1 | 0x4040
			pn.Slot = i | 0x4040;
			if (cursor < mcNumFiles)
			{
				func = 8;
			}

		}//loc_63048

		break;
	}
	case 4:
	{
		AutoRequester = &InsertReq;

		if (func == 4)
		{
			Requester(&CheckingReq);
		}

		//loc_630A4
		func = stat;
		cursor = 0;
		FormatReq.CursorPos = 1;
		OverwriteReq.CursorPos = 1;
		break;
	}
	case 7:
	{
		Requester(AutoRequester);

		if (AutoTime == 0)
		{
			if (AutoFunc != 255)
			{
				func = AutoFunc;
				cancel = 0;
			}
			else
			{
				ret = 1;
				cancel = 0;
			}
		}
		else
		{
			//loc_6343C
			AutoTime--;
			cancel = 0;
		}
		break;
	}
	case 8:
	{
		if (stat == 0)
		{
			result = Requester(&OverwriteReq);
			if (result != 0)
			{
				if (result == 0x8000)
				{
					func = 7;
					AutoRequester = &SavingReq;
					AutoTime = 3;
					AutoFunc = 12;
					cancel = 0;
					break;
				}
				else
				{
					//loc_6348C
					ret = -1;
				}
			}
			//loc_6368C
			cancel = 0;
			break;
		}
		//loc_63070
		func = stat;
		cancel = 0;
		break;
	}
	case 12:
	{
		//v0 = &SaveErrorReq
		AutoRequester = &SaveErrorReq;
#if 0
lhu     $v0, 0x4F74($gp)
li      $v1, 0x3C
sb      $v1, 0x4F78($gp)
li      $v1, 3
sb      $v1, 0x198F($gp)
andi    $v0, 0x3F
beqz    $v0, loc_63568
lui     $a0, 9
move    $s4, $a0
addiu   $s1, $sp, 0x40+var_20
addiu   $s0, $sp, 0x40+var_1C
la      $a0, dword_95014
li      $a1, 0x81
li      $v0, 0x69
li      $v1, 0x82
sb      $a1, (byte_95034 - 0x95014)($a0)
sb      $v0, (byte_95035 - 0x95014)($a0)
sb      $v1, (byte_95036 - 0x95014)($a0)
sb      $a1, (byte_95038 - 0x95014)($a0)
lbu     $v0, 0x4F74($gp)
li      $v1, 0x6A
sb      $v1, (byte_95039 - 0x95014)($a0)
andi    $v0, 0x3F
addiu   $v0, 0x4F
j       loc_63598
sb      $v0, (byte_95037 - 0x95014)($a0)

loc_63568:
li      $v1, 0x1C
lui     $s4, 9
addiu   $s1, $sp, 0x40+var_20
addiu   $s0, $sp, 0x40+var_1C
lui     $v0, 9
addiu   $a0, $v0, (dword_95018 - 0x90000)
addu    $v0, $v1, $a0

loc_63584:
sb      $zero, 0($v0)
addiu   $v1, 1
slti    $v0, $v1, 0x22
bnez    $v0, loc_63584
addu    $v0, $v1, $a0

loc_63598:
move    $a0, $zero
move    $a1, $s1
jal     sub_6B2FC
move    $a2, $s0
lw      $v1, 0x4F60($gp)
lw      $v0, dword_800A4794
nop
sltu    $v0, $v1, $v0
beqz    $v0, loc_635E8
move    $a0, $zero
sll     $a1, $v1, 2
addu    $a1, $v1
sll     $a1, 2
li      $v0, 0xA4798
jal     sub_6C000
addu    $a1, $v0
bnez    $v0, def_6302C   # jumptable 0006302C default case
nop

loc_635E8:
move    $a0, $zero
addiu   $a1, $gp, 0x4F64
jal     sub_6B418
li      $a2, 2
bnez    $v0, def_6302C   # jumptable 0006302C default case
move    $a0, $zero
addiu   $a1, $gp, 0x4F64
jal     sub_6A9F4
li      $a2, 2
bnez    $v0, def_6302C   # jumptable 0006302C default case
addiu   $a0, $s4, 0x5014
move    $a1, $zero
jal     sub_6AE28
li      $a2, 0x200
beqz    $v0, def_6302C   # jumptable 0006302C default case
li      $a1, 1
lw      $a0, dword_800A3924
jal     sub_5E8E8
li      $a2, 0x2000
jal     sub_55AF8
nop
move    $a0, $zero
move    $a1, $s1
jal     sub_6B2FC
move    $a2, $s0
lw      $v1, 0x40+var_1C($sp)
nop
bnez    $v1, def_6302C   # jumptable 0006302C default case
li      $a1, 0x200
lw      $a0, dword_800A3924
jal     sub_6AE28
li      $a2, 0x1E00
beqz    $v0, def_6302C   # jumptable 0006302C default case
move    $s2, $zero
addiu   $a0, $gp, 0x18AC
jal     sub_63718
nop
li      $v1, 6

loc_63688:
sb      $v1, 0x198F($gp)

loc_6368C:
#endif
		break;
	}
	}

	//def_6302C
	if (cancel != 0)
	{
		PrintString(0x100, 0xE8, 5, &gfStringWad[gfStringOffset[STR_CANCEL]], 0x8000);

		if ((RawEdge & IN_TRIANGLE))
		{
			ret = -1;
		}//loc_636E0
	}

	//loc_636E0
	//v0 = ret
	if (ret != 0)
	{
		mcClose();
		init = 0;
	}

	return ret;
}