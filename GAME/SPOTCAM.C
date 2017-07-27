#include "SPOTCAM.H"

///HACK
#include "OBJECTS.H"
#include "DELTAPAK.H"

#include "GAMEFLOW.H"
#include "LARA.H"
#include "SPECIFIC.H"
#include "TOMB4FX.H"

int bUseSpotCam;
int bDisableLaraControl;
int bTrackCamInit;
char SCOverlay;
char SCNoDrawLara;
char SniperOverlay;
short spotcam_timer;
int bCheckTrigger;
short LastSequence;
short CurrentFov;
short spotcam_loopcnt;
short number_spotcams;
struct SPOTCAM* SpotCam;
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

void InitialiseSpotCam(short Sequence /*$s0*/)//37648, 37B48
{
	struct SPOTCAM* s;

	///@HACK************************************************************************************
	lara_item = find_a_fucking_item(LARA);

	if (bTrackCamInit != 0 && LastSequence == Sequence)
	{
		bTrackCamInit = 0;
		return;
	}//loc_37B94

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
		int v1 = CameraCnt[0];
		int a0 = 0;
		for (int i = 0; i < SpotRemap[Sequence]; i++)
		{
			a0 = v1 = CameraCnt[i] + a0;
		}

		current_spline_camera = v1;

	}//377E0

	//loc_377E0
	current_spline_position = 0;
	spline_to_camera = 0;

	first_camera = current_spline_camera;

	s = &SpotCam[current_spline_camera];

	last_camera = current_spline_camera + (CameraCnt[SpotRemap[Sequence]] + -1);
	current_camera_cnt = CameraCnt[SpotRemap[Sequence]];

	if (!(s->flags & 0x400) && gfGameMode == 1)
	{
		bDisableLaraControl = 1;

		if (gfGameMode != 1)//? likely wrong
		{
			SetFadeClip(16, 1);
		}//loc_37888
	}

	//loc_37888
	int v0 = s->flags & 1;
	if (s->flags & 8)
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
		
		int t3 = 1;
		if (current_camera_cnt > 0)
		{
			s = &SpotCam[first_camera];
			//loc_37960
			for (int i = 1; i < current_camera_cnt + 1; i++, s++)
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

		}//loc_379F8
			
	}//loc_37AA8

	S_Warn("[InitialiseSpotCam] - Unimplemented!\n");
}