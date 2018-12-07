#include "DELTAPAK.H"

#include "CALCHAIR.H"
#include "CALCLARA.H"
#include "CODEWAD.H"
#include "CONTROL.H"
#include "DRAW.H"
#include "DELSTUFF.H"
#include "EFFECT2.H"
#include "GAMEFLOW.H"
#include "HAIR.H"
#include "HEALTH.H"
#include "ITEMS.H"
#include "LARA.H"
#include "LARA1GUN.H"
#include "LARA2GUN.H"
#include "LOT.H"

#include "NEWINV2.H"
#include "OBJECTS.H"

#include "SPECIFIC.H"
#include "SPOTCAM.H"
#include "TEXT.H"
#include "TOMB4FX.H"
#include "TYPES.H"
#include "TYPEDEFS.H"

#if PC_VERSION
#include "GLOBAL.H"
#include "GAME.H"
#include "SPECIFIC.H"
#include "FILE.H"
#else
#include "PROFILE.H"
#include "SETUP.H"
#include "ROOMLOAD.H"
#include "MATHS.H"
#include "DRAWPHAS.H"
#include "DELTAPAK_S.H"
#include "CD.H"
#endif

#include "SPECTYPES.H"
#include <assert.h>
#include <stddef.h>
#include "SOUND.H"
#include "EFFECTS.H"
#include <stdio.h>

#if PSX_VERSION || PSXPC_VERSION
#include "MISC.H"
#endif



struct CUTSEQ_ROUTINES cutseq_control_routines[45] =
{
	{ NULL, NULL, NULL },								  // 
	{ stealth3_start, NULL, stealth3_end },				  // 
	{ stealth3_start, NULL, stealth3_end },				  // 
	{ stealth3_start, NULL, stealth3_end },				  // 
	{ stealth3_start, NULL, stealth3_end },				  // 
	{ joby6_init, joby6_control, joby6_end },			  // JOBY6 (into suit)
	{ andy5_init, andy5_control, andy5_end },			  // ANDY5 (monk)
	{ andrea3b_init, andrea3b_control, andrea3b_end },	  // ANDREA3b (snakes)
	{ andrea3_init, andrea3_control, andrea3_end },		  // ANDREA3 (larson shootout)
	{ andy4b_init, andy4b_control, andy4b_end },		  // ANDY4b (imps2)
	{ andy4_init, andy4_control, andy4_end },			  // ANDY4 (imps1)
	{ richcut4_init, richcut4_control, richcut4_end },	  // RICHCUT4 (twogun kits up)
	{ joby10_init, joby10_control, joby10_end },		  // JOBY10 (lara & admiral 2)
	{ joby9_init, joby9_control, joby9_end },			  // JOBY9 (lara & admiral 1)
	{ andy3_init, andy3_control, andy3_end },			  // ANDY3 (catapault)
	{ joby5_init, joby5_control, joby5_end },			  // JOBY5 (periscope)
	{ andrea2_init, andrea2_control, andrea2_end },		  // ANDREA2
	{ andrea1_init, andrea1_control, andrea1_end },		  // ANDREA1
	{ joby4_init, joby4_control, joby4_end },			  // Joby4 (lara+navyboyz+admiral)
	{ andy2_init, andy2_control, andy2_end },			  // Andy2 (priest + younglara)
	{ hamgate_init, hamgate_control, hamgate_end },		  // Rich1 (hammer gate thing)
	{ andy1_init, andy1_control, andy1_end },			  // Andy1 (hangman + younglara)
	{ joby3_init, joby3_control, joby3_end },			  // Joby Cut 3 (Lara Jump+Sailor)
	{ richcut3_init, richcut3_control, richcut3_end },	  // Rich Cut 3 (Lara+Gun)
	{ richcut1_init, richcut1_control, richcut1_end },	  // Rich Cut 1 (Lara+Guard)
	{ joby2_init, joby2_control, joby2_end },			  // Joby Cut 2 (Admiral+Sergie+Sailors)
	{ richcut2_init, richcut2_control, richcut2_end },	  // Rich Cut 2 (Voncroy etc)
	{ cranecut_init, cranecut_control, cranecut_end },	  // Joby Crane Cut
	{ special1_init, special1_control, special1_end },	  // Title (VCI bookshelf + Croft manor)
	{ special2_init, special2_control, special2_end },	  // Title (VCI office + Church)
	{ special3_init, special3_control, special3_end },	  // Title (VCI corridor + Egypt)
	{ special4_init, special4_control, special4_end },	  // Title (VCI soldier fire)
	{ joby8_init, joby8_control, joby8_end },			  // JOBY8 (out of suit)
	{ andy6_init, andy6_control, andy6_end },			  // ANDY6 (white hair priest)
	{ andypew_init, andypew_control, andypew_end },		  // ANDYPEW (!)
	{ andy7_init, andy7_control, andy7_end },			  // ANDY7 (white hair priest2)
	{ cossack_init, cossack_control, cossack_end },		  // COSSACK (phil)
	{ andy9_init, andy9_control, andy9_end },			  // ANDY9 (priest/cossack)
	{ andy8_init, andy8_control, andy8_end },			  // ANDY8 (chalk)
	{ andy10_init, andy10_control, andy10_end },		  // ANDY10 (SWAMPY)
	{ joby7_init, joby7_control, joby7_end },			  // JOBY7 (Underwater)
	{ andrea4_init, andrea4_control, andrea4_end },		  // ANDREA4 (lara/pierre)
	{ monk2_init, monk2_control, monk2_end },			  // MONK2
	{ swampy_init, swampy_control, swampy_end },		  // SWAMPY
	{ andy11_init, andy11_control, andy11_end },		  // ANDY11 (long one!)
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

short actor_chat_ranges_joby8[14] =
{
	0x02B3, 0x03A8, 0x0447, 0x04E2, 0x064F, 0x068F, 0x069F, 0x06ED, 0x076D, 0x0799, 
	0x07A6, 0x07F7, 0xFFFF, 0xFFFF
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

short priest_chat_ranges_andy6[18] =
{
	0x0208, 0x02A0, 0x0319, 0x0338, 0x039C, 0x03AA, 0x03B4, 0x03D1, 0x03E0, 0x0471, 
	0x047F, 0x04AD, 0x04C4, 0x0512, 0x051D, 0x0565, 0xFFFF, 0xFFFF
};

short priest_chat_ranges_andy2[24] =
{
	0x00EF, 0x014B, 0x02E0, 0x0321, 0x0332, 0x0367, 0x050D, 0x051B, 0x052C, 0x059D,
	0x069A, 0x06B4, 0x06C8, 0x074E, 0x0765, 0x07B8, 0x083D, 0x086B, 0x087D, 0x08EF, 
	0x0916, 0x0980, 0xFFFF, 0xFFFF
};

short voncroy_chat_ranges_richcut2[20] =
{
	0x01E1, 0x01F5, 0x0290, 0x02AC, 0x02B7, 0x02F7, 0x0300, 0x033E, 0x039F, 0x03CA, 
	0x03D7, 0x0408, 0x0414, 0x0443, 0x05C6, 0x0628, 0x0638, 0x0663, 0xFFFF, 0xFFFF
};

short associate_chat_ranges_richcut2[12] =
{
	0x045D, 0x0515, 0x0681, 0x0723, 0x0731, 0x0741, 0x074A, 0x0764, 0x0772, 0x07AA, 
	0xFFFF, 0xFFFF
};

short guard_chat_ranges_richcut2[10] =
{
	0x0036, 0x00B0, 0x0205, 0x0287, 0x034F, 0x0392, 0x0529, 0x054C, 0xFFFF, 0xFFFF
};

short hanged_man_chat_ranges_andy1[18] =
{
	0x01EE, 0x022D, 0x023E, 0x02F1, 0x0348, 0x052A, 0x0596, 0x084C, 0x0890, 0x0BFB, 
	0x0C81, 0x0C8F, 0x0C9C, 0x0D4C, 0x0D5A, 0x0F16, 0xFFFF, 0xFFFF
};

short priest_chat_ranges_andy9[20] =
{
	0x024C, 0x0270, 0x0281, 0x02A7, 0x02BB, 0x0310, 0x0679, 0x06B4, 0x06C7, 0x0731, 
	0x073F, 0x077A, 0x0AA3, 0x0ACE, 0x0AF0, 0x0B38, 0x0F8F, 0x0FE8, 0xFFFF, 0xFFFF
};

short knight_chat_ranges_andy9[14] =
{
	0x0130, 0x0228, 0x031E, 0x0389, 0x0449, 0x0634, 0x07A4, 0x0A83, 0x0B51, 0x0F0E, 
	0x1012, 0x11F0, 0xFFFF, 0xFFFF
};

short priest_chat_ranges_andy11[30] =
{
	0x0427, 0x044B, 0x045F, 0x0486, 0x06B6, 0x0734, 0x09DA, 0x0A15, 0x0B4F, 0x0B65, 
	0x0B78, 0x0BB3, 0x0DD6, 0x0E22, 0x1164, 0x11D4, 0x11E5, 0x1271, 0x127C, 0x12AC, 
	0x1311, 0x13C8, 0x1549, 0x15E4, 0x1633, 0x1620, 0x1640, 0x16C0, 0xFFFF, 0xFFFF
};
short knight_chat_ranges_andy11[14] =
{
	0x01B4, 0x03BE, 0x04C7, 0x0698, 0x0890, 0x08C4, 0x08D6, 0x0942, 0x1081, 0x1105, 
	0x13E9, 0x150A, 0xFFFF, 0xFFFF
};

unsigned short special2_pistols_info[13] =
{
	0x00C4, 0x00CC, 0x00D4, 0x00DC, 0x00E4, 0x00EC, 0x00F4, 0x00FC, 0x0104, 0x010C, 
	0x0114, 0x0121, 0xFFFF
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
enum camera_type GLOBAL_oldcamtype;
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
int special_num;

#if DEBUG_VERSION
	#define CD_PLAY_MODE 1
#else
	#define CD_PLAY_MODE 0
#endif

void andy11_end()//32D6C(<), 3326C(<) (F)
{
	cutseq_restore_item(ANIMATING15);
}

void andy11_control()//32C70(<), 33108(<) (F)
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
		lara_item->mesh_bits = 0xFFFFFFFF;
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

	handle_lara_chatting(lara_chat_ranges_andy11);
	handle_actor_chatting(21, 2, 4, SAILOR_MIP, priest_chat_ranges_andy11); // todo find the names
	handle_actor_chatting(23, 15, 1, SWAT_MIP, knight_chat_ranges_andy11);
	actor_chat_cnt = (actor_chat_cnt - 1) & 1;
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
	item->status = ITEM_ACTIVE;
	item->flags |= IFLAG_ACTIVATION_MASK;
}

struct ITEM_INFO* ResetCutanimate(int objnum)//32A80(<), 32F18(<) (F)
{
	struct ITEM_INFO* item = find_a_fucking_item(objnum);

	item->anim_number = objects[objnum].anim_index;
	item->frame_number = anims[item->anim_number].frame_base;
	RemoveActiveItem(item - items);	
	item->status = ITEM_INACTIVE;
	item->flags &= ~IFLAG_ACTIVATION_MASK;

	return item;
}

void trigger_title_spotcam(int num)//32904(<), 32D9C(<) (F)
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
		S_CDPlay(CDA_XA11_FLYBY1, CD_PLAY_MODE);
	}
	else if (num == 2)
	{
		S_CDPlay(CDA_XA11_FLYBY2, CD_PLAY_MODE);
	}
	else if (num == 3)
	{
		S_CDPlay(CDA_XA11_FLYBY3, CD_PLAY_MODE);
	}
	else if (num == 4)
	{
		S_CDPlay(CDA_XA12_FLYBY4, CD_PLAY_MODE);
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
	SetCutNotPlayed(CUT_SWAMPY);
	AddActiveItem(find_a_fucking_item(GREEN_TEETH) - items);
	DelsHandyTeleportLara(42477, 12456, 55982, 28953);
	lara.water_status = LW_UNDERWATER;
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
		item->status = ITEM_INVISIBLE;
		RemoveActiveItem(item - items);
		DisableBaddieAI(item - items);
		item->flags |= IFLAG_INVISIBLE;
	}

