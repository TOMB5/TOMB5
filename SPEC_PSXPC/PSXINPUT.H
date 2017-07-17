#ifndef PSXINPUT_H
#define PSXINPUT_H

struct pad_configs
{
	unsigned long pad_L2;
	unsigned long pad_R2;
	unsigned long pad_L1;
	unsigned long pad_R1;
	unsigned long pad_triangle;
	unsigned long pad_square;
	unsigned long pad_circle;
	unsigned long pad_cross;
};

struct MouseData
{
	unsigned short buttons;
	char xOffset;
	char yOffset;
};

struct NegconData
{
	unsigned short digitalButtons;
	char centralTwist;
	char buttonI;
	char buttonII;
	char topLeft;
};

struct GunConData
{
	unsigned short digitalButtons;
	unsigned char GunconX;
	unsigned char GunConScreenDiv;
	unsigned char GunconY;
	unsigned char pad;
};

struct AnalogjoyData
{
	unsigned short digitalButtons;
	unsigned char right_x;
	unsigned char right_y;
	unsigned char left_x;
	unsigned char left_y;
};

struct AnalogController
{
	unsigned short digitalButtons;
	unsigned char right_x;
	unsigned char right_y;
	unsigned char left_x;
	unsigned char left_y;
};

struct fake85
{
	unsigned short pad;
	struct NegconData negcon;
	struct AnalogController Analog;
};

struct TapCtrllerData
{
	unsigned char transStatus;
	unsigned char dataFormat;
	struct fake85 data;
};

struct MultiTapData
{
	struct TapCtrllerData ctrllers[4];
};

struct fake76
{
	unsigned short pad;
	struct MouseData mouse;
	struct NegconData negcon;
	struct AnalogjoyData joystick;
	struct MultiTapData tap;
	struct GunConData guncon;
	struct AnalogController analog;
};

struct ControllerPacket
{
	unsigned char transStatus;
	unsigned char dataFormat;
	struct fake76 data;
};

struct GouraudBarColourSet
{
	unsigned char abLeftRed[5];
	unsigned char abLeftGreen[5];
	unsigned char abLeftBlue[5];
	unsigned char abRightRed[5];
	unsigned char abRightGreen[5];
	unsigned char abRightBlue[5];
};

extern unsigned char DualShock;
extern unsigned char PadConnected;
extern short reset_count;
extern char SayNoCount;
extern long input;
extern long dbinput;
extern long dbinput2;
extern long inputBusy;
extern long RawPad;
extern long RawEdge;
extern unsigned char Motors[2];
extern long LaraLookY;
extern long LaraLookX;
extern struct ControllerPacket GPad1;
extern struct ControllerPacket GPad2;
extern unsigned long Edge2;
extern struct GouraudBarColourSet healthBarColourSet;
extern struct GouraudBarColourSet poisonBarColourSet;
extern struct GouraudBarColourSet airBarColourSet;
extern struct GouraudBarColourSet dashBarColourSet;

extern void S_UpdateInput();

#endif