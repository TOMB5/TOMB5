#include "FILE.H"
#include "SPECTYPES.H"
#include "SPECIFIC.H"
#include <cstdio>
#include <cstring>
#include "INCLUDE.H"
#include "GAMEFLOW.H"
#include "DRAWPRIMITIVE.H"
#include "HWINSERT.H"
#include "INIT.H"
#include "GLOBAL.H"
#include "CONTROL.H"
#include "GAME.H"
#include "DIRECTX.H"
#include "DRAW.H"
#include "SWITCH.H"
#include "HAIR.H"
#include "PICKUP.H"
#include "LARA.H"
#include "DOOR.H"
#include "CAMERA.H"
#include "SPOTCAM.H"
#include "BOX.H"
#include "EFFECTS.H"
#include "TOMB4FX.H"
#include "DELTAPAK.H"
#include "LOT.H"
#include "ITEMS.H"
#include "EFFECT2.H"
#include "OBJLIGHT.H"
#include "LARAMISC.H"
#include "FLMTORCH.H"

short* floor_data;
short* mesh_base;
int AnimFileLen;
char	cd_drive = 0;

int num_pages;
FILE* fp_level;
char* level_data;
char* level_data_orig;
struct mesh_vbuf_s
{
	char pad0[4]; // pos 0 size 4
	short* field1; // pos 4 size 4  APPARENTLY object texture index
	char pad[22]; // pos 8 size 22
	LPDIRECT3DVERTEXBUFFER vbuf; // pos 30 size 4
	char pad2[36]; // pos 34 size 36
};
mesh_vbuf_s** mesh_vbufs;
OBJECT_TEXTURE* object_textures;
SPRITE_STRUCT* sprites;
OBJECT_TEXTURE* waterfall_textures[6];
float waterfall_y[6];
int num_room_lights;

