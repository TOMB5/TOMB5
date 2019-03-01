#include "TITSEQ.H"

#include "CONTROL.H"
#include "DELTAPAK.H"
#include "EFFECTS.H"
#include "GAMEFLOW.H"
#include "GPU.H"
#include "LOADSAVE.H"
#include "MEMCARD.H"
#include "PSXINPUT.H"
#include "ROOMLOAD.H"
#include "SAVEGAME.H"
#include "SOUND.H"
#include "SPOTCAM.H"
#include "TEXT_S.H"
#include "MISC.H"

#include <LIBETC.H>
#include <stdio.h>//deleteme

#if! DISC_VERSION
#include <LIBSN.H>
#include "FILE.H"
#endif

#if DEBUG_VERSION
#include <PROFILE.H>
#endif

#define BLOCK_SPLINE_CAM (0)
#define HACK_SAVE_SECRETS (0)

#if PSX_VERSION && RELOC
void* func_titseq[] __attribute__((section(".header"))) =
{
	&TitleOptions,
};

unsigned char titseqData[] __attribute__((section(".data"))) =
{
	0,//xyte_46
	0,//xyte_47
	0,//xyte_1A8
};

unsigned int titseqData2[] __attribute__((section(".data"))) =
{
	0,//xord_38
};

#endif

unsigned short unk_3C[] = { STR_MOVIE_TRAILER, STR_STORYBOARDS_PART_1, STR_NEXT_GENERATION_CONCEPT_ART, STR_STORYBOARDS_PART_2, STR_NEXT_GENERATION_PREVIEW };
unsigned char byte_2600[] = { 0, 0, 0, 0, 0 }; ///@FIXME i don't know the len (maybe max of titseqData[0])

struct CutseqMenuItem
{
	unsigned short menuText;
	unsigned char unk00;
	unsigned char unk01;
	unsigned short cutseq;
};

struct CutseqMenuItem unk_1AC[] =
{
	{ STR_SEVERAL_HOURS_LATER,0x00, 0x00,0x0000 },
{ STR_ANDY4B,0x08, 0x00,0x0900 },
{ STR_ANDY11,0x0A, 0x00,0x2C00 },
{ STR_SWAMPY,0x0A, 0x00,0x2B00 },
{ STR_MONK2,0x09, 0x00,0x2A00 },
{ STR_ANDREA4,0x03, 0x00,0x2900 },
{ STR_JOBY7,0x06, 0x00,0x2800 },
{ STR_ANDY10,0x0A, 0x00,0x2700 },
{ STR_ANDY8,0x0A, 0x00,0x2600 },
{ STR_ANDY9,0x0A, 0x00,0x2500 },
{ STR_COSSACK,0x0A, 0x00,0x2400 },
{ STR_JOBY_CUT_2,0x04, 0x00,0x1900 },
{ STR_JOBY_CRANE_CUT,0x04, 0x00,0x1B00 },
{ STR_RICH_CUT_2,0x0D, 0x00,0x1A00 },
{ STR_RICH_CUT_1,0x0B, 0x00,0x1800 },
{ STR_RICH_CUT_3,0x0C, 0x00,0x1700 },
{ STR_JOBY_CUT_3,0x04, 0x00,0x1600 },
{ STR_ANDY1,0x08, 0x00,0x1500 },
{ STR_RICH1,0x0B, 0x00,0x1400 },
{ STR_ANDY2,0x08, 0x00,0x1300 },
{ STR_JOBY4,0x05, 0x00,0x1200 },
{ STR_ANDREA1,0x01, 0x00,0x1100 },
{ STR_ANDREA2,0x01, 0x00,0x1000 },
{ STR_JOBY5,0x05, 0x00,0x0F00 },
{ STR_ANDY3,0x08, 0x00,0x0E00 },
{ STR_JOBY9,0x07, 0x00,0x0D00 },
{ STR_JOBY10,0x07, 0x00,0x0C00 },
{ STR_RICHCUT4,0x0B, 0x00,0x0B00 },
{ STR_ANDY4,0x08, 0x00,0x0A00 },
{ STR_ANDREA3,0x02, 0x00,0x0800 },
{ STR_ANDREA3B,0x02, 0x00,0x0700 },
{ STR_ANDY5,0x09, 0x00,0x0600 },
{ STR_JOBY6,0x05, 0x00,0x0500 },
{ STR_JOBY8,0x07, 0x00,0x2000 },
{ STR_ANDY6,0x09, 0x00,0x2100 }
};

