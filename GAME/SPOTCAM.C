#include "SPOTCAM.H"

#include "SPECIFIC.H"

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

void InitSpotCamSequences()//374B8(<), 379B8(<)
{
	int s, cc, n, ce;

	n = number_spotcams;
	bTrackCamInit = 0;

	//Current camera
	cc = 1;

	if (n != 0)
	{
		ce = 0;
		struct SPOTCAM* sc = SpotCam;

		s = sc->sequence;

		if (cc < n)
		{
			sc++;
			n--;

			for (int i = 0; i < n; i++, sc++)
			{
				cc++;

				if (sc->sequence != s)
				{
					CameraCnt[ce] = cc;
					cc = 1;

					SpotRemap[s] = ce++;

					s = sc->sequence;
				}
			}

			CameraCnt[ce] = cc;
			SpotRemap[s] = ce;
		}
	}
}

void InitialiseSpotCam(short Sequence /*$s0*/)//37648, 37B48
{
	S_Warn("[InitialiseSpotCam] - Unimplemented!\n");
}