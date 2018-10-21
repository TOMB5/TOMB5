#include "REQUEST.H"

#include "FXTRIG.H"
#include "GAMEFLOW.H"
#include "MISC.H"
#include "SPECIFIC.H"
#include "TEXT.H"

long Requester(struct REQUESTER* r)//63718, 63DF4
{
	//sizeof(struct REQUESTER);

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
	//{ // line 66, offset 0x63a90
	int val; // $s0
	//} // line 68, offset 0x63ad0
	long t0;

	//a1 = &w;
	//s3 = r;
	//v0 = r->TitleTxt;
	//v1 = gfStringOffset;
	//a0 = gfStringWad;

	//a0 = &gfStringWad[gfStringOffset[r->TitleTxt]];

	GetStringDimensions(&gfStringWad[gfStringOffset[r->TitleTxt]], &w, &h);

	//s2 = &top;
	//v0 = 0x00E00000;
	//v1 = h;

	//a0 = r->nOptions

	optiony = h + 4;

	if (r->nOptions != 0)
	{
		//loc_637B0
		for (i = 0; i < r->nOptions; i++)
		{
			h += 2;

			GetStringLength(&gfStringWad[gfStringOffset[r->OptionTxt[i]]], (unsigned short*)&OptionTop[i], (unsigned short*)&OptionBottom[i]);
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

			//loc_63874
			h += rh;
		}
	}

#if 1
	//loc_6389C
	//a1 = y;
	//a2 = 0;
	//a0 = 0x78
	//v0 = h;
	//a3 = w;
	//v0 >>= 1;
	//s2 = a0 - v0;///@todo y
	//v1 = a3 - 0x20;
	//a3 >>= 1;

	rw = w - 32;


	//t0 = gfStringOffset[r->TitleTxt];
	//v1 = h;
	//v1 += 0x10;
	//v0 = 0x100
	x = 0x100 - (w >> 1);
	rh = h + 16;

	//v1 = s4 + -0x10;
	//s5 = v1 & 0xFFFF;
	//v0 = s2 - 8;
	//a0 = gfStringWad;
	//s7 = v0 & 0xFFFF;

	GetStringLength(&gfStringWad[gfStringOffset[r->TitleTxt]], (unsigned short*)&top, NULL);

	//a0 = 0x100
	//a1 = top
	//a2 = r->TitleCol
	//v0 = r->TitleTxt;

	//v1 = gfStringOffset
	//a3 = gfStringWad;

	//a1 = ((y - top) + 2) & 0xFFFF;

	//t0 = gfStringOffset[r->TitleTxt];
	//v0 = 0x8000;
	OptionTop[4] = 0x8000;///@CHECKME sw	$v0, 0x70 + var_60($sp) //TODO cast word

	PrintString(256, ((y - top) + 2) & 0xFFFF, r->TitleCol, &gfStringWad[gfStringOffset[r->TitleTxt]], 0);

	if (r->nOptions != 0)
	{
		//s0 = x & 0xFFFF
		//a0 = s0;
		//a1 = ((y + optiony) - 4) & 0xFFFF
#if 1

		//a2 = W;
		//a3 = 1

		((long*) &OptionTop[4])[0] = 0;//sw	$zero, 0x70 + var_60($sp) check
		((long*) &OptionTop[2])[0] = 0xC0C0C0;//sw	$v0, 0x70 + var_5C($sp)
		DrawLineH(x & 0xFFFF, ((y + optiony) - 4) & 0xFFFF, w, 1);


		DrawTPage(1, 1);

		//v1 = OptionTop[0];

		//s1 = 0 (i)
		//sw	$s0, 0x70 + var_2C($sp)
		//v1 = optiony - OptionTop[0];

		y += optiony - OptionTop[0]; 	//addu	$s2, $v1

			if (r->nOptions != 0)
			{

				//s6 = &r->OptionTxt[0];
				//fp = &savegame;

				//loc_639D8://LOOP
				//lw	$v1, 4($s3)
					//v0 = r.JustifyL;
					if (i == 0 && r->Ignore != 0)
					{
						DisplayConfig(x, y);
					}
					else
					{
						//loc_63A08
						//v0 = r.JustifyL >> i;
						// andi	$a1, $s2, 0xFFFF
						if ((r->JustifyL >> i) & 1)
						{
							t0 = 1;
							if (i == r->CursorPos)
							{
								t0 = r->OptionCol;

							}//loc_63A34

							//v0 = &r->OptionTxt[i << 1];
							//a0 = x;//checkme  lw	$a0, 0x70 + var_2C($sp)
							//v1 = r->OptionTxt[i << 1];
							//a2 = gfStringOffset
							//a3 = &gfStringWad[gfStringOffset[r->OptionTxt[i << 1]]];

							//v1 = gfStringOffset[r->OptionTxt[i << 1]];
							OptionTop[4] = 0;//checkme sw	$zero, 0x70 + var_60($sp)
							PrintString(x, y & 0xFFFF, t0, &gfStringWad[gfStringOffset[r->OptionTxt[i << 1]]], 0);
							//j	loc_63B88
						}
						else
						{
							//loc_63A78
							if ((r->JustifyR >> i) & 1)
							{
								if (i != 0)
								{
									//val = lhu	$s0, 0x70 + var_6E($fp)
								}//loc_63AA4
								else
								{
									//val =  lhu	$s0, 0x70 + var_6C($fp)
								}

								//loc_63AA8
								//v0 = rw;

								//  lw	$a2, 0($s3)
								//a0 = (x - 32) & 0xFFFF

								// srl	$a2, 27
								if (i == r->CursorPos)
								{
									//a2 = 1;

								}

								//loc_63AD0
								//v0 = s1 << 1;
								//v0 = &r->OptionTxt[i];
								//v1 = &gfStringWad[gfStringOffset[r->OptionTxt[i]]];
								//a3 = gfStringWad;
								((long*) &OptionTop[4])[0] = 0x4000;

								//PrintString((x - 32) & 0xFFFF, y & 0xFFFF, a2, &gfStringWad[gfStringOffset[r->OptionTxt[i]]], 0);
								//PrintGauge((rw - 140) & 0xFFFF, (y - 7) & 0xFFFF, val);

								//jmp loc_63B88

							}
							else
							{
								//loc_63B30
								//lw	$a2, 0($s3)
								//srl	$a2, 27
								if (r->CursorPos = i)
								{
								//a2 = 1;
									
								}

								//loc_63B4C
								//a0 = 256;
								//v1 = 
								//((long*) &OptionTop[4])[0] = 0x8000;
								//PrintString(256, y & 0xFFFF, a2, &gfStringWad[gfStringOffset[r->OptionTxt[i]]], a4);
							}
						}
					}

				//loc_63B88

					//s0 = s2 & 0xFFFF
					if (r->CursorPos == i && (r->Arrows >> i) & 1)
					{
						//a0 = (s5 - 4) & 0xFFFF;
						//a1 = s0;
						//a2 = 1;
						//a3 = NoGamesReq[0]
						//sw	$zero, 0x70 + var_60($sp)//TODO
						//PrintString();

#if 0
						li	$a2, 1
							la	$a3, dword_A1F44//?
							jal	sub_8DB4C

							move	$a1, $s0
							li	$a2, 1
							lui	$a3, 0xA
							lhu	$a0, 0x70 + var_34($sp)
							la	$a3, dword_A1F48
							sw	$zero, 0x70 + var_60($sp)
							addu	$a0, $s5, $a0
							addiu	$a0, -8
							jal	sub_8DB4C
							andi	$a0, 0xFFFF
#endif

					}//loc_63C04
					
					
					
		
				
					
					
#if 0
					loc_63C04:
				lw	$v0, 0($s3)
					nop
					srl	$v0, 21
					andi	$a3, $v0, 7
					addiu	$v1, $a3, -1
					slt	$v1, $s1, $v1
					beqz	$v1, loc_63C48
					addiu	$a2, $s1, 1
					sll	$v0, $s1, 1
					addu	$a1, $sp, $v0
					sll	$v1, $a2, 1
					addu	$a0, $sp, $v1
					lh	$v0, 0x28($a1)
					lh	$v1, 0x18($a0)
					addiu	$a1, $s2, 2
					subu	$v0, $v1
					addu	$s2, $a1, $v0

					loc_63C48 :
				move	$s1, $a2
					slt	$v0, $s1, $a3
					bnez	$v0, loc_639D8
					nop
#endif
	}
#endif
	}
	
	//loc_63C58
#if 0

	//li	$s2, 0x404040
	((long*) &OptionTop[4])[0] = 0;//sw	$zero, 0x70 + var_60($sp) check
	((long*) &OptionTop[2])[0] = 0x2A800000;//sw	$v0, 0x70 + var_5C($sp) check
	DrawF4(rx, ry, rw, rh);
	DrawTPage(0, 1);

	//a0 = (rx + 2) & 0xFFFF;
	//a1 = (ry + 1) & 0xFFFF;
	
	//a2 = (rw - 4) & 0xFFFF;
		a3 = 0;
		((long*) &OptionTop[4])[0] = 0x404040;
		((long*) &OptionTop[2])[0] = 0//sw	$zero, 0x70 + var_5C($sp)

		DrawLineH((rx + 2) & 0xFFFF, (ry + 1) & 0xFFFF, (rw - 4) & 0xFFFF, 0);


		//
		//s0 = (rx + 2) & 0xFFFF

		//a0 = s0;

		//a1 = rh;
		//a2 = rw;
		//a3 = 0;

		((long*) &OptionTop[4])[0] = 0x404040;//sw	$s2, 0x70 + var_60($sp)
		((long*) &OptionTop[2])[0] = 0x0;//sw	$zero, 0x70 + var_5C($sp)
		DrawLineH((rx + 2) & 0xFFFF, ((ry + rh) - 2) & 0xFFFF, (rw - 4) & 0xFFFF, 0);

		((long*) &OptionTop[4])[0] = 0x404040;//sw	$s2, 0x70 + var_60($sp)
		((long*) &OptionTop[2])[0] = 0x0;//sw	$zero, 0x70 + var_5C($sp)
		DrawLineV((rx + 2) & 0xFFFF, (ry + 1) & 0xFFFF, (rh - 2) & 0xFFFF, 0);

		((long*) &OptionTop[4])[0] = 0x404040;//sw	$s2, 0x70 + var_60($sp)
		((long*) &OptionTop[2])[0] = 0x0;//sw	$zero, 0x70 + var_5C($sp)

		DrawLineV(((rx + rw) - 3) & 0xFFFF, (ry + 1) & 0xFFFF, (rh - 2) & 0xFFFF, 0);
		DrawTPage(0, 1);


		if (r->Options == 0)
		{
			//loc_63ED4
			return 0;
		}

		//a1 = dbinput2;
		if (dbinput2 & 1)
		{
			//srl	$v0, $a0, 24
			if (((long*) &r)[0] & 0x7000000)
			{


			}//loc_63DDC

		}//loc_63DDC


				 lw	$v1, 4($s3)
				 andi	$v0, 7
				 addiu	$v0, -1
				 srl	$v1, 15
				 andi	$v1, 0x1F
				 srav	$v1, $v0
				 andi	$v1, 1
				 bnez	$v1, loc_63DDC
				 li	$a0, 0x6D
				 move	$a1, $zero
				 jal	sub_91780
				 li	$a2, 2
				 lui	$v1, 0xF8FF
				 lw	$v0, 0($s3)
				 li	$v1, 0xF8FFFFFF
				 and $v1, $v0, $v1
				 srl	$v0, 24
				 andi	$v0, 7
				 j	loc_63E38
				 addiu	$v0, -1

				 loc_63DDC:
			 andi	$v0, $a1, 2
				 beqz	$v0, loc_63E4C
				 nop
				 lw	$v0, 0($s3)
				 nop
				 srl	$v1, $v0, 24
				 andi	$v1, 7
				 srl	$v0, 21
				 andi	$v0, 7
				 addiu	$v0, -1
				 slt	$v1, $v0
				 beqz	$v1, loc_63E4C
				 li	$a0, 0x6D
				 move	$a1, $zero
				 jal	sub_91780
				 li	$a2, 2
				 lui	$v1, 0xF8FF
				 lw	$v0, 0($s3)
				 li	$v1, 0xF8FFFFFF
				 and $v1, $v0, $v1
				 srl	$v0, 24
				 andi	$v0, 7
				 addiu	$v0, 1

				 loc_63E38:
			 andi	$v0, 7
				 sll	$v0, 24
				 or $v1, $v0
				 j	loc_63ED0
				 sw	$v1, 0($s3)

				 loc_63E4C :
				 lw	$v0, dword_800A4520
				 nop
				 andi	$v0, 0x4000
				 beqz	$v0, loc_63ED4
				 move	$v0, $zero
				 lw	$v1, 0($s3)
				 nop
				 srl	$v0, $v1, 24
				 andi	$v0, 7
				 sltiu	$v0, 2
				 beqz	$v0, loc_63E90
				 lui	$v0, 0x700
				 la	$v0, dword_A1990
				 beq	$s3, $v0, loc_63ED0
				 lui	$v0, 0x700

				 loc_63E90:
			 and	$v0, $v1, $v0
				 lui	$v1, 0x100
				 bne	$v0, $v1, loc_63EB0
				 li	$a0, 0x6F
				 la	$v0, dword_A19A4
				 beq	$s3, $v0, loc_63ED0
				 nop

				 loc_63EB0 :
			 move	$a1, $zero
				 jal	sub_91780
				 li	$a2, 2
				 lbu	$v0, 3($s3)
				 nop
				 andi	$v0, 7
				 j	loc_63ED4
				 ori	$v0, 0x8000

				 loc_63ED0:
			 move	$v0, $zero

				 loc_63ED4 :
			 lw	$ra, 0x70 + var_4($sp)
				 lw	$fp, 0x70 + var_8($sp)
				 lw	$s7, 0x70 + var_C($sp)
				 lw	$s6, 0x70 + var_10($sp)
				 lw	$s5, 0x70 + var_14($sp)
				 lw	$s4, 0x70 + var_18($sp)
				 lw	$s3, 0x70 + var_1C($sp)
				 lw	$s2, 0x70 + var_20($sp)
				 lw	$s1, 0x70 + var_24($sp)
				 lw	$s0, 0x70 + var_28($sp)
				 jr	$ra
				 addiu	$sp, 0x70
				 # End of function sub_63718
#endif
#endif
	return 0;
}