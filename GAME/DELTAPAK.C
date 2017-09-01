#include "DELTAPAK.H"

#include "CD.H"
#include "CONTROL.H"
#include "DRAW.H"
#include "GAMEFLOW.H"
#include "ITEMS.H"
#include "LARA.H"
#include "OBJECTS.H"
#include "PROFILE.H"
#include "SETUP.H"
#include "SPECIFIC.H"
#include "SPOTCAM.H"
#include "TOMB4FX.H"

#include <assert.h>
#include <stddef.h>
#include "ROOMLOAD.H"
#include "HEALTH.H"
#include "EFFECT2.H"
#include "NEWINV2.H"
#include "LOT.H"
#include "LARA2GUN.H"

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
	0x8035, 0x803D, 0x81C5, 0x81CF, 0x81EA, 0x4031, 0x403A, 0x41C9, 0x41DE, 0x41EE, 
	0xFFFF
};

unsigned short craneguard_pistols_info[7] =
{
	0x006A, 0x0075, 0x00F0, 0x00F7, 0x0104, 0x0112, 0xFFFF
};

short admiral_chat_ranges_joby2[12] =
{
	0x0118, 0x0154, 0x015C, 0x0175, 0x017C, 0x019D, 0x02CF, 0x0376, 0x0457, 0x0488, 
	0xFFFF, 0xFFFF
};

short sergie_chat_ranges_joby2[8] =
{
	0x01B9, 0x02B8, 0x0386, 0x041E, 0x07A2, 0x0868, 0xFFFF, 0xFFFF
};

short lara_chat_ranges_joby3[6] =
{
	0x052B, 0x0530, 0x053D, 0x0556, 0xFFFF, 0xFFFF
};

short lara_chat_ranges_joby4[10] =
{
	0x0244, 0x0267, 0x0279, 0x0302, 0x074F, 0x0786, 0x0796, 0x07AB, 0xFFFF, 0xFFFF
};

short admiral_chat_ranges_joby4[20] =
{
	0x012D, 0x0187, 0x0193, 0x0203, 0x030F, 0x0330, 0x033C, 0x0404, 0x040E, 0x04E6, 
	0x04F1, 0x0586, 0x06EB, 0x070C, 0x07EC, 0x084B, 0x0857, 0x087A, 0xFFFF, 0xFFFF
};

unsigned short larson_pistols_info1[2] =
{
	0x0390, 0xFFFF
};

short lara_chat_ranges_andrea1[4] =
{
	0x0248, 0x0279, 0xFFFF, 0xFFFF
};

short larson_chat_ranges1[12] =
{
	0x03AF, 0x03CB, 0x04AC, 0x04C9, 0x04DE, 0x0516, 0x05EC, 0x060C, 0x071A, 0x0762, 
	0xFFFF, 0xFFFF
};

short pierre_chat_ranges1[30] =
{
	0x02B8, 0x02C4, 0x02D5, 0x02E8, 0x03EB, 0x03FC, 0x0414, 0x0423, 0x0438, 0x0499, 
	0x052A, 0x056C, 0x0578, 0x05C0, 0x061B, 0x0630, 0x063A, 0x064A, 0x0668, 0x0706, 
	0x0783, 0x07A7, 0x07B6, 0x07D8, 0x07E2, 0x07ED, 0x07F5, 0x0814, 0xFFFF, 0xFFFF
};

short lara_chat_ranges_andrea2[32] =
{
	0x03D6, 0x03E6, 0x03EF, 0x0401, 0x05B1, 0x05E6, 0x077B, 0x07AE, 0x07BA, 0x07F5, 
	0x0803, 0x0817, 0x0881, 0x08D1, 0x08DE, 0x08FD, 0x090B, 0x092A, 0x0AEE, 0x0B07, 
	0x0BFA, 0x0C20, 0x0CBA, 0x0D35, 0x0D8F, 0x0DED, 0x0E01, 0x0E5E, 0x0E9B, 0x0F47, 
	0xFFFF, 0xFFFF
};

short larson_chat_ranges2[8] =
{
	0x01C2, 0x0255, 0x04DE, 0x0533, 0x082A, 0x0863, 0xFFFF, 0xFFFF
};

short pierre_chat_ranges2[34] =
{
	0x00F2, 0x0121, 0x012E, 0x0155, 0x0348, 0x0352, 0x035F, 0x03B2, 0x041B, 0x0427, 
	0x043A, 0x047F, 0x048F, 0x04C7, 0x0647, 0x065C, 0x066F, 0x067D, 0x0693, 0x06A6, 
	0x06BD, 0x0738, 0x0960, 0x097D, 0x0A80, 0x0AC9, 0x0C60, 0x0C73, 0x0C85, 0x0C9E, 
	0x0D46, 0x0D74, 0xFFFF, 0xFFFF
};

short admiral_chat_ranges_joby5[18] =
{
	0x01EB, 0x0242, 0x0369, 0x0459, 0x04DC, 0x0505, 0x0518, 0x0529, 0x0535, 0x05EE, 
	0x0757, 0x07B9, 0x07C3, 0x07F5, 0x0839, 0x08C4, 0xFFFF, 0xFFFF
};

short sergie_chat_ranges_joby5[20] =
{
	0x009C, 0x00B9, 0x00C2, 0x018B, 0x019C, 0x01CD, 0x025A, 0x0349, 0x0469, 0x0480, 
	0x0492, 0x04CC, 0x0605, 0x0616, 0x0627, 0x0673, 0x0681, 0x06F8, 0xFFFF, 0xFFFF
};

short lara_chat_ranges_joby9[12] =
{
	0x0282, 0x030C, 0x058A, 0x05A6, 0x05B1, 0x05DB, 0x05E6, 0x060A, 0x0619, 0x0691, 
	0xFFFF, 0xFFFF
};

short admiral_chat_ranges_joby9[36] =
{
	0x00B6, 0x015B, 0x0177, 0x0258, 0x033A, 0x04F5, 0x0509, 0x052D, 0x053C, 0x054D, 
	0x055A, 0x057F, 0x06A3, 0x06D2, 0x06E0, 0x076E, 0x077E, 0x07A4, 0x07B6, 0x07F5, 
	0x0807, 0x085C, 0x087A, 0x08AF, 0x08BC, 0x08CF, 0x08DE, 0x08F2, 0x08FE, 0x0977, 
	0x0988, 0x09B4, 0x09C5, 0x09D0, 0xFFFF, 0xFFFF
};

short lara_chat_ranges_joby10[12] =
{
	0x01ED, 0x020C, 0x0514, 0x052F, 0x0769, 0x078D, 0x09D9, 0x09FB, 0x0BA4, 0x0BC0, 
	0xFFFF, 0xFFFF
};

