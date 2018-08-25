#ifndef GLOBAL_H
#define GLOBAL_H

#define phd_sqrt_asm phd_sqrt


#include "SPECTYPES.H"

extern struct WINAPP App;

#define mPushUnitMatrix phd_PushUnitMatrix
#define mPopMatrix phd_PopMatrix

#ifdef __cplusplus
extern "C" {
#endif

	extern uint32	phd_sqrt(uint32 n);

#define InitDXStruct(s) memset(&(s),0,sizeof(s)),(s).dwSize=sizeof(s)
#define ZeroArray(a) memset((a),0,sizeof(a))

#define		ERR_SOUND_NOT_ENABLED	(-3)
#define		ERR_SOUND_FAILED		(-2)
#define		ERR_SOUND_NO_FREE_SLOTS	(-1)


extern	char*		malloc_buffer;
extern	int			script_malloc_size;
extern	int			malloc_size;
extern	int			malloc_free, malloc_used;
extern	char*		malloc_ptr;

extern sint32		phd_left;  				/* Left Clipping Value */
extern sint32		phd_right;              /* Right Clipping Value */
extern sint32		phd_top;                /* Top Clipping Value */
extern sint32		phd_bottom;             /* Bottom Clipping Value */
extern sint16		phd_winxmin;
extern sint16		phd_winymin;
extern sint16		phd_winxmax;        	/* Maximum Window X coord*/
extern sint16		phd_winymax;        	/* Maximum Window Y coord*/
extern sint32		phd_winwidth;       	/* Window Width*/
extern sint32		phd_winheight;      	/* Window Height*/
extern sint32		phd_centerx;        	/* Vanishing point X*/
extern sint32		phd_centery;        	/* Vanishing point Y*/
extern sint32		phd_znear;          	/* Distance to near clip plane in View.Frame*/
extern sint32		phd_zfar;           	/* Distance to far clip plane in View.Frame*/
extern sint32		phd_viewdist;       	/* Distance you can see in World.Frame*/
extern sint32		phd_scrwidth;       	/* Width of Screen ie. 320 or 640*/
extern sint32		phd_scrheight;       	/* Height of Screen ie. 200 or 480*/
extern sint32		phd_persp;				/* perspective thang*/
extern sint32		*phd_mxptr;				/* matrix pointer....*/
extern sint32		phd_oopersp;
extern float* phd_dxptr;

extern	float		one;				// in 3dinsert.cpp
extern	float		f_znear;			// phd_znear
extern	float		f_zfar;				// phd_zfar
extern	float		f_oneoznear;		// one / phd_znear
extern	float		f_persp;			// phd_persp
extern	float		f_oneopersp;		// one / phd_persp
extern	float		f_perspoznear;		// phd_persp / phd_znear
extern	float		f_centerx;			// phd_centrex
extern	float		f_centery;			// phd_centrey
extern	float		f_invzfar;			// 1.0/phd_zfar (actually 65535/65536 at the moment)
extern	float		f_oneozfar;			// one/phd_zfar
extern	float		f_a, f_b, f_boo;		// a/b factors for z buffering (f_boo is f_b/one)

extern	sint32		w2v_matrix[];		// World to View Matrix...
extern	sint32		matrix_stack[];		// matrix stack for animations etc..

extern struct SVECTOR CamRot;

#define EndOfArray(a) ((a)+ArraySize(a))

extern void D3DIdentityMatrix(LPD3DMATRIX mat);
extern void SetD3DMatrixF(LPD3DMATRIX dst, LPD3DMATRIX src);
extern void phd_RotX(long angle);
extern void phd_RotY(long angle);
extern void phd_RotZ(long angle);
extern void phd_PushMatrix();
extern void phd_PushUnitMatrix();
extern void phd_UnitMatrix();
extern void phd_TransposeMatrix();
extern void phd_TranslateAbs(long x, long y, long z);
extern void phd_RotYXZ(long y, long x, long z);
extern unsigned long mGetAngle(long x1, long y1, long x2, long y2);
#define phd_PopMatrix()		{ phd_mxptr -= 12; phd_dxptr -= 12; }

#ifdef __cplusplus
}
#endif

extern WATERTAB	WaterTable[22][64];
extern bool thread_started;;

void WaitUntilFalse(DWORD* ptr);
void WaitUntilTrue(DWORD* ptr);
void Sleep1ms();
void* GetSleepFunc();


#endif