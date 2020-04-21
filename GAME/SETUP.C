#include "SETUP.H"


#include "BOX.H"

#include "COLLIDE.H"
#include "CONTROL.H"
#include "CODEWAD.H"
#include "DELTAPAK.H"
#include "DEBRIS.H"
#include "DRAW.H"

#include "DOOR.H"
#include "EFFECTS.H"
#include "EFFECT2.H"
#include "FILE.H"
#include "FLMTORCH.H"
#include "GAMEFLOW.H"

#include "HAIR.H"
#include "HEALTH.H"
#include "ITEMS.H"
#include "LARA.H"
#include "LARAFIRE.H"
#include "LARAMISC.H"

#include "LOT.H"
#include "MALLOC.H"

#include "NEWINV2.H"
#include "OBJECTS.H"
#include "OBJLIGHT.H"
#include "PICKUP.H"

#include "SAVEGAME.H"
#include "SPECIFIC.H"
#include "SPOTCAM.H"
#include "SOUND.H"

#include "SWITCH.H"
#include "TOMB4FX.H"
#include "TYPES.H"

#include "STYPES.H"

#include <assert.h>
#if !SAT_VERSION
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#endif

#if PC_VERSION
#include "INIT.H"
#include "GAME.H"
#include "GLOBAL.H"
#else
#include "3D_OBJ.H"
#include "CD.H"
#include "DRAWPHAS.H"
#include "GPU.H"
#include "LOAD_LEV.H"
#include "MATHS.H"
#include "MISC.H"
#include "ROOMLOAD.H"
#include "SPUSOUND.H"
#include "TYPEDEFS.H"
#endif

#if defined(__linux__) || defined(__EMSCRIPTEN__) || defined(__ANDROID__)
        #define CODE_WAD "DATA/CODE.WAD"
#else
        #define CODE_WAD "DATA\\CODE.WAD"
#endif

#if PSX_VERSION
	#if !DISC_VERSION
		#include <LIBSN.H>
	#endif
#include <LIBSPU.H>
#include <LIBGTE.H>

#if PSX_VERSION && RELOC
void* setupFunc[] __attribute__((section(".header"))) =
{
	&InitialiseGameFlags,
	&InitialiseObjects,
	&GetCarriedItems,
	&GetAIPickups,
	&SetupGame,
	&LoadLevel
};
#endif

#if PSXPC_TEST
RECT16 dword_BD7F4[] = { { 576, 68, 64, 57 },{ 32768, 40960, 49152, 57344 } };
#else
RECT dword_BD7F4[] = { { 576, 68, 64, 57 },{ 32768, 40960, 49152, 57344 } };
#endif
#endif

#if PSXPC_TEST
#include <EMULATOR_PRIVATE.H>
#include <stdint.h>
#include "TEXT_S.H"
#elif PSX_VERSION || SAT_VERSION
typedef unsigned int uintptr_t;
#endif
#if PC_VERSION
struct object_info objects[NUMBER_OBJECTS];
struct static_info static_objects[NUMBER_STATIC_OBJECTS];
char SkinVertNums[480];
char ScratchVertNums[480];
#endif

#if (PSXPC_VERSION || PSXPC_TEST || SAT_VERSION) && !PC_VERSION
struct object_container objects_raw;
struct object_info* objects = &objects_raw.m_objects[0];
struct static_info* static_objects = &objects_raw.m_static_objects[0];
extern char* SkinVertNums = &objects_raw.m_SkinVertNums[0];
extern char* ScratchVertNums = &objects_raw.m_ScratchVertNums[0];
#endif

#if PSX_VERSION || PSXPC_VERSION || SAT_VERSION
int LoadSoundEffects(int numSoundEffects, long* pSoundWadLengths, char* pSoundData, int soundWadSize)//?, B3974(F)
{
#ifndef NO_SOUND

	int i;

	if (numSoundEffects > MAX_NUM_SOUND_EFFECTS || soundWadSize > 524288)
	{
		return 0;
	}

	if (LnSamplesLoaded != 0)
	{
		SPU_FreeSamples();
	}//loc_9C

#if PSX_VERSION
	LlVABAddr = SpuMalloc(soundWadSize);
	if (LlVABAddr == -1)
	{
		return 0;
	}

	SpuIsTransferCompleted(SPU_TRANSFER_WAIT);
	SpuSetTransferStartAddr(LlVABAddr);
	SpuWrite((unsigned char*)pSoundData, soundWadSize);
	SpuIsTransferCompleted(SPU_TRANSFER_WAIT);
#endif

	if (numSoundEffects > 0)
	{
		for (i = 0; i < numSoundEffects; i++)
		{
			LadwSampleAddr[i] = LlVABAddr + pSoundWadLengths[i];
		}
	}//loc_110

	LnSamplesLoaded = numSoundEffects;

	return 1;

#else
	return 0;
#endif
}
#endif

void InitialiseAnimatedTextures()//?(<), B4904(<)
{
	int i;
	unsigned short* animTexRange = &App.AnimTextureRanges[0];
#if 0
	//000B4B50 3C03000A lui     v1, $A
	//v0 = nAnimUVRanges;
	//a1 = AnimTextureRanges;
	if (nAnimUVRanges == 0)
	{
		return;
	}

	//a0 = 0;
	//t4 = RoomTextInfo;
	for (i = 0; i < nAnimUVRanges; i++)
	{
		//v1 = AnimTextureRanges[0];
		animTexRange++;
		//if(AnimTextureRanges[0] > -1)
		{
			//t1 = t4;
			//t3 = AnimatingTexturesV;
			//v0 = i << 1;
			//v0 += i;
			//t0 = v0 << 4;
			while (v1 >= 0)
			{
				//a3 = animTexRange++;
				//a2 = v1 - 1;
				//v0 = v1 << 1;
				//v0 += v1;
				//v0 <<= 1;
				//v0 += t0;
				//a0 = v0 + t3;
				//v1 = *animTexRange++;
				//v0 = v1 << 1;
				//v0 += v1;
				//v0 <<= 4;
				//v1 = t1 + v0;
				//while(a1 >= 0)
				{
					//a1 -= 1;
					//v0 = v1[1]//byte
					//v1 += 16;//sizeof what?
					//v0 = a0[0];
					//a0 += 2;
				}

				//v1 = a2;
				//a1 = a3;
			}
		}
	}

	return;
#endif
}

int GetRandom(struct WATERTAB* w, int n)///@check args
{
	int i;
	unsigned short random;

	do {
		random = GetRandomDraw() & 0xfc;

		for (i = 0; i<n; i++)
		{
			if (w[i].random == random)
				break;
		}

		if (i == n)
			return random;

	} while (1);

	return 0;		// to stop warning
}

void init_water_table()//(<), B4A40(<)
{
	long	lp;

	SeedRandomDraw(121197);

	for (lp = 0; lp<64; lp++)
	{
		int i, j, k;
		short sin = rcossin_tbl[(lp << 7)];

		// underwater

		WaterTable[0][lp].shimmer = (sin * 63) >> (12 + 3);
		WaterTable[0][lp].choppy = (sin * 16) >> 12;
		WaterTable[0][lp].random = GetRandom(&WaterTable[0][0], lp);
		WaterTable[0][lp].abs = 0;

		// mist

		WaterTable[1][lp].shimmer = (sin * 32) >> (12 + 3);
		WaterTable[1][lp].choppy = 0;
		WaterTable[1][lp].random = GetRandom(&WaterTable[1][0], lp);
		WaterTable[1][lp].abs = -3;

		WaterTable[2][lp].shimmer = (sin * 64) >> (12 + 3);
		WaterTable[2][lp].choppy = 0;
		WaterTable[2][lp].random = GetRandom(&WaterTable[2][0], lp);
		WaterTable[2][lp].abs = 0;

		WaterTable[3][lp].shimmer = (sin * 96) >> (12 + 3);
		WaterTable[3][lp].choppy = 0;
		WaterTable[3][lp].random = GetRandom(&WaterTable[3][0], lp);
		WaterTable[3][lp].abs = 4;

		WaterTable[4][lp].shimmer = (sin * 127) >> (12 + 3);
		WaterTable[4][lp].choppy = 0;
		WaterTable[4][lp].random = GetRandom(&WaterTable[4][0], lp);
		WaterTable[4][lp].abs = 8;

		// ripple

		for (i = 0, j = 5; i<4; i++, j += 4)
		{
			for (k = 0; k<4; k++)
			{
				unsigned char off[4] = { 4, 8, 12, 16 };
				short shim[4] = { 31, 63, 95, 127 };
				short chop[4] = { 16, 53, 90, 127 };

				WaterTable[j + k][lp].shimmer = -((sin*shim[k]) >> 15);
				WaterTable[j + k][lp].choppy = (sin*chop[i]) >> 12;
				WaterTable[j + k][lp].random = GetRandom(&WaterTable[j + k][0], lp);
				WaterTable[j + k][lp].abs = off[k];
			}
		}
	}

#if PC_VERSION
	UNIMPLEMENTED();
#endif
}

#if !PC_VERSION
void InitialiseSqrtTable()//?(<), B4D14(<)
{
	int i;

	for (i = 0; i < 1024; i++)
	{
		OurSqrt[i] = phd_sqrt_asm(i);
	}

	return;
}
#endif

void InitTarget()//(<), B4D64(<)
{
	int i;
	int v0;
	int v1;
	struct MESH_STRUCT* mesh;

	target_mesh_ptr = meshes[objects[TARGET_GRAPHICS].mesh_index];
	mesh = (struct MESH_STRUCT*)target_mesh_ptr;

	if (mesh->unk03 == 0)
	{
		return;
	}

	for (i = 0; i < mesh->unk03; i++, mesh++)
	{
		//a1 = mesh->unk03

		//v0 = mesh->unk00;
		//v1 = v0 << 2;//shift shrt.
		//v1 += v0;
		//v1 <<= 4;
		//v0 = v1 * 0x2AAAAAAB;
		//v1 >>= 0x1F;
		//v0 >>= 4;
		//v0 -= v1;
		//v0 += 0x100;
		//mesh->unk00 = v0;

		v1 = (((mesh->unk01 << 4) - mesh->unk01) << 2) >> 0x1F;
		v0 = (((((mesh->unk01 << 4) - mesh->unk01) << 2) * 0x92492493) + (((mesh->unk01 << 4) - mesh->unk01) << 2)) >> 7;
		v0 -= v1;
		v0 += 0x78;
		mesh->unk01 = v0;
	}

	return;
}

void InitBinoculars()//?(<), B4E28(<)
{
	sizeof(struct object_info);

#if 0
	000B5074 3C040020 lui     a0, $20
		000B5078 3C05000A lui     a1, $A


		binoculars_mesh_ptr = meshes[objects[BINOCULAR_GRAPHICS].mesh_index];//$a0

	if ()//TODO reconstruct struct.

		000B5098 90820008 lbu     v0, $8(a0)
		000B509C 00000000 nop
		000B50A0 10400021 beq     v0, 0, $B5128
		000B50A4 2484000C addiu   a0, $C
		000B50A8 3C075555 li      a3, $55555556
		000B50B0 3C069249 li      a2, $92492493
		000B50B8 00402821 addu    a1, v0, 0
		000B50BC 94830000 lhu     v1, $0(a0)
		000B50C0 00000000 nop
		000B50C4 00031C00 sll     v1, $10
		000B50C8 00031403 sra     v0, v1, $10
		000B50CC 00470018 mult    v0, a3
		000B50D0 00031FC3 sra     v1, $1F
		000B50D4 00001010 mfhi    v0
		000B50D8 00431023 subu    v0, v1
		000B50DC 24420100 addiu   v0, $100
		000B50E0 A4820000 sh      v0, $0(a0)
		000B50E4 24840002 addiu   a0, $2
		000B50E8 84820000 lh      v0, $0(a0)
		000B50EC 00000000 nop
		000B50F0 00021900 sll     v1, v0, $4
		000B50F4 00621823 subu    v1, v0
		000B50F8 00031840 sll     v1, $1
		000B50FC 00660018 mult    v1, a2
		000B5100 24A5FFFF subiu   a1, $1
		000B5104 00001010 mfhi    v0
		000B5108 00431021 addu    v0, v1
		000B510C 000211C3 sra     v0, $7
		000B5110 00031FC3 sra     v1, $1F
		000B5114 00431023 subu    v0, v1
		000B5118 24420078 addiu   v0, $78
		000B511C A4820000 sh      v0, $0(a0)
		000B5120 14A0FFE6 bne     a1, 0, $B50BC
		000B5124 24840006 addiu   a0, $6
		000B5128 03E00008 jr      ra
#endif
}

void InitialiseLaraCarriedItems(long keep_carried_items)//?, B4EE4
{
	long i;
	long gun_type;
	struct lara_info lara_backup;
	short lara_item_number = lara.item_number;

	if (lara.item_number == -1)
	{
		return;
	}

	lara_item->meshswap_meshbits &= 0xFFDF;
	lara_item->data = &lara;

	if (keep_carried_items)
	{
		//$B51C0
		memcpy(&lara_backup, &lara, sizeof(struct lara_info));
		memset(&lara, 0, sizeof(struct lara_info));
		memcpy(&lara.pistols_type_carried, &lara_backup.pistols_type_carried, 59);
	}
	else
	{
		memset(&lara, 0, sizeof(struct lara_info));
	}

	lara.item_number = lara_item_number;

	lara.air = 0x708;
	lara.hit_direction = -1;
	lara.weapon_item = -1;
	PoisonFlag = 0;
	lara.holster = 0xE;
	lara.RopePtr = -1;
	lara.water_surface_dist = 0x64;
	lara.dpoisoned = 0;
	lara.poisoned = 0;
	lara.location = -1;
	lara.highest_location = -1;
	lara.Unused1 = 1;

	//a0 = 0xA0000;
	//s3= lara_item
	lara_item->hit_points = 0x3E8;

	for (i = 0; i < gfNumPickups; i++)
	{
		DEL_picked_up_object(convert_invobj_to_obj(gfPickups[i]));
	}//$B52AC

	gfNumPickups = 0;
	if (!(gfLevelFlags & 1) && objects[PISTOLS_ITEM].loaded)
	{
		gun_type = 1;
	}
	else
	{
		//$B52D8
		gun_type = 0;
	}

	//v0 = &objects
	if ((gfLevelFlags & 0x80) && objects[HK_ITEM].loaded)
	{
		//v1 = lara
		if ((lara.hk_type_carried & 1))
		{
			gun_type = 5;
		}//$B531C
	}//$B531C

	 //s1 = lara;
	lara.gun_status = 0;
	lara.last_gun_type = gun_type;
	lara.gun_type = gun_type;
	lara.request_gun_type = gun_type;

	LaraInitialiseMeshes();

	//a0 = &objects
	lara.skelebob = 0;

	//objects[PISTOLS_ITEM]

	if (objects[PISTOLS_ITEM].loaded)
	{
		lara.pistols_type_carried = 9;
	}//$B5354

	lara.binoculars = 1;

#if 0
	000B535C 8FA20198 lw      v0, $198(sp)
		000B5360 00000000 nop
		000B5364 1440000B bne     v0, 0, $B5394
		000B5368 00000000 nop
		000B536C 8C8258F0 lw      v0, $58F0(a0)
		000B5370 00000000 nop
		000B5374 00431024 and v0, v1
		000B5378 10400002 beq     v0, 0, $B5384
		000B537C 24020003 addiu   v0, 0, $3
		000B5380 A6220146 sh      v0, $146(s1)
#endif

		lara.num_small_medipack = 3;
	lara.num_large_medipack = 1;

	lara.num_pistols_ammo = -1;
	InitialiseLaraAnims(lara_item);

	//s0 = 0;
	//v1 = 0x78
	//a0 = gfNumTakeaways;
	//v0 = 0xA0000
	DashTimer = 120;

	if (gfNumTakeaways != 0)
	{
		for (i = 0; i < gfNumTakeaways; i++)
		{
			convert_invobj_to_obj(gfTakeaways[i]);
			NailInvItem(gfTakeaways[i]);
		}
	}//$B53F8

	gfNumTakeaways = 0;

	if (gfCurrentLevel < LVL5_BASE)
	{
		weapons[1].damage = 6;
	}
	else
	{
		//$B541C
		weapons[1].damage = 15;
	}

	if (gfCurrentLevel == LVL5_DEEPSEA_DIVE)
	{
		lara.puzzleitems[0] = 10;
	}//$B5450

	if (gfCurrentLevel == LVL5_SUBMARINE)
	{
		lara.pickupitems = 0;
		lara.pickupitemscombo = 0;
		lara.keyitems = 0;
		lara.keyitemscombo = 0;
		lara.puzzleitemscombo = 0;

		for (i = 0; i < 0xB; i++)
		{
			lara.puzzleitems[i] = 0;
		}
	}

	if (gfCurrentLevel == LVL5_SINKING_SUBMARINE)
	{
		lara.puzzleitems[0] = 0;
		lara.pickupitems = 0;
	}//$B54A8

	if (gfCurrentLevel == LVL5_ESCAPE_WITH_THE_IRIS)
	{
		lara.puzzleitems[2] = 0;
		lara.puzzleitems[3] = 0;
		lara.pickupitems &= -2;
	}

	if (gfCurrentLevel == LVL5_RED_ALERT)
	{
		lara.pickupitems &= -3;
	}

	if (gfCurrentLevel - 0xB < 4)
	{
		lara.bottle = 0;
		lara.wetcloth = 0;
	}

	lara.pickupitems &= -9;
}

void InitialiseFootPrints()//?(<), B52FC(<)
{
	int i;

	for (i = 0; i < 32; i++)
	{
		FootPrint[i].Active = 0;
	}

	return;
}

