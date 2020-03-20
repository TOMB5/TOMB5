#ifndef GLOBAL_H
#define GLOBAL_H
#define D3D_OVERLOADS
#define phd_sqrt_asm phd_sqrt


#include "SPECTYPES.H"

extern struct WINAPP App;

#define AnimTextureRanges App.AnimTextureRanges

#define mPushUnitMatrix phd_PushUnitMatrix
#define mPopMatrix phd_PopMatrix

#ifdef __cplusplus
//extern "C" {
#endif

	extern uint32	phd_sqrt(uint32 n);

#define InitDXStruct(s) memset(&(s),0,sizeof(s)),(s).dwSize=sizeof(s)
#define ZeroArray(a) memset((a),0,sizeof(a))

#define		ERR_SOUND_NOT_ENABLED	(-3)
#define		ERR_SOUND_FAILED		(-2)
#define		ERR_SOUND_NO_FREE_SLOTS	(-1)

	extern BYTE tsv_buffer[];

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
extern float flt_878658[32];
extern float clip_xmin;
extern float clip_xmax;
extern float clip_ymin;
extern float clip_ymax;
extern float f_persp_bis;
extern float f_znear3;
extern float f_persp_bis_over_znear3;
extern float LfAspectCorrection;
extern float flt_55D1F8;
extern float dword_50A440;
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
	extern float		w2v_matrix_f[];
extern	sint32		matrix_stack[];		// matrix stack for animations etc..
	extern float		matrix_stack_dx[];
	extern float		sin_flt_table[];
	extern D3DMATRIX w2v_matrix_d3d;
extern struct SVECTOR CamRot;

extern WORD* d9ab34;
extern int e4b100;
extern int d9ab1c;
extern int d9ab10;
extern DWORD dword_921684;
extern DWORD dword_7EE0D4;
extern DWORD dword_57A018;
extern LPSTR reg_class;
extern DWORD dword_C87BF0;
extern DWORD dword_C86BE8;
extern DWORD dword_C713D4;
extern DWORD dword_C713DC;
extern DWORD dword_C713E0;

extern DWORD dword_51CE58;

extern D3DMATRIX transform_projection;
extern PHD_VECTOR lookatpos;
#define EndOfArray(a) ((a)+ArraySize(a))
extern void phd_QuickW2VMatrix(float a1, float a2, float a3, int a4, int a5, int a6, int a7);
extern void D3DNormalise(LPD3DMATRIX m);
extern void HandleApp(LPARAM lParam, WPARAM wParam);
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
extern void phd_TranslateRel(long x, long y, long z);
extern void phd_RotYXZ(long y, long x, long z);
extern void phd_SetTrans(long x, long y, long z);
extern void SetD3DViewMatrix();
extern unsigned long mGetAngle(long x1, long y1, long x2, long y2);
extern void S_InitD3DMatrix();
extern void phd_LookAt(int32_t xsrc, int32_t ysrc, int32_t zsrc, int32_t xtar, int32_t ytar, int32_t ztar, short roll);
extern void phd_GetVectorAngles(int32_t x, int32_t y, int32_t z, short* dest);
extern void SetViewMatrix();
extern void ScaleCurrentMatrix(VECTOR vec);
extern void mRotSuperPackedYXZ(short** a0, long a1);
extern void gte_sttr(PHD_VECTOR *v);
#define phd_PopMatrix()		{ phd_mxptr -= 12; phd_dxptr -= 12; }

#define mPushMatrix phd_PushMatrix
#define mPopMatrix phd_PopMatrix
#define mRotYXZ phd_RotYXZ
#define mTranslateXYZ phd_TranslateRel
#define mTranslateAbsXYZ phd_TranslateAbs
#define mSetTrans phd_SetTrans
void updateAnimFrame(PACKNODE* node, int flags, short* frame);
#ifdef __cplusplus
//}
#endif

extern WATERTAB	WaterTable[22][64];
extern bool thread_started;;

void WaitUntilFalse(DWORD* ptr);
void WaitUntilTrue(DWORD* ptr);
void Sleep1ms();
void* GetSleepFunc();


#endif