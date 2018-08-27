#ifndef _INPUT_H_
#define _INPUT_H_

#include "SPECTYPES.H"

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

extern char*		kname[];
extern int			conflict[];
extern int joy_x, joy_y, joy_fire;

extern unsigned char keymap[];
extern int16_t layout[2][18];
#define rawkey(A) (keymap[A] & 0x80)





#endif