void BaddyObjects()//?, B5328
{
	struct object_info* object = &objects[LARA];

	object->shadow_size = (10 * UNIT_SHADOW) / 16;
	object->initialise = &InitialiseLaraLoad;
	object->hit_points = LARA_HITPOINTS;
	object->draw_routine = NULL;

	object->using_drawanimating_item = FALSE;
	object->save_hitpoints = TRUE;
	object->save_position = TRUE;
	object->save_flags = TRUE;
	object->save_anim = TRUE;


	object = &objects[SAS];

	if (object->loaded)
	{
		object->intelligent = 1;
		object->HitEffect = 0;
		//v1 = 0x4000000
		object->HitEffect = 1;
		//v0 = 0xFFFF8C7C
		//v1 = 0x1F0000
		///object->initialise = NULL;///@FIXME Local module 0xFFFF8C7C(IB), 0xFFFF8C08(RET)

		object->collision = &CreatureCollision;
		object->shadow_size = 46;
		object->pivot_length = 50;
		object->radius = 102;
		object->hit_points = 40;
		object->bite_offset = 0;
		object->save_flags = 1;//t3
		object->save_anim = 1;
		object->save_hitpoints = 1;
		object->save_position = 1;

		//a0 = &bones[object->bone_index];

#if PSX_VERSION && RELOC
		object->control = RelocPtr[MOD_SAS][0];
#endif
		bones[object->bone_index + 24] |= 8u;
		bones[object->bone_index + 24] |= 4u;
		bones[object->bone_index + 52] |= 8u;
		bones[object->bone_index + 52] |= 4u;
	}

	//loc_1BA4
	object = &objects[BLUE_GUARD];
	//v0 = *(int*)&object->bite_offset;

	//v0 = 0;
	if (object->loaded)
	{
		//v0 = 0xFFFF8C7C
		///object->initialise = 0xFFFF8C7C
		//a0 = RelocPtr[MOD_SAS][0]
		//a3 = &objects[LARA];
#if PSX_VERSION && RELOC
		object->control = RelocPtr[MOD_SAS][0];
#endif
		//v0 = *(int*)&objects[SWAT].bite_offset

		//a0 = 0xF3FF0000
		if (objects[SWAT].loaded)
		{
			object->anim_index = objects[SWAT].anim_index;
		}//loc_1BFC

		 //a0 = 0xF3FFFFFF
		 //v0 = &CreatureCollision;
		object->collision = &CreatureCollision;
		object->hit_points = 24;
		object->radius = 102;

		//v0 = *(int*)&object->bite_offset;
		object->shadow_size = 128;
		object->pivot_length = 50;
		object->explodable_meshbits = 0x4000;

		//v1 = 0x20000;
		object->intelligent = 1;
		object->HitEffect = 0;
		//v1 = 0x4000000
		object->HitEffect = 1;

		//a0 = 4
		//v1 = DrawBaddieGunFlash
		object->draw_routine_extra = &DrawBaddieGunFlash;

		//v1 = 0xA0000

		object->bite_offset = 4;
		//v0 = *(int*)&object->bite_offset;
		//a0 = object->bone_index;
		//a1 = &bones

		object->intelligent = 1;
		object->save_anim = 1;
		object->save_hitpoints = 1;
		object->save_position = 1;

#if 0///@CRASH
		((int*)bones[object->bone_index])[24] |= 8;
		((int*)bones[object->bone_index])[24] |= 4;
		((int*)bones[object->bone_index])[52] |= 8;
		((int*)bones[object->bone_index])[52] |= 4;
#endif
		//v1 = 0xA0000
		//a0 = object->mesh_index;
		//v0 = objects[MESHSWAP1].mesh_index
		//a2 = &meshes[]
		//v0 = meshes[objects[MESHSWAP1].mesh_index]
		//a0 = ((int*)meshes[object->mesh_index])[21] = ((int*)meshes[objects[MESHSWAP1].mesh_index])[20];

		//v1 = meshes[object->mesh_index];
		//v0 = meshes[objects[MESHSWAP1].mesh_index];

		((int*)meshes[object->mesh_index])[28] = ((int*)meshes[objects[MESHSWAP1].mesh_index])[26];

		object->object_mip = 0x1400;
	}//loc_1D50

	object = &objects[SWAT];
	//v1 = *(int*)&object->bite_offset
	//t1 = 0x10000
	if (object->loaded)
	{
		//v0 = 0xF3FFFFFF
		//a0 = 0x20000
		object->intelligent = 1;
		object->HitEffect = 0;
		//v1 = 0x4000000
		object->HitEffect = 1;
		//v0 = 0xFFFF8C7C
		//v1 = 0x1F0000
		///object->initialise = 0xFFFF8C7C
		//v0 = 0x30000
		//a1 = RelocPtr[MOD_SAS];
		//v0 = &CreatureCollision
		//a2 = RelocPtr[MOD_SAS][0];
		//v1 = 0x80
		object->collision = &CreatureCollision;
		//v0 = 0x18
		object->shadow_size = 128;
		object->hit_points = 24;
		//V1 = 0X32
		object->radius = 102;
		object->explodable_meshbits = 16384;
		//v0 = 0x50594
		object->pivot_length = 50;
		//v1 = 0x200000
		object->bite_offset = 0;
		object->draw_routine_extra = &DrawBaddieGunFlash;
		//v0 = *(int*)&object->bite_offset
		object->save_flags = 1;
		object->save_anim = 1;
		object->save_hitpoints = 1;
		object->save_position = 1;

		//a0 = object->bone_index
		//a1 = bones
#if PSX_VERSION && RELOC
		object->control = RelocPtr[MOD_SAS][0];
#endif

#if 0///@CRASH
		//a0 = &bones[object->bone_index];
		((int*)bones[object->bone_index])[24] |= 8;
		((int*)bones[object->bone_index])[24] |= 4;
		((int*)bones[object->bone_index])[52] |= 8;
		((int*)bones[object->bone_index])[52] |= 4;
#endif
		//a3 = &objects[LARA]
		//a0 = meshes[object->mesh_index]

		//v0 = meshes[objects[BRIDGE_TILT2].mesh_index]
		//a2 = meshes

		((int*)meshes[object->mesh_index])[21] = ((int*)meshes[objects[BRIDGE_TILT2].mesh_index])[20];

		//v1 = meshes[object->mesh_index]
		//v0 = meshes[objects[BRIDGE_TILT2].mesh_index]

		//a0 = ((int*)meshes[objects[BRIDGE_TILT2].mesh_index])[26]
		((int*)meshes[object->mesh_index])[27] = ((int*)meshes[objects[BRIDGE_TILT2].mesh_index])[26];

		object->object_mip = 0x1400;

	}//loc_1EE4

	object = &objects[SWAT_PLUS];

	//v0 = 0x0
	if (object->loaded)
	{
		//v0 = 0xFFFF8C7C
		//v1 = 0x1F0000
		///object->initialise = 0xFFFF8C7C;
		//v0 = RelocPtr[SWAT];
		//a0 = RelocPtr[SWAT][0];
		//v1 = &objects[LARA];
#if PSX_VERSION && RELOC
		object->control = RelocPtr[SWAT][0];
#endif
		//v0 = objects[SWAT].

		if (objects[SWAT].loaded)
		{
			object->anim_index = objects[SWAT].anim_index;
		}
		else
		{
			//loc_1F3C
			object->anim_index = objects[BLUE_GUARD].anim_index;
		}

		//a1 = 0xF3FFFFFF
		//v0 = CreatureCollision
		//v1 = 0x80
		object->collision = &CreatureCollision;
		//v0 = 0x18
		object->shadow_size = 128;

		//li      $v1, 0x32  # '2'
		//li      $a0, 0x66  # 'f'
		object->hit_points = 24;
		object->pivot_length = 50;

		//v1 = *(int*)&object->bite_offset
		object->draw_routine_extra = DrawBaddieGunFlash;
		//v0 = 0x20000
		object->radius = 102;
		//a0 = 0x400000
		object->intelligent = 1;
		object->HitEffect = 0;
		//v0 = 0x4000000
		object->HitEffect = 1;
		object->bite_offset = 0;
		//v0 = *(int*)&object->bite_offset
		//v1 = 0x200000
		object->save_flags = 1;
		object->save_anim = 1;
		//v1 = 0x100000
		object->save_hitpoints = 1;
		object->save_position = 1;
		//0x80000

		//a0 = object->bone_index
		//a1 = bones
		//a0 = &bones[object->bone_index];
#if 0///@CRASH
		((int*)bones[object->bone_index])[24] |= 8;
		((int*)bones[object->bone_index])[24] |= 4;
		((int*)bones[object->bone_index])[52] |= 8;
		((int*)bones[object->bone_index])[52] |= 4;

		//a3 = &objects
		//a0 = meshes[object->mesh_index]
		//v0 = meshes]objects[MESHSWAP1].mesh_index]
		//a2 = meshes

		((int*)meshes[object->mesh_index])[21] = ((int*)meshes[objects[MESHSWAP1].mesh_index])[20];

		//v1 = meshes[object->mesh_index]
		//v0 = meshes[objects[MESHSWAP1].mesh_index]
		((int*)meshes[object->mesh_index])[27] = ((int*)meshes[objects[MESHSWAP1].mesh_index])[26];
		object->object_mip = 0x1400;
#endif
	}//loc_20A4
}

void InitialiseObjects()//?(<), B96EC(<) sub_5DE0
{
	int i;

	//loc_5E5C
	for (i = 0; i < NUMBER_OBJECTS; i++)
	{
		objects[i].initialise = NULL;
		objects[i].collision = NULL;
		objects[i].control = NULL;
		objects[i].draw_routine = NULL;
		objects[i].ceiling = NULL;
		objects[i].floor = NULL;
		objects[i].pivot_length = 0;
		objects[i].radius = 10;
		objects[i].shadow_size = 0;
		objects[i].hit_points = -16384;
		objects[i].explodable_meshbits = 0;
		objects[i].draw_routine_extra = NULL;
		objects[i].object_mip = 0;

		objects[i].intelligent = FALSE;
		objects[i].save_position = FALSE;
		objects[i].save_hitpoints = FALSE;
		objects[i].save_flags = FALSE;
		objects[i].save_anim = FALSE;
		objects[i].water_creature = FALSE;
		objects[i].save_mesh = FALSE;
		objects[i].using_drawanimating_item = TRUE;

		((int*)&objects[i].frame_base)[0] += (uintptr_t)frames;
	}

	BaddyObjects();
	ObjectObjects();
	TrapObjects();
	InitialiseHair();
	InitialiseEffects();

	NumRPickups = 0;
	CurrentSequence = 0;

	SequenceResults[0][2][1] = 1;
	SequenceResults[1][0][2] = 2;
	SequenceResults[1][2][0] = 3;
	SequenceResults[2][0][1] = 4;
	SequenceResults[2][1][0] = 5;

	for (i = 0; i < 6; i++)
	{
		SequenceUsed[i] = 0;
	}

	if (gfNumMips != 0)
	{
		for (i = 0; i < gfNumMips; i++)
		{
			objects[((gfMips[i] & 0xF) << 1) | ANIMATING1].object_mip = (gfMips[i] & 0xF0) << 6;
		}
	}//0xB98B8

	if (gfCurrentLevel == LVL5_STREETS_OF_ROME)
	{
		find_a_fucking_item(ANIMATING10);
	}

	if (gfCurrentLevel == LVL5_OLD_MILL)
	{
		find_a_fucking_item(ANIMATING16)->mesh_bits = 0;
	}//B98F0

	if (objects[RAT].loaded)
	{
		Rats = (struct RAT_STRUCT*)game_malloc(sizeof(struct RAT_STRUCT) * 32);
	}//B9914

	if (objects[BAT].loaded)
	{
		Bats = (struct BAT_STRUCT*)game_malloc(sizeof(struct BAT_STRUCT) * 64);
	}//B9938

	if (objects[SPIDER].loaded)
	{
		Spiders = (struct SPIDER_STRUCT*)game_malloc(sizeof(struct SPIDER_STRUCT) * 64);
	}
}//0xB996C

#if !PC_VERSION
void sub_B3A7C(int a0)
{
	struct PSXSPRITESTRUCT* spr = &psxspriteinfo[objects[MISC_SPRITES].mesh_index];

	envmap_data[0] = (spr->tpage << 16) | spr->clut;
	envmap_data[1] = ((spr->u1 + 32) & 0xFF) | (((spr->v1 + 32) & 0xFF) << 8);
	spr++;

	envmap_data[2] = (spr->tpage << 16) | spr->clut;
	envmap_data[3] = ((spr->u1 + 32) & 0xFF) | (((spr->v1 + 32) & 0xFF) << 8);
	spr++;

	envmap_data[4] = (spr->tpage << 16) | spr->clut;
	envmap_data[5] = ((spr->u1 + 32) & 0xFF) | (((spr->v1 + 32) & 0xFF) << 8);
}
#endif
/*
 * [FUNCTIONALITY] - LoadLevel.
 * Relocates all game data pointers from the level file to be loaded back into the engine.
 * Note: The GAMEWAD reader must be initialised to a level file entry.
 * Note: The GAMEWAD reader's position must point to the level file data.
 * Note: This code is part of the SETUP.MOD module.
 */
#if PSXPC_VERSION || PSX_VERSION || SAT_VERSION
#if DISC_VERSION
void LoadLevel()//?(<), B3B50(<) (F)
#else
#if PSX_VERSION || SAT_VERSION
void LoadLevel(int nHandle)//?, B3B50(<)
#elif PSXPC_VERSION
void LoadLevel(FILE* nHandle)
#endif
#endif