short admiral_chat_ranges_joby10[42] =
{
	0x0091, 0x00A3, 0x00D0, 0x00F0, 0x00FB, 0x0129, 0x0134, 0x0166, 0x0174, 0x01BD, 
	0x01C8, 0x01D5, 0x0222, 0x0331, 0x0340, 0x0398, 0x03A7, 0x04FD, 0x0539, 0x0563,
	0x0570, 0x060F, 0x061E, 0x06E8, 0x06F3, 0x0742, 0x07A0, 0x07DC, 0x07EB, 0x08BB, 
	0x08CC, 0x0983, 0x0A3E, 0x0A62, 0x0A74, 0x0A80, 0x0A8F, 0x0AB3, 0x0ABF, 0x0B0D, 
	0xFFFF, 0xFFFF
};

unsigned short andrea3_pistols_info[5] =
{
	0x454B, 0x854E, 0x8557, 0x4557, 0xFFFF
};

short lara_chat_ranges_andrea3[14] =
{
	0x0028, 0x005E, 0x0104, 0x0141, 0x01AC, 0x01BF, 0x01E3, 0x020F, 0x02C2, 0x033D, 
	0x035A, 0x03AC, 0xFFFF, 0xFFFF
};

short larson_chat_ranges3[14] =
{
	0x00A0, 0x00F1, 0x0152, 0x0199, 0x022F, 0x02B1, 0x03CB, 0x0462, 0x0472, 0x0512,
	0x05B4, 0x05F3, 0xFFFF, 0xFFFF
};

short lara_chat_ranges_andrea3b[12] =
{
	0x020A, 0x021B, 0x0223, 0x0238, 0x02BE, 0x02E0, 0x02E9, 0x0302, 0x0318, 0x03D2, 
	0xFFFF, 0xFFFF
};

short larson_chat_ranges3b[4] =
{
	0x0254, 0x02AD, 0xFFFF, 0xFFFF
};

short priest_chat_ranges_andy7[32] =
{
	0x0003, 0x0018, 0x0023, 0x0074, 0x0088, 0x00A7, 0x00BB, 0x010F, 0x011A, 0x0159, 
	0x01C9, 0x01FC, 0x0208, 0x0234, 0x0286, 0x02D2, 0x0310, 0x0343, 0x0356, 0x03DD, 
	0x03F1, 0x0404, 0x041C, 0x045C, 0x0477, 0x047F, 0x0487, 0x04D7, 0x04E8, 0x0528, 
	0xFFFF, 0xFFFF
};

short lara_chat_ranges_andy7[14] =
{
	0x017D, 0x0189, 0x0195, 0x01BE, 0x023E, 0x026D, 0x02EA, 0x0307, 0x054B, 0x0564, 
	0x056D, 0x0582, 0xFFFF, 0xFFFF
};

short lara_chat_ranges_joby7[10] =
{
	0x02D5, 0x02F7, 0x030D, 0x0339, 0x05CD, 0x05DD, 0x05EC, 0x0609, 0xFFFF, 0xFFFF
};

short lara_chat_ranges_andrea4[22] =
{
	0x01C9, 0x021C, 0x03B1, 0x03FF, 0x064B, 0x0677, 0x0686, 0x0694, 0x069D, 0x06BE, 
	0x0843, 0x0867, 0x0C02, 0x0C0D, 0x0DA3, 0x0DEB, 0x0DFE, 0x0E1F, 0x0E69, 0x0EAA, 
	0xFFFF, 0xFFFF
};

short pierre_chat_ranges4[48] =
{
	0x014E, 0x015B, 0x0168, 0x01A8, 0x022E, 0x0258, 0x0267, 0x0304, 0x0315, 0x038A,
	0x0424, 0x042D, 0x0439, 0x045C, 0x046E, 0x04DE, 0x04EC, 0x0504, 0x0511, 0x052B, 
	0x053C, 0x056A, 0x057E, 0x05F5, 0x060F, 0x063C, 0x06E5, 0x0739, 0x074A, 0x0809, 
	0x0A3F, 0x0A50, 0x0A66, 0x0A82, 0x0AC3, 0x0B23, 0x0B67, 0x0BC2, 0x0CE1, 0x0D22, 
	0x0D3E, 0x0D62, 0x0E3A, 0x0E53, 0x0F16, 0x0F1C, 0xFFFF, 0xFFFF
};

short lara_chat_ranges_andy9[6] =
{
	0x041A, 0x043A, 0x0F2C, 0x0F7F, 0xFFFF, 0xFFFF
};

short lara_chat_ranges_andy1[14] =
{
	0x0312, 0x0333, 0x054B, 0x0555, 0x056D, 0x0588, 0x0868, 0x087D, 0x0C25, 0x0C55, 
	0x0C6A, 0x0C74, 0xFFFF, 0xFFFF
};

short lara_chat_ranges_andy2[8] =
{
	0x05BA, 0x05D2, 0x05E5, 0x05FB, 0x07D9, 0x07FD, 0xFFFF, 0xFFFF
};

short lara_chat_ranges_joby8[20] =
{
	0x03BC, 0x042D, 0x04ED, 0x053A, 0x0550, 0x0597, 0x05AB, 0x05BE, 0x05CD, 0x05E0, 
	0x05F6, 0x0620, 0x070C, 0x072F, 0x0897, 0x08CF, 0x0913, 0x0940, 0xFFFF, 0xFFFF
};

short lara_chat_ranges_andy6[8] =
{
	0x02C8, 0x02D7, 0x02EF, 0x0303, 0x034C, 0x037A, 0xFFFF, 0xFFFF
};

