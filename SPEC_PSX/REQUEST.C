#include "REQUEST.H"

#include "EFFECTS.H"
#include "FXTRIG.H"
#include "GAMEFLOW.H"
#include "MISC.H"
#include "SAVEGAME.H"
#include "SPECIFIC.H"
#include "PSXINPUT.H"
#include "TEXT_S.H"

long Requester(struct REQUESTER* r)//63718(<), 63DF4 (F)
{
	int x;
	int y;
	short top;
	unsigned short w;
	unsigned short h;
	int i;
	int optiony;
	unsigned short rx;
	unsigned short ry;
	unsigned short rw;
	unsigned short rh;
	short OptionTop[5];
	short OptionBottom[5];
	int val;

	GetStringDimensions(&gfStringWad[gfStringOffset[r->TitleTxt]], &w, &h);
	optiony = h + 4;
	if (r->nOptions != 0)
	{
		h += 2;

		if (r->nOptions != 0)
		{
			//loc_637B0
			for (i = 0; i < r->nOptions; i++)
			{
				GetStringLength(&gfStringWad[gfStringOffset[r->OptionTxt[i]]], &OptionTop[i], &OptionBottom[i]);
				GetStringDimensions(&gfStringWad[gfStringOffset[r->OptionTxt[i]]], &rw, &rh);

				if (i == 0 && r->Ignore != 0)
				{
					OptionBottom[0] = OptionTop[0] + rh;
				}
				//loc_63858
				if (w < rw)
				{
					w = rw;
				}
			}
		}//loc_6389C
	}
	//loc_6389C

	y = 120 - (h >> 1);
	rw = w + 32;
	x = 256 - (w >> 1);
	rh = h + 16;
	rx = (x - 16) & 0xFFFF;
	ry = (y - 8) & 0xFFFF;

	GetStringLength(&gfStringWad[gfStringOffset[r->TitleTxt]], &top, NULL);
	PrintString(256, ((y - top) + 2) & 0xFFFF, r->TitleCol, &gfStringWad[gfStringOffset[r->TitleTxt]], 0x8000);

	if (r->nOptions != 0)
	{
		DrawLineH(x & 0xFFFF, ((y + optiony) - 4) & 0xFFFF, w, 1, 0, 0xC0C0C0);
		DrawTPage(0, 1);

		y += optiony - OptionTop[0];
		if (r->nOptions != 0)
		{
			//loc_639D8
			for (i = 0; i < r->nOptions; i++)
			{
				if (i == 0 && r->Ignore != 0)
				{
					DisplayConfig(x, y);
				}
				else
				{
					//loc_63A08
					if ((r->JustifyL >> h) & 1)
					{
						if (i != r->CursorPos)
						{
							PrintString(x & 0xFFFF, y & 0xFFFF, r->OptionCol, &gfStringWad[gfStringOffset[r->OptionTxt[i]]], 0);
						}//loc_63A34
						else
						{
							PrintString(x & 0xFFFF, y & 0xFFFF, 1, &gfStringWad[gfStringOffset[r->OptionTxt[i]]], 0);
						}
					}
					else
					{
						//loc_63A78
						if ((r->JustifyR >> i) & 1)
						{
							if (i != 0)
							{
								val = savegame.VolumeCD;
							}
							else
							{
								val = savegame.VolumeFX;
							}

							//loc_63AA8
							if (i == r->CursorPos)
							{
								PrintString(((rw + x) - 32) & 0xFFFF, y & 0xFFFF, 1, &gfStringWad[gfStringOffset[r->OptionTxt[i]]], 0x4000);
							}
							else
							{
								//loc_63AD0
								PrintString(((rw + x) - 32) & 0xFFFF, y & 0xFFFF, r->OptionCol, &gfStringWad[gfStringOffset[r->OptionTxt[i]]], 0x4000);
							}

							PrintGauge(((rw + x) - 140) & 0xFFFF, (y - 7) & 0xFFFF, val);
						}
						else
						{
							//loc_63B30
							if (i == r->CursorPos)
							{
								PrintString(0x100, y & 0xFFFF, 1, &gfStringWad[gfStringOffset[r->OptionTxt[i]]], 0x8000);
							}
							else
							{
								PrintString(0x100, y & 0xFFFF, r->OptionCol, &gfStringWad[gfStringOffset[r->OptionTxt[i]]], 0x8000);
							}
						}
					}
				}
				//loc_63B88
				if (i == r->CursorPos)
				{
					if ((r->Arrows >> i) & 1)
					{
						PrintString((rx - 4) & 0xFFFF, y & 0xFFFF, 2, "\x00000019", 0);
						PrintString(((rx + rw) - 8) & 0xFFFF, y & 0xFFFF, 1, "\x0000001B", 0);
					}//loc_63C04
				}//loc_63C04

				if (i < (r->nOptions - 1))
				{
					//v0 = i << 1;
#if 0///@FIXME sp
					sll     $v0, $s1, 1
					addu    $a1, $sp, $v0
					sll     $v1, $a2, 1
					addu    $a0, $sp, $v1
					lh      $v0, 0x28($a1)
					lh      $v1, 0x18($a0)
					addiu   $a1, $s2, 2
					subu    $v0, $v1
					addu    $s2, $a1, $v0
#endif
				}//loc_63C48
			}
		}//loc_63C58
	}//loc_63C58

	DrawF4(rx, ry, rw, rh, 0, 0x2A800000);
	DrawTPage(0, 1);
	DrawLineH((rx + 2) & 0xFFFF, (ry + 1) & 0xFFFF, (rw - 4) & 0xFFFF, 0, 0x404040, 0);
	DrawLineH((rx + 2) & 0xFFFF, ((ry - rh) - 2) & 0xFFFF, (rw - 4) & 0xFFFF, 0, 0x404040, 0);
	DrawLineV((rx + 2) & 0xFFFF, (ry + 1) & 0xFFFF, (rh - 2) & 0xFFFF, 0, 0x404040, 0);
	DrawLineV(((rx - rw) - 3) & 0xFFFF, (ry + 1) & 0xFFFF, (rh - 2) & 0xFFFF, 0, 0x404040, 0);
	DrawTPage(0, 1);

	if ((r->nOptions != 0))
	{
		if ((dbinput2 & 1) && r->CursorPos != 0 && !(r->Ignore >> (r->nOptions - 1) & 1))
		{

			SoundEffect(0x6D, NULL, 2);
			r->OptionCol &= 0x18;
			//loc_63E38
			r->CursorPos--;
		}
		else if ((dbinput2 & 2) && r->CursorPos < (r->nOptions - 1)) //loc_63DDC
		{
			SoundEffect(0x6D, NULL, 2);
			r->OptionCol &= 0x18;
			//loc_63E38
			r->CursorPos++;
		}

		//loc_63E4C
		if ((RawEdge & 0x4000))
		{
			if (r->CursorPos < 2)
			{
				if (r == &SettingsReq)
				{
					return 0x7000000;
				}
			}
			else if (r->CursorPos == 0x1000000)//loc_63E90
			{
				if (r == &ConfigReq)
				{
					return 0;
				}
			}
			else
			{
				//loc_63EB0
				SoundEffect(0x6F, NULL, 2);
				return r->CursorPos | 0x80000000;
			}
		}
		//loc_63ED4
	}
	//loc_63ED4
	return 0;
}