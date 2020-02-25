#include "CONTROL_S.H"

#include "LARA.H"
#include "CAMERA.H"
#include "COLLIDE_S.H"
#include "DRAW.H"
#include "SPECIFIC.H"
#include "EFFECTS.H"
#include "CONTROL.H"
#include "LARAMISC.H"

void DrawBinoculars()
{
	S_Warn("[DrawBinoculars] - Unimplemented!\n");
}

void TranslateItem(struct ITEM_INFO* item, unsigned short x, unsigned short y, unsigned short z)
{
	short sin;//$v1
	short cos;//$t0

	cos = COS(item->pos.y_rot);
	sin = SIN(item->pos.y_rot);

	item->pos.x_pos += ((cos * x) + (sin * z)) >> W2V_SHIFT;
	item->pos.y_pos += y;
	item->pos.z_pos += ((-sin * x) + (cos * z)) >> W2V_SHIFT;
}

int GetChange(struct ITEM_INFO* item, struct ANIM_STRUCT* anim)//7D48C
{
	struct CHANGE_STRUCT* change = NULL;//$t1
	struct RANGE_STRUCT* range = NULL;//$v1
	int i = 0;//$t2
	int j = 0;//$t0

	if (item->current_anim_state != item->goal_anim_state)
	{
		change = &changes[anim->change_index];

		if (anim->number_changes > 0)
		{
			//loc_7D4C4
			do
			{
				if (change->goal_anim_state == item->goal_anim_state)
				{
					range = &ranges[change->range_index];
					if (change->number_ranges > 0)
					{
						//loc_7D4E4
						do
						{
							if (item->frame_number < range->start_frame && range->end_frame >= item->frame_number)
							{
								//loc_7D4FC
								j++;
								range++;

							}
							else
							{
								//loc_7D524
								item->anim_number = range->link_anim_num;
								item->frame_number = range->link_frame_num;
								return 1;
							}
						} while (j < change->number_ranges);
					}
					//loc_7D50C
				}//loc_7D50C
				change++;
			} while (++i < anim->number_changes);
		}//locret_7D51C
	}//locret_7D51C

	return 0;
}

void AnimateLara(struct ITEM_INFO* item /* s1 */)//7D53C(<)
{
	struct ANIM_STRUCT* anim = &anims[item->anim_number];//$s2
	unsigned short* command;//$s0
	unsigned short data;//$v0
	int numAnimCommands;
	int i;
	int velocity;//$s0
	int speed;//$v0;
	short sin;//$v0
	short cos;//$at

	item->frame_number += 1;

	if (anim->number_changes > 0 && GetChange(item, anim))
	{
		anim = &anims[item->anim_number];
		item->current_anim_state = anim->current_anim_state;
	}
	//loc_7D5BC
	if (anim->frame_end < item->frame_number)
	{
		numAnimCommands = anim->number_commands;
		if (anim->number_commands > 0)
		{
			command = (unsigned short*)&commands[anim->command_index];

			//loc_7D5EC
			do
			{
				data = *command++;

				if (data - 1 == 0)
				{
					//loc_7D628
					TranslateItem(item, command[0], command[1], command[2]);
					command += 3;
					UpdateLaraRoom(item, -381);
				}
				else if (data - 2 == 0)
				{
					//loc_7D650
					item->gravity_status = 1;
					item->fallspeed = command[0];
					item->speed = command[1];
					command += 2;

					if (lara.calc_fallspeed != 0)
					{
						item->fallspeed = lara.calc_fallspeed;
						lara.calc_fallspeed = 0;
					}
				}
				else if (data - 3 == 0)
				{
					//loc_7D684
					if (lara.gun_status != 5)
					{
						lara.gun_status = 0;
					}
				}
				else if (data - 5 == 0 || data - 6 == 0)
				{
					//loc_7D620
					command += 2;
				}

				//loc_7D698
			} while (--numAnimCommands > 0);
		}
		//loc_7D6A4
		item->anim_number = anim->jump_anim_num;
		item->frame_number = anim->jump_frame_num;

		anim = &anims[anim->jump_anim_num];
		item->current_anim_state = anim->current_anim_state;
	}
	
	//loc_7D6D4
	i = anim->number_commands;
	if (anim->number_commands > 0)
	{
		command = (unsigned short*)&commands[anim->command_index];

		//loc_7D6EC
		do
		{
			data = *command++;

			if (data - 2 == 0)
			{
				//loc_7D7B8
				command += 2;
			}
			else if (data - 5 == 0)
			{
				//loc_7D720
				if (item->frame_number == command[0])
				{
					if ((command[1] & 0xC000))
					{
						if ((command[1] & 0xC000) != 0x4000 || lara.water_surface_dist < 0 &&
							lara.water_surface_dist != -32512)
						{
							//loc_7D754
							if ((command[1] & 0xC000) != 0x8000 || lara.water_surface_dist >= 0 || lara.water_surface_dist == -32512)
							{
								//loc_7D7B8
								command += 2;
							}
						}

					}//loc_7D76C
				}
				else
				{
					//loc_7D7B8
					command += 2;
				}
				//loc_7D76C
				SoundEffect((command[1] & 0x3FFF), &item->pos, 2);
			}
			else if (data - 6 == 0)
			{
				//loc_7D780
				if (item->frame_number == command[0])
				{
					FXType = (command[1] & 0xC000);
					effect_routines[command[1] & 0x3FFF](item);
				}
				else
				{
					//loc_7D7B8
					command += 2;
				}
			}
			else if (data - 1 == 0)
			{
				command += 3;
			}

			//loc_7D7BC
		} while (--i > 0);
	}
	
	//loc_7D7C8
	velocity = anim->Xvelocity;

	if (anim->Xacceleration != 0)
	{
		velocity += anim->Xacceleration * (item->frame_number - anim->frame_base);
	}
	//loc_7D7EC
	velocity >>= 16;
	if (!item->gravity_status)
	{
		speed = anim->velocity >> 16;
		if (anim->acceleration != 0)
		{
			speed = (anim->velocity + (anim->acceleration * (item->frame_number - anim->frame_base))) >> 16;
		}

		item->speed = speed;
	}
	else
	{
		//loc_7D828
		item->speed = item->speed - ((anim->velocity + (anim->acceleration * (item->frame_number - 1))) >> 16) + ((anim->velocity + (anim->acceleration * (item->frame_number - 1)) + anim->acceleration) >> 16);

		if (item->fallspeed < 128)
		{
			item->fallspeed += 6;
		}
		else
		{
			item->fallspeed += 1;
		}

		//loc_7D870
		item->pos.y_pos += item->fallspeed;
	}
	//loc_7D884
	if (lara.RopePtr != -1)
	{
		DelAlignLaraToRope(item);
	}

	//loc_7D89C
	if (!lara.IsMoving)
	{
		item->pos.x_pos = (item->pos.x_pos + ((SIN(lara.move_angle) * item->speed) >> W2V_SHIFT)) + (((SIN(lara.move_angle) * item->speed) >> W2V_SHIFT) >> W2V_SHIFT);
		item->pos.z_pos = (item->pos.z_pos + ((COS(lara.move_angle) * item->speed) >> W2V_SHIFT)) + ((COS(lara.move_angle + 16384) * velocity) >> W2V_SHIFT);
	}
	//loc_7D934
}