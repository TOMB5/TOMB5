#include "TITSEQ.H"

#include "CD.H"
#include "CONTROL.H"
#include "DELTAPAK.H"
#include "EFFECTS.H"
#include "GAMEFLOW.H"
#include "GPU.H"
#include "LOADSAVE.H"
#include "MEMCARD.H"
#include "MOVIE.H"
#include "PSXINPUT.H"
#include "ROOMLOAD.H"
#include "SAVEGAME.H"
#include "SOUND.H"
#include "SPOTCAM.H"
#include "TEXT_S.H"
#include "MISC.H"

#include <LIBETC.H>
#include <stdio.h>//deleteme
#include "PROFILE.H"

#if! DISC_VERSION
#include <LIBSN.H>
#include "FILE.H"
#else
#include "MOVIE.H"
#endif

#if DEBUG_VERSION
#include <PROFILE.H>
#endif

#define BLOCK_SPLINE_CAM (0)
#define HACK_SAVE_SECRETS (1)

#if PSX_VERSION && RELOC
void* func_titseq[] __attribute__((section(".header"))) =
{
	&TitleOptions,
};

unsigned char titseqData[] __attribute__((section(".data"))) =
{
	0,//byte_46
	0,//byte_47
	0,//byte_1A8
};

unsigned int titseqData2[] __attribute__((section(".data"))) =
{
	0,//word_38
};

#endif

unsigned char byte_46 = 0;
unsigned char byte_47 = 0;
unsigned char byte_1A8 = 0;

#if BETA_VERSON
unsigned short unk_3C[] = { STR_MOVIE_TRAILER, STR_STORYBOARDS_PART_1, STR_NEXT_GENERATION_CONCEPT_ART, STR_STORYBOARDS_PART_2, STR_NEXT_GENERATION_PREVIEW };
#else
unsigned short unk_3C[] = { STR_STORYBOARDS_PART_1, STR_NEXT_GENERATION_CONCEPT_ART, STR_STORYBOARDS_PART_2, STR_NEXT_GENERATION_PREVIEW };
#endif

unsigned int word_38 = 1;
unsigned char byte_2600[] = { 0, 0, 0, 0, 0 }; ///@FIXME i don't know the len (maybe max of byte_46)


struct CutseqMenuItem
{
	unsigned short menuText;
	unsigned char unk00;
	unsigned char unk01;
	unsigned short cutseq;
};

struct CutseqMenuItem unk_1AC[] =
{
{ STR_SEVERAL_HOURS_LATER,0x00, 0x00,0x00 },
{ STR_ANDY4B,0x08, 0x00,0x09 },
{ STR_ANDY11,0x0A, 0x00,0x2C },
{ STR_SWAMPY,0x0A, 0x00,0x2B },
{ STR_MONK2,0x09, 0x00,0x2A },
{ STR_ANDREA4,0x03, 0x00,0x29 },
{ STR_JOBY7,0x06, 0x00,0x28 },
{ STR_ANDY10,0x0A, 0x00,0x27 },
{ STR_ANDY8,0x0A, 0x00,0x26 },
{ STR_ANDY9,0x0A, 0x00,0x25 },
{ STR_COSSACK,0x0A, 0x00,0x24 },
{ STR_JOBY_CUT_2,0x04, 0x00,0x19 },
{ STR_JOBY_CRANE_CUT,0x04, 0x00,0x1B },
{ STR_RICH_CUT_2,0x0D, 0x00,0x1A },
{ STR_RICH_CUT_1,0x0B, 0x00,0x18 },
{ STR_RICH_CUT_3,0x0C, 0x00,0x17 },
{ STR_JOBY_CUT_3,0x04, 0x00,0x16 },
{ STR_ANDY1,0x08, 0x00,0x15 },
{ STR_RICH1,0x0B, 0x00,0x14 },
{ STR_ANDY2,0x08, 0x00,0x13 },
{ STR_JOBY4,0x05, 0x00,0x12 },
{ STR_ANDREA1,0x01, 0x00,0x11 },
{ STR_ANDREA2,0x01, 0x00,0x10 },
{ STR_JOBY5,0x05, 0x00,0x0F },
{ STR_ANDY3,0x08, 0x00,0x0E },
{ STR_JOBY9,0x07, 0x00,0x0D },
{ STR_JOBY10,0x07, 0x00,0x0C },
{ STR_RICHCUT4,0x0B, 0x00,0x0B },
{ STR_ANDY4,0x08, 0x00,0x0A },
{ STR_ANDREA3,0x02, 0x00,0x08 },
{ STR_ANDREA3B,0x02, 0x00,0x07 },
{ STR_ANDY5,0x09, 0x00,0x06 },
{ STR_JOBY6,0x05, 0x00,0x05 },
{ STR_JOBY8,0x07, 0x00,0x20 },
{ STR_ANDY6,0x09, 0x00,0x21 }
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
//	unsigned short* s4;
	int s5 = 0;
//	int s6;
	int s0 = 0;

