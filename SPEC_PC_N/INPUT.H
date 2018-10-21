#ifndef _INPUT_H_
#define _INPUT_H_

#include "SPECTYPES.H"

enum IKEYS
{
	KEY_FORWARD = 0,
	KEY_BACK = 1,
	KEY_LEFT = 2,
	KEY_RIGHT = 3,
	KEY_DUCK = 4,
	KEY_SPRINT = 5,
	KEY_WALK = 6,
	KEY_JUMP = 7,
	KEY_ACTION = 8,
	KEY_DRAW = 9,
	KEY_FLARE = 10,
	KEY_LOOK = 11,
	KEY_ROLL = 12,
	KEY_OPTION = 13,
	KEY_STEPL = 14,
	KEY_STEPR = 15,
	KEY_PAUSE = 16,
	KEY_SELECT = 17,
};

extern short mouse_x;
extern short mouse_y;
extern int mouse_vkeys;

#ifdef __cplusplus
extern "C" {
#endif

	// The global input variable
	extern sint32 input;
	extern sint32 dbinput;
	extern sint32 inputBusy;


	extern int bLaraOn;
	extern int bRoomOn;
	extern int bObjectOn;
	extern int bAObjectOn;
	extern int bEffectOn;


	

#ifdef __cplusplus
}
#endif

extern int S_UpdateInput();

extern int joy_x, joy_y, joy_fire;

extern unsigned char keymap[];
extern int32_t conflict[];
extern int16_t layout[2][18];
#define rawkey(A) (keymap[A] & 0x80)





#endif