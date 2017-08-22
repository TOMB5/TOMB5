#include "DELTAPAK.H"

#include "CD.H"
#include "CONTROL.H"
#include "DRAW.H"
#include "GAMEFLOW.H"
#include "ITEMS.H"
#include "LARA.H"
#include "OBJECTS.H"
#include "SETUP.H"
#include "SPECIFIC.H"
#include "SPOTCAM.H"
#include "TOMB4FX.H"

#include <assert.h>
#include <stddef.h>

struct CUTSEQ_ROUTINES cutseq_control_routines[45] =
{
	{ NULL, NULL, NULL },
	{ stealth3_start, NULL, stealth3_end },
	{ stealth3_start, NULL, stealth3_end },
	{ stealth3_start, NULL, stealth3_end },
	{ stealth3_start, NULL, stealth3_end },
	{ joby6_init, joby6_control, joby6_end },
	{ andy5_init, andy5_control, andy5_end },
	{ andrea3b_init, andrea3b_control, andrea3b_end },
	{ andrea3_init, andrea3_control, andrea3_end },
	{ andy4b_init, andy4b_control, andy4b_end },
	{ andy4_init, andy4_control, andy4_end },
	{ richcut4_init, richcut4_control, richcut4_end },
	{ joby10_init, joby10_control, joby10_end },
	{ joby9_init, joby9_control, joby9_end },
	{ andy3_init, andy3_control, andy3_end },
	{ joby5_init, joby5_control, joby5_end },
	{ andrea2_init, andrea2_control, andrea2_end },
	{ andrea1_init, andrea1_control, andrea1_end },
	{ joby4_init, joby4_control, joby4_end },
	{ andy2_init, andy2_control, andy2_end },
	{ hamgate_init, hamgate_control, hamgate_end },
	{ andy1_init, andy1_control, andy1_end },
	{ joby3_init, joby3_control, joby3_end },
	{ richcut3_init, richcut3_control, richcut3_end },
	{ richcut1_init, richcut1_control, richcut1_end },
	{ joby2_init, joby2_control, joby2_end },
	{ richcut2_init, richcut2_control, richcut2_end },
	{ cranecut_init, cranecut_control, cranecut_end },
	{ special1_init, special1_control, special1_end },
	{ special2_init, special2_control, special2_end },
	{ special3_init, special3_control, special3_end },
	{ special4_init, special4_control, special4_end },
	{ joby8_init, joby8_control, joby8_end },
	{ andy6_init, andy6_control, andy6_end },
	{ andypew_init, andypew_control, andypew_end },
	{ andy7_init, andy7_control, andy7_end },
	{ cossack_init, cossack_control, cossack_end },
	{ andy9_init, andy9_control, andy9_end },
	{ andy8_init, andy8_control, andy8_end },
	{ andy10_init, andy10_control, andy10_end },
	{ joby7_init, joby7_control, joby7_end },
	{ andrea4_init, andrea4_control, andrea4_end },
	{ monk2_init, monk2_control, monk2_end },
	{ swampy_init, swampy_control, swampy_end },
	{ andy11_init, andy11_control, andy11_end },
};
unsigned short crane_pistols_info[11] =
{
	0x8035, 0x3D80, 0x803D, 0xC580, 0x81C5, 0xCF81, 0x81CF, 0xEA81, 0x81EA, 0x3181, 
	0x4031
};
unsigned short craneguard_pistols_info[7] =
{
	0x006A, 0x7500, 0x0075, 0xF000, 0x00F0, 0xF700, 0x00F7
};
short admiral_chat_ranges_joby2[12] =
{
	0x0118, 0x5401, 0x0154, 0x5C01, 0x015C, 0x7501, 0x0175, 0x7C01, 0x017C, 0x9D01, 
	0x019D, 0xCF01
};
short sergie_chat_ranges_joby2[8] =
{
	0x01B9, 0xB801, 0x02B8, 0x8602, 0x0386, 0x1E03, 0x041E, 0xA204
};
short lara_chat_ranges_joby3[6] =
{
	0x052B, 0x3005, 0x0530, 0x3D05, 0x053D, 0x5605
};
short lara_chat_ranges_joby4[10] =
{
	0x0244, 0x6702, 0x0267, 0x7902, 0x0279, 0x0202, 0x0302, 0x4F03, 0x074F, 0x8607
};
short admiral_chat_ranges_joby4[20] =
{
	0x012D, 0x8701, 0x0187, 0x9301, 0x0193, 0x0301, 0x0203, 0x0F02, 0x030F, 0x3003, 
	0x0330, 0x3C03, 0x033C, 0x0403, 0x0404, 0x0E04, 0x040E, 0xE604, 0x04E6, 0xF104
};
unsigned short larson_pistols_info1[2] =
{
	0x0390, 0xFF03
};
short lara_chat_ranges_andrea1[4] =
{
	0x0248, 0x7902, 0x0279, 0xFF02
};
short larson_chat_ranges1[12] =
{
	0x03AF, 0xCB03, 0x03CB, 0xAC03, 0x04AC, 0xC904, 0x04C9, 0xDE04, 0x04DE, 0x1604, 
	0x0516, 0xEC05
};
short pierre_chat_ranges1[30] =
{
	0x02B8, 0xC402, 0x02C4, 0xD502, 0x02D5, 0xE802, 0x02E8, 0xEB02, 0x03EB, 0xFC03, 
	0x03FC, 0x1403, 0x0414, 0x2304, 0x0423, 0x3804, 0x0438, 0x9904, 0x0499, 0x2A04, 
	0x052A, 0x6C05, 0x056C, 0x7805, 0x0578, 0xC005, 0x05C0, 0x1B05, 0x061B, 0x3006
};
short lara_chat_ranges_andrea2[32] =
{
	0x03D6, 0xE603, 0x03E6, 0xEF03, 0x03EF, 0x0103, 0x0401, 0xB104, 0x05B1, 0xE605, 
	0x05E6, 0x7B05, 0x077B, 0xAE07, 0x07AE, 0xBA07, 0x07BA, 0xF507, 0x07F5, 0x0307, 
	0x0803, 0x1708, 0x0817, 0x8108, 0x0881, 0xD108, 0x08D1, 0xDE08, 0x08DE, 0xFD08,
	0x08FD, 0x0B08
};
short larson_chat_ranges2[8] =
{
	0x01C2, 0x5501, 0x0255, 0xDE02, 0x04DE, 0x3304, 0x0533, 0x2A05
};
short pierre_chat_ranges2[34] =
{
	0x00F2, 0x2100, 0x0121, 0x2E01, 0x012E, 0x5501, 0x0155, 0x4801, 0x0348, 0x5203, 
	0x0352, 0x5F03, 0x035F, 0xB203, 0x03B2, 0x1B03, 0x041B, 0x2704, 0x0427, 0x3A04, 
	0x043A, 0x7F04, 0x047F, 0x8F04, 0x048F, 0xC704, 0x04C7, 0x4704, 0x0647, 0x5C06, 
	0x065C, 0x6F06, 0x066F, 0x7D06
};
short admiral_chat_ranges_joby5[18] =
{
	0x01EB, 0x4201, 0x0242, 0x6902, 0x0369, 0x5903, 0x0459, 0xDC04, 0x04DC, 0x0504, 
	0x0505, 0x1805, 0x0518, 0x2905, 0x0529, 0x3505, 0x0535, 0xEE05
};
short sergie_chat_ranges_joby5[20] =
{
	0x009C, 0xB900, 0x00B9, 0xC200, 0x00C2, 0x8B00, 0x018B, 0x9C01, 0x019C, 0xCD01, 
	0x01CD, 0x5A01, 0x025A, 0x4902, 0x0349, 0x6903, 0x0469, 0x8004, 0x0480, 0x9204
};
short lara_chat_ranges_joby9[12] =
{
	0x0282, 0x0C02, 0x030C, 0x8A03, 0x058A, 0xA605, 0x05A6, 0xB105, 0x05B1, 0xDB05, 
	0x05DB, 0xE605
};
short admiral_chat_ranges_joby9[36] =
{
	0x00B6, 0x5B00, 0x015B, 0x7701, 0x0177, 0x5801, 0x0258, 0x3A02, 0x033A, 0xF503, 
	0x04F5, 0x0904, 0x0509, 0x2D05, 0x052D, 0x3C05, 0x053C, 0x4D05, 0x054D, 0x5A05, 
	0x055A, 0x7F05, 0x057F, 0xA305, 0x06A3, 0xD206, 0x06D2, 0xE006, 0x06E0, 0x6E06, 
	0x076E, 0x7E07, 0x077E, 0xA407, 0x07A4, 0xB607
};
short lara_chat_ranges_joby10[12] =
{
	0x01ED, 0x0C01, 0x020C, 0x1402, 0x0514, 0x2F05, 0x052F, 0x6905, 0x0769, 0x8D07, 
	0x078D, 0xD907
};
short admiral_chat_ranges_joby10[42] =
{
	0x0091, 0xA300, 0x00A3, 0xD000, 0x00D0, 0xF000, 0x00F0, 0xFB00, 0x00FB, 0x2900, 
	0x0129, 0x3401, 0x0134, 0x6601, 0x0166, 0x7401, 0x0174, 0xBD01, 0x01BD, 0xC801, 
	0x01C8, 0xD501, 0x01D5, 0x2201, 0x0222, 0x3102, 0x0331, 0x4003, 0x0340, 0x9803, 
	0x0398, 0xA703, 0x03A7, 0xFD03, 0x04FD, 0x3904, 0x0539, 0x6305, 0x0563, 0x7005, 
	0x0570, 0x0F05
};
unsigned short andrea3_pistols_info[5] =
{
	0x454B, 0x4E45, 0x854E, 0x5785, 0x8557
};
short lara_chat_ranges_andrea3[14] =
{
	0x0028, 0x5E00, 0x005E, 0x0400, 0x0104, 0x4101, 0x0141, 0xAC01, 0x01AC, 0xBF01, 
	0x01BF, 0xE301, 0x01E3, 0x0F01
};
short larson_chat_ranges3[14] =
{
	0xA603, 0x17A6, 0x5817, 0x0058, 0x0C00, 0x210C, 0x2821, 0x2028, 0x0220, 0x1802, 
	0x0018, 0xBF00, 0x8FBF, 0x148F
};
short lara_chat_ranges_andrea3b[12] =
{
	0x020A, 0x1B02, 0x021B, 0x2302, 0x0223, 0x3802, 0x0238, 0xBE02, 0x02BE, 0xE002, 
	0x02E0, 0xE902
};
short larson_chat_ranges3b[4] =
{
	0x0254, 0xAD02, 0x02AD, 0xFF02
};
short priest_chat_ranges_andy7[32] =
{
	0x0003, 0x1800, 0x0018, 0x2300, 0x0023, 0x7400, 0x0074, 0x8800, 0x0088, 0xA700, 
	0x00A7, 0xBB00, 0x00BB, 0x0F00, 0x010F, 0x1A01, 0x011A, 0x5901, 0x0159, 0xC901, 
	0x01C9, 0xFC01, 0x01FC, 0x0801, 0x0208, 0x3402, 0x0234, 0x8602, 0x0286, 0xD202, 
	0x02D2, 0x1002
};
short lara_chat_ranges_andy7[14] =
{
	0x017D, 0x8901, 0x0189, 0x9501, 0x0195, 0xBE01, 0x01BE, 0x3E01, 0x023E, 0x6D02,
	0x026D, 0xEA02, 0x02EA, 0x0702
};
short lara_chat_ranges_joby7[10] =
{
	0x02D5, 0xF702, 0x02F7, 0x0D02, 0x030D, 0x3903, 0x0339, 0xCD03, 0x05CD, 0xDD05
};
short lara_chat_ranges_andrea4[22] =
{
	0x01C9, 0x1C01, 0x021C, 0xB102, 0x03B1, 0xFF03, 0x03FF, 0x4B03, 0x064B, 0x7706, 
	0x0677, 0x8606, 0x0686, 0x9406, 0x0694, 0x9D06, 0x069D, 0xBE06, 0x06BE, 0x4306,
	0x0843, 0x6708
};
short pierre_chat_ranges4[48] =
{
	0x014E, 0x5B01, 0x015B, 0x6801, 0x0168, 0xA801, 0x01A8, 0x2E01, 0x022E, 0x5802,
	0x0258, 0x6702, 0x0267, 0x0402, 0x0304, 0x1503, 0x0315, 0x8A03, 0x038A, 0x2403, 
	0x0424, 0x2D04, 0x042D, 0x3904, 0x0439, 0x5C04, 0x045C, 0x6E04, 0x046E, 0xDE04,
	0x04DE, 0xEC04, 0x04EC, 0x0404, 0x0504, 0x1105, 0x0511, 0x2B05, 0x052B, 0x3C05, 
	0x053C, 0x6A05, 0x056A, 0x7E05, 0x057E, 0xF505, 0x05F5, 0x0F05
};
int cuntercunter;
char jobyfrigger;
int cutrot;
int GLOBAL_playing_cutseq;
int cutseq_trig;
int cutseq_num;
unsigned char disable_horizon;
char cutseq_busy_timeout;
short frig_shadow_bbox[6] =
{
	0xFF5B, 0x96FF, 0x0096, 0xF700, 0xFCF7, 0x01FC
};
int cut_seethrough;
char lara_chat_cnt;
char actor_chat_cnt;
struct NEW_CUTSCENE* GLOBAL_cutme;
int lastcamnum;
int GLOBAL_cutseq_frame;
int GLOBAL_numcutseq_frames;
int GLOBAL_oldcamtype;
struct PACKNODE* camera_pnodes;
struct PACKNODE* actor_pnodes[10];
struct ITEM_INFO duff_item;
int numnailed;
char old_status_flags[32];
unsigned short old_status_flags2[32];
unsigned long cutseq_meshbits[10];
unsigned long cutseq_meshswapbits[10];
struct RESIDENT_THING cutseq_resident_addresses[47];
char* GLOBAL_resident_depack_buffers;
int cutseq_malloc_used;
char* cutseq_malloc_ptr;
int cutseq_malloc_free;
unsigned short old_lara_holster;
short temp_rotation_buffer[160];

