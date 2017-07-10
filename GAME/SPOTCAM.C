#include "SPOTCAM.H"

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

void InitSpotCamSequences()//374B8, 379B8
{
	int s; // $a2
	int cc; // $a3
	int n; // $a1
	int ce; // $t0

	short a1 = number_spotcams;// number_spotcams;
	bTrackCamInit = 0;

	if (a1 != 0)
	{
		int a3 = 1;
		int t0 = 0;
		
		int t3 = 0x000A0000;
		struct SPOTCAM *a0 = SpotCam;

		char a2 = 0;// a0->sequence;

		if (a3 < a1)
		{
			unsigned char* t2 = &CameraCnt[0];
			unsigned char* t1 = &SpotRemap[0];

			a0++;
			a1 -= 1;//?not required?

			//loc_374F8:
			for (int i = 0; i < a1; i++)
			{
				unsigned char v00 = a0->sequence;

				//loc_37510
				int t0 = 0;//fixme

				unsigned char* v000 = &t2[t0];//fixme why take a0 sequence then add

				if (v00 != a2)
				{
					a3 += 1;
					v000[0] = a3;//byte not int, fixme
					a3 = 0;
					v000 = &t1[a2];
					v000[0] = t0;//byte not int, fix me!
					t0++;
					a2 = a0->sequence;
				}
			}


			a0++;
			//loc_37534
			char* v0000 = (char*)&current_spline_camera;//ptr?
			v0000 = &v0000[t0];//index into current_spline_camera
			unsigned char* v1111 = &SpotRemap[a2];
			v0000[0] = a3;
			v1111[0] = t0;
		}
	}
}