#ifndef PSXINPUT_H
#define PSXINPUT_H

#include "SPECTYPES.H"

#define P_L2       (1 << 0)
#define P_R2       (1 << 1)
#define P_L1       (1 << 2)
#define P_R1       (1 << 3)
#define P_TRIANGLE (1 << 4)
#define P_CIRCLE   (1 << 5)
#define P_CROSS    (1 << 6)
#define P_SQUARE   (1 << 7)
#define P_SELECT   (1 << 8)
#define P_UNK_9    (1 << 9)
#define P_UNK_10   (1 << 10)
#define P_START    (1 << 11)
#define P_UP       (1 << 12)
#define P_RIGHT    (1 << 13)
#define P_DOWN     (1 << 14)
#define P_LEFT     (1 << 15)

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
extern volatile ControllerPacket GPad1;
extern volatile ControllerPacket GPad2;
extern unsigned long Edge2;
extern struct GouraudBarColourSet healthBarColourSet;
extern struct GouraudBarColourSet poisonBarColourSet;
extern struct GouraudBarColourSet airBarColourSet;
extern struct GouraudBarColourSet dashBarColourSet;

extern void S_UpdateInput();
extern void InitialisePadSubsystem();

#endif