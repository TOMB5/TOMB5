#include "ROPE.H"

#include "CONTROL.H"
#include "LARA.H"
#include "SAVEGAME.H"
#include "SPECIFIC.H"

#if PSX_VERSION
typedef int ptrdiff_t;
#endif

void SaveRope()// (F)
{
	WriteSG((char*)&Ropes[lara.RopePtr], sizeof(struct ROPE_STRUCT));
	CurrentPendulum.Rope = (struct ROPE_STRUCT*)((char*)CurrentPendulum.Rope - (ptrdiff_t)Ropes);
	WriteSG((char*)&CurrentPendulum, sizeof(struct PENDULUM));
	CurrentPendulum.Rope = (struct ROPE_STRUCT*)((char*)CurrentPendulum.Rope + (ptrdiff_t)Ropes);
}

void LoadRope()// (F)
{
	ReadSG((char*)&Ropes[lara.RopePtr], sizeof(struct ROPE_STRUCT));
	ReadSG((char*)&CurrentPendulum, sizeof(struct PENDULUM));

	CurrentPendulum.Rope = (struct ROPE_STRUCT*)((char*)CurrentPendulum.Rope + (ptrdiff_t)Ropes);
}

void Straighten(struct ROPE_STRUCT* a1, struct PHD_VECTOR* a2, struct PHD_VECTOR* a3, long a4)
{
	UNIMPLEMENTED();
}

void StraightenRope(struct ITEM_INFO* item)// (F)
{
	short room_num = item->room_number;
	struct PHD_VECTOR v1, v2;

	v1.x = item->pos.x_pos;
	v1.y = item->pos.y_pos;
	v1.z = item->pos.z_pos;

	v1.y = GetCeiling(GetFloor(v1.x, v1.y, v1.z, &room_num), v1.x, v1.y, v1.z);

	v2.x = 0;
	v2.y = 16384;
	v2.z = 0;

	Straighten(&Ropes[nRope], &v1, &v2, 128);
}