#define WORLD_UNITS_PER_SECTOR 1024
#define SECTOR_TO_WORLD(S) ((S) > (0) ? ((S * WORLD_UNITS_PER_SECTOR) + (WORLD_UNITS_PER_SECTOR / 2)) : (0))

enum title_spotcam_sequences
{
	FIRST,
	OUTSIDE_CHURCH_SEQUENCE,
	INSIDE_CHURCH_SEQUENCE,
	HOUSE_SEQUENCE,
	PYRAMID_SEQUENCE
};

void andy11_end()//32D6C, 3326C
{
	S_Warn("[andy11_end] - Unimplemented!\\n");
}

void andy11_control()//32C70, 33108
{
	S_Warn("[andy11_control] - Unimplemented!\\n");
}

void andy11_init()//32C20, 330B8
{
	S_Warn("[andy11_init] - Unimplemented!\\n");
}

void Cutanimate(int objnum)
{
	S_Warn("[Cutanimate] - Unimplemented!\\n");
}


struct ITEM_INFO* ResetCutanimate(int objnum)//32A80, 32F18
{
#if 1
	struct ITEM_INFO* item; // $s1

	item = find_a_fucking_item(objnum);

	item->anim_number = *(short*)&objects[(objnum << 6) + 38];//0x237, basically objects[objnum]+38
	item->frame_number = anims[item->anim_number].frame_base;
	RemoveActiveItem(item - items);