{
	struct Level* level;
#if PSX_VERSION
#if PSXPC_TEST
	RECT16 tex[2];
#elif PSX_VERSION
	RECT tex[2];
#endif
#endif
	char* ptr = NULL;
	char* ptr2 = NULL;
	int size, i, j;
	long* relocationPtr = NULL;
	long gunType;

	InItemControlLoop = 0;

#if DISC_VERSION
	DEL_CDFS_Read((char*)&tsv_buffer[0], sizeof(struct Level));
#else
	FILE_Read((char*)&tsv_buffer[0], sizeof(struct Level), 1, nHandle);
#endif

	level = (struct Level*)&tsv_buffer[0];

#if DEBUG_VERSION
	if (level->objectVersion != PSX_FILE_VERSION)
	{
		printf("Wrong Version Number!!!\n");
		printf("Game Ver: %d  Level Ver: %d\n", OBJECT_VERSION, level->objectVersion);
	}
#endif

	LaraDrawType = level->laraDrawType;
	WeatherType = level->weatherType;
	RoomDrawType = level->roomDrawType;

#if !DISC_VERSION
#if PSX_VERSION
	PClseek(nHandle, level->offsetSoundPointers, 0);
#elif PSXPC_VERSION
	fseek(nHandle, level->offsetSoundPointers, SEEK_SET);
#endif
#endif

	if (level->numSoundEffects != 0)
	{
		GtSFXEnabled = 0;
		ptr = game_malloc(level->numSoundEffects * sizeof(int));

#if DISC_VERSION
		DEL_CDFS_Read(ptr, level->numSoundEffects * sizeof(int));
#else
		FILE_Read(ptr, sizeof(int), level->numSoundEffects, nHandle);
#if PSX_VERSION
		PClseek(nHandle, level->offsetSoundData, 0);
#elif PSXPC_VERSION
		fseek(nHandle, level->offsetSoundData, 0);
#endif
#endif
		ptr2 = game_malloc(level->soundWadLength);

#if DISC_VERSION
		DEL_CDFS_Read(ptr2, level->soundWadLength);
#else
		FILE_Read(ptr, level->soundWadLength, sizeof(char), nHandle);
#endif
		GtSFXEnabled = LoadSoundEffects(level->numSoundEffects, (long*)ptr, ptr2, level->soundWadLength);//LoadSoundEffects

		game_free(level->numSoundEffects * sizeof(int));
		game_free(level->soundWadLength);

	}//R loc_304, IB loc_36C

#if !DISC_VERSION
#if PSX_VERSION
	PClseek(nHandle, level->offsetTextiles, 0);
#elif PSXPC_VERSION
	fseek(nHandle, level->offsetTextiles, SEEK_SET);
#endif
#endif

	ptr = game_malloc(0x40000);///@TODO macro size

	/*   PSX VRAM   (H)
	*  --------------------- 1024px
	*  | TL | TR | TPAGE1 |  |
	*  ---------------------  v
	*  | BL | BR | TPAGE2 |
	*  ---------------------
	*(W)1024px-->
	*
	* Loading texture pages+cluts into VRAM (TPAGE1, TPAGE2)
	*
	*/

	//Setup rect
#if PSX_VERSION
	tex[0].x = 512;//x position of textile data in VRAM
	tex[0].y = 0;
	tex[0].w = 512;//Width of VRAM texture space
	tex[0].h = 256;//Height of tpage
#endif

	//loc_340, loc_3B4
	for (i = 0; i < 2; i++)///@CHECK
	{
#if DISC_VERSION
		DEL_CDFS_Read(ptr, 0x40000);
#else
		FILE_Read(ptr, 1, 0x40000, nHandle);
#endif
		LOAD_DrawEnable(0);

#if PSX_VERSION
#if PSXPC_TEST
		LoadImagePSX(&tex[0], (unsigned long*)ptr);
#else
		LoadImage(&tex[0], (unsigned long*)ptr);
#endif
		DrawSync(0);
#endif

		LOAD_DrawEnable(1);

#if PSX_VERSION
		tex[0].y += 256;
#endif
	}

	game_free(0x40000);

	ClutStartY = level->clutStartY;

#if !DISC_VERSION
#if PSX_VERSION
	PClseek(nHandle, level->offsetAnimFrames, 0);
#elif PSXPC_VERSION
	fseek(nHandle, level->offsetAnimFrames, SEEK_SET);
#endif
	AnimFilePos = level->offsetAnimFrames;
#else
	AnimFilePos = cdCurrentSector;
#endif

	ptr = game_malloc(level->frameDataLength);
	frames = (short*)ptr;

#if DISC_VERSION
	DEL_CDFS_Read(ptr, level->frameDataLength);
#else
	FILE_Read(ptr, 1, level->frameDataLength, nHandle);
#endif

	AnimFileLen = level->frameDataLength;

#if !DISC_VERSION
#if PSX_VERSION
	PClseek(nHandle, level->offsetRoomInfo, 0);
#elif PSXPC_VERSION
	fseek(nHandle, level->offsetRoomInfo, SEEK_SET);
#endif
#endif

	ptr = game_malloc(level->roomInfoLength);

#if DISC_VERSION
	DEL_CDFS_Read(ptr, level->roomInfoLength);
#else
	FILE_Read(ptr, 1, level->roomInfoLength, nHandle);
#endif

	room = (struct room_info*)ptr;
	ptr += sizeof(struct room_info) * level->numRooms;

	number_rooms = level->numRooms;
#define OLD_CODE 1
	if (level->numRooms > 0)
	{
		//loc_4D4
		for(i = 0; i < number_rooms; i++)
		{

#if OLD_CODE
			size = *(unsigned int*)&room[i].data;
			room[i].data = (short*)ptr;

			for (j = 0; j < 24; j++)
			{
				*(int*)&ptr[4 + (j * 4)] += (*(int*)&room[i].data);
			}///@CRITICAL the last relocated pointer seemingly points to invalid memory?!?!?!??

			ptr += size;

#elif UNOPTIMISED//Original
			ptr2 = ptr;
			ptr2 += 4;

			size = (int)room[i].data;
			room[i].data = (short*)ptr;
			ptr += size;

			//loc_4F8:
			for (j = 23; j >= 0; j--)
			{
				((int*)ptr2)[1 + j] += (int)room[i].data;
			}
#else
			size = (int)room[i].data;
			room[i].data = (short*)ptr;
			
			//loc_4F8:
			for (j = 23; j >= 0; j--)
			{
				((int*)ptr)[1 + j] += (int)room[i].data;
			}

			ptr += size;
#endif

			size = (uintptr_t)room[i].door;
			room[i].door = (short*)ptr;
			ptr += size;

			size = (uintptr_t)room[i].floor;
			room[i].floor = (struct FLOOR_INFO*)ptr;
			ptr += size;

			size = (uintptr_t)room[i].light;
			room[i].light = (struct LIGHTINFO*)ptr;
			ptr += size;

			size = (uintptr_t)room[i].mesh;
			room[i].mesh = (struct MESH_INFO*)ptr;
			ptr += size;
		}
	}//loc_570

	floor_data = (short*)ptr;
	ptr += level->floorDataLength;

	OutsideRoomOffsets = (short*)ptr;
	ptr += 1460;

	OutsideRoomTable = ptr;
	ptr += level->outsideRoomTableLength;

	RoomBBoxes = (struct SVECTOR*)ptr;
	ptr += level->roomBoundingBoxesLength;

	mesh_base = (short*)ptr;
	ptr += level->meshBaseLength;

	meshes = (short**)ptr;
	ptr += level->meshesLength;

	anims = (struct ANIM_STRUCT*)ptr;
	ptr += level->animsLength;

	changes = (struct CHANGE_STRUCT*)ptr;
	ptr += level->changesLength;

	ranges = (struct RANGE_STRUCT*)ptr;
	ptr += level->rangesLength;

	commands = (short*)ptr;
	ptr += level->commandsLength;

	bones = (long*)ptr;
	ptr += level->bonesLength;

	if (level->numBones * 2 > 0)
	{
		for (i = 0; i < level->numBones * 2; i++)
		{
#if OLD_CODE
			*(int*)&meshes[i] += *(int*)&mesh_base;//Original game does add *(int*) &meshes[i] >> 0x1F too
#else
			((int*)&meshes)[i] += (int)mesh_base + ((((int)meshes[i] + ((int)meshes[i] >> 31)) >> 1) << 1);
#endif
		}
	}
	//loc_674

	if (level->numAnims > 0)
	{
		for (i = 0; i < level->numAnims; i++)
		{
#if 0
			*(int*)&anims[i].frame_ptr += *(int*)&frames;
#else
			((int*)&anims[i].frame_ptr)[0] += (uintptr_t)frames;
#endif
		}
	}//loc_6BC

	AnimTextureRanges = (unsigned short*)ptr;
	ptr += level->animTextureRangesLength;

	psxtextinfo = (struct PSXTEXTSTRUCT*)ptr;
	ptr += level->textureInfoLength;

	psxspriteinfo = (struct PSXSPRITESTRUCT*)ptr;
	ptr += level->spriteInfoLength;

	RoomTextInfo = (struct MMTEXTURE*)ptr;
	ptr += level->mmTextureInfoLength;

	sound_effects = (struct OBJECT_VECTOR*)ptr;
	ptr += level->soundEffectInfoLength;

	sample_lut = (short*)ptr;
#if AUG_VERSION || JULY_VERSION
	ptr += 740;
#else
	ptr += 900;
#endif

	sample_infos = (struct SAMPLE_INFO*)ptr;
	ptr += level->sampleInfoLength;

	items = (struct ITEM_INFO*)ptr;
	ptr += 0x9000;

	AIObjects = (struct AIOBJECT*)ptr;
	ptr += sizeof(struct AIOBJECT) * level->numAIObjects;

	boxes = (struct box_info*)ptr;
	ptr += level->boxesLength;

	overlap = (unsigned short*)ptr;
	ptr += level->overlapsLength;

	ground_zone[0][0] = (short*)ptr;
	ptr += level->groundZoneLength;

	ground_zone[1][0] = (short*)ptr;
	ptr += level->groundZone2Length;

	ground_zone[2][0] = (short*)ptr;
	ptr += level->groundZone3Length;

	nAnimTextureRanges = level->numAnimTextureRanges;
	number_sound_effects = level->soundEffectInfoLength / sizeof(struct OBJECT_VECTOR);
	nAnimUVRanges = level->numAnimUVRanges;
	level_items = level->numLevelItems;
	nAIObjects = level->numAIObjects;

	ground_zone[3][0] = (short*)ptr;
	ptr += level->groundZone4Length;

	ground_zone[4][0] = (short*)ptr;
	ptr += level->groundZone5Length;

	ground_zone[0][1] = (short*)ptr;
	ptr += level->groundZoneLength;
	
	ground_zone[1][1] = (short*)ptr;
	ptr += level->groundZone2Length;

	ground_zone[2][1] = (short*)ptr;
	ptr += level->groundZone3Length;

	ground_zone[3][1] = (short*)ptr;
	ptr += level->groundZone4Length;

	ground_zone[4][1] = (short*)ptr;
	ptr += level->groundZone5Length;

	number_boxes = level->numBoxes;

	if (level->numBoxes > 0)
	{
		for (i = level->numBoxes; i != 0; i--)
		{
			if ((boxes[i].overlap_index & BOX_LAST))
			{
				boxes[i].overlap_index |= BOX_BLOCKED;
			}
		}
	}//loc_854

	camera.fixed = (struct OBJECT_VECTOR*)ptr;
	ptr += level->fixedCameraLength;

	SpotCam = (struct SPOTCAM*)ptr;
	NumFixedCameras = level->numFixedCameras;
	number_spotcams = level->numSpotCameras;
	number_cameras = level->numFixedCameras;

#if DISC_VERSION
#if PSX_VERSION
#if PSXPC_TEST
	DEL_CDFS_Read((char*)&objects_raw, NUMBER_OBJECTS * sizeof(struct object_info) + NUMBER_STATIC_OBJECTS * sizeof(struct static_info) + 480 + 480);
#else
	DEL_CDFS_Read((char*)&objects, NUMBER_OBJECTS * sizeof(struct object_info) + NUMBER_STATIC_OBJECTS * sizeof(struct static_info) + 480 + 480);
#endif
#elif PSXPC_VERSION
	DEL_CDFS_Read((char*)&objects_raw, NUMBER_OBJECTS * sizeof(struct object_info) + NUMBER_STATIC_OBJECTS * sizeof(struct static_info) + 480 + 480);
#endif
#else
#if PSX_VERSION
	PClseek(nHandle, level->offsetObjects, 0);
#if PSXPC_TEST
	FILE_Read((char*)&objects_raw, 1, NUMBER_OBJECTS * sizeof(struct object_info) + NUMBER_STATIC_OBJECTS * sizeof(struct static_info) + 480 + 480, nHandle);
#else
	FILE_Read((char*)&objects, 1, NUMBER_OBJECTS * sizeof(struct object_info) + NUMBER_STATIC_OBJECTS * sizeof(struct static_info) + 480 + 480, nHandle);
#endif
	PCclose(nHandle);
#elif PSXPC_VERSION
	fseek(nHandle, level->offsetObjects, SEEK_SET);
	FILE_Read((char*)&objects_raw, 1, NUMBER_OBJECTS * sizeof(struct object_info) + NUMBER_STATIC_OBJECTS * sizeof(struct static_info) + 480 + 480, nHandle);
	fclose(nHandle);
#endif
#endif

	for (i = 63; i >= 0; i--)
	{
		RelocPtr[i] = NULL;
	}

	if (level->numAiModules != 0)
	{
#if DISC_VERSION
		FRIG_CD_POS_TO_CUR();
		DEL_CDFS_Read((char*)&tsv_buffer[256], 1920);
#else
#if PSX_VERSION
		nHandle = PCopen(CODE_WAD, 0, 0);
#elif PSXPC_VERSION
		nHandle = fopen(CODE_WAD, "rb");
#endif
		FILE_Read((char*)&tsv_buffer[256], 20, 96, nHandle);
#endif

		if (level->numAiModules > 0)
		{
			//loc_938
			for(i = 0; i < level->numAiModules; i++)
			{
				relocationPtr = (long*)((char*)&tsv_buffer[256] + (level->aiModuleIndices[i] * 20));
				///relocationPtr = (long*)&((char*)&tsv_buffer)[level->aiModuleIndices[i] * 20];
				ptr = game_malloc(relocationPtr[1]);

#if DISC_VERSION
				DEL_CDFS_Seek(relocationPtr[0]);
				DEL_CDFS_Read(ptr, relocationPtr[1]);
#else
#if PSX_VERSION
				PClseek(nHandle, relocationPtr[0], 0);
#elif PSXPC_VERSION
				fseek(nHandle, relocationPtr[0], SEEK_SET);
#endif
				FILE_Read(ptr, 1, relocationPtr[1], nHandle);
#endif
				ptr2 = game_malloc(relocationPtr[3]);

#if DISC_VERSION
				DEL_CDFS_Seek(relocationPtr[2]);
				DEL_CDFS_Read(ptr2, relocationPtr[3]);
#else
#if PSX_VERSION
				PClseek(nHandle, relocationPtr[2], 0);
#elif PSXPC_VERSION
				fseek(nHandle, relocationPtr[2], SEEK_SET);
#endif
				FILE_Read(ptr2, 1, relocationPtr[3], nHandle);
#endif
				RelocateModule((unsigned long)ptr, (unsigned long*)ptr2);

				game_free(relocationPtr[3]);

				RelocPtr[relocationPtr[4]] = (unsigned long*)ptr;
			}
		}
		//loc_9F0
#if !DISC_VERSION
#if PSX_VERSION
		PCclose(nHandle);
#elif PSXPC_VERSION
		fclose(nHandle);
#endif
#endif
	}//loc_9F8

	//B4228
	InitialiseFXArray(1);
	InitialiseLOTarray(1);
	InitialiseObjects();
	InitialiseClosedDoors();
	InitialiseItemArray(256);

	GlobalPulleyFrigItem = -1;

	if (level_items > 0)
	{
		//loc_A3C
		for(i = 0; i < level_items; i++)
		{
			InitialiseItem(i);
		}
	}
	//loc_A5C
	SetupGame();

	if (number_rooms > 0)
	{
#if 0 ///@FIXME segfault under linux
		//loc_A84
		for(i = 0; i < number_rooms; i++)
		{
			if (room[i].num_meshes > 0)
			{
				struct FLOOR_INFO* t1;
				struct box_info* v0;

				//loc_A9C
				for (j = room[i].num_meshes; j > 0; j--)
				{
					t1 = &room[i].floor[((room[i].mesh[j].z - room[i].z) >> 10) + ((room[i].mesh[j].x - room[i].x) >> 10) * room[i].x_size];
					v0 = &boxes[t1->box];
					if (!(v0->overlap_index & BOX_BLOCKED))
					{
						if (gfCurrentLevel == LVL5_BASE && i != 0x13 && i != 0x17 && i != 0x10)
						{
							struct static_info* v1 = &static_objects[room[i].mesh[j].static_number];
							//loc_B30
							if ((t1->floor << 8) < ((room[i].mesh[j].y - v1->y_maxc) + 512) && (room[i].mesh[j].y - v1->y_minc) < (t1->floor << 8))
							{
								if (v1->x_maxc != 0 && v1->x_minc != 0 && v1->z_maxc != 0 && v1->z_minc != 0 && !((v1->x_maxc ^ v1->x_minc) & 0x8000) && !((v1->z_maxc ^ v1->z_minc) & 0x8000))
								{
									//loc_BE8
									room[i].floor[((room[i].mesh[j].z - room[i].z) >> 10) + ((room[i].mesh[j].x - room[i].x) >> 10) * room[i].x_size].stopper = 1;
								}
							}//loc_C20
						}//loc_C20
					}//loc_C20
				}
			}//loc_C2C
		}
#endif
	}//loc_C3C

	InitialiseResidentCut(gfResidentCut[0], gfResidentCut[1], gfResidentCut[2], gfResidentCut[3]);
	
	GLOBAL_default_sprites_ptr = &psxspriteinfo[objects[DEFAULT_SPRITES].mesh_index];

	sub_B3A7C(0xB);

	GLOBAL_gunflash_meshptr = meshes[objects[GUN_FLASH].mesh_index];

	if (objects[SEARCH_OBJECT1].loaded && objects[SEARCH_OBJECT1_MIP].loaded)
	{
		((int*)meshes[objects[SEARCH_OBJECT1].mesh_index])[1] = ((int*)meshes[objects[SEARCH_OBJECT1_MIP].mesh_index])[0];
	}//loc_CF4


	//a3 = &AnimatingWaterfallsV
	//v1 = 0xA0000
	//a2 = &AnimatingWaterfalls
	//v0 = &objects
	//a1 = &objects[WATERFALL1];
	//s4 = 5;
	//t1 = meshes
	//t0 = psxtextinfo

	//loc_D20
#if 0
	for (i = 5; i >= 0; i--)
	{
		if (objects[WATERFALL1 + i].loaded)
		{
			short* meshptr;//a0
			meshptr = meshes[objects[WATERFALL1 + i].mesh_index];
			meshptr += 6;//0xC for next itr?
			meshptr += meshptr[5] << 16 >> 17;
			AnimatingWaterfalls[i] = (PSXTEXTI*)&psxtextinfo[meshptr[2] << 4];//why << 4? 1<<4=16!
			AnimatingWaterfallsV[i] = ((char*)&psxtextinfo[meshptr[2] << 4])[1];//why << 4? 1<<4=16!
		}//loc_D84
	}
#endif

	MonitorScreenTI = NULL;

	//a0 = &objects
#if 0
	if (objects[MONITOR_SCREEN].loaded)
	{
		short* meshptr;//v1
		short* meshptr_2;//a1
		short v0;
		short t0;

		//s4 = 0
		//v0 = objects[MONITOR_SCREEN].mesh_index
		//v1 = meshes
		meshptr = meshes[objects[MONITOR_SCREEN].mesh_index];

		meshptr_2 = (short*)meshptr[0];
		//v0 = meshptr_2[5];
		meshptr_2 += 6;
		//v1 = meshptr_2[5] << 16 >> 17
		meshptr_2 += meshptr_2[5] << 16 >> 17;

		v0 = meshptr_2[0];
		t0 = meshptr_2[1];

		meshptr_2 += 2;
		//a3 = 0

		meshptr_2 += meshptr_2[0] << 1;
		meshptr_2 += v0 + 3 >> 2 << 1;

		if (t0 > 0)
		{
			//v1 = 0xA0000
			//v0 = (meshptr_2[0] & 0xFFFF) << 3;
			//a0 = psxtextinfo[(meshptr_2[0] & 0xFFFF)];
			///@TODO can't find a2.....
		}//loc_EA4


	}//loc_EE4
#endif

	reset_cutseq_vars();

#if RELOC
	/*if (RelocPtr[MOD_STARS] != NULL)
	{
		((VOIDFUNCVOID*)RelocPtr[MOD_STARS][0])();
	}*///loc_DFC, loc_F14
#else
	//Unimplemented
#endif

#if 0//DISC_VERSION && !BETA_VERSION

	if (gfCurrentLevel == LVL5_TITLE && Gameflow->Language - 1 < 2)
	{
#if PSX_VERSION
		tex[0] = dword_BD7F4[0];
		tex[1] = dword_BD7F4[1];
#endif
		ptr = game_malloc(0x2000);

		LOAD_DrawEnable(0);

		if (Gameflow->Language == 2)
		{
			DEL_CDFS_OpenFile(UNKNOWN_50);
		}//loc_EA0
		else if (Gameflow->Language == 1)
		{
			DEL_CDFS_OpenFile(UNKNOWN_49);
		}

		DEL_CDFS_Read(ptr, 7296);

#if PSX_VERSION
#if PSXPC_TEST
		LoadImagePSX(&tex[0], (unsigned long*)ptr);
#else
		//LoadImage(&tex[0], (unsigned long*)ptr);
#endif
		DrawSync(0);
#endif
		LOAD_DrawEnable(1);
	}//loc_EDC

#endif

	if (gfCurrentLevel == LVL5_ESCAPE_WITH_THE_IRIS)
	{
		inventry_objects_list[INV_HK_ITEM1].yoff = 4;
		inventry_objects_list[INV_HK_ITEM1].yrot = ANGLE(-90);
		inventry_objects_list[INV_HK_ITEM1].xrot = 8448;
		inventry_objects_list[INV_HK_ITEM1].zrot = ANGLE(90);
		inventry_objects_list[INV_HK_ITEM1].flags = 10;

		inventry_objects_list[INV_HK_ITEM2].yoff = ANGLE(-90);
		inventry_objects_list[INV_HK_ITEM2].xrot = 8448;
		inventry_objects_list[INV_HK_ITEM2].zrot = ANGLE(90);
		inventry_objects_list[INV_HK_ITEM2].flags = 10;
	}
	else
	{
		//loc_F30
		inventry_objects_list[INV_HK_ITEM1].yoff = 0;
		inventry_objects_list[INV_HK_ITEM1].yrot = 0;
		inventry_objects_list[INV_HK_ITEM1].xrot = ANGLE(-90);
		inventry_objects_list[INV_HK_ITEM1].zrot = 0;
		inventry_objects_list[INV_HK_ITEM1].flags = 2;

		inventry_objects_list[INV_HK_ITEM2].yoff = 0;
		inventry_objects_list[INV_HK_ITEM2].xrot = ANGLE(-90);
		inventry_objects_list[INV_HK_ITEM2].zrot = 0;
		inventry_objects_list[INV_HK_ITEM2].flags = 2;
	}

	if (gfCurrentLevel == LVL5_TITLE)
	{
		MGSaveGamePtr = game_malloc(8192);
		FromTitle = 1;
	}//loc_F94

}
#endif

void TrapObjects()//?, B7E04
{
	UNIMPLEMENTED();
}

