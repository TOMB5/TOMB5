#ifndef SPHERE_H
#define SPHERE_H

struct SPHERE
{
	long x;
	long y;
	long z;
	long r;
};

extern char GotLaraSpheres;
extern int NumLaraSpheres;
extern struct SPHERE LaraSpheres[15];
extern struct SPHERE Slist[34];

#endif