	item->flags &= 0xC1FF;
#if 0
	int test = *(int*)item->active;
	test &= -7;
	*(int*)item->active = test;
#endif
#endif
	return item;
}

void trigger_title_spotcam(int num)//32904(<), 32D9C(<)
{
	struct ITEM_INFO* item;

	jobyfrigger = 0;

	if (num == OUTSIDE_CHURCH_SEQUENCE)
	{
		/*
		 * Resetting all outside church sequence animatings to their original position & animation.
		 */
		//Man holding umbrella at church area (TITLE.TRC)
		item = ResetCutanimate(ANIMATING10);
		item->pos.x_pos = SECTOR_TO_WORLD(58);
		item->pos.y_pos = SECTOR_TO_WORLD(0);
		item->pos.z_pos = SECTOR_TO_WORLD(41);
		item->room_number = 0;

		//Female walking with man holding umbrella, church area (TITLE.TRC)
		item = ResetCutanimate(ANIMATING11);
		item->pos.x_pos = SECTOR_TO_WORLD(58);
		item->pos.y_pos = SECTOR_TO_WORLD(0);
		item->pos.z_pos = SECTOR_TO_WORLD(41);
		item->room_number = 0;

	}
	else if (num == PYRAMID_SEQUENCE)
	{
		/*
		 * Resetting all pyramid sequence animatings to their original positions/animations.
		 */
		jobyfrigger = 1;

		//Stone slab being pulled on slope outside pyramid entrance.
		ResetCutanimate(ANIMATING4);

		//Jeep
		item = ResetCutanimate(ANIMATING7);
		item->pos.x_pos = SECTOR_TO_WORLD(31);
		item->pos.y_pos = SECTOR_TO_WORLD(0);
		item->pos.z_pos = SECTOR_TO_WORLD(88);
		item->room_number = 104;

		//Jeep
		ResetCutanimate(ANIMATING8);

		//Tomb Raider 4 Guide
		item = ResetCutanimate(ANIMATING9);
		item->pos.x_pos = SECTOR_TO_WORLD(30);
		item->pos.y_pos = SECTOR_TO_WORLD(0);
		item->pos.z_pos = SECTOR_TO_WORLD(89);
		item->room_number = 61;

		//Voncroy
		ResetCutanimate(ANIMATING12);

		//Tomb Raider 4 guides pulling stone slab (ANIMATING4).
		ResetCutanimate(ANIMATING13);
		ResetCutanimate(ANIMATING14);
		ResetCutanimate(ANIMATING15);

	}//0x32A00

	/*
	 * Each flyby sequence should play it's own unique music.
	 * Here we alter the music for the current flyby sequence.
	 */
	if (num == OUTSIDE_CHURCH_SEQUENCE)
	{
#ifdef INTERNAL//second arg is prob a def.
		S_CDPlay(83, 1);
#else
		S_CDPlay(83, 0);
#endif
	}
	else if (num == INSIDE_CHURCH_SEQUENCE)
	{
#ifdef INTERNAL
		S_CDPlay(87, 1);
#else
		S_CDPlay(87, 0);
#endif
	}
	else if (num == HOUSE_SEQUENCE)
	{
#ifdef INTERNAL
		S_CDPlay(86, 1);
#else
		S_CDPlay(86, 0);
#endif
	}
	else if (num == PYRAMID_SEQUENCE)
	{
#ifdef INTERNAL
		S_CDPlay(91, 1);
#else
		S_CDPlay(91, 0);
#endif
	}

	InitialiseSpotCam(num);

}//32968

