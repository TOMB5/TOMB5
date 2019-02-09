#include "TITSEQ.H"

#include "EFFECTS.H"
#include "GAMEFLOW.H"
#include "LOADSAVE.H"
#include "MEMCARD.H"
#include "PSXINPUT.H"
#include "SOUND.H"
#include "SPOTCAM.H"
#include "TEXT_S.H"

#if PSX_VERSION && RELOC
void* func_titseq[] __attribute__((section(".header"))) =
{
	&TitleOptions(int Name),
};
#endif

unsigned char byte_46 = 0;
unsigned char byte_47 = 0;

void Test()
{
}

int TitleOptions(int Name)
{
	int a1;
#if DEBUG_VERSION
	char buf[80];//0x18(sp)
#endif
	int ret; //0x68(sp)
	int s1;
	int y;//s3
	//v0 = 0xA0000
	//v1 = PadConnected
	ret = 0;
	//0x98(sp) = Name

	if (PadConnected == 0)
	{
		byte_46 = 0;
		Chris_Menu = 0;
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
		Chris_Menu = 0;
		byte_46 = 0;
		///return sub_1054();
	}//loc_4DC

	//a0 = Chris_Menu
	//v1 = 1
	//s7 = v0
	if (Chris_Menu != 1 && Chris_Menu != 3 && bDoCredits == 0)
	{
		///sub_2B0();
	}
	else
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
	if (Chris_Menu == 1)
	{
		//loc_91C
		s1 = LoadGame();
		if (!s1)
		{
			return 0;
		}

		Chris_Menu = 0;
		byte_46 = 0;

		if (s1 <= 0)
		{
			ret = 2;
			return ret;
		}
	}
	else if (Chris_Menu > 1)
	{
		//loc_5E8
		if (Chris_Menu == 2)
		{
			//loc_948
			//v0 = 0
			//a0 = byte_46
			s1 = byte_46 - 6;
			if (s1 < 0)
			{
				s1 = 0;
			}//loc_964

			if ((RawEdge & 0x10) && byte_46 != 0)
			{
				SoundEffect(SFX_MENU_SELECT, NULL, 2);
				--byte_46;
			}
			else
			{
				//loc_9A4
				if ((RawEdge & 0x40) && byte_46 < Gameflow->nLevels - 2)
				{
					SoundEffect(SFX_MENU_SELECT, NULL, 2);
					++byte_46;
				}
				else
				{
					//loc_9FC
					if ((RawEdge & 0x200))
					{
						byte_46 = Gameflow->nLevels - 2;
					}
					else
					{
						//loc_A30
						if ((RawEdge & 0x100))
						{
							byte_46 = 0;
						}
						else
						{
							if ((RawEdge & 0x800))
							{
								byte_46 = ((Gameflow->nLevels - 2) + ((Gameflow->nLevels - 2) >> 31)) >> 1;
							}
							else
							{
								//loc_A7C
								if ((RawEdge & 0x400))
								{
									byte_47 ^= 1;
								}
							}
						}
					}
				}
			}
			//loc_A98
			//v1 = Gameflow
			//Gameflow->nLevels -1
			//v0 = s1 < v0 ? 1 : 0

			//s4 = 0
			if (s1 < Gameflow->nLevels - 1)
			{
				//s5 = 0x8000
				//s6 = &gfLevelNames
				//s3 = 0x70
				//s2 = 0x70
				//v0 = 0

				//v1 = byte_47
				//t0 = 5
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
					if (byte_46 == s1)
					{
						//a2 = 1
					}//loc_B64

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
			}
			//loc_BD4

			//v1 = RawEdge
			if ((RawEdge & 0x4000))
			{
				SoundEffect(SFX_MENU_CHOOSE, NULL, 2);
				ret = 3;
				Chris_Menu = 0;
				gfLevelComplete = byte_46 + 1;
				byte_46 = 0;
				return ret;
			}
			else if ((RawEdge & 0x1000))
			{
				//loc_C20
				SoundEffect(SFX_MENU_CHOOSE, NULL, 2);
				Chris_Menu = 0;
				return ret;
			}
		}
		else if (Chris_Menu == 3)
		{
			//loc_C3C
			
		}
	}
	else if (Chris_Menu == 0)
	{
		//loc_600
		//v1 = Gameflow
		//s3 = 0xC0
		y = 192;
		if (!Gameflow->LoadSaveEnabled)
		{
			//loc_6B4
			//s1 = a0
			if (CanLoad == 1)
			{
				byte_46 = 0;
				CanLoad = 0;
			}//loc_6D4
		}
		else if (mcGetStatus() != 0)
		{
			//loc_6B8
			if (CanLoad == 1)
			{
				byte_46 = 0;
				CanLoad = 0;
			}//loc_6D4
		}
		else if (mcNumFiles == 0)
		{
			//loc_6B0
			y = 208;
			if (CanLoad == 1)
			{
				byte_46 = 0;
				CanLoad = 0;
			}//loc_6D4
		}
		else if (CanLoad == 0)
		{
			byte_46 = 0;
			CanLoad = 1;
		}//loc_664

		if (byte_46 == 1)
		{
			PrintString(256, 192, 1, &gfStringWad[gfStringOffset[STR_LOAD_GAME_BIS]], 0x8000);
		}
		else
		{
			PrintString(256, 192, 2, &gfStringWad[gfStringOffset[STR_LOAD_GAME_BIS]], 0x8000);
		}

		//j loc_6D8
	}
	else
	{
		return ret;
	}

	//loc_6D8
	if (byte_46 == 0)
	{
		PrintString(256, 176, 1, &gfStringWad[gfStringOffset[STR_SAVE_GAME_BIS]], 0x8000);
	}
	else
	{
		PrintString(256, 176, 2, &gfStringWad[gfStringOffset[STR_SAVE_GAME_BIS]], 0x8000);
	}

	//a0 = 0
	if (byte_46 == 2)
	{
		PrintString(0, y, 1, &gfStringWad[gfStringOffset[STR_SPECIAL_FEATURES]], 0x8000);
	}
	else if (byte_46 == 1)
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
	if ((RawEdge & 0x10) && byte_46 != 0)
	{
		SoundEffect(SFX_MENU_SELECT, NULL, 2);
		--byte_46;
	}
	else if((RawEdge & 0x40) && CanLoad+1 < byte_46)
	{
		//loc_7C0
		SoundEffect(SFX_MENU_SELECT, NULL, 2);
		++byte_46;
	}//loc_810

	if ((RawEdge & 0x4000))
	{
		if (byte_46 == 1)
		{
			//loc_850
			///sub_3A8();
			Chris_Menu = 3;
			byte_46 = 0;
		}
		else
		{
			//loc_86C
			if (byte_46 != 0)
			{
				//loc_8EC
				//sub_3A8();
				Chris_Menu = 0;
				byte_46 = 0;
			}
			else
			{
				if (Gameflow->PlayAnyLevel)
				{
					Chris_Menu = 2;
				}
				else
				{
					//loc_89C
					ret = 3;
					Chris_Menu = 0;
					
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
		}
	}
	else
	{
		//loc_EB4
		return ret;
	}

	//loc_904
	SoundEffect(SFX_MENU_CHOOSE, NULL, 2);

	s1 = LoadGame();

	if (s1 == 0)
	{
		return ret;
	}

	Chris_Menu = 0;
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
