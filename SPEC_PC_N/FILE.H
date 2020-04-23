#ifndef FILE_H
#define FILE_H

#include <cstdio>
#include "SPECTYPES.H"

#ifdef __cplusplus
//extern "C" {
#endif

int S_LoadLevelFile(int Name);

int LoadFile(const char* szFileName, void** pDest);

int FindCdDrive(void);

FILE* FileOpen(const char* filename);

int FileClose(FILE* fp);

unsigned long FileLength(FILE* nHandle);

void FreeD3DLights();

void FreeLevel();

NEW_CUTSCENE* FetchCutData(int num);

NEW_CUTSCENE* ReadCutData(int num, FILE* fp);

#ifdef __cplusplus
//}
#endif
#define MAX_ROOM_LIGHTS 21
extern FILE* acm_file_stream;
extern OBJECT_TEXTURE* object_textures;
extern room_light_begin fog_bulb[40];
extern short* floor_data;
extern short* mesh_base;

extern int num_pages;
extern bool levelLoading;
extern SPRITE_STRUCT* sprites;
extern int AnimFileLen;
extern LPDIRECTDRAWSURFACE4 surf_screen;

#pragma pack(push, 1)
struct mesh_thing
{
	tr5_vertex pos;
	tr5_vertex norm;
	int f6, f7;
};

struct tr4_mesh
{
	tr_vertex center;
	int coll_radius;
	short num_vert;
	short num_normals;
	short num_rectangles;
	tr4_mesh_face4* rectangles;
	short num_triangles;
	tr4_mesh_face3* triangles;
	int* lights;
	LPDIRECT3DVERTEXBUFFER vbuf;
	void* normals;
	int attributes;
	mesh_thing* vert;
	bounding_box_f bbox;
};
#pragma pack(pop)

#endif