void CutLaraBubbles()
{
	S_Warn("[CutLaraBubbles] - Unimplemented!\\n");
}

void swampy_end()//3271C, 32BB4
{
	S_Warn("[swampy_end] - Unimplemented!\\n");
}

void swampy_control()//326EC, 32B84
{
	S_Warn("[swampy_control] - Unimplemented!\\n");
}

void swampy_init()//32608, 32AA0
{
	S_Warn("[swampy_init] - Unimplemented!\\n");
}

void monk2_end()//325F4(<), 32A8C(<) (F)
{
	lara_item->mesh_bits = 0xFFFFFFFF;
}

void monk2_control()//324E4, 3297C
{
	S_Warn("[monk2_control] - Unimplemented!\\n");
}

void monk2_init()//324D4(<), 3296C(<) (F)
{
	cutrot = 1;
}

void do_pierre_gun_meshswap()
{
	S_Warn("[do_pierre_gun_meshswap] - Unimplemented!\\n");
}

void andrea4_end()//32464, 328FC
{
	S_Warn("[andrea4_end] - Unimplemented!\\n");
}

void andrea4_control()//323C8, 32860
{
	S_Warn("[andrea4_control] - Unimplemented!\\n");
}

void andrea4_init()//323C0(<), 32858(<) (F)
{
}

void joby7_end()
{
	S_Warn("[joby7_end] - Unimplemented!\\n");
}

void joby7_control()
{
	S_Warn("[joby7_control] - Unimplemented!\\n");
}

void joby7_init()
{
	S_Warn("[joby7_init] - Unimplemented!\\n");
}

void andy10_end()//3202C, 324C4
{
	S_Warn("[andy10_end] - Unimplemented!\\n");
}