	lara.water_status = LW_UNDERWATER;
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
	handle_actor_chatting(23, 8, 1, PIERRE, pierre_chat_ranges4);
	actor_chat_cnt = (actor_chat_cnt - 1) & 1;
}

void andrea4_init()//323C0(<), 32858(<) (F)
{
}

void joby7_end()//32328(<), 327C0(<) (F)
{
	lara_item->mesh_bits = 0xFFFFFFFF;
	cutseq_restore_item(ANIMATING2);
	AddDisplayPickup(PICKUP_ITEM1);
	DelsHandyTeleportLara(30049, 17583, 69794, -13706);
	lara.water_status = LW_UNDERWATER;
	lara_item->pos.x_rot = 1090;
	lara_item->goal_anim_state = STATE_LARA_UNDERWATER_STOP;
	lara_item->current_anim_state = STATE_LARA_UNDERWATER_STOP;
	lara_item->frame_number = anims[ANIMATION_LARA_UNDERWATER_IDLE].frame_base;
	lara_item->anim_number = ANIMATION_LARA_UNDERWATER_IDLE;
	lara.Anxiety = 80;
}

void joby7_control()//3210C(<), 325A4(<) (F)
{
	struct PHD_VECTOR s, d;
	int f, brightme, b;
	short room_no;
	
	f = GLOBAL_cutseq_frame;
	if (f == 750)
	{
		cutseq_meshbits[6] |= 0x80000000;
	}
	else if (f >= 650 && f <= 1050)
	{

		s.x = 0;
		s.y = -100;
		s.z = 0;
		GetActorJointAbsPosition(6, 0, &s);
		TriggerDynamic(s.x, s.y, s.z, ((f - 650) >> 5) + 8, 0, 0, MIN(f - 650, 220));
	}
	if (f == 1410)
	{
		s.x = 0;
		s.y = -100;
		s.z = 0;
		GetActorJointAbsPosition(1, 0, &s);
		room_no = lara_item->room_number;
		IsRoomOutsideNo = -1;
		IsRoomOutside(s.x, s.y, s.z);
		if (IsRoomOutsideNo != -1)
		{
			room_no = IsRoomOutsideNo;
		}
		TriggerExplosionBubble(s.x, s.y, s.z, room_no);
		TriggerExplosionSparks(s.x, s.y, s.z, 2, -2, 1, room_no);
		TriggerExplosionSparks(s.x, s.y, s.z, 2, -1, 1, room_no);
	}
	s.x = 0;
	s.y = -1024;
	s.z = -128;
	GetActorJointAbsPosition(1, 7, &s);
	d.x = 0;
	d.y = -20480;
	d.z = -128;
	GetActorJointAbsPosition(1, 7, &d);
	LaraTorch(&s, &d, 0, 255);
	TriggerEngineEffects_CUT();
	handle_actor_chatting(17, 14, 1, CROW_MIP, lara_chat_ranges_joby7);
	actor_chat_cnt = (actor_chat_cnt - 1) & 1;
}

void joby7_init()//320D0(<), 32568(<) (F)
{
	lara_item->mesh_bits = 0;
	cutseq_kill_item(ANIMATING2);
	cutseq_meshbits[6] &= 0x7FFFFFFF;
}

void andy10_end()//3202C(<), 324C4(<) (F)
{
	lara_item->mesh_bits = 0xFFFFFFFF;
	SetCutPlayed(CUT_SWAMPY);
	Cutanimate(ANIMATING12);
	Cutanimate(ANIMATING13);
	FlipMap(7);
	DelsHandyTeleportLara(SECTOR_TO_WORLD(38), SECTOR_TO_WORLD(14.5), SECTOR_TO_WORLD(47), 0);
	lara.water_status = LW_UNDERWATER;
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
		lara_item->mesh_bits = 0xFFFFFFFF;
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
	item->status = ITEM_INVISIBLE;
	RemoveActiveItem(item - items);
	DisableBaddieAI(item - items);
	item->flags |= IFLAG_INVISIBLE;
	lara.water_status = LW_UNDERWATER;
	FlipMap(7);
	disable_horizon = 1;
}

void do_chalk_meshswap()//31D24(<), 321BC(<) (F)
{
	short* temp = lara.mesh_ptrs[LM_RHAND];
	lara.mesh_ptrs[LM_RHAND] = meshes[objects[MAFIA_MIP].mesh_index + 2 * LM_RHAND];
	meshes[objects[MAFIA_MIP].mesh_index + 2 * LM_RHAND] = temp;
}

void andy8_end()//31CF8(<), 32190(<) (F)
{
	SetCutPlayed(CUT_COSSACK);

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
		lara_item->mesh_bits = 0xFFFFFFFF;
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
	lara_item->mesh_bits = 0xFFFFFFFF;
}

void andy9_control()//31BA4(<), 31FD4(<) (F)
{
	int f = GLOBAL_cutseq_frame;

	if (f == 151 || f == 1033 || f == 3868)
		lara_item->mesh_bits = 0xFFFFFFFF;
	if (f == 192 || f == 1099 || f == 3974)
		lara_item->mesh_bits = 0;

	handle_lara_chatting(lara_chat_ranges_andy9);
	handle_actor_chatting(21, 2, 4, SAILOR_MIP, priest_chat_ranges_andy9); // todo find the names
	handle_actor_chatting(23, 15, 1, SWAT_MIP, knight_chat_ranges_andy9);
	actor_chat_cnt = (actor_chat_cnt - 1) & 1;
}

void andy9_init()//31B7C(<), 31FAC(<) (F)
{
	cutseq_kill_item(ANIMATING15);
	lara_item->mesh_bits = 0;
}

void TriggerDelBrownSmoke(long x, long y, long z)//319D0(<), 31E00(<) (F)
{
	struct SPARKS* sptr;
	long size;

	sptr = &spark[GetFreeSpark()];
	sptr->On = 1;
	sptr->sR = 50;
	sptr->sG = 45;
	sptr->sB = 40;
	sptr->dR = 40;
	sptr->dG = 35;
	sptr->dB = 30;
	sptr->ColFadeSpeed = 2;
	sptr->FadeToBlack = 5;
	sptr->TransType = 2;
	sptr->Life = sptr->sLife = (GetRandomControl() & 7) + 20;
	sptr->x = (GetRandomControl() & 0x7F) + x - 63;
	sptr->y = (GetRandomControl() & 0x7F) + y - 63;
	sptr->z = (GetRandomControl() & 0x7F) + z - 63;
	sptr->Xvel = ((GetRandomControl() & 0xFFF) - 2048) >> 2;
	sptr->Yvel = (GetRandomControl() & 0xFF) - 128;
	sptr->Friction = 2;
	sptr->Flags = 538;
	sptr->Zvel = ((GetRandomControl() & 0xFFF) - 2048) >> 2;
	sptr->RotAng = GetRandomControl() & 0xFFF;
	sptr->Scalar = 2;
	sptr->RotAdd = (GetRandomControl() & 0xF) + 16;
	sptr->Gravity = -3 - (GetRandomControl() & 3);
	sptr->MaxYvel = -4 - (GetRandomControl() & 3);
	size = (GetRandomControl() & 0x1F) + 40;
	sptr->dSize = size;
	sptr->sSize = size >> 2;
	sptr->Size = size >> 2;
}

void cossack_end()//31998(<), 31DC8(<) (F)
{
	DelsHandyTeleportLara(SECTOR_TO_WORLD(75.75), SECTOR_TO_WORLD(4.75), SECTOR_TO_WORLD(36.5), 0);
	SetCutNotPlayed(CUT_COSSACK);
}

void cossack_control()//3178C(<), 31BBC(<) (F)
{
	struct PHD_VECTOR pos;
	int n;
	int f = GLOBAL_cutseq_frame;

	if (f == 98
		|| f == 344
		|| f == 743
		|| f == 1263)
	{
		lara_item->mesh_bits = 0;
	}
	if (f == 281 || f == 468 || f == 901 || f == 1339)
	{
		lara_item->mesh_bits = 0xFFFFFFFF;
	}
	if (f == 156)
	{
		pos.x = 0;
		pos.y = 120;
		pos.z = 0;
		GetActorJointAbsPosition(1, 17, &pos);
		for (n = 0; n < 7; n++)
		{
			TriggerDelBrownSmoke(pos.x, pos.y, pos.z);
		}
	}
	else if (f == 157)
	{
		pos.x = 0;
		pos.y = 120;
		pos.z = 0;
		GetActorJointAbsPosition(1, 13, &pos);
		for (n = 0; n < 7; n++)
		{
			TriggerDelBrownSmoke(pos.x, pos.y, pos.z);
		}
	}
	else
	{
		if (f >= 581 && f <= 620)
		{
			pos.z = 0;
			pos.y = 0;
			pos.x = 0;
			GetLaraJointPos(&pos, LJ_RHAND);
			TriggerDelBrownSmoke(pos.x, pos.y, pos.z);

			pos.z = 0;
			pos.y = 0;
			pos.x = 0;
			GetLaraJointPos(&pos, LJ_LHAND);
			TriggerDelBrownSmoke(pos.x, pos.y, pos.z);
		}
		if (f >= 1110 && f <= 1125)
		{
			pos.z = 0;
			pos.y = 0;
			pos.x = 0;
			GetLaraJointPos(&pos, LJ_RHAND);
			TriggerDelBrownSmoke(pos.x, pos.y, pos.z);
		}
		if (f >= 1111 && f <= 1126)
		{
			pos.z = 0;
			pos.y = 0;
			pos.x = 0;
			GetLaraJointPos(&pos, LJ_RTHIGH);
			TriggerDelBrownSmoke(pos.x, pos.y, pos.z);
		}
	}
}

void cossack_init()//31784(<), 31BB4(<) (F)
{
	return;
}

void andy7_end()//31754(<), 31B84(<) (F)
{
	DelsHandyTeleportLara(78336, 5503, 41658, 0);
}

void andy7_control()//31704(<), 31B34(<) (F)
{
	handle_lara_chatting(lara_chat_ranges_andy7);
	handle_actor_chatting(21, 2, 1, SAILOR_MIP, priest_chat_ranges_andy7);
	actor_chat_cnt = (actor_chat_cnt - 1) & 1;
}

