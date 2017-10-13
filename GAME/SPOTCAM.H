#ifndef SPOTCAM_H
#define SPOTCAM_H

#include "CAMERA.H"

#include "SPECTYPES.H"

enum spotcam_flags
{
	SCF_CUT_PAN = (1 << 0),					 // 0x0001   cut without panning smoothly
	SCF_VIGNETTE = (1 << 1),				 // 0x0002
	SCF_LOOP_SEQUENCE = (1 << 2),			 // 0x0004
	SCF_TRACKING_CAM = (1 << 3),			 // 0x0008
	SCF_HIDE_LARA = (1 << 4),				 // 0x0010
	SCF_FOCUS_LARA_HEAD = (1 << 5),			 // 0x0020
	SCF_PAN_TO_LARA_CAM = (1 << 6),			 // 0x0040
	SCF_CUT_TO_CAM = (1 << 7),				 // 0x0080
	SCF_STOP_MOVEMENT = (1 << 8),			 // 0x0100   stops movement for a given time (cf. `Timer` field)
	SCF_DISABLE_BREAKOUT = (1 << 9),		 // 0x0200   disables breaking out from cutscene using Look key
	SCF_DISABLE_LARA_CONTROLS = (1 << 10),	 // 0x0400   also adds widescreen bars
	SCF_REENABLE_LARA_CONTROLS = (1 << 11),	 // 0x0800   use with 0x0400, keeps widescreen bars
	SCF_SCREEN_FADE_IN = (1 << 12),			 // 0x1000
	SCF_SCREEN_FADE_OUT = (1 << 13),		 // 0x2000
	SCF_ACTIVATE_HEAVY_TRIGGERS = (1 << 14), // 0x4000   when camera is moving above heavy trigger sector, it'll be	activated
	SCF_CAMERA_ONE_SHOT = (1 << 15),		 // 0x8000
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
#if PC_VERSION
extern struct SPOTCAM SpotCam[255];
#else
extern struct SPOTCAM* SpotCam;
#endif
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

extern void InitSpotCamSequences();
extern void InitialiseSpotCam(short Sequence);
extern void CalculateSpotCams();
extern long Spline(long x /*$s3*/, long* knots /*$s4*/, int nk /*$s2*/);

#endif