void andy10_control()//31E9C, 32334
{
	S_Warn("[andy10_control] - Unimplemented!\\n");
}

void andy10_init()//31D58, 321F0
{
	S_Warn("[andy10_init] - Unimplemented!\\n");
}

void do_chalk_meshswap()
{
	S_Warn("[do_chalk_meshswap] - Unimplemented!\\n");
}

void andy8_end()//31CF8, 32190
{
	S_Warn("[andy8_end] - Unimplemented!\\n");
}

void andy8_control()//31C3C, 320D4
{
	S_Warn("[andy8_control] - Unimplemented!\\n");
}

void andy8_init()//31C34(<), 320CC(<) (F)
{
}

void andy9_end()//31C08, 320A0
{
	S_Warn("[andy9_end] - Unimplemented!\\n");
}

void andy9_control()//31BA4, 31FD4
{
	S_Warn("[andy9_control] - Unimplemented!\\n");
}

void andy9_init()//31B7C, 31FAC
{
	S_Warn("[andy9_init] - Unimplemented!\\n");
}

void TriggerDelBrownSmoke(long x, long y, long z)
{
	S_Warn("[TriggerDelBrownSmoke] - Unimplemented!\\n");
}

void cossack_end()//31998, 31DC8
{
	S_Warn("[cossack_end] - Unimplemented!\\n");
}

void cossack_control()//3178C, 31BBC
{
	S_Warn("[cossack_control] - Unimplemented!\\n");
}

void cossack_init()//31784(<), 31BB4(<) (F)
{
	return;
}

void andy7_end()//31754, 31B84
{
	S_Warn("[andy7_end] - Unimplemented!\\n");
}

void andy7_control()//31704, 31B34
{
	S_Warn("[andy7_control] - Unimplemented!\\n");
}

void andy7_init()//316F4(<), 31B24(<) (F)
{
	cutrot = 1;
}

void andypew_end()//316C0, 31AF0
{
	S_Warn("[andypew_end] - Unimplemented!\\n");
}

void andypew_control()//316B8(<), 31AE8(<) (F)
{
	return;
}

void andypew_init()//31698, 31AC8
{
	S_Warn("[andypew_init] - Unimplemented!\\n");
}

void andy6_end()//31690(<), 31AC0(<) (F)
{
	return;
}

void andy6_control()//315F8, 319B4
{
	S_Warn("[andy6_control] - Unimplemented!\\n");
}

void andy6_init()//30D84, 31104
{
	S_Warn("[andy6_init] - Unimplemented!\\n");
}

void joby8_end()
{
	S_Warn("[joby8_end] - Unimplemented!\\n");
}

void joby8_control()
{
	S_Warn("[joby8_control] - Unimplemented!\\n");
}

void joby8_init()
{
	S_Warn("[joby8_init] - Unimplemented!\\n");
}

void joby6_end()
{
	S_Warn("[joby6_end] - Unimplemented!\\n");
}

void joby6_control()
{
	S_Warn("[joby6_control] - Unimplemented!\\n");
}

void joby6_init()
{
	S_Warn("[joby6_init] - Unimplemented!\\n");
}

void andy5_end()
{
	S_Warn("[andy5_end] - Unimplemented!\\n");
}

void andy5_control()
{
	S_Warn("[andy5_control] - Unimplemented!\\n");
}

void andy5_init()
{
	S_Warn("[andy5_init] - Unimplemented!\\n");
}

void andrea3b_end()
{
	S_Warn("[andrea3b_end] - Unimplemented!\\n");
}

void andrea3b_control()
{
	S_Warn("[andrea3b_control] - Unimplemented!\\n");
}

void andrea3b_init()
{
	S_Warn("[andrea3b_init] - Unimplemented!\\n");
}

void andrea3_end()
{
	S_Warn("[andrea3_end] - Unimplemented!\\n");
}

void andrea3_control()
{
	S_Warn("[andrea3_control] - Unimplemented!\\n");
}

void andrea3_init()
{
	S_Warn("[andrea3_init] - Unimplemented!\\n");
}

void do_clanger_meshswap()
{
	S_Warn("[do_clanger_meshswap] - Unimplemented!\\n");
}

void andy4b_end()
{
	S_Warn("[andy4b_end] - Unimplemented!\\n");
}

void andy4b_control()
{
	S_Warn("[andy4b_control] - Unimplemented!\\n");
}

void andy4b_init()
{
	S_Warn("[andy4b_init] - Unimplemented!\\n");
}

void andy4_end()
{
	S_Warn("[andy4_end] - Unimplemented!\\n");
}

void andy4_control()
{
	S_Warn("[andy4_control] - Unimplemented!\\n");
}

void andy4_init()
{
	S_Warn("[andy4_init] - Unimplemented!\\n");
}

void richcut4_end()
{
	S_Warn("[richcut4_end] - Unimplemented!\\n");
}

void richcut4_control()
{
	S_Warn("[richcut4_control] - Unimplemented!\\n");
}

void richcut4_init()
{
	S_Warn("[richcut4_init] - Unimplemented!\\n");
}

void joby10_end()
{
	S_Warn("[joby10_end] - Unimplemented!\\n");
}

void joby10_control()
{
	S_Warn("[joby10_control] - Unimplemented!\\n");
}

