#include "PRINTOBJ.H"

#include "DRAW.H"
#include "SPECIFIC.H"
#include "MATHS.H"
#include "3D_GEN.H"
#include "CONTROL.H"
#include "SETUP.H"
#include "ITEMS.H"
#include "EFFECTS.H"
#include "LOAD_LEV.H"
#include "DELTAPAK.H"
#include "DRAWOBJ.H"

void CalcAllAnimatingItems_ASM()
{
	UNIMPLEMENTED();
}

void DrawEffect(short item_num)
{
	struct FX_INFO* fx = &effects[item_num];
	struct object_info* obj = &objects[fx->object_number];

	if (obj->draw_routine != NULL && obj->loaded)
	{
		mPushMatrix();
		mTranslateAbsXYZ(fx->pos.x_pos, fx->pos.y_pos, fx->pos.z_pos);

		if (Matrix->tz < 20480)
		{
			mRotYXZ(fx->pos.y_rot, fx->pos.x_rot, fx->pos.z_rot);

			S_CalculateLight(fx->pos.x_pos, fx->pos.y_pos, fx->pos.z_pos, fx->room_number, &duff_item.il);
			duff_item.il.Light[3].pad = 0;

			phd_PutPolygons(meshes[obj->nmeshes != 0 ? obj->mesh_index : fx->frame_number], -1);
		}

		mPopMatrix();
	}
}

void PrintAllOtherObjects_ASM(short room_num)//(F)
{
	struct room_info* r = &room[room_num];

	r->bound_active = 0;

	mPushMatrix();
	mTranslateAbsXYZ(r->x, r->y, r->z);

	phd_right = 512;
	phd_bottom = 240;
	phd_left = 0;
	phd_top = 0;

	for (short item_num = r->item_number; item_num != -1; item_num = items[item_num].next_item)
	{
		struct ITEM_INFO* item = &items[item_num];
		struct object_info* obj = &objects[item->object_number];

#if _DEBUG
		if (item->object_number == LARA)
		{
			phd_PutPolygons(meshes[obj->mesh_index], -1);
		}
#endif

		if (item->status != ITEM_INVISIBLE && !obj->using_drawanimating_item && obj->draw_routine != NULL)
		{
			obj->draw_routine(item);
		}

		if (obj->draw_routine_extra != NULL)
		{
			obj->draw_routine_extra(item);
		}

		if (item->after_death < 0x80)
		{
			if (++item->after_death == 0x80) 
				KillItem(item_num);
		}
	}

	for (short item_num = r->fx_number; item_num != -1; item_num = effects[item_num].next_fx)
	{
		DrawEffect(item_num);
	}

	mPopMatrix();

	r->left = 511;
	r->top = 239;
}

void print_all_object_NOW()//8F474(<), 914B8(<) (F)
{
	CalcAllAnimatingItems_ASM();

	for (int i = 0; i < number_draw_rooms; i++)
	{
		PrintAllOtherObjects_ASM(draw_rooms[i]);
	}
}