enum
{
	MENU_MAIN_MENU,
	MENU_LOAD_MENU,
	MENU_LEVEL_SELECT_MENU,
	MENU_SPECIAL_FEATURES_MENU
};

int TitleOptions(int Name)
{
	int a1;
#if DEBUG_VERSION
	char buf[80];//0x18(sp)
#endif
	int ret; //0x68(sp)
	int s1 = 0;
	int s2 = 0;
	int s3 = 0;
	int y = 0;//s3 = 0 = runtimecheckfailure
	int i = 0;//s4
	unsigned short* s4;
	int s5 = 0;
	int s6;

	//v0 = 0xA0000
	//v1 = PadConnected
	ret = 0;
	//0x98(sp) = Name

#if BLOCK_SPLINE_CAM
	current_spline_position = 0;
#endif

#if HACK_SAVE_SECRETS
	savegame.CampaignSecrets[0] = 9;
	savegame.CampaignSecrets[1] = 9;
	savegame.CampaignSecrets[2] = 9;
	savegame.CampaignSecrets[3] = 9;
#endif

	if (PadConnected == 0)
	{
		titseqData[0] = 0;
		Chris_Menu = MENU_MAIN_MENU;
		dels_cutseq_selector_flag = 0;
	}
	//loc_49C
	//a0 = gfGameMode
	if (gfGameMode == 2)
	{
		return 0;
	}

	//v1 = dels_cutseq_selector_flag
	//v0 = 0xA0000
	if (dels_cutseq_selector_flag != 0)
	{
		//v1 = 0x00000
		Chris_Menu = MENU_MAIN_MENU;
		titseqData[0] = 0;
		return sub_1054();
	}//loc_4DC

	 //a0 = Chris_Menu
	 //v1 = 1
	 //s7 = v0
	if (Chris_Menu != MENU_LOAD_MENU && Chris_Menu != MENU_SPECIAL_FEATURES_MENU)
	{
		if (bDoCredits == 0)
		{
			sub_2B0();
		}
	}
	else if (bDoCredits == 0)
	{
		//loc_514
#if DEBUG_VERSION
		if (bDoCredits == 0)
		{
			sprintf(&buf[0], "Savegame = %d bytes", 0x3B4);
			PrintString(256, 232, 5, &buf[0], 0x9064);
		}//loc_558
#endif
	}


	//loc_558
	a1 = last_camera;
	//a0 = current_sequence

	if (current_sequence == 2)
	{
		a1 = current_sequence - 1;
	}
	//loc_57C
	//v0 = current_spline_camera

	if (current_spline_camera > a1 && 0xCB20 < current_spline_position)
	{
		title_controls_locked_out = 1;
	}

	//loc_5AC
	if (title_controls_locked_out)
	{
		RawEdge = 0;
	}

	//loc_5C0
	//v1 = Chris_Menu
	//v0 = Chris_Menu < 2 ? 1 : 0 
	if (Chris_Menu == MENU_LOAD_MENU)
	{
		//loc_91C
		s1 = LoadGame();

		if (s1 != 0)
		{
			Chris_Menu = MENU_MAIN_MENU;
			titseqData[0] = 0;
			if (s1 > 0)
			{
				ret = 2;
			}
		}//loc_EB4

		return ret;
	}
	else if (Chris_Menu == MENU_LEVEL_SELECT_MENU)
	{
		//loc_948
		//v0 = 0
		//a0 = titseqData[0]
		s1 = titseqData[0] - 6;
		if (s1 < 0)
		{
			s1 = 0;
		}//loc_964

		if ((RawEdge & 0x10) && titseqData[0] != 0)
		{
			SoundEffect(SFX_MENU_SELECT, NULL, 2);
			--titseqData[0];
		}
		else if ((RawEdge & 0x40) && titseqData[0] < Gameflow->nLevels - 2)
		{
			SoundEffect(SFX_MENU_SELECT, NULL, 2);
			++titseqData[0];
		}
		else if ((RawEdge & 0x200))
		{
			titseqData[0] = Gameflow->nLevels - 2;
		}
		else if ((RawEdge & 0x100))
		{
			titseqData[0] = 0;
		}
		else if ((RawEdge & 0x800))
		{
			titseqData[0] = ((Gameflow->nLevels - 2) + ((Gameflow->nLevels - 2) >> 31)) >> 1;
		}
		else if ((RawEdge & 0x400))
		{
			titseqData[1] ^= 1;

		}
		//loc_A98
		//v1 = Gameflow
		//Gameflow->nLevels -1
		//v0 = s1 < v0 ? 1 : 0

		i = 0;
		if (s1 < Gameflow->nLevels - 1)
		{
			//s5 = 0x8000
			//s6 = &gfLevelNames
			y = 0x70;
			//s2 = 0x70
			//v0 = 0

			//v1 = titseqData[1]
			//t0 = 5
			//loc_AD8
			do
			{
				if (titseqData[1])
				{
					//a3 = 0
					//v0 = titseqData[0]
					//a1 = s2 & 0xFFFF
					if (titseqData[0] == s1)
					{
						//t0 = 1
					}//loc_B00

					 //a0 = 0x100
					 //s9 = s1 + 1
					 ///TODO la      $v0, unk_2608


				}
				else
				{
					//loc_B48
					//a2 = 5
					//v1 = 0
					//v0 = titseqData[0]
					//a1 = s3 & 0xFFFF

					//s5 = 0x8000
					//a0 = 0x100
					//s0 = s1 + 1
					//v1 = &gfLevelNames[s0]
					//a3 = 0xA0000
					//v0 = gfLevelNames[s0]
					//t0 = gfStringOffset
					//a3 = gfStringWad
					//a3 = &gfStringWad[gfStringOffset[gfLevelNames[s1 + 1]]];



					///@TODO tomorrow
				}
				//loc_B94

				if (titseqData[0] == s1)
				{
					PrintString(256, y & 0xFFFF, 1, &gfStringWad[gfStringOffset[gfLevelNames[s1 + 1]]], 0x8000);
				}
				else
				{
					PrintString(256, y & 0xFFFF, 5, &gfStringWad[gfStringOffset[gfLevelNames[s1 + 1]]], 0x8000);
				}
				y += 18;
				//v0 = s0
				s1++;
				s2 += 18;
				//v0 = 
				//s4++;
				if (s1 > Gameflow->nLevels - 1)
				{
					break;
				}
			} while (++i < 7);
		}
		//loc_BD4

		//v1 = RawEdge
		if ((RawEdge & 0x4000))
		{
			SoundEffect(SFX_MENU_CHOOSE, NULL, 2);
			ret = 3;
			Chris_Menu = MENU_MAIN_MENU;
			gfLevelComplete = titseqData[0] + 1;
			titseqData[0] = 0;
		}
		else if ((RawEdge & 0x1000))
		{
			//loc_C20
			SoundEffect(SFX_MENU_CHOOSE, NULL, 2);
			Chris_Menu = MENU_MAIN_MENU;
		}

		return ret;
	}
	else if (Chris_Menu == MENU_SPECIAL_FEATURES_MENU)
	{
		//loc_C3C
		//a0 = 256
		//a1 = 32
		//a2 = 6
		s6 = 0;
		s1 = 0;
		//s2 = 0x404040
		//s5 = 0
		//v0 = gfStringOffset
		//a3 = gfStringWad
		PrintString(256, 32, 6, &gfStringWad[gfStringOffset[STR_SPECIAL_FEATURES]], 0x8000);
		//v0 = 0xB0000
		//fp = &savegame.CampaignSecrets
		s4 = &unk_3C[0];

		//v1 = &savegame.CampaignSecrets[s1];
		//loc_C8C
		for (s1 = 0; s1 < 5; s1++, s4++)
		{
			if (s1 != 0)
			{
				if (savegame.CampaignSecrets[s1 - 1] < 9)
				{
					//loc_DDC
					continue;
				}
			}

			//loc_CA8
			//v0 = 0
			//v1 = dtitseqData2[0]
			//a2 = 2

			y = ((s5 - (titseqData2[0] * 12) + 0x70)) & 0xFF;

			//nop
			//addiu   $a1, $s3, 4
			if (titseqData[0] == s6)
			{
				PrintString(256, y + 4, 1, &gfStringWad[gfStringOffset[s4[0]]], 0x8000);
			}
			else
			{
				PrintString(256, y + 4, 2, &gfStringWad[gfStringOffset[s4[0]]], 0x8000);
			}

			//loc_CE4
			s5 += 24;

			DrawF4(64, y - 11, 384, 22, 0, 0x2A800000);
			DrawTPage(0, 0);
			DrawLineH(66, y - 10, 380, 0, s2, 0);
			DrawLineH(66, y + 9, 380, 0, s2, 0);
			DrawLineV(66, y - 10, 20, 0, s2, 0);
			DrawLineV(445, y - 10, 20, 0, s2, 0);

			DrawTPage(0, 1);

			s6++;

			//loc_DDC
		}

		if ((RawEdge & 0x10) && titseqData[0] != 0)
		{
			--titseqData[0];
			//j loc_EB4
		}
		else if ((RawEdge & 0x40) && titseqData[0] < titseqData2[0] - 1)
		{
			++titseqData[0];
			//j loc_EB4
		}
		else if ((RawEdge & 0x1000))
		{
			Chris_Menu = MENU_MAIN_MENU;
			titseqData[0] = CanLoad + 1;
			//j loc_EB4
		}
		else if ((RawEdge & 0x4000))
		{
			sub_2154(Name, byte_2600[titseqData[0]]);
		}

		return ret;
	}
	else if (Chris_Menu == MENU_MAIN_MENU)
	{
		//loc_600
		//v1 = Gameflow
		//s3 = 0xC0

		//Overidden in gameflow script disable loading now.
		if (!Gameflow->LoadSaveEnabled)
		{
			y = 192;
			//loc_6B4
			//s1 = a0
			if (CanLoad == 1)
			{
				titseqData[0] = 0;
				CanLoad = 0;
			}//loc_6D4
		}
		else if (mcGetStatus() != 0)
		{
			y = 192;
			//loc_6B8
			if (CanLoad == 1)
			{
				titseqData[0] = 0;
				CanLoad = 0;
			}//loc_6D4
		}
		else if (mcNumFiles != 0)
		{
			//loc_6B0
			y = 208;
			if (CanLoad == 0)
			{
				titseqData[0] = 0;
				CanLoad = 1;
			}//loc_664

			if (titseqData[0] == 1)
			{
				PrintString(256, 192, 1, &gfStringWad[gfStringOffset[STR_LOAD_GAME_BIS]], 0x8000);
			}
			else
			{
				PrintString(256, 192, 2, &gfStringWad[gfStringOffset[STR_LOAD_GAME_BIS]], 0x8000);
			}
		}//loc_6B0 mcnumfiles
		else
		{
			//loc_6B0
			y = 192;
		}

		//j loc_6D8
	}
	else
	{
		return ret;
	}

	//loc_6D8
	if (titseqData[0] == 0)
	{
		PrintString(256, 176, 1, &gfStringWad[gfStringOffset[STR_SAVE_GAME_BIS]], 0x8000);
	}
	else
	{
		PrintString(256, 176, 2, &gfStringWad[gfStringOffset[STR_SAVE_GAME_BIS]], 0x8000);
	}

	//a0 = 0

	if (titseqData[0] == 2)
	{
		//v0 = 1
		PrintString(256, y, 1, &gfStringWad[gfStringOffset[STR_SPECIAL_FEATURES]], 0x8000);
	}
	else if (titseqData[0] != 1)
	{
		PrintString(256, y, 2, &gfStringWad[gfStringOffset[STR_SPECIAL_FEATURES]], 0x8000);
	}
	else if (CanLoad != 0)
	{
		PrintString(256, y, 2, &gfStringWad[gfStringOffset[STR_SPECIAL_FEATURES]], 0x8000);
	}
	else
	{
		PrintString(256, y, 1, &gfStringWad[gfStringOffset[STR_SPECIAL_FEATURES]], 0x8000);
	}

	//v0 = gfStringOffset
	//a1 = y
	//v1 = ;
	if ((RawEdge & 0x10) && titseqData[0] != 0)//Up
	{
		SoundEffect(SFX_MENU_SELECT, NULL, 2);
		--titseqData[0];
	}//loc_7C0
	else if ((RawEdge & 0x40) && titseqData[0] < CanLoad + 1)//Down
	{
		//loc_7C0
		SoundEffect(SFX_MENU_SELECT, NULL, 2);
		++titseqData[0];
	}//loc_810



	if ((RawEdge & 0x4000))//X pressed
	{
		if (titseqData[0] == 1)
		{
			if (CanLoad != 0)
			{
				Chris_Menu = MENU_LOAD_MENU;
			}
			else
			{
				//loc_850
				sub_3A8();
				Chris_Menu = MENU_SPECIAL_FEATURES_MENU;
				titseqData[0] = 0;
			}

			//loc_904
			SoundEffect(SFX_MENU_CHOOSE, NULL, 2);
		}//loc_86C
		else
		{
			//loc_86C
			if (titseqData[0] != 0)
			{
				//loc_8EC
				sub_3A8();
				Chris_Menu = MENU_SPECIAL_FEATURES_MENU;
				titseqData[0] = 0;
			}
			else
			{
				if (Gameflow->PlayAnyLevel)
				{
					Chris_Menu = MENU_LEVEL_SELECT_MENU;
				}
				else
				{
					//loc_89C
					ret = 3;
					Chris_Menu = MENU_MAIN_MENU;

					if ((RawPad & 0x400))
					{
						gfLevelComplete = 4;
					}
					else
					{
						gfLevelComplete = 1;
					}

					//loc_8C8
					if ((RawPad & 0x100))
					{
						gfLevelComplete = 8;
					}

					if ((RawPad & 0x800))
					{
						gfLevelComplete = 11;
					}
				}
			}
			//loc_904
			SoundEffect(SFX_MENU_CHOOSE, NULL, 2);
			return ret;
		}
	}
	else
	{
		//loc_EB4
		return ret;
	}

	s1 = LoadGame(); //Disabled due to crashing

	if (s1 == 0)
	{
		return ret;
	}

	Chris_Menu = MENU_MAIN_MENU;
	titseqData[0] = 0;

	if (s1 <= 0)
	{
		return ret;
	}
	else
	{
		ret = 2;
	}

	return ret;
}

