#include "HAIR.H"

#include "DRAW.H"
#include "OBJECTS.H"
#ifdef PC_VERSION
#include "GAME.H"
#else
#include "SETUP.H"
#endif

int hair_wind;
int hair_wind_angle = 2048;
int hair_dwind_angle = 2048;
int first_hair[2];
struct HAIR_STRUCT hairs[2][7];

void InitialiseHair()//3AC70, 3B170 (F)
{
	int i;
	int j;
	long* bone;
	struct HAIR_STRUCT* hptr;

	bone = &bones[objects[HAIR].bone_index + 4];

	//loc_3ACA0
	for(j = 0; j < 2; j++)
	{
		hptr = &hairs[j][0];

		hptr->pos.y_rot = 0;
		hptr->pos.x_rot = ANGLE(-90);
		first_hair[j] = 1;

		//loc_3ACD0
		for(i = 0; i < 7; i++)
		{
			hptr->pos.x_pos = bone[1];
			hptr->pos.y_pos = bone[2];
			hptr->pos.z_pos = bone[3];

			hptr->pos.x_rot = ANGLE(-90);
			hptr->pos.y_rot = 0;
			hptr->pos.z_rot = 0;

			hptr->vel.x = 0;
			hptr->vel.y = 0;
			hptr->vel.z = 0;

			hptr++;
			bone += 4;
		}

		bone = &bones[objects[HAIR].bone_index];
	}
}