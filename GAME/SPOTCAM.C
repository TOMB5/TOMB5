#include "SPOTCAM.H"

#include "CONTROL.H"
#include "DELTAPAK.H"
#include "GAMEFLOW.H"
#include "LARA.H"
#if PSXENGINE
#include "MATHS.H"
#include "GETSTUFF.H"
#else
#include "GLOBAL.H"
#endif
#include "OBJECTS.H"
#include INPUT_H
#include "SPECIFIC.H"
#include "SPOTCAM.H"
#include "SWITCH.H"
#include "TOMB4FX.H"

#include <assert.h>

#if PSXPC_VERSION || PC_VERSION
	#include <math.h>
#elif PSX_VERSION
	#include <LIBMATH.H>
#endif

#include <stdio.h>

int bUseSpotCam = 0;
int bDisableLaraControl = 0;
int bTrackCamInit = 0;
char SCOverlay = 0;
char SCNoDrawLara = 0;
char SniperOverlay = 0;
short spotcam_timer = 0;
int bCheckTrigger = 0;
short LastSequence;
short CurrentFov;
short spotcam_loopcnt;
short number_spotcams;
#if PC_VERSION
struct SPOTCAM SpotCam[255];
#else
struct SPOTCAM* SpotCam;
#endif
unsigned char CameraCnt[16];
unsigned char SpotRemap[16];
long current_spline_position;
short LastFov;
int CameraFade;
int LaraHealth;
int LaraAir;
long camera_xposition[18];
long camera_yposition[18];
long camera_zposition[18];
long camera_xtarget[18];
long camera_ytarget[18];
long camera_ztarget[18];
long camera_roll[18];
long camera_fov[18];
long camera_speed[18];
short current_spline_camera;
short current_camera_cnt;
short current_sequence;
short first_camera;
short last_camera;
int spline_from_camera;
int spline_to_camera;
struct PHD_VECTOR InitialCameraPosition;
struct PHD_VECTOR InitialCameraTarget;
struct PHD_VECTOR LaraFixedPosition;
short InitialCameraRoom;
struct QUAKE_CAM quakecam;

long dword_A0AC4;

void InitSpotCamSequences()//374B8(<), 379B8(<) (F)
{
	int s, cc, n, ce;

	n = number_spotcams;
	cc = 1;

	bTrackCamInit = 0;

	if (n != 0)
	{
		ce = 0;
		s = SpotCam[0].sequence;

		if (cc < n)
		{
			for (n = 1; n < number_spotcams; n++)
			{
				//Same sequence
				if (SpotCam[n].sequence == s)
				{
					cc++;
				}
				else
				{
					//New sequence
					CameraCnt[ce] = cc;
					cc = 1;
					SpotRemap[s] = ce;
					ce++;
					s = SpotCam[n].sequence;
				}
			}
		}

		CameraCnt[ce] = cc;
		SpotRemap[s] = ce;
	}

	return;
}