void ObjectObjects()//?, B84F0
{
	struct object_info* object = &objects[LARA];//$t0
	//a1 = 0x1F0000
	//t0 = objects
	//a0 = 0xFDFFFFFF
	//v0 = InitialiseLaraLoad
	//v1 = 0xA0
	object->shadow_size = 160;
	//v1 = 0x3E8
	//t5 = 0x100000
	//t4 = 0x80000
	//t3 = 0x200000
	//t2 = 0x400000
	object->initialise = &InitialiseLaraLoad;
	//v0 = object->flags
	//t1 = 0x10000
	object->hit_points = 1000;
	object->draw_routine = NULL;
	object->bite_offset &= 0xFDFF;
	object->save_hitpoints = 1;
	object->save_position = 1;
	object->save_flags = 1;
	object->save_anim = 1;

#if 1//LARA temporary hack (this function is incomplete)
	bones[0] = 10;
#endif
	
	object = &objects[SAS];
	//v1 = object->flags
	//v0 = v1 & t1
	//t6 = 0x1F0000
	if (object->loaded)
	{
		//v0 = 0xF3FFFFFF
		//a0 = 0x20000
	}//loc_1BA4

#if 0
		or $a0, $v1, $a0
		and $a0, $v0
		lui     $v1, 0x400
		or $a0, $v1
		li      $v0, 0xFFFF8C7C
		lui     $v1, 0x1F
		sw      $v0, 0xC($t0)
		lui     $v0, 3
		lw      $a1, 0x1EDDD4
		li      $v0, 0x29E10
		lw      $a2, 0($a1)
		li      $v1, 0x80
		sw      $v0, 0x20($t0)
		li      $v0, 0x28  # '('
		sh      $v1, 0x2E($t0)
		li      $v1, 0x32  # '2'
		sh      $v1, 0x2A($t0)
		li      $v1, 0x66  # 'f'
		sh      $v1, 0x2C($t0)
		lui     $v1, 0xA
		sh      $v0, 0x28($t0)
		sw      $a0, 0x30($t0)
		sh      $zero, 0x30($t0)
		lw      $v0, 0x30($t0)
		lw      $a0, 4($t0)
		lw      $a1, 0xA25E4
		or $v0, $t3
		or $v0, $t2
		or $v0, $t5
		or $v0, $t4
		sll     $a0, 2
		addu    $a0, $a1
		sw      $a2, 0x10($t0)
		sw      $v0, 0x30($t0)
		lw      $v0, 0x60($a0)
		nop
		ori     $v0, 8
		sw      $v0, 0x60($a0)
		lw      $v1, 4($t0)
		nop
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0x60($v1)
		nop
		ori     $v0, 4
		sw      $v0, 0x60($v1)
		lw      $a0, 4($t0)
		nop
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0xD0($a0)
		nop
		ori     $v0, 8
		sw      $v0, 0xD0($a0)
		lw      $v1, 4($t0)
		nop
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0xD0($v1)
		nop
		ori     $v0, 4
		sw      $v0, 0xD0($v1)

		loc_1BA4:                                # CODE XREF : ROM:00001A94↑j
		addiu   $t0, 0x180
		lw      $v0, 0x30($t0)
		nop
		and $v0, $t1
		beqz    $v0, loc_1D50
		lui     $v0, 0
		li      $v0, 0xFFFF8C7C
		lui     $v1, 0x1F
		sw      $v0, 0xC($t0)
		lw      $v0, 0x1EDDD4
		nop
		lw      $a0, 0($v0)
		addiu   $a3, $t0, -0x940
		sw      $a0, 0x10($t0)
		lw      $v0, 0x870($a3)
		nop
		and $v0, $t1
		beqz    $v0, loc_1BFC
		lui     $a0, 0xF3FF
		lhu     $v0, 0x866($a3)
		nop
		sh      $v0, 0x26($t0)

		loc_1BFC:                                # CODE XREF : ROM:00001BE8↑j
		ori     $a0, 0xFFFF
		li      $v0, 0x29E10
		sw      $v0, 0x20($t0)
		li      $v0, 0x18
		sh      $v0, 0x28($t0)
		li      $v0, 0x66  # 'f'
		sh      $v0, 0x2C($t0)
		lw      $v0, 0x30($t0)
		li      $v1, 0x80
		sh      $v1, 0x2E($t0)
		li      $v1, 0x32  # '2'
		sh      $v1, 0x2A($t0)
		li      $v1, 0x4000
		sw      $v1, 0x38($t0)
		lui     $v1, 2
		or $v0, $v1
		and $v0, $a0
		lui     $v1, 0x400
		or $v0, $v1
		li      $a0, 4
		li      $v1, 0x50594
		sw      $v1, 0x34($t0)
		lui     $v1, 0xA
		sw      $v0, 0x30($t0)
		sh      $a0, 0x30($t0)
		lw      $v0, 0x30($t0)
		lw      $a0, 4($t0)
		lw      $a1, 0xA25E4
		or $v0, $t3
		or $v0, $t2
		or $v0, $t5
		or $v0, $t4
		sll     $a0, 2
		addu    $a0, $a1
		sw      $v0, 0x30($t0)
		lw      $v0, 0x60($a0)
		nop
		ori     $v0, 8
		sw      $v0, 0x60($a0)
		lw      $v1, 4($t0)
		nop
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0x60($v1)
		nop
		ori     $v0, 4
		sw      $v0, 0x60($v1)
		lw      $a0, 4($t0)
		nop
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0xD0($a0)
		nop
		ori     $v0, 8
		sw      $v0, 0xD0($a0)
		lw      $v1, 4($t0)
		nop
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0xD0($v1)
		nop
		ori     $v0, 4
		sw      $v0, 0xD0($v1)
		lui     $v1, 0xA
		lh      $a0, 2($t0)
		lh      $v0, 0x6542($a3)
		lw      $a2, 0xA2600
		sll     $a0, 2
		sll     $v0, 2
		addu    $v0, $a2
		lw      $a1, 0x50($v0)
		addu    $a0, $a2
		sw      $a1, 0x54($a0)
		lh      $v1, 2($t0)
		lh      $v0, 0x6542($a3)
		sll     $v1, 2
		sll     $v0, 2
		addu    $v0, $a2
		addu    $v1, $a2
		lw      $a0, 0x68($v0)
		li      $v0, 0x1400
		sw      $a0, 0x6C($v1)
		sh      $v0, 0x24($t0)

		loc_1D50:                                # CODE XREF : ROM:00001BB4↑j
		lui     $v0, 0x1F
		addiu   $t0, $v0, 0x2CC0
		lw      $v1, 0x30($t0)
		lui     $t1, 1
		and $v0, $v1, $t1
		beqz    $v0, loc_1EE4
		lui     $v0, 0xF3FF
		li      $v0, 0xF3FFFFFF
		lui     $a0, 2
		or $a0, $v1, $a0
		and $a0, $v0
		lui     $v1, 0x400
		or $a0, $v1
		li      $v0, 0xFFFF8C7C
		lui     $v1, 0x1F
		sw      $v0, 0xC($t0)
		lui     $v0, 3
		lw      $a1, 0x1EDDD4
		li      $v0, 0x29E10
		lw      $a2, 0($a1)
		li      $v1, 0x80
		sw      $v0, 0x20($t0)
		li      $v0, 0x18
		sh      $v1, 0x2E($t0)
		li      $v1, 0x32  # '2'
		sh      $v0, 0x28($t0)
		li      $v0, 0x66  # 'f'
		sh      $v0, 0x2C($t0)
		li      $v0, 0x4000
		sw      $v0, 0x38($t0)
		li      $v0, 0x50594
		sh      $v1, 0x2A($t0)
		lui     $v1, 0x20  # ' '
		sw      $a0, 0x30($t0)
		sh      $zero, 0x30($t0)
		sw      $v0, 0x34($t0)
		lw      $v0, 0x30($t0)
		lui     $a0, 0x40  # '@'
		or $v0, $v1
		or $v0, $a0
		lui     $v1, 0x10
		or $v0, $v1
		lui     $a0, 8
		or $v0, $a0
		lui     $v1, 0xA
		lw      $a0, 4($t0)
		lw      $a1, 0xA25E4
		sw      $a2, 0x10($t0)
		sw      $v0, 0x30($t0)
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0x60($a0)
		nop
		ori     $v0, 8
		sw      $v0, 0x60($a0)
		lw      $v1, 4($t0)
		nop
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0x60($v1)
		nop
		ori     $v0, 4
		sw      $v0, 0x60($v1)
		lw      $a0, 4($t0)
		nop
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0xD0($a0)
		nop
		ori     $v0, 8
		sw      $v0, 0xD0($a0)
		lw      $v1, 4($t0)
		nop
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0xD0($v1)
		addiu   $a3, $t0, -0x840
		ori     $v0, 4
		sw      $v0, 0xD0($v1)
		lui     $v1, 0xA
		lh      $a0, 2($t0)
		lh      $v0, 0x6542($a3)
		lw      $a2, 0xA2600
		sll     $a0, 2
		sll     $v0, 2
		addu    $v0, $a2
		lw      $a1, 0x50($v0)
		addu    $a0, $a2
		sw      $a1, 0x54($a0)
		lh      $v1, 2($t0)
		lh      $v0, 0x6542($a3)
		sll     $v1, 2
		sll     $v0, 2
		addu    $v0, $a2
		addu    $v1, $a2
		lw      $a0, 0x68($v0)
		li      $v0, 0x1400
		sw      $a0, 0x6C($v1)
		sh      $v0, 0x24($t0)

		loc_1EE4:                                # CODE XREF : ROM:00001D64↑j
		addiu   $t0, 0x80
		lw      $v0, 0x30($t0)
		nop
		and $v0, $t1
		beqz    $v0, loc_20A4
		lui     $v0, 0
		li      $v0, 0xFFFF8C7C
		lui     $v1, 0x1F
		sw      $v0, 0xC($t0)
		lw      $v0, 0x1EDDD4
		nop
		lw      $a0, 0($v0)
		addiu   $v1, $t0, -0x8C0
		sw      $a0, 0x10($t0)
		lw      $v0, 0x870($v1)
		nop
		and $v0, $t1
		beqz    $v0, loc_1F3C
		nop
		lhu     $v0, 0x866($v1)
		j       loc_1F40
		sh      $v0, 0x26($t0)
# ---------------------------------------------------------------------------

		loc_1F3C:                                # CODE XREF : ROM:00001F28↑j
		lhu     $v0, 0x966($v1)

		loc_1F40 : # CODE XREF : ROM:00001F34↑j
		nop
		sh      $v0, 0x26($t0)
		li      $a1, 0xF3FFFFFF
		li      $v0, 0x29E10
		li      $v1, 0x80
		sw      $v0, 0x20($t0)
		li      $v0, 0x18
		sh      $v1, 0x2E($t0)
		li      $v1, 0x32  # '2'
		li      $a0, 0x66  # 'f'
		sh      $v0, 0x28($t0)
		lui     $v0, 5
		sh      $v1, 0x2A($t0)
		lw      $v1, 0x30($t0)
		li      $v0, 0x50594
		sw      $v0, 0x34($t0)
		lui     $v0, 2
		sh      $a0, 0x2C($t0)
		lui     $a0, 0x40  # '@'
		or $v1, $v0
		and $v1, $a1
		lui     $v0, 0x400
		or $v1, $v0
		sw      $v1, 0x30($t0)
		sh      $zero, 0x30($t0)
		lw      $v0, 0x30($t0)
		lui     $v1, 0x20  # ' '
		or $v0, $v1
		or $v0, $a0
		lui     $v1, 0x10
		or $v0, $v1
		lui     $a0, 8
		or $v0, $a0
		lui     $v1, 0xA
		lw      $a0, 4($t0)
		lw      $a1, 0xA25E4
		sw      $v0, 0x30($t0)
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0x60($a0)
		nop
		ori     $v0, 8
		sw      $v0, 0x60($a0)
		lw      $v1, 4($t0)
		nop
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0x60($v1)
		nop
		ori     $v0, 4
		sw      $v0, 0x60($v1)
		lw      $a0, 4($t0)
		nop
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0xD0($a0)
		nop
		ori     $v0, 8
		sw      $v0, 0xD0($a0)
		lw      $v1, 4($t0)
		nop
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0xD0($v1)
		addiu   $a3, $t6, 0x2480
		ori     $v0, 4
		sw      $v0, 0xD0($v1)
		lui     $v1, 0xA
		lh      $a0, 2($t0)
		lh      $v0, 0x6542($a3)
		lw      $a2, 0xA2600
		sll     $a0, 2
		sll     $v0, 2
		addu    $v0, $a2
		lw      $a1, 0x50($v0)
		addu    $a0, $a2
		sw      $a1, 0x54($a0)
		lh      $v1, 2($t0)
		lh      $v0, 0x6542($a3)
		sll     $v1, 2
		sll     $v0, 2
		addu    $v0, $a2
		addu    $v1, $a2
		lw      $a0, 0x68($v0)
		li      $v0, 0x1400
		sw      $a0, 0x6C($v1)
		sh      $v0, 0x24($t0)

		loc_20A4:                                # CODE XREF : ROM:00001EF4↑j
		lui     $v1, 0x1F
		addiu   $t0, $v1, 0x30C0
		lw      $v0, 0x30($t0)
		lui     $a1, 1
		and $v0, $a1
		beqz    $v0, loc_2270
		lui     $v0, 0
		li      $v0, 0xFFFF8C7C
		lui     $v1, 0x1F
		sw      $v0, 0xC($t0)
		lw      $v0, 0x1EDDD4
		nop
		lw      $a0, 0($v0)
		addiu   $v1, $t0, -0xC40
		sw      $a0, 0x10($t0)
		lw      $v0, 0x870($v1)
		nop
		and $v0, $a1
		beqz    $v0, loc_2100
		nop
		lhu     $v0, 0x866($v1)
		j       loc_2104
		sh      $v0, 0x26($t0)
# ---------------------------------------------------------------------------

		loc_2100:                                # CODE XREF : ROM:000020EC↑j
		lhu     $v0, 0x966($v1)

		loc_2104 : # CODE XREF : ROM:000020F8↑j
		nop
		sh      $v0, 0x26($t0)
		li      $a0, 0xF3FFFFFF
		li      $v0, 0x29E10
		li      $v1, 0x80
		sw      $v0, 0x20($t0)
		li      $v0, 0x18
		sh      $v1, 0x2E($t0)
		li      $v1, 0x32  # '2'
		sh      $v0, 0x28($t0)
		li      $v0, 0x66  # 'f'
		sh      $v1, 0x2A($t0)
		li      $v1, 0x4000
		sh      $v0, 0x2C($t0)
		lui     $v0, 5
		sw      $v1, 0x38($t0)
		lw      $v1, 0x30($t0)
		li      $v0, 0x50594
		sw      $v0, 0x34($t0)
		lui     $v0, 2
		or $v1, $v0
		and $v1, $a0
		lui     $v0, 0x400
		or $v1, $v0
		sw      $v1, 0x30($t0)
		lui     $v1, 0x20  # ' '
		sh      $zero, 0x30($t0)
		lw      $v0, 0x30($t0)
		lui     $a0, 0x40  # '@'
		or $v0, $v1
		or $v0, $a0
		lui     $v1, 0x10
		or $v0, $v1
		lui     $a0, 8
		or $v0, $a0
		lui     $v1, 0xA
		lw      $a0, 4($t0)
		lw      $a1, 0xA25E4
		sw      $v0, 0x30($t0)
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0x60($a0)
		nop
		ori     $v0, 8
		sw      $v0, 0x60($a0)
		lw      $v1, 4($t0)
		nop
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0x60($v1)
		nop
		ori     $v0, 4
		sw      $v0, 0x60($v1)
		lw      $a0, 4($t0)
		nop
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0xD0($a0)
		nop
		ori     $v0, 8
		sw      $v0, 0xD0($a0)
		lw      $v1, 4($t0)
		nop
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0xD0($v1)
		addiu   $a3, $t6, 0x2480
		ori     $v0, 4
		sw      $v0, 0xD0($v1)
		lui     $v1, 0xA
		lh      $a0, 2($t0)
		lh      $v0, 0x6542($a3)
		lw      $a2, 0xA2600
		sll     $a0, 2
		sll     $v0, 2
		addu    $v0, $a2
		lw      $a1, 0x50($v0)
		addu    $a0, $a2
		sw      $a1, 0x54($a0)
		lh      $v1, 2($t0)
		lh      $v0, 0x6542($a3)
		sll     $v1, 2
		sll     $v0, 2
		addu    $v0, $a2
		addu    $v1, $a2
		lw      $a0, 0x68($v0)
		li      $v0, 0x1400
		sw      $a0, 0x6C($v1)
		sh      $v0, 0x24($t0)

		loc_2270:                                # CODE XREF : ROM:000020B8↑j
		lui     $v1, 0x1F
		addiu   $t0, $v1, 0x35C0
		lw      $v0, 0x30($t0)
		lui     $a1, 1
		and $v0, $a1
		beqz    $v0, loc_2428
		lui     $v0, 0
		li      $v0, 0xFFFF8C7C
		lui     $v1, 0x1F
		sw      $v0, 0xC($t0)
		lw      $v0, 0x1EDDD4
		nop
		lw      $a0, 0($v0)
		addiu   $v1, $t0, -0x1140
		sw      $a0, 0x10($t0)
		lw      $v0, 0x870($v1)
		nop
		and $v0, $a1
		beqz    $v0, loc_22CC
		nop
		lhu     $v0, 0x866($v1)
		j       loc_22D0
		sh      $v0, 0x26($t0)
# ---------------------------------------------------------------------------

		loc_22CC:                                # CODE XREF : ROM:000022B8↑j
		lhu     $v0, 0x966($v1)

		loc_22D0 : # CODE XREF : ROM:000022C4↑j
		nop
		sh      $v0, 0x26($t0)
		li      $a1, 0xF3FFFFFF
		li      $v0, 0x29E10
		li      $v1, 0x80
		sw      $v0, 0x20($t0)
		li      $v0, 0x18
		sh      $v1, 0x2E($t0)
		li      $v1, 0x32  # '2'
		sh      $v0, 0x28($t0)
		lw      $v0, 0x30($t0)
		li      $a0, 0x66  # 'f'
		sh      $v1, 0x2A($t0)
		lui     $v1, 2
		sh      $a0, 0x2C($t0)
		lui     $a0, 0x40  # '@'
		or $v0, $v1
		and $v0, $a1
		lui     $v1, 0x400
		or $v0, $v1
		sw      $v0, 0x30($t0)
		sh      $zero, 0x30($t0)
		lw      $v0, 0x30($t0)
		lui     $v1, 0x20  # ' '
		or $v0, $v1
		or $v0, $a0
		lui     $v1, 0x10
		or $v0, $v1
		lui     $a0, 8
		or $v0, $a0
		lui     $v1, 0xA
		lw      $a0, 4($t0)
		lw      $a1, 0xA25E4
		sw      $v0, 0x30($t0)
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0x60($a0)
		nop
		ori     $v0, 8
		sw      $v0, 0x60($a0)
		lw      $v1, 4($t0)
		nop
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0x60($v1)
		nop
		ori     $v0, 4
		sw      $v0, 0x60($v1)
		lw      $a0, 4($t0)
		nop
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0xD0($a0)
		nop
		ori     $v0, 8
		sw      $v0, 0xD0($a0)
		lw      $v1, 4($t0)
		nop
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0xD0($v1)
		addiu   $a3, $t6, 0x2480
		ori     $v0, 4
		sw      $v0, 0xD0($v1)
		lui     $v1, 0xA
		lh      $a0, 2($t0)
		lh      $v0, 0x6542($a3)
		lw      $a2, 0xA2600
		sll     $a0, 2
		sll     $v0, 2
		addu    $v0, $a2
		lw      $a1, 0x50($v0)
		addu    $a0, $a2
		sw      $a1, 0x54($a0)
		lh      $v1, 2($t0)
		lh      $v0, 0x6542($a3)
		sll     $v1, 2
		sll     $v0, 2
		addu    $v0, $a2
		addu    $v1, $a2
		lw      $a0, 0x68($v0)
		li      $v0, 0x1400
		sw      $a0, 0x6C($v1)
		sh      $v0, 0x24($t0)

		loc_2428:                                # CODE XREF : ROM:00002284↑j
		lui     $v1, 0x1F
		addiu   $t0, $v1, 0x3240
		lw      $v0, 0x30($t0)
		lui     $a1, 1
		and $v0, $a1
		beqz    $v0, loc_25F8
		lui     $v0, 0
		li      $v0, 0xFFFF8C7C
		lui     $v1, 0x1F
		sw      $v0, 0xC($t0)
		lw      $v0, 0x1EDDD4
		nop
		lw      $a0, 0($v0)
		addiu   $v1, $t0, -0xDC0
		sw      $a0, 0x10($t0)
		lw      $v0, 0x870($v1)
		nop
		and $v0, $a1
		beqz    $v0, loc_2484
		nop
		lhu     $v0, 0x866($v1)
		j       loc_2488
		sh      $v0, 0x26($t0)
# ---------------------------------------------------------------------------

		loc_2484:                                # CODE XREF : ROM:00002470↑j
		lhu     $v0, 0x966($v1)

		loc_2488 : # CODE XREF : ROM:0000247C↑j
		nop
		sh      $v0, 0x26($t0)
		li      $a0, 0xF3FFFFFF
		li      $v0, 0x29E10
		li      $v1, 0x80
		sw      $v0, 0x20($t0)
		li      $v0, 0x18
		sh      $v1, 0x2E($t0)
		li      $v1, 0x32  # '2'
		sh      $v0, 0x28($t0)
		li      $v0, 0x66  # 'f'
		sh      $v1, 0x2A($t0)
		li      $v1, 0x4000
		sh      $v0, 0x2C($t0)
		lui     $v0, 5
		sw      $v1, 0x38($t0)
		lw      $v1, 0x30($t0)
		li      $v0, 0x50594
		sw      $v0, 0x34($t0)
		lui     $v0, 2
		or $v1, $v0
		and $v1, $a0
		lui     $v0, 0x400
		or $v1, $v0
		li      $a0, 4
		sw      $v1, 0x30($t0)
		lui     $v1, 0x20  # ' '
		sh      $a0, 0x30($t0)
		lw      $v0, 0x30($t0)
		lui     $a0, 0x40  # '@'
		or $v0, $v1
		or $v0, $a0
		lui     $v1, 0x10
		or $v0, $v1
		lui     $a0, 8
		or $v0, $a0
		lui     $v1, 0xA
		lw      $a0, 4($t0)
		lw      $a1, 0xA25E4
		sw      $v0, 0x30($t0)
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0x60($a0)
		nop
		ori     $v0, 8
		sw      $v0, 0x60($a0)
		lw      $v1, 4($t0)
		nop
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0x60($v1)
		nop
		ori     $v0, 4
		sw      $v0, 0x60($v1)
		lw      $a0, 4($t0)
		nop
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0xD0($a0)
		nop
		ori     $v0, 8
		sw      $v0, 0xD0($a0)
		lw      $v1, 4($t0)
		nop
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0xD0($v1)
		addiu   $a3, $t6, 0x2480
		ori     $v0, 4
		sw      $v0, 0xD0($v1)
		lui     $v1, 0xA
		lh      $a0, 2($t0)
		lh      $v0, 0x6542($a3)
		lw      $a2, 0xA2600
		sll     $a0, 2
		sll     $v0, 2
		addu    $v0, $a2
		lw      $a1, 0x50($v0)
		addu    $a0, $a2
		sw      $a1, 0x54($a0)
		lh      $v1, 2($t0)
		lh      $v0, 0x6542($a3)
		sll     $v1, 2
		sll     $v0, 2
		addu    $v0, $a2
		addu    $v1, $a2
		lw      $a0, 0x68($v0)
		li      $v0, 0x1400
		sw      $a0, 0x6C($v1)
		sh      $v0, 0x24($t0)

		loc_25F8:                                # CODE XREF : ROM:0000243C↑j
		lui     $v1, 0x1F
		addiu   $t0, $v1, 0x3280
		li      $v0, 0x4F154
		lui     $a1, 0x20  # ' '
		lw      $v1, 0x30($t0)
		addiu   $a2, $t0, -0xE00
		sw      $v0, 0x10($t0)
		or $v1, $a1
		sw      $v1, 0x30($t0)
		addiu   $t0, -0xC0
		lw      $v0, 0x830($a2)
		lw      $v1, 0x8B0($a2)
		or $v0, $a1
		sw      $v0, 0x830($a2)
		lw      $v0, 0x930($a2)
		or $v1, $a1
		sw      $v1, 0x8B0($a2)
		lw      $v1, 0x9B0($a2)
		or $v0, $a1
		sw      $v0, 0x930($a2)
		lw      $v0, 0xA30($a2)
		or $v1, $a1
		sw      $v1, 0x9B0($a2)
		lw      $v1, 0xAB0($a2)
		or $v0, $a1
		sw      $v0, 0xA30($a2)
		lw      $v0, 0xB30($a2)
		or $v1, $a1
		sw      $v1, 0xAB0($a2)
		lw      $v1, 0xBB0($a2)
		or $v0, $a1
		sw      $v0, 0xB30($a2)
		lw      $v0, 0xC30($a2)
		or $v1, $a1
		sw      $v1, 0xBB0($a2)
		lw      $v1, 0xCB0($a2)
		or $v0, $a1
		sw      $v0, 0xC30($a2)
		lw      $v0, 0xD30($a2)
		or $v1, $a1
		sw      $v1, 0xCB0($a2)
		lw      $v1, 0xDB0($a2)
		or $v0, $a1
		sw      $v0, 0xD30($a2)
		lw      $v0, 0xE30($a2)
		or $v1, $a1
		sw      $v1, 0xDB0($a2)
		lw      $v1, 0xEB0($a2)
		or $v0, $a1
		sw      $v0, 0xE30($a2)
		lw      $v0, 0xF30($a2)
		or $v1, $a1
		sw      $v1, 0xEB0($a2)
		lw      $v1, 0xFB0($a2)
		or $v0, $a1
		or $v1, $a1
		sw      $v0, 0xF30($a2)
		sw      $v1, 0xFB0($a2)
		lw      $v0, 0x1030($a2)
		lw      $v1, 0x10B0($a2)
		lw      $a0, 0x1130($a2)
		or $v0, $a1
		sw      $v0, 0x1030($a2)
		lw      $v0, 0x11B0($a2)
		or $v1, $a1
		sw      $v1, 0x10B0($a2)
		lw      $v1, 0x1230($a2)
		or $a0, $a1
		sw      $a0, 0x1130($a2)
		or $v0, $a1
		sw      $v0, 0x11B0($a2)
		lw      $v0, 0x12B0($a2)
		or $v1, $a1
		sw      $v1, 0x1230($a2)
		lw      $v1, 0x1330($a2)
		or $v0, $a1
		sw      $v0, 0x12B0($a2)
		lw      $v0, 0x13B0($a2)
		or $v1, $a1
		sw      $v1, 0x1330($a2)
		lw      $v1, 0x1430($a2)
		or $v0, $a1
		sw      $v0, 0x13B0($a2)
		lw      $v0, 0x14B0($a2)
		or $v1, $a1
		sw      $v1, 0x1430($a2)
		lw      $v1, 0x1530($a2)
		or $v0, $a1
		sw      $v0, 0x14B0($a2)
		lw      $v0, 0x15B0($a2)
		or $v1, $a1
		sw      $v1, 0x1530($a2)
		lw      $v1, 0x1630($a2)
		or $v0, $a1
		sw      $v0, 0x15B0($a2)
		lw      $v0, 0x16B0($a2)
		or $v1, $a1
		sw      $v1, 0x1630($a2)
		lw      $v1, 0x1730($a2)
		or $v0, $a1
		or $v1, $a1
		sw      $v0, 0x16B0($a2)
		sw      $v1, 0x1730($a2)
		lw      $v0, 0x30($t0)
		lui     $a1, 1
		and $v0, $a1
		beqz    $v0, loc_28FC
		lui     $v0, 0
		li      $v0, 0xFFFF8C7C
		lui     $v1, 0x1F
		sw      $v0, 0xC($t0)
		lw      $v0, 0x1EDDD4
		nop
		lw      $a0, 0($v0)
		nop
		sw      $a0, 0x10($t0)
		lw      $v0, 0x870($a2)
		nop
		and $v0, $a1
		beqz    $v0, loc_27EC
		nop
		lhu     $v0, 0x866($a2)
		j       loc_27F0
		sh      $v0, 0x26($t0)
# ---------------------------------------------------------------------------

		loc_27EC:                                # CODE XREF : ROM:000027D8↑j
		lhu     $v0, 0x966($a2)

		loc_27F0 : # CODE XREF : ROM:000027E4↑j
		nop
		sh      $v0, 0x26($t0)
		li      $a1, 0xF3FFFFFF
		li      $v0, 0x29E10
		li      $v1, 0x80
		sw      $v0, 0x20($t0)
		li      $v0, 0x18
		sh      $v1, 0x2E($t0)
		li      $v1, 0x32  # '2'
		sh      $v0, 0x28($t0)
		lw      $v0, 0x30($t0)
		li      $a0, 0x66  # 'f'
		sh      $v1, 0x2A($t0)
		lui     $v1, 2
		sh      $a0, 0x2C($t0)
		lui     $a0, 0x40  # '@'
		or $v0, $v1
		and $v0, $a1
		lui     $v1, 0x400
		or $v0, $v1
		sw      $v0, 0x30($t0)
		sh      $zero, 0x30($t0)
		lw      $v0, 0x30($t0)
		lui     $v1, 0x20  # ' '
		or $v0, $v1
		or $v0, $a0
		lui     $v1, 0x10
		or $v0, $v1
		lui     $a0, 8
		or $v0, $a0
		lui     $v1, 0xA
		lw      $a0, 4($t0)
		lw      $a1, 0xA25E4
		sw      $v0, 0x30($t0)
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0x60($a0)
		nop
		ori     $v0, 8
		sw      $v0, 0x60($a0)
		lw      $v1, 4($t0)
		nop
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0x60($v1)
		nop
		ori     $v0, 4
		sw      $v0, 0x60($v1)
		lw      $a0, 4($t0)
		nop
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0xD0($a0)
		nop
		ori     $v0, 8
		sw      $v0, 0xD0($a0)
		lw      $v1, 4($t0)
		nop
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0xD0($v1)
		li      $a0, 0x1400
		ori     $v0, 4
		sw      $v0, 0xD0($v1)
		sh      $a0, 0x24($t0)

		loc_28FC:                                # CODE XREF : ROM:000027A4↑j
		lui     $v0, 0x1F
		addiu   $t0, $v0, 0x38C0
		lw      $a3, 0x30($t0)
		lui     $t1, 1
		and $v0, $a3, $t1
		beqz    $v0, loc_29FC
		lui     $v1, 0x1F
		li      $v1, 0x1EDDC0
		lw      $v0, 0x9C($v1)
		nop
		lw      $a0, 0($v0)
		li      $v0, 0x29E10
		sw      $a0, 0xC($t0)
		lw      $a1, 0x9C($v1)
		li      $v1, 0x80
		lw      $a2, 4($a1)
		li      $a0, 0x200
		sw      $v0, 0x20($t0)
		li      $v0, 0x64  # 'd'
		sh      $v1, 0x2E($t0)
		li      $v1, 0xC8
		sh      $v0, 0x28($t0)
		lui     $v0, 2
		or $v0, $a3, $v0
		sh      $v1, 0x2A($t0)
		lui     $v1, 0x1000
		or $v0, $v1
		sh      $a0, 0x2C($t0)
		lui     $a0, 0xC00
		or $v0, $a0
		lui     $v1, 0x100
		sw      $v0, 0x30($t0)
		sh      $zero, 0x30($t0)
		lw      $v0, 0x30($t0)
		lui     $a0, 0x20  # ' '
		or $v0, $v1
		or $v0, $a0
		lui     $v1, 0x40  # '@'
		or $v0, $v1
		lui     $a0, 0x10
		or $v0, $a0
		lui     $v1, 8
		or $v0, $v1
		lui     $v1, 0xA
		lw      $a0, 4($t0)
		lw      $a1, 0xA25E4
		sw      $a2, 0x10($t0)
		sw      $v0, 0x30($t0)
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0($a0)
		nop
		ori     $v0, 4
		sw      $v0, 0($a0)
		lw      $v1, 4($t0)
		nop
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0x10($v1)
		li      $a0, 0x1C00
		ori     $v0, 4
		sw      $v0, 0x10($v1)
		sh      $a0, 0x24($t0)

		loc_29FC:                                # CODE XREF : ROM:00002910↑j
		addiu   $t0, -0x600
		lw      $v1, 0x30($t0)
		nop
		and $v0, $v1, $t1
		beqz    $v0, loc_2AF0
		lui     $v0, 0xF3FF
		li      $v0, 0xF3FFFFFF
		lui     $a0, 2
		or $a0, $v1, $a0
		and $a0, $v0
		li      $v1, 0x1EDDC0
		lui     $a1, 0x400
		lw      $v0, 0x48($v1)
		or $a0, $a1
		lw      $a2, 0($v0)
		lui     $v0, 3
		sw      $a2, 0xC($t0)
		lw      $a1, 0x48($v1)
		li      $v0, 0x29E10
		lw      $a2, 4($a1)
		li      $v1, 0x80
		sw      $v0, 0x20($t0)
		li      $v0, 0x28  # '('
		sh      $v1, 0x2E($t0)
		li      $v1, 0x32  # '2'
		sh      $v0, 0x28($t0)
		li      $v0, 0x155
		sh      $v1, 0x2A($t0)
		lui     $v1, 0x20  # ' '
		sh      $v0, 0x2C($t0)
		sw      $a0, 0x30($t0)
		sh      $zero, 0x30($t0)
		lw      $v0, 0x30($t0)
		lui     $a0, 0x40  # '@'
		or $v0, $v1
		or $v0, $a0
		lui     $v1, 0x10
		or $v0, $v1
		lui     $a0, 8
		or $v0, $a0
		lui     $v1, 0xA
		lw      $a0, 4($t0)
		lw      $a1, 0xA25E4
		sw      $a2, 0x10($t0)
		sw      $v0, 0x30($t0)
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0x60($a0)
		nop
		ori     $v0, 8
		sw      $v0, 0x60($a0)
		lw      $v1, 4($t0)
		nop
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0x130($v1)
		li      $a0, 0x1400
		ori     $v0, 8
		sw      $v0, 0x130($v1)
		sh      $a0, 0x24($t0)

		loc_2AF0:                                # CODE XREF : ROM:00002A0C↑j
		addiu   $t0, -0x400
		lw      $v1, 0x30($t0)
		nop
		and $v0, $v1, $t1
		beqz    $v0, loc_2BC4
		lui     $v0, 0xF3FF
		li      $v0, 0xF3FFFFFF
		lui     $a0, 2
		or $a0, $v1, $a0
		and $a0, $v0
		li      $v1, 0x1EDDC0
		lui     $a1, 0x400
		lw      $v0, 0x58($v1)
		or $a0, $a1
		lw      $a2, 0($v0)
		lui     $v0, 3
		sw      $a2, 0xC($t0)
		lw      $a1, 0x58($v1)
		li      $v0, 0x29E10
		lw      $a2, 4($a1)
		li      $v1, 0x80
		sw      $v0, 0x20($t0)
		li      $v0, 0x12
		sh      $v1, 0x2E($t0)
		li      $v1, 0x32  # '2'
		sh      $v0, 0x28($t0)
		li      $v0, 0x100
		sh      $v1, 0x2A($t0)
		lui     $v1, 0x20  # ' '
		sh      $v0, 0x2C($t0)
		sw      $a0, 0x30($t0)
		sh      $zero, 0x30($t0)
		lw      $v0, 0x30($t0)
		lui     $a0, 0x40  # '@'
		or $v0, $v1
		or $v0, $a0
		lui     $v1, 0x10
		or $v0, $v1
		lui     $a0, 8
		or $v0, $a0
		lui     $a0, 0xA
		lw      $v1, 4($t0)
		lw      $a1, 0xA25E4
		sw      $a2, 0x10($t0)
		sw      $v0, 0x30($t0)
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0x130($v1)
		li      $a0, 0x1400
		ori     $v0, 8
		sw      $v0, 0x130($v1)
		sh      $a0, 0x24($t0)

		loc_2BC4:                                # CODE XREF : ROM:00002B00↑j
		addiu   $t0, 0xB00
		lw      $v1, 0x30($t0)
		nop
		and $v0, $v1, $t1
		beqz    $v0, loc_2C98
		lui     $v0, 0xF3FF
		li      $v0, 0xF3FFFFFF
		lui     $a0, 2
		or $a0, $v1, $a0
		and $a0, $v0
		li      $v1, 0x1EDDC0
		lui     $a1, 0x400
		lw      $v0, 0x5C($v1)
		or $a0, $a1
		lw      $a2, 0($v0)
		lui     $v0, 3
		sw      $a2, 0xC($t0)
		lw      $a1, 0x5C($v1)
		li      $v0, 0x29E10
		lw      $a2, 4($a1)
		li      $v1, 0x80
		sw      $v0, 0x20($t0)
		li      $v0, 0x18
		sh      $v1, 0x2E($t0)
		li      $v1, 0x32  # '2'
		sh      $v0, 0x28($t0)
		li      $v0, 0x100
		sh      $v1, 0x2A($t0)
		lui     $v1, 0x20  # ' '
		sh      $v0, 0x2C($t0)
		sw      $a0, 0x30($t0)
		sh      $zero, 0x30($t0)
		lw      $v0, 0x30($t0)
		lui     $a0, 0x40  # '@'
		or $v0, $v1
		or $v0, $a0
		lui     $v1, 0x10
		or $v0, $v1
		lui     $a0, 8
		or $v0, $a0
		lui     $a0, 0xA
		lw      $v1, 4($t0)
		lw      $a1, 0xA25E4
		sw      $a2, 0x10($t0)
		sw      $v0, 0x30($t0)
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0x130($v1)
		li      $a0, 0x1400
		ori     $v0, 8
		sw      $v0, 0x130($v1)
		sh      $a0, 0x24($t0)

		loc_2C98:                                # CODE XREF : ROM:00002BD4↑j
		addiu   $t0, -0xA80
		lw      $v1, 0x30($t0)
		nop
		and $v0, $v1, $t1
		beqz    $v0, loc_2D6C
		lui     $v0, 0xF3FF
		li      $v0, 0xF3FFFFFF
		lui     $a0, 2
		or $a0, $v1, $a0
		and $a0, $v0
		li      $v1, 0x1EDDC0
		lui     $a1, 0x400
		lw      $v0, 0x40($v1)
		or $a0, $a1
		lw      $a2, 0($v0)
		lui     $v0, 3
		sw      $a2, 0xC($t0)
		lw      $a1, 0x40($v1)
		li      $v0, 0x29E10
		lw      $a2, 4($a1)
		li      $v1, 0x80
		sw      $v0, 0x20($t0)
		li      $v0, 0xA
		sh      $v1, 0x2E($t0)
		li      $v1, 0x32  # '2'
		sh      $v0, 0x28($t0)
		li      $v0, 0x66  # 'f'
		sh      $v1, 0x2A($t0)
		lui     $v1, 0x20  # ' '
		sh      $v0, 0x2C($t0)
		sw      $a0, 0x30($t0)
		sh      $zero, 0x30($t0)
		lw      $v0, 0x30($t0)
		lui     $a0, 0x40  # '@'
		or $v0, $v1
		or $v0, $a0
		lui     $v1, 0x10
		or $v0, $v1
		lui     $a0, 8
		or $v0, $a0
		lui     $a0, 0xA
		lw      $v1, 4($t0)
		lw      $a1, 0xA25E4
		sw      $a2, 0x10($t0)
		sw      $v0, 0x30($t0)
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0x130($v1)
		li      $a0, 0x1400
		ori     $v0, 8
		sw      $v0, 0x130($v1)
		sh      $a0, 0x24($t0)

		loc_2D6C:                                # CODE XREF : ROM:00002CA8↑j
		addiu   $t0, 0x800
		lw      $v1, 0x30($t0)
		nop
		and $v0, $v1, $t1
		beqz    $v0, loc_2E28
		lui     $v0, 0xF3FF
		li      $v0, 0xF3FFFFFF
		lui     $a0, 2
		or $a0, $v1, $a0
		and $a0, $v0
		li      $v1, 0x1EDDC0
		lui     $a1, 0x400
		lw      $v0, 0x9C($v1)
		or $a0, $a1
		lw      $a2, 0x14($v0)
		lui     $v0, 3
		sw      $a2, 0xC($t0)
		lw      $a1, 0x9C($v1)
		li      $v0, 0x29E10
		lw      $a2, 0x18($a1)
		li      $v1, 0x80
		sw      $v0, 0x20($t0)
		li      $v0, 0xA
		sh      $v1, 0x2E($t0)
		li      $v1, 0x32  # '2'
		sh      $v0, 0x28($t0)
		li      $v0, 0x66  # 'f'
		sh      $v0, 0x2C($t0)
		li      $v0, 0x1400
		sh      $v1, 0x2A($t0)
		lui     $v1, 0x100
		sw      $a0, 0x30($t0)
		sh      $zero, 0x30($t0)
		sh      $v0, 0x24($t0)
		lw      $v0, 0x30($t0)
		lui     $a0, 0x20  # ' '
		or $v0, $v1
		or $v0, $a0
		lui     $v1, 0x40  # '@'
		or $v0, $v1
		lui     $a0, 0x10
		or $v0, $a0
		lui     $v1, 8
		or $v0, $v1
		sw      $a2, 0x10($t0)
		sw      $v0, 0x30($t0)

		loc_2E28:                                # CODE XREF : ROM:00002D7C↑j
		addiu   $t0, -0x600
		lw      $v1, 0x30($t0)
		nop
		and $v0, $v1, $t1
		beqz    $v0, loc_2FE0
		lui     $v0, 0xF3FF
		li      $v0, 0xF3FFFFFF
		lui     $a0, 2
		or $a0, $v1, $a0
		and $a0, $v0
		li      $v1, 0x1EDDC0
		lui     $a1, 0x400
		lw      $v0, 0x60($v1)
		or $a0, $a1
		lw      $a2, 0($v0)
		lui     $v0, 3
		sw      $a2, 0xC($t0)
		lw      $a1, 0x60($v1)
		li      $v0, 0x29E10
		lw      $a2, 4($a1)
		li      $v1, 0x80
		sw      $v0, 0x20($t0)
		li      $v0, 0x1A
		sh      $v1, 0x2E($t0)
		li      $v1, 0x32  # '2'
		sh      $v0, 0x28($t0)
		li      $v0, 0x66  # 'f'
		sh      $v0, 0x2C($t0)
		li      $v0, 0x4000
		sh      $v1, 0x2A($t0)
		li      $v1, 7
		sw      $v0, 0x38($t0)
		li      $v0, 0x50594
		sw      $a0, 0x30($t0)
		sh      $v1, 0x30($t0)
		lui     $v1, 0x20  # ' '
		sw      $v0, 0x34($t0)
		lw      $v0, 0x30($t0)
		lui     $a0, 0x40  # '@'
		or $v0, $v1
		or $v0, $a0
		lui     $v1, 0x10
		or $v0, $v1
		lui     $a0, 8
		or $v0, $a0
		lui     $v1, 0xA
		lw      $a0, 4($t0)
		lw      $a1, 0xA25E4
		sw      $a2, 0x10($t0)
		sw      $v0, 0x30($t0)
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0x60($a0)
		nop
		ori     $v0, 8
		sw      $v0, 0x60($a0)
		lw      $v1, 4($t0)
		nop
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0x60($v1)
		nop
		ori     $v0, 4
		sw      $v0, 0x60($v1)
		lw      $a0, 4($t0)
		nop
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0xD0($a0)
		nop
		ori     $v0, 8
		sw      $v0, 0xD0($a0)
		lw      $v1, 4($t0)
		nop
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0xD0($v1)
		addiu   $a3, $t0, -0xCC0
		ori     $v0, 4
		sw      $v0, 0xD0($v1)
		lui     $v1, 0xA
		lh      $a0, 2($t0)
		lh      $v0, 0x6582($a3)
		lw      $a2, 0xA2600
		sll     $a0, 2
		sll     $v0, 2
		addu    $v0, $a2
		lw      $a1, 0x38($v0)
		addu    $a0, $a2
		sw      $a1, 0x3C($a0)
		lh      $v1, 2($t0)
		lh      $v0, 0x6582($a3)
		sll     $v1, 2
		sll     $v0, 2
		addu    $v0, $a2
		lw      $a1, 0x50($v0)
		addu    $v1, $a2
		sw      $a1, 0x54($v1)
		lh      $a0, 2($t0)
		lh      $v0, 0x6582($a3)
		sll     $a0, 2
		sll     $v0, 2
		addu    $v0, $a2
		addu    $a0, $a2
		lw      $v1, 0x68($v0)
		li      $v0, 0x1400
		sw      $v1, 0x6C($a0)
		sh      $v0, 0x24($t0)

		loc_2FE0:                                # CODE XREF : ROM:00002E38↑j
		addiu   $t0, -0x100
		lw      $v1, 0x30($t0)
		nop
		and $v0, $v1, $t1
		beqz    $v0, loc_3124
		lui     $v0, 0xF3FF
		li      $v0, 0xF3FFFFFF
		lui     $a0, 2
		or $a0, $v1, $a0
		and $a0, $v0
		li      $v1, 0x1EDDC0
		lui     $a1, 0x400
		lw      $v0, 0x3C($v1)
		or $a0, $a1
		lw      $a2, 0($v0)
		lui     $v0, 3
		sw      $a2, 0xC($t0)
		lw      $a1, 0x3C($v1)
		li      $v0, 0x29E10
		lw      $a2, 4($a1)
		li      $v1, 0x80
		sw      $v0, 0x20($t0)
		li      $v0, 0x3C  # '<'
		sh      $v1, 0x2E($t0)
		li      $v1, 0x32  # '2'
		sh      $v0, 0x28($t0)
		li      $v0, 0x66  # 'f'
		sh      $v1, 0x2A($t0)
		li      $v1, 1
		sh      $v0, 0x2C($t0)
		li      $v0, 0x50594
		sw      $a0, 0x30($t0)
		sh      $v1, 0x30($t0)
		lui     $v1, 0x20  # ' '
		sw      $v0, 0x34($t0)
		lw      $v0, 0x30($t0)
		lui     $a0, 0x40  # '@'
		or $v0, $v1
		or $v0, $a0
		lui     $v1, 0x10
		or $v0, $v1
		lui     $a0, 8
		or $v0, $a0
		lui     $v1, 0xA
		lw      $a0, 4($t0)
		lw      $a1, 0xA25E4
		sw      $a2, 0x10($t0)
		sw      $v0, 0x30($t0)
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0x60($a0)
		nop
		ori     $v0, 8
		sw      $v0, 0x60($a0)
		lw      $v1, 4($t0)
		nop
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0x60($v1)
		nop
		ori     $v0, 4
		sw      $v0, 0x60($v1)
		lw      $a0, 4($t0)
		nop
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0x70($a0)
		nop
		ori     $v0, 8
		sw      $v0, 0x70($a0)
		lw      $v1, 4($t0)
		nop
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0x70($v1)
		li      $a0, 0x1400
		ori     $v0, 4
		sw      $v0, 0x70($v1)
		sh      $a0, 0x24($t0)

		loc_3124:                                # CODE XREF : ROM:00002FF0↑j
		addiu   $t0, -0x80
		lw      $v1, 0x30($t0)
		nop
		and $v0, $v1, $t1
		beqz    $v0, loc_3268
		lui     $v0, 0xF3FF
		li      $v0, 0xF3FFFFFF
		lui     $a0, 2
		or $a0, $v1, $a0
		and $a0, $v0
		li      $v1, 0x1EDDC0
		lui     $a1, 0x400
		lw      $v0, 0x3C($v1)
		or $a0, $a1
		lw      $a2, 0($v0)
		lui     $v0, 3
		sw      $a2, 0xC($t0)
		lw      $a1, 0x3C($v1)
		li      $v0, 0x29E10
		lw      $a2, 4($a1)
		li      $v1, 0x80
		sw      $v0, 0x20($t0)
		li      $v0, 0x3C  # '<'
		sh      $v1, 0x2E($t0)
		li      $v1, 0x32  # '2'
		sh      $v0, 0x28($t0)
		li      $v0, 0x66  # 'f'
		sh      $v1, 0x2A($t0)
		li      $v1, 3
		sh      $v0, 0x2C($t0)
		li      $v0, 0x50594
		sw      $a0, 0x30($t0)
		sh      $v1, 0x30($t0)
		lui     $v1, 0x20  # ' '
		sw      $v0, 0x34($t0)
		lw      $v0, 0x30($t0)
		lui     $a0, 0x40  # '@'
		or $v0, $v1
		or $v0, $a0
		lui     $v1, 0x10
		or $v0, $v1
		lui     $a0, 8
		or $v0, $a0
		lui     $v1, 0xA
		lw      $a0, 4($t0)
		lw      $a1, 0xA25E4
		sw      $a2, 0x10($t0)
		sw      $v0, 0x30($t0)
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0x60($a0)
		nop
		ori     $v0, 8
		sw      $v0, 0x60($a0)
		lw      $v1, 4($t0)
		nop
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0x60($v1)
		nop
		ori     $v0, 4
		sw      $v0, 0x60($v1)
		lw      $a0, 4($t0)
		nop
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0x70($a0)
		nop
		ori     $v0, 8
		sw      $v0, 0x70($a0)
		lw      $v1, 4($t0)
		nop
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0x70($v1)
		li      $a0, 0x1400
		ori     $v0, 4
		sw      $v0, 0x70($v1)
		sh      $a0, 0x24($t0)

		loc_3268:                                # CODE XREF : ROM:00003134↑j
		addiu   $t0, 0x580
		lui     $t4, 0x1F
		lui     $t5, 0x1F
		lw      $a2, 0x30($t0)
		nop
		and $v0, $a2, $t1
		beqz    $v0, loc_33F8
		lui     $t6, 0x1F
		li      $v1, 0x1EDDC0
		lw      $v0, 0x44($v1)
		nop
		lw      $a0, 0($v0)
		lui     $v0, 3
		sw      $a0, 0xC($t0)
		lw      $a1, 0x44($v1)
		li      $v0, 0x29E10
		lw      $a0, 4($a1)
		li      $v1, 0x80
		sw      $v0, 0x20($t0)
		li      $v0, 0x32  # '2'
		sh      $v1, 0x2E($t0)
		li      $v1, 0x66  # 'f'
		sh      $v0, 0x28($t0)
		sh      $v0, 0x2A($t0)
		lui     $v0, 2
		or $v0, $a2, $v0
		sh      $v1, 0x2C($t0)
		lui     $v1, 0xC00
		or $v0, $v1
		li      $v1, 5
		sw      $v0, 0x30($t0)
		li      $v0, 0x50594
		sh      $v1, 0x30($t0)
		sw      $v0, 0x34($t0)
		lw      $v0, 0x30($t0)
		lui     $v1, 0x1000
		or $v0, $v1
		sw      $a0, 0x10($t0)
		lui     $a0, 0x20  # ' '
		or $v0, $a0
		lui     $v1, 0x40  # '@'
		or $v0, $v1
		lui     $a0, 0x10
		or $v0, $a0
		lui     $v1, 8
		or $v0, $v1
		lui     $a0, 0xA
		lw      $v1, 4($t0)
		lw      $a1, 0xA25E4
		sw      $v0, 0x30($t0)
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0x60($v1)
		nop
		ori     $v0, 8
		sw      $v0, 0x60($v1)
		lw      $a0, 4($t0)
		move    $a3, $zero
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0x60($a0)
		addiu   $t3, $t0, -0x10C0
		ori     $v0, 4
		sw      $v0, 0x60($a0)
		lw      $v1, 4($t0)
		lui     $t1, 1
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0xD0($v1)
		lui     $t2, 1
		ori     $v0, 8
		sw      $v0, 0xD0($v1)
		lw      $a0, 4($t0)
		lui     $v1, 0xA
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0xD0($a0)
		lw      $a2, 0xA2600
		ori     $v0, 4
		sw      $v0, 0xD0($a0)

		loc_33B0:                                # CODE XREF : ROM:000033E8↓j
		move    $v0, $t1
		addu    $t1, $t2
		sll     $a1, $a3, 3
		sra     $a3, $v0, 16
		lh      $v1, 2($t0)
		lh      $v0, 0x6542($t3)
		sll     $v1, 2
		addu    $v1, $a2
		sll     $v0, 2
		addu    $v0, $a2
		addu    $v0, $a1, $v0
		addu    $a1, $v1
		lw      $a0, 0($v0)
		slti    $v0, $a3, 0x14
		bnez    $v0, loc_33B0
		sw      $a0, 4($a1)
		li      $v0, 0x1400
		sh      $v0, 0x24($t0)

		loc_33F8:                                # CODE XREF : ROM:00003280↑j
		addiu   $t0, $t4, 0x3940
		lw      $v1, 0x30($t0)
		lui     $v0, 1
		and $v0, $v1, $v0
		beqz    $v0, loc_3544
		lui     $v0, 0xF3FF
		li      $v0, 0xF3FFFFFF
		lui     $a0, 2
		or $a0, $v1, $a0
		and $a0, $v0
		li      $v1, 0x1EDDC0
		lui     $a1, 0x400
		lw      $v0, 0x64($v1)
		or $a0, $a1
		lw      $a2, 0($v0)
		lui     $v0, 3
		sw      $a2, 0xC($t0)
		lw      $a1, 0x64($v1)
		li      $v0, 0x29E10
		lw      $a2, 4($a1)
		li      $v1, 0x80
		sw      $v0, 0x20($t0)
		li      $v0, 0x23  # '#'
		sh      $v1, 0x2E($t0)
		li      $v1, 0x32  # '2'
		sh      $v0, 0x28($t0)
		li      $v0, 0x66  # 'f'
		sh      $v0, 0x2C($t0)
		li      $v0, 0x4000
		sh      $v1, 0x2A($t0)
		li      $v1, 6
		sw      $v0, 0x38($t0)
		li      $v0, 0x50594
		sw      $a0, 0x30($t0)
		sh      $v1, 0x30($t0)
		lui     $v1, 0x20  # ' '
		sw      $v0, 0x34($t0)
		lw      $v0, 0x30($t0)
		lui     $a0, 0x40  # '@'
		or $v0, $v1
		or $v0, $a0
		lui     $v1, 0x10
		or $v0, $v1
		lui     $a0, 8
		or $v0, $a0
		lui     $v1, 0xA
		lw      $a0, 4($t0)
		lw      $a1, 0xA25E4
		sw      $a2, 0x10($t0)
		sw      $v0, 0x30($t0)
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0x60($a0)
		nop
		ori     $v0, 8
		sw      $v0, 0x60($a0)
		lw      $v1, 4($t0)
		nop
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0x60($v1)
		nop
		ori     $v0, 4
		sw      $v0, 0x60($v1)
		lw      $a0, 4($t0)
		nop
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0xD0($a0)
		nop
		ori     $v0, 8
		sw      $v0, 0xD0($a0)
		lw      $v1, 4($t0)
		nop
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0xD0($v1)
		li      $a0, 0x1400
		ori     $v0, 4
		sw      $v0, 0xD0($v1)
		sh      $a0, 0x24($t0)

		loc_3544:                                # CODE XREF : ROM:00003408↑j
		addiu   $t0, 0x100
		lw      $v1, 0x30($t0)
		lui     $v0, 1
		and $v0, $v1, $v0
		beqz    $v0, loc_3678
		lui     $v0, 0xF3FF
		li      $v0, 0xF3FFFFFF
		lui     $a0, 2
		or $a0, $v1, $a0
		and $a0, $v0
		li      $v1, 0x1EDDC0
		lui     $a1, 0x400
		lw      $v0, 0x90($v1)
		or $a0, $a1
		lw      $a2, 0($v0)
		lui     $v0, 3
		sw      $a2, 0xC($t0)
		lw      $a1, 0x90($v1)
		li      $v0, 0x29E10
		lw      $a2, 4($a1)
		li      $v1, 0x80
		sw      $v0, 0x20($t0)
		li      $v0, 0x23  # '#'
		sh      $v1, 0x2E($t0)
		li      $v1, 0x32  # '2'
		sh      $v0, 0x28($t0)
		li      $v0, 0x66  # 'f'
		sh      $v1, 0x2A($t0)
		lui     $v1, 0x20  # ' '
		sh      $v0, 0x2C($t0)
		sw      $a0, 0x30($t0)
		sh      $zero, 0x30($t0)
		lw      $v0, 0x30($t0)
		lui     $a0, 0x40  # '@'
		or $v0, $v1
		or $v0, $a0
		lui     $v1, 0x10
		or $v0, $v1
		lui     $a0, 8
		or $v0, $a0
		lui     $v1, 0xA
		lw      $a0, 4($t0)
		lw      $a1, 0xA25E4
		sw      $a2, 0x10($t0)
		sw      $v0, 0x30($t0)
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0x60($a0)
		nop
		ori     $v0, 8
		sw      $v0, 0x60($a0)
		lw      $v1, 4($t0)
		nop
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0x60($v1)
		nop
		ori     $v0, 4
		sw      $v0, 0x60($v1)
		lw      $a0, 4($t0)
		nop
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0xD0($a0)
		nop
		ori     $v0, 8
		sw      $v0, 0xD0($a0)
		lw      $v1, 4($t0)
		nop
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0xD0($v1)
		li      $a0, 0x1400
		ori     $v0, 4
		sw      $v0, 0xD0($v1)
		sh      $a0, 0x24($t0)

		loc_3678:                                # CODE XREF : ROM:00003554↑j
		addiu   $t0, -0xC00
		lw      $a3, 0x30($t0)
		lui     $v0, 1
		and $v0, $a3, $v0
		beqz    $v0, loc_37DC
		lui     $v1, 0x1F
		li      $v1, 0x1EDDC0
		lw      $v0, 0x1C($v1)
		nop
		lw      $a0, 0($v0)
		li      $v0, 0x29E10
		sw      $a0, 0xC($t0)
		lw      $a1, 0x1C($v1)
		li      $a0, 0x80
		lw      $a2, 4($a1)
		li      $v1, 0x32  # '2'
		sw      $v0, 0x20($t0)
		li      $v0, 0x18
		sh      $v0, 0x28($t0)
		lui     $v0, 2
		or $v0, $a3, $v0
		sh      $v1, 0x2A($t0)
		lui     $v1, 0xC00
		or $v0, $v1
		sw      $v0, 0x30($t0)
		sh      $zero, 0x30($t0)
		lw      $v0, 0x30($t0)
		li      $v1, 4
		sw      $v1, 0x38($t0)
		lui     $v1, 0x1000
		sh      $a0, 0x2E($t0)
		sh      $a0, 0x2C($t0)
		lui     $a0, 0x20  # ' '
		or $v0, $v1
		or $v0, $a0
		lui     $v1, 0x40  # '@'
		or $v0, $v1
		lui     $a0, 0x10
		or $v0, $a0
		lui     $v1, 8
		or $v0, $v1
		lui     $v1, 0xA
		lw      $a0, 4($t0)
		lw      $a1, 0xA25E4
		sw      $a2, 0x10($t0)
		sw      $v0, 0x30($t0)
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0($a0)
		nop
		ori     $v0, 8
		sw      $v0, 0($a0)
		lw      $v1, 4($t0)
		nop
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0($v1)
		nop
		ori     $v0, 4
		sw      $v0, 0($v1)
		lw      $a0, 4($t0)
		nop
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0x10($a0)
		nop
		ori     $v0, 8
		sw      $v0, 0x10($a0)
		lw      $v1, 4($t0)
		nop
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0x10($v1)
		nop
		ori     $v0, 4
		sw      $v0, 0x10($v1)
		lui     $v1, 0xA
		lh      $a0, 2($t0)
		lh      $v0, 0x5B82($t0)
		lw      $a1, 0xA2600
		sll     $a0, 2
		sll     $v0, 2
		addu    $v0, $a1
		addu    $a0, $a1
		lw      $v1, 0x10($v0)
		li      $v0, 0x1400
		sw      $v1, 0x54($a0)
		sh      $v0, 0x24($t0)

		loc_37DC:                                # CODE XREF : ROM:00003688↑j
		addiu   $t0, 0x600
		lw      $a3, 0x30($t0)
		lui     $t1, 1
		and $v0, $a3, $t1
		beqz    $v0, loc_3914
		lui     $v1, 0x1F
		li      $v1, 0x1EDDC0
		lw      $v0, 0x20($v1)
		nop
		lw      $a0, 0($v0)
		li      $v0, 0x29E10
		sw      $a0, 0xC($t0)
		lw      $a1, 0x20($v1)
		li      $v1, 0x80
		lw      $a2, 4($a1)
		li      $a0, 0x66  # 'f'
		sw      $v0, 0x20($t0)
		li      $v0, 0x1E
		sh      $v1, 0x2E($t0)
		li      $v1, 0x32  # '2'
		sh      $v0, 0x28($t0)
		lui     $v0, 2
		or $v0, $a3, $v0
		sh      $v1, 0x2A($t0)
		lui     $v1, 0xC00
		or $v0, $v1
		sh      $a0, 0x2C($t0)
		lui     $a0, 0x1000
		or $v0, $a0
		li      $v1, 0x400
		sw      $v0, 0x30($t0)
		sh      $v1, 0x30($t0)
		lui     $v1, 0x20  # ' '
		lw      $v0, 0x30($t0)
		lui     $a0, 0x40  # '@'
		or $v0, $v1
		or $v0, $a0
		lui     $v1, 0x10
		or $v0, $v1
		lui     $a0, 8
		or $v0, $a0
		lui     $v1, 0xA
		lw      $a0, 4($t0)
		lw      $a1, 0xA25E4
		sw      $a2, 0x10($t0)
		sw      $v0, 0x30($t0)
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0($a0)
		nop
		ori     $v0, 8
		sw      $v0, 0($a0)
		lw      $v1, 4($t0)
		nop
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0x80($v1)
		nop
		ori     $v0, 8
		sw      $v0, 0x80($v1)
		lw      $a0, 4($t0)
		nop
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0x80($a0)
		nop
		ori     $v0, 4
		sw      $v0, 0x80($a0)
		lw      $v1, 4($t0)
		nop
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0x80($v1)
		li      $a0, 0x1400
		ori     $v0, 0x10
		sw      $v0, 0x80($v1)
		sh      $a0, 0x24($t0)

		loc_3914:                                # CODE XREF : ROM:000037EC↑j
		addiu   $t0, 0x680
		lw      $v1, 0x30($t0)
		nop
		and $v0, $v1, $t1
		beqz    $v0, loc_3A78
		lui     $v0, 0xF3FF
		li      $v0, 0xF3FFFFFF
		lui     $a0, 2
		or $a0, $v1, $a0
		and $a0, $v0
		li      $v1, 0x1EDDC0
		lui     $a1, 0x400
		lw      $v0, 0x4C($v1)
		or $a0, $a1
		lw      $a2, 0($v0)
		lui     $v0, 3
		sw      $a2, 0xC($t0)
		lw      $a1, 0x4C($v1)
		li      $v0, 0x29E10
		lw      $a2, 4($a1)
		li      $v1, 0x80
		sw      $v0, 0x20($t0)
		li      $v0, 0xC
		sh      $v1, 0x2E($t0)
		li      $v1, 0x14
		sh      $v0, 0x28($t0)
		li      $v0, 0x66  # 'f'
		sh      $v0, 0x2C($t0)
		li      $v0, 0x100
		sh      $v1, 0x2A($t0)
		lui     $v1, 0x20  # ' '
		sw      $a0, 0x30($t0)
		sh      $v0, 0x30($t0)
		lw      $v0, 0x30($t0)
		lui     $a0, 0x40  # '@'
		or $v0, $v1
		or $v0, $a0
		lui     $v1, 0x10
		or $v0, $v1
		lui     $a0, 8
		or $v0, $a0
		lui     $v1, 0xA
		lw      $a0, 4($t0)
		lw      $a1, 0xA25E4
		sw      $a2, 0x10($t0)
		sw      $v0, 0x30($t0)
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0x40($a0)
		nop
		ori     $v0, 0x10
		sw      $v0, 0x40($a0)
		lw      $v1, 4($t0)
		nop
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0x40($v1)
		nop
		ori     $v0, 4
		sw      $v0, 0x40($v1)
		lw      $a0, 4($t0)
		nop
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0x90($a0)
		nop
		ori     $v0, 0x10
		sw      $v0, 0x90($a0)
		lw      $v1, 4($t0)
		nop
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0x90($v1)
		nop
		ori     $v0, 4
		sw      $v0, 0x90($v1)
		lui     $v1, 0xA
		lh      $a0, 2($t0)
		lh      $v0, 0x4F02($t0)
		lw      $a1, 0xA2600
		sll     $a0, 2
		sll     $v0, 2
		addu    $v0, $a1
		addu    $a0, $a1
		lw      $v1, 0x50($v0)
		li      $v0, 0x1400
		sw      $v1, 0x54($a0)
		sh      $v0, 0x24($t0)

		loc_3A78:                                # CODE XREF : ROM:00003924↑j
		addiu   $t0, -0x480
		lw      $v1, 0x30($t0)
		nop
		and $v0, $v1, $t1
		beqz    $v0, loc_3BB0
		lui     $a0, 0xFDFF
		li      $a0, 0xFDFFFFFF
		li      $a3, 0xF3FFFFFF
		li      $v0, 0x1EDDC0
		and $a0, $v1, $a0
		lui     $v1, 2
		or $a0, $v1
		lw      $a1, 0x68($v0)
		and $a0, $a3
		lw      $a2, 0($a1)
		lui     $a1, 0x400
		or $a0, $a1
		sw      $a2, 0xC($t0)
		lw      $v1, 0x68($v0)
		li      $v0, 0x80
		lw      $a2, 4($v1)
		li      $v1, 0x10
		sh      $v0, 0x2E($t0)
		li      $v0, 0x14
		sh      $v1, 0x28($t0)
		li      $v1, 0x100
		sh      $v1, 0x2C($t0)
		sw      $a0, 0x30($t0)
		sh      $v1, 0x30($t0)
		lui     $v1, 0x20  # ' '
		sh      $v0, 0x2A($t0)
		lw      $v0, 0x30($t0)
		lui     $a0, 0x40  # '@'
		or $v0, $v1
		or $v0, $a0
		lui     $v1, 0x10
		or $v0, $v1
		lui     $a0, 8
		or $v0, $a0
		lui     $v1, 0xA
		lw      $a0, 4($t0)
		lw      $a1, 0xA25E4
		sw      $zero, 0x1C($t0)
		sw      $a2, 0x10($t0)
		sw      $v0, 0x30($t0)
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0x40($a0)
		nop
		ori     $v0, 0x10
		sw      $v0, 0x40($a0)
		lw      $v1, 4($t0)
		nop
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0x40($v1)
		nop
		ori     $v0, 4
		sw      $v0, 0x40($v1)
		lw      $a0, 4($t0)
		nop
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0x90($a0)
		nop
		ori     $v0, 0x10
		sw      $v0, 0x90($a0)
		lw      $v1, 4($t0)
		nop
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0x90($v1)
		li      $a0, 0x1400
		ori     $v0, 4
		sw      $v0, 0x90($v1)
		sh      $a0, 0x24($t0)

		loc_3BB0:                                # CODE XREF : ROM:00003A88↑j
		addiu   $t0, 0x180
		lw      $v1, 0x30($t0)
		nop
		and $v0, $v1, $t1
		beqz    $v0, loc_3CE8
		lui     $v0, 0xF3FF
		li      $v0, 0xF3FFFFFF
		lui     $a0, 2
		or $a0, $v1, $a0
		and $a0, $v0
		li      $v1, 0x1EDDC0
		lui     $a1, 0x400
		lw      $v0, 0x68($v1)
		or $a0, $a1
		lw      $a2, 8($v0)
		lui     $v0, 3
		sw      $a2, 0xC($t0)
		lw      $a1, 0x68($v1)
		li      $v0, 0x29E10
		lw      $a2, 0xC($a1)
		li      $v1, 0x80
		sw      $v0, 0x20($t0)
		li      $v0, 0xFA0
		sh      $v1, 0x2E($t0)
		li      $v1, 0x14
		sh      $v0, 0x28($t0)
		li      $v0, 0x155
		sh      $v0, 0x2C($t0)
		li      $v0, 0x100
		sh      $v1, 0x2A($t0)
		lui     $v1, 0x20  # ' '
		sw      $a0, 0x30($t0)
		sh      $v0, 0x30($t0)
		lw      $v0, 0x30($t0)
		lui     $a0, 0x40  # '@'
		or $v0, $v1
		or $v0, $a0
		lui     $v1, 0x10
		or $v0, $v1
		lui     $a0, 8
		or $v0, $a0
		lui     $v1, 0xA
		lw      $a0, 4($t0)
		lw      $a1, 0xA25E4
		sw      $a2, 0x10($t0)
		sw      $v0, 0x30($t0)
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0x40($a0)
		nop
		ori     $v0, 0x10
		sw      $v0, 0x40($a0)
		lw      $v1, 4($t0)
		nop
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0x40($v1)
		nop
		ori     $v0, 4
		sw      $v0, 0x40($v1)
		lw      $a0, 4($t0)
		nop
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0x90($a0)
		nop
		ori     $v0, 0x10
		sw      $v0, 0x90($a0)
		lw      $v1, 4($t0)
		nop
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0x90($v1)
		li      $a0, 0x1400
		ori     $v0, 4
		sw      $v0, 0x90($v1)
		sh      $a0, 0x24($t0)

		loc_3CE8:                                # CODE XREF : ROM:00003BC0↑j
		addiu   $t0, 0x80
		lw      $v1, 0x30($t0)
		nop
		and $v0, $v1, $t1
		beqz    $v0, loc_3E24
		lui     $v0, 0xF3FF
		li      $v0, 0xF3FFFFFF
		lui     $a0, 2
		or $a0, $v1, $a0
		and $a0, $v0
		li      $v1, 0x1EDDC0
		lui     $a1, 0x400
		lw      $v0, 0x78($v1)
		or $a0, $a1
		lw      $a2, 0($v0)
		lui     $v0, 3
		sw      $a2, 0xC($t0)
		lw      $a1, 0x78($v1)
		li      $v0, 0x29E10
		lw      $a2, 4($a1)
		li      $v1, 0x80
		sw      $v0, 0x20($t0)
		li      $v0, 0x64  # 'd'
		sh      $v1, 0x2E($t0)
		li      $v1, 0x14
		sh      $v0, 0x28($t0)
		li      $v0, 0x100
		sh      $v1, 0x2A($t0)
		lui     $v1, 0x100
		sh      $v0, 0x2C($t0)
		sw      $a0, 0x30($t0)
		sh      $v0, 0x30($t0)
		lw      $v0, 0x30($t0)
		lui     $a0, 0x20  # ' '
		or $v0, $v1
		or $v0, $a0
		lui     $v1, 0x40  # '@'
		or $v0, $v1
		lui     $a0, 0x10
		or $v0, $a0
		lui     $v1, 8
		or $v0, $v1
		lui     $v1, 0xA
		lw      $a0, 4($t0)
		lw      $a1, 0xA25E4
		sw      $a2, 0x10($t0)
		sw      $v0, 0x30($t0)
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0x40($a0)
		nop
		ori     $v0, 0x10
		sw      $v0, 0x40($a0)
		lw      $v1, 4($t0)
		nop
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0x40($v1)
		nop
		ori     $v0, 4
		sw      $v0, 0x40($v1)
		lw      $a0, 4($t0)
		nop
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0x90($a0)
		nop
		ori     $v0, 0x10
		sw      $v0, 0x90($a0)
		lw      $v1, 4($t0)
		nop
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0x90($v1)
		li      $a0, 0x1400
		ori     $v0, 4
		sw      $v0, 0x90($v1)
		sh      $a0, 0x24($t0)

		loc_3E24:                                # CODE XREF : ROM:00003CF8↑j
		addiu   $t0, -0x180
		lw      $v1, 0x30($t0)
		nop
		and $v0, $v1, $t1
		beqz    $v0, loc_3F58
		lui     $v0, 0xF3FF
		li      $v0, 0xF3FFFFFF
		lui     $a0, 2
		or $a0, $v1, $a0
		and $a0, $v0
		li      $v1, 0x1EDDC0
		lui     $a1, 0x400
		lw      $v0, 0x70($v1)
		or $a0, $a1
		lw      $a2, 0($v0)
		lui     $v0, 3
		sw      $a2, 0xC($t0)
		lw      $a1, 0x70($v1)
		li      $v0, 0x29E10
		lw      $a2, 4($a1)
		li      $v1, 0x80
		sw      $v0, 0x20($t0)
		li      $v0, 0x64  # 'd'
		sh      $v1, 0x2E($t0)
		li      $v1, 0x14
		sh      $v0, 0x28($t0)
		li      $v0, 0x100
		sh      $v1, 0x2A($t0)
		lui     $v1, 0x20  # ' '
		sh      $v0, 0x2C($t0)
		sw      $a0, 0x30($t0)
		sh      $v0, 0x30($t0)
		lw      $v0, 0x30($t0)
		lui     $a0, 0x40  # '@'
		or $v0, $v1
		or $v0, $a0
		lui     $v1, 0x10
		or $v0, $v1
		lui     $a0, 8
		or $v0, $a0
		lui     $v1, 0xA
		lw      $a0, 4($t0)
		lw      $a1, 0xA25E4
		sw      $a2, 0x10($t0)
		sw      $v0, 0x30($t0)
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0x60($a0)
		nop
		ori     $v0, 8
		sw      $v0, 0x60($a0)
		lw      $v1, 4($t0)
		nop
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0x60($v1)
		nop
		ori     $v0, 4
		sw      $v0, 0x60($v1)
		lw      $a0, 4($t0)
		nop
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0x80($a0)
		nop
		ori     $v0, 8
		sw      $v0, 0x80($a0)
		lw      $v1, 4($t0)
		nop
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0x80($v1)
		li      $a0, 0x1400
		ori     $v0, 4
		sw      $v0, 0x80($v1)
		sh      $a0, 0x24($t0)

		loc_3F58:                                # CODE XREF : ROM:00003E34↑j
		addiu   $t0, 0x540
		lw      $v1, 0x30($t0)
		nop
		and $v0, $v1, $t1
		beqz    $v0, loc_3FB0
		lui     $v0, 0xFDFF
		li      $v0, 0xFDFFFFFF
		and $v0, $v1, $v0
		li      $v1, 0x1EDDC0
		sw      $zero, 0x1C($t0)
		sw      $v0, 0x30($t0)
		lw      $v0, 0x24($v1)
		nop
		lw      $a0, 0x1C($v0)
		nop
		sw      $a0, 0xC($t0)
		lw      $v0, 0x24($v1)
		nop
		lw      $a0, 0xC($v0)
		nop
		sw      $a0, 0x10($t0)

		loc_3FB0:                                # CODE XREF : ROM:00003F68↑j
		addiu   $t0, -0x40
		lw      $v1, 0x30($t0)
		nop
		and $v0, $v1, $t1
		beqz    $v0, loc_4008
		lui     $v0, 0xFDFF
		li      $v0, 0xFDFFFFFF
		and $v0, $v1, $v0
		li      $v1, 0x1EDDC0
		sw      $zero, 0x1C($t0)
		sw      $v0, 0x30($t0)
		lw      $v0, 0x54($v1)
		nop
		lw      $a0, 0xC($v0)
		nop
		sw      $a0, 0xC($t0)
		lw      $v0, 0x54($v1)
		nop
		lw      $a0, 0x10($v0)
		nop
		sw      $a0, 0x10($t0)

		loc_4008:                                # CODE XREF : ROM:00003FC0↑j
		addiu   $t0, 0x80
		lw      $a0, 0x30($t0)
		nop
		and $v0, $a0, $t1
		beqz    $v0, loc_4054
		lui     $v1, 0xFDFF
		li      $v1, 0xFDFFFFFF
		and $v1, $a0, $v1
		li      $v0, 0xFFFF8AD8
		sw      $v1, 0x30($t0)
		lui     $v1, 0x1F
		sw      $zero, 0x1C($t0)
		sw      $v0, 0xC($t0)
		lw      $v0, 0x1EDE40
		nop
		lw      $a0, 0xC($v0)
		nop
		sw      $a0, 0x10($t0)

		loc_4054:                                # CODE XREF : ROM:00004018↑j
		addiu   $t0, -0x900
		lw      $v1, 0x30($t0)
		nop
		and $v0, $v1, $t1
		beqz    $v0, loc_41CC
		lui     $v0, 0xF3FF
		li      $v0, 0xF3FFFFFF
		lui     $a0, 2
		or $a0, $v1, $a0
		and $a0, $v0
		li      $v1, 0x1EDDC0
		lui     $a1, 0x400
		lw      $v0, 0x50($v1)
		or $a0, $a1
		lw      $a2, 0($v0)
		lui     $v0, 3
		sw      $a2, 0xC($t0)
		lw      $a1, 0x50($v1)
		li      $v0, 0x29E10
		lw      $a2, 4($a1)
		li      $v1, 0x80
		sw      $v0, 0x20($t0)
		li      $v0, 0x14
		sh      $v1, 0x2E($t0)
		li      $v1, 0x32  # '2'
		sh      $v0, 0x28($t0)
		li      $v0, 0x66  # 'f'
		sh      $v1, 0x2A($t0)
		lui     $v1, 0x20  # ' '
		sh      $v0, 0x2C($t0)
		sw      $a0, 0x30($t0)
		sh      $zero, 0x30($t0)
		lw      $v0, 0x30($t0)
		lui     $a0, 0x40  # '@'
		or $v0, $v1
		or $v0, $a0
		lui     $v1, 0x10
		or $v0, $v1
		lui     $a0, 8
		or $v0, $a0
		lui     $a0, 0xA
		lw      $v1, 4($t0)
		lw      $a1, 0xA25E4
		sw      $a2, 0x10($t0)
		sw      $v0, 0x30($t0)
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0x60($v1)
		nop
		ori     $v0, 8
		sw      $v0, 0x60($v1)
		lw      $a0, 4($t0)
		move    $a3, $zero
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0x60($a0)
		addiu   $t3, $t0, -0xEC0
		ori     $v0, 4
		sw      $v0, 0x60($a0)
		lw      $v1, 4($t0)
		lui     $t1, 1
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0xD0($v1)
		lui     $t2, 1
		ori     $v0, 8
		sw      $v0, 0xD0($v1)
		lw      $a0, 4($t0)
		lui     $v1, 0xA
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0xD0($a0)
		lw      $a2, 0xA2600
		ori     $v0, 4
		sw      $v0, 0xD0($a0)

		loc_4184:                                # CODE XREF : ROM:000041BC↓j
		move    $v0, $t1
		addu    $t1, $t2
		sll     $a1, $a3, 3
		sra     $a3, $v0, 16
		lh      $v1, 2($t0)
		lh      $v0, 0x6542($t3)
		sll     $v1, 2
		addu    $v1, $a2
		sll     $v0, 2
		addu    $v0, $a2
		addu    $v0, $a1, $v0
		addu    $a1, $v1
		lw      $a0, 0($v0)
		slti    $v0, $a3, 0x10
		bnez    $v0, loc_4184
		sw      $a0, 4($a1)
		li      $v0, 0x1400
		sh      $v0, 0x24($t0)

		loc_41CC:                                # CODE XREF : ROM:00004064↑j
		addiu   $t0, $t5, 0x33C0
		lw      $v1, 0x30($t0)
		lui     $v0, 1
		and $v0, $v1, $v0
		beqz    $v0, loc_4344
		lui     $v0, 0xF3FF
		li      $v0, 0xF3FFFFFF
		lui     $a0, 2
		or $a0, $v1, $a0
		and $a0, $v0
		li      $v1, 0x1EDDC0
		lui     $a1, 0x800
		lw      $v0, 0x74($v1)
		or $a0, $a1
		lw      $a2, 0($v0)
		lui     $v0, 3
		sw      $a2, 0xC($t0)
		lw      $a1, 0x74($v1)
		li      $v0, 0x29E10
		lw      $a2, 4($a1)
		li      $v1, 0x80
		sw      $v0, 0x20($t0)
		li      $v0, 0x12C
		sh      $v1, 0x2E($t0)
		li      $v1, 0x32  # '2'
		sh      $v0, 0x28($t0)
		li      $v0, 0x100
		sh      $v1, 0x2A($t0)
		lui     $v1, 0x20  # ' '
		sh      $v0, 0x2C($t0)
		sw      $a0, 0x30($t0)
		sh      $zero, 0x30($t0)
		lw      $v0, 0x30($t0)
		lui     $a0, 0x40  # '@'
		or $v0, $v1
		or $v0, $a0
		lui     $v1, 0x10
		or $v0, $v1
		lui     $a0, 8
		or $v0, $a0
		lui     $a0, 0xA
		lw      $v1, 4($t0)
		lw      $a1, 0xA25E4
		sw      $a2, 0x10($t0)
		sw      $v0, 0x30($t0)
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0x60($v1)
		nop
		ori     $v0, 8
		sw      $v0, 0x60($v1)
		lw      $a0, 4($t0)
		move    $a3, $zero
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0x60($a0)
		addiu   $t3, $t0, -0xF40
		ori     $v0, 4
		sw      $v0, 0x60($a0)
		lw      $v1, 4($t0)
		lui     $t1, 1
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0xD0($v1)
		lui     $t2, 1
		ori     $v0, 8
		sw      $v0, 0xD0($v1)
		lw      $a0, 4($t0)
		lui     $v1, 0xA
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0xD0($a0)
		lw      $a2, 0xA2600
		ori     $v0, 4
		sw      $v0, 0xD0($a0)

		loc_42FC:                                # CODE XREF : ROM:00004334↓j
		move    $v0, $t1
		addu    $t1, $t2
		sll     $a1, $a3, 3
		sra     $a3, $v0, 16
		lh      $v1, 2($t0)
		lh      $v0, 0x6542($t3)
		sll     $v1, 2
		addu    $v1, $a2
		sll     $v0, 2
		addu    $v0, $a2
		addu    $v0, $a1, $v0
		addu    $a1, $v1
		lw      $a0, 0($v0)
		slti    $v0, $a3, 0x11
		bnez    $v0, loc_42FC
		sw      $a0, 4($a1)
		li      $v0, 0x1400
		sh      $v0, 0x24($t0)

		loc_4344:                                # CODE XREF : ROM:000041DC↑j
		addiu   $t0, $t6, 0x34C0
		lw      $a3, 0x30($t0)
		lui     $t1, 1
		and $v0, $a3, $t1
		beqz    $v0, loc_43C4
		lui     $v1, 0x1F
		li      $v1, 0x1EDDC0
		lw      $v0, 0x88($v1)
		nop
		lw      $a0, 4($v0)
		li      $v0, 0x29E10
		sw      $a0, 0xC($t0)
		lw      $a1, 0x88($v1)
		li      $v1, 6
		lw      $a2, 0($a1)
		lui     $a0, 0x2000
		sw      $v0, 0x20($t0)
		lui     $v0, 0xC00
		or $v0, $a3, $v0
		sw      $v1, 0x38($t0)
		lui     $v1, 8
		or $v0, $v1
		or $v0, $a0
		lui     $v1, 0x20  # ' '
		or $v0, $v1
		lui     $a0, 0x10
		or $v0, $a0
		lui     $v1, 0x40  # '@'
		or $v0, $v1
		sw      $v0, 0x30($t0)
		sw      $a2, 0x10($t0)

		loc_43C4:                                # CODE XREF : ROM:00004354↑j
		addiu   $t0, 0x800
		lw      $v1, 0x30($t0)
		nop
		and $v0, $v1, $t1
		beqz    $v0, loc_447C
		lui     $v0, 0
		li      $v0, 0xFFFF90E8
		lui     $a1, 0x1F
		sw      $v0, 0xC($t0)
		lui     $v0, 0xC00
		or $v0, $v1, $v0
		lui     $v1, 0x40  # '@'
		or $v0, $v1
		lui     $a0, 0x20  # ' '
		or $v0, $a0
		lui     $a0, 0x10
		or $v0, $a0
		lw      $v1, 0x1EDE54
		lw      $a0, 4($t0)
		lw      $a1, 4($v1)
		sw      $v0, 0x30($t0)
		lui     $v0, 0xA
		sw      $a1, 0x10($t0)
		lw      $a1, 0xA25E4
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0x60($a0)
		nop
		ori     $v0, 8
		sw      $v0, 0x60($a0)
		lw      $v1, 4($t0)
		nop
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0x60($v1)
		nop
		ori     $v0, 4
		sw      $v0, 0x60($v1)
		lw      $a0, 4($t0)
		nop
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0x80($a0)
		nop
		ori     $v0, 8
		sw      $v0, 0x80($a0)

		loc_447C:                                # CODE XREF : ROM:000043D4↑j
		addiu   $t0, -0x180
		lw      $v1, 0x30($t0)
		nop
		and $v0, $v1, $t1
		beqz    $v0, nullsub_2
		lui     $a1, 0x1F
		lui     $v0, 0x40  # '@'
		or $v0, $v1, $v0
		lui     $a0, 0x20  # ' '
		or $v0, $a0
		lw      $v1, 0x1EDE60
		lw      $a0, 4($t0)
		lw      $a1, 0($v1)
		sw      $v0, 0x30($t0)
		lui     $v0, 0xA
		sw      $a1, 0x10($t0)
		lw      $a1, 0xA25E4
		sll     $a0, 2
		addu    $a0, $a1
		lw      $v0, 0($a0)
		nop
		ori     $v0, 8
		sw      $v0, 0($a0)
		lw      $v1, 4($t0)
		nop
		sll     $v1, 2
		addu    $v1, $a1
		lw      $v0, 0x10($v1)
		nop
		ori     $v0, 4
		sw      $v0, 0x10($v1)
#endif
	UNIMPLEMENTED();
}

