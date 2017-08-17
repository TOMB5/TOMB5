#ifndef PSXINPUT_H
#define PSXINPUT_H

#include "PSXTYPES.H"

#define L2       (1 << 0)
#define R2       (1 << 1)
#define L1       (1 << 2)
#define R1       (1 << 3)
#define TRIANGLE (1 << 4)
#define CIRCLE   (1 << 5)
#define CROSS    (1 << 6)
#define SQUARE   (1 << 7)
#define SELECT   (1 << 8)
#define UNK_9    (1 << 9)
#define UNK_10   (1 << 10)
#define START    (1 << 11)
#define UP       (1 << 12)
#define RIGHT    (1 << 13)
#define DOWN     (1 << 14)
#define LEFT     (1 << 15)

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