#include "REQUEST.H"

#include "EFFECTS.H"
#include "FXTRIG.H"
#include "GAMEFLOW.H"
#include "MISC.H"
#include "SAVEGAME.H"
#include "SPECIFIC.H"
#include "PSXINPUT.H"
#include "TEXT_S.H"

long Requester(struct REQUESTER* r/*$s3*/)//63718(<), 63DF4 (F)
{
	int x; // $s4
	int y; // $s2
	short top; // stack offset -48
	unsigned short w; // stack offset -56
	unsigned short h; // stack offset -54
	int i; // $s1
	int optiony; // $s6
	unsigned short rx; // $s5
	unsigned short ry; // $s7
	unsigned short rw; // stack offset -52
	unsigned short rh; // stack offset -50
	short OptionTop[5]; // stack offset -88
	short OptionBottom[5]; // stack offset -72
	int val; // $s0

	GetStringDimensions(&gfStringWad[gfStringOffset[r->TitleTxt]], &w, &h);
	//s2 = &top
	//v0 = 0xE00000
	//v1 = h
	//a0 = r->
	//v0 = r->nOptions;
	optiony = h + 4;
	if (r->nOptions != 0)
	{
		h += 2;

		i = 0;
		if (r->nOptions != 0)
		{
			//loc_637B0
			for (i = 0; i < r->nOptions; i++)
			{
				//a3 = i << 1
				//a1 = &OptionTop[i]
				//s0 = &r->OptionTxt[i]
				//a2 = &OptionBottom[i]
				//a0 = &gfStringWad[gfStringOffset[r->OptionTxt[i]]]
				//a0 = gfStringWad

				GetStringLength(&gfStringWad[gfStringOffset[r->OptionTxt[i]]], &OptionTop[i], &OptionBottom[i]);

				//a1 = &rw
				//v0 = 
				//a3 = gfStringOffset[r->OptionTxt[i]]
				//a0 = gfStringWad
				//a2 = &rh
				GetStringDimensions(&gfStringWad[gfStringOffset[r->OptionTxt[i]]], &rw, &rh);

				if (i == 0 && r->Ignore != 0)
				{
					OptionBottom[0] = OptionTop[0] + rh;
				}
				//loc_63858
				//v1 = rw
				//v0 = w
				//v0 = v0 < v1 ? 1 : 0
				if (w < rw)
				{
					w = rw;
				}
				//loc_63874
				//v0 = h
				//a0 = rh
				//v1 = *(int*)r;
				//h += rh;
				//v1 = i < r->nOptions ? 1 : 0;
			}
		}//loc_6389C
	}
	//loc_6389C
	//a1 = y;
	//a2 = 0;
	//a0 = 0x78
	//v0 = h >> 1;
	//a3 = w;

	y = 120 - (h >> 1);
	rw = w + 32;
	//a3 = w >> 1;
	//v0 = r->TitleTxt
	//a0 = gfStringOffset
	//v1 = h + 16
	//v0 = &gfStringOffset[r->TitleTxt];
	//t0 = gfStringOffset[r->TitleTxt];
	//v0 = 0x100
	x = 256 - (w >> 1);//s4
	rh = h + 16;

	///@TODO rx, ry
	//v1 = x - 16
	rx = (x - 16) & 0xFFFF;
	//v0 = y - 8
	//a0 = gfStringWad
	ry = (y - 8) & 0xFFFF;

	GetStringLength(&gfStringWad[gfStringOffset[r->TitleTxt]], &top, NULL);

	//a0 = 0x100
	//a1 = top
	//lhu     $a2, 2($s3)
	//v0 = r->TitleTxt
	//v1 = gfStringOffset
	//a3 = gfStringWad

	//a1 = ((y - top) + 2) & 0xFFFF
	//a2 = r->TitleCol
	//v0 = &gfStringOffset[r->TitleTxt];
	//t0 = gfStringOffset[r->TitleTxt];

	PrintString(256, ((y - top) + 2) & 0xFFFF, r->TitleCol, &gfStringWad[gfStringOffset[r->TitleTxt]], 0x8000);

	if (r->nOptions != 0)
	{
		//v0 = 0xC0C0C0
		//s0 = x & 0xFFFF
		//a0 = x & 0xFFFF
		//a1 = ((y + optiony) - 4) & 0xFFFF
		//a2 = w
		//a3 = 1
		DrawLineH(x & 0xFFFF, ((y + optiony) - 4) & 0xFFFF, w, 1, 0, 0xC0C0C0);
		DrawTPage(0, 1);
		//v1 = OptionTop[0]
		//v0 = *(int*)r;

		//v1 = optiony - OptionTop[0]

		y += optiony - OptionTop[0];
		if (r->nOptions != 0)
		{
			//s6 = &r->OptionTxt[0]
			//fp = &savegame

			//loc_639D8
			for (i = 0; i < r->nOptions; i++)
			{
				//lw      $v1, 4($s3)
				//v0 = r->JustifyL;
				if (i == 0 && r->Ignore != 0)
				{
					DisplayConfig(x, y);
					//j       loc_63B88
				}
				else
				{
					//loc_63A08
					//a1 = s2 & 0xFFFF
					if ((r->JustifyL >> h) & 1)
					{
						//v0 = r->CursorPos;
						if (i != r->CursorPos)
						{
							PrintString(x & 0xFFFF, y & 0xFFFF, r->OptionCol, &gfStringWad[gfStringOffset[r->OptionTxt[i]]], 0);
							///j       loc_63B88
						}//loc_63A34
						else
						{
							PrintString(x & 0xFFFF, y & 0xFFFF, 1, &gfStringWad[gfStringOffset[r->OptionTxt[i]]], 0);
							///j       loc_63B88
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
							//a0 = ((rw + x) - 32) & 0xFFFF
							if (i == r->CursorPos)
							{
								PrintString(((rw + x) - 32) & 0xFFFF, y & 0xFFFF, 1, &gfStringWad[gfStringOffset[r->OptionTxt[i]]], 0x4000);
							}
							else
							{
								//loc_63AD0
								PrintString(((rw + x) - 32) & 0xFFFF, y & 0xFFFF, r->OptionCol, &gfStringWad[gfStringOffset[r->OptionTxt[i]]], 0x4000);
							}

							///PrintGauge(((rw + x) - 140) & 0xFFFF, (y - 7) & 0xFFFF, val);
							/// j       loc_63B88
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
					//s0 = y & 0xFFFF
					if ((r->Arrows >> i) & 1)
					{
						PrintString((rx - 4) & 0xFFFF, y & 0xFFFF, 2, "\x00000019", 0);
						PrintString(((rx + rw) - 8) & 0xFFFF, y & 0xFFFF, 1, "\x0000001B", 0);
					}//loc_63C04
				}//loc_63C04

				//a3 = r->nOptions
				//v1 = r->nOptions - 1
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
				}
				//loc_63C48
			}
		}//loc_63C58
	}//loc_63C58

	//a0 = rx
	//a1 = ry
	//s2 = 0x404040
	//a2 = rw
	//a3 = rh
	//v0 = 0x2A800000

	DrawF4(rx, ry, rw, rh, 0, 0x2A800000);
	DrawTPage(0, 1);
	//s0 = (rx + 2) & 0xFFFF

	//a0 = s0
	//s1 = (ry + 1) & 0xFFFF;

	//a1 = (ry + 1) & 0xFFFF
	//a2 = (rw - 4) & 0xFFFF
	//a3 = 0
	DrawLineH((rx + 2) & 0xFFFF, (ry + 1) & 0xFFFF, (rw - 4) & 0xFFFF, 0, 0x404040, 0);
	DrawLineH((rx + 2) & 0xFFFF, ((ry - rh) - 2) & 0xFFFF, (rw - 4) & 0xFFFF, 0, 0x404040, 0);
	DrawLineV((rx + 2) & 0xFFFF, (ry + 1) & 0xFFFF, (rh - 2) & 0xFFFF, 0, 0x404040, 0);
	DrawLineV(((rx - rw) - 3) & 0xFFFF, (ry + 1) & 0xFFFF, (rh - 2) & 0xFFFF, 0, 0x404040, 0);
	DrawTPage(0, 1);

	//v0 = 0;
	if ((r->nOptions != 0))
	{
		//v0 = dbinput2
		//v1 = 
		//a1 = v0
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
			///loc_63E38
			r->CursorPos++;
		}

		//loc_63E4C
		if ((RawEdge & 0x4000))
		{
			//v0 = 0x7000000
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