void sub_2B0()
{
	if ((unsigned long)db.polyptr < (unsigned long)db.polybuf_limit)
	{
		POLY_FT4* ptr = (POLY_FT4*)db.polyptr;

		setPolyFT4(ptr);

		setRGB0(ptr, 128, 128, 128);

		setXY4(ptr,
			56, 24,
			440, 24,
			56, 80,
			440, 80);

		setClut(ptr, 576, 124);
		setTPage(ptr, 0, 1, 576, 0);

		setUV4(ptr,
			0, 68,
			255, 68,
			0, 124,
			255, 124);

		addPrim(db.ot, ptr);

		db.polyptr += sizeof(POLY_FT4);
	}//locret_3A0
}

void sub_3A8()
{
	int i = 0;//a2
			  //t1 = 1
			  //a2 = 0
			  //t4 = &savgame.CampaignSecrets[0]
			  //a1 = 0
			  //t0 = 0
			  //a0 = 0
			  //v1 = &byte_2600[0]
			  //t3 = &byte_2600[0]
			  //a3 = 0x20000
			  //t2 = 0x10000
			  //v0 = 1
	titseqData2[0] = 1;

	byte_2600[0] = 0;
	byte_2600[1] = 0;
	byte_2600[2] = 0;
	byte_2600[3] = 0;
	byte_2600[4] = 0;

	//v0 = &savgame.CampaignSecrets[0]

	//loc_3F4
	do
	{
		//v1 = savgame.CampaignSecrets[0]
		//v1 = savgame.CampaignSecrets[0] < 9 ? 1 : 0

		//a1 = a2 + 1
		if (savegame.CampaignSecrets[i] > 8)
		{
			byte_2600[i + 1] = i + 1;
			titseqData2[0]++;
		}//loc_428

	} while (++i < 4);
}

