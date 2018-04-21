#ifndef MATHS_H
#define MATHS_H

#include "TYPES.H"

#define phd_PushMatrix		mPushMatrix
#define phd_PopMatrix		mPopMatrix
#define phd_PushUnitMatrix 	mPushUnitMatrix
#define phd_TranslateRel		mTranslateXYZ
#define phd_TranslateAbs 	mTranslateAbsXYZ
#define phd_RotX			mRotX
#define phd_RotY    		mRotY
#define phd_RotZ			mRotZ
#define phd_RotYXZ			mRotYXZ
#define phd_RotYXZpack		mRotPackedYXZ
#define gar_RotYXZsuperpack	mRotSuperPackedYXZ

#define InitInterpolate		InitInterpolation
#define phd_PushMatrix_I		iPushMatrix
#define phd_PopMatrix_I		iPopMatrix
#define phd_TranslateRel_I	iTranslateXYZ
#define phd_TranslateRel_ID	iTranslateXYZ2
#define phd_RotX_I(ang)		{ mRotX(ang); iRotX(ang); }
#define phd_RotY_I(ang)		{ mRotY(ang); iRotY(ang); }
#define phd_RotZ_I(ang)		{ mRotZ(ang); iRotZ(ang); }
#define phd_RotYXZ_I(x, y, z)	{ mRotYXZ(x, y, z); iRotYXZ(x, y, z); }
#define gar_RotYXZsuperpack_I(p1, p2, s) { mRotSuperPackedYXZ(p1, s); iRotSuperPackedYXZ(p2, s); }

#define mPopMatrix()		phd_mxptr -= 12

extern long phd_sqrt_asm(long val);

extern	int	*phd_mxptr;			// Pointer to Current Matrix...

#endif