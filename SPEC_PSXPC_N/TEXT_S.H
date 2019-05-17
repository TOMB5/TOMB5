#ifndef TEXT_S_H
#define TEXT_S_H

#include "TYPES.H"

extern void UpdatePulseColour();
extern void PrintString(unsigned short x, unsigned short y, unsigned char colourFlag, char* string, unsigned short flag);
extern int GetStringLength(char* string, unsigned short* a1, unsigned short* a2);
extern void GetStringDimensions(char* string, unsigned short* w, unsigned short* h);
extern void DrawChar(unsigned short a0, unsigned short a1, unsigned short colourFlag, struct CHARDEF* a3);
extern void draw_outlines();
extern char aUEAAAAEEEAAEOO[];
extern CHARDEF word_9230E[];
extern CHARDEF loc_92020[];

enum font_flags
{
	FF_NONE = (0 << 0), // 0x0000
	FF_UNK0 = (1 << 0),	// 0x0001
	FF_UNK1 = (1 << 1),	// 0x0002
	FF_UNK2 = (1 << 2),	// 0x0004
	FF_UNK3 = (1 << 3),	// 0x0008
	FF_UNK4 = (1 << 4),	// 0x0010
	FF_UNK5 = (1 << 5),	// 0x0020
	FF_UNK6 = (1 << 6),	// 0x0040
	FF_UNK7 = (1 << 7),	// 0x0080
	FF_UNK8 = (1 << 8),	// 0x0100
	FF_UNK9 = (1 << 9),	// 0x0200
	FF_UNK10 = (1 << 10),	// 0x0400
	FF_UNK11 = (1 << 11),	// 0x0800
	FF_SMALL = (1 << 12),	// 0x1000
	FF_UNK13 = (1 << 13),	// 0x2000
	FF_R_JUSTIFY = (1 << 14),	// 0x4000
	FF_CENTER = (1 << 15),	// 0x8000
};

#endif