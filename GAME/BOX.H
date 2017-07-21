#ifndef BOX_H
#define BOX_H

#define BOX_BLOCKED (1 << 14)
#define BOX_LAST    (1 << 15)

struct box_info
{
	unsigned char left;
	unsigned char right;
	unsigned char top;
	unsigned char bottom;
	short height;
	short overlap_index;
};

extern int number_boxes;
extern struct box_info* boxes;
extern unsigned short* overlap;
extern short* ground_zone[5][2];
extern unsigned short testclip;
extern unsigned short loops;

#endif