#ifndef LARATWOGUN_H
#define LARATWOGUN_H

#include "CAMERA.H"

struct TWOGUN_INFO
{
	struct PHD_3DPOS pos;
	short life;
	short coil;
	short spin;
	short spinadd;
	short length;
	short dlength;
	short size;
	char r;
	char g;
	char b;
	char fadein;
};

#endif