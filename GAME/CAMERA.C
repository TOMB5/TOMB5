#include "CAMERA.H"

#include "GAMEFLOW.H"
#include "LARA.H"

long BinocularRange;
long BinocularOn;
long BinocularOldCamera;
long LaserSight;
long InfraRed;
char SniperCount;
char SniperCamActive;
long ExittingBinos;
long TooFarCount;
long CombatShift;
unsigned char camerasnaps;
unsigned char TargetSnaps;
char TLFlag;
char LSHKShotsFired;
char LSHKTimer;
struct CAMERA_INFO camera;
char UseForcedFixedCamera;
struct GAME_VECTOR ForcedFixedCamera;
long NumFixedCameras;
int number_cameras;
struct PHD_VECTOR CamOldPos;
struct SHATTER_ITEM ShatterItem;
struct GAME_VECTOR static_lookcamp;
struct GAME_VECTOR static_lookcamt;
struct OLD_CAMERA old_cam;
struct GAME_VECTOR last_ideal;
struct GAME_VECTOR last_target;

void InitialiseCamera()//25AAC
{
	last_target.x = lara_item->pos.x_pos;
	camera.target.x = lara_item->pos.x_pos;
	camera.shift = lara_item->pos.y_pos - 1024;
	camera.fixed_camera = lara_item->pos.y_pos - 1024;
	camera.target.y = lara_item->pos.y_pos - 1024;

	last_target.z = lara_item->pos.x_rot;

	camera.target.z = lara_item->pos.x_rot;
	camera.pos.y = lara_item->pos.y_pos - 1024;
	camera.target_distance = 1536;
	camera.number_frames = 1;
	camera.speed = 1;
	camera.flags = 1;
	camera.pos.x = lara_item->pos.x_pos;
	camera.pos.z = lara_item->pos.x_rot - 100;
	camera.item->floor = 0;
	camera.type = CHASE_CAMERA;
	camera.number = -1;
	camera.fixed_camera = 0;

	last_target.room_number = nframes;//CHECK @a2 lhu
	camera.target.room_number = nframes;
	camera.pos.room_number = nframes;
	
	//AlterFOV();
	
	int a0 = 16380;
	UseForcedFixedCamera = 0;
	//CalculateCamera();
}