void joby10_init()
{
	S_Warn("[joby10_init] - Unimplemented!\\n");
}

void joby9_end()
{
	S_Warn("[joby9_end] - Unimplemented!\\n");
}

void joby9_control()
{
	S_Warn("[joby9_control] - Unimplemented!\\n");
}

void joby9_init()
{
	S_Warn("[joby9_init] - Unimplemented!\\n");
}

void do_catapult_meshswap()
{
	S_Warn("[do_catapult_meshswap] - Unimplemented!\\n");
}

void andy3_end()
{
	S_Warn("[andy3_end] - Unimplemented!\\n");
}

void andy3_control()
{
	S_Warn("[andy3_control] - Unimplemented!\\n");
}

void andy3_init()
{
	S_Warn("[andy3_init] - Unimplemented!\\n");
}

void joby5_end()
{
	S_Warn("[joby5_end] - Unimplemented!\\n");
}

void joby5_control()
{
	S_Warn("[joby5_control] - Unimplemented!\\n");
}

void joby5_init()
{
	S_Warn("[joby5_init] - Unimplemented!\\n");
}

void andrea2_end()//2FFD4, 30354
{
	S_Warn("[andrea2_end] - Unimplemented!\\n");
}

void andrea2_control()//2FCDC, 3005C
{
	S_Warn("[andrea2_control] - Unimplemented!\\n");
}

void andrea2_init()//2FCC0(<), 30040(<) (F)
{
	cutseq_meshbits[1] &= 0x7FFFFFFF;
}

void andrea1_end()//2FC94, 30014
{
	S_Warn("[andrea1_end] - Unimplemented!\\n");
}

void andrea1_control()//2FB58, 2FED8
{
	S_Warn("[andrea1_control] - Unimplemented!\\n");
}

void andrea1_init()//2FB50(<), 2FED0(<) (F)
{
	return;
}

void joby4_end()
{
	S_Warn("[joby4_end] - Unimplemented!\\n");
}

void joby4_control()
{
	S_Warn("[joby4_control] - Unimplemented!\\n");
}

void joby4_init()
{
	S_Warn("[joby4_init] - Unimplemented!\\n");
}

void DelTorchFlames(struct PHD_VECTOR *pos)
{
	S_Warn("[DelTorchFlames] - Unimplemented!\\n");
}

void setup_preist_meshswap()
{
	S_Warn("[setup_preist_meshswap] - Unimplemented!\\n");
}

void andy2_end()
{
	S_Warn("[andy2_end] - Unimplemented!\\n");
}

void andy2_control()
{
	S_Warn("[andy2_control] - Unimplemented!\\n");
}

void andy2_init()
{
	S_Warn("[andy2_init] - Unimplemented!\\n");
}

void do_hammer_meshswap()
{
	S_Warn("[do_hammer_meshswap] - Unimplemented!\\n");
}

void hamgate_end()
{
	S_Warn("[hamgate_end] - Unimplemented!\\n");
}

void hamgate_control()
{
	S_Warn("[hamgate_control] - Unimplemented!\\n");
}

void hamgate_init()
{
	S_Warn("[hamgate_init] - Unimplemented!\\n");
}

void andy1_end()//2F408, 2F74C
{
	S_Warn("[andy1_end] - Unimplemented!\\n");
}

void andy1_control()//2F39C, 2F6A8
{
	S_Warn("[andy1_control] - Unimplemented!\\n");
}

void andy1_init()//2F37C, 2F688
{
	S_Warn("[andy1_init] - Unimplemented!\\n");
}

void joby3_end()//2F374(<), 2F680(<) (F)
{
	return;
}

void joby3_control()//2F304, 2F610
{
	S_Warn("[joby3_control] - Unimplemented!\\n");
}

void joby3_init()//2F2FC(<), 2F608(<) (F)
{
	return;
}

void joby2_end()//2F2B8, 2F5C4
{
	S_Warn("[joby2_end] - Unimplemented!\\n");
}

void joby2_control()//2F114, 2F420
{
	S_Warn("[joby2_control] - Unimplemented!\\n");
}

void joby2_init()//2F0C0, 2F3CC
{
	S_Warn("[joby2_init] - Unimplemented!\\n");
}

void TriggerDelSmoke(long x, long y, long z, int sizeme)
{
	S_Warn("[TriggerDelSmoke] - Unimplemented!\\n");
}

void TriggerActorBlood(int actornum, unsigned long nodenum, struct PHD_VECTOR *pos, int direction, int speed)
{
	S_Warn("[TriggerActorBlood] - Unimplemented!\\n");
}

void GetActorJointAbsPosition(int actornum, unsigned long nodenum, struct PHD_VECTOR *vec)
{
	S_Warn("[GetActorJointAbsPosition] - Unimplemented!\\n");
}

void deal_with_actor_shooting(unsigned short *shootdata, int actornum, int nodenum, struct PHD_VECTOR *pos)
{
	S_Warn("[deal_with_actor_shooting] - Unimplemented!\\n");
}

void stealth3_end()
{
	S_Warn("[stealth3_end] - Unimplemented!\\n");
}

void stealth3_start()
{
	S_Warn("[stealth3_start] - Unimplemented!\\n");
}

