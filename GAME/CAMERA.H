#ifndef CAMERA_H
#define CAMERA_H

#include "SPECTYPES.H"

extern long BinocularRange;
extern long BinocularOn;
extern long BinocularOldCamera;
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
extern CAMERA_INFO camera;
extern char UseForcedFixedCamera;
extern GAME_VECTOR ForcedFixedCamera;
extern long NumFixedCameras;
extern int number_cameras;
extern PHD_VECTOR CamOldPos;
extern SHATTER_ITEM ShatterItem;
extern GAME_VECTOR static_lookcamp;
extern GAME_VECTOR static_lookcamt;
extern OLD_CAMERA old_cam;
extern GAME_VECTOR last_ideal;
extern GAME_VECTOR last_target;
extern short rcossin_tbl[];

extern void InitialiseCamera();
extern void AlterFOV(short fov);
extern void CalculateCamera();
extern void BinocularCamera(ITEM_INFO* item);
extern void LookCamera(ITEM_INFO* item);
extern void CombatCamera(ITEM_INFO* item);
extern void FixedCamera();
extern void ChaseCamera(ITEM_INFO* item);
extern void ConfirmCameraTargetPos();
extern void ScreenShake(ITEM_INFO* item, short MaxVal, short MaxDist);
extern void UpdateCameraElevation();
extern void LaraTorch(PHD_VECTOR* Soffset, PHD_VECTOR* Eoffset, short yrot, long brightness);
extern long mgLOS(GAME_VECTOR* start, GAME_VECTOR* target, long push);
extern long CameraCollisionBounds(GAME_VECTOR* ideal, long push, long yfirst);
extern void MoveCamera(GAME_VECTOR* ideal, int speed);

#endif