int sub_1054()
{
	int i;
	int a3 = 0;
	int y = 0;//s1
	int ret = 0;//fp

	sub_2B0();
	PrintString(256, 102, 6, &gfStringWad[gfStringOffset[STR_SELECT_CUTSCENE]], 0x8000);

	a3 = titseqData[2] - 4;
	if ((titseqData[2] - 4) < 0)
	{
		a3 = 0;
	}
	//loc_10DC

	if ((RawEdge & 0x10) && titseqData[2] != 0)
	{
		--titseqData[2];
	}
	else if ((RawEdge & 0x40) && titseqData[2] < 35)
	{
		++titseqData[2];
	}

	i = 0;
	//loc_1128
	if ((titseqData[2] - 4) < 36)
	{
		y = 136;
		//loc_1144
		do
		{
			if (titseqData[2] == a3)
			{
				PrintString(256, y, 1, &gfStringWad[gfStringOffset[unk_1AC[a3 + 1].menuText]], 0x8000);
			}
			else
			{
				PrintString(256, y, 5, &gfStringWad[gfStringOffset[unk_1AC[a3 + 1].menuText]], 0x8000);
			}

			y += 18;

			if (a3 + 1 > 0x23)
			{
				break;
			}

			a3++;
		} while (++i < 5);

	}//loc_11B8

	if ((RawEdge & 0x4000))
	{
		SoundEffect(SFX_MENU_CHOOSE, NULL, 2);
		ret = 3;
		dels_cutseq_selector_flag = 0;
		cutrot = 0;
		gfLevelComplete = unk_1AC[titseqData[2] + 1].unk00;
		dels_cutseq_player = unk_1AC[titseqData[2] + 1].cutseq;
		titseqData[2] = 0;
	}//loc_1240

	if ((RawEdge & 0x1000))
	{
		dels_cutseq_selector_flag = 0;
	}

	return ret;
}