void andy7_init()//316F4(<), 31B24(<) (F)
{
	cutrot = 1;
}

void andypew_end()//316C0(<), 31AF0(<) (F)
{
	cutseq_restore_item(PUZZLE_HOLE2);
	DelsHandyTeleportLara(45556, 7680, 23415, -32768);
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

void andy6_control()//315F8(<), 319B4(<) (F)
{
	struct PHD_VECTOR pos;

	if (GLOBAL_cutseq_frame == 900)
	{
		lara_item->mesh_bits = 0;
	}
	else if (GLOBAL_cutseq_frame == 1401)
	{
		lara_item->mesh_bits = 0xFFFFFFFF;
	}
	pos.x = 0;
	pos.y = 48;
	pos.z = 240;
	GetActorJointAbsPosition(1, 8, &pos);
	TriggerDynamic(pos.x, pos.y, pos.z, 
	               12 - (GetRandomControl() & 1), 
	               (GetRandomControl() & 0x3F) + 192, 
	               (GetRandomControl() & 0x1F) + 96, 0);
	DelTorchFlames(&pos);
	handle_lara_chatting(lara_chat_ranges_andy6);
	handle_actor_chatting(21, 2, 1, SAILOR_MIP, priest_chat_ranges_andy6);
	actor_chat_cnt = (actor_chat_cnt - 1) & 1;
}

void andy6_init()//30D84(<), 31104(<) (F)
{
	cutrot = 1;
	setup_preist_meshswap();
}

void joby8_end()//315A0(<), 3195C(<) (F)
{
	DelsHandyTeleportLara(58880, 5120, 76288, 0);
}

void joby8_control()//310E0, 31460 (F)
{
	short room_num;
	
	switch (GLOBAL_cutseq_frame)
	{
	case 147:
		cutseq_meshbits[2] |= 0x80000000;
		cutseq_meshbits[3] |= 0x80000000;
		cutseq_meshbits[4] |= 0x80000000;
		break;
	case 2440:
		cutseq_meshbits[8] &= 0x7FFFFFFF;
		break;
	case 2681:
		cutseq_meshbits[1] &= 0x7FFFFFFF;
		cutseq_meshbits[2] &= 0x7FFFFFFF;		
		cutseq_meshbits[3] &= 0x7FFFFFFF;		
		cutseq_meshbits[4] &= 0x7FFFFFFF;
		cutseq_meshbits[5] &= 0x7FFFFFFF;
		break;
	case 440:
		lara_item->mesh_bits = 0xFFFFFFFF;
		break;
	case 2103:
		cutseq_meshswapbits[7] = 9216;
		break;
	case 2724:
		room_num = lara_item->room_number;
		GetHeight(GetFloor(lara_item->pos.x_pos + SECTOR(1), lara_item->pos.y_pos, lara_item->pos.z_pos, &room_num), lara_item->pos.x_pos + 1024, lara_item->pos.y_pos, lara_item->pos.z_pos);
		TestTriggers(trigger_index, 1, 0);
		break;
	}

	if (GLOBAL_cutseq_frame >= 2440 && GLOBAL_cutseq_frame <= 2659)
	{
		int r = (GetRandomControl() & 0x3F) + 96;
		int g = GetRandomControl() % r;
		int b = GetRandomControl() & 0xF;
		int i;
		struct SPARKS* sptr;
		struct PHD_VECTOR s;
		int scale;
		struct PHD_VECTOR d;
		
		for (i = 0; i < 3; i++)
		{
			s.x = 0;
			s.y = 0;
			s.z = 0;

			GetActorJointAbsPosition(1, GetRandomControl() % 20, &s);

			sptr = &spark[GetFreeSpark()];

			sptr->On = 1;

			sptr->dR = r;
			sptr->dG = g;
			sptr->dB = b;

			scale = (GetRandomControl() & 0x3F) - 64;
			sptr->sR = scale;
			sptr->sB = scale;
			sptr->sG = scale;

			sptr->ColFadeSpeed = 8;
			sptr->TransType = 2;
			sptr->FadeToBlack = 4;

			sptr->Life = 12;
			sptr->sLife = 12;

			sptr->x = s.x;
			sptr->y = s.y;
			sptr->z = s.z;

			sptr->Xvel = 2 * (GetRandomControl() & 0x1FF) - 512;
			sptr->Yvel = 2 * (GetRandomControl() & 0x1FF) - 512;
			sptr->Zvel = 2 * (GetRandomControl() & 0x1FF) - 512;

			sptr->Friction = 51;
			sptr->MaxYvel = 0;
			sptr->Gravity = 0;

			sptr->Flags = 0;

			TriggerFireFlame(s.x, s.y, s.z, -1, 254);
		}

		d.x = s.x + (SIN(2 * (GetRandomControl() & 0x7FFF)) >> 3);
		d.y = s.y;
		d.z = s.z + (COS(2 * (GetRandomControl() & 0x7FFF)) >> 3);

		TriggerLightning(&s, &d, (GetRandomControl() & 0xF) + 30, RGBA(r, g, b, 16), 15, 40, 5);
		TriggerDynamic(s.x, s.y, s.z, 10, (GetRandomControl() & 0x7F) + 128, g, b);
	}
	else if(GLOBAL_cutseq_frame >= 2681 && GLOBAL_cutseq_frame <= 2724)
	{
		struct PHD_VECTOR s;
		int scale;
		int r;
		int g;
		int b;
		
		s.x = 512;
		s.y = 0;
		s.z = 0;
		GetLaraJointPos(&s, LJ_HIPS);

		scale = (GLOBAL_cutseq_frame - 2681) >> 4;

		r = (GetRandomControl() & 0x3F) + 192 >> scale;
		g = ((GetRandomControl() & 0x1F) + 128) >> scale;
		b = (GetRandomControl() & 0x3F) >> scale;

		if (GetRandomControl() & 1)
			TriggerDynamic(s.x, s.y, s.z, 24, r, g, b);

		TriggerDynamic(s.x, s.y, s.z, 31, r, g, b);
	}

	handle_lara_chatting(lara_chat_ranges_joby8);
	handle_actor_chatting(23, 3, 1, LION_MIP, actor_chat_ranges_joby8);
	actor_chat_cnt = (actor_chat_cnt - 1) & 1;
}

void joby8_init()//31024(<), 313A4(<) (F)
{
	short room_number = lara_item->room_number;

	cutseq_kill_item(DOOR_TYPE4);
	cutseq_kill_item(ANIMATING16);
	lara_item->mesh_bits = 0x81FF01FFu;
	GetHeight(
		GetFloor(lara_item->pos.x_pos, lara_item->pos.y_pos, lara_item->pos.z_pos, &room_number), 
		lara_item->pos.x_pos, lara_item->pos.y_pos, lara_item->pos.z_pos);
	TestTriggers(trigger_index, 1, 0);
	cutseq_meshswapbits[7] = 128;
	cutseq_meshbits[2] &= 0x7FFFFFFFu;	
	cutseq_meshbits[3] &= 0x7FFFFFFFu;
	cutseq_meshbits[4] &= 0x7FFFFFFFu;
	cutrot = 0;
}

void joby6_end()//30FEC(<), 3136C(<) (F)
{
	lara_item->mesh_bits = 0xFFFFFFFF;
	lara.mesh_ptrs[LM_HIPS] = meshes[objects[LARA].mesh_index];
}

void joby6_control()//30FA0(<), 31320(<) (F)
{
	if (GLOBAL_cutseq_frame == 542)
	{
		lara_item->mesh_bits = 0x81FF01FFu;
		lara.mesh_ptrs[LM_HIPS] = meshes[objects[MESHSWAP3].mesh_index];
	}
}

void joby6_init()//30F48(<), 312C8(<) (F)
{
	cutseq_kill_item(ANIMATING10);
	cutseq_kill_item(ANIMATING10_MIP);
	cutseq_kill_item(ANIMATING16);
	cutseq_kill_item(DOOR_TYPE4);
	cutseq_kill_item(PUZZLE_DONE3);
	cutseq_kill_item(PUZZLE_DONE4);
	cutseq_kill_item(PUZZLE_HOLE3);
	cutseq_kill_item(PUZZLE_HOLE4);
}

void andy5_end()//30F28(<), 312A8(<) (F)
{
	cutseq_restore_item(PUZZLE_HOLE2);
	return;
}

void andy5_control()//30DA4(<), 31124(<) (F)
{
	struct PHD_VECTOR pos;
	int f = GLOBAL_cutseq_frame;

	if (f >= 310)
	{
		if (f < 350)
		{
			if (cut_seethrough > 32)
				cut_seethrough -= 4;
		}
		else if (f <= 450)
		{
			cut_seethrough += 8;

			if (cut_seethrough > 128) // todo check this if it doesn't work
			{
				cut_seethrough = 128;
			}
		}		
	}

	if (f == 451)
	{
		cut_seethrough = 128;
	}
	else if (f >= 1100)
	{
		cut_seethrough -= 4;
		if (cut_seethrough < 0)
			cut_seethrough = 0;
	}

	pos.x = 0;
	pos.y = 0;
	pos.z = 0;

	if (f >= 1100)
	{
		if (!cut_seethrough)
			return GetActorJointAbsPosition(1, 0, &pos);
		f = cut_seethrough + (GetRandomControl() & 0x1F);
	}
	else
	{
		f = (GetRandomControl() & 0x3F) + 128;
	}

	return TriggerDynamic(pos.x, pos.y, pos.z, 10, GetRandomControl() & 0xF, (GetRandomControl() & 0x1F) + 16, f);
}

void andy5_init()//30D84(<), 31104(<) (F)
{
	cutseq_kill_item(PUZZLE_HOLE2);
	return;
}

void andrea3b_end()//30C54(<), 30FD4(<) (F)
{
	struct ITEM_INFO* item;
	int i;

	disable_horizon = 0;
	cutseq_removelara_pistols();

	if (level_items > 0)
	{
		for (i = 0; i < level_items; i++)
		{
			item = &items[i];
			if (item->object_number == HYDRA)
			{
				item->status = ITEM_ACTIVE;
				item->flags |= IFLAG_INVISIBLE;
				AddActiveItem(item - items);
				EnableBaddieAI(item - items, 1);
			}
		}
	}

	DelsHandyTeleportLara(56846, 0, 26986, -15360);
}

void andrea3b_control()//30B08(<), 30E88(<) (F)
{
	int f = GLOBAL_cutseq_frame;
	
	cutseq_meshbits[4] = -1;

	if (f == 301 || f == 639 || f == 781)
	{
		lara_item->mesh_bits = 0;
	}
	else if (f == 512 || f == 692 || f == 1084)
	{
		lara_item->mesh_bits = 0xFFFFFFFF;
	}
	else if (f == 1191)
	{
		cutseq_meshbits[1] &= 0x7FFFFFFFu;
		cutseq_meshbits[2] |= 0x80000000;
		cutseq_meshbits[3] |= 0x80000000;
		cutseq_meshbits[4] |= 0x80000000;
	}
	else if (f == 550)
	{
		cutseq_meshbits[2] = -1;
		cutseq_meshbits[3] = -1;
	}
	else if (f == 1150)
	{
		cutseq_meshbits[2] &= 0x7FFFFFFFu;
		cutseq_meshbits[3] &= 0x7FFFFFFFu;
		cutseq_meshbits[4] &= 0x7FFFFFFFu;
	}

	handle_lara_chatting(lara_chat_ranges_andrea3b);
	handle_actor_chatting(21, 8, 1, LARSON, larson_chat_ranges3b);
	actor_chat_cnt = (actor_chat_cnt - 1) & 1;
}

void andrea3b_init()//30A1C(<), 30D9C(<) (F)
{
	struct ITEM_INFO* item;

	cutseq_givelara_pistols();
	cutseq_kill_item(ANIMATING10);

	cutseq_meshbits[2] = 0x80000F00u;
	cutseq_meshbits[3] = 0x80000F00u;
	cutseq_meshbits[4] = 0x80000F00u;

	item = find_a_fucking_item(LARSON);
	item->status = ITEM_INVISIBLE;
	RemoveActiveItem(item - items);
	DisableBaddieAI(item - items);
	item->flags |= IFLAG_INVISIBLE;
	disable_horizon = 1;
}

void andrea3_end()//30904(<), 30C84(<) (F)
{
	struct ITEM_INFO* item;

	cutseq_removelara_pistols();

	item = find_a_fucking_item(LARSON);
	item->anim_number = objects[LARSON].anim_index;
	item->flags |= IFLAG_INVISIBLE;
	item->frame_number = anims[objects[LARSON].anim_index].frame_base;
	item->status = ITEM_ACTIVE;

	AddActiveItem(item - items);
	EnableBaddieAI(item - items, 1);

	DelsHandyTeleportLara(55808, 0, 30208, -32768);
}

void andrea3_control()//30870(<), 30BF0(<) (F)
{
	if (GLOBAL_cutseq_frame == 332)
	{
		lara_item->mesh_bits = 0;
	}
	else if (GLOBAL_cutseq_frame == 421)
	{
		lara_item->mesh_bits = 0xFFFFFFFF;
	}

	deal_with_pistols(andrea3_pistols_info);
	handle_lara_chatting(lara_chat_ranges_andrea3);
	handle_actor_chatting(21, 8, 1, LARSON, larson_chat_ranges3);
	actor_chat_cnt = (actor_chat_cnt - 1) & 1;
}

void andrea3_init()//30850(<), 30BD0(<) (F)
{
	cutseq_givelara_pistols();
	return;
}

void do_clanger_meshswap()//3081C(<), 30B9C(<) (F)
{
	short* temp = lara.mesh_ptrs[LM_RHAND];
	lara.mesh_ptrs[LM_RHAND] = meshes[objects[MESHSWAP2].mesh_index + 2 * LM_RHAND];
	meshes[objects[MESHSWAP2].mesh_index + 2 * LM_RHAND] = temp;
}

void andy4b_end()//307EC(<), 30B6C(<) (F)
{
	DelsHandyTeleportLara(43543, 5376, 47285, -32768);
	lara.puzzleitems[2] = 0;
}

void andy4b_control()//30710(<), 30A90(<) (F)
{
	struct PHD_VECTOR pos;
	int n, actor;
	int f = GLOBAL_cutseq_frame;

	if (GLOBAL_cutseq_frame == 510 || GLOBAL_cutseq_frame == 662)
	{
		do_clanger_meshswap();
	}

	if (f == 697 || f == 708 || f == 723 || f == 735)
	{
		if (f == 708) actor = 2;
		else if (f == 697) actor = 3;
		else if (f == 735) actor = 4;
		else actor = 1;

		for (n = 0; n < 16; n++)
		{
			pos.z = 0;
			pos.y = 0;
			pos.x = 0;
			GetActorJointAbsPosition(actor, 0, &pos);
			TriggerDelSmoke(pos.x, pos.y, pos.z, 88);
		}
	}
}

void andy4b_init()//306F0(<), 30A70(<) (F)
{
	cutseq_kill_item(ANIMATING5_MIP);
	return;
}

void andy4_end()//306B4(<), 30A34(<) (F)
{
	cutseq_restore_item(ANIMATING5_MIP);
	DelsHandyTeleportLara(43484, 5376, 50626, 0);
	SetCutNotPlayed(CUT_ANDY4);
}

void andy4_control()//305BC(<), 3093C(<) (F)
{
	struct PHD_VECTOR pos;
	int n;

	if (GLOBAL_cutseq_frame == 733)
	{
		for (n = 0; n < 8; n++)
		{
			pos.x = 0;
			pos.y = 0;
			pos.z = 0;
			GetActorJointAbsPosition(1, 0, &pos);
			TriggerDelSmoke(pos.x, pos.y, pos.z, 88);
			pos.x = 0;
			pos.y = 0;
			pos.z = 0;
			GetActorJointAbsPosition(2, 0, &pos);
			TriggerDelSmoke(pos.x, pos.y, pos.z, 88);
			GetActorJointAbsPosition(3, 0, &pos); // todo weird
			pos.x = 0;
			pos.y = 0;
			pos.z = 0;
			TriggerDelSmoke(0, 0, 0, 88);
			pos.x = 0;
			pos.y = 0;
			pos.z = 0;
			GetActorJointAbsPosition(4, 0, &pos);
			TriggerDelSmoke(pos.x, pos.y, pos.z, 88);
		}
	}
}

void andy4_init()//3059C(<), 3091C(<) (F)
{
	cutseq_kill_item(ANIMATING5_MIP);
	return;
}

void richcut4_end()//30560(<), 308E0(<) (F)
{
	find_a_fucking_item(SAILOR_MIP)->mesh_bits = -1;
	DelsHandyTeleportLara(35328, 0, 35328, -16384);
	lara_item->mesh_bits = 0xFFFFFFFF;
}

void richcut4_control()//30478(<), 307F8(<) (F)
{
	struct ITEM_INFO* item;
	int f = GLOBAL_cutseq_frame;

	if (f >= 300 && f <= 312)
	{
		item = find_a_fucking_item(SAILOR_MIP);
		if (!(f & 1))
			item->mesh_bits &= ~(1 << (8 - ((f - 300) >> 1)));
	}
	
	if (f != 308)
	{
		if (f == 534)
		{
			cutseq_meshswapbits[1] &= 0xFFFFFEFF;
			cutseq_meshbits[2] &= 0xFFFFFFDF;
		}
		else if (f == 557)
		{
			cutseq_meshswapbits[1] &= 0xFFFFFFDF;
			cutseq_meshbits[2] &= 0xFFFFFFFB;
		}
	}
	else
	{
		cutseq_meshbits[2] |= 4;
	}
}

void richcut4_init()//303E0(<), 30760(<) (F)
{
	cutrot = 3;
	// todo maybe it's 10,16 (on psx) instead of 11,17 (on pc)
	meshes[objects[TWOGUN].mesh_index + 11] = meshes[objects[MAFIA2_MIP].mesh_index + 10];
	cutseq_meshswapbits[1] |= 0x20u;
	meshes[objects[TWOGUN].mesh_index + 17] = meshes[objects[MAFIA2_MIP].mesh_index + 16];
	cutseq_meshbits[2] &= 0xFFFFFFFB;
	cutseq_meshswapbits[1] |= 0x100;
	lara_item->mesh_bits = 0;
}

void joby10_end()//303AC(<), 3072C(<) (F)
{
	cutseq_restore_item(CRANE_GUY_MIP);
	DelsHandyTeleportLara(58267, -3072, 48676, -16578);
}

void joby10_control()//30338(<), 306B8(<) (F)
{
	struct ITEM_INFO* item;

	if (GLOBAL_cutseq_frame == 3235)
	{
		item = find_a_fucking_item(HYDRA_MIP);
		item->status = ITEM_INACTIVE;
	}

	handle_lara_chatting(lara_chat_ranges_joby10);
	handle_actor_chatting(21, 2, 1, CRANE_GUY_MIP, admiral_chat_ranges_joby10);
	actor_chat_cnt = (actor_chat_cnt - 1) & 1;
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

void joby9_control()//302A0(<), 30620(<) (F)
{
	handle_lara_chatting(lara_chat_ranges_joby9);
	handle_actor_chatting(21, 2, 1, CRANE_GUY_MIP, admiral_chat_ranges_joby9);
	actor_chat_cnt = (actor_chat_cnt - 1) & 1;
}

void joby9_init()//30280(<), 30600(<) (F)
{
	cutseq_kill_item(CRANE_GUY_MIP);
	return;
}

void do_catapult_meshswap()//3024C(<), 305CC(<) (F)
{
	short* temp = lara.mesh_ptrs[LM_LHAND];
	lara.mesh_ptrs[LM_LHAND] = meshes[objects[CROW_MIP].mesh_index + 2 * LM_LHAND];
	meshes[objects[CROW_MIP].mesh_index + 2 * LM_LHAND] = temp;
}

void andy3_end()//30208(<), 30588(<) (F)
{
	FlipMap(2);
	do_catapult_meshswap();
	lara.puzzleitems[1] = 0;
	DelsHandyTeleportLara(55902, 8448, 53349, -32768);
}

void andy3_control()//301DC, 3055C (F)
{
	if (GLOBAL_cutseq_frame == 240)
		do_catapult_meshswap();
}

void andy3_init()//3018C(<), 3050C(<) (F)
{
	cutseq_kill_item(SWAT_PLUS_MIP);
	cutseq_kill_item(BLUE_GUARD_MIP);
	cutseq_kill_item(TWOGUN_MIP);
	cutseq_kill_item(DOG_MIP);
	cutseq_kill_item(LARSON_MIP);
	cutseq_kill_item(PIERRE_MIP);
	cutseq_kill_item(MAFIA_MIP);
}

void joby5_end()//30144(<), 304C4(<) (F)
{
	cutseq_restore_item(ANIMATING3);
	cutseq_restore_item(ANIMATING4);
	DelsHandyTeleportLara(SECTOR_TO_WORLD(60), -SECTOR_TO_WORLD(1.25), SECTOR_TO_WORLD(54), ANGLE(-180));
	lara_item->mesh_bits = 0xFFFFFFFF;
}

void joby5_control()//30034(<), 303B4() (F)
{
	int f = GLOBAL_cutseq_frame;

	if (f == 144)
	{
		lara_item->mesh_bits = 0;
	}
	else if (f == 436)
	{
		cutseq_meshbits[2] |= 0x80000000;
	}
	else if (f == 1796)
	{
		cutseq_meshbits[4] &= 0x7FFFFFFF;
	}
	else if (f == 2175)
	{
		cutseq_meshbits[1] &= 0x7FFFFFFFu;
	}
	else if (f == 151 || f == 2330)
	{
		cutseq_meshbits[4] |= 0x80000000;
	}

	handle_actor_chatting(21, 2, 3, CRANE_GUY_MIP, admiral_chat_ranges_joby5);
	handle_actor_chatting(23, 3, 4, LION_MIP, sergie_chat_ranges_joby5);
	actor_chat_cnt = (actor_chat_cnt - 1) & 1;
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
	UNIMPLEMENTED();
}

void andrea2_init()//2FCC0(<), 30040(<) (F)
{
	cutseq_meshbits[1] &= 0x7FFFFFFF;
}

void andrea1_end()//2FC94(<), 30014(<) (F)
{
	lara_item->mesh_bits = 0xFFFFFFFF;
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
	handle_actor_chatting(21, 8, 1, LARSON, larson_chat_ranges1);
	handle_actor_chatting(23, 8, 2, ANIMATING2_MIP, pierre_chat_ranges1);
	actor_chat_cnt = (actor_chat_cnt - 1) & 1;
}

void andrea1_init()//2FB50(<), 2FED0(<) (F)
{
	return;
}

void joby4_end()//2FB04(<), 2FE84(<) (F)
{
	lara_item->mesh_bits = 0xFFFFFFFF;
	cutseq_restore_item(DOOR_TYPE1);
	cutseq_restore_item(DOOR_TYPE5);
	DelsHandyTeleportLara(57950, 8960, 53760, ANGLE(90));
}

void joby4_control()//2FA0C, 2FD8C (F)
{
	int f = GLOBAL_cutseq_frame;
	if (GLOBAL_cutseq_frame <= 130)
	{
#if PC_VERSION
		//PrintString(middle_width, window_height_minus_1 - 3 * font_height, 5, &gfStringWad[gfStringOffset[STR_SEVERAL_HOURS_LATER]], 0x8000);
#else
		PrintString(256, 200, 0, &gfStringWad[gfStringOffset[STR_SEVERAL_HOURS_LATER]], 0x8000); // todo maybe wrong on pc , @Gh0stBlade check third arg!
#endif
	}
	if (f == 575)
	{
		cutseq_meshbits[5] &= 0x7FFFFFFFu;
	}
	else
	{
		if (f == 769 || f == 1966)
			lara_item->mesh_bits = 0;
		if (f == 1593)
			lara_item->mesh_bits = 0xFFFFFFFF;
	}
	handle_lara_chatting(lara_chat_ranges_joby4);
	handle_actor_chatting(21, 2, 3, CRANE_GUY_MIP, admiral_chat_ranges_joby4);
	actor_chat_cnt = (actor_chat_cnt - 1) & 1;
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
	meshes[objects[SAILOR_MIP].mesh_index + 17] = meshes[objects[MESHSWAP3].mesh_index + 16];
	cutseq_meshswapbits[1] |= 0x100;
}

void andy2_end()//2F668(<), 2F9E8(<) (F)
{
	DelsHandyTeleportLara(32289, 6271, 48635, 5661);
}

void andy2_control()//2F5D0(<), 2F914(<) (F)
{
	struct PHD_VECTOR pos;

	pos.x = 0;
	pos.y = 48;
	pos.z = 240;

	GetActorJointAbsPosition(1, 8, &pos);
	TriggerDynamic(pos.x, pos.y, pos.z, 
	               12 - (GetRandomControl() & 1), 
	               (GetRandomControl() & 0x3F) + 192, 
	               (GetRandomControl() & 0x1F) + 96, 0);
	DelTorchFlames(&pos);

	handle_lara_chatting(lara_chat_ranges_andy2);
	handle_actor_chatting(21, 2, 1, SAILOR_MIP, priest_chat_ranges_andy2);
	actor_chat_cnt = (actor_chat_cnt - 1) & 1;
}

void andy2_init()//2F5B0(<), 2F8F4(<) (F)
{
	setup_preist_meshswap();
}

void do_hammer_meshswap()//2F57C(<), 2F8C0(<) (F)
{
	short* temp = lara.mesh_ptrs[LM_RHAND];
	lara.mesh_ptrs[LM_RHAND] = meshes[objects[MESHSWAP3].mesh_index + 2 * LM_RHAND];
	meshes[objects[MESHSWAP3].mesh_index + 2 * LM_RHAND] = temp;
}

void hamgate_end()//2F534(<), 2F878(<) (F)
{
	struct ITEM_INFO* item = find_a_fucking_item(DOOR_TYPE1);
	item->status = ITEM_ACTIVE;
	DelsHandyTeleportLara(31232, -3328, 48344, 0);
}

void hamgate_control()//2F4D0(<), 2F814(<) (F)
{
	int f = GLOBAL_cutseq_frame;

	if (f == 14 || f == 269)
		do_hammer_meshswap();

	if (f == 442)
	{
		cutseq_meshbits[3] &= 0x7FFFFFFFu;
		cutseq_meshbits[2] |= 2;
	}
}

void hamgate_init()//2F434(<), 2F778(<) (F)
{
	struct ITEM_INFO* item = find_a_fucking_item(DOOR_TYPE1);
	AddActiveItem(item - items);
	item->flags |= IFLAG_ACTIVATION_MASK;
	item->mesh_bits = 3;
	item->status = ITEM_INVISIBLE;
	cutseq_meshbits[2] &= 0xFFFFFFFD;
	cutrot = 0;
}

void andy1_end()//2F408(<), 2F74C(<) (F)
{
	DelsHandyTeleportLara(63508, 9710, 65464, 949);
}

void andy1_control()//2F39C(<), 2F6A8(<) (F)
{
	if (GLOBAL_cutseq_frame == 3750)
	{
		cutseq_meshbits[1] &= 0x7FFFFFFFu;
		cutseq_restore_item(418);
		FlashFadeR = 255;
		FlashFadeG = 255;
		FlashFadeB = 255;
		FlashFader = 32;
	}
	handle_lara_chatting(lara_chat_ranges_andy1);
	handle_actor_chatting(23, 21, 1, SNIPER_MIP, hanged_man_chat_ranges_andy1); // todo find the name
	actor_chat_cnt = (actor_chat_cnt - 1) & 1;
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

void joby3_control()//2F304(<), 2F610(<) (F)
{
	if (GLOBAL_cutseq_frame == 583)
	{
		lara_item->mesh_bits = 0;
	}
	else if (GLOBAL_cutseq_frame == 765)
	{
		lara_item->mesh_bits = 0xFFFFFFFF;
	}
	else if (GLOBAL_cutseq_frame == 1299)
	{
		FlipMap(3);
	}

	handle_lara_chatting(lara_chat_ranges_joby3);
}

void joby3_init()//2F2FC(<), 2F608(<) (F)
{
	return;
}

void joby2_end()//2F2B8(<), 2F5C4(<) (F)
{
	lara_item->mesh_bits = 0xFFFFFFFF;
	DelsHandyTeleportLara(22905, -4608, 45415, -16730);
	cutseq_kill_item(ANIMATING6);
}

void joby2_control()//2F114(<), 2F420(<) (F)
{
	switch (GLOBAL_cutseq_frame)
	{
	case 176:
		lara_item->mesh_bits = 0;
		cutseq_meshbits[3] |= 0x80000000;
		cutseq_meshbits[4] |= 0x80000000;
		break;
	case 1622:
		lara_item->mesh_bits = 0xFFFFFFFF;
		cutseq_meshbits[1] &= 0x7FFFFFFFu;
		cutseq_meshbits[2] &= 0x7FFFFFFFu;
		cutseq_meshbits[3] &= 0x7FFFFFFFu;
		cutseq_meshbits[4] &= 0x7FFFFFFFu;
		cutseq_meshbits[5] &= 0x7FFFFFFFu;
		cutseq_meshbits[6] &= 0x7FFFFFFFu;
		disable_horizon = 1;
		break;
	case 1822:
		lara_item->mesh_bits = 0;
		disable_horizon = 0;
		cutseq_meshbits[1] |= 0x80000000;
		cutseq_meshbits[2] |= 0x80000000;
		cutseq_meshbits[3] |= 0x80000000;
		cutseq_meshbits[4] |= 0x80000000;
		break;
	case 254:
		disable_horizon = 0;
		break;
	case 1485:
		cutseq_meshbits[1] |= 0x80000000;
		cutseq_meshbits[2] |= 0x80000000;
		cutseq_meshbits[6] |= 0x80000000;
		break;
	}

	handle_actor_chatting(21, 2, 3, ANIMATING6_MIP, admiral_chat_ranges_joby2);
	handle_actor_chatting(23, 3, 4, ANIMATING9_MIP, sergie_chat_ranges_joby2);
	actor_chat_cnt = (actor_chat_cnt - 1) & 1;
}

void joby2_init()//2F0C0(<), 2F3CC(<) (F)
{
	disable_horizon = 1;
	cutseq_meshbits[1] &= 0x7FFFFFFFu;
	cutseq_meshbits[2] &= 0x7FFFFFFFu;
	cutseq_meshbits[3] &= 0x7FFFFFFFu;
	cutseq_meshbits[4] &= 0x7FFFFFFFu;
	cutseq_meshbits[6] &= 0x7FFFFFFFu;
}

void TriggerDelSmoke(long x, long y, long z, int sizeme)//2EED8(<), 2F1E4(<) (F)
{
	struct SPARKS* sptr;
	long size, dx, dz;

	dx = lara_item->pos.x_pos - x;
	dz = lara_item->pos.z_pos - z;
	if (dx >= SECTOR(-16) && dx <= SECTOR(16) && 
		dz >= SECTOR(-16) && dz <= SECTOR(16))
	{
		sptr = &spark[GetFreeSpark()];
		sptr->On = 1;
		sptr->sR = -128;
		sptr->sG = -128;
		sptr->sB = -128;
		sptr->dR = 64;
		sptr->dG = 64;
		sptr->dB = 64;
		sptr->ColFadeSpeed = 2;
		sptr->FadeToBlack = 8;
		sptr->TransType = 2;
		sptr->Life = sptr->sLife = (GetRandomControl() & 3) + 11;
		sptr->x = (GetRandomControl() & 0x1FF) + x - 256;
		sptr->y = (GetRandomControl() & 0x1FF) + y - 256;
		sptr->z = (GetRandomControl() & 0x1FF) + z - 256;
		sptr->Xvel = ((GetRandomControl() & 0xFFF) - 2048) >> 2;
		sptr->Yvel = (GetRandomControl() & 0xFF) - 128;
		sptr->Friction = 2;
		sptr->Flags = 538;
		sptr->Zvel = ((GetRandomControl() & 0xFFF) - 2048) >> 2;
		sptr->RotAng = GetRandomControl() & 0xFFF;
		sptr->Scalar = 2;
		sptr->RotAdd = (GetRandomControl() & 0xF) + 16;
		sptr->Gravity = -3 - (GetRandomControl() & 3);
		sptr->MaxYvel = -4 - (GetRandomControl() & 3);
		size = sizeme + (GetRandomControl() & 0x1F);
		sptr->dSize = size;
		sptr->sSize = size >> 2;
		sptr->Size = size>> 2;
	}
}

void TriggerUnderwaterBlood(int x, int y, int z, int sizeme)// (F)
{
	int i;

	for(i = 0; i < 32; i++)
	{
		if (!(ripples[i].flags & 1))
		{
			ripples[i].flags = 0x31;
			ripples[i].init = 1;
			ripples[i].life = (GetRandomControl() & 7) - 16;
			ripples[i].size = sizeme;
			ripples[i].x = (GetRandomControl() & 0x3F) + x - 32;
			ripples[i].y = y;
			ripples[i].z = (GetRandomControl() & 0x3F) + z - 32;
			return;
		}
	}
}

void TriggerActorBlood(int actornum, unsigned long nodenum, struct PHD_VECTOR* pos, int direction, int speed)//2EE84(<), 2F190(<) (F)
{
	GetActorJointAbsPosition(actornum, nodenum, pos);
	TriggerBlood(pos->x, pos->y, pos->z, direction >> 4, speed);
}

void GetActorJointAbsPosition(int actornum, unsigned long nodenum, struct PHD_VECTOR* vec)
{
	UNIMPLEMENTED();
}

void GrabActorMatrix(int actornum, int nodenum, struct MATRIX3D* matrix)
{
	UNIMPLEMENTED();
}

void deal_with_actor_shooting(unsigned short* shootdata, int actornum, int nodenum, struct PHD_VECTOR* pos)// (F)
{
	int i;
	unsigned short dat;
	struct MATRIX3D arse;

	for(i = 0; shootdata[i] != -1; i++)
	{
		dat = shootdata[i];

		if (GLOBAL_cutseq_frame == dat || GLOBAL_cutseq_frame == dat + 1)
		{
			GrabActorMatrix(actornum, nodenum, &arse);
			trig_actor_gunflash(&arse, pos);
			GetActorJointAbsPosition(actornum, nodenum, pos);
			TriggerDynamic(pos->x, pos->y, pos->z, 10,
			               (GetRandomControl() & 0x3F) + 192,
			               (GetRandomControl() & 0x1F) + 128,
			               (GetRandomControl() & 0x3F));
		}
	}
}

void stealth3_end()//2E99C, 2ECA8 (F)
{
	int i;
	struct ITEM_INFO* item = &items[0];

	for (i = 0; i < level_items; i++, item++)
	{
		if (cutseq_num == CUT_STEALTH3_3)
			continue;

		if (item->object_number == CHEF ||
			item->object_number == SAS ||
			item->object_number == BLUE_GUARD ||
			item->object_number == SWAT_PLUS ||
			item->object_number == SWAT ||
			item->object_number == TWOGUN)
		{
			if (abs(item->pos.x_pos - lara_item->pos.x_pos) < SECTOR(1) &&
				abs(item->pos.z_pos - lara_item->pos.z_pos) < SECTOR(1) &&
				abs(item->pos.y_pos - lara_item->pos.y_pos) < CLICK)
			{
				item->hit_points = 0;
				item->current_anim_state = 6;

				if (item->object_number == TWOGUN)
				{
					item->anim_number = objects[TWOGUN].anim_index + 3;
				}
				else if (item->object_number == CHEF)
				{
					item->anim_number = objects[CHEF].anim_index + 11;
				}
				else if (objects[SWAT].loaded)
				{
					item->anim_number = objects[SWAT].anim_index + 11;
				}
				else
				{
					item->anim_number = objects[BLUE_GUARD].anim_index + 11;
				}
					
				item->frame_number = anims[item->anim_number].frame_end;
				AddActiveItem(i);
			}
		}
	}

	if (cutseq_num == CUT_STEALTH3_2)
		SwapCrowbar(NULL);
}

void stealth3_start()//2E824, 2EB30 (F)
{
	int i;
	struct ITEM_INFO* item = &items[0];

	for (i = 0; i < level_items; i++, item++)
	{
		if (item->object_number == CHEF ||
			item->object_number == SAS ||
			item->object_number == BLUE_GUARD ||
			item->object_number == SWAT_PLUS ||
			item->object_number == SWAT ||
			item->object_number == TWOGUN)
		{
			if (abs(item->pos.x_pos - lara_item->pos.x_pos) < SECTOR(1) &&
				abs(item->pos.z_pos - lara_item->pos.z_pos) < SECTOR(1) &&
				abs(item->pos.y_pos - lara_item->pos.y_pos) < CLICK)
			{
				GLOBAL_cutme->actor_data[1].objslot = item->object_number;
				item->status = ITEM_INVISIBLE;
				RemoveActiveItem(i);
				DisableBaddieAI(i);
				item->flags |= IFLAG_INVISIBLE;
			}
		}
	}

	if (cutseq_num == CUT_STEALTH3_2)
		SwapCrowbar(NULL);
}

void special4_end()//2E7F4(<), 2EB00(<) (F)
{
	ResetCutanimate(STROBE_LIGHT);

	if (!bDoCredits)
	{
		trigger_title_spotcam(1);
		lara_item->mesh_bits = 0;
	}

	Chris_Menu = 0;
	title_controls_locked_out = 0;
}

void special4_control()//2E7C4(<), 2EAD0(<) (F)
{
	struct PHD_VECTOR pos;
	int r, g, b;
	
	pos.x = 85834;
	pos.z = 72300;
	pos.y = -3138;

	TriggerFireFlame(85834, -3010, 72300, -1, 1);
	TriggerFireFlame(85834, -3010, 72044, -1, 1);
	TriggerFireFlame(85834, -3010, 72556, -1, 1);
	TriggerFireFlame(85578, -3010, 72300, -1, 1);
	TriggerFireFlame(86090, -3010, 72300, -1, 1);

	if (GLOBAL_cutseq_frame >= 460)
		FlamingHell(&pos);

	if (GLOBAL_cutseq_frame < 470)
	{
		b = GetRandomControl() & 0x3F;
		g = (GetRandomControl() & 0xF) + 31;
		r = (GetRandomControl() & 0x3F) + 31;
	}
	else
	{
		b = GetRandomControl() & 0x3F;
		g = (GetRandomControl() & 0x7F) + 127;
		r = (GetRandomControl() & 0x7F) + 127;
	}

	TriggerDynamic(pos.x, pos.y, pos.z, 10, r, g, b);

	if (GLOBAL_cutseq_frame == 390)
		Cutanimate(STROBE_LIGHT);
}

void special4_init()//2E794(<), 2EAA0(<)
{
#if PSXENGINE
	cutrot = 0;
	UNIMPLEMENTED();
#else
	lara_item->mesh_bits = 0xFFFFFFFF;
	Chris_Menu = 0;
	cutrot = 1;
	special_num = 4;
#endif
}

void special3_end()//2E764(<), 2EA70(<) (F)
{
	if (!bDoCredits)
	{
		trigger_title_spotcam(4);
		lara_item->mesh_bits = 0;
	}

	Chris_Menu = 0;
	title_controls_locked_out = 0;
}

void special3_control()//2E734(<), 2EA40(<)
{
	UNIMPLEMENTED();
}

void special3_init()//2E704(<), 2EA10(<) (F)
{
	cutrot = 0;
	lara_item->mesh_bits = 0xFFFFFFFF;
	Chris_Menu = 0;
	special_num = 3;
}

void special2_end()//2E6D4(<), 2E9E0(<) (F)
{
	if (!bDoCredits)
	{
		trigger_title_spotcam(3);
		lara_item->mesh_bits = 0;
	}

	Chris_Menu = 0;
	title_controls_locked_out = 0;
}

void special2_control()//2E6A4(<), 2E9B0(<) (F)
{
	struct PHD_VECTOR pos;
	struct ITEM_INFO* item;

	pos.x = 12;
	pos.y = 200;
	pos.z = 92;

	deal_with_actor_shooting(special2_pistols_info, 1, 13, &pos);

	switch (GLOBAL_cutseq_frame)
	{
	case 0xC5:
		item = find_a_fucking_item(ANIMATING1_MIP);
		ExplodeItemNode(item, 0, 0, 64);
		break;
	case 0xC8:
		item = find_a_fucking_item(ANIMATING2_MIP);
		ExplodeItemNode(item, 0, 0, 64);
		break;
	case 0xC9:
		triggerwindowsmash(50);
		break;
	case 0xCF:
		item = find_a_fucking_item(ANIMATING3_MIP);
		ExplodeItemNode(item, 0, 0, 64);
		break;
	case 0xD1:
		triggerwindowsmash(52);
		break;
	case 0xDD:
		item = find_a_fucking_item(ANIMATING4_MIP);
		ExplodeItemNode(item, 0, 0, 64);
		break;
	case 0xE0:
		triggerwindowsmash(54);
		break;
	case 0xE5:
		Cutanimate(446);
		break;
	case 0xF5:
		triggerwindowsmash(56);
		break;
	case 0x105:
		item = find_a_fucking_item(ANIMATING5_MIP);
		ExplodeItemNode(item, 0, 0, 64);
		break;
	case 0x10D:
		triggerwindowsmash(58);
		break;
	case 0x118:
		item = find_a_fucking_item(ANIMATING6_MIP);
		ExplodeItemNode(item, 0, 0, 64);
		break;
	case 0x11A:
		item = find_a_fucking_item(ANIMATING7_MIP);
		ExplodeItemNode(item, 0, 0, 64);
		break;
	case 0x11C:
		Cutanimate(ANIMATING5);
		break;
	case 0x123:
		triggerwindowsmash(60);
		break;
	}
}

void special2_init()//2E674(<), 2E980(<) (F)
{
	cutrot = 0;
	lara_item->mesh_bits = 0xFFFFFFFF;
	Chris_Menu = 0;
	ResetCutItem(ANIMATING1_MIP);
	ResetCutItem(ANIMATING2_MIP);
	ResetCutItem(ANIMATING3_MIP);
	ResetCutItem(ANIMATING4_MIP);
	ResetCutItem(ANIMATING5_MIP);
	ResetCutItem(ANIMATING6_MIP);
	ResetCutItem(ANIMATING7_MIP);
	resetwindowsmash(50);
	resetwindowsmash(52);
	resetwindowsmash(54);
	resetwindowsmash(56);
	resetwindowsmash(58);
	resetwindowsmash(60);
	ResetCutanimate(ANIMATING16);
	ResetCutanimate(ANIMATING5);
	special_num = 2;
}

void special1_end()//2E644(<), 2E950(<) (F) (*)
{
#if PSX_VERSION
	((VOIDFUNCVOID*)RelocPtr[13][4])();
#else
	UNIMPLEMENTED();
#endif
}

void special1_control()//2E614(<), 2E920(<) (F) (*)
{
#if PSX_VERSION
	((VOIDFUNCVOID*)RelocPtr[13][3])();
#else
	UNIMPLEMENTED();
#endif
}

void special1_init()//2E5E4(<), 2E8F0(<) (F)
{
	cutrot = 0;
	lara_item->mesh_bits = 0xFFFFFFFF;
	Chris_Menu = 0;
}

void richcut3_control()//2E594(<), 2E8A0(<) (F)
{
	if (GLOBAL_cutseq_frame == 320)
	{
		cutseq_meshbits[1] |= 0x80000000;
		cutseq_removelara_hk();
		lara.back_gun = WEAPON_NONE;
		lara.hk_type_carried = WTYPE_MISSING;
		lara.last_gun_type = WEAPON_NONE;
	}
}

void richcut3_end()//2E54C(<), 2E858(<) (F)
{
	struct ITEM_INFO* item = find_a_fucking_item(HK_ITEM);

	if (item)
	{
		item->status = ITEM_ACTIVE;
		item->flags |= 0x20;
	}
}

void richcut3_init()//2E514(<), 2E820(<) (F)
{
	cutseq_givelara_hk();
	cutrot = 1;
	cutseq_meshbits[1] &= 0x7FFFFFFFu;
}

void richcut2_control()//2E4EC, 2E77C (F)
{
	if (GLOBAL_cutseq_frame == 300)
		cutseq_meshbits[5] &= 0x7FFFFFFFu;

	handle_actor_chatting(23, 11, 1, ANIMATING6, voncroy_chat_ranges_richcut2); // todo find the names
	handle_actor_chatting(21, 18, 3, ANIMATING4, associate_chat_ranges_richcut2);
	handle_actor_chatting(438, 14, 2, ANIMATING1, guard_chat_ranges_richcut2);

	actor_chat_cnt = (actor_chat_cnt - 1) & 1;
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

void richcut1_control()//2E3D8(<), 2E668(<) (F)
{
	struct ITEM_INFO* item;
	int f = GLOBAL_cutseq_frame;

	if (f == 101 || f == 493 || f == 673)
		lara_item->mesh_bits = 0;

	if (f == 208 || f == 580 || f == 810)
		lara_item->mesh_bits = 0xFFFFFFFF;

	if (f == 840)
	{
		item = find_a_fucking_item(CLOSED_DOOR2);
		AddActiveItem(item - items);
		item->status = ITEM_INVISIBLE;
		item->flags |= IFLAG_ACTIVATION_MASK;
	}
}

void richcut1_end()//2E3A0(<), 2E630(<) (F)
{
	DelsHandyTeleportLara(34504, SECTOR(-1), 54799, -29215);
	cutseq_removelara_hk();
	cutrot = 1;
}

void richcut1_init()//2E26C(<), 2E4FC(<) (F)
{
	short item_num, nex;
	struct ITEM_INFO* item;

	item_num = room[lara_item->room_number].item_number;

	if (item_num != -1)
	{
		do
		{
			item = &items[item_num];

			nex = item->next_item;

			if (item->object_number == SCIENTIST)
			{
				item->status = ITEM_INVISIBLE;
				RemoveActiveItem(item - items);
				DisableBaddieAI(item - items);
				item->flags |= IFLAG_INVISIBLE;
			}

			item_num = nex;
		} while (nex != -1);
	}

	cutseq_givelara_hk();
	cutrot = 1;
}

void cranecut_control()//2E0B8(<), 2E348(<) (F)
{
	struct PHD_VECTOR pos;
	int n, f;

	f = GLOBAL_cutseq_frame;

	switch (f)
	{
	case 74:
		lara_item->mesh_bits = 0;
		break;
	case 124:
		lara_item->mesh_bits = 0xFFFFFFFF;
		break;
	case 801:
		cutseq_meshbits[1] &= 0x7FFFFFFFu;
		break;
	case 850:
		cutseq_removelara_pistols();
		break;
	case 1301:
		cutseq_meshbits[5] |= 0x80000000;
		FlipMap(1);
		break;
	}
	deal_with_pistols(crane_pistols_info);
	pos.x = 12;
	pos.y = 200;
	pos.z = 60;
	deal_with_actor_shooting(craneguard_pistols_info, 1, 13, &pos);
	if (f >= 456 && f <= 462)
	{
		pos.x = 0;
		pos.y = 0;
		pos.z = 0;
		TriggerActorBlood(1, 2, &pos, 0, 1);
		pos.x = 0;
		pos.y = 0;
		pos.z = 0;
		TriggerActorBlood(1, 5, &pos, 0, 1);
	}
	if (f >= 1455 && f <= 1495)
	{
		pos.x = 1400;
		pos.y = 900;
		pos.z = 512;
		GetActorJointAbsPosition(5, 0, &pos);
		for (n = 0; n < 2800; n += 175)
		{
			TriggerDelSmoke(pos.x, pos.y, n + pos.z, f - 1367);
		}
	}
}

void cranecut_end()//2E020(<), 2E2B0(<) (F)
{
	struct ITEM_INFO* item = cutseq_restore_item(ANIMATING5);
	RemoveActiveItem(item - items);
	item->flags &= ~IFLAG_ACTIVATION_MASK;
	cutseq_restore_item(ANIMATING16);
	cutseq_restore_item(WRECKING_BALL);
	DelsHandyTeleportLara(58543, SECTOR(-4), 34972, ANGLE(-90));
}

void cranecut_init()//2DFA0(<), 2E230(<) (F)
{
	cutseq_kill_item(ANIMATING5);
	cutseq_kill_item(ANIMATING16);
	cutseq_kill_item(WRECKING_BALL);
	cutseq_kill_item(ANIMATING4);
	cutseq_givelara_pistols();
	meshes[objects[ANIMATING4].mesh_index + 26] = meshes[objects[BLUE_GUARD].mesh_index + 26];
	cutseq_meshbits[5] &= 0x7FFFFFFFu;
}

struct ITEM_INFO* find_a_fucking_item(int object_number)//2DF50(<), 2E1E0(<) (F)
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

void handle_actor_chatting(int speechslot, int node, int slot, int objslot, short* ranges)//2DDF0(<), 2E080(<) (F)
{
	int r1, r2, f, rnd;

	f = GLOBAL_cutseq_frame;
	rnd = GetRandomControl() & 1;

	while(1)
	{
		r1 = ranges[0];
		r2 = ranges[1];

		if (r1 == -1)
		{
			cutseq_meshswapbits[slot] &= ~(1 << node);
			return;
		}

		if (f >= r1 && f <= r2)
			break;

		ranges += 2;
	}

	if (!actor_chat_cnt)
	{
		cutseq_meshswapbits[slot] |= 1 << node;
		meshes[2 * (node + objects[objslot].mesh_index) + 1] = meshes[2 * node + objects[speechslot + rnd].mesh_index];
		
		if ((GetRandomControl() & 7) >= 6)
		{
			cutseq_meshswapbits[slot] &= ~(1 << node);
		}
	}
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
			lara.mesh_ptrs[LM_HEAD] = meshes[objects[LARA_SKIN].mesh_index + 2 * LM_HEAD];
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
		lara.mesh_ptrs[LM_HEAD] = meshes[rndme + 2 * LM_HEAD];
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

	lara.gun_status = LG_NO_ARMS;
	camera.fixed_camera = 1;
}

void init_resident_cutseq(int num)//2DB8C(<), 2DE1C(<) (F)
{
	char* packed = cutseq_resident_addresses[num].packed_data;

	GLOBAL_cutme = (struct NEW_CUTSCENE*)packed;

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
	UNIMPLEMENTED();
}

int Load_and_Init_Cutseq(int num)
{
#if PC_VERSION
	SetCutPlayed(num);
	struct NEW_CUTSCENE* cut = FetchCutData(num);
	GLOBAL_cutme = cut;
	if (cutseq_num <= CUT_STEALTH3_4)
	{
		GLOBAL_cutme->orgx = (lara_item->pos.x_pos & 0xFFFFFC00) + 512;
		GLOBAL_cutme->orgy = lara_item->pos.y_pos;
		GLOBAL_cutme->orgz = (lara_item->pos.z_pos & 0xFFFFFC00) + 512;
	}
	init_cutseq_actors((char*)cut, FALSE);
#else
	UNIMPLEMENTED();
#endif

	return 0;
}

struct ITEM_INFO* cutseq_restore_item(int num)//2D738(<), 2DA20(<) (F)
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

				items[i].status = ITEM_INVISIBLE;
				items[i].flags &= ~IFLAG_ACTIVATION_MASK;
				items[i].flags |= 0x20;
			}			
		}
	}
}