void special4_end()
{
	S_Warn("[special4_end] - Unimplemented!\\n");
}

void special4_control()
{
	S_Warn("[special4_control] - Unimplemented!\\n");
}

void special4_init()
{
	S_Warn("[special4_init] - Unimplemented!\\n");
}

void special3_end()
{
	S_Warn("[special3_end] - Unimplemented!\\n");
}

void special3_control()
{
	S_Warn("[special3_control] - Unimplemented!\\n");
}

void special3_init()
{
	S_Warn("[special3_init] - Unimplemented!\\n");
}

void special2_end()
{
	S_Warn("[special2_end] - Unimplemented!\\n");
}

void special2_control()
{
	S_Warn("[special2_control] - Unimplemented!\\n");
}

void special2_init()
{
	S_Warn("[special2_init] - Unimplemented!\\n");
}

void special1_end()
{
	S_Warn("[special1_end] - Unimplemented!\\n");
}

void special1_control()
{
	S_Warn("[special1_control] - Unimplemented!\\n");
}

void special1_init()
{
	S_Warn("[special1_init] - Unimplemented!\\n");
}

void richcut3_control()//2E594, 2E8A0
{
	S_Warn("[richcut3_control] - Unimplemented!\\n");
}

void richcut3_end()//2E54C, 2E858
{
	S_Warn("[richcut3_end] - Unimplemented!\\n");
}

void richcut3_init()//2E514, 2E820
{
	S_Warn("[richcut3_init] - Unimplemented!\\n");
}

void richcut2_control()//2E4EC, 2E77C
{
	S_Warn("[richcut2_control] - Unimplemented!\\n");
}

void richcut2_end()//2E4D8(<), 2E768(<) (F)
{
	lara_item->mesh_bits = 0xFFFFFFFF;
}

void richcut2_init()//2E4C0(<), 2E750(<) (F)
{
	cutrot = 1;
	lara_item->mesh_bits = 0;
}

void richcut1_control()//2E3D8, 2E668
{
	S_Warn("[richcut1_control] - Unimplemented!\\n");
}

void richcut1_end()//2E3A0, 2E630
{
	S_Warn("[richcut1_end] - Unimplemented!\\n");
}

void richcut1_init()//2E26C, 2E4FC
{
	S_Warn("[richcut1_init] - Unimplemented!\\n");
}

void cranecut_control()
{
	S_Warn("[cranecut_control] - Unimplemented!\\n");
}

void cranecut_end()
{
	S_Warn("[cranecut_end] - Unimplemented!\\n");
}

void cranecut_init()
{
	S_Warn("[cranecut_init] - Unimplemented!\\n");
}


struct ITEM_INFO* find_a_fucking_item(int object_number)//2DF50(<), 2E1E0(<)
{
	int i;

	if (level_items > 0)
	{
		for (i = 0; i < level_items; i++)
		{
			if (items[i].object_number == object_number)
			{
				return &items[i];
			}
		}
	}

	return NULL;
}

void handle_actor_chatting(int speechslot, int node, int slot, int objslot, short *ranges)
{
	S_Warn("[handle_actor_chatting] - Unimplemented!\\n");
}

void handle_lara_chatting(short *ranges)
{
	S_Warn("[handle_lara_chatting] - Unimplemented!\\n");
}

void DelsHandyTeleportLara(int x, int y, int z, int yrot)
{
	S_Warn("[DelsHandyTeleportLara] - Unimplemented!\\n");
}

void init_resident_cutseq(int num)
{
	S_Warn("[init_resident_cutseq] - Unimplemented!\\n");
}

void init_cutseq_actors(char *data, int resident)
{
	S_Warn("[init_cutseq_actors] - Unimplemented!\\n");
}

int Load_and_Init_Cutseq(int num)
{
	S_Warn("[Load_and_Init_Cutseq] - Unimplemented!\\n");
	return 0;
}

struct ITEM_INFO *cutseq_restore_item(int num)
{
	S_Warn("[*cutseq_restore_item] - Unimplemented!\\n");
	return NULL;
}

void cutseq_kill_item(int num)
{
	S_Warn("[cutseq_kill_item] - Unimplemented!\\n");
}

void deal_with_pistols(unsigned short *shootdata)
{
	S_Warn("[deal_with_pistols] - Unimplemented!\\n");
}

void trigger_weapon_dynamics(int left_or_right)
{
	S_Warn("[trigger_weapon_dynamics] - Unimplemented!\\n");
}

void cutseq_shoot_pistols(int left_or_right)
{
	S_Warn("[cutseq_shoot_pistols] - Unimplemented!\\n");
}

void cutseq_removelara_hk()
{
	S_Warn("[cutseq_removelara_hk] - Unimplemented!\\n");
}

void cutseq_givelara_hk()
{
	S_Warn("[cutseq_givelara_hk] - Unimplemented!\\n");
}

void cutseq_removelara_pistols()
{
	S_Warn("[cutseq_removelara_pistols] - Unimplemented!\\n");
}

void cutseq_givelara_pistols()
{
	S_Warn("[cutseq_givelara_pistols] - Unimplemented!\\n");
}

void CalculateObjectLightingLaraCutSeq()
{
	S_Warn("[CalculateObjectLightingLaraCutSeq] - Unimplemented!\\n");
}