void sub_2154(int Name, unsigned char a1)
{
	if (a1 != 0 && a1 != 4)
	{
		sub_219C(a1 - 1);
		ReloadAnims(Name, cutseq_malloc_used);
	}//loc_218C
}

void sub_219C(unsigned char a0)
{
	void* s1;
	int fp;
	int s4;
	fp = 12;
	//s7 = a0
	//v0 = 1

	if (a0 == 1)
	{
		fp = 15;
	}

	//loc_21DC
	s4 = 0;

#if DEBUG_VERSION
	ProfileDraw = 0;
#endif

	DrawSync(0);
	VSync(0);
	//s0 = &db
	//s1 = &db.disp[1]
	//a0 = s1
	db.draw[1].isbg = 0;
	db.draw[0].isbg = 0;
	db.draw[1].dtd = 0;
	db.draw[0].dtd = 0;
	db.current_buffer = 0;

	PutDispEnv(&db.disp[1]);
	ClearImage(&db.disp[1].disp, 0, 0, 0);

	DrawSync(0);

	//a0 = &db.disp[0];
	ClearImage(&db.disp[0].disp, 0, 0, 0);
	DrawSync(0);

	init_cutseq_malloc();
	s1 = cutseq_malloc(0x3C000);
	sub_2398((char*)s1, a0, 0);

	goto loc_22F4;

	do
	{
		//loc_2290
		if ((RawEdge & 0x80))
		{
			if (s4 < 0)
			{
				s4 = fp;
			}
			else
			{//loc_22B4
				s4--;
			}

			sub_2398((char*)s1, a0, s4);
		}
		//loc_22B4
		//v0 = s4 < fp ? 1 : 0
		if ((RawEdge & 0x20))
		{
			if (s4 < fp)
			{
				s4++;
			}
			else
			{
				s4 = 1;
			}

			//loc_22D4
			sub_2398((char*)s1, a0, s4);

		}//loc_22E4

		DrawSync(0);
		GPU_FlipStory((unsigned long*)s1);

	loc_22F4:
		GPU_BeginScene();
		SetDebounce = 1;
		S_UpdateInput();
		PrintString(256, 220, 6, &gfStringWad[gfStringOffset[STR_PREVIOUS_NEXT_BACK]], 0x8000);

	} while (!(RawEdge & 0x1000));

	DrawSync(0);

#if DEBUG_VERSION
	ProfileDraw = 1;
#endif

	db.draw[1].isbg = 1;
	db.draw[0].isbg = 1;
	db.draw[1].dtd = 1;
	db.draw[0].dtd = 1;
}

void sub_2398(char* gfx, unsigned char wadIndex, int a2)
{
	char buf[12];//var_20
#if PSX_VERSION
#if PSXPC_TEST
	uintptr_t nHandle;//s0
#else
	int nHandle;//s0
#endif
#endif

#if !DISC_VERSION
	sprintf(&buf[0], "\\story%d.wad", wadIndex + 1);
	nHandle = PCopen(&buf[0], 0, 0);
	PClseek(nHandle, a2 * 0x3C000, 0);//0x3C000 storyboard image size
	FILE_Read(gfx, 1, 0x3C000, nHandle);
	PCclose(nHandle);
#endif
}