#ifndef CAMERA_H
#define CAMERA_H

#include "SPECTYPES.H"

enum camera_flags
{
	CF_FOLLOW_CENTER = 1,
	CF_UNKNOWN_2 = 2,
	CF_CHASE_OBJECT = 3,
};

extern long BinocularRange;
extern long BinocularOn;
extern enum camera_type BinocularOldCamera;
extern long LaserSight;
extern long InfraRed;
extern char SniperCount;
extern char SniperCamActive;
extern long ExittingBinos;
extern long TooFarCount;
extern long CombatShift;
extern unsigned char camerasnaps;
extern unsigned char TargetSnaps;
extern char TLFlag;
extern char LSHKShotsFired;
extern char LSHKTimer;
extern struct CAMERA_INFO camera;
extern char UseForcedFixedCamera;
extern struct GAME_VECTOR ForcedFixedCamera;
extern long NumFixedCameras;
extern int number_cameras;
extern struct PHD_VECTOR CamOldPos;
extern struct SHATTER_ITEM ShatterItem;
extern struct GAME_VECTOR static_lookcamp;
extern struct GAME_VECTOR static_lookcamt;
extern struct OLD_CAMERA old_cam;
extern struct GAME_VECTOR last_ideal;
extern struct GAME_VECTOR last_target;
extern short rcossin_tbl[];

extern void InitialiseCamera();
extern void AlterFOV(short fov);
extern void CalculateCamera();
extern void BinocularCamera(struct ITEM_INFO* item);
extern void LookCamera(struct ITEM_INFO* item);
extern void CombatCamera(struct ITEM_INFO* item);
extern void FixedCamera();
extern void ChaseCamera(struct ITEM_INFO* item);
extern void ConfirmCameraTargetPos();
extern void ScreenShake(struct ITEM_INFO* item, short MaxVal, short MaxDist);
extern void UpdateCameraElevation();
extern void LaraTorch(struct PHD_VECTOR* Soffset, struct PHD_VECTOR* Eoffset, short yrot, long brightness);
extern long mgLOS(struct GAME_VECTOR* start, struct GAME_VECTOR* target, long push);
extern long CameraCollisionBounds(struct GAME_VECTOR* ideal, long push, long yfirst);
extern void MoveCamera(struct GAME_VECTOR* ideal, int speed);
extern void CheckForRichesIllegalDiagonalWalls();

#endif