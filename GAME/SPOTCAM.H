#ifndef SPOTCAM_H
#define SPOTCAM_H

#include "CAMERA.H"

struct SPOTCAM
{
	long x;
	long y;
	long z;
	long tx;
	long ty;
	long tz;
	unsigned char sequence;
	unsigned char camera;
	short fov;
	short roll;
	short timer;
	short speed;
	short flags;
	short room_number;
	short pad;
};

struct QUAKE_CAM
{
	struct GAME_VECTOR spos;
	struct GAME_VECTOR epos;
};

extern int bUseSpotCam;
extern int bDisableLaraControl;
extern int bTrackCamInit;
extern char SCOverlay;
extern char SCNoDrawLara;
extern char SniperOverlay;
extern short spotcam_timer;
extern int bCheckTrigger;
extern short LastSequence;
extern short CurrentFov;
extern short spotcam_loopcnt;
extern short number_spotcams;
extern struct SPOTCAM* SpotCam;
extern unsigned char CameraCnt[16];
extern unsigned char SpotRemap[16];
extern long current_spline_position;
extern short LastFov;
extern int CameraFade;
extern int LaraHealth;
extern int LaraAir;
extern long camera_xposition[18];
extern long camera_yposition[18];
extern long camera_zposition[18];
extern long camera_xtarget[18];
extern long camera_ytarget[18];
extern long camera_ztarget[18];
extern long camera_roll[18];
extern long camera_fov[18];
extern long camera_speed[18];
extern short current_spline_camera;
extern short current_camera_cnt;
extern short current_sequence;
extern short first_camera;
extern short last_camera;
extern int spline_from_camera;
extern int spline_to_camera;
extern struct PHD_VECTOR InitialCameraPosition;
extern struct PHD_VECTOR InitialCameraTarget;
extern struct PHD_VECTOR LaraFixedPosition;
extern short InitialCameraRoom;
extern struct QUAKE_CAM quakecam;

#endif