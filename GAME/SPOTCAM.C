#include "SPOTCAM.H"

#include "CONTROL.H"
#include "DELTAPAK.H"
#include "GAMEFLOW.H"
#include "LARA.H"
#include "MATHS.H"
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

#define MULFP(A, B) ((A % B) << 16) | ((A * B) >> 16)
#define DIVFP(A, B) (A / (B >> 8)) << 8

#include <STDIO.H>

long DIVTEMP(long A, long B)
{
	B >>= 8;
	A /= B;
	B <<= 8;
	return B;
}

long MULTEMP(long A/*$a0*/, long B/*$a1*/)
{
	int v1 = A * B;
	int v0 = 0;

	if (A != 0 && B != 0)
	{
		v0 = A % B;
	}
	v1 >>= 16;
	v0 <<= 16;
	return v1|v0;
}

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

	lara_item->mesh_bits = -1;

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
		int cn; // $s0
	//} // line 396, offset 0x38a50

	{ // line 1, offset 0x38b04
		int sp; // $s5
		int cn; // $s0
	} // line 1, offset 0x38b04

	{ // line 1, offset 0x38c2c
		int sp; // $s5
		int cn; // $s0
	} // line 1, offset 0x38c2c

	{ // line 439, offset 0x38d68
		struct CAMERA_INFO Backup; // stack offset -216
		{ // line 441, offset 0x38d68
			int cn; // $v1
		} // line 441, offset 0x38d68
		{ // line 441, offset 0x38d68
		} // line 441, offset 0x38d68
	} // line 441, offset 0x38d68
	{ // line 1, offset 0x38ff0
		{ // line 1, offset 0x38ff0
			int ctype; // $s0
		} // line 1, offset 0x390a0
	} // line 1, offset 0x390a0

	if (bDisableLaraControl)
	{
		lara_item->hit_points = LaraHealth;
		lara.air = LaraAir;
	}
	
	//loc_37F20
	//v0 = first_camera
	//a0 = SpotCam
	s = &SpotCam[first_camera];//a0
	//v0 = s->flags;

	spline_cnt = 4;//s3
	if ((s->flags & SCF_TRACKING_CAM))
	{
		spline_cnt = current_camera_cnt + 2;
	}
	
	//loc_37F64
	//a1 = &camera_xposition[0];
	//a0 = current_spline_position;
	//a2 = spline_cnt;

	cpx = Spline(current_spline_position, &camera_xposition[0], spline_cnt);
	cpy = Spline(current_spline_position, &camera_yposition[0], spline_cnt);
	cpz = Spline(current_spline_position, &camera_zposition[0], spline_cnt);

	ctx = Spline(current_spline_position, &camera_xtarget[0], spline_cnt);
	cty = Spline(current_spline_position, &camera_ytarget[0], spline_cnt);
	ctz = Spline(current_spline_position, &camera_ztarget[0], spline_cnt);

	cspeed = Spline(current_spline_position, &camera_speed[0], spline_cnt);
	croll = Spline(current_spline_position, &camera_roll[0], spline_cnt);
	cfov = Spline(current_spline_position, &camera_fov[0], spline_cnt);
	
	//a2 = current_spline_camera;
	//a1 = SpotCam;
	//a0 = SpotCam[current_spline_camera].flags;
	if ((SpotCam[current_spline_camera].flags & SCF_SCREEN_FADE_IN) && CameraFade != current_spline_camera )
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

	//a1 = current_spline_camera;
	//a0 = SpotCam;
	//v0 = SpotCam[current_spline_camera];

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
		while(var_2C < 8)
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

		//v0 = current_spline_position;
		//a1 = s;
		//v1 = (cp - current_spline_posision) >> 5;

		//a0 = s->flags
		//v0 += v1;
		current_spline_position += (cp - current_spline_position) >> 5;

		//v1 = cp - current_spline_position
		if((s->flags & SCF_CUT_PAN))
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
		//v0 = current_spline_position;
		if (current_spline_position < 0)
		{
			//v1 = 0x10000;
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
	//a1 = s
	//a0 = s->flags;
	//s0 = 1;

	//v0 = s->flags & 8
	if ((s->flags & SCF_DISABLE_BREAKOUT) && (input & IN_LOOK) && gfGameMode != 1)
	{
		//a0 = 0;
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
	//v0 = cpx
	//v1 = cpy
	//a0 = cpz
	//a1 = s
	camera.pos.x = cpx;
	camera.pos.y = cpy;
	camera.pos.z = cpz;
	//v0 = s->speed;
	//v1 = 0x280000

	if ((s->speed & 0x280000))
	{
		//v0 = lara_item;
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
	//v1 = -1;
	//v0 = IsRoomOutsideNo;
	//a0 = IsRoomOutsideNo;

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

	//v0 = quakecam.spos.box_number;

	if (quakecam.spos.box_number != 0)
	{
		dx = (camera.pos.x - quakecam.epos.x);
		dy = (camera.pos.y - quakecam.epos.y);
		dz = (camera.pos.z - quakecam.epos.z);

		phd_sqrt_asm(dx * dy * dz);

#if 0
			lh      $a1, 0x301A($gp)
			move    $v1, $v0
			slt     $v0, $v1, $a1
			beqz    $v0, loc_38650
			subu    $v1, $a1, $v1
			lh      $s0, 0x3008($gp)
			lh      $v0, 0x3018($gp)
			nop
			subu    $s1, $v0, $s0
			mult    $s1, $v1
			mflo    $s1
			nop
			nop
			div     $s1, $a1
			mflo    $v0
			bnez    $a1, loc_385A8
			nop
			break   7

			loc_385A8:
			addu    $s0, $v0
			blez    $s0, loc_38650
			sra     $s1, $s0, 1
			jal     sub_5E9F0
			nop
			div     $v0, $s0
			mfhi    $v1
			bnez    $s0, loc_385D0
			nop
			break   7

			loc_385D0:
		lw      $v0, camera.pos.x
			subu    $v1, $s1
			addu    $v0, $v1
			sw      $v0, camera.pos.x
			jal     sub_5E9F0
			nop
			div     $v0, $s0
			mfhi    $v1
			bnez    $s0, loc_38604
			nop
			break   7

			loc_38604:
			lw      $v0, camera.pos.y
			subu    $v1, $s1
			addu    $v0, $v1
			sw      $v0, camera.pos.y
			jal     sub_5E9F0
			nop
			div     $v0, $s0
			mfhi    $v1
			bnez    $s0, loc_38638
			nop
			break   7

			loc_38638:
			lw      $v0, camera.pos.z
			subu    $v1, $s1
			addu    $v0, $v1
			sw      $v0, camera.pos.z
#endif


	}//loc_38650

#if 0
		loc_38650 :
		lw      $a0, camera.pos.x
		lw      $a1, camera.pos.y
		lw      $a2, camera.pos.z
		lw      $a3, camera.target.x
		lw      $v0, 0xF8 + var_40($sp)//croll
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

		//v1 = s;
		//v0 = s->flags;

		if ((s->flags & SCF_TRACKING_CAM))
		{
			bTrackCamInit = 1;
			return;
		}
		
		//loc_38794
		//v0 = 0x10000;
		//a0 = cspeed;
		//v1 = current_spline_position;
		//v0 -= cspeed;
	
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

		//a0 = SpotCam[current_spline_camera];
		if((SpotCam[current_spline_camera].flags & SCF_HIDE_LARA))
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
			if (quakecam.spos.box_number != 0)
			{
				if (SpotCam[current_spline_camera].timer == -1)
				{
					//loc_38990
					quakecam.spos.box_number = 0;
				}
				else
				{
					//loc_38888
#if 0

					loc_38888 :
							  lw      $v0, 0($a0)
								  nop
								  sw      $v0, 0x2FFC($gp)
								  lw      $v1, 4($a0)
								  nop
								  sw      $v1, 0x3000($gp)
								  lw      $v0, 8($a0)
								  li      $v1, 0xFFFFFFFF
								  sw      $v0, 0x3004($gp)
								  lh      $v0, 0x1E($a0)
								  lhu     $a0, 0x1E($a0)
								  beq     $v0, $v1, loc_388C8
								  sll     $v0, $a0, 3
								  sh      $v0, 0x3008($gp)
								  j       loc_388CC
								  nop

								  loc_388C8 :
							  sh      $zero, 0x3008($gp)

								  loc_388CC :
								  lh      $a1, current_spline_camera
								  lw      $a0, SpotCam($gp)
								  li      $v1, 1
								  sh      $v1, 0x300A($gp)
								  sll     $v0, $a1, 2
								  addu    $v0, $a1
								  sll     $v0, 3
								  addu    $v0, $a0
								  lw      $v1, 0x28($v0)
								  addiu   $v0, 0x28
								  sw      $v1, 0x300C($gp)
								  lw      $v1, 4($v0)
								  nop
								  sw      $v1, 0x3010($gp)
								  lw      $a0, 8($v0)
								  li      $a1, 0xFFFFFFFF
								  sw      $a0, 0x3014($gp)
								  lh      $v1, 0x1E($v0)
								  lhu     $v0, 0x1E($v0)
								  beq     $v1, $a1, loc_3892C
								  sll     $v0, 3
								  sh      $v0, 0x3018($gp)
								  j       loc_38930
								  nop

								  loc_3892C :
							  sh      $zero, 0x3018($gp)

								  loc_38930 :
								  lw      $v1, 0x2FFC($gp)
								  lw      $v0, 0x300C($gp)
								  nop
								  subu    $v1, $v0
								  mult    $v1, $v1
								  lw      $v1, 0x3000($gp)
								  lw      $v0, 0x3010($gp)
								  mflo    $a1
								  subu    $s0, $v1, $v0
								  nop
								  mult    $s0, $s0
								  lw      $v1, 0x3004($gp)
								  lw      $v0, 0x3014($gp)
								  mflo    $a2
								  subu    $s1, $v1, $v0
								  nop
								  mult    $s1, $s1
								  addu    $a1, $a2
								  mflo    $a0
								  jal     sub_779DC
								  addu    $a0, $a1, $a0
								  sh      $v0, 0x301A($gp)
								  j       loc_38994
								  nop

								  loc_38990 :
							  sh      $zero, 0x300A($gp)
#endif
				}
			}//loc_38888
		}
		
		//loc_38994

		if (spotcam_timer != 0)
		{
			return;
		}

		//v1 = current_spline_camera;
		//v0 = first_camera;
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
#if 0


			loc_389DC:
					 lh      $v1, current_spline_camera
						 lw      $a0, SpotCam($gp)
						 sll     $v0, $v1, 2
						 addu    $v0, $v1
						 sll     $v0, 3
						 addu    $v0, $a0
						 lhu     $v0, 0x22($v0)
						 nop
						 andi    $v1, $v0, 0x800
						 beqz    $v1, loc_38A0C
						 nop
						 sw      $zero, 0x508($gp)

						 loc_38A0C:
					 andi    $v0, 0x400
						 beqz    $v0, loc_38A24
						 li      $a0, 0x10
						 jal     sub_34A8C
						 li      $a1, 1
						 sw      $s5, 0x508($gp)

						 loc_38A24:
					 lh      $v0, current_spline_camera
						 lw      $a1, SpotCam($gp)
						 sll     $v1, $v0, 2
						 addu    $v1, $v0
						 sll     $v1, 3
						 addu    $v1, $a1
						 lhu     $v0, 0x22($v1)
						 nop
						 andi    $v0, 0x80
						 beqz    $v0, loc_38B04
						 move    $s5, $zero
						 lhu     $v1, 0x1E($v1)
						 lh      $a0, first_camera
						 andi    $v1, 0xF
						 addu    $s0, $v1, $a0
						 sll     $v0, $s0, 2
						 addu    $v0, $s0
						 sll     $v0, 3
						 addu    $v0, $a1
						 lw      $v1, 0($v0)
						 nop
						 sw      $v1, 0x2DB0($gp)
						 lw      $a0, 4($v0)
						 nop
						 sw      $a0, 0x2DF8($gp)
						 lw      $v1, 8($v0)
						 nop
						 sw      $v1, 0x2E40($gp)
						 lw      $a0, 0xC($v0)
						 nop
						 sw      $a0, 0x301C($gp)
						 lw      $v1, 0x10($v0)
						 nop
						 sw      $v1, 0x306C($gp)
						 lw      $a0, 0x14($v0)
						 nop
						 sw      $a0, 0x2FB0($gp)
						 lw      $v1, 0xC($v0)
						 nop
						 sw      $v1, 0x301C($gp)
						 lw      $a0, 0x10($v0)
						 nop
						 sw      $a0, 0x306C($gp)
						 lw      $v1, 0x14($v0)
						 nop
						 sw      $v1, 0x2FB0($gp)
						 lh      $a0, 0x1C($v0)
						 nop
						 sw      $a0, 0x2F00($gp)
						 lh      $v1, 0x1A($v0)
						 nop
						 sw      $v1, 0x2F4C($gp)
						 lh      $a0, 0x20($v0)
						 li      $s5, 1
						 sh      $s0, current_spline_camera
						 sw      $a0, 0x2EB8($gp)

						 loc_38B04:
					 sll     $t0, $s5, 2
						 addiu   $v1, $gp, 0x2DB0
						 sll     $a0, $s0, 2
						 addu    $a0, $s0
						 sll     $a0, 3
						 addu    $v1, $t0, $v1
						 addiu   $a2, $gp, 0x301C
						 addu    $a2, $t0, $a2
						 lw      $v0, SpotCam($gp)
						 addiu   $a3, $gp, 0x306C
						 addu    $a0, $v0
						 addiu   $v0, $gp, 0x2DF8
						 lw      $a1, 0($a0)
						 addu    $v0, $t0, $v0
						 sw      $a1, 0($v1)
						 lw      $a1, 4($a0)
						 addiu   $v1, $gp, 0x2E40
						 sw      $a1, 0($v0)
						 lw      $v0, 8($a0)
						 addu    $v1, $t0, $v1
						 sw      $v0, 0($v1)
						 lw      $v0, 0xC($a0)
						 addu    $a3, $t0, $a3
						 sw      $v0, 0($a2)
						 lw      $v0, 0x10($a0)
						 addiu   $a1, $gp, 0x2FB0
						 sw      $v0, 0($a3)
						 lw      $v1, 0x14($a0)
						 addu    $a1, $t0, $a1
						 sw      $v1, 0($a1)
						 lw      $v0, 0xC($a0)
						 addiu   $s5, 1
						 sw      $v0, 0($a2)
						 addiu   $v0, $gp, 0x2F00
						 lw      $v1, 0x10($a0)
						 addu    $v0, $t0, $v0
						 sw      $v1, 0($a3)
						 lw      $a2, 0x14($a0)
						 addiu   $v1, $gp, 0x2F4C
						 sw      $a2, 0($a1)
						 lh      $a1, 0x1C($a0)
						 addu    $v1, $t0, $v1
						 sw      $a1, 0($v0)
						 lh      $v0, 0x1A($a0)
						 addiu   $a1, $gp, 0x2EB8
						 sw      $v0, 0($v1)
						 lh      $v0, 0x20($a0)
						 addu    $t0, $a1
						 sw      $v0, 0($t0)
#endif
		}

		cn = 1;
		if (sp < 4)
		{
			//v0 = last_camera;
			//t4 = SpotCam;
			//v1 = first_camera;
			//t1 = last_camera << 16
			//t3 = last_camera;
			//t2 = first_camera << 16;

			//loc_38BEC
			while (sp < 4)
			{
				if ((s->flags & SCF_LOOP_SEQUENCE))
				{
					if (last_camera < cn)
					{
						//t0 = sp << 2;
						cn = first_camera;
					}//loc_38C2C
				}//loc_38C18
				else
				{
					//loc_38C18
					if (last_camera < cn)
					{
						//t0 = sp << 2;
						cn = last_camera;
					}//loc_38C2C
				}

				//loc_38C2C
				//a1 = &camera_xposition[sp];
				//a0 = &SpotCam[cn];
				//v0 = &camera_yposition[sp];
				//a3 = &camera_ytarget[sp];
				//a3 = t0 + a3;
				//v1 = SpotCam[cn].x;
				//a2 = &camera_ztarget[sp];
				camera_xposition[sp] = SpotCam[cn].x;
				//v1 = &camera_zposition[sp];
				camera_yposition[sp] = SpotCam[cn].y;
				//v0 = //SpotCam[cn].z;
				//a1 = &camera_xtarget[sp];
				camera_zposition[sp] = SpotCam[cn].z;
				camera_xtarget[sp] = SpotCam[cn].tx;
				camera_ytarget[sp] = SpotCam[cn].ty;
				camera_ztarget[sp] = SpotCam[cn].tz;
				///cn++;
				//v0 = SpotCam[cn].tx;
				///sp++;
				camera_xtarget[sp] = SpotCam[cn].tx;
				//v0 = &camera_roll[sp];
				camera_ytarget[sp] = SpotCam[cn].ty;
				//a1 = SpotCam[cn].tz;
				//v1 = &camera_fov[sp];
				camera_ztarget[sp] = SpotCam[cn].tz;
				camera_roll[sp] = SpotCam[cn].roll;
				//t0 = &camera_speed[sp];
				camera_fov[sp] = SpotCam[cn].fov;
				camera_speed[sp] = SpotCam[cn].speed;
				cn++;
				sp++;
			}
		}//loc_38CF4

		//a3 = current_spline_camera;
		//v1 = last_camera

		//v1 = last_camera < current_spline_camera ? 1 : 0
		if (last_camera > ++current_spline_camera)
		{
			return;
		}

		//a0 = s;
		//v1 = s->flags

		//v0 = s->flags & 0x40;
		if ((s->flags & SCF_LOOP_SEQUENCE))
		{
			current_spline_camera = first_camera;
			spotcam_loopcnt++;
			return;
		}//loc_38D50

		if (!(s->flags & SCF_PAN_TO_LARA_CAM))
		{
			//loc_38D50
			//v0 = spline_to_camera;
			if (spline_to_camera == 0)
			{
				//a1 = current_spline_camera;
				//v1 = current_spline_camera - 1;
				//v0 = SpotCam[current_spline_camera - 1];
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
				
				//v0 = SpotCam[current_spline_camera];
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

				///S_MemCpy(&Backup, &camera, sizeof(struct CAMERA_INFO));
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

				return;
			}
#if 0

						  lw      $a0, camera.pos.x
						  lw      $a1, camera.pos.y
						  lw      $a2, camera.pos.z
						  lw      $a3, camera.target.x
						  lw      $v1, camera.target.y
						  lw      $t0, camera.target.z
						  sra     $v0, $s2, 16
						  sw      $v0, 0xF8 + var_E0($sp)
						  sw      $v1, 0xF8 + var_E8($sp)
						  jal     sub_77728//phd_LookAt
						  sw      $t0, 0xF8 + var_E4($sp)
						  sw      $s0, 0x2FA8($gp)
						  j       loc_39160
						  nop
#endif
		}//loc_38FE0

		if (bCheckTrigger)
		{
			//v0 = 5;
			ctype = camera.type;
			//v1 = gfCurrentLevel;
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
}

#if 0
void CalculateSpotCams()//
{
	long cpx;
	long cpy;
	long cpz;
	long ctx;
	long cty;
	long ctz;
	long cspeed;
	long cfov;
	long croll;
	struct SPOTCAM* s;
	short spline_cnt;
	int next_spline_camera;
	int n;
	static int bFirstLook;
	long dx;
	long dy;
	long dz;
	long cs;
	long sp;
	long cp;
	long clen;
	long tlen;
	long cx;
	long cy;
	long cz;
	long lx;
	long lz;
	long ly;
	int i;//var_2C
	int ctype;
	int cn;
	struct CAMERA_INFO Backup;
	struct SPOTCAM* v1111111;
	struct SPOTCAM* v1;
	int v0;
	int s2;//sp?
	int s5;
	int s0;
	int a00;
	int a11;
	int a22;
	int a33;
	int v11;
	int t00;
	int v00;
	int fp;
	int s6;
	int s7;
	int s11;
	int s00;
	int v000;
	int v111;
	int a000;
	int a0;
	int a111;
	int a222;
	struct SPOTCAM* a1;

	if (bDisableLaraControl != 0)
	{
		lara_item->hit_points = LaraHealth;
		lara.air = LaraAir;
	}

	//loc_37F20
	s = &SpotCam[first_camera];//$a0

	if (s->flags & 8)
	{

		spline_cnt = current_camera_cnt + 2;
	}
	else
	{
		spline_cnt = 4;//$s3
	}

	//loc_37F64
	cpx = Spline(0, &camera_xposition[0], spline_cnt);
	cpy = Spline(0, &camera_yposition[0], spline_cnt);
	cpz = Spline(0, &camera_zposition[0], spline_cnt);

	ctx = Spline(0, &camera_xtarget[0], spline_cnt);
	cty = Spline(0, &camera_ytarget[0], spline_cnt);
	ctz = Spline(0, &camera_ztarget[0], spline_cnt);

	cspeed = Spline(0, &camera_speed[0], spline_cnt);
	croll = Spline(0, &camera_roll[0], spline_cnt);
	cfov = Spline(0, &camera_fov[0], spline_cnt);

	if (SpotCam[current_spline_camera].flags & SCF_SCREEN_FADE_IN && current_spline_camera != CameraFade)
	{
		CameraFade = current_spline_camera;

		if (gfCurrentLevel != LVL5_TITLE)
		{
			ScreenFadedOut = 0;
			ScreenFade = 255;
			dScreenFade = 0;
			SetScreenFadeIn(16);
		}
	}

	//loc_38084
	if (SpotCam[current_spline_camera].flags & SCF_SCREEN_FADE_OUT && CameraFade != current_spline_camera)
	{
		if (gfCurrentLevel != LVL5_TITLE)
		{
			ScreenFadedOut = 0;
			ScreenFade = 0;
			dScreenFade = 255;
			SetScreenFadeOut(16, 0);
		}
	}

	//loc_380F8
	v1 = s;
	v0 = s->flags;
	s2 = 0;//sp?
	if (s->flags & 8)
	{
		fp = 0;//cp
		lx = lara_item->pos.x_pos;
		s6 = 0x2000;//cs?
		ly = lara_item->pos.y_pos;
		i = 0;
		lz = lara_item->pos.z_pos;

		//loc_38144
		while (i < 8)
		{
			s5 = 0;
			s7 = s6 >> 1;
			i++;

			//loc_38158
			while (s5 < 8)
			{
				a00 = s2;
				cx = Spline(0, &camera_xposition[0], spline_cnt);
				cy = Spline(0, &camera_yposition[0], spline_cnt);
				cz = Spline(0, &camera_zposition[0], spline_cnt);

				tlen = sqrt((cx - lx) * (cx - lx) + (cz - lz) * (cz - lz) + (cy - ly) * (cy - ly)); //$v1

				if (tlen > 1024 * 64)
				{
					fp = s2;
					clen = tlen;
				}

				//loc_381F0 *
				s2 += s6;
				v0 = 0x00010000;
				v0 = v0 < s2 ? 1 : 0;

				v0 = s7 >> 1;
				if (0x00010000 < s2)
				{
					break;
				}//loc_38214

				s5++;
				v0 = s5 < 8 ? 1 : 0;
				v0 = s7 >> 1;
			}

			//loc_38214
			v0 <<= 2;
			s2 = fp - v0;

			s6 = s7;
			if (s2 < 0)
			{
				s2 = 0;
			}
		}

		//loc_38228
		v0 = current_spline_position;
		a1 = s;
		v11 = fp - v0;
		v11 >>= 5;
		a0 = a1->flags;
		v0 += v11;

		current_spline_position = v0;

		v11 = fp - v0;
		if (a1->flags & 1)
		{
			if (v11 > 0 || 0x8000 < v11)
			{
				//loc_38284
				v11 = -fp;
				if (v11 < 0x8000)
				{
					//loc_38298
					current_spline_position = fp;
				}
			}
		}

		//loc_3829C
		v0 = current_spline_position;
		v11 = 0x00010000;
		if (v0 < 0)
		{
			current_spline_position = 0;
			v0 = current_spline_position;
		}

		//loc_382B4
		v0 = v11 < v0 ? 1 : 0;
		if (v11 < v0)
		{
			current_spline_position = v11;
		}
	}//loc_382D0
	else if (spotcam_timer == 0)
	{
		current_spline_position += cspeed;
	}

	//loc_382F4
	if (!(input & IN_LOOK))
	{
		dword_A0AC4 = 0;
	}
	
	//loc_38310
	if (!(s->flags & SCF_DISABLE_BREAKOUT) && (input & IN_LOOK) && gfGameMode != 1)
	{
		if (s->flags & SCF_TRACKING_CAM)
		{
			if (dword_A0AC4 == 0)
			{
				camera.old_type = FIXED_CAMERA;
				dword_A0AC4 = 1;
			}

			//loc_3836C
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

	if (s->speed & 0x280000)
	{
		ctx = lara_item->pos.x_pos;
		cty = lara_item->pos.y_pos;
		ctz = lara_item->pos.z_pos;
	}
	
	//loc_38420
	v000 = ctx;
	a000 = cpx;
	a111 = cpy;
	a222 = cpz;
	v111 = cty;

	camera.target.x = ctx;
	camera.target.y = cty;
	camera.target.z = ctz;
	v000 = -1;
	IsRoomOutsideNo = -1;


	IsRoomOutside(cpx, cpy, cpz);

	if (IsRoomOutsideNo == -1)
	{
		camera.pos.room_number = SpotCam[current_spline_camera].room_number;
		GetFloor(camera.pos.x, camera.pos.y, camera.pos.z, &camera.pos.room_number);
	}
	else
	{
		camera.pos.room_number = IsRoomOutsideNo;
	}

	//loc_384DC
	AlterFOV(cfov);//FIXME cfov = 0;

	if (quakecam.spos.box_number != 0)
	{
		v00 = sqrt((camera.pos.x - quakecam.epos.x) * (camera.pos.x - quakecam.epos.x) + (camera.pos.y - quakecam.epos.y) * (camera.pos.y - quakecam.epos.y) + (camera.pos.z - quakecam.epos.z) * (camera.pos.z - quakecam.epos.z));
		a11 = quakecam.epos.box_number;
		v11 = v00;

		if (v00 < quakecam.epos.box_number)
		{
			v11 = (quakecam.epos.box_number - v00)
				* (quakecam.epos.room_number - quakecam.spos.room_number)
				/ quakecam.epos.box_number
				+ quakecam.spos.room_number;
			s11 = v11 >> 1;
			if (v11 > 0)
			{
				camera.pos.x += GetRandomControl() % v11 - s11;
				camera.pos.y += GetRandomControl() % v11 - s11;
				camera.pos.z += GetRandomControl() % v11 - s11;
			}
		}

/*
		if (v11 < a11)
		{
			v11 -= a11;
			s00 = quakecam.spos.room_number;
			v00 = quakecam.epos.room_number;
			s11 = v00 - s00;
			s11 *= v11;
			v00 = s11 / a11;

			if (v00 == 0)
			{
				//Simulate break 7
				assert(0);
			}

			//loc_385A8
			s00 += v00;
			s11 = s00 >> 1;
			if (s00 > 0)
			{
				v11 = GetRandomControl() / s00;
				if (s00 != 0)
				{
					//loc_385D0
					v11 -= s11;
					camera.pos.x += v11;

					v11 = GetRandomControl() / s00;

					if (s00 == 0)
					{
						//Simulate break 7
						assert(0);
					}

					//loc_38604
					v11 -= s11;
					camera.pos.y += v11;

					v11 = GetRandomControl() / s00;

					if (s00 == 0)
					{
						//Simulate break 7
						assert(0);
					}

					//loc_38638
					v11 -= s11;
					camera.pos.z += v11;
				}

				//Simulate break 7
				assert(0);

			}//loc_38650
		}//loc_38650
		*/
	}//loc_38650

	a00 = camera.pos.x;
	a11 = camera.pos.y;
	a22 = camera.pos.z;
	a33 = camera.target.x;
	v11 = camera.target.y;
	t00 = camera.target.z;
	v00 = croll;
#if 0
	//loc_38650:

	//sw	$v0, 0xF8 + var_E0($sp)
	//sw	$v1, 0xF8 + var_E8($sp)
	//sw	$t0, 0xF8 + var_E4($sp)
	//jal	sub_77728//phd_LookAt
	phd_LookAt();

	int s22 = s00;
	if (!bCheckTrigger)
	{
		s00 = camera.type;
		camera.type = HEAVY_CAMERA;

		if (gfCurrentLevel != 0)
		{
			TestTriggersAtXYZ(camera.pos.x, camera.pos.y, camera.pos.z, camera.pos.room_number, 1, 0);
		}
		else
		{
			//loc_38704
			TestTriggersAtXYZ(camera.pos.x, camera.pos.y, camera.pos.z, camera.pos.room_number, 0, 0);
			TestTriggersAtXYZ(camera.pos.x, camera.pos.y, camera.pos.z, camera.pos.room_number, 1, 0);
		}

		//loc_38760
		camera.type = s00;
		bCheckTrigger = 0;
	}
#endif

	//loc_3876C
	if (s->flags & 8)
	{
		bTrackCamInit = 1;
		return;
	}

	//loc_38794
	if (0x10000 - cspeed < current_spline_position)
	{
		if (SpotCam[current_spline_camera].flags & 2)
		{
			if (SpotCam[current_spline_camera].timer < 0)
			{
				SCOverlay = 1;
			}
			else if (!SlowMotion)
			{
				//loc_387F8
				SlowMotion = 1;
			}
		}

		//loc_38814
		if (SpotCam[current_spline_camera].flags & SCF_HIDE_LARA)
		{
			SCNoDrawLara = 1;
		}

		//loc_38844
		if (SpotCam[current_spline_camera].flags & SCF_ACTIVATE_HEAVY_TRIGGERS)
		{
			bCheckTrigger = 1;
		}

		//loc_3885C
		if (SpotCam[current_spline_camera].flags & SCF_STOP_MOVEMENT)
		{
			if (quakecam.spos.box_number == 0 && SpotCam[current_spline_camera].timer != -1)
			{
				//loc_38888
				quakecam.epos.x = SpotCam[current_spline_camera].x;
				quakecam.epos.y = SpotCam[current_spline_camera].y;
				quakecam.epos.z = SpotCam[current_spline_camera].z;

				if (SpotCam[current_spline_camera].timer != -1)
				{
					quakecam.epos.room_number = SpotCam[current_spline_camera].timer << 3;
				}
				else
				{
					//loc_388C8
					quakecam.epos.room_number = 0;
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
				quakecam.epos.box_number = sqrt((quakecam.spos.x - quakecam.epos.x) * (quakecam.spos.x - quakecam.epos.x) + (quakecam.spos.y - quakecam.epos.y) * (quakecam.spos.y - quakecam.epos.y) + (quakecam.spos.z - quakecam.epos.z) * (quakecam.spos.z - quakecam.epos.z));

			}
			else if (SpotCam[current_spline_camera].timer != -1)
			{
				//loc_38990
				quakecam.spos.box_number = 0;
			}
		}

		//loc_38994
		if (spotcam_timer != 0)
		{
			return;
		}

		v11 = current_spline_camera;
		v00 = first_camera;
		current_spline_position = 0;

		s0 = current_spline_camera - 1;
		if (current_spline_camera == first_camera)
		{
			s0 = last_camera;
		}
		
		//loc_389BC
		s5 = 1;
		if (!spline_from_camera)
		{
			spline_from_camera = 0;
			s0 = first_camera - 1;
			//j	loc_38BC8
		}
		else
		{
			//loc_389DC
			if (SpotCam[current_spline_camera].flags & SCF_REENABLE_LARA_CONTROLS)
			{
				bDisableLaraControl = 0;
			}

			//loc_38A0C
			if (SpotCam[current_spline_camera].flags & SCF_DISABLE_LARA_CONTROLS)
			{
				SetFadeClip(16, 1);
				bDisableLaraControl = 1;
			}
			
			//loc_38A24
			v1111111 = &SpotCam[current_spline_camera];
			s5 = 0;
			if (SpotCam[current_spline_camera].flags & SCF_CUT_TO_CAM)
			{
				current_spline_camera = (SpotCam[current_spline_camera].timer & 0xF) + first_camera;

				camera_xposition[0] = SpotCam[current_spline_camera].x;
				camera_yposition[0] = SpotCam[current_spline_camera].y;
				camera_zposition[0] = SpotCam[current_spline_camera].z;

				camera_xtarget[0] = SpotCam[current_spline_camera].tx;
				camera_ytarget[0] = SpotCam[current_spline_camera].ty;
				camera_ztarget[0] = SpotCam[current_spline_camera].tz;

				camera_roll[0] = SpotCam[current_spline_camera].roll;
				camera_fov[0] = SpotCam[current_spline_camera].fov;
				camera_speed[0] = SpotCam[current_spline_camera].speed;

				s5 = 1;
			}
			
			//loc_38B04
#if 0
			loc_38B04:
			sll	$t0, $s5, 2
			addiu	$v1, $gp, 0x2DB0
			sll	$a0, $s0, 2
			addu	$a0, $s0
			sll	$a0, 3
			addu	$v1, $t0, $v1
			addiu	$a2, $gp, 0x301C
			addu	$a2, $t0, $a2
			lw	$v0, SpotCam($gp)
			addiu	$a3, $gp, 0x306C
			addu	$a0, $v0
			addiu	$v0, $gp, 0x2DF8
			lw	$a1, 0($a0)
			addu	$v0, $t0, $v0
			sw	$a1, 0($v1)
			lw	$a1, 4($a0)
						 addiu	$v1, $gp, 0x2E40
						 sw	$a1, 0($v0)
						 lw	$v0, 8($a0)
						 addu	$v1, $t0, $v1
						 sw	$v0, 0($v1)
						 lw	$v0, 0xC($a0)
						 addu	$a3, $t0, $a3
						 sw	$v0, 0($a2)
						 lw	$v0, 0x10($a0)
						 addiu	$a1, $gp, 0x2FB0
						 sw	$v0, 0($a3)
						 lw	$v1, 0x14($a0)
						 addu	$a1, $t0, $a1
						 sw	$v1, 0($a1)
						 lw	$v0, 0xC($a0)
						 addiu	$s5, 1
						 sw	$v0, 0($a2)
						 addiu	$v0, $gp, 0x2F00
						 lw	$v1, 0x10($a0)
						 addu	$v0, $t0, $v0
						 sw	$v1, 0($a3)
						 lw	$a2, 0x14($a0)
						 addiu	$v1, $gp, 0x2F4C
						 sw	$a2, 0($a1)
						 lh	$a1, 0x1C($a0)
						 addu	$v1, $t0, $v1
						 sw	$a1, 0($v0)
						 lh	$v0, 0x1A($a0)
						 addiu	$a1, $gp, 0x2EB8
						 sw	$v0, 0($v1)
						 lh	$v0, 0x20($a0)
						 addu	$t0, $a1
						 sw	$v0, 0($t0)
#endif//critical 8BC8 jmp
		}


	}//loc_39160
	S_Warn("[CalculateSpotCams] - Unimplemented!\n");
}//loc_39160
#endif

long Spline(long x, long* knots, int nk)//37554(<), 37A54(<) (F)
{
	int span;
	long* k;
	long c1;
	long c2;
	int ret;

	c2 = nk - 3;
	x = MULFP(x, c2 << 16);
	span = x >> 16;
	
	if (!(x < c2))
	{
		span = nk - 4;
	}

	//loc_375A0
	x -= span << 16;
	k = &knots[span];

	ret = (((k[1] + (k[1] >> 1)) + (k[0] ^ -1) >> 2) - k[2] + (k[2] >> 1)) + (k[3] >> 1);
	ret = MULTEMP(ret, x) + (((k[0] - ((k[1] << 1) + (k[1] >> 1))) + (k[2] << 1) - (k[3] >> 1)) - (k[3] >> 1)) + (k[2] >> 1);
	ret = MULTEMP(ret, x) + (k[0] ^ -1) >> 2;
	return MULTEMP(ret, x) + k[1];
}