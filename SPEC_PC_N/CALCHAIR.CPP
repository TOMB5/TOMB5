#include "CALCHAIR.H"
#include "SPECIFIC.H"
#include "LARA.H"
#include "DRAW.H"
#include "COLLIDE.H"
#include "DEBUG.H"
#include "OBJECTS.H"
#include "GAME.H"
#include "GAMEFLOW.H"
#include "HAIR.H"
#include "EFFECT2.H"
#include "CONTROL.H"
#include "CAMERA.H"

void HairControl(int unk01, int bIsYoungLara, short* frame)
{
    short* frame_;
    short anim;

    if (!frame)
    {
        if (lara.hit_direction < 0)
        {
            frame_ = GetBestFrame(lara_item);
        }
        else
        {
            switch (lara.hit_direction)
            {
                case NORTH:
                    anim = lara.IsDucked ? ANIMATION_LARA_CROUCH_SMASH_BACKWARD : ANIMATION_LARA_AH_FORWARD;
                    break;
                case EAST:
                    anim = lara.IsDucked ? ANIMATION_LARA_CROUCH_SMASH_RIGHT : ANIMATION_LARA_AH_LEFT;
                    break;
                case SOUTH:
                    anim = lara.IsDucked ? ANIMATION_LARA_CROUCH_SMASH_FORWARD : ANIMATION_LARA_AH_BACKWARD;
                    break;
                case WEST:
                    anim = lara.IsDucked ? ANIMATION_LARA_CROUCH_SMASH_LEFT : ANIMATION_LARA_AH_RIGHT;
                    break;
            }

            frame_ = &anims[anim].frame_ptr[lara.hit_frame * (anims[anim].interpolation >> 8)];
        }

        short* a0 = &frame_[9];
        struct
        {
            PHD_VECTOR pos;
            int thing;
        } things[5];

        phd_PushUnitMatrix();
        phd_SetTrans(lara_item->pos.x_pos, lara_item->pos.y_pos, lara_item->pos.z_pos);
        phd_RotYXZ(lara_item->pos.x_rot, lara_item->pos.y_rot, lara_item->pos.z_rot);
        phd_TranslateRel(frame_[6], frame_[7], frame_[8]);
        mRotSuperPackedYXZ(&a0, 0);
        phd_PushMatrix();
        phd_TranslateRel(lara.mesh_ptrs[LM_HIPS][0], lara.mesh_ptrs[LM_HIPS][1], lara.mesh_ptrs[LM_HIPS][2]);
        things[0] =
                {
                        {
                                phd_mxptr[M03] >> W2V_SHIFT,
                                phd_mxptr[M13] >> W2V_SHIFT,
                                phd_mxptr[M23] >> W2V_SHIFT
                        },
                        lara.mesh_ptrs[LM_HIPS][3]
                };
        phd_PopMatrix();
        long* bone = &bones[objects[LARA].bone_index];
        phd_TranslateRel(bone[25], bone[26], bone[27]);
        mRotSuperPackedYXZ(&a0, 6);
        phd_RotYXZ(lara.torso_y_rot, lara.torso_x_rot, lara.torso_z_rot);
        phd_PushMatrix();
        phd_TranslateRel(lara.mesh_ptrs[LM_TORSO][0], lara.mesh_ptrs[LM_TORSO][1], lara.mesh_ptrs[LM_TORSO][2]);
        things[1] =
                {
                        {
                                phd_mxptr[M03] >> W2V_SHIFT,
                                phd_mxptr[M13] >> W2V_SHIFT,
                                phd_mxptr[M23] >> W2V_SHIFT
                        },
                        lara.mesh_ptrs[LM_TORSO][3]
                };
        const auto v20 = things[1].thing;
        if (gfLevelFlags & GF_LVOP_YOUNG_LARA)
            things[1].thing = v20 - ((v20 >> 2) + (v20 >> 3)); // v20 * 5 / 8
        phd_PopMatrix();
        phd_PushMatrix();
        phd_TranslateRel(bone[29], bone[30], bone[31]);
        mRotSuperPackedYXZ(&a0, 0);
        phd_TranslateRel(lara.mesh_ptrs[LM_RINARM][0], lara.mesh_ptrs[LM_RINARM][1], lara.mesh_ptrs[LM_RINARM][2]);
        things[3] =
                {
                        {
                                phd_mxptr[M03] >> W2V_SHIFT,
                                phd_mxptr[M13] >> W2V_SHIFT,
                                phd_mxptr[M23] >> W2V_SHIFT
                        },
                        3 * lara.mesh_ptrs[LM_RINARM][3] / 2
                };
        phd_PopMatrix();

        //202
        phd_PushMatrix();
        phd_TranslateRel(bone[41], bone[42], bone[43]);
        mRotSuperPackedYXZ(&a0, 2);
        phd_TranslateRel(lara.mesh_ptrs[LM_LINARM][0], lara.mesh_ptrs[LM_LINARM][1], lara.mesh_ptrs[LM_LINARM][2]);
        things[4] =
                {
                        {
                                phd_mxptr[M03] >> W2V_SHIFT,
                                phd_mxptr[M13] >> W2V_SHIFT,
                                phd_mxptr[M23] >> W2V_SHIFT
                        },
                        3 * lara.mesh_ptrs[LM_LINARM][3] / 2
                };
        phd_PopMatrix();

        phd_TranslateRel(bone[53], bone[54], bone[55]);
        mRotSuperPackedYXZ(&a0, 2);
        phd_RotYXZ(lara.head_y_rot, lara.head_x_rot, lara.head_z_rot);
        phd_PushMatrix();
        phd_TranslateRel(lara.mesh_ptrs[LM_HEAD][0], lara.mesh_ptrs[LM_HEAD][1], lara.mesh_ptrs[LM_HEAD][2]);
        things[2] =
                {
                        {
                                phd_mxptr[M03] >> W2V_SHIFT,
                                phd_mxptr[M13] >> W2V_SHIFT,
                                phd_mxptr[M23] >> W2V_SHIFT
                        },
                        lara.mesh_ptrs[LM_HEAD][3]
                };
        phd_PopMatrix();

        if (gfLevelFlags & GF_LVOP_YOUNG_LARA)
        {
            things[1].pos.x = AVG(things[1].pos.x, things[2].pos.x);
            things[1].pos.y = AVG(things[1].pos.y, things[2].pos.y);
            things[1].pos.z = AVG(things[1].pos.z, things[2].pos.z);
        }

        if (bIsYoungLara)
        {
            phd_TranslateRel(44, -48, -50);
        }
        else if (gfLevelFlags & GF_LVOP_YOUNG_LARA)
        {
            phd_TranslateRel(-52, -48, -50);
        }
        else
        {
            phd_TranslateRel(-4, -4, -48);
        }

        PHD_VECTOR thing6 =
                {
                        phd_mxptr[M03] >> W2V_SHIFT,
                        phd_mxptr[M13] >> W2V_SHIFT,
                        phd_mxptr[M23] >> W2V_SHIFT
                };
        phd_PopMatrix();

        long* bone2 = &bones[objects[HAIR].bone_index];
        HAIR_STRUCT* hair = hairs[bIsYoungLara];

        if (first_hair[bIsYoungLara])
        {
            first_hair[bIsYoungLara] = 0;
            hair->pos.x_pos = thing6.x;
            hair->pos.y_pos = thing6.y;
            hair->pos.z_pos = thing6.z;
            auto v47 = bone2;
            for (int i = 0; i < 6; i++, v47 += 4)
            {
                phd_PushUnitMatrix();
                phd_SetTrans(hair->pos.x_pos, hair->pos.y_pos, hair->pos.z_pos);
                phd_RotYXZ(hair->pos.y_rot, hair->pos.x_rot, 0);
                phd_TranslateRel(v47[1], v47[2], v47[3]);
                hair++;
                hair->pos.x_pos = phd_mxptr[M03] >> W2V_SHIFT;
                hair->pos.y_pos = phd_mxptr[M13] >> W2V_SHIFT;
                hair->pos.z_pos = phd_mxptr[M23] >> W2V_SHIFT;
                phd_PopMatrix();
            }
            SmokeWindZ = 0;
            SmokeWindX = 0;
            hair_wind = 0;
            hair_dwind_angle = ANGLE(11.25);
            hair_wind_angle = ANGLE(11.25);
            return;
        }

        hair->pos.x_pos = thing6.x;
        hair->pos.y_pos = thing6.y;
        hair->pos.z_pos = thing6.z;

        short a4[2];

        a4[0] = lara_item->room_number;

        int v94;

        if (unk01)
            v94 = BAD_HEIGHT;
        else
            v94 = GetWaterHeight(
                    lara_item->pos.x_pos + AVG(frame_[0], frame_[1]),
                    lara_item->pos.y_pos + AVG(frame_[2], frame_[3]),
                    lara_item->pos.z_pos + AVG(frame_[4], frame_[5]),
                    a4[0]);

        hair_wind += (GetRandomControl() & 7) - 3;

        if (hair_wind >= 9)
        {
            hair_wind--;
        }
        else if (hair_wind <= -2)
        {
            hair_wind++;
        }

        hair_dwind_angle = (hair_dwind_angle + 2 * (GetRandomControl() & 0x3F) - 64) & 0x1FFE;

        if (hair_dwind_angle > 3072)
        {
            hair_dwind_angle += 6144 - 2 * hair_dwind_angle;
        }
        else if (hair_dwind_angle < 1024)
        {
            hair_dwind_angle = 2048 - hair_dwind_angle;
        }

        hair_wind_angle = ((WORD) hair_wind_angle + (WORD)((hair_dwind_angle - hair_wind_angle) >> 3)) & 0x1FFE;
        SmokeWindX = hair_wind * rcossin_tbl[hair_wind_angle] * 4 >> W2V_SHIFT;
        SmokeWindZ = hair_wind * rcossin_tbl[hair_wind_angle + 1] * 4 >> W2V_SHIFT;
        auto v92 = bone2 - 2;

        for (int k = 1; k <= 6; k++)
        {
            PHD_VECTOR old_pos{hair[k].pos.x_pos, hair[k].pos.y_pos, hair[k].pos.z_pos};

            short v60;

            if (unk01)
            {
                v60 = 0x7FFF;
            }
            else
            {
                v60 = GetHeight(GetFloor(old_pos.x, old_pos.y, old_pos.z, a4),
                                old_pos.x, old_pos.y, old_pos.z);
            }

            hair[k].pos.x_pos += hair[k].vel.x * 3 / 4;
            hair[k].pos.y_pos += hair[k].vel.y * 3 / 4;
            hair[k].pos.z_pos += hair[k].vel.z * 3 / 4;

            if (lara.water_status == LW_ABOVE_WATER && room[a4[0]].flags & RF_WIND_BLOWS_PONYTAIL)
            {
                hair[k].pos.x_pos += SmokeWindX;
                hair[k].pos.z_pos += SmokeWindZ;
            }

            switch (lara.water_status)
            {
                case LW_ABOVE_WATER:
                    hair[k].pos.y_pos += 10;
                    if (v94 == BAD_HEIGHT || hair[k].pos.y_pos <= v94)
                    {
                        if (hair[k].pos.y_pos > v60)
                        {
                            hair[k].pos.x_pos = old_pos.x;
                            hair[k].pos.z_pos = old_pos.z;
                        }
                    }
                    else
                    {
                        hair[k].pos.y_pos = v94;
                    }
                    break;

                case LW_UNDERWATER:
                case LW_SURFACE:
                case LW_WADE:
                    if (hair[k].pos.y_pos >= v94)
                    {
                        if (hair[k].pos.y_pos > v60)
                            hair[k].pos.y_pos = v60;
                    }
                    else
                    {
                        hair[k].pos.y_pos = v94;
                    }
                    break;

                default:
                    break;
            }

            auto thing = &things[0];

            for (int j = 0; j < 5; j++, thing++)
            {
                const auto dx = hair[k].pos.x_pos - thing->pos.x;
                const auto dy = hair[k].pos.y_pos - thing->pos.y;
                const auto dz = hair[k].pos.z_pos - thing->pos.z;

                const auto normsq = dx * dx + dy * dy + dz * dz;
                const auto th = thing->thing;

                if (normsq < th * th)
                {
                    auto norm = phd_sqrt_asm(normsq);

                    if (norm == 0)
                        norm = 1;

                    hair[k].pos.x_pos = thing->pos.x + dx * th / norm;
                    hair[k].pos.y_pos = thing->pos.y + dy * th / norm;
                    hair[k].pos.z_pos = thing->pos.z + dz * th / norm;
                }
            }

            const auto dx = hair[k].pos.x_pos - hair[k - 1].pos.x_pos;
            const auto dy = hair[k].pos.y_pos - hair[k - 1].pos.y_pos;
            const auto dz = hair[k].pos.z_pos - hair[k - 1].pos.z_pos;

            hair[k - 1].pos.x_rot = -phd_atan_asm(phd_hypot(dz, dx), dy);
            hair[k - 1].pos.y_rot = phd_atan_asm(dz, dx);

            phd_PushUnitMatrix();
            phd_SetTrans(hair[k - 1].pos.x_pos, hair[k - 1].pos.y_pos, hair[k - 1].pos.z_pos);
            phd_RotYXZ(hair[k - 1].pos.y_rot, hair[k - 1].pos.x_rot, 0);
            if (k == 5)
            {
                phd_TranslateRel(*(v92 - 1), *v92, v92[1]);
            }
            else
            {
                phd_TranslateRel(v92[3], v92[4], v92[5]);
            }

            v92 += 4;
            hair[k].pos.x_pos = phd_mxptr[M03] >> W2V_SHIFT;
            hair[k].pos.y_pos = phd_mxptr[M13] >> W2V_SHIFT;
            hair[k].pos.z_pos = phd_mxptr[M23] >> W2V_SHIFT;
            hair[k].vel.x = hair[k].pos.x_pos - old_pos.x;
            hair[k].vel.y = hair[k].pos.y_pos - old_pos.y;
            hair[k].vel.z = hair[k].pos.z_pos - old_pos.z;

            phd_PopMatrix();
        }
    }
}