void finish_cutseq(int name)
{
	S_Warn("[finish_cutseq] - Unimplemented!\\n");
}

void *cutseq_malloc(int size)
{
	S_Warn("[*cutseq_malloc] - Unimplemented!\\n");
	return NULL;
}

void init_cutseq_malloc()
{
	S_Warn("[init_cutseq_malloc] - Unimplemented!\\n");
}

void frigup_lara()
{
	S_Warn("[frigup_lara] - Unimplemented!\\n");
}

void InitPackNodes(struct NODELOADHEADER *lnode, struct PACKNODE *pnode, char *packed, int numnodes)
{
	S_Warn("[InitPackNodes] - Unimplemented!\\n");
}


void do_new_cutscene_camera()
{
	S_Warn("[do_new_cutscene_camera] - Unimplemented!\n");
}

void handle_cutseq_triggering(int name)//2C3C4, 2C6EC
{
	int i;
	int s1 = name;//guessed, moved but not used

	if (cutseq_num == 0)
	{
		int a1 = 0;//Must confirm initial value.
		if (cutseq_trig == 0)
		{
			if (lara.gun_status == 0)
			{
				if (lara.gun_type == 7)
				{
					a1 = -1;
				}//loc_2C448
			}
			else
			{
				//loc_2C41C
				if (lara.gun_type != 1)
				{
					lara.gun_status = 3;
				}

				//loc_2C430
				if (lara.gun_status != 1)
				{
					lara.gun_status = 3;
				}

				//loc_2C444
				a1 = -1;
			}

			//loc_2C448
			//loc_2C454
			for (i = 0; i < 9; i++)//TODO const
			{
				cutseq_meshswapbits[i] = 0;
				cutseq_meshbits[i] = a1;
			}

			cutseq_trig = 1;
			cutseq_busy_timeout = 50;

			//Not title
			if (gfCurrentLevel != 0)
			{
				SetFadeClip(28, 1);
			}

			//loc_2C494
			if (ScreenFadedOut == 0)
			{
				//Not title
				if (gfCurrentLevel != 0)
				{
					XAReqVolume = 0;
				}

				//loc_2C4C8
				SetScreenFadeOut(16, 0);
			}

			//loc_2C4D0
#ifdef INTERNAL
			ProfileDraw = 0;
#endif
		}
		else
		{
			if (cutseq_num == 1)
			{
				struct ITEM_INFO* v00 = lara_item;
				int v1 = ScreenFadedOut;
				int a0 = v00->current_anim_state;
				int a1 = 0;

				if (ScreenFadedOut != 0)
				{
					cutseq_busy_timeout--;

					if ((cutseq_busy_timeout & 0xFF) == 0)
					{
						cutseq_busy_timeout = 0;
						a1 = 1;

					}//j loc_2C588
					else
					{
						//loc_2C52C
						if (lara.gun_status != 1 && lara.gun_status == 0 && lara.flare_control_left != 0)
						{
							//loc_2C55C

							if ((lara_item->current_anim_state - 80) > 2 ||
								(lara_item->current_anim_state - 80) != 84 ||
								(lara_item->current_anim_state - 80) != 85 ||
								(lara_item->current_anim_state - 80) == 86)
							{
								//2C584
								a1 = 1;
							}

						}
						//loc_2C584 - may merge
						a1 = 1;
					}
				}

				//loc_2C588
				if (a1 == 0)
				{
					//loc_2CA50 cpy
					return;
				}

				lara.IsClimbing = 0;
				lara.flare_age = 0;

				if ((gfLevelFlags & 1))
				{

					lara.gun_type = 0;
					lara.request_gun_type = 0;
					lara.last_gun_type = 0;

					if (((*(int*)&objects[0x53B0]) & 1) != 0 && lara.pistols_type_carried != 0)
					{
						//loc_2C5FC
						lara.last_gun_type = 1;
					}
					else
					{
						//loc_2C5F4
						lara.last_gun_type = 0;
					}

					//loc_2C600
					if ((gfLevelFlags & 0x80) != 0)
					{
						if (((*(int*)&objects[0x5670]) & 0x10000) != 0)
						{
							if ((objects[0x5670 + 0x121] & 1) != 0)
							{
								int v0000 = 5;
								///TODO:
								assert(0);
							}//loc_2C644
						}//loc_2C648

					}//loc_2C644

					 //assert(0);//intentional, not finished!
					S_Warn("[handle_cutseq_triggering] - Unimplemented condition! loc_2C644\n");

				}//loc_2C6E4

			}//loc_2C79C

			if (gfCurrentLevel != 3)
			{
				//2C7DC
				if (gfCurrentLevel == 4 && ScreenFadedOut != 0)
				{
					if (gfCurrentLevel != 0)
					{
						S_CDStop();

					}//loc_2C818

					 //loc_2C818
					assert(0);//Data is malformed in IDA output, also jalr	$v0 must be debugged on emu.

				}//loc_2CA50

			}///@CHECK does jump to loc_2CA50 at end?
			else
			{
				SetScreenFadeOut(16, 1);

				if (gfCurrentLevel != 0)
				{
					XAReqVolume = 0;
				}//loc_2C7D0

				 //loc_2C7D0
				cutseq_trig = 4;
			}//loc_2CA50
		}
	}
	return;
}







