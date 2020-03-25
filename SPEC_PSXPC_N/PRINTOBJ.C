#include "PRINTOBJ.H"

#include "EFFECTS.H"
#include "MATHS.H"
#include "LOAD_LEV.H"
#include "SETUP.H"
#include "SPECIFIC.H"
#include "DRAWOBJ.H"
#include "DRAW.H"
#include "3D_GEN.H"
#include "ITEMS.H"
#include "DELTAPAK.H"
#include "CONTROL.H"
#include "ANIMITEM.H"
#include "LIGHT.H"

#include <GTEREG.H>

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

void PrintAllOtherObjects_ASM(short room_num /*s3*/)//(F)
{
	struct room_info* r = &room[room_num];
	struct ITEM_INFO* item = NULL;
	struct object_info* object;
	short item_num;
	struct FX_INFO* effect;
	int mesh_num;
	short* mesh;
	int effect_num;

	r->bound_active = 0;
	mPushMatrix();
	mTranslateAbsXYZ(r->x, r->y, r->z);

	phd_right = 512;
	phd_bottom = 240;
	phd_left = 0;
	phd_top = 0;

	item_num = r->item_number;

	if (item_num != -1)
	{
		do
		{
			item = &items[item_num];
			object = &objects[item->object_number];

			if (item->status != 6)
			{
				if (!object->using_drawanimating_item && object->draw_routine != NULL)
				{
					object->draw_routine(item);
				}
			}
			//loc_8F5AC
			if (object->draw_routine_extra != NULL)
			{
				object->draw_routine_extra(item);
			}

			//loc_8F5C4
			if (item->after_death - 1 < 127)
			{
				item->after_death++;

				if (item->after_death == 128)
				{
					KillItem(r->item_number);
				}
			}//loc_8F5EC

			item_num = item->next_item;
		} while (item_num != -1);

	}//loc_8F5FC

	effect_num = r->fx_number;

	if (effect_num != -1)
	{
		//loc_8F608
		do
		{
			effect = &effect[effect_num];
			object = &objects[effect->object_number];

			if (object->draw_routine != NULL && object->loaded)
			{
				mPushMatrix();
				mTranslateAbsXYZ(effect->pos.x_pos, effect->pos.y_pos, effect->pos.z_pos);

				if (((int*)MatrixStack)[2] - 21 < 20459)
				{
					mRotYXZ(effect->pos.y_rot, effect->pos.x_rot, effect->pos.z_rot);

					duff_item.il.Light[3].pad = 0;
					S_CalculateLight(effect->pos.x_pos, effect->pos.y_pos, effect->pos.z_pos, effect->room_number, &duff_item.il);

					mesh_num = effect->frame_number;

					if (object->nmeshes != 0)
					{
						mesh_num = object->mesh_index;
					}//loc_8F6C0

					phd_PutPolygons(meshes[mesh_num], -1);
				}//loc_8F6D8

				mPopMatrix();

				//loc_8F6E0
				effect_num = effect->next_fx;
			}
		} while (effect_num != -1);//loc_8F6E0
	}//loc_8F6EC

	mPopMatrix();
	((int*)&r->left)[0] = 511;
	((int*)&r->top)[0] = 239;
}

void print_all_object_NOW()//8F474(<), 914B8(<) (F)
{
	CalcAllAnimatingItems_ASM();

	for (int i = 0; i < number_draw_rooms; i++)
	{
		PrintAllOtherObjects_ASM(draw_rooms[i]);
	}
}