void deal_with_pistols(unsigned short* shootdata)// (F)
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
				cutseq_shoot_pistols(LJ_LHAND);
			if (dat & CPI_SHOOT_RIGHT)
				cutseq_shoot_pistols(LJ_RHAND);
		}
	}
	if (SmokeCountL || SmokeCountR)
	{
		lara.mesh_ptrs[LM_HEAD] = meshes[objects[LARA_SCREAM].mesh_index + 2 * LM_HEAD];
		if (SmokeCountL)
		{
			pos.x = 4;
			pos.y = 128;
			pos.z = 40;
			GetLaraJointPos(&pos, LJ_LHAND);
			TriggerGunSmoke(pos.x, pos.y, pos.z, 0, 0, 0, 0, SmokeWeapon, SmokeCountL);
		}
		if (SmokeCountR)
		{
			pos.x = -16;
			pos.y = 128;
			pos.z = 40;
			GetLaraJointPos(&pos, LJ_RHAND);
			TriggerGunSmoke(pos.x, pos.y, pos.z, 0, 0, 0, 0, SmokeWeapon, SmokeCountR);
		}
	}
	else
	{
		lara.mesh_ptrs[LM_HEAD] = meshes[objects[LARA].mesh_index + 2 * LM_HEAD];
	}

	if (lara.left_arm.flash_gun)
	{
		--lara.left_arm.flash_gun;
		trigger_weapon_dynamics(LJ_LHAND);
	}
	if (lara.right_arm.flash_gun)
	{
		--lara.right_arm.flash_gun;
		trigger_weapon_dynamics(LJ_RHAND);
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

void cutseq_shoot_pistols(int left_or_right)//2D360, 2D648 (F)
{
	if (left_or_right == LJ_LHAND)
	{
		lara.left_arm.flash_gun = 4;
		SmokeCountL = 16;
	}
	else
	{
		lara.right_arm.flash_gun = 4;
		SmokeCountR = 16;
	}
}

void cutseq_removelara_hk()//2D328(<), 2D610(<) (F)
{
	undraw_shotgun_meshes(WEAPON_HK);
	lara.gun_type = WEAPON_NONE;
	lara.request_gun_type = WEAPON_NONE;
	lara.gun_status = LG_NO_ARMS;
	lara.last_gun_type = WEAPON_HK;
}

void cutseq_givelara_hk()//2D308(<), 2D5F0(<) (F)
{
	draw_shotgun_meshes(WEAPON_HK);
}

void cutseq_removelara_pistols()//2D2D8(<), 2D5C0(<) (F)
{
	undraw_pistol_mesh_left(WEAPON_PISTOLS);
	undraw_pistol_mesh_right(WEAPON_PISTOLS);
	lara.holster = old_lara_holster;
}

void cutseq_givelara_pistols()//2D2A0(<), 2D588(<) (F)
{
	old_lara_holster = lara.holster;
	lara.holster = LARA_HOLSTERS;
	draw_pistol_meshes(WEAPON_PISTOLS);
}

void CalculateObjectLightingLaraCutSeq()
{
	UNIMPLEMENTED();
}

void finish_cutseq(int name)//2D180(<), 2D4A0(<) (F)
{
#if PC_VERSION
	GLOBAL_playing_cutseq = 0;
#else

	if (cutseq_resident_addresses[cutseq_num].packed_data == NULL)
	{
#if DEBUG_VERSION && PSX_VERSION
		ProfileDraw = 0;
		DrawSync(0);
		VSync(0);
#endif

		ReloadAnims(name, cutseq_malloc_used);
	}

#if DEBUG_VERSION && PSX_VERSION
	ProfileDraw = 1;
	DrawSync(0);
	VSync(0);
#endif

#endif

	InitialiseHair();
}

void* cutseq_malloc(int size)//2D134(<), 2D454(<) (F)
{
	char* ptr;

	size = (size + 3) & -4;

	if(cutseq_malloc_free >= size)
	{		
		ptr = cutseq_malloc_ptr;

		cutseq_malloc_free -= size;
		cutseq_malloc_ptr += size;
		cutseq_malloc_used += size;
		
		return ptr;
	}

	return NULL;
}

void init_cutseq_malloc()//2D110(<), 2D430(<) (F)
{
	cutseq_malloc_used = 0;
	cutseq_malloc_ptr = (char*)frames;
	cutseq_malloc_free = AnimFileLen;
	return;
}

void frigup_lara()//2D000(<), ? (F)
{
	struct object_info* object;
	long* bone;
	short* frame;

	lara_item->pos.x_pos = GLOBAL_cutme->orgx;
	lara_item->pos.y_pos = GLOBAL_cutme->orgy;
	lara_item->pos.z_pos = GLOBAL_cutme->orgz;

	if (GLOBAL_cutme->actor_data[0].objslot == -1)
	{
		return;
	}

	frame = &temp_rotation_buffer[0];
	object = &objects[lara_item->object_number];
	bone = &bones[object->bone_index];

	//updateAnimFrame(actor_pnodes[0], 0x10, frame);
	DEL_CalcLaraMatrices_Normal_ASM(frame, bone, 0);
	mPushUnitMatrix();
	DEL_CalcLaraMatrices_Normal_ASM(frame, bone, 1);
	mPopMatrix();

	//HairControl(0, 0, frame);

	if ((gfLevelFlags & GF_LVOP_YOUNG_LARA))
	{
		//HairControl(0, 1, frame);
	}

	//loc_2D0F0
	GLaraShadowframe = &frig_shadow_bbox[0];
}

void InitPackNodes(struct NODELOADHEADER* lnode, struct PACKNODE* pnode, char* packed, int numnodes)//2CED4(<), ?
{
	int offset;
	int xoff;
	int yoffset;
	int yoff;
	int zoffset;
	int zoff;
	int i;

	offset = ((numnodes << 3) - numnodes) << 1;
	if (numnodes <= 0)
	{
		return;
	}

	//loc_2CEF0
	for(i = numnodes; i >= numnodes; i--)
	{
		pnode->xkey = lnode->xkey;
		pnode->ykey = lnode->ykey;
		pnode->zkey = lnode->zkey;

		pnode->decode_x.packmethod = (lnode->packmethod >> 10) & 0xF;
		pnode->decode_y.packmethod = (lnode->packmethod >> 5) & 0xF;
		pnode->decode_z.packmethod = (lnode->packmethod) & 0xF;

		pnode->xlength = lnode->xlength;
		pnode->ylength = lnode->ylength;
		pnode->zlength = lnode->zlength;

		xoff = ((lnode->xlength * pnode->decode_x.packmethod) >> 3) + 4;
		yoff = (lnode->ylength * pnode->decode_y.packmethod);
		zoff = (lnode->zlength * pnode->decode_z.packmethod);

		lnode++;

		yoffset = offset + xoff;
		yoff >>= 3;
		yoff += 4;
		xoff += yoff;
		pnode->xpacked = packed + offset;
		pnode->ypacked = packed + yoffset;
		zoffset += yoff;
		pnode->zpacked = packed + zoffset;
		pnode++;
		zoff >>= 3;
		zoff += 4;
		xoff += zoff;
		offset += xoff;

	}

	return;
}


void do_new_cutscene_camera()
{
	UNIMPLEMENTED();
}

void handle_cutseq_triggering(int name)//2C3C4, 2C6EC
{
#if PC_VERSION
	if (cutseq_num == CUT_NULL)
		return;

	if (cutseq_trig == 0)
	{
		if (lara.gun_type == WEAPON_FLARE || lara.gun_status != LG_NO_ARMS && lara.gun_status != LG_HANDS_BUSY)
		{
			lara.gun_status = LG_UNDRAW_GUNS;
		}

		cutseq_trig = 1;
		memset(cutseq_meshswapbits, 0, sizeof(cutseq_meshswapbits));
		cutseq_busy_timeout = 50;
		memset(cutseq_meshbits, 0xFF, sizeof(cutseq_meshbits));

		if (gfCurrentLevel)
			SetFadeClip(28, 1);

		if (!ScreenFadedOut)
		{
			if (gfCurrentLevel)
				S_CDFade(0);

			SetScreenFadeOut(16, 0);
		}

		return;
	}

	if (cutseq_trig != 1)
	{
		if (cutseq_trig == 3)
		{
			SetScreenFadeOut(16, 1);

			if (gfCurrentLevel != LVL5_TITLE)
				S_CDFade(0);

			cutseq_trig = 4;
			return;
		}

		if (cutseq_trig != 4 || !ScreenFadedOut)
			return;

		if (gfCurrentLevel)
		{
			S_CDStop();
		}

		ScreenFadedOut = FALSE;
		numnailed = 0;

		void(*end)() = cutseq_control_routines[cutseq_num].end_func;

		if (end != NULL)
		{
			end();
		}

		if (cutseq_num >= CUT_STEALTH3_1 && cutseq_num <= CUT_STEALTH3_4)
		{
			DelsHandyTeleportLara(GLOBAL_cutme->orgx, GLOBAL_cutme->orgy, GLOBAL_cutme->orgz, cutrot << W2V_SHIFT);
		}

		cutseq_trig = 0;
		GLOBAL_playing_cutseq = 0;

		if (!bDoCredits)
		{
			if (dels_cutseq_player)
			{
				reset_flag = 1;
				dels_cutseq_player = 0;
			}
			else
			{
				if (cutseq_num != CUT_RICH_CUT_2 &&
					cutseq_num != CUT_JOBY_CUT_3 &&
					cutseq_num != CUT_JOBY6 &&
					cutseq_num != CUT_ANDREA2 &&
					cutseq_num != CUT_ANDY6 &&
					cutseq_num != CUT_ANDY11 &&
					cutseq_num != CUT_JOBY10)
				{
					finish_cutseq(name);

					cutseq_num = CUT_NULL;
					camera.type = GLOBAL_oldcamtype;

					if (gfCurrentLevel)
						SetFadeClip(0, 1);

					AlterFOV(ANGLE(80));

					if (gfCurrentLevel)
						S_CDPlay(CurrentAtmosphere, 1);

					IsAtmospherePlaying = 1;
					return;
				}

				gfLevelComplete = gfCurrentLevel + 1;
			}

			gfRequiredStartPos = 0;

			cutseq_num = 0;
			GLOBAL_playing_cutseq = 0;
			cutseq_trig = 0;

			AlterFOV(ANGLE(80));

			ScreenFade = 0;
			dScreenFade = 0;

			ScreenFadeSpeed = 8;
			ScreenFadeBack = 0;
			ScreenFadedOut = 0;
			ScreenFading = 0;

			return;
		}

		switch (cutseq_num)
		{
		case 28:
			cutseq_num = 29;
			break;
		case 29:
			cutseq_num = 30;
			break;
		case 30:
			cutseq_num = 28;
			break;
		}

		Load_and_Init_Cutseq(cutseq_num);
		cutseq_trig = 2;
		return;
	}

	if (!ScreenFadedOut)
		return;

	if (--cutseq_busy_timeout > 0)
	{
		if (lara.gun_status != LG_HANDS_BUSY
			&& (lara.gun_status != LG_NO_ARMS || lara.flare_control_left)
			&&  lara_item->current_anim_state != STATE_LARA_CRAWL_IDLE
			&&  lara_item->current_anim_state != STATE_LARA_CRAWL_FORWARD
			&&  lara_item->current_anim_state != STATE_LARA_CRAWL_TURN_LEFT
			&&  lara_item->current_anim_state != STATE_LARA_CRAWL_TURN_RIGHT
			&&  lara_item->current_anim_state != STATE_LARA_CRAWL_BACK)
		{
			return;
		}
	}
	else
	{
		cutseq_busy_timeout = 0;
	}

	lara.flare_control_left = FALSE;
	lara.flare_age = 0;

	if (!(gfLevelFlags & GF_LVOP_YOUNG_LARA))
	{
		lara.gun_type = WEAPON_NONE;
		lara.request_gun_type = WEAPON_NONE;

		lara.gun_status = LG_NO_ARMS;

		lara.last_gun_type = WEAPON_PISTOLS;

		if (!objects[PISTOLS_ITEM].loaded || lara.pistols_type_carried == WTYPE_MISSING)
			lara.last_gun_type = WEAPON_NONE;

		if (gfLevelFlags & GF_LVOP_TRAIN && objects[HK_ITEM].loaded && lara.hk_type_carried & WTYPE_PRESENT)
			lara.last_gun_type = WEAPON_HK;

		lara.mesh_ptrs[LM_LHAND] = meshes[objects[LARA].mesh_index + 2 * LM_LHAND];
		lara.mesh_ptrs[LM_RHAND] = meshes[objects[LARA].mesh_index + 2 * LM_RHAND];

		lara.left_arm.frame_number = 0;
		lara.right_arm.frame_number = 0;

		lara.target = 0;

		lara.right_arm.lock = 0;
		lara.left_arm.lock = 0;

		lara_item->goal_anim_state = STATE_LARA_STOP;
		lara_item->current_anim_state = STATE_LARA_STOP;
		lara_item->frame_number = anims[ANIMATION_LARA_STAY_SOLID].frame_base;
		lara_item->anim_number = ANIMATION_LARA_STAY_SOLID;

		lara_item->speed = 0;
		lara_item->fallspeed = 0;

		lara_item->gravity_status = FALSE;

		lara.back_gun = 0;

		if (lara.weapon_item != -1)
		{
			KillItem(lara.weapon_item);
			lara.weapon_item = -1;
		}
	}

	lara.water_status = 0;

	if (gfCurrentLevel)
		S_CDStop();

	numnailed = 0;
	GLOBAL_oldcamtype = camera.type;

	ScreenFading = 0;
	SetScreenFadeIn(16);
	Load_and_Init_Cutseq(cutseq_num);
	cutseq_trig = 2;

	cut_seethrough = 128;

	void(*init)() = cutseq_control_routines[cutseq_num].init_func;

	if (init != NULL)
	{
		init();
	}

	AlterFOV(11488);

	if (GLOBAL_cutme->audio_track != -1 && !bDoCredits)
		S_StartSyncedAudio(GLOBAL_cutme->audio_track);
#else
	int i;
	int s1 = name;//guessed, moved but not used

	if (cutseq_num == 0)
	{
		int a1 = 0;//Must confirm initial value.
		if (cutseq_trig == 0)
		{
			if (lara.gun_status == LG_NO_ARMS)
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
				if (lara.gun_status != LG_HANDS_BUSY)
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
#if DEBUG_VERSION && PSX_VERSION
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
						if (lara.gun_status != LG_HANDS_BUSY && lara.gun_status == LG_NO_ARMS && lara.flare_control_left != 0)
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

					if (objects[PISTOLS_ITEM].loaded && lara.pistols_type_carried != 0)
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
						if (objects[HK_ITEM].loaded)
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
#endif
	return;
}

void triggerwindowsmash(int item_num) // (F)
{
	struct ITEM_INFO* item = find_a_fucking_item(item_num);
	ExplodeItemNode(item, 0, 0, 64);
	item->mesh_bits = 2;
}

void resetwindowsmash(int item_num)// (F)
{
	find_a_fucking_item(item_num)->mesh_bits = 1;
}

void ResetCutItem(int item_num)// (F)
{
	find_a_fucking_item(item_num)->mesh_bits = -1;
}