void GetCarriedItems()//?(<), B9974(<) (F)
{
	int i;
	int j;

	for (i = 0; i < level_items; i++)
	{
		items[i].carried_item = -1;
	}

	for (i = 0; i < level_items; i++)
	{
		struct ITEM_INFO* item = &items[i];

		if (objects[item->object_number].intelligent ||
			item->object_number >= SEARCH_OBJECT1 && item->object_number <= SEARCH_OBJECT3)
		{
			struct ITEM_INFO* cur;

			for (j =room[item->room_number].item_number; j != -1; j = cur->next_item)
			{
				cur = &items[j];

				if (abs(cur->pos.x_pos - item->pos.x_pos) < SECTOR(0.5) &&
					abs(cur->pos.y_pos - item->pos.y_pos) < SECTOR(0.25) &&
					abs(cur->pos.z_pos - item->pos.z_pos) < SECTOR(0.5) &&
					objects[cur->object_number].collision == PickUpCollision)
				{
					cur->carried_item = item->carried_item;
					item->carried_item = j;
					RemoveDrawnItem(j);
					cur->room_number = 255;
				}
			}
		}
	}
}

void GetAIPickups()//?, B9B84 (F)
{
	int i, j;

	//loc_62CC
	for (i = 0; i < level_items; i++)
	{
		if (objects[items[i].object_number].intelligent)
		{
			items[i].ai_bits = 0;

			if (nAIObjects > 0)
			{
				//loc_6318
				for (j = 0; j < nAIObjects; j++)
				{
					if (ABS(AIObjects[j].x - items[i].pos.x_pos) < SECTOR(0.5) &&
						ABS(AIObjects[j].z - items[i].pos.z_pos) < SECTOR(0.5) &&
						AIObjects[j].room_number == items[i].room_number &&
						AIObjects[j].object_number < AI_PATROL2)
					{
						items[i].active = FALSE;
						items[i].status = ITEM_INACTIVE;
						items[i].gravity_status = FALSE;
						items[i].hit_status = FALSE;
						items[i].collidable = FALSE;
						items[i].looked_at = FALSE;
						items[i].dynamic_light = FALSE;
						items[i].poisoned = FALSE;
						items[i].ai_bits = 1 << (AIObjects[j].object_number - AI_GUARD);
						items[i].item_flags[3] = AIObjects[j].trigger_flags;

						if (AIObjects[j].object_number != AI_GUARD)
						{
							AIObjects[j].room_number = 255;
						}
					}//loc_63D8
				}
			}
			//loc_63F0
			items[i].TOSSPAD |= (items[i].ai_bits | items[i].item_flags[3]);

		}//loc_6410
	}
	//loc_6420
}