short lara_chat_ranges_andy11[28] =
{
	0x083F, 0x0851, 0x0CB0, 0x0CC6, 0x0CD5, 0x0CEA, 0x0CF9, 0x0D15, 0x0D1F, 0x0D35, 
	0x0D3E, 0x0D50, 0x0D6B, 0x0DBE, 0x0E5B, 0x0E6C, 0x0E8B, 0x0EA2, 0x1021, 0x103A, 
	0x12E3, 0x12F7, 0x1510, 0x152F, 0x16F2, 0x1715, 0xFFFF, 0xFFFF
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
	0xFF5B, 0x0096, 0xFCF7, 0x0001, 0xFFA9, 0x004E
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

#if INTERNAL
	#define CD_PLAY_MODE 1
#else
	#define CD_PLAY_MODE 0
#endif

void andy11_end()//32D6C, 3326C
{
	cutseq_restore_item(ANIMATING15);
}

void andy11_control()//32C70, 33108
{
	if (GLOBAL_cutseq_frame == 2112 ||
		GLOBAL_cutseq_frame == 2660 ||
		GLOBAL_cutseq_frame == 3082 ||
		GLOBAL_cutseq_frame == 3626 ||
		GLOBAL_cutseq_frame == 4002 ||
		GLOBAL_cutseq_frame == 4064 ||
		GLOBAL_cutseq_frame == 4118 ||
		GLOBAL_cutseq_frame == 4366 ||
		GLOBAL_cutseq_frame == 4789 ||
		GLOBAL_cutseq_frame == 5390)
	{
		lara_item->mesh_bits = -1;
	}

	if (GLOBAL_cutseq_frame == 2164 ||
		GLOBAL_cutseq_frame == 2863 ||
		GLOBAL_cutseq_frame == 3534 ||
		GLOBAL_cutseq_frame == 3915 ||
		GLOBAL_cutseq_frame == 4064 ||
		GLOBAL_cutseq_frame == 4158 ||
		GLOBAL_cutseq_frame == 4569 ||
		GLOBAL_cutseq_frame == 5076)
	{
		lara_item->mesh_bits = 0;
	}

	if (GLOBAL_cutseq_frame == 3082)
	{
		cutseq_meshbits[5] |= 0x80000000;
	}
	else if (GLOBAL_cutseq_frame == 2660)
	{
		cutseq_meshbits[2] &= 0x7FFFFFFFu;
	}

	S_Warn("[andy11_control] - Unimplemented end of function!\n");
} 

void andy11_init()//32C20(<), 330B8(<) (F)
{
	cutseq_kill_item(ANIMATING15);
	lara_item->mesh_bits = 0;
	cutseq_meshbits[4] &= 0xFFF07FFF;
	cutseq_meshbits[5] &= 0x7FFFFFFFu;
}

void Cutanimate(int objnum)//32B50(<), 32FE8(<) (F)
{
	struct ITEM_INFO* item = find_a_fucking_item(objnum);

	item->anim_number = objects[objnum].anim_index;
	item->frame_number = anims[item->anim_number].frame_base;
	AddActiveItem(item - items);
	item->status = 1;
	item->flags |= IFLAG_ACTIVATION_MASK;
}

struct ITEM_INFO* ResetCutanimate(int objnum)//32A80(<), 32F18(<) (F)
{
	struct ITEM_INFO* item = find_a_fucking_item(objnum);

	item->anim_number = objects[objnum].anim_index;
	item->frame_number = anims[item->anim_number].frame_base;
	RemoveActiveItem(item - items);	
	item->status = 0;
	item->flags &= 0xC1FF;

	return item;
}

void trigger_title_spotcam(int num)//32904(<), 32D9C(<)
{
	struct ITEM_INFO* item;

	jobyfrigger = 0;

	if (num == 1)
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
	else if (num == 4)
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
	 * Each flyby sequence should play its own unique music.
	 * Here we alter the music for the current flyby sequence.
	 */
	if (num == 1)
	{
		S_CDPlay(83, CD_PLAY_MODE);
	}
	else if (num == 2)
	{
		S_CDPlay(87, CD_PLAY_MODE);
	}
	else if (num == 3)
	{
		S_CDPlay(86, CD_PLAY_MODE);
	}
	else if (num == 4)
	{
		S_CDPlay(91, CD_PLAY_MODE);
	}

	InitialiseSpotCam(num);

}//32968

void CutLaraBubbles()//327F8(<), 32C90(<) (F)
{
	struct PHD_VECTOR offset;
	struct PHD_VECTOR pos;
	int i; 
	short roomnum; 

	offset.x = 0;
	offset.y = -4;
	offset.z = 64;
	GetLaraJointPos(&offset, 8);
	roomnum = camera.pos.room_number;
	IsRoomOutsideNo = -1;
	IsRoomOutside(offset.x, offset.y, offset.z);
	if (IsRoomOutsideNo != -1)
	{
		roomnum = IsRoomOutsideNo;
	}
	for (i = 0; i < 2; i++)
	{
		pos.x = (GetRandomControl() & 0x3F) + offset.x - 32;
		pos.y = (GetRandomControl() & 0x3F) + offset.y - 32;
		pos.z = (GetRandomControl() & 0x3F) + offset.z - 32;
		CreateBubble(&pos, roomnum, 7, 8, 0, 0, -96, 0);
	}
}

void swampy_end()//3271C(<), 32BB4(<) (F)
{
	SetCutNotPlayed(43);
	AddActiveItem(find_a_fucking_item(GREEN_TEETH) - items);
	DelsHandyTeleportLara(42477, 12456, 55982, 28953);
	lara.water_status = 1;
	lara_item->pos.x_rot = ANGLE(-29);
	lara_item->goal_anim_state = STATE_LARA_UNDERWATER_STOP;
	lara_item->current_anim_state = STATE_LARA_UNDERWATER_STOP;
	lara_item->frame_number = anims[ANIMATION_LARA_UNDERWATER_IDLE].frame_base;
	lara_item->anim_number = ANIMATION_LARA_UNDERWATER_IDLE;
	if (lara.air > 200)
		lara.air = 200;
}

void swampy_control()//326EC(<), 32B84(<) (F)
{
	if (GLOBAL_cutseq_frame >= 385 && GLOBAL_cutseq_frame <= 396)
		CutLaraBubbles();
}

void swampy_init()//32608(<), 32AA0(<) (F)
{
	struct ITEM_INFO* item = find_a_fucking_item(GREEN_TEETH);

	cutrot = 0;

	if (item)
	{
		item->status = 3;
		RemoveActiveItem(item - items);
		DisableBaddieAI(item - items);
		item->flags |= IFLAG_INVISIBLE;
	}

	lara.water_status = 1;
}

void monk2_end()//325F4(<), 32A8C(<) (F)
{
	lara_item->mesh_bits = 0xFFFFFFFF;
}

void monk2_control()//324E4(<), 3297C(<) (F)
{
	struct PHD_VECTOR pos;
	int f;

	if (GLOBAL_cutseq_frame == 70)
	{
		lara_item->mesh_bits = 0;
	}
	else
	{
		if (GLOBAL_cutseq_frame < 630 || GLOBAL_cutseq_frame >= 720)
		{
			f = cut_seethrough;
		}
		else
		{
			f = cut_seethrough;
			if (cut_seethrough > 32)
			{
				f = cut_seethrough - 4;
				cut_seethrough -= 4;
			}
		}
		if (GLOBAL_cutseq_frame == 740)
		{
			cut_seethrough = 128;
		}
		else if (GLOBAL_cutseq_frame >= 940)
		{
			if (f > 0)
			{
				cut_seethrough = f - 4;
				if (f - 4 < 0)
					cut_seethrough = 0;
			}
			else
			{
				if (f < 0)
					cut_seethrough = 0;
			}
		}
	}

	pos.x = 0;
	pos.y = 0;
	pos.z = 0;
	GetActorJointAbsPosition(1, 0, &pos);

	TriggerDynamic(pos.x, pos.y, pos.z, 10,
		GetRandomControl() & 0xF, (GetRandomControl() & 0x1F) + 16, (GetRandomControl() & 0x3F) + 128);
}

void monk2_init()//324D4(<), 3296C(<) (F)
{
	cutrot = 1;
}

void do_pierre_gun_meshswap()//32484(<), 3291C(<) (F)
{
	meshes[objects[PIERRE].mesh_index + 23] = meshes[objects[MESHSWAP2].mesh_index + 22];
	cutseq_meshswapbits[1] |= 0x800;
}

void andrea4_end()//32464(<), 328FC(<) (F)
{
	cutseq_removelara_pistols();
}

void andrea4_control()//323C8(<), 32860(<) (F)
{
	switch (GLOBAL_cutseq_frame)
	{
	case 3134:
		cutseq_givelara_pistols();
		undraw_pistol_mesh_left(1);
		break;
	case 3169:
		cutseq_givelara_pistols();
		break;
	case 3173:
		do_pierre_gun_meshswap();
		break;
	}

	handle_lara_chatting(lara_chat_ranges_andrea4);
	handle_actor_chatting(23, 8, 1, 47, pierre_chat_ranges4);
	actor_chat_cnt = (actor_chat_cnt - 1) & 1;
}

void andrea4_init()//323C0(<), 32858(<) (F)
{
}

void joby7_end()//32328(<), 327C0(<) (F)
{
	lara_item->mesh_bits = -1;
	cutseq_restore_item(ANIMATING2);
	AddDisplayPickup(PICKUP_ITEM1);
	DelsHandyTeleportLara(30049, 17583, 69794, -13706);
	lara.water_status = 1;
	lara_item->pos.x_rot = 1090;
	lara_item->goal_anim_state = STATE_LARA_UNDERWATER_STOP;
	lara_item->current_anim_state = STATE_LARA_UNDERWATER_STOP;
	lara_item->frame_number = anims[ANIMATION_LARA_UNDERWATER_IDLE].frame_base;
	lara_item->anim_number = ANIMATION_LARA_UNDERWATER_IDLE;
	lara.Anxiety = 80;
}

void joby7_control()//3210C, 325A4
{
	S_Warn("[joby7_control] - Unimplemented!\n");
}

void joby7_init()//320D0(<), 32568(<) (F)
{
	lara_item->mesh_bits = 0;
	cutseq_kill_item(ANIMATING2);
	cutseq_meshbits[6] &= 0x7FFFFFFF;
}

void andy10_end()//3202C(<), 324C4(<) (F)
{
	lara_item->mesh_bits = -1;
	SetCutPlayed(43);
	Cutanimate(ANIMATING12);
	Cutanimate(ANIMATING13);
	FlipMap(7);
	DelsHandyTeleportLara(SECTOR_TO_WORLD(38), SECTOR_TO_WORLD(14.5), SECTOR_TO_WORLD(47), 0);
	lara.water_status = 1;
	lara_item->pos.x_rot = ANGLE(-29);
	lara_item->goal_anim_state = STATE_LARA_UNDERWATER_STOP;
	lara_item->current_anim_state = STATE_LARA_UNDERWATER_STOP;
	lara_item->frame_number = anims[ANIMATION_LARA_UNDERWATER_IDLE].frame_base;
	lara_item->anim_number = ANIMATION_LARA_UNDERWATER_IDLE;
	NailInvItem(PUZZLE_ITEM2);
	disable_horizon = 0;
}

void andy10_control()//31E9C(<), 32334(<) (F)
{
	if (GLOBAL_cutseq_frame == 1250)
	{
		cutseq_meshbits[8] &= 0xE0;
		TriggerDynamic(GLOBAL_cutme->orgx, GLOBAL_cutme->orgy, GLOBAL_cutme->orgz, 31, 255, 255, 255);
		return;
	}
	
	if (GLOBAL_cutseq_frame == 902)
	{
		cutseq_meshbits[1] |= 0x80000000;
		cutseq_meshbits[2] |= 0x80000000;
		cutseq_meshbits[3] |= 0x80000000;
		cutseq_meshbits[4] &= 0x7FFFFFFFu;
		cutseq_meshbits[5] |= 0x80000000;
		cutseq_meshbits[6] |= 0x80000000;
	}
	else if (GLOBAL_cutseq_frame == 338 || GLOBAL_cutseq_frame == 775)
	{
		lara_item->mesh_bits = 0;
	}
	else if (GLOBAL_cutseq_frame == 747)
	{
		lara_item->mesh_bits = -1;
		TriggerDynamic(GLOBAL_cutme->orgx, GLOBAL_cutme->orgy, GLOBAL_cutme->orgz, 31, 255, 255, 255);
		return;
	}
	else if (GLOBAL_cutseq_frame == 1574)
	{
		cutseq_meshbits[4] &= 0x7FFFFFFFu;
	}
	
	if (GLOBAL_cutseq_frame == 338 || GLOBAL_cutseq_frame == 1030)
	{
		cutseq_meshbits[4] |= 0x80000000;
	}
	else if(GLOBAL_cutseq_frame == 1603)
	{
		cutseq_meshbits[1] &= 0x7FFFFFFFu;
	}
	else if(GLOBAL_cutseq_frame == 1624)
	{
		cutseq_meshbits[2] &= 0x7FFFFFFFu;
	}
	else if(GLOBAL_cutseq_frame == 854)
	{
		cutseq_meshbits[7] &= 0x7FFFFFFFu;
	}

	TriggerDynamic(GLOBAL_cutme->orgx, GLOBAL_cutme->orgy, GLOBAL_cutme->orgz, 31, 255, 255, 255);
}

void andy10_init()//31D58(<), 321F0(<) (F)
{
	struct ITEM_INFO* item;

	cutseq_kill_item(ANIMATING4);
	cutseq_kill_item(ANIMATING5);
	cutseq_kill_item(ANIMATING14);
	
	cutseq_meshbits[1] &= 0x7FFFFFFFu;
	cutseq_meshbits[2] &= 0x7FFFFFFFu;
	cutseq_meshbits[3] &= 0x7FFFFFFFu;
	cutseq_meshbits[4] &= 0x7FFFFFFFu;
	cutseq_meshbits[5] &= 0x7FFFFFFFu;
	cutseq_meshbits[6] &= 0x7FFFFFFFu;
	
	item = find_a_fucking_item(GREEN_TEETH);
	item->status = 3;
	RemoveActiveItem(item - items);
	DisableBaddieAI(item - items);
	item->flags |= IFLAG_INVISIBLE;
	lara.water_status = 1;
	FlipMap(7);
	disable_horizon = 1;
}

void do_chalk_meshswap()//31D24(<), 321BC(<) (F)
{
	short* temp = lara.mesh_ptrs[LM_RHAND];
	lara.mesh_ptrs[LM_RHAND] = meshes[objects[MAFIA_MIP].mesh_index + 20];
	meshes[objects[MAFIA_MIP].mesh_index + 80] = temp;
}

void andy8_end()//31CF8, 32190
{
	SetCutPlayed(36);

	do_chalk_meshswap();

	lara.puzzleitems[0] = 0;
}

void andy8_control()//31C3C(<), 320D4(<) (F)
{
	struct ITEM_INFO* item = find_a_fucking_item(ANIMATING16);

	item->flags |= 0x20u;
	switch (GLOBAL_cutseq_frame)
	{
	case 311:
		item->mesh_bits = 2;
		break;
	case 701:
		item->mesh_bits = 4;
		break;
	case 831:
		item->mesh_bits = 8;
		break;
	case 1244:
		lara_item->mesh_bits = 0;
		break;
	case 1476:
		lara_item->mesh_bits = -1;
		break;
	case 145:
		do_chalk_meshswap();
		break;
	}
}

void andy8_init()//31C34(<), 320CC(<) (F)
{
}

void andy9_end()//31C08(<), 320A0(<) (F)
{
	cutseq_restore_item(ANIMATING15);
	lara_item->mesh_bits = -1;
}

void andy9_control()//31BA4, 31FD4
{
	S_Warn("[andy9_control] - Unimplemented!\n");
}

void andy9_init()//31B7C(<), 31FAC(<) (F)
{
	cutseq_kill_item(ANIMATING15);
	lara_item->mesh_bits = 0;
}

void TriggerDelBrownSmoke(long x, long y, long z)
{
	S_Warn("[TriggerDelBrownSmoke] - Unimplemented!\n");
}

void cossack_end()//31998(<), 31DC8(<) (F)
{
	DelsHandyTeleportLara(SECTOR_TO_WORLD(75.75), SECTOR_TO_WORLD(4.75), SECTOR_TO_WORLD(36.5), 0);
	SetCutNotPlayed(36);
}

void cossack_control()//3178C, 31BBC
{
	S_Warn("[cossack_control] - Unimplemented!\n");
}

void cossack_init()//31784(<), 31BB4(<) (F)
{
	return;
}

void andy7_end()//31754, 31B84
{
	S_Warn("[andy7_end] - Unimplemented!\n");
}

void andy7_control()//31704, 31B34
{
	S_Warn("[andy7_control] - Unimplemented!\n");
}

void andy7_init()//316F4(<), 31B24(<) (F)
{
	cutrot = 1;
}

void andypew_end()//316C0, 31AF0
{
	S_Warn("[andypew_end] - Unimplemented!\n");
}

void andypew_control()//316B8(<), 31AE8(<) (F)
{
	return;
}

void andypew_init()//31698(<), 31AC8(<) (F)
{
	cutseq_kill_item(PUZZLE_HOLE2);
}

void andy6_end()//31690(<), 31AC0(<) (F)
{
	return;
}

void andy6_control()//315F8, 319B4
{
	S_Warn("[andy6_control] - Unimplemented!\n");
}

void andy6_init()//30D84(<), 31104(<) (F)
{
	cutrot = 1;
	setup_preist_meshswap();
}

void joby8_end()
{
	S_Warn("[joby8_end] - Unimplemented!\n");
}

void joby8_control()
{
	S_Warn("[joby8_control] - Unimplemented!\n");
}

void joby8_init()
{
	S_Warn("[joby8_init] - Unimplemented!\n");
}

void joby6_end()
{
	S_Warn("[joby6_end] - Unimplemented!\n");
}

void joby6_control()
{
	S_Warn("[joby6_control] - Unimplemented!\n");
}

void joby6_init()
{
	S_Warn("[joby6_init] - Unimplemented!\n");
}

void andy5_end()//30F28(<), 312A8(<) (F)
{
	cutseq_restore_item(PUZZLE_HOLE2);
	return;
}

void andy5_control()//30DA4, 31124
{
	S_Warn("[andy5_control] - Unimplemented!\n");
}

void andy5_init()//30D84(<), 31104(<) (F)
{
	cutseq_kill_item(PUZZLE_HOLE2);
	return;
}

void andrea3b_end()//30C54, 30FD4
{
	S_Warn("[andrea3b_end] - Unimplemented!\n");
}

void andrea3b_control()//30B08, 30E88
{
	S_Warn("[andrea3b_control] - Unimplemented!\n");
}

void andrea3b_init()//30A1C, 30D9C
{
	S_Warn("[andrea3b_init] - Unimplemented!\n");
}

void andrea3_end()//30904, 30C84
{
	S_Warn("[andrea3_end] - Unimplemented!\n");
}

void andrea3_control()//30870, 30BF0
{
	S_Warn("[andrea3_control] - Unimplemented!\n");
}

void andrea3_init()//30850, 30BD0
{
	cutseq_givelara_pistols();
	return;
}

void do_clanger_meshswap()
{
	S_Warn("[do_clanger_meshswap] - Unimplemented!\n");
}

void andy4b_end()//307EC, 30B6C
{
	S_Warn("[andy4b_end] - Unimplemented!\n");
}

void andy4b_control()//30710, 30A90
{
	S_Warn("[andy4b_control] - Unimplemented!\n");
}

void andy4b_init()//306F0(<), 30A70(<) (F)
{
	cutseq_kill_item(ANIMATING5_MIP);
	return;
}

void andy4_end()//306B4, 30A34
{
	S_Warn("[andy4_end] - Unimplemented!\n");
}

void andy4_control()//305BC, 3093C
{
	S_Warn("[andy4_control] - Unimplemented!\n");
}

void andy4_init()//3059C(<), 3091C(<) (F)
{
	cutseq_kill_item(ANIMATING5_MIP);
	return;
}

void richcut4_end()
{
	S_Warn("[richcut4_end] - Unimplemented!\n");
}

void richcut4_control()
{
	S_Warn("[richcut4_control] - Unimplemented!\n");
}

void richcut4_init()
{
	S_Warn("[richcut4_init] - Unimplemented!\n");
}

void joby10_end()//303AC, 3072C
{
	S_Warn("[joby10_end] - Unimplemented!\n");
}

void joby10_control()//30338, 306B8
{
	S_Warn("[joby10_control] - Unimplemented!\n");
}

void joby10_init()//30318(<), 30698(<) (F)
{
	cutseq_kill_item(CRANE_GUY_MIP);
	return;
}

void joby9_end()//302F0(<), 30670(<) (F)
{
	cutseq_restore_item(CRANE_GUY_MIP);
	AddDisplayPickup(KEY_ITEM7);
	return;
}

void joby9_control()//302A0, 30620
{
	S_Warn("[joby9_control] - Unimplemented!\n");
}

void joby9_init()//30280(<), 30600(<) (F)
{
	cutseq_kill_item(CRANE_GUY_MIP);
	return;
}

void do_catapult_meshswap()
{
	S_Warn("[do_catapult_meshswap] - Unimplemented!\n");
}

void andy3_end()
{
	S_Warn("[andy3_end] - Unimplemented!\n");
}

void andy3_control()
{
	S_Warn("[andy3_control] - Unimplemented!\n");
}

void andy3_init()
{
	S_Warn("[andy3_init] - Unimplemented!\n");
}

void joby5_end()//30144, 304C4
{
	cutseq_restore_item(ANIMATING3);
	cutseq_restore_item(ANIMATING4);
	DelsHandyTeleportLara(SECTOR_TO_WORLD(60), -SECTOR_TO_WORLD(1.25), SECTOR_TO_WORLD(54), ANGLE(-180));
	lara_item->mesh_bits = -1;
}

void joby5_control()//30034, 303B4
{
	S_Warn("[joby5_control] - Unimplemented!\n");
}

void joby5_init()//2FFF0(<), 30370(<) (F)
{
	cutseq_kill_item(ANIMATING3);
	cutseq_kill_item(ANIMATING4);
	cutseq_meshbits[2] &= 0x7FFFFFFFu;
	cutseq_meshbits[4] &= 0x7FFFFFFFu;
}

void andrea2_end()//2FFD4(<), 30354(<) (F)
{
	lara.pickupitems &= 0xFFFD;
	return;
}

void andrea2_control()//2FCDC, 3005C
{
	S_Warn("[andrea2_control] - Unimplemented!\n");
}

void andrea2_init()//2FCC0(<), 30040(<) (F)
{
	cutseq_meshbits[1] &= 0x7FFFFFFF;
}

void andrea1_end()//2FC94(<), 30014(<) (F)
{
	lara_item->mesh_bits = -1;
	lara.pickupitems &= 0xFFFEu;
}

void andrea1_control()//2FB58(<), 2FED8(<) (F)
{
	struct PHD_VECTOR pos;
	struct ITEM_INFO* item;

	switch (GLOBAL_cutseq_frame)
	{
	case 330:
		item = find_a_fucking_item(ANIMATING10);
		item->flags |= 0x20u;
		item->mesh_bits = item->mesh_bits & 0xFFFFFFFD | 4;
		break;
	case 452:
		cutseq_givelara_pistols();
		break;
	case 580:
		undraw_pistol_mesh_left(1);
		break;
	case 603:
		undraw_pistol_mesh_right(1);
		lara.holster = old_lara_holster;
		break;
	case 705:
		lara_item->mesh_bits = 0;
		break;
	}

	pos.x = -50;
	pos.y = 200;
	pos.z = 0;
	deal_with_actor_shooting(larson_pistols_info1, 1, 14, &pos);
	handle_lara_chatting(lara_chat_ranges_andrea1);
	handle_actor_chatting(21, 8, 1, 45, larson_chat_ranges1);
	handle_actor_chatting(23, 8, 2, 419, pierre_chat_ranges1);
	actor_chat_cnt = (actor_chat_cnt - 1) & 1;
}

void andrea1_init()//2FB50(<), 2FED0(<) (F)
{
	return;
}

void joby4_end()//2FB04(<), 2FE84(<) (F)
{
	lara_item->mesh_bits = -1;
	cutseq_restore_item(DOOR_TYPE1);
	cutseq_restore_item(DOOR_TYPE5);
	DelsHandyTeleportLara(57950, 8960, 53760, ANGLE(90));
}

void joby4_control()//2FA0C, 2FD8C
{
	S_Warn("[joby4_control] - Unimplemented!\n");
}

void joby4_init()//2F9E4(<), 2FD64(<) (F)
{
	cutseq_kill_item(DOOR_TYPE1);
	cutseq_kill_item(DOOR_TYPE5);
	cutrot = 0;
	return;
}

void DelTorchFlames(struct PHD_VECTOR* pos)//2F6E4(<), 2FA64(<) (F)
{
	long x, y, z, size;
	struct SPARKS* sptr;

	y = pos->y;
	z = pos->z;
	x = pos->x;

	sptr = &spark[GetFreeSpark()];
	sptr->On = 1;
	sptr->sR = -1;
	sptr->sB = 48;
	sptr->sG = (GetRandomControl() & 0x1F) + 48;
	sptr->dR = (GetRandomControl() & 0x3F) - 64;
	sptr->dB = 32;
	sptr->dG = (GetRandomControl() & 0x3F) + -128;
	sptr->FadeToBlack = 8;
	sptr->ColFadeSpeed = (GetRandomControl() & 3) + 16;
	sptr->TransType = 2;
	sptr->Life = sptr->sLife = (GetRandomControl() & 7) + 32;
	sptr->x = x;	
	sptr->y = y;
	sptr->z = z;
	sptr->Xvel = (GetRandomControl() & 0xFF) - 128;
	sptr->Yvel = -((GetRandomControl() & 0xF) + 16);
	sptr->Zvel = GetRandomControl() - 128;
	sptr->Friction = 51;
	sptr->Gravity = -16 - (GetRandomControl() & 0x1F);
	sptr->Flags = -32230;
	sptr->MaxYvel = -16 - (GetRandomControl() & 7);
	sptr->RotAng = GetRandomControl() & 0xFFF;
	sptr->Scalar = 2;
	sptr->RotAdd = (GetRandomControl() & 0x1F) - 16;
	size = (GetRandomControl() & 0xF) + 16;
	sptr->sSize = size;
	sptr->Size = size;
	sptr->dSize = size >> 4;

	sptr = &spark[GetFreeSpark()];
	sptr->On = 1;
	sptr->sR = (GetRandomControl() & 0x3F) - 64;
	sptr->sG = (GetRandomControl() & 0x3F) - 64;
	sptr->sB = (GetRandomControl() & 0xF) + 16;
	sptr->ColFadeSpeed = 8;
	sptr->FadeToBlack = 8;	
	sptr->dR = sptr->sR >> 2;
	sptr->dG = sptr->sG >> 2;
	sptr->dB = sptr->sB >> 2;
	sptr->TransType = 2;
	sptr->Life = sptr->sLife = (GetRandomControl() & 0xF) + 24;
	sptr->x = (GetRandomControl() & 0x3F) + x - 32;
	sptr->y = (GetRandomControl() & 0x3F) + y - 32;
	sptr->Friction = 51;
	sptr->MaxYvel = 0;
	sptr->Flags = -32230;
	sptr->Scalar = 2;
	sptr->z = (GetRandomControl() & 0x3F) + z - 32;
	size = (GetRandomControl() & 0xF) + 16;
	sptr->dSize = size;
	sptr->sSize = size >> 1;
	sptr->Size = size >> 1;
	sptr->Gravity = -((GetRandomControl() & 0x1F) + 16);
	sptr->Yvel = -22;
	sptr->Xvel = GetRandomControl() - 128;
	sptr->Zvel = (GetRandomControl() & 0xFF) - 128;
	sptr->dSize = sptr->dSize + (sptr->dSize >> 2);
}

void setup_preist_meshswap()//2F694(<), 2FA14(<) (F)
{
	meshes[objects[SAILOR_MIP].mesh_index + 0x10] = meshes[objects[MESHSWAP3].mesh_index + 0x10];
	cutseq_meshswapbits[1] |= 0x100;
	return;
}

void andy2_end()//2F668, 2F9E8
{
	S_Warn("[andy2_end] - Unimplemented!\n");
}

void andy2_control()//2F5D0, 2F914
{
	S_Warn("[andy2_control] - Unimplemented!\n");
}

void andy2_init()//2F5B0(<), 2F8F4(<) (F)
{
	setup_preist_meshswap();
	return;
}

void do_hammer_meshswap()
{
	S_Warn("[do_hammer_meshswap] - Unimplemented!\n");
}

void hamgate_end()
{
	S_Warn("[hamgate_end] - Unimplemented!\n");
}

void hamgate_control()
{
	S_Warn("[hamgate_control] - Unimplemented!\n");
}

void hamgate_init()
{
	S_Warn("[hamgate_init] - Unimplemented!\n");
}

void andy1_end()//2F408, 2F74C
{
	S_Warn("[andy1_end] - Unimplemented!\n");
}

void andy1_control()//2F39C, 2F6A8
{
	S_Warn("[andy1_control] - Unimplemented!\n");
}

void andy1_init()//2F37C(<), 2F688(<) (F)
{
	cutseq_kill_item(ANIMATING2);
	return;
}

void joby3_end()//2F374(<), 2F680(<) (F)
{
	return;
}

void joby3_control()//2F304, 2F610
{
	S_Warn("[joby3_control] - Unimplemented!\n");
}

void joby3_init()//2F2FC(<), 2F608(<) (F)
{
	return;
}

void joby2_end()//2F2B8, 2F5C4
{
	S_Warn("[joby2_end] - Unimplemented!\n");
}

void joby2_control()//2F114, 2F420
{
	S_Warn("[joby2_control] - Unimplemented!\n");
}

void joby2_init()//2F0C0, 2F3CC
{
	S_Warn("[joby2_init] - Unimplemented!\n");
}

void TriggerDelSmoke(long x, long y, long z, int sizeme)
{
	S_Warn("[TriggerDelSmoke] - Unimplemented!\n");
}

void TriggerActorBlood(int actornum, unsigned long nodenum, struct PHD_VECTOR* pos, int direction, int speed)
{
	S_Warn("[TriggerActorBlood] - Unimplemented!\n");
}

void GetActorJointAbsPosition(int actornum, unsigned long nodenum, struct PHD_VECTOR* vec)
{
	S_Warn("[GetActorJointAbsPosition] - Unimplemented!\n");
}

void deal_with_actor_shooting(unsigned short* shootdata, int actornum, int nodenum, struct PHD_VECTOR* pos)
{
	S_Warn("[deal_with_actor_shooting] - Unimplemented!\n");
}

void stealth3_end()
{
	S_Warn("[stealth3_end] - Unimplemented!\n");
}

void stealth3_start()
{
	S_Warn("[stealth3_start] - Unimplemented!\n");
}

void special4_end()
{
	S_Warn("[special4_end] - Unimplemented!\n");
}

void special4_control()
{
	S_Warn("[special4_control] - Unimplemented!\n");
}

void special4_init()
{
	S_Warn("[special4_init] - Unimplemented!\n");
}

void special3_end()
{
	S_Warn("[special3_end] - Unimplemented!\n");
}

void special3_control()
{
	S_Warn("[special3_control] - Unimplemented!\n");
}

void special3_init()
{
	S_Warn("[special3_init] - Unimplemented!\n");
}

void special2_end()
{
	S_Warn("[special2_end] - Unimplemented!\n");
}

void special2_control()
{
	S_Warn("[special2_control] - Unimplemented!\n");
}

void special2_init()
{
	S_Warn("[special2_init] - Unimplemented!\n");
}

void special1_end()
{
	S_Warn("[special1_end] - Unimplemented!\n");
}

void special1_control()
{
	S_Warn("[special1_control] - Unimplemented!\n");
}

void special1_init()
{
	S_Warn("[special1_init] - Unimplemented!\n");
}

void richcut3_control()//2E594, 2E8A0
{
	S_Warn("[richcut3_control] - Unimplemented!\n");
}

void richcut3_end()//2E54C, 2E858
{
	S_Warn("[richcut3_end] - Unimplemented!\n");
}

void richcut3_init()//2E514, 2E820
{
	S_Warn("[richcut3_init] - Unimplemented!\n");
}

void richcut2_control()//2E4EC, 2E77C
{
	S_Warn("[richcut2_control] - Unimplemented!\n");
}

void richcut2_end()//2E4D8(<), 2E768(<) (F)
{
	lara_item->mesh_bits = 0xFFFFFFFF;
	return;
}

void richcut2_init()//2E4C0(<), 2E750(<) (F)
{
	cutrot = 1;
	lara_item->mesh_bits = 0;
	return;
}

void richcut1_control()//2E3D8, 2E668
{
	S_Warn("[richcut1_control] - Unimplemented!\n");
}

void richcut1_end()//2E3A0, 2E630
{
	S_Warn("[richcut1_end] - Unimplemented!\n");
}

void richcut1_init()//2E26C, 2E4FC
{
	S_Warn("[richcut1_init] - Unimplemented!\n");
}

void cranecut_control()
{
	S_Warn("[cranecut_control] - Unimplemented!\n");
}

void cranecut_end()
{
	S_Warn("[cranecut_end] - Unimplemented!\n");
}

void cranecut_init()
{
	S_Warn("[cranecut_init] - Unimplemented!\n");
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

void handle_actor_chatting(int speechslot, int node, int slot, int objslot, short* ranges)
{
	S_Warn("[handle_actor_chatting] - Unimplemented!\n");
}

void handle_lara_chatting(short* ranges)//2DD00(<), 2DF90(<) (F)
{
	short* poo = ranges; // original variable name
	int r1, r2, rndme;

	lara_chat_cnt = (lara_chat_cnt - 1) & 1;

	while (1)
	{
		r1 = poo[0];
		r2 = poo[1];

		if (r1 == -1)
		{
			lara.mesh_ptrs[LM_HEAD] = meshes[objects[LARA_SKIN].mesh_index + 28];
			return;
		}

		if (GLOBAL_cutseq_frame >= r1 && GLOBAL_cutseq_frame <= r2)
		{
			break;
		}

		poo += 2;
	}

	if (lara_chat_cnt == 0)
	{
		rndme = objects[(GetRandomControl() & 3) + LARA_SPEECH_HEAD1].mesh_index;
		lara.mesh_ptrs[LM_HEAD] = meshes[rndme + 28];
	}
}

void DelsHandyTeleportLara(int x, int y, int z, int yrot)//2DC14(<), 2DEA4(<) (F)
{
	lara_item->pos.x_pos = x;
	lara_item->pos.y_pos = y;
	lara_item->pos.z_pos = z;

	lara.head_x_rot = 0;
	lara.head_y_rot = 0;
	lara.torso_x_rot = 0;
	lara.torso_y_rot = 0;

	lara_item->pos.x_rot = 0;
	lara_item->pos.y_rot = yrot;
	lara_item->pos.z_rot = 0;

	IsRoomOutside(lara_item->pos.x_pos, lara_item->pos.y_pos, lara_item->pos.z_pos);
	if (IsRoomOutsideNo != lara_item->room_number)
		ItemNewRoom(lara.item_number, IsRoomOutsideNo);

	lara_item->goal_anim_state = STATE_LARA_STOP;
	lara_item->current_anim_state = STATE_LARA_STOP;
	lara_item->frame_number = anims[ANIMATION_LARA_STAY_SOLID].frame_base;
	lara_item->anim_number = ANIMATION_LARA_STAY_SOLID;

	lara_item->speed = 0;
	lara_item->fallspeed = 0;
	lara_item->gravity_status = 0;

	lara.gun_status = 0;
	camera.fixed_camera = 1;
}

void init_resident_cutseq(int num)//2DB8C(<), 2DE1C(<) (F)
{
	char* packed = cutseq_resident_addresses[num].packed_data;

	GLOBAL_cutme = (NEW_CUTSCENE*)packed;

	if (cutseq_num <= 4)
	{
		GLOBAL_cutme->orgx = (lara_item->pos.x_pos & 0xFFFFFC00) + 512;
		GLOBAL_cutme->orgy = lara_item->pos.y_pos;
		GLOBAL_cutme->orgz = (lara_item->pos.z_pos & 0xFFFFFC00) + 512;
	}

	init_cutseq_actors(packed, 1);
}

void init_cutseq_actors(char* data, int resident)
{
	S_Warn("[init_cutseq_actors] - Unimplemented!\n");
}

int Load_and_Init_Cutseq(int num)
{
	S_Warn("[Load_and_Init_Cutseq] - Unimplemented!\n");
	return 0;
}

struct ITEM_INFO* cutseq_restore_item(int num)//2D738(<), 2DA20(<)
{
	int i;
	if(level_items > 0)
	{
		for(i = 0; i < numnailed; i++)
		{
			if(items[i].object_number == num)
			{
				items[i].status = old_status_flags[numnailed];
				items[i].flags = old_status_flags2[numnailed];
				numnailed++;

				return items + i;
			}
		}
	}

	return NULL;
}

void cutseq_kill_item(int num)//2D69C(<), 2D984(<) (F)
{
	int i;
	if(level_items > 0)
	{
		for (i = 0; i < level_items; i++) {
			if (items[i].object_number == num)
			{
				old_status_flags2[numnailed] = items[i].flags;
				old_status_flags[numnailed] = items[i].status;
				numnailed++;

				items[i].status = 3;
				items[i].flags &= 0xFFFFC1FF;
				items[i].flags |= 0x20;
			}			
		}
	}
}

void deal_with_pistols(unsigned short* shootdata)
{
	struct PHD_VECTOR pos;
	int f;
	short dat;

	f = GLOBAL_cutseq_frame;

	while (1)
	{
		dat = *shootdata;
		++shootdata;

		if (dat == -1)
			break;

		if (f == (dat & CPI_FRAME_MASK))
		{
			if (dat & CPI_SHOOT_LEFT)
				cutseq_shoot_pistols(14);
			if (dat & CPI_SHOOT_RIGHT)
				cutseq_shoot_pistols(11);
		}
	}
	if (SmokeCountL || SmokeCountR)
	{
		lara.mesh_ptrs[LM_HEAD] = meshes[objects[LARA_SCREAM].mesh_index + 28];
		if (SmokeCountL)
		{
			pos.x = 4;
			pos.y = 128;
			pos.z = 40;
			GetLaraJointPos(&pos, 14);
			TriggerGunSmoke(pos.x, pos.y, pos.z, 0, 0, 0, 0, SmokeWeapon, SmokeCountL);
		}
		if (SmokeCountR)
		{
			pos.x = -16;
			pos.y = 128;
			pos.z = 40;
			GetLaraJointPos(&pos, 11);
			TriggerGunSmoke(pos.x, pos.y, pos.z, 0, 0, 0, 0, SmokeWeapon, SmokeCountR);
		}
	}
	else
	{
		lara.mesh_ptrs[LM_HEAD] = meshes[objects[LARA].mesh_index + 28];
	}

	if (lara.left_arm.flash_gun)
	{
		--lara.left_arm.flash_gun;
		trigger_weapon_dynamics(14);
	}
	if (lara.right_arm.flash_gun)
	{
		--lara.right_arm.flash_gun;
		trigger_weapon_dynamics(11);
	}
}

void trigger_weapon_dynamics(int left_or_right)//2D3E4(<), 2D6CC(<) (F)
{
	struct PHD_VECTOR pos;
	int v1, v2;
	char v3;

	pos.x = (GetRandomControl() & 0xFF) - 128;
	pos.y = (GetRandomControl() & 0x7F) - 63;
	pos.z = (GetRandomControl() & 0xFF) - 128;
	GetLaraJointPos(&pos, left_or_right);
	v1 = (GetRandomControl() & 0x3F);
	v2 = (GetRandomControl() & 0x1F) + 128;
	v3 = (GetRandomControl() & 0x3F);
	TriggerDynamic(pos.x, pos.y, pos.z, 10, v3 + 192, v2, v1);
}

void cutseq_shoot_pistols(int left_or_right)
{
	S_Warn("[cutseq_shoot_pistols] - Unimplemented!\n");
}

void cutseq_removelara_hk()
{
	S_Warn("[cutseq_removelara_hk] - Unimplemented!\n");
}

void cutseq_givelara_hk()
{
	S_Warn("[cutseq_givelara_hk] - Unimplemented!\n");
}

void cutseq_removelara_pistols()
{
	S_Warn("[cutseq_removelara_pistols] - Unimplemented!\n");
}

void cutseq_givelara_pistols()
{
	S_Warn("[cutseq_givelara_pistols] - Unimplemented!\n");
}

void CalculateObjectLightingLaraCutSeq()
{
	S_Warn("[CalculateObjectLightingLaraCutSeq] - Unimplemented!\n");
}

void finish_cutseq(int name)
{
	S_Warn("[finish_cutseq] - Unimplemented!\n");
}

void* cutseq_malloc(int size)
{
	S_Warn("[*cutseq_malloc] - Unimplemented!\n");
	return NULL;
}

void init_cutseq_malloc()//2D110(<), 2D430(<) (F)
{
	cutseq_malloc_used = 0;
	cutseq_malloc_ptr = (char*)frames;
	cutseq_malloc_free = AnimFileLen;
	return;
}

void frigup_lara()
{
	S_Warn("[frigup_lara] - Unimplemented!\n");
}

void InitPackNodes(struct NODELOADHEADER* lnode, struct PACKNODE* pnode, char* packed, int numnodes)
{
	S_Warn("[InitPackNodes] - Unimplemented!\n");
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
#if INTERNAL
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

							if ((lara_item->current_anim_state) > STATE_LARA_MONKEYSWING_TURN_LEFT ||
								(lara_item->current_anim_state) != 164 ||
								(lara_item->current_anim_state) != 165 ||
								(lara_item->current_anim_state) == 166)
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

				if ((gfLevelFlags & GF_LVOP_YOUNG_LARA))
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
					if ((gfLevelFlags & GF_LVOP_TRAIN) != 0)
					{
						if (objects[345].loaded)
						{
							//if ((objects[0x5670 + 0x121] & 1) != 0)
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