	ret = 0;

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
		byte_46 = 0;
		Chris_Menu = MENU_MAIN_MENU;
		dels_cutseq_selector_flag = 0;
	}
	//loc_49C
	if (gfGameMode == 2)
	{
		return 0;
	}

	if (dels_cutseq_selector_flag != 0)
	{
		//v1 = 0x00000
		Chris_Menu = MENU_MAIN_MENU;
		byte_46 = 0;
		return sub_1054();
	}//loc_4DC

	if (Chris_Menu != MENU_LOAD_MENU && Chris_Menu != MENU_SPECIAL_FEATURES_MENU)
	{
		if (bDoCredits == 0)
		{
			TITSEQ_DrawLogo();
		}
	}
#if DEBUG_VERSION
	else if (bDoCredits == 0)
	{
		//loc_514
		if (bDoCredits == 0)
		{
			sprintf(&buf[0], "Savegame = %d bytes", 0x3B4);
			PrintString(256, 232, 5, &buf[0], (FF_CENTER | FF_SMALL | FF_UNK6 | FF_UNK5 | FF_UNK2));
		}//loc_558
	}
#endif
	
	//loc_558
	a1 = last_camera;
	if (current_sequence == 2)
	{
		a1 = current_sequence - 1;
	}
	//loc_57C
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
	if (Chris_Menu == MENU_LOAD_MENU)
	{
		//loc_91C
		s1 = LoadGame();

		if (s1 != 0)
		{
			Chris_Menu = MENU_MAIN_MENU;
			byte_46 = 0;
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
		s1 = byte_46 - 6;
		if (s1 < 0)
		{
			s1 = 0;
		}//loc_964

		if ((RawEdge & IN_DPAD_UP) && byte_46 != 0)
		{
			SoundEffect(SFX_MENU_SELECT, NULL, 2);
			--byte_46;
		}
		else if ((RawEdge & IN_DPAD_DOWN) && byte_46 < Gameflow->nLevels - 2)
		{
			SoundEffect(SFX_MENU_SELECT, NULL, 2);
			++byte_46;
		}
#if DEBUG_VERSION
		else if ((RawEdge & IN_R2))
		{
			byte_46 = Gameflow->nLevels - 2;
		}
		else if ((RawEdge & IN_L2))
		{
			byte_46 = 0;
		}
		else if ((RawEdge & IN_R1))
		{
			byte_46 = ((Gameflow->nLevels - 2) + ((Gameflow->nLevels - 2) >> 31)) >> 1;
		}
		else if ((RawEdge & IN_L1))
		{
			byte_47 ^= 1;

		}
#endif
		//loc_A98
		i = 0;

		if (s1 < Gameflow->nLevels - 1)
		{
			//s5 = 0x8000
			//s6 = &gfLevelNames
			y = 0x70;
			//s2 = 0x70
			//v0 = 0

			//v1 = byte_47
			//t0 = 5
			//loc_AD8
			do
			{
#if BETA_VERSION///@TODO
				if (byte_47)
				{
					//a3 = 0
					//v0 = byte_46
					//a1 = s2 & 0xFFFF
					if (byte_46 == s1)
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
					//v0 = byte_46
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
#else
				if (byte_46 == s1)
				{
					PrintString(256, y & 0xFFFF, 1, &gfStringWad[gfStringOffset[gfLevelNames[s1 + 1]]], FF_CENTER);
				}
				else
				{
					PrintString(256, y & 0xFFFF, 5, &gfStringWad[gfStringOffset[gfLevelNames[s1 + 1]]], FF_CENTER);
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
#endif
			} while (++i < 7);
		}
		//loc_BD4, loc_AB4
		if ((RawEdge & IN_CROSS))
		{
			SoundEffect(SFX_MENU_CHOOSE, NULL, 2);
			ret = 3;
			Chris_Menu = MENU_MAIN_MENU;
			gfLevelComplete = byte_46 + 1;
			byte_46 = 0;
		}
		else if ((RawEdge & IN_TRIANGLE))
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
		s1 = 0;
		s5 = 0;

#if !BETA_VERSION
		PrintString(256, 232, 5, &gfStringWad[gfStringOffset[STR_CANCEL]], FF_CENTER);
#endif
		PrintString(256, 32, 6, &gfStringWad[gfStringOffset[STR_SPECIAL_FEATURES]], FF_CENTER);

		//loc_C8C
#if BETA_VERSION
		for (s1 = 0; s1 < 5; s1++)
#else
		for (s1 = 0; s1 < 4; s1++)
#endif
		{
			if (s1 != 0)
			{
#if !BETA_VERSION
				if (savegame.CampaignSecrets[s1] < 9)
#else
				if (savegame.CampaignSecrets[s1 - 1] < 9)
#endif
				{
					//loc_DDC
					continue;
				}
			}

			//loc_CA8
			y = (s5 - ((word_38 * 12) + 0x70)) & 0xFF;

			if (byte_46 == s1)
			{
				PrintString(256, y + 4, 1, &gfStringWad[gfStringOffset[unk_3C[s1]]], FF_CENTER);
			}
			else
			{
				PrintString(256, y + 4, 2, &gfStringWad[gfStringOffset[unk_3C[s1]]], FF_CENTER);
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
		}

		if ((RawEdge & IN_DPAD_UP) && byte_46 != 0)
		{
#if !BETA_VERSION
			SoundEffect(SFX_MENU_SELECT, NULL, 2);
#endif
			--byte_46;
		}
		else if ((RawEdge & IN_DPAD_DOWN) && byte_46 < word_38 - 1)
		{
#if !BETA_VERSION
			SoundEffect(SFX_MENU_SELECT, NULL, 2);
#endif
			++byte_46;
		}
		else if ((RawEdge & IN_TRIANGLE))
		{
#if !BETA_VERSION
			SoundEffect(SFX_MENU_CHOOSE, NULL, 2);
#endif
			Chris_Menu = MENU_MAIN_MENU;
			byte_46 = CanLoad + 1;
		}
		else if ((RawEdge & IN_CROSS))
		{
#if !BETA_VERSION
			SoundEffect(SFX_MENU_CHOOSE, NULL, 2);
#endif
			sub_2154(Name, byte_2600[byte_46]);
		}

		return ret;
	}
	else if (Chris_Menu == MENU_MAIN_MENU)
	{
		//loc_600
#if !BETA_VERSION
		s0 = 1;
		if (savegame.CampaignSecrets[0] != 9 && savegame.CampaignSecrets[1] != 9 &&
			savegame.CampaignSecrets[2] != 9 && savegame.CampaignSecrets[3] != 9)
		{
			s0 = 0;
		}
		else
		{
			s0 = 1;
		}
#endif
		//loc_5EC
		if (!Gameflow->LoadSaveEnabled)
		{
			y = 192;
			//loc_6A0
			if (CanLoad == 1)
			{
				byte_46 = 0;
				CanLoad = 0;
			}//loc_6C4
		}
		else if (mcGetStatus() != 0)
		{
			y = 192;
			//loc_6A4
			if (CanLoad == 1)
			{
				byte_46 = 0;
				CanLoad = 0;
			}//loc_6C4
		}
		else if (mcNumFiles == 0)
		{
			y = 208;
			//loc_6A0
			if (CanLoad == 1)
			{
				byte_46 = 0;
				CanLoad = 0;
			}//loc_6C4
		}
		else if (CanLoad)
		{
			y = 208;

			//loc_658
			if (byte_46 == 1)
			{
				PrintString(256, 192, 1, &gfStringWad[gfStringOffset[STR_LOAD_GAME_BIS]], FF_CENTER);
			}
			else
			{
				PrintString(256, 192, 2, &gfStringWad[gfStringOffset[STR_LOAD_GAME_BIS]], FF_CENTER);
			}
		}
		else
		{
			y = 192;
			byte_46 = 0;
			CanLoad = 1;
		}
	}
	else
	{
		return ret;
	}

	//loc_6D8
	if (byte_46 == 0)
	{
		PrintString(256, 176, 1, &gfStringWad[gfStringOffset[STR_SAVE_GAME_BIS]], FF_CENTER);
	}
	else
	{
		PrintString(256, 176, 2, &gfStringWad[gfStringOffset[STR_SAVE_GAME_BIS]], FF_CENTER);
	}

	if (s0)
	{
		if (byte_46 == 2)
		{
			PrintString(256, y, 1, &gfStringWad[gfStringOffset[STR_SPECIAL_FEATURES]], FF_CENTER);
		}
		else if (byte_46 != 1)
		{
			PrintString(256, y, 2, &gfStringWad[gfStringOffset[STR_SPECIAL_FEATURES]], FF_CENTER);
		}
		else if (CanLoad != 0)
		{
			PrintString(256, y, 2, &gfStringWad[gfStringOffset[STR_SPECIAL_FEATURES]], FF_CENTER);
		}
		else
		{
			PrintString(256, y, 1, &gfStringWad[gfStringOffset[STR_SPECIAL_FEATURES]], FF_CENTER);
		}
	}//loc_764

	if ((RawEdge & IN_DPAD_UP) && byte_46 != 0)
	{
		SoundEffect(SFX_MENU_SELECT, NULL, 2);
		--byte_46;
	}//loc_7C0
	else if((RawEdge & IN_DPAD_DOWN) && byte_46 < CanLoad + 1)
	{
		//loc_7C0
		SoundEffect(SFX_MENU_SELECT, NULL, 2);
		++byte_46;
	}//loc_810

	if ((RawEdge & IN_CROSS))
	{
		if (byte_46 == 1)
		{
			if (CanLoad != 0)
			{
				Chris_Menu = MENU_LOAD_MENU;
			}
			else
			{
				//loc_850
				TITSEQ_CheckSecretsCollected();
				Chris_Menu = MENU_SPECIAL_FEATURES_MENU;
				byte_46 = 0;
			}
			
			//loc_904
			SoundEffect(SFX_MENU_CHOOSE, NULL, 2);
		}//loc_86C
		else
		{
			//loc_86C
			if (byte_46 != 0)
			{
				//loc_8EC
				TITSEQ_CheckSecretsCollected();
				Chris_Menu = MENU_SPECIAL_FEATURES_MENU;
				byte_46 = 0;
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
					
					if ((RawPad & IN_L1))
					{
						gfLevelComplete = 4;
					}
					else
					{
						gfLevelComplete = 1;
					}

					//loc_8C8
					if ((RawPad & IN_L2))
					{
						gfLevelComplete = 8;
					}

					if ((RawPad & IN_R1))
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

	s1 = LoadGame();

	if (s1 == 0)
	{
		return ret;
	}

	Chris_Menu = MENU_MAIN_MENU;
	byte_46 = 0;

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

void TITSEQ_DrawLogo()//2B0(<) 29C(<) (F)
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

void TITSEQ_CheckSecretsCollected()//3A8(<) 394(<) (F)
{
	int i = 0;

#if BETA_VERSION
	word_38 = 1;
#else
	word_38 = 0;
#endif

	byte_2600[0] = 0;
	byte_2600[1] = 0;
	byte_2600[2] = 0;
	byte_2600[3] = 0;
#if BETA_VERSION
	byte_2600[4] = 0;
#endif

	//loc_3D8:
	do
	{
		if (savegame.CampaignSecrets[i] > 8)
		{
			byte_2600[i + 1] = i + 1;
			word_38++;
		}
		//loc_414
	} while (++i < 4);
}

int sub_1054()//1054(<) F98(<)
{
	int i;
	int a3 = 0;
	int y = 0;//s1
	int ret = 0;//fp

	TITSEQ_DrawLogo();
	PrintString(256, 102, 6, &gfStringWad[gfStringOffset[STR_SELECT_CUTSCENE]], FF_CENTER);

	a3 = byte_1A8 - 4;
	if ((byte_1A8 - 4) < 0)
	{
		a3 = 0;
	}
	//loc_10DC

	if ((RawEdge & IN_DPAD_UP) && byte_1A8 != 0)
	{
		--byte_1A8;
	}
	else if ((RawEdge & IN_DPAD_DOWN) && byte_1A8 < 35)
	{
		++byte_1A8;
	}

	i = 0;
	//loc_1128
	if ((byte_1A8 - 4) < 36)
	{
		y = 136;
		//loc_1144
		do
		{
			if (byte_1A8 == a3)
			{
				PrintString(256, y, 1, &gfStringWad[gfStringOffset[unk_1AC[a3 + 1].menuText]], FF_CENTER);
			}
			else
			{
				PrintString(256, y, 5, &gfStringWad[gfStringOffset[unk_1AC[a3 + 1].menuText]], FF_CENTER);
			}

			y += 18;

			if (a3 + 1 > 0x23)
			{
				break;
			}

			a3++;
		} while (++i < 5);

	}//loc_11B8

	if ((RawEdge & IN_CROSS))
	{
		SoundEffect(SFX_MENU_CHOOSE, NULL, 2);
		ret = 3;
		dels_cutseq_selector_flag = 0;
		cutrot = 0;
		gfLevelComplete = unk_1AC[byte_1A8 + 1].unk00;
		dels_cutseq_player = unk_1AC[byte_1A8 + 1].cutseq;
		byte_1A8 = 0;
	}//loc_1240

	if ((RawEdge & IN_TRIANGLE))
	{
		dels_cutseq_selector_flag = 0;
	}

	return ret;
}

void sub_2154(int Name, unsigned char a1)//2154(<) 2098(<) (F)
{
#if !BETA_VERSION
	if (a1 == 3)
	{
		DrawSync(0);
		ClearOTagR(db.order_table[0], db.nOTSize);
		ClearOTagR(db.order_table[1], db.nOTSize);
		DrawSync(0);

#if DISC_VERSION
		S_PlayFMV(FMV_NEXT_GENERATION_PREVIEW, 1);
#endif

		ReloadAnims(Name, cutseq_malloc_free);
		S_CDPlay(XATrack, 0);
	}
	else
	{
		//loc_2130
		DrawSync(0);
		ClearOTagR(db.order_table[0], db.nOTSize);
		ClearOTagR(db.order_table[1], db.nOTSize);
		DrawSync(0);

		TITSEQ_StoryBoardMenuControl(a1);//-1?
		ReloadAnims(Name, cutseq_malloc_free);
		S_CDPlay(XATrack, 0);
	}
	//loc_218C
#else
	if (a1 != 0 && a1 != 4)
	{
		TITSEQ_StoryBoardMenuControl(a1 - 1);
		ReloadAnims(Name, cutseq_malloc_used);
	}//loc_218C
#endif
}

void TITSEQ_StoryBoardMenuControl(unsigned char extrasMenuIndex)//219C(<), 21A8(<) (F)
{
	void* gfx;//$s1
	int maxNumberOfImages;//$fp
	int currentlySelectedImage;//$s4

	maxNumberOfImages = 12;
	if (extrasMenuIndex == 1)
	{
		maxNumberOfImages = 15;
	}

	//loc_21DC
	currentlySelectedImage = 0;

#if DEBUG_VERSION
	ProfileDraw = 0;
#endif

	DrawSync(0);
	VSync(0);

	db.draw[1].isbg = 0;
	db.draw[0].isbg = 0;
	db.draw[1].dtd = 0;
	db.draw[0].dtd = 0;
	db.current_buffer = 0;

	PutDispEnv(&db.disp[1]);
	ClearImage(&db.disp[1].disp, 0, 0, 0);

	DrawSync(0);
	ClearImage(&db.disp[0].disp, 0, 0, 0);
	DrawSync(0);

	init_cutseq_malloc();
	gfx = cutseq_malloc(STORY_BOARD_IMG_SIZE);
	TITSEQ_ReadStoryboardImage((char*)gfx, extrasMenuIndex, 0);

	goto loc_22F4;

	do
	{
		//loc_2290
		if ((RawEdge & IN_DPAD_LEFT))
		{
			if (currentlySelectedImage < 0)
			{
				currentlySelectedImage = maxNumberOfImages;
			}
			else
			{
				//loc_22B4
				currentlySelectedImage--;
			}

			TITSEQ_ReadStoryboardImage((char*)gfx, extrasMenuIndex, currentlySelectedImage);
#if !BETA_VERSION
			SoundEffect(SFX_MENU_CHOOSE, NULL, 2);
#endif
		}
		//loc_22B4
		if ((RawEdge & IN_DPAD_RIGHT))
		{
			if (currentlySelectedImage < maxNumberOfImages)
			{
				currentlySelectedImage++;
			}
			else
			{
				currentlySelectedImage = 1;
			}

			//loc_22D4
			TITSEQ_ReadStoryboardImage((char*)gfx, extrasMenuIndex, currentlySelectedImage);

#if !BETA_VERSION
			SoundEffect(SFX_MENU_CHOOSE, NULL, 2);
#endif
		}
		
		//loc_22E4
		DrawSync(0);
		GPU_FlipStory((unsigned long*)gfx);

	loc_22F4:
		GPU_BeginScene();
		SetDebounce = 1;
		S_UpdateInput();
		PrintString(256, 220, 6, &gfStringWad[gfStringOffset[STR_PREVIOUS_NEXT_BACK]], FF_CENTER);

	} while (!(RawEdge & IN_TRIANGLE));

#if !BETA_VERSION
	SoundEffect(SFX_MENU_CHOOSE, NULL, 2);
#endif

	DrawSync(0);

#if DEBUG_VERSION
	ProfileDraw = 1;
#endif

	db.draw[1].isbg = 1;
	db.draw[0].isbg = 1;
	db.draw[1].dtd = 1;
	db.draw[0].dtd = 1;
}

void TITSEQ_ReadStoryboardImage(char* gfx, unsigned char wadIndex, int imageIndex)//2398(<) 23C4(<) (F)
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
	PClseek(nHandle, imageIndex * STORY_BOARD_IMG_SIZE, 0);
	FILE_Read(gfx, 1, STORY_BOARD_IMG_SIZE, nHandle);
	PCclose(nHandle);
#else
	DEL_CDFS_OpenFile(wadIndex + STORY_1);
	DEL_CDFS_Seek(imageIndex * STORY_BOARD_IMG_SIZE);
	DEL_CDFS_Read(gfx, STORY_BOARD_IMG_SIZE);
#endif
}