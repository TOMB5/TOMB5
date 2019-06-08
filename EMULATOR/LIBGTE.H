#ifndef LIBGTE_H
#define LIBGTE_H

#include "TYPES.H"

typedef struct {
	short	m[3][3];	/* 3x3 rotation matrix */
	long    t[3];		/* transfer vector */
} MATRIX;

typedef struct {		/* long word type 3D vector */
	long	vx, vy;
	long	vz, pad;
} VECTOR;

struct SVECTOR {		/* short word type 3D vector */
	short	vx, vy;
	short	vz, pad;
};

struct CVECTOR {		/* color type vector */
	unsigned char	r, g, b, cd;
};

typedef struct {		/* 2D short vector */
	short vx, vy;
} DVECTOR;

extern void InitGeom();
extern void SetGeomOffset(int ofx, int ofy);
extern void SetGeomScreen(int h);

#endif