void InitialiseSpotCam(short Sequence)//37648, 37B48 (F)
{
	struct SPOTCAM* s;
	int cn;
	int sp;
	int i;

	if (bTrackCamInit != 0 && LastSequence == Sequence)
	{
		bTrackCamInit = 0;
		return;
	}

	//loc_37B94
	BinocularRange = 0;
	LaserSight = 0;

	AlterFOV(16380);

	lara_item->mesh_bits = 0xFFFFFFFF;

	lara.head_x_rot = 0;
	lara.head_y_rot = 0;

	lara.torso_x_rot = 0;
	lara.torso_y_rot = 0;

	camera.bounce = 0;

	lara.look = 0;
	CameraFade = -1;
	LastSequence = Sequence;
	bTrackCamInit = 0;
	spotcam_timer = 0;
	spotcam_loopcnt = 0;
	bDisableLaraControl = 0;

	LastFov = CurrentFov;
	LaraAir = lara.air;

	InitialCameraPosition.x = camera.pos.x;
	InitialCameraPosition.y = camera.pos.y;
	InitialCameraPosition.z = camera.pos.z;

	InitialCameraTarget.x = camera.target.x;
	InitialCameraTarget.y = camera.target.y;
	InitialCameraTarget.z = camera.target.z;

	LaraHealth = lara_item->hit_points;
	InitialCameraRoom = camera.pos.room_number;

	LaraFixedPosition.x = lara_item->pos.x_pos;
	LaraFixedPosition.y = lara_item->pos.y_pos;
	LaraFixedPosition.z = lara_item->pos.z_pos;

	current_sequence = Sequence;
	current_spline_camera = 0;

	if (SpotRemap[Sequence] != 0)
	{
		//loc_377C0
		for (i = 0; i < SpotRemap[Sequence]; i++)
		{
			current_spline_camera += CameraCnt[i];
		}
	}

	//loc_377E0
	current_spline_position = 0;
	spline_to_camera = 0;

	first_camera = current_spline_camera;

	s = &SpotCam[current_spline_camera];

	last_camera = current_spline_camera + (CameraCnt[SpotRemap[Sequence]] + -1);
	current_camera_cnt = CameraCnt[SpotRemap[Sequence]];

	if ((s->flags & SCF_DISABLE_LARA_CONTROLS) || gfGameMode == 1)
	{
		//loc_37868
		bDisableLaraControl = 1;
		if (gfGameMode != 1)
		{
			SetFadeClip(16, 1);
		}	
	}

	//loc_37888
	if (s->flags & SCF_TRACKING_CAM)
	{
		camera_xposition[0] = SpotCam[first_camera].x;
		camera_yposition[0] = SpotCam[first_camera].y;
		camera_zposition[0] = SpotCam[first_camera].z;

		camera_xtarget[0] = SpotCam[first_camera].tx;
		camera_ytarget[0] = SpotCam[first_camera].ty;
		camera_ztarget[0] = SpotCam[first_camera].tz;

		camera_xtarget[0] = SpotCam[first_camera].tx;
		camera_ytarget[0] = SpotCam[first_camera].ty;
		camera_ztarget[0] = SpotCam[first_camera].tz;

		camera_roll[0] = SpotCam[first_camera].roll;
		camera_fov[0] = SpotCam[first_camera].fov;

		spline_from_camera = 0;
		camera_speed[0] = SpotCam[first_camera].speed;

		if (current_camera_cnt > 0)//NV!
		{
			s = &SpotCam[first_camera];
			//loc_37960
			for (i = 1; i < current_camera_cnt + 1; i++, s++)
			{
				camera_xposition[i] = s->x;
				camera_yposition[i] = s->y;
				camera_zposition[i] = s->z;

				camera_xtarget[i] = s->tx;
				camera_ytarget[i] = s->ty;
				camera_ztarget[i] = s->tz;

				camera_xtarget[i] = s->tx;
				camera_ytarget[i] = s->ty;
				camera_ztarget[i] = s->tz;

				camera_roll[i] = s->roll;
				camera_fov[i] = s->fov;
				camera_speed[i] = s->speed;
			}
		}
		
		//loc_379F8
		camera_xposition[1] = SpotCam[last_camera].x;
		camera_yposition[1] = SpotCam[last_camera].y;
		camera_zposition[1] = SpotCam[last_camera].z;

		camera_xtarget[1] = SpotCam[last_camera].tx;
		camera_ytarget[1] = SpotCam[last_camera].ty;
		camera_ztarget[1] = SpotCam[last_camera].tz;

		camera_fov[1] = SpotCam[last_camera].fov;
		camera_roll[1] = SpotCam[last_camera].roll;
		camera_speed[1] = SpotCam[last_camera].speed;
	}
	else
	{
		//loc_37AA8
		sp = 1;
		if ((s->flags & SCF_CUT_PAN))
		{
			camera_xposition[0] = SpotCam[current_spline_camera].x;
			camera_yposition[0] = SpotCam[current_spline_camera].y;
			camera_zposition[0] = SpotCam[current_spline_camera].z;

			camera_xtarget[0] = SpotCam[current_spline_camera].tx;
			camera_ytarget[0] = SpotCam[current_spline_camera].ty;
			camera_ztarget[0] = SpotCam[current_spline_camera].tz;
			
			camera_roll[0] = SpotCam[current_spline_camera].roll;
			camera_fov[0] = SpotCam[current_spline_camera].fov;
			camera_speed[0] = SpotCam[current_spline_camera].speed;

			spline_from_camera = 0;

			//loc_37B64
			cn = current_spline_camera;
			while (sp < 4)
			{
				if (last_camera < current_spline_camera)
				{
					cn = first_camera;
				}

				//loc_37B74
				camera_xposition[sp] = SpotCam[cn].x;
				camera_yposition[sp] = SpotCam[cn].y;
				camera_zposition[sp] = SpotCam[cn].z;

				camera_xtarget[sp] = SpotCam[cn].tx;
				camera_ytarget[sp] = SpotCam[cn].ty;
				camera_ztarget[sp] = SpotCam[cn].tz;

				camera_roll[sp] = SpotCam[cn].roll;
				camera_fov[sp] = SpotCam[cn].fov;
				camera_speed[sp] = SpotCam[cn].speed;
				cn++;
				sp++;
			}

			current_spline_camera++;

			if (current_spline_camera < last_camera)
			{
				current_spline_camera = first_camera;
			}

			//loc_37C4C
			if (s->flags & SCF_ACTIVATE_HEAVY_TRIGGERS)
			{
				bCheckTrigger = 1;
			}

			//loc_37C64
			if (s->flags & SCF_VIGNETTE)
			{
				if (s->timer < 0)
				{
					SCOverlay = 1;
				}//loc_37C8C
				else if (SlowMotion == 0)
				{
					SlowMotion = s->timer;
				}
			}

			//loc_37CA8
			if (s->flags & SCF_HIDE_LARA)
			{
				SCNoDrawLara = 1;
			}//loc_37EA8
			else
			{
				quakecam.spos.box_number = 0;
				return;
			}

		}
		else
		{
			//loc_37CC8
			cn = current_spline_camera;

			camera_roll[0] = 0;
			camera_xposition[0] = InitialCameraPosition.x;
			camera_yposition[0] = InitialCameraPosition.y;
			camera_zposition[0] = InitialCameraPosition.z;
			camera_xtarget[0] = InitialCameraTarget.x;
			camera_ytarget[0] = InitialCameraTarget.y;
			camera_ztarget[0] = InitialCameraTarget.z;
			camera_fov[0] = CurrentFov;

			camera_xposition[1] = InitialCameraPosition.x;
			camera_xtarget[1] = InitialCameraTarget.x;
			camera_yposition[1] = InitialCameraPosition.y;
			camera_zposition[1] = InitialCameraPosition.z;
			camera_ytarget[1] = InitialCameraTarget.y;
			camera_ztarget[1] = InitialCameraTarget.z;
			camera_roll[1] = 0;
			camera_fov[1] = 0;

			camera_speed[0] = s->speed;
			camera_speed[1] = s->speed;

			camera_xposition[2] = SpotCam[current_spline_camera].x;
			camera_yposition[2] = SpotCam[current_spline_camera].y;
			camera_zposition[2] = SpotCam[current_spline_camera].z;

			spline_from_camera = 1;

			camera_xtarget[2] = SpotCam[current_spline_camera].tx;
			camera_ytarget[2] = SpotCam[current_spline_camera].ty;
			camera_ztarget[2] = SpotCam[current_spline_camera].tz;

			camera_roll[2] = SpotCam[current_spline_camera].roll;
			camera_fov[2] = SpotCam[current_spline_camera].fov;
			

			camera_speed[2] = SpotCam[current_spline_camera].speed;

			cn++;

			if (last_camera < cn)
			{
				cn = first_camera;
			}
			
			//loc_37DF4
			camera_xposition[3] = SpotCam[cn].x;
			camera_yposition[3] = SpotCam[cn].y;
			camera_zposition[3] = SpotCam[cn].z;

			camera_xtarget[3] = SpotCam[cn].tx;
			camera_ytarget[3] = SpotCam[cn].ty;
			camera_ztarget[3] = SpotCam[cn].tz;

			camera_roll[3] = SpotCam[cn].roll;
			camera_fov[3] = SpotCam[cn].fov;
			camera_speed[3] = SpotCam[cn].speed;
		}
	}

	//loc_37E90
	if (s->flags & SCF_HIDE_LARA)
	{
		SCNoDrawLara = 1;
	}

	//loc_37EA8
	quakecam.spos.box_number = 0;

	//loc_37EAC
	return;
}


