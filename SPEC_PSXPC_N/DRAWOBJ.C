#include "DRAWOBJ.H"

#include "SPECIFIC.H"
#include "LIBGPU.H"
#include "EMULATOR.H"
#include "GPU.H"

void MakeMono(unsigned short* s, unsigned char* d)//7F9E4
{
	S_Warn("[MakeMono] - Unimplemented!\n");
}

void InitObjGTE()
{
	S_Warn("[InitObjGTE] - Unimplemented!\n");
}

void DrawClippedMesh(int vertcache, short* mesh, MMTEXTURE* text, char* ot, char* prim, char* prim_lim, long fp, long prim_len, long num_tri)
{
	UNIMPLEMENTED();
}

void DrawSubDivMesh()
{
	UNIMPLEMENTED();
}

void initialise_light_matrix()
{
	UNIMPLEMENTED();
}

void phd_PutPolygons_normal(short* mesh, short clip)
{
	initialise_light_matrix();

	mesh_header* mptr = (mesh_header*)mesh;

#if GLTEST
	Emulator_TestDrawVertices(mesh, RoomTextInfo);
#endif
	UNIMPLEMENTED();
}

void phd_PutPolygons_pickup(short* mesh, short clip)
{
	UNIMPLEMENTED();
}

void phd_PutPolygons_seethrough(short* mesh, short clip)
{
	UNIMPLEMENTED();
}

void phd_PutPolygons_train(short* mesh, short clip)
{
	UNIMPLEMENTED();
}

void phd_PutPolygons(short* mesh, short clip)
{
	phd_PutPolygons_normal(mesh, clip);
}