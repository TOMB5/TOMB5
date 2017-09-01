#include "HAIR.H"

#include "DRAW.H"
#include "OBJECTS.H"
#include "SETUP.H"

int hair_wind;
int hair_wind_angle = 2048;
int hair_dwind_angle = 2048;
int first_hair[2];
struct HAIR_STRUCT hairs[2][7];

void InitialiseHair()//3AC70, 3B170
{
	int i;
	int j;
	long* bone;
	struct HAIR_STRUCT* hptr;

	bone = &bones[objects[HAIR].bone_index];

	j = 0;

	//loc_3ACA0
	while (j < 2)
	{
		bone = &bone[4];
		hptr = &hairs[j][0];

		hptr->pos.y_rot = 0;
		hptr->pos.x_rot = ANGLE(-90);
		first_hair[j] = 1;

		i = 5;

		//loc_3ACD0
		while (i >= 0)
		{
			hptr->pos.x_pos = bone[1];
			hptr->pos.y_pos = bone[2];
			hptr->pos.z_pos = bone[3];

			hptr->pos.x_rot = ANGLE(-90);
			hptr->pos.z_rot = 0;
			hptr->pos.y_rot = 0;

			hptr->vel.x = 0;
			hptr->vel.y = 0;
			hptr->vel.z = 0;

			hptr++;
			bone = &bone[4];
			i--;
		}

		j++;
		bone = &bones[objects[HAIR].bone_index];
	}
}