#ifdef __cplusplus
extern "C" {
#endif

#define AllocT(d, s, n) d = (s*)game_malloc(sizeof(s) * (n))
#define AllocReadT(d, s, n) AllocT((d), s, (n));OnlyReadT((d), s, (n))
#define OnlyReadT(d, s, n) readBytes((d), sizeof(s) * (n))

#define Alloc(d, s, n) d = (struct s*)game_malloc(sizeof(struct s) * (n))
#define AllocRead(d, s, n) Alloc((d), s, (n));OnlyRead((d), s, (n))
#define OnlyRead(d, s, n) readBytes((d), sizeof(struct s) * (n))

#define AddPtr(p, t, n) p = (t*)((char*)(p) + (ptrdiff_t)(n));

	//#define LogCurPos() Log(2, "current pos: %08x", 0x319af7 + (int)(level_data - level_data_orig))

	inline uint8_t readByte()
	{
		const uint8_t ret = *(uint8_t*)level_data;
		level_data += 1;
		return ret;
	}

	inline uint16_t readWord()
	{
		const uint16_t ret = *(uint16_t*)level_data;
		level_data += 2;
		return ret;
	}

	inline uint32_t readDword()
	{
		const uint32_t ret = *(uint32_t*)level_data;
		level_data += 4;
		return ret;
	}

	inline uint16_t freadWord()
	{
		uint16_t ret;
		fread(&ret, 2, 1, fp_level);
		return ret;
	}

	inline uint32_t freadDword()
	{
		uint32_t ret;
		fread(&ret, 4, 1, fp_level);
		return ret;
	}

	inline void readBytes(void* dst, unsigned int count)
	{
		memcpy(dst, level_data, count);
		level_data += count;
	}

	inline void freadBytes(unsigned int count)
	{
		void* buf = malloc(count);
		fread(buf, 1, count, fp_level);
		free(buf);
	}

	void FreeTextures()
	{
		DX_TRY(App.lpD3DDevice->SetTexture(0, nullptr));
		DX_TRY(App.lpD3D->EvictManagedTextures());

		Unimpl();
	}

	void FreeD3DLights()
	{
		;
	}

	void DXFreeSounds()
	{
		Unimpl();
	}

	void FreeLevel()
	{
		Log(LT_Enter, "FreeLevel");

		// todo meshes

		Log(LT_Info, "Free Textures");
		FreeTextures();

		Log(LT_Info, "Free Lights");
		FreeD3DLights();

		DXFreeSounds();

		malloc_ptr = malloc_buffer;
		malloc_free = malloc_size;
	}

	void MakeCutsceneResident(int r1, int r2, int r3, int r4)
	{
		Unimpl();
	}

	void ClearFX()
	{
		Unimpl();
	}

	void InitMatrix()
	{
		// todo

		phd_dxptr = (float*)malloc(480 * sizeof(float));
	}

	void InitWater()
	{
		Unimpl();
	}

	void BuildGlobalFogBulbList()
	{
		Unimpl();
	}

	void RoomInit()
	{
		BuildGlobalFogBulbList();
	}

	void Init()
	{
		InitWater();
		RoomInit();
	}

	void LoadTextures(int numRoom, int numObj, int numBump)
	{
		Log(LT_Enter, "LoadTextures");

		int uncomp32 = freadDword();
		int comp32 = freadDword();
		fseek(fp_level, comp32, SEEK_CUR);
		int uncomp16 = freadDword();
		int comp16 = freadDword();
		fseek(fp_level, comp16, SEEK_CUR);
		uncomp32 = freadDword();
		comp32 = freadDword();
		fseek(fp_level, comp32, SEEK_CUR);
		return;

		//dword_875144 = level_data;
		num_pages = 1;

		int v85 = 0;
		int depth = 4;

		D3DTEXTUREINFO* texf = &CUR_TEX;

		void* texbuf;
		bool useCompression = true;

		if (texf->rbpp == 5 && texf->gbpp == 5 && texf->bbpp == 5 && texf->abpp == 1)
		{
			v85 = 2;
			depth = 2;

			int uncomp32 = freadDword();
			int comp32 = freadDword();
			if (useCompression)
				fseek(fp_level, comp32, SEEK_CUR);
			else
				fseek(fp_level, uncomp32, SEEK_CUR);

			int uncomp16 = freadDword();
			int comp16 = freadDword();
			texbuf = malloc(comp16);
			level_data = (char*)malloc(uncomp16);

			if (useCompression)
			{
				fread(texbuf, comp16, 1, fp_level);
				Decompress(level_data, texbuf, comp16, uncomp16);
			}
			else
			{
				fread(level_data, uncomp16, 1, fp_level);
			}
		}
		else
		{
			if (texf->rbpp == 8 && texf->gbpp == 8 && texf->bbpp == 8 && texf->abpp == 8)
				v85 = 1;

			int uncomp32 = freadDword();
			int comp32 = freadDword();
			texbuf = malloc(comp32);
			level_data = (char*)malloc(uncomp32);

			if (useCompression)
			{
				fread(texbuf, comp32, 1, fp_level);
				Decompress(level_data, texbuf, comp32, uncomp32);

				int uncomp16 = freadDword();
				int comp16 = freadDword();
				fseek(fp_level, comp16, SEEK_CUR);
			}
			else
			{
				fread(level_data, comp32, 1, fp_level);

				int uncomp16 = freadDword();
				int comp16 = freadDword();
				fseek(fp_level, uncomp16, SEEK_CUR);
			}
		}

		free(texbuf);

		Log(LT_Info, "RTPages %d", numRoom);

		int szRoom = numRoom * depth * TEXTURE_PAGE;
		void* bufRoom;
		AllocReadT(bufRoom, char, szRoom);
		S_LoadBar();

		if (numRoom > 0)
		{
			Unimpl();
		}
	}
	void FixUpRoom(room_info *rooms, room_info *roomData)
	{
		AddPtr(roomData->door, short, roomData + 1);
		AddPtr(roomData->floor, struct FLOOR_INFO, roomData + 1);
		AddPtr(roomData->light, struct LIGHTINFO, roomData + 1);
		AddPtr(roomData->mesh, struct MESH_INFO, roomData + 1);
		AddPtr(roomData->Separator4, void, roomData + 1);
		AddPtr(roomData->LayerOffset, struct tr5_room_layer, roomData + 1);
		AddPtr(roomData->PolyOffset, void, roomData + 1);
		AddPtr(roomData->PolyOffset2, void, roomData + 1);
		AddPtr(roomData->VerticesOffset, struct tr5_room_vertex, roomData + 1);

		roomData->LightDataSize += (uint32_t)(roomData + 1);

		if ((uint8_t)roomData->door & 1)
		{
			Log(0, "%X", roomData->door);
			roomData->door = 0;
		}

		char* polyOff = (char*)roomData->PolyOffset;
		char* polyOff2 = (char*)roomData->PolyOffset2;
		char* vertOff = (char*)roomData->VerticesOffset;

		for (int i = 0; i < roomData->NumLayers; i++)
		{
			roomData->LayerOffset[i].PolyOffset = polyOff;
			roomData->LayerOffset[i].PolyOffset2 = polyOff2;
			roomData->LayerOffset[i].VerticesOffset = vertOff;

			polyOff += sizeof(struct tr4_mesh_face3) * roomData->LayerOffset[i].NumLayerTriangles +
				sizeof(struct tr4_mesh_face4) * roomData->LayerOffset[i].NumLayerRectangles;

			polyOff2 += 4 * roomData->LayerOffset[i].NumLayerVertices; // todo find what struct this is

			vertOff += sizeof(struct tr5_room_vertex) * roomData->LayerOffset[i].NumLayerVertices;
		}

		memcpy(rooms, roomData, sizeof(struct room_info));

		if (rooms->num_lights > num_room_lights)
			num_room_lights = rooms->num_lights;
	}
	void LoadRoomStream()
	{
		readDword(); // read unused value

		int numRooms = readDword(); // todo maybe it's 16 so it'll explode
		Alloc(room, room_info, numRooms);

		for (int i = 0; i < numRooms; i++)
		{
			readDword(); // XELA landmark

			int roomDataSize = readDword();
			char* roomData;
			AllocReadT(roomData, char, roomDataSize);

			FixUpRoom(&room[i], (room_info*)roomData);
		}

		number_rooms = numRooms;
	}
	void BuildOutsideTable()
	{
		Unimpl();
	}
	void LoadRooms()
	{
		Log(LT_Enter, "LoadRooms");

		wibble = 0;
		num_room_lights = 0;
		//dword_7E7FE8 = 0;

		LoadRoomStream();
		BuildOutsideTable();

		int numFloorData = readDword();
		AllocReadT(floor_data, short, numFloorData);
		Log(LT_Default, "Floor Data Size %d @ %x", numFloorData, floor_data);
	}
	void BaddyObjects()
	{
		struct object_info* object = &objects[LARA];

		object->shadow_size = 160;
		object->initialise = &InitialiseLaraLoad;
		object->hit_points = 1000;
		object->draw_routine = NULL;

		object->using_drawanimating_item = 0;
		object->save_hitpoints = 1;
		object->save_position = 1;
		object->save_flags = 1;
		object->save_anim = 1;

		Unimpl();
	}
	void ObjectObjects()
	{
		Unimpl();
	}
	void TrapObjects()
	{
		Unimpl();
	}
	void InitialiseEffects()
	{
		Unimpl();
	}
	void InitialiseObjects()
	{
		for (int i = 0; i < NUMBER_OBJECTS; i++)
		{
			objects[i].initialise = nullptr;
			objects[i].collision = nullptr;
			objects[i].control = nullptr;

			objects[i].intelligent = false;
			objects[i].save_position = false;
			objects[i].save_hitpoints = false;
			objects[i].save_flags = false;
			objects[i].save_anim = false;
			objects[i].water_creature = false;
			objects[i].save_mesh = false;
			objects[i].using_drawanimating_item = true;

			objects[i].draw_routine = DrawAnimatingItem;
			objects[i].ceiling = nullptr;
			objects[i].floor = nullptr;

			objects[i].pivot_length = 0;
			objects[i].radius = 10;
			objects[i].shadow_size = 0;
			objects[i].hit_points = -16384;
			objects[i].explodable_meshbits = 0;
			objects[i].draw_routine_extra = nullptr;

			AddPtr(objects[i].frame_base, short, frames);

			objects[i].object_mip = 0;
		}

		BaddyObjects();
		ObjectObjects();
		TrapObjects();
		InitialiseHair();
		InitialiseEffects();

		SequenceUsed[0] = 0;
		SequenceUsed[1] = 0;
		SequenceUsed[2] = 0;
		SequenceUsed[3] = 0;
		SequenceUsed[4] = 0;
		SequenceUsed[5] = 0;

		NumRPickups = 0;

		CurrentSequence = 0;

		SequenceResults[0][1][2] = 0;
		SequenceResults[0][2][1] = 1;
		SequenceResults[1][0][2] = 2;
		SequenceResults[1][2][0] = 3;
		SequenceResults[2][0][1] = 4;
		SequenceResults[2][1][0] = 5;

		for (int i = 0; i < gfNumMips; i++)
		{
			const int mip = (gfMips[i] & 0xF0) << 6;
			const int index = (gfMips[i] & 0xF) << 7;
			objects[ANIMATING1 + 2 * index].object_mip = mip;
		}

		if (objects[RAT].loaded)
			Alloc(Rats, RAT_STRUCT, 32); // todo: RAT_STRUCT size wrong, should be 26, is 28 (should be 832 B)

		if (objects[BAT].loaded)
			Alloc(Bats, BAT_STRUCT, 64); // todo: BAT_STRUCT size wrong, should be 30, is 32 (should be 1920 B)

		if (objects[SPIDER].loaded)
			Alloc(Spiders, SPIDER_STRUCT, 64); // todo: SPIDER_STRUCT size wrong, should be 26, is 28 (should be 1664 B)
	}
	void ProcessMeshData(int nmeshes)
	{
		Log(LT_Enter, "ProcessMeshData %d", nmeshes);

		//numLvlMeshes = nmeshes;

		AllocT(mesh_vbufs, struct mesh_vbuf_s*, nmeshes);
		mesh_base = (short*)malloc_ptr;

		Unimpl();

		Log(LT_Enter, "End ProcessMeshData");
	}
	void CreateSkinningData()
	{
		Unimpl();
	}
	void InitialiseClosedDoors()
	{
		memset(ClosedDoors, 0, 32 * sizeof(long));
	}
	void LoadObjects()
	{
		Log(LT_Enter, "LoadObjects");

		Zero(objects);
		Zero(static_objects);

		int numMeshWords = readDword();
		AllocReadT(mesh_base, short, numMeshWords);

		int numMeshPtrs = readDword();
		AllocT(meshes, short*, 2 * numMeshPtrs);
		OnlyReadT(meshes, short*, numMeshPtrs);

		for (int i = 0; i < numMeshPtrs; i++)
		{
			meshes[i] = &mesh_base[(int)meshes[i] / 2];
		}

		int numMeshes = numMeshPtrs;

		int numAnims = readDword();
		AllocRead(anims, ANIM_STRUCT, numAnims);

		int numChanges = readDword();
		AllocRead(changes, CHANGE_STRUCT, numChanges);

		int numDisps = readDword();
		AllocRead(ranges, RANGE_STRUCT, numDisps);

		int numAnimCmds = readDword();
		AllocReadT(commands, short, numAnimCmds);

		int numBones = readDword();
		AllocReadT(bones, long, numBones);

		int numFrames = readDword();
		AllocReadT(frames, short, numFrames);

		for (int i = 0; i < numAnims; i++)
		{
			AddPtr(anims[i].frame_ptr, short, frames);
		}

		int numModels = readDword();

		for (int i = 0; i < numModels; i++)
		{
			int obj = readDword();

			objects[obj].nmeshes = readWord();
			objects[obj].mesh_index = readWord();
			objects[obj].bone_index = readDword();
			objects[obj].frame_base = (short*)readDword();
			objects[obj].anim_index = readWord();

			readWord(); // alignment, always 0xFFEF

			objects[obj].loaded = 1;
		}

		if (LaraDrawType != LARA_DIVESUIT)
			CreateSkinningData();

		for (int i = 0; i < NUMBER_OBJECTS; i++)
		{
			objects[i].mesh_index *= 2;
		}

		// DUPLICATE THE ITEMS
		// before:   meshes = [1, 2, 3, 4, 5, ?, ?, ?, ?, ?]
		// qmemcpy:  meshes = [1, 2, 3, 4, 5, 1, 2, 3, 4, 5]
		// for loop: meshes = [1, 1, 2, 2, 3, 3, 4, 4, 5, 5]

		memcpy(&meshes[numMeshes], &meshes[0], sizeof(short*) * numMeshes);

		for (int i = 0; i < numMeshes; i++)
		{
			meshes[2 * i] = meshes[numMeshes + i];
			meshes[2 * i + 1] = meshes[numMeshes + i];
		}

		InitialiseObjects();
		InitialiseClosedDoors();

		int numStatics = readDword();

		for (int i = 0; i < numStatics; i++)
		{
			int meshID = readDword();

			static_objects[meshID].mesh_number = readWord();

			static_objects[meshID].x_minp = readWord();
			static_objects[meshID].x_maxp = readWord();
			static_objects[meshID].y_minp = readWord();
			static_objects[meshID].y_maxp = readWord();
			static_objects[meshID].z_minp = readWord();
			static_objects[meshID].z_maxp = readWord();

			static_objects[meshID].x_minc = readWord();
			static_objects[meshID].x_maxc = readWord();
			static_objects[meshID].y_minc = readWord();
			static_objects[meshID].y_maxc = readWord();
			static_objects[meshID].z_minc = readWord();
			static_objects[meshID].z_maxc = readWord();

			static_objects[meshID].flags = readWord();
		}

		for (int i = 0; i < NUMBER_STATIC_OBJECTS; i++)
		{
			static_objects[i].mesh_number *= 2;
		}

		ProcessMeshData(2 * numMeshes);
	}
	void LoadSprites()
	{
		Log(2, "LoadSprites");

		readDword(); // SPR\0

		int numSpr = readDword();

		Alloc(sprites, SPRITE_STRUCT, numSpr);

		for (int i = 0; i < numSpr; i++)
		{
			sprites[i].tile = readWord() + 1;
			sprites[i].x = readByte();
			sprites[i].y = readByte();
			sprites[i].width = readWord();
			sprites[i].height = readWord();
			sprites[i].left = (readWord() + 1) / 256.0;
			sprites[i].top = (readWord() + 1) / 256.0;
			sprites[i].right = (readWord() - 1) / 256.0;
			sprites[i].bottom = (readWord() - 1) / 256.0;
		}

		int numSprSeqs = readDword();

		for (int i = 0; i < numSprSeqs; i++)
		{
			int spriteID = readDword();
			short negLength = readWord();
			short offset = readWord();

			if (spriteID >= NUMBER_OBJECTS)
			{
				static_objects[spriteID - NUMBER_OBJECTS].mesh_number = offset;
			}
			else
			{
				objects[spriteID].nmeshes = negLength;
				objects[spriteID].mesh_index = offset;
				objects[spriteID].loaded = true;
			}
		}
	}
	void LoadCameras()
	{
		Log(LT_Enter, "LoadCameras");

		number_cameras = readDword();

		if (number_cameras != 0)
		{
			AllocRead(camera.fixed, OBJECT_VECTOR, number_cameras);
		}

		number_spotcams = readDword();

		if (number_spotcams != 0)
		{
			OnlyRead(SpotCam, SPOTCAM, number_spotcams);
		}
	}
	void LoadSoundEffects()
	{
		Log(LT_Enter, "LoadSoundEffects");

		number_sound_effects = readDword();
		Log(LT_Sound, "Number of SFX %d", number_sound_effects);

		if (number_sound_effects)
		{
			AllocRead(sound_effects, OBJECT_VECTOR, number_sound_effects);
		}
	}
	void LoadBoxes()
	{
		Log(LT_Enter, "LoadBoxes");

		number_boxes = readDword();
		AllocRead(boxes, box_info, number_boxes);

		int numOverlaps = readDword();
		AllocReadT(overlap, uint16_t, numOverlaps);

#if FALSE
		short** v3 = ground_zone[4];
		int v4 = number_boxes;
		int v13;
		do
		{
			int v5 = 2 * v4;
			short** v6 = v3 - 8;
			int v21 = 4;
			do
			{
				short* v7 = (short*)game_malloc(v5);
				void* v8 = level_data;
				unsigned int v9 = 2 * number_boxes;
				char v10 = 2 * number_boxes;
				*v6 = v7;
				v9 >>= 2;
				qmemcpy(v7, v8, 4 * v9);
				char* v12 = (char*)v8 + 4 * v9;
				short* v11 = &v7[2 * v9];
				LOBYTE(v9) = v10;
				v13 = v21;
				qmemcpy(v11, v12, v9 & 3);
				v6 += 2;
				v5 = 2 * number_boxes;
				level_data = (char*)level_data + 2 * number_boxes;
				--v21;
			} while (v13 != 1);

			char* v14 = (char*)game_malloc(2 * number_boxes);
			void* v15 = level_data;
			unsigned int v16 = 2 * number_boxes;
			*v3 = (short*)v14;
			qmemcpy(v14, v15, v16);
			++v3;
		} while ((int)v3 < (int)(ground_zone + 5 * 2));
#endif
		// todo may not work, but gives the same result as code (Core) above on ideone
		for (int i = 0; i < 5; i++)
		{
			AllocReadT(ground_zone[i][0], short, number_boxes);
		}
		// weird workaround because Core's code seem to only read half of the zones
		for (int i = 0; i < 5; i++)
		{
			short* tmp;
			AllocReadT(tmp, short, number_boxes);
			game_free(number_boxes * sizeof(short));
		}

		for (int i = 0; i < number_boxes; i++)
		{
			if (boxes[i].overlap_index & BOX_LAST)
			{
				boxes[i].overlap_index |= BOX_BLOCKED;
			}
		}
	}
	void LoadAnimatedTextures()
	{
		int numAnimTex = readDword();
		AllocReadT(AnimTextureRanges, uint16_t, numAnimTex);

		nAnimUVRanges = readByte();
	}
	void AdjustUV(int numTex)
	{
		Log(2, "AdjustUV");

		Unimpl();
	}
	void LoadTextureInfos()
	{
		Log(LT_Enter, "LoadTextureInfos");

		readDword(); // TEX\0

		int numObjTex = readDword();
		Log(LT_Info, "Texture Infos : %d", numObjTex);

		Alloc(object_textures, OBJECT_TEXTURE, numObjTex);

		struct tr4_object_texture tex;
		for (int i = 0; i < numObjTex; i++)
		{
			OnlyRead(&tex, tr4_object_texture, 1);

			object_textures[i].attribute = tex.Attribute;
			object_textures[i].tile_and_flag = tex.TileAndFlag & 0x7FFF;
			object_textures[i].new_flags = tex.NewFlags & 0x7FFF;

			for (int j = 0; j < 4; j++)
			{
				object_textures[i].vertices[j].x = tex.Vertices[j].Xpixel / 256.0;
				object_textures[i].vertices[j].y = tex.Vertices[j].Ypixel / 256.0;
			}
		}

		AdjustUV(numObjTex);

		Log(5, "Created %d Texture Pages", num_pages - 1);
	}
	void LoadDemoData()
	{
		uint16_t numDemoData = readWord();
		// no demo data anymore, count is always 0
	}
	void LoadAIObjects()
	{
		int num = readDword();

		if (num != 0)
		{
			nAIObjects = num;
			AllocRead(AIObjects, AIOBJECT, nAIObjects);
		}
	}
	void LoadItems()
	{
		Log(LT_Enter, "LoadItems");

		int num_items = readDword();

		if (num_items == 0) return;
		Alloc(items, ITEM_INFO, 256);
		level_items = num_items;
		InitialiseClosedDoors();
		InitialiseItemArray(256);

		for (int it = 0; it < num_items; it++)
		{
			struct ITEM_INFO* item = &items[it];

			item->object_number = readWord();
			item->room_number = readWord();
			item->pos.x_pos = readDword();
			item->pos.y_pos = readDword();
			item->pos.z_pos = readDword();
			item->pos.y_rot = readWord();
			item->shade = readWord();
			item->trigger_flags = readWord();
			item->flags = readWord();
		}

		for (int it = 0; it < num_items; it++)
		{
			InitialiseItem(it);
		}

		for (int r = 0; r < number_rooms; r++)
		{
			struct MESH_INFO* mesh = room[r].mesh;

			for (int m = 0; m < room[r].num_meshes; m++)
			{
				int sec = ((mesh->z - room[r].z) >> 10) + room[r].x_size * ((mesh->x - room[r].x) >> 10);
				struct FLOOR_INFO* floor = &room[r].floor[sec];

				if (!(boxes[floor->box].overlap_index & 0x4000)
					&& !(gfCurrentLevel == LVL5_BASE && (r == 19 || r == 23 || r == 16)))
				{
					int fl = floor->floor << 2;
					struct static_info* st = &static_objects[mesh->static_number];
					if (fl <= mesh->y - st->y_maxc + 512
						&& fl < mesh->y - st->y_minc)
					{
						if (st->x_maxc == 0 || st->x_minc == 0 ||
							st->z_maxc == 0 || st->z_minc == 0 ||
							(HIBYTE(st->x_maxc) ^ HIBYTE(st->x_minc) & 0x80 &&
								HIBYTE(st->z_maxc) ^ HIBYTE(st->z_minc) & 0x80))
						{
							floor->box |= 8;
						}
					}
				}
			}
		}
	}
	void MallocD3DLights()
	{
		Unimpl();
	}
	void CreateD3DLights()
	{
		Unimpl();
	}
	int GetCarriedItems()
	{
		Unimpl();
		return 0;
	}
	int GetAIPickups()
	{
		Unimpl();
		return 0;
	}
	void ClearFootPrints()
	{
		for (int i = 0; i < 32; i++)
		{
			FootPrint[i].Active = false;
		}

		FootPrintNum = 0;
	}
	void InitBinoculars()
	{
		Unimpl();
	}
	void InitTarget()
	{
		Unimpl();
	}
	void InitialiseGameFlags()
	{
		Unimpl();
	}
	void SetupGame()
	{
		SeedRandomDraw(0xD371F947);
		SeedRandomControl(0xD371F947);

		wibble = 0;
		torchroom = 255;

		ClearFootPrints();
		InitBinoculars();
		InitTarget();
		InitialiseGameFlags();

		InitialiseLara(
			gfCurrentLevel != LVL5_THIRTEENTH_FLOOR &&
			gfCurrentLevel != LVL5_BASE &&
			gfCurrentLevel != LVL5_GALLOWS_TREE &&
			gfCurrentLevel != LVL5_STREETS_OF_ROME &&
			!gfInitialiseGame);

		GetCarriedItems();
		GetAIPickups();

		SeedRandomDraw(0xD371F947);
		SeedRandomControl(0xD371F947);
	}
	void reset_cutseq_vars()
	{
		cutseq_num = 0;
		cutseq_trig = 0;

		GLOBAL_playing_cutseq = 0;
		GLOBAL_cutseq_frame = 0;

		SetFadeClip(0, 1);
	}
	unsigned __stdcall LoadLevel(char* filename)
	{
		Log(LT_Info, "Begin LoadLevel");

		FreeLevel();

		num_pages = 1;
		//
		fp_level = FileOpen(filename);

		if (fp_level)
		{
			int version = freadDword();
			int numRoomTex = freadWord();
			int numObjTex = freadWord();
			int numBumpTex = freadWord();

			S_InitLoadBar(numObjTex + numBumpTex + numRoomTex + 20);
			S_LoadBar();

			Log(LT_Status, "Process Level Data");
			LoadTextures(numRoomTex, numObjTex, numBumpTex);

			LaraDrawType = freadWord() + 1;
			WeatherType = freadWord();

			freadBytes(28); // padding

			int uncompSize = freadDword();
			int compSize = freadDword();

			level_data = (char*)malloc(uncompSize);
			level_data_orig = level_data;

			fread(level_data, uncompSize, 1, fp_level);

			Log(LT_Info, "Rooms");
			LoadRooms();
			S_LoadBar();

			Log(LT_Info, "Objects");
			LoadObjects();
			S_LoadBar();

			LoadSprites();
			S_LoadBar();

			LoadCameras();
			S_LoadBar();

			LoadSoundEffects();
			S_LoadBar();

			LoadBoxes();
			S_LoadBar();

			LoadAnimatedTextures();
			S_LoadBar();

			LoadTextureInfos();
			S_LoadBar();

			char* backup = level_data;
			int numItems = readDword();
			level_data += 24 * numItems;

			LoadAIObjects();
			char* backup2 = level_data;
			level_data = backup;

			LoadItems();
			level_data = backup2;

			S_LoadBar();
			S_LoadBar();

			LoadDemoData();
			S_LoadBar();

			/*if (ACMInited && !ptr_ctx->opt_DisableSound)
				LoadSamples();*/

			free(level_data_orig);

			S_LoadBar();

			for (int i = WATERFALL1; i <= WATERFALLSS2 && false; i++)
			{
				if (objects[i].loaded)
				{
					struct OBJECT_TEXTURE* tex = &object_textures[mesh_vbufs[objects[i].mesh_index]->field1[4]];
					waterfall_textures[i] = tex;
					waterfall_y[i] = tex->vertices[0].y;
				}
			}

			S_LoadBar();

			//sub_4A6AB0();
			S_LoadBar();

			MallocD3DLights();
			CreateD3DLights();
			SetupGame();
			S_LoadBar();
			SetFadeClip(0, 1);
			reset_cutseq_vars();

			if (gfCurrentLevel == LVL5_STREETS_OF_ROME)
				find_a_fucking_item(ANIMATING10)->mesh_bits = 11;

			if (gfCurrentLevel == LVL5_OLD_MILL)
				find_a_fucking_item(ANIMATING16)->mesh_bits = 1;



			//todo
			//objects[0].initialise(0);
			// todo

			FileClose(fp_level);
			Init();
			InitMatrix();
			ClearFX();
		}

		MakeCutsceneResident(gfResidentCut[0], gfResidentCut[1], gfResidentCut[2], gfResidentCut[3]);
		//
		return true;
	}

	int 		S_LoadLevelFile(int Name)
	{
		Log(LT_Enter, "S_LoadLevelFile");

		// todo

		char filename[80];
		strcpy(filename, &gfFilenameWad[gfFilenameOffset[Name]]);
		//
		strcat(filename, ".TRC");

		for (int i = 0; i < 4; i++)
		{
			BeginScene();
			InitBuckets();
			/*InitialiseSortList();
			DrawLoadingScreen();
			SortPolyList(dword_BA4384, &dword_BA4390);
			RestoreFPCW();
			DrawSortList(word_878654);
			MungeFPCW(&word_878654);*/
			S_DumpScreenFrame();
		}

		// todo thread

		LoadLevel(filename);

		Unimpl();
		return 0;
	}

	FILE* FileOpen(const char *filename)
	{
		FILE* fp;
		char fn[80];

		memset(&fn, 0, 80u);
		fn[0] = 0;
		fn[1] = 0;
		fn[2] = 0;
		strcat(fn, filename);

		Log(LT_Info, "FileOpen - %s", fn);

		fp = fopen(fn, "rb");

		if (!fp)
			Log(LT_Error, "Unable To Open %s", fn);

		return fp;
	}

	int FileClose(FILE* fp)
	{
		Log(LT_Enter, "FileClose");

		return fclose(fp);
	}

	unsigned long FileLength(FILE* nHandle)
	{
		unsigned long ret;

		fseek(nHandle, 0, SEEK_END);
		ret = ftell(nHandle);
		fseek(nHandle, 0, SEEK_SET);

		return ret;
	}

	int LoadFile(char* szFileName, void** pDest)
	{
		FILE* fp;
		int len, read;

		Log(LT_Enter, "LoadFile");
		Log(LT_Info, "File - %s", szFileName);

		fp = FileOpen(szFileName);
		if (!fp)
			return 0;

		len = FileLength(fp);

		if (!*pDest)
			*pDest = malloc(len);

		read = fread(*pDest, 1, len, fp);

		Log(LT_Info, "Read - %d FileSize - %d", read, len);

		if (read != len)
		{
			Log(LT_Error, "Error Reading File");
			FileClose(fp);
			free(*pDest);
			return 0;
		}

		FileClose(fp);
		return len;
	}

	int FindCdDrive(void)
	{
		unsigned int type;
		char root[5];
		char file_check[] = "C:\\script.dat";

		DWORD drives;
		HANDLE file;

		// WIN95: Bit mask of which drives available
		drives = GetLogicalDrives();

		cd_drive = 'A';
		lstrcpy(root, "A:\\");
		while (drives)
		{
			// WIN95: If drive letter exists, check out if it is a CD drive
			if (drives & 1)
			{
				root[0] = cd_drive;

				type = GetDriveType(root);
				if (type == DRIVE_CDROM)
				{
					// NOTE: user may have more than one CD drive, so need to check this has Tomb 2 in it
					file_check[0] = cd_drive;
					file = CreateFile(file_check, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
					if (file != INVALID_HANDLE_VALUE)
					{
						CloseHandle(file);
						return 1;
					}
				}
			}

			// Go on to next drive letter
			cd_drive++;
			drives >>= 1;
		}

		return (0);
	}

#ifdef __cplusplus
}
#endif