void CalculateSpotCams()//37ED0(<), ? 
{
#if !PC_VERSION
	long cpx; // stack offset -96
	long cpy; // stack offset -92
	long cpz; // stack offset -88
	long ctx; // stack offset -84
	long cty; // stack offset -80
	long ctz; // stack offset -76
	long cspeed; // stack offset -72
	long cfov; // stack offset -68
	long croll; // stack offset -64
	struct SPOTCAM *s; // stack offset -60
	short spline_cnt; // $s3
	int next_spline_camera; // $s0
	int n; // $s5
	static int bFirstLook; // offset 0x18 dword_A0AC4?
	long dx; // $v1
	long dy; // $s0
	long dz; // $s1

	//{ // line 76, offset 0x38114
	long cs; // $s6
	long sp; // $s2
	long cp; // $fp
	long clen; // $s4
	long tlen; // $v1
	long cx; // $s1
	long cy; // $s0
	long cz; // $v0
	long lx; // stack offset -56
	long lz; // stack offset -52
	long ly; // stack offset -48
	int i; // $v1
	int var_2C;

	//} // line 142, offset 0x382c4

	//{ // line 1, offset 0x386ac
		//{ // line 1, offset 0x386ac
	int ctype; // $s0
		// // line 1, offset 0x38760
	//} // line 1, offset 0x38760

	//{ // line 396, offset 0x38a50
		//int sp; // $s5
	int cn = 0; // $s0
	//} // line 396, offset 0x38a50

	//{ // line 1, offset 0x38b04
	//int sp = 0; // $s5
	//	int cn; // $s0
	//} // line 1, offset 0x38b04

	{ // line 1, offset 0x38c2c

	} // line 1, offset 0x38c2c

	{ // line 439, offset 0x38d68
		struct CAMERA_INFO Backup; // stack offset -216
		{ // line 441, offset 0x38d68

		} // line 441, offset 0x38d68
		{ // line 441, offset 0x38d68
		} // line 441, offset 0x38d68
	} // line 441, offset 0x38d68
	{ // line 1, offset 0x38ff0
		{ // line 1, offset 0x38ff0
			int ctype; // $s0
		} // line 1, offset 0x390a0
	} // line 1, offset 0x390a0
	printf("CX:%d, CY:%d CZ:%d CR:%d\n", camera.pos.x, camera.pos.y, camera.pos.z, camera.pos.room_number);
	if (bDisableLaraControl)
	{
		lara_item->hit_points = LaraHealth;
		lara.air = LaraAir;
	}

	//loc_37F20
	s = &SpotCam[first_camera];
	spline_cnt = 4;

	if ((s->flags & SCF_TRACKING_CAM))
	{
		spline_cnt = current_camera_cnt + 2;
	}

	//loc_37F64
	cpx = Spline(current_spline_position, &camera_xposition[0], spline_cnt);
	cpy = Spline(current_spline_position, &camera_yposition[0], spline_cnt);
	cpz = Spline(current_spline_position, &camera_zposition[0], spline_cnt);

	ctx = Spline(current_spline_position, &camera_xtarget[0], spline_cnt);
	cty = Spline(current_spline_position, &camera_ytarget[0], spline_cnt);
	ctz = Spline(current_spline_position, &camera_ztarget[0], spline_cnt);

	cspeed = Spline(current_spline_position, &camera_speed[0], spline_cnt);
	croll = Spline(current_spline_position, &camera_roll[0], spline_cnt);
	cfov = Spline(current_spline_position, &camera_fov[0], spline_cnt);

	if ((SpotCam[current_spline_camera].flags & SCF_SCREEN_FADE_IN) && CameraFade != current_spline_camera)
	{
		CameraFade = current_spline_camera;

		if (gfCurrentLevel != LVL5_TITLE)
		{
			ScreenFadedOut = 0;
			ScreenFade = 255;
			dScreenFade = 0;
			SetScreenFadeIn(16);
		}
	}//loc_38084

	if ((SpotCam[current_spline_camera].flags & SCF_SCREEN_FADE_OUT) && CameraFade != current_spline_camera)
	{
		CameraFade = current_spline_camera;

		if (gfCurrentLevel != LVL5_TITLE)
		{
			ScreenFadedOut = 0;
			ScreenFade = 0;
			dScreenFade = 255;
			SetScreenFadeOut(16, 0);
		}
	}
	//loc_380F8
	//v1 = s;
	//v0 = s->flags;
	sp = 0;

	if ((s->flags & SCF_TRACKING_CAM))
	{
		long s7;
		long v0;

		//v0 = lara_item;
		//a0 = lara_item->pos.x_pos;
		cp = 0;
		lx = lara_item->pos.x_pos;
		cs = 0x2000;
		ly = lara_item->pos.y_pos;
		tlen = 0;
		lz = lara_item->pos.z_pos;

		//loc_38144
		while (var_2C < 8)
		{
			clen = 1;
			n = 0;
			s7 = cs >> 1;
			tlen++;
			var_2C = 1;

			//loc_38158
			for (n = 0; n < 8; n++)
			{
				cx = Spline(sp, &camera_xposition[0], spline_cnt);
				cy = Spline(sp, &camera_yposition[0], spline_cnt);
				cz = Spline(sp, &camera_zposition[0], spline_cnt);

				dx = (cx - lx) * (cx - lx);
				dz = (cz - lz) * (cz - lz);//v0
				dy = (cy - ly) * (cy - ly);//s0

				tlen = phd_sqrt_asm(dx + dz + dy);

				if (tlen > clen)
				{
					cp = sp;
					clen = tlen;
				}//loc_381F0

				sp = cs;
				//v0 = 0x10000;
				//v0 = 0x10000 < sp ? 1 : 0

				v0 = s7 >> 1;

				if (0x10000 < sp)
				{
					//loc_38214
					break;
				}
			}

			v0 <<= 2;

			sp = cp - v0;
			cs = s7;

			if (sp < 0)
			{
				sp = 0;
			}//loc_38228

			//v1 = var_2c;
		}

		current_spline_position += (cp - current_spline_position) >> 5;
		if ((s->flags & SCF_CUT_PAN))
		{
			if ((cp - current_spline_position) >= 0 && 0x8000 < (cp - current_spline_position))
			{
				current_spline_position = cp;
			}
			else
			{
				if (0x8000 < (current_spline_position - cp))
				{
					current_spline_position = cp;
				}
			}
		}
		//loc_3829C
		if (current_spline_position < 0)
		{
			current_spline_position = 0;
		}//loc_382B4

		if (0x10000 < current_spline_position)
		{
			current_spline_position = 0x10000;
		}//loc_382F4
	}
	else
	{
		//loc_382D0
		if (spotcam_timer == 0)
		{
			current_spline_position += cspeed;
		}
	}

	//loc_382F4
	if (!(input & IN_LOOK))
	{
		dword_A0AC4 = 0;
	}

	//loc_38310
	if ((s->flags & SCF_DISABLE_BREAKOUT) && (input & IN_LOOK) && gfGameMode != 1)
	{
		if ((s->flags & SCF_TRACKING_CAM))
		{
			if (dword_A0AC4 == 0)
			{
				camera.old_type = FIXED_CAMERA;
				dword_A0AC4 = 1;
			}//loc_3836C

			CalculateCamera();

			return;
		}
		else
		{
			//loc_3837C
			SetFadeClip(0, 1);
			bUseSpotCam = 0;
			bDisableLaraControl = 0;
			camera.speed = 1;

			AlterFOV(LastFov);
			CalculateCamera();
			bCheckTrigger = 0;

			return;
		}
	}
	//loc_383B4
	camera.pos.x = cpx;
	camera.pos.y = cpy;
	camera.pos.z = cpz;

	if ((s->speed & 0x280000))
	{
		ctx = lara_item->pos.x_pos;
		cty = lara_item->pos.y_pos;
		ctz = lara_item->pos.z_pos;
	}

	//loc_38420
	camera.target.x = ctx;
	camera.target.y = ctx;
	camera.target.z = ctz;

	IsRoomOutsideNo = -1;
	IsRoomOutside(cpx, cpy, cpz);

	if (IsRoomOutsideNo != -1)
	{
		camera.pos.room_number = IsRoomOutsideNo;
	}
	else
	{
		//loc_38490
		camera.pos.room_number = SpotCam[current_spline_camera].room_number;
		GetFloor(camera.pos.x, camera.pos.y, camera.pos.z, &camera.pos.room_number);
	}

	//loc_384DC
	AlterFOV(cfov);

	if (quakecam.spos.box_number != 0)
	{
		dx = (camera.pos.x - quakecam.epos.x);
		dy = (camera.pos.y - quakecam.epos.y);
		dz = (camera.pos.z - quakecam.epos.z);


		if (phd_sqrt_asm(dx * dy * dz) < quakecam.epos.box_number)
		{
			dz = quakecam.spos.room_number + (((quakecam.epos.room_number - quakecam.spos.room_number) * -quakecam.epos.box_number) / quakecam.epos.box_number) >> 1;//s1
			dy = quakecam.spos.room_number + (((quakecam.epos.room_number - quakecam.spos.room_number) * -quakecam.epos.box_number) / quakecam.epos.box_number);//s0
			if (dy > 0)
			{
				camera.pos.x += (GetRandomControl() / dy) - dz;
				camera.pos.y += (GetRandomControl() / dy) - dz;
				camera.pos.z += (GetRandomControl() / dy) - dz;
			}//loc_38650
		}//loc_38650
	}//loc_38650

#if PSXENGINE
	phd_LookAt(camera.pos.x, camera.pos.y, camera.pos.z, camera.target.x, camera.target.y, camera.target.z, croll);
#endif
#if 0
	lw      $a3, camera.target.x
		lw      $v0, 0xF8 + var_40($sp)//croll?
		lw      $v1, camera.target.y
		lw      $t0, camera.target.z
		sll     $s0, $v0, 16
		sra     $v0, $s0, 16
		sw      $v0, 0xF8 + var_E0($sp)
		sw      $v1, 0xF8 + var_E8($sp)
		sw      $t0, 0xF8 + var_E4($sp)
		phd_LookAt();
#endif

	///sp = s0
	if (bCheckTrigger)
	{
		ctype = camera.type;
		camera.type = HEAVY_CAMERA;

		if (gfCurrentLevel != LVL5_TITLE)
		{
			TestTriggersAtXYZ(camera.pos.x, camera.pos.y, camera.pos.z, camera.pos.room_number, 1, 0);
		}
		else
		{
			//loc_38704
			TestTriggersAtXYZ(camera.pos.x, camera.pos.y, camera.pos.z, camera.pos.room_number, 0, 0);
			TestTriggersAtXYZ(camera.pos.x, camera.pos.y, camera.pos.z, camera.pos.room_number, 1, 0);
		}

		camera.type = (enum camera_type)ctype;
	}//loc_3876C

	if ((s->flags & SCF_TRACKING_CAM))
	{
		bTrackCamInit = 1;
		return;
	}

	if (current_spline_position > 0xFFFF)
	{
		return;
	}

	if ((SpotCam[current_spline_camera].flags & SCF_VIGNETTE))
	{
		if (SpotCam[current_spline_camera].timer < 0)
		{
			SCOverlay = 1;
		}
		else
		{
			//loc_387F8
			if (SlowMotion == 0)
			{
				SlowMotion = 1;
			}
		}
	}//loc_38814

	if ((SpotCam[current_spline_camera].flags & SCF_HIDE_LARA))
	{
		SCNoDrawLara = 1;
	}
	//loc_38844

	if ((SpotCam[current_spline_camera].flags & SCF_ACTIVATE_HEAVY_TRIGGERS))
	{
		bCheckTrigger = 1;
	}

	//loc_3885C
	if ((SpotCam[current_spline_camera].flags & SCF_STOP_MOVEMENT))
	{
		if (quakecam.spos.box_number != 0 && SpotCam[current_spline_camera].timer != -1)
		{
			//loc_38990
			quakecam.spos.box_number = 0;
		}
		else
		{
			//loc_38888
			quakecam.spos.x = SpotCam[current_spline_camera].x;
			quakecam.spos.y = SpotCam[current_spline_camera].y;
			quakecam.spos.z = SpotCam[current_spline_camera].z;

			if (SpotCam[current_spline_camera].timer != -1)
			{
				quakecam.spos.room_number = SpotCam[current_spline_camera].timer << 3;
			}
			else
			{
				//loc_388C8
				quakecam.spos.room_number = 0;
			}
			//loc_388CC
			quakecam.spos.box_number = 1;
			quakecam.epos.x = SpotCam[current_spline_camera + 1].x;
			quakecam.epos.y = SpotCam[current_spline_camera + 1].y;
			quakecam.epos.z = SpotCam[current_spline_camera + 1].z;

			if (SpotCam[current_spline_camera + 1].timer != -1)
			{
				quakecam.epos.room_number = SpotCam[current_spline_camera + 1].timer << 3;
			}
			else
			{
				//loc_3892C
				quakecam.epos.room_number = 0;
			}

			//loc_38930
			quakecam.epos.box_number = phd_sqrt_asm(((quakecam.spos.x - quakecam.epos.x) * (quakecam.spos.x - quakecam.epos.x)) + ((quakecam.spos.y - quakecam.epos.y) * (quakecam.spos.y - quakecam.epos.y) + ((quakecam.spos.z - quakecam.epos.z) * (quakecam.spos.z - quakecam.epos.z))));
		}
	}

	//loc_38994

	if (spotcam_timer != 0)
	{
		return;
	}

	current_spline_position = 0;

	if (current_spline_camera == first_camera)
	{
		last_camera = current_spline_camera - 1;
	}

	//loc_389BC
	if (spline_from_camera)
	{
		sp = 1;
		spline_from_camera = 0;
		cn = first_camera - 1;
	}
	else
	{
		if ((SpotCam[current_spline_camera].flags & SCF_REENABLE_LARA_CONTROLS))
		{
			bDisableLaraControl = 0;
		}//loc_38A0C

		if ((SpotCam[current_spline_camera].flags & SCF_DISABLE_LARA_CONTROLS))
		{
			SetFadeClip(16, 1);
			bDisableLaraControl = 1;
		}
		//loc_38A24

		sp = 0;
		if ((SpotCam[current_spline_camera].flags & SCF_CUT_TO_CAM))
		{
			cn = (SpotCam[current_spline_camera].timer & 0xF) + first_camera;
			//v0 = SpotCam[cn]
			camera_xposition[0] = SpotCam[cn].x;
			camera_yposition[0] = SpotCam[cn].y;
			camera_zposition[0] = SpotCam[cn].z;
			camera_xtarget[0] = SpotCam[cn].tx;
			camera_ytarget[0] = SpotCam[cn].ty;
			camera_ztarget[0] = SpotCam[cn].tz;
			camera_xtarget[0] = SpotCam[cn].tx;
			camera_ytarget[0] = SpotCam[cn].ty;
			camera_ztarget[0] = SpotCam[cn].tz;
			camera_roll[0] = SpotCam[cn].roll;
			camera_fov[0] = SpotCam[cn].fov;
			sp = 1;
			current_spline_camera = cn;
			camera_speed[0] = SpotCam[cn].speed;
		}//loc_38B04

		camera_xposition[sp] = SpotCam[cn].x;
		camera_yposition[sp] = SpotCam[cn].y;
		camera_zposition[sp] = SpotCam[cn].z;
		camera_xtarget[sp] = SpotCam[cn].tx;
		camera_ytarget[sp] = SpotCam[cn].ty;
		camera_ztarget[sp] = SpotCam[cn].tz;
		sp = 1;
		camera_xtarget[sp] = SpotCam[cn].tx;
		camera_ytarget[sp] = SpotCam[cn].ty;
		camera_ztarget[sp] = SpotCam[cn].tz;
		camera_roll[sp] = SpotCam[cn].roll;
		camera_fov[sp] = SpotCam[cn].fov;
		camera_speed[sp] = SpotCam[cn].speed;
	}

	cn = 1;
	if (sp < 4)
	{
		//loc_38BEC
		while (sp < 4)
		{
			if ((s->flags & SCF_LOOP_SEQUENCE))
			{
				if (last_camera < cn)
				{
					cn = first_camera;
				}//loc_38C2C
			}//loc_38C18
			else
			{
				//loc_38C18
				if (last_camera < cn)
				{
					cn = last_camera;
				}//loc_38C2C
			}

			//loc_38C2C
			camera_xposition[sp] = SpotCam[cn].x;
			camera_yposition[sp] = SpotCam[cn].y;
			camera_zposition[sp] = SpotCam[cn].z;
			camera_xtarget[sp] = SpotCam[cn].tx;
			camera_ytarget[sp] = SpotCam[cn].ty;
			camera_ztarget[sp] = SpotCam[cn].tz;
			camera_xtarget[sp] = SpotCam[cn].tx;
			camera_ytarget[sp] = SpotCam[cn].ty;
			camera_ztarget[sp] = SpotCam[cn].tz;
			camera_roll[sp] = SpotCam[cn].roll;
			camera_fov[sp] = SpotCam[cn].fov;
			camera_speed[sp] = SpotCam[cn].speed;
			cn++;
			sp++;
		}
	}//loc_38CF4

	if (last_camera > ++current_spline_camera)
	{
		return;
	}

	if ((s->flags & SCF_LOOP_SEQUENCE))
	{
		current_spline_camera = first_camera;
		spotcam_loopcnt++;
		return;
	}//loc_38D50

	if (!(s->flags & SCF_PAN_TO_LARA_CAM))
	{
		//loc_38D50
		if (spline_to_camera == 0)
		{
			camera_xposition[0] = SpotCam[current_spline_camera - 1].x;
			camera_yposition[0] = SpotCam[current_spline_camera - 1].y;
			camera_zposition[0] = SpotCam[current_spline_camera - 1].z;
			camera_xtarget[0] = SpotCam[current_spline_camera - 1].tx;
			camera_ytarget[0] = SpotCam[current_spline_camera - 1].ty;
			camera_ztarget[0] = SpotCam[current_spline_camera - 1].tz;
			camera_xtarget[0] = SpotCam[current_spline_camera - 1].tx;
			camera_ytarget[0] = SpotCam[current_spline_camera - 1].ty;
			camera_ztarget[0] = SpotCam[current_spline_camera - 1].tz;
			camera_roll[0] = SpotCam[current_spline_camera - 1].roll;
			camera_fov[0] = SpotCam[current_spline_camera - 1].fov;
			camera_speed[0] = SpotCam[current_spline_camera - 1].speed;

			camera_xposition[1] = SpotCam[current_spline_camera].x;
			camera_yposition[1] = SpotCam[current_spline_camera].y;
			camera_zposition[1] = SpotCam[current_spline_camera].z;
			current_spline_camera = current_spline_camera;///?
			camera_xtarget[1] = SpotCam[current_spline_camera].tx;
			camera_ytarget[1] = SpotCam[current_spline_camera].ty;
			camera_ztarget[1] = SpotCam[current_spline_camera].tz;
			camera_xtarget[1] = SpotCam[current_spline_camera].tx;
			camera_ytarget[1] = SpotCam[current_spline_camera].ty;
			camera_ztarget[1] = SpotCam[current_spline_camera].tz;
			camera_roll[1] = SpotCam[current_spline_camera].roll;
			camera_fov[1] = SpotCam[current_spline_camera].fov;
			camera_speed[1] = SpotCam[current_spline_camera].speed;

			//S_MemCpy(&Backup, &camera, sizeof(struct CAMERA_INFO));
			camera.old_type = FIXED_CAMERA;
			camera.type = CHASE_CAMERA;
			camera.speed = 1;

			CalculateCamera();
			//a0 = &camera;
			//a1 = &Backup;

			camera_roll[2] = 0;
			camera_roll[3] = 0;
			camera_speed[2] = camera_speed[1];

			InitialCameraPosition.x = camera.pos.x;
			InitialCameraPosition.y = camera.pos.y;
			InitialCameraPosition.z = camera.pos.z;

			InitialCameraTarget.x = camera.target.x;
			InitialCameraTarget.y = camera.target.y;
			InitialCameraTarget.z = camera.target.z;

			camera_xposition[2] = camera.pos.x;
			camera_yposition[2] = camera.pos.y;
			camera_zposition[2] = camera.pos.z;
			camera_xtarget[2] = camera.target.x;
			camera_ytarget[2] = camera.target.y;
			camera_ztarget[2] = camera.target.z;
			camera_fov[2] = CurrentFov;

			camera_xposition[3] = camera.pos.x;
			camera_yposition[3] = camera.pos.y;
			camera_zposition[3] = camera.pos.z;
			camera_xtarget[3] = camera.target.x;
			camera_ytarget[3] = camera.target.y;
			camera_ztarget[3] = camera.target.z;
			camera_fov[3] = CurrentFov;
			camera_speed[3] = camera_speed[1] >> 1;

			///S_MemCpy(&camera, &backup, sizeof(struct CAMERA_INFO));
#if PSXENGINE
			phd_LookAt(camera.pos.x, camera.pos.y, camera.pos.z, camera.target.x, camera.target.y, camera.target.z, 0);
#endif
			spline_to_camera = 1;
			return;
		}
	}//loc_38FE0

	if (bCheckTrigger)
	{
		ctype = camera.type;
		camera.type = HEAVY_CAMERA;

		if (gfCurrentLevel != LVL5_TITLE)
		{
			TestTriggersAtXYZ(camera.pos.x, camera.pos.y, camera.pos.z, camera.pos.room_number, 1, 0);
		}//loc_39044
		else
		{
			TestTriggersAtXYZ(camera.pos.x, camera.pos.y, camera.pos.z, camera.pos.room_number, 0, 0);
			TestTriggersAtXYZ(camera.pos.x, camera.pos.y, camera.pos.z, camera.pos.room_number, 1, 0);
		}

		//loc_390A0
		camera.type = (enum camera_type)ctype;

		bCheckTrigger = 0;
	}

	//loc_390AC
	SetFadeClip(0, 1);

	camera.old_type = FIXED_CAMERA;
	camera.type = CHASE_CAMERA;
	camera.speed = 1;
	bUseSpotCam = 0;
	bDisableLaraControl = 0;
	bCheckTrigger = 0;

	if ((s->flags & SCF_PAN_TO_LARA_CAM))
	{
		camera.pos.x = InitialCameraPosition.x;
		camera.pos.y = InitialCameraPosition.y;
		camera.pos.z = InitialCameraPosition.z;

		camera.target.x = InitialCameraTarget.x;
		camera.target.y = InitialCameraTarget.y;
		camera.target.z = InitialCameraTarget.z;

		camera.pos.room_number = InitialCameraRoom;
	}

	//loc_39148
	SCOverlay = 0;
	SCNoDrawLara = 0;
	cfov = LastFov;
	AlterFOV(LastFov);
#endif
}

long Spline(long x, long* knots, int nk)//37554(<), 37A54(<) (F)
{
	int span;
	long* k;
	long c1;
	long c2;

	c2 = nk - 3;
	x = MULFP(x, c2 << 16);
	span = x >> 16;

	if (c2 > span)
	{
		x -= (nk - 4) << 16;
	}
	else
	{
		x -= span << 16;
	}

	//loc_375A0
	k = &knots[span];

	return MULFP(MULFP(MULFP((((k[1]) + (k[1] >> 1)) + ((k[0] ^ -1) >> 2)) - ((k[2]) + (k[2] >> 1)) + (k[3] >> 1), x) + k[0] - (k[1] << 1) + (k[1] >> 1) + (k[2] << 1) - (k[3] >> 1), x) + ((k[0] ^ -1) >> 2) - (k[2] >> 1), x) + k[1];
}