void SetupGame()//?(<), B9DA8(<) (F)
{
	SeedRandomDraw(0xD371F947);
	SeedRandomControl(0xD371F947);

	wibble = 0;
	torchroom = 255;

#if !PC_VERSION
	init_water_table();
	InitialiseSqrtTable();

	InGameCnt = 0;

	InitialiseAnimatedTextures();
#endif

	InitialiseFootPrints();
	InitBinoculars();
#if !AUG_VERSION
	InitTarget();
#endif
	InitialiseGameFlags();

#if PC_VERSION
	InitialiseLara(
		gfCurrentLevel != LVL5_THIRTEENTH_FLOOR &&
		gfCurrentLevel != LVL5_BASE &&
		gfCurrentLevel != LVL5_GALLOWS_TREE &&
		gfCurrentLevel != LVL5_STREETS_OF_ROME &&
		!gfInitialiseGame);
#else
	if ((gfCurrentLevel == LVL5_THIRTEENTH_FLOOR || gfCurrentLevel == LVL5_BASE || gfCurrentLevel == LVL5_GALLOWS_TREE || gfCurrentLevel == LVL5_STREETS_OF_ROME) && gfInitialiseGame != 0)
	{
		//B9E50
		InitialiseLaraCarriedItems(0);
	}
	else
	{
		//B9E60
		InitialiseLaraCarriedItems(1);
	}
#endif

	//B9E68
	GetCarriedItems();
	GetAIPickups();

	SeedRandomDraw(0xD371F947);
	SeedRandomControl(0xD371F947);

	return;
}

void InitialiseGameFlags()//?(<), B9D30(<) (F)
{
	int i;

	//loc_6440:
	for (i = 0; i < 10; i++)
	{
		flipmap[i] = 0;
		flip_stats[i] = 0;
	}

	flip_status = 0;
	flipeffect = -1;

	//loc_647C
	for (i = 0; i < 136; i++)
	{
		cd_flags[i] = 0;
	}

	IsAtmospherePlaying = 0;
	camera.underwater = 0;
}

void InitialiseResidentCut(unsigned char a0, unsigned char a1, unsigned char a2, unsigned char a3)//?(<), B9EA0(<) (F)
{
#if !PC_VERSION
	int i;
	int s0;
	int s1;
	int s2;
	char* s3;
	char* s4;
	char* s5;
	char* s6;
	int s7;
	int mallocSize;//$a0
#if PSX_VERSION || SAT_VERSION
#if PSXPC_TEST
	int nHandle = 0;
#else
	int nHandle;
#endif
#elif PSXPC_VERSION
	FILE* nHandle = NULL;
#endif
	int residentData[4];

	residentData[0] = a0;//0x38(sp)
	residentData[1] = a1;//0x3C(sp)
	residentData[2] = a2;//0x40(sp)
	residentData[3] = a3;//0x44(sp)

	if ((a0 | a1 | a2 | a3))
	{
		lastcamnum = -1;
		GLOBAL_playing_cutseq = 0;
		cutseq_trig = 0;

		//loc_6614
		for (i = 46; i >= 0; i--)
		{
			cutseq_resident_addresses[i].packed_data = NULL;
		}

#if DISC_VERSION
		DEL_CDFS_OpenFile(CUTSEQ);
		DEL_CDFS_Read((char*)&tsv_buffer[0], 2048);
#else
#if PSX_VERSION
		nHandle = PCopen("\\CUTSEQ.JIZ", 0, 0);
#elif PSXPC_VERSION
		nHandle = fopen("CUTSEQ.JIZ", "rb");
#endif
		FILE_Read((char*)&tsv_buffer[0], 1, 2048, nHandle);
#endif
		s3 = ReadResidentData(residentData[0], nHandle);
		s4 = ReadResidentData(residentData[1], nHandle);
		s5 = ReadResidentData(residentData[2], nHandle);
		s6 = ReadResidentData(residentData[3], nHandle);

		s7 = 0;
		s2 = 0;
		s1 = 0;
		s0 = 0;

		if (s3 != NULL)
		{
			s0 = sub_BA148((short*)s3);
		}
		//loc_66C0
		if (s4 != NULL)
		{
			s1 = sub_BA148((short*)s4);
		}
		//loc_66D4
		if (s5 != NULL)
		{
			s2 = sub_BA148((short*)s5);
		}
		//loc_66E8
		if (s6 != NULL)
		{
			s7 = sub_BA148((short*)s6);
		}

		//loc_66FC
		mallocSize = 0;

		if (s0 > 0)
		{
			mallocSize = s0;
		}

		//loc_6708
		if (mallocSize < s1)
		{
			mallocSize = s1;
		}//loc_671C

		if (mallocSize < s2)
		{
			mallocSize = s2;
		}//loc_672C

		if (mallocSize < s7)
		{
			mallocSize = s7;
		}

		//loc_6738
		GLOBAL_resident_depack_buffers = (char*)game_malloc(mallocSize);

		if (residentData[0] != 0)
		{
			cutseq_resident_addresses[residentData[0]].packed_data = s3;
		}

		//loc_6764
		if (residentData[1] != 0)
		{
			cutseq_resident_addresses[residentData[1]].packed_data = s4;
		}
		//loc_6788
		if (residentData[2] != 0)
		{
			cutseq_resident_addresses[residentData[2]].packed_data = s5;
		}
		//loc_67A4
		if (residentData[3] != 0)
		{
			cutseq_resident_addresses[residentData[3]].packed_data = s6;
		}
	}//loc_67C8
#endif
}

#if !PC_VERSION
#if (PSX_VERSION || SAT_VERSION)
char* ReadResidentData(int residentIndex, int nHandle)//(<), BA0DC(<) (F)
#elif PSXPC_VERSION
char* ReadResidentData(int residentIndex, FILE* nHandle)//(<), BA0DC(<) (F)
#endif
{
	char* ptr;

	if (residentIndex != 0)
	{
#if DISC_VERSION
		DEL_CDFS_Seek(tsv_buffer[residentIndex].xy);
#else
#if PSX_VERSION
		PClseek(nHandle, tsv_buffer[residentIndex].xy, 0);
#elif PSXPC_VERSION
		fseek(nHandle, tsv_buffer[residentIndex].xy, SEEK_SET);
#endif
#endif
		ptr = game_malloc(tsv_buffer[residentIndex].rgz);

#if DISC_VERSION
		DEL_CDFS_Read(ptr, tsv_buffer[residentIndex].rgz);
#else
		FILE_Read(ptr, sizeof(char), tsv_buffer[residentIndex].rgz, nHandle);
#endif
		return ptr;
	}
	
	return NULL;
}
#endif
long sub_BA148(short* ptr)//?, BA148(<) (F)
{
	int i;//$a1
	long addr = 0;//$a2
	short v1;

	GLOBAL_cutme = (struct NEW_CUTSCENE*)ptr;

	if (ptr[0] > 0)
	{
		//loc_6894
		for(i = ptr[0]; i != 0; i--)
		{
			v1 = ptr[15] + 1;
			ptr += 4;
			addr += (((((v1 + 1) << 2) + v1 + 1) << 2) + v1 + 1) << 2;///@FIXME * sizeof x
		}
	}//locret_68C0

	return addr + 0xA8;

}

void reset_cutseq_vars()//?(<), BA194(<) (F)
{
	cutseq_num = 0;
	cutseq_trig = 0;
	GLOBAL_playing_cutseq = 0;
	GLOBAL_cutseq_frame = 0;

	SetFadeClip(0, 1);
}

void InitialiseEffects()//?(<), BA81C(<) (F)
{
	int i;

	S_MemSet((char*)&spark, 0, sizeof(spark));
	S_MemSet((char*)&fire_spark, 0, sizeof(fire_spark));
	S_MemSet((char*)&smoke_spark, 0, sizeof(smoke_spark));
	S_MemSet((char*)&Gunshells, 0, sizeof(Gunshells));
	S_MemSet((char*)&Gunflashes, 0, sizeof(Gunflashes));
	S_MemSet((char*)&debris, 0, sizeof(debris));
	S_MemSet((char*)&blood, 0, sizeof(blood));
	S_MemSet((char*)&splashes, 0, sizeof(splashes));
	S_MemSet((char*)&ripples, 0, sizeof(ripples));
	S_MemSet((char*)&Bubbles, 0, sizeof(Bubbles));
	S_MemSet((char*)&Drips, 0, sizeof(Drips));
	S_MemSet((char*)&ShockWaves, 0, sizeof(ShockWaves));

	for (i = 0; i < sizeof(spark) / sizeof(struct SPARKS); i++)
	{
		spark[i].Dynamic = -1;
	}

	next_fire_spark = 1;
	next_smoke_spark = 0;
	next_gunshell = 0;
	next_bubble = 0;
	next_drip = 0;
	next_debris = 0;
	next_blood = 0;
	WB_room = -1;
}

void InitialiseClosedDoors()//?(<), BB498(<) (F)
{
	int i;

	for (i = 0; i < 32; i++)
	{
		ClosedDoors[i] = 0;
	}

	return;
}