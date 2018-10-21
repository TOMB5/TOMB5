#ifndef SPECTYPES_H
#define SPECTYPES_H

#define INPUT_H "PSXINPUT.H"
#define CMATH_H "LIBMATH.H"

#include "TYPES.H"

#ifdef PAELLA
#define exit(x) exit()
#define _STDDEF_H
#define INLINE_H "PAELLA.H"
#define ASSEMBLER
#define _WCHAR_T
#endif

#include "TYPES.H"

#ifdef PAELLA

#define LMAX 256

#ifndef NULL
#define NULL 0		       /* null pointer constant */
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned int size_t;  /* result type of the sizeof operator (ANSI) */
#endif

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif
	/* To avoid conflicting */
	extern void *memcpy(void *, void *, int);
	extern void *memmove(void *, const void *, int);
	/* To avoid conflicting */
	extern int   memcmp(void *, void *, int);
	extern void *memchr(const void *, int, int);
	extern void *memset(void *, int, int);

	extern void *bcopy(const void *, void *, int); /* src,dest */
	extern void *bzero(void *, int);
	extern int   bcmp(const void *, const void *, int);
#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif
	extern char *strcat(char *, const char *);
	extern char *strncat(char *, const char *, int);
	extern int   strcmp(char *, char *);
	extern int   strncmp(const char *, const char *, int);
	extern char *strcpy(char *, char *);
	extern char *strncpy(char *, const char *, int);
	extern int   strlen(char *);
	extern char *index(const char *, char);
	extern char *rindex(const char *, char);

	extern char *strchr(const char *, char);
	extern char *strrchr(const char *, char);
	extern char *strpbrk(const char *, const char *);
	extern int   strspn(const char *, const char *);
	extern int   strcspn(const char *, const char *);
	extern char *strtok(char *, const char *);
	extern char *strstr(const char *, const char *);
#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#define strdup(p)	( strcpy(malloc(strlen(p)+1),p); )



#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif

	extern void InitGeom();

	extern void EigenMatrix(struct MATRIX3D *m, struct MATRIX3D *t);
	extern int  IsIdMatrix(struct MATRIX3D *m);
	extern struct MATRIX3D *MulMatrix0(struct MATRIX3D *m0, struct MATRIX3D *m1, struct MATRIX3D *m2);
	extern struct MATRIX3D *MulRotMatrix0(struct MATRIX3D *m0, struct MATRIX3D *m1);
	extern struct MATRIX3D *MulMatrix(struct MATRIX3D *m0, struct MATRIX3D *m1);
	extern struct MATRIX3D *MulMatrix2(struct MATRIX3D *m0, struct MATRIX3D *m1);
	extern struct MATRIX3D *MulRotMatrix(struct MATRIX3D *m0);
	extern struct MATRIX3D *SetMulMatrix(struct MATRIX3D *m0, struct MATRIX3D *m1);
	extern struct MATRIX3D *SetMulRotMatrix(struct MATRIX3D *m0);
	extern struct VECTOR *ApplyMatrix(struct MATRIX3D *m, struct SVECTOR *v0, struct VECTOR *v1);
	extern struct VECTOR *ApplyRotMatrix(struct SVECTOR *v0, struct VECTOR *v1);
	extern struct VECTOR *ApplyRotMatrixLV(struct VECTOR *v0, struct VECTOR *v1);
	extern struct VECTOR *ApplyMatrixLV(struct MATRIX3D *m, struct VECTOR *v0, struct VECTOR *v1);
	extern struct SVECTOR *ApplyMatrixSV(struct MATRIX3D *m, struct SVECTOR *v0, struct SVECTOR *v1);
	extern struct VECTOR *ApplyTransposeMatrixLV(struct MATRIX3D *m, struct VECTOR *v0, struct VECTOR *v1);
	extern struct MATRIX3D *RotMatrix(struct SVECTOR *r, struct MATRIX3D *m);
	extern struct MATRIX3D *RotMatrixXZY(struct SVECTOR *r, struct MATRIX3D *m);
	extern struct MATRIX3D *RotMatrixYXZ(struct SVECTOR *r, struct MATRIX3D *m);
	extern struct MATRIX3D *RotMatrixYZX(struct SVECTOR *r, struct MATRIX3D *m);
	extern struct MATRIX3D *RotMatrixZXY(struct SVECTOR *r, struct MATRIX3D *m);
	extern struct MATRIX3D *RotMatrixZYX(struct SVECTOR *r, struct MATRIX3D *m);
	extern struct MATRIX3D *RotMatrix_gte(struct SVECTOR *r, struct MATRIX3D *m);
	extern struct MATRIX3D *RotMatrixYXZ_gte(struct SVECTOR *r, struct MATRIX3D *m);
	extern struct MATRIX3D *RotMatrixZYX_gte(struct SVECTOR *r, struct MATRIX3D *m);
	extern struct MATRIX3D *RotMatrixX(long r, struct MATRIX3D *m);
	extern struct MATRIX3D *RotMatrixY(long r, struct MATRIX3D *m);
	extern struct MATRIX3D *RotMatrixZ(long r, struct MATRIX3D *m);
	extern struct MATRIX3D *RotMatrixC(struct SVECTOR *r, struct MATRIX3D *m);
	extern struct MATRIX3D *TransMatrix(struct MATRIX3D *m, struct VECTOR *v);
	extern struct MATRIX3D *ScaleMatrix(struct MATRIX3D *m, struct VECTOR *v);
	extern struct MATRIX3D *ScaleMatrixL(struct MATRIX3D *m, struct VECTOR *v);
	extern struct MATRIX3D *TransposeMatrix(struct MATRIX3D *m0, struct MATRIX3D *m1);
	extern struct MATRIX3D *CompMatrix(struct MATRIX3D *m0, struct MATRIX3D *m1, struct MATRIX3D *m2);
	extern struct MATRIX3D *CompMatrixLV(struct MATRIX3D *m0, struct MATRIX3D *m1, struct MATRIX3D *m2);

	extern void MatrixNormal(struct MATRIX3D *m, struct MATRIX3D *n);
	extern void MatrixNormal_0(struct MATRIX3D *m, struct MATRIX3D *n);
	extern void MatrixNormal_1(struct MATRIX3D *m, struct MATRIX3D *n);
	extern void MatrixNormal_2(struct MATRIX3D *m, struct MATRIX3D *n);

	extern void SetRotMatrix(struct MATRIX3D *m);
	extern void SetLightMatrix(struct MATRIX3D *m);
	extern void SetColorMatrix(struct MATRIX3D *m);
	extern void SetTransMatrix(struct MATRIX3D *m);
	extern void PushMatrix();
	extern void PopMatrix();
	extern void ReadRotMatrix(struct MATRIX3D *m);
	extern void ReadLightMatrix(struct MATRIX3D *m);
	extern void ReadColorMatrix(struct MATRIX3D *m);
	extern void SetRGBcd(struct CVECTOR *v);
	extern void SetBackColor(long rbk, long gbk, long bbk);
	extern void SetFarColor(long rfc, long gfc, long bfc);
	extern void SetGeomOffset(long ofx, long ofy);
	extern void SetGeomScreen(long h);
	extern void ReadSZfifo3(long *sz0, long *sz1, long *sz2);
	extern void ReadSZfifo4(long *szx, long *sz0, long *sz1, long *sz2);
	extern void ReadSXSYfifo(long *sxy0, long *sxy1, long *sxy2);
	extern void ReadRGBfifo(struct CVECTOR *v0, struct CVECTOR *v1, struct CVECTOR *v2);
	extern void ReadGeomOffset(long *ofx, long *ofy);
	extern long ReadGeomScreen();

	extern void TransRot_32(struct VECTOR *v0, struct VECTOR *v1, long *flag);
	extern long TransRotPers(struct SVECTOR *v0, long *sxy, long *p, long *flag);
	extern long TransRotPers3(struct SVECTOR *v0, struct SVECTOR *v1, struct SVECTOR *v2, long *sxy0,
		long *sxy1, long *sxy2, long *p, long *flag);

	extern void pers_map(int abuf, struct SVECTOR **vertex, int tex[4][2], unsigned short *dtext);
	extern void PhongLine(int istart_x, int iend_x, int p, int q, unsigned short **pixx,
		int fs, int ft, int i4, int det);

	extern long RotTransPers(struct SVECTOR *v0, long *sxy, long *p, long *flag);
	extern long RotTransPers3(struct SVECTOR *v0, struct SVECTOR *v1, struct SVECTOR *v2,
		long *sxy0, long *sxy1, long *sxy2, long *p, long *flag);
	extern void RotTrans(struct SVECTOR *v0, struct VECTOR *v1, long *flag);
	extern void RotTransSV(struct SVECTOR *v0, struct SVECTOR *v1, long *flag);
	extern void LocalLight(struct SVECTOR *v0, struct VECTOR *v1);
	extern void LightColor(struct VECTOR *v0, struct VECTOR *v1);
	extern void DpqColorLight(struct VECTOR *v0, struct CVECTOR *v1, long p, struct CVECTOR *v2);
	extern void DpqColor(struct CVECTOR *v0, long p, struct CVECTOR *v1);
	extern void DpqColor3(struct CVECTOR *v0, struct CVECTOR *v1, struct CVECTOR *v2,
		long p, struct CVECTOR *v3, struct CVECTOR *v4, struct CVECTOR *v5);
	extern void Intpl(struct VECTOR *v0, long p, struct CVECTOR *v1);
	extern struct VECTOR *Square12(struct VECTOR *v0, struct VECTOR *v1);
	extern struct VECTOR *Square0(struct VECTOR *v0, struct VECTOR *v1);
	extern struct VECTOR *SquareSL12(struct SVECTOR *v0, struct VECTOR *v1);
	extern struct VECTOR *SquareSL0(struct SVECTOR *v0, struct VECTOR *v1);
	extern struct SVECTOR *SquareSS12(struct SVECTOR *v0, struct SVECTOR *v1);
	extern struct SVECTOR *SquareSS0(struct SVECTOR *v0, struct SVECTOR *v1);
	extern void NormalColor(struct SVECTOR *v0, struct CVECTOR *v1);
	extern void NormalColor3(struct SVECTOR *v0, struct SVECTOR *v1, struct SVECTOR *v2,
		struct CVECTOR *v3, struct CVECTOR *v4, struct CVECTOR *v5);
	extern void NormalColorDpq(struct SVECTOR *v0, struct CVECTOR *v1, long p, struct CVECTOR *v2);
	extern void NormalColorDpq3(struct SVECTOR *v0, struct SVECTOR *v1, struct SVECTOR *v2, struct CVECTOR *v3,
		long p, struct CVECTOR *v4, struct CVECTOR *v5, struct CVECTOR *v6);
	extern void NormalColorCol(struct SVECTOR *v0, struct CVECTOR *v1, struct CVECTOR *v2);
	extern void NormalColorCol3(struct SVECTOR *v0, struct SVECTOR *v1, struct SVECTOR *v2, struct CVECTOR *v3,
		struct CVECTOR *v4, struct CVECTOR *v5, struct CVECTOR *v6);
	extern void ColorDpq(struct VECTOR *v0, struct CVECTOR *v1, long p, struct CVECTOR *v2);
	extern void ColorCol(struct VECTOR *v0, struct CVECTOR *v1, struct CVECTOR *v2);
	extern long NormalClip(long sxy0, long sxy1, long sxy2);
	extern long AverageZ3(long sz0, long sz1, long sz2);
	extern long AverageZ4(long sz0, long sz1, long sz2, long sz3);
	extern void OuterProduct12(struct VECTOR *v0, struct VECTOR *v1, struct VECTOR *v2);
	extern void OuterProduct0(struct VECTOR *v0, struct VECTOR *v1, struct VECTOR *v2);
	extern long Lzc(long data);


	extern long RotTransPers4(struct SVECTOR *v0, struct SVECTOR *v1, struct SVECTOR *v2, struct SVECTOR *v3,
		long *sxy0, long *sxy1, long *sxy2, long *sxy3,
		long *p, long *flag);
	extern void RotTransPersN(struct SVECTOR *v0, struct DVECTOR *v1, unsigned short *sz, unsigned short *p,
		unsigned short *flag, long n);
	extern void RotTransPers3N(struct SVECTOR *v0, struct DVECTOR *v1, unsigned short *sz, unsigned short *flag,
		long n);
	extern void RotMeshH(short *Yheight, struct DVECTOR *Vo, unsigned short *sz, unsigned short *flag,
		short Xoffset, short Zoffset, short m, short n,
		struct DVECTOR *base);
	extern long RotAverage3(struct SVECTOR *v0, struct SVECTOR *v1, struct SVECTOR *v2,
		long *sxy0, long *sxy1, long *sxy2, long *p, long *flag);
	extern long RotAverage4(struct SVECTOR *v0, struct SVECTOR *v1, struct SVECTOR *v2, struct SVECTOR *v3,
		long *sxy0, long *sxy1, long *sxy2, long *sxy3,
		long *p, long *flag);
	extern long RotNclip3(struct SVECTOR *v0, struct SVECTOR *v1, struct SVECTOR *v2,
		long *sxy0, long *sxy1, long *sxy2, long *p, long *otz,
		long *flag);
	extern long RotNclip4(struct SVECTOR *v0, struct SVECTOR *v1, struct SVECTOR *v2, struct SVECTOR *v3,
		long *sxy0, long *sxy1, long *sxy2, long *sxy3,
		long *p, long *otz, long *flag);
	extern long RotAverageNclip3(struct SVECTOR *v0, struct SVECTOR *v1, struct SVECTOR *v2,
		long *sxy0, long *sxy1, long *sxy2,
		long *p, long *otz, long *flag);
	extern long RotAverageNclip4(struct SVECTOR *v0, struct SVECTOR *v1, struct SVECTOR *v2, struct SVECTOR *v3,
		long *sxy0, long *sxy1, long *sxy2, long *sxy3,
		long *p, long *otz, long *flag);
	extern long RotColorDpq(struct SVECTOR *v0, struct SVECTOR *v1, struct CVECTOR *v2,
		long *sxy, struct CVECTOR *v3, long *flag);
	extern long RotColorDpq3(struct SVECTOR *v0, struct SVECTOR *v1, struct SVECTOR *v2,
		struct SVECTOR *v3, struct SVECTOR *v4, struct SVECTOR *v5, struct CVECTOR *v6,
		long *sxy0, long *sxy1, long *sxy2,
		struct CVECTOR *v7, struct CVECTOR *v8, struct CVECTOR *v9, long *flag);
	extern long RotAverageNclipColorDpq3(struct SVECTOR *v0, struct SVECTOR *v1, struct SVECTOR *v2,
		struct SVECTOR *v3, struct SVECTOR *v4, struct SVECTOR *v5, struct CVECTOR *v6,
		long *sxy0, long *sxy1, long *sxy2,
		struct CVECTOR *v7, struct CVECTOR *v8, struct CVECTOR *v9,
		long *otz, long *flag);
	extern long RotAverageNclipColorCol3(struct SVECTOR *v0, struct SVECTOR *v1, struct SVECTOR *v2,
		struct SVECTOR *v3, struct SVECTOR *v4, struct SVECTOR *v5, struct CVECTOR *v6,
		long *sxy0, long *sxy1, long *sxy2,
		struct CVECTOR *v7, struct CVECTOR *v8, struct CVECTOR *v9,
		long *otz, long *flag);
	extern long RotColorMatDpq(struct SVECTOR *v0, struct SVECTOR *v1, struct CVECTOR *v2, long *sxy,
		struct CVECTOR *v3, long matc, long flag);
	extern void ColorMatDpq(struct SVECTOR *v0, struct CVECTOR *v1, long p, struct CVECTOR *v2, long matc);
	extern void ColorMatCol(struct SVECTOR *v0, struct CVECTOR *v1, struct CVECTOR *v2, long matc);
	extern void LoadAverage12(struct VECTOR *v0, struct VECTOR *v1, long p0, long p1, struct VECTOR *v2);
	extern void LoadAverageShort12(struct SVECTOR *v0, struct SVECTOR *v1, long p0, long p1,
		struct SVECTOR *v2);
	extern void LoadAverage0(struct VECTOR *v0, struct VECTOR *v1, long p0, long p1, struct VECTOR *v2);
	extern void LoadAverageShort0(struct SVECTOR *v0, struct SVECTOR *v1, long p0, long p1,
		struct SVECTOR *v2);
	extern void LoadAverageByte(unsigned char *v0, unsigned char *v1, long p0, long p1, unsigned char *v2);
	extern void LoadAverageCol(unsigned char *v0, unsigned char *v1, long p0, long p1, unsigned char *v2);
	extern long VectorNormal(struct VECTOR *v0, struct VECTOR *v1);
	extern long VectorNormalS(struct VECTOR *v0, struct SVECTOR *v1);
	extern long VectorNormalSS(struct SVECTOR *v0, struct SVECTOR *v1);
	extern long SquareRoot0(long a);
	extern long SquareRoot12(long a);
	extern void InvSquareRoot(long a, long *b, long *c);
	extern void gteMIMefunc(struct SVECTOR *otp, struct SVECTOR *dfp, long n, long p);
	extern void SetFogFar(long a, long h);
	extern void SetFogNear(long a, long h);
	extern void SetFogNearFar(long a, long b, long h);
	extern void SubPol4(struct POL4 *p, struct SPOL *sp, int ndiv);
	extern void SubPol3(struct POL3 *p, struct SPOL *sp, int ndiv);

	extern int rcos(int a);
	extern int rsin(int a);
	extern int ccos(int a);
	extern int csin(int a);
	extern int cln(int a);
	extern int csqrt(int a);
	extern int catan(int a);
	extern long ratan2(long y, long x);


	extern void RotPMD_F3(long *pa, unsigned long *ot, int otlen, int id, int backc);
	extern void RotPMD_G3(long *pa, unsigned long *ot, int otlen, int id, int backc);
	extern void RotPMD_FT3(long *pa, unsigned long *ot, int otlen, int id, int backc);
	extern void RotPMD_GT3(long *pa, unsigned long *ot, int otlen, int id, int backc);
	extern void RotPMD_F4(long *pa, unsigned long *ot, int otlen, int id, int backc);
	extern void RotPMD_G4(long *pa, unsigned long *ot, int otlen, int id, int backc);
	extern void RotPMD_FT4(long *pa, unsigned long *ot, int otlen, int id, int backc);
	extern void RotPMD_GT4(long *pa, unsigned long *ot, int otlen, int id, int backc);

	extern void RotPMD_SV_F3(long *pa, long *va, unsigned long *ot, int otlen, int id,
		int backc);
	extern void RotPMD_SV_G3(long *pa, long *va, unsigned long *ot, int otlen, int id,
		int backc);
	extern void RotPMD_SV_FT3(long *pa, long *va, unsigned long *ot, int otlen, int id,
		int backc);
	extern void RotPMD_SV_GT3(long *pa, long *va, unsigned long *ot, int otlen, int id,
		int backc);
	extern void RotPMD_SV_F4(long *pa, long *va, unsigned long *ot, int otlen, int id,
		int backc);
	extern void RotPMD_SV_G4(long *pa, long *va, unsigned long *ot, int otlen, int id,
		int backc);
	extern void RotPMD_SV_FT4(long *pa, long *va, unsigned long *ot, int otlen, int id,
		int backc);
	extern void RotPMD_SV_GT4(long *pa, long *va, unsigned long *ot, int otlen, int id,
		int backc);


	extern void InitClip(struct EVECTOR *evbfad, long hw, long vw, long h, long near, long far);
	extern long Clip3F(struct SVECTOR *v0, struct SVECTOR *v1, struct SVECTOR *v2, struct EVECTOR **evmx);
	extern long Clip3FP(struct SVECTOR *v0, struct SVECTOR *v1, struct SVECTOR *v2, struct EVECTOR **evmx);
	extern long Clip4F(struct SVECTOR *v0, struct SVECTOR *v1, struct SVECTOR *v2, struct SVECTOR *v3,
		struct EVECTOR **evmx);
	extern long Clip4FP(struct SVECTOR *v0, struct SVECTOR *v1, struct SVECTOR *v2, struct SVECTOR *v3,
		struct EVECTOR **evmx);
	extern long Clip3FT(struct SVECTOR *v0, struct SVECTOR *v1, struct SVECTOR *v2,
		short *uv0, short *uv1, short *uv2, struct EVECTOR **evmx);
	extern long Clip3FTP(struct SVECTOR *v0, struct SVECTOR *v1, struct SVECTOR *v2,
		short *uv0, short *uv1, short *uv2, struct EVECTOR **evmx);
	extern long Clip4FT(struct SVECTOR *v0, struct SVECTOR *v1, struct SVECTOR *v2, struct SVECTOR *v3,
		short *uv0, short *uv1, short *uv2, short *uv3, struct EVECTOR **evmx);
	extern long Clip4FTP(struct SVECTOR *v0, struct SVECTOR *v1, struct SVECTOR *v2, struct SVECTOR *v3,
		short *uv0, short *uv1, short *uv2, short *uv3, struct EVECTOR **evmx);
	extern long Clip3G(struct SVECTOR *v0, struct SVECTOR *v1, struct SVECTOR *v2,
		struct CVECTOR *rgb0, struct CVECTOR *rgb1, struct CVECTOR *rgb2, struct EVECTOR **evmx);
	extern long Clip3GP(struct SVECTOR *v0, struct SVECTOR *v1, struct SVECTOR *v2,
		struct CVECTOR *rgb0, struct CVECTOR *rgb1, struct CVECTOR *rgb2, struct EVECTOR **evmx);
	extern long Clip4G(struct SVECTOR *v0, struct SVECTOR *v1, struct SVECTOR *v2, struct SVECTOR *v3,
		struct CVECTOR *rgb0, struct CVECTOR *rgb1, struct CVECTOR *rgb2, struct CVECTOR *rgb3,
		struct EVECTOR **evmx);
	extern long Clip4GP(struct SVECTOR *v0, struct SVECTOR *v1, struct SVECTOR *v2, struct SVECTOR *v3,
		struct CVECTOR *rgb0, struct CVECTOR *rgb1, struct CVECTOR *rgb2, struct CVECTOR *rgb3,
		struct EVECTOR **evmx);
	extern long Clip3GT(struct SVECTOR *v0, struct SVECTOR *v1, struct SVECTOR *v2,
		short *uv0, short *uv1, short *uv2,
		struct CVECTOR *rgb0, struct CVECTOR *rgb1, struct CVECTOR *rgb2,
		struct EVECTOR **evmx);
	extern long Clip3GTP(struct SVECTOR *v0, struct SVECTOR *v1, struct SVECTOR *v2,
		short *uv0, short *uv1, short *uv2,
		struct CVECTOR *rgb0, struct CVECTOR *rgb1, struct CVECTOR *rgb2,
		struct EVECTOR **evmx);
	extern long Clip4GT(struct SVECTOR *v0, struct SVECTOR *v1, struct SVECTOR *v2, struct SVECTOR *v3,
		short *uv0, short *uv1, short *uv2, short *uv3,
		struct CVECTOR *rgb0, struct CVECTOR *rgb1, struct CVECTOR *rgb2, struct CVECTOR *rgb3,
		struct EVECTOR **evmx);
	extern long Clip4GTP(struct SVECTOR *v0, struct SVECTOR *v1, struct SVECTOR *v2, struct SVECTOR *v3,
		short *uv0, short *uv1, short *uv2, short *uv3,
		struct CVECTOR *rgb0, struct CVECTOR *rgb1, struct CVECTOR *rgb2, struct CVECTOR *rgb3,
		struct EVECTOR **evmx);

	extern void RotTransPers_nom(struct SVECTOR *v0);
	extern void RotTransPers3_nom(struct SVECTOR *v0, struct SVECTOR *v1, struct SVECTOR *v2);
	extern void RotTransPers4_nom(struct SVECTOR *v0, struct SVECTOR *v1, struct SVECTOR *v2, struct SVECTOR *v3);
	extern void RotTrans_nom(struct SVECTOR *v0);
	extern void RotAverage3_nom(struct SVECTOR *v0, struct SVECTOR *v1, struct SVECTOR *v2);
	extern void RotNclip3_nom(struct SVECTOR *v0, struct SVECTOR *v1, struct SVECTOR *v2);
	extern void RotAverageNclip3_nom(struct SVECTOR *v0, struct SVECTOR *v1, struct SVECTOR *v2);
	extern void RotAverageNclipColorDpq3_nom(struct SVECTOR *v0, struct SVECTOR *v1, struct SVECTOR *v2,
		struct SVECTOR *v3, struct SVECTOR *v4, struct SVECTOR *v5, struct CVECTOR *v6);
	extern void RotAverageNclipColorCol3_nom(struct SVECTOR *v0, struct SVECTOR *v1, struct SVECTOR *v2,
		struct SVECTOR *v3, struct SVECTOR *v4, struct SVECTOR *v5, struct CVECTOR *v6);
	extern void RotColorDpq_nom(struct SVECTOR *v0, struct SVECTOR *v1, struct CVECTOR *v2);
	extern long RotColorDpq3_nom(struct SVECTOR *v0, struct SVECTOR *v1, struct SVECTOR *v2,
		struct SVECTOR *v3, struct SVECTOR *v4, struct SVECTOR *v5, struct CVECTOR *v6);
	extern void NormalColor_nom(struct SVECTOR *v0);
	extern void NormalColor3_nom(struct SVECTOR *v0, struct SVECTOR *v1, struct SVECTOR *v2);
	extern void NormalColorDpq_nom(struct SVECTOR *v0, struct CVECTOR *v1, long p);
	extern void NormalColorDpq3_nom(struct SVECTOR *v0, struct SVECTOR *v1, struct SVECTOR *v2,
		struct CVECTOR *v3, long p);
	extern void NormalColorCol_nom(struct SVECTOR *v0, struct CVECTOR *v1);
	extern void NormalColorCol3_nom(struct SVECTOR *v0, struct SVECTOR *v1, struct SVECTOR *v2,
		struct CVECTOR *v3);

	/*

	extern unsigned long *DivideF3(struct SVECTOR *v0,struct SVECTOR *v1,struct SVECTOR *v2,struct CVECTOR *rgbc,
	POLY *otp);
	extern unsigned long *GsPrng n,unsigned long shift,GsOT *otp);

	extern unsigned long *GsTMDfastTG3LB(TMD_P_TG3 *primtop,struct SVECTOR *vertop,struct SVECTOR *nortop,
	POLY_GT3 *s,unsigned long n,unsigned long shift,GsOT *otp);
	extern unsigned long *GsTMDfastTG3LFGB(TMD_P_TG3 *primtop,struct SVECTOR *vertop,
	struct SVECTOR *nortop,POLY_GT3 *s,unsigned long n,unsigned long shift,GsOT *otp);
	extern unsigned long *GsTMDfastTG3NLB(TMD_P_TG3 *primtop,struct SVECTOR *vertop,
	struct SVECTOR *nortop,POLY_GT3 *s,unsigned long n,unsigned long shift,GsOT *otp);
	extern unsigned long *GsTMDfastTNG3B(TMD_P_TNG3 *primtop,struct SVECTOR *vertop,
	POLY_GT3 *s,unsigned long n,unsigned long shift,GsOT *otp);

	extern unsigned long *GsTMDfastTG4LB(TMD_P_TG4 *primtop,struct SVECTOR *vertop,struct SVECTOR *nortop,
	POLY_GT4 *s,unsigned long n,unsigned long shift,GsOT *otp);
	extern unsigned long *GsTMDfastTG4LFGB(TMD_P_TG4 *primtop,struct SVECTOR *vertop,
	struct SVECTOR *nortop,POLY_GT4 *s,unsigned long n,unsigned long shift,GsOT *otp);
	extern unsigned long *GsTMDfastTG4NLB(TMD_P_TG4 *primtop,struct SVECTOR *vertop,
	struct SVECTOR *nortop,POLY_GT4 *s,unsigned long n,unsigned long shift,GsOT *otp);
	extern unsigned long *GsTMDfastTNG4B(TMD_P_TNG4 *primtop,struct SVECTOR *vertop,
	POLY_GT4 *s,unsigned long n,unsigned long shift,GsOT *otp);

	extern unsigned long *GsTMDdivF3LB(TMD_P_F3 *primtop,struct SVECTOR *vertop,struct SVECTOR *nortop,
	POLY_F3 *s,unsigned long n,unsigned long shift,GsOT *otp,DIVPOLYGON3 *divp);
	extern unsigned long *GsTMDdivF3LFGB(TMD_P_F3 *primtop,struct SVECTOR *vertop,struct SVECTOR *nortop,
	POLY_F3 *s,unsigned long n,unsigned long shift,GsOT *otp,DIVPOLYGON3 *divp);
	extern unsigned long *GsTMDdivF3NLB(TMD_P_F3 *primtop,struct SVECTOR *vertop,struct SVECTOR *nortop,
	POLY_F3 *s,unsigned long n,unsigned long shift,GsOT *otp,DIVPOLYGON3 *divp);
	extern unsigned long *GsTMDdivNF3B(TMD_P_NF3 *primtop,struct SVECTOR *vertop,
	POLY_F3 *s,unsigned long n,unsigned long shift,GsOT *otp,DIVPOLYGON3 *divp);

	extern unsigned long *GsTMDdivF4LB(TMD_P_F4 *primtop,struct SVECTOR *vertop,struct SVECTOR *nortop,
	POLY_F4 *s,unsigned long n,unsigned long shift,GsOT *otp,DIVPOLYGON4 *divp);
	extern unsigned long *GsTMDdivF4LFGB(TMD_P_F4 *primtop,struct SVECTOR *vertop,struct SVECTOR *nortop,
	POLY_F4 *s,unsigned long n,unsigned long shift,GsOT *otp,DIVPOLYGON4 *divp);
	extern unsigned long *GsTMDdivF4NLB(TMD_P_F4 *primtop,struct SVECTOR *vertop,struct SVECTOR *nortop,
	POLY_F4 *s,unsigned long n,unsigned long shift,GsOT *otp,DIVPOLYGON4 *divp);
	extern unsigned long *GsTMDdivNF4B(TMD_P_NF4 *primtop,struct SVECTOR *vertop,
	POLY_F4 *s,unsigned long n,unsigned long shift,GsOT *otp,DIVPOLYGON4 *divp);

	extern unsigned long *GsTMDdivTF3LB(TMD_P_TF3 *primtop,struct SVECTOR *vertop,struct SVECTOR *nortop,
	POLY_FT3 *s,unsigned long n,unsigned long shift,GsOT *otp,DIVPOLYGON3 *divp);
	extern unsigned long *GsTMDdivTF3LFGB(TMD_P_TF3 *primtop,struct SVECTOR *vertop,
	struct SVECTOR *nortop,POLY_FT3 *s,unsigned long n,unsigned long shift,
	GsOT *otp,DIVPOLYGON3 *divp);
	extern unsigned long *GsTMDdivTF3NLB(TMD_P_TF3 *primtop,struct SVECTOR *vertop,struct SVECTOR *nortop,
	POLY_FT3 *s,unsigned long n,unsigned long shift,GsOT *otp,DIVPOLYGON3 *divp);
	extern unsigned long *GsTMDdivTNF3B(TMD_P_TNF3 *primtop,struct SVECTOR *vertop,
	POLY_FT3 *s,unsigned long n,unsigned long shift,GsOT *otp,DIVPOLYGON3 *divp);

	extern unsigned long *GsTMDdivTF4LB(TMD_P_TF4 *primtop,struct SVECTOR *vertop,struct SVECTOR *nortop,
	POLY_FT4 *s,unsigned long n,unsigned long shift,GsOT *otp,DIVPOLYGON4 *divp);
	extern unsigned long *GsTMDdivTF4LFGB(TMD_P_TF4 *primtop,struct SVECTOR *vertop,
	struct SVECTOR *nortop,POLY_FT4 *s,unsigned long n,unsigned long shift,
	GsOT *otp,DIVPOLYGON4 *divp);
	extern unsigned long *GsTMDdivTF4NLB(TMD_P_TF4 *primtop,struct SVECTOR *vertop,struct SVECTOR *nortop,
	POLY_FT4 *s,unsigned long n,unsigned long shift,GsOT *otp,DIVPOLYGON4 *divp);
	extern unsigned long *GsTMDdivTNF4B(TMD_P_TNF4 *primtop,struct SVECTOR *vertop,
	POLY_FT4 *s,unsigned long n,unsigned long shift,GsOT *otp,DIVPOLYGON4 *divp);

	extern unsigned long *GsTMDdivG3LB(TMD_P_G3 *primtop,struct SVECTOR *vertop,struct SVECTOR *nortop,
	POLY_G3 *s,unsigned long n,unsigned long shift,GsOT *otp,DIVPOLYGON3 *divp);
	extern unsigned long *GsTMDdivG3LFGB(TMD_P_G3 *primtop,struct SVECTOR *vertop,struct SVECTOR *nortop,
	POLY_G3 *s,unsigned long n,unsigned long shift,GsOT *otp,DIVPOLYGON3 *divp);
	extern unsigned long *GsTMDdivG3NLB(TMD_P_G3 *primtop,struct SVECTOR *vertop,struct SVECTOR *nortop,
	POLY_G3 *s,unsigned long n,unsigned long shift,GsOT *otp,DIVPOLYGON3 *divp);
	extern unsigned long *GsTMDdivNG3B(TMD_P_NG3 *primtop,struct SVECTOR *vertop,
	POLY_G3 *s,unsigned long n,unsigned long shift,GsOT *otp,DIVPOLYGON3 *divp);

	extern unsigned long *GsTMDdivG4LB(TMD_P_G4 *primtop,struct SVECTOR *vertop,struct SVECTOR *nortop,
	POLY_G4 *s,unsigned long n,unsigned long shift,GsOT *otp,DIVPOLYGON4 *divp);
	extern unsigned long *GsTMDdivG4LFGB(TMD_P_G4 *primtop,struct SVECTOR *vertop,struct SVECTOR *nortop,
	POLY_G4 *s,unsigned long n,unsigned long shift,GsOT *otp,DIVPOLYGON4 *divp);
	extern unsigned long *GsTMDdivG4NLB(TMD_P_G4 *primtop,struct SVECTOR *vertop,struct SVECTOR *nortop,
	POLY_G4 *s,unsigned long n,unsigned long shift,GsOT *otp,DIVPOLYGON4 *divp);
	extern unsigned long *GsTMDdivNG4B(TMD_P_NG4 *primtop,struct SVECTOR *vertop,
	POLY_G4 *s,unsigned long n,unsigned long shift,GsOT *otp,DIVPOLYGON4 *divp);

	extern unsigned long *GsTMDdivTG3LB(TMD_P_TG3 *primtop,struct SVECTOR *vertop,struct SVECTOR *nortop,
	POLY_GT3 *s,unsigned long n,unsigned long shift,GsOT *otp,DIVPOLYGON3 *divp);
	extern unsigned long *GsTMDdivTG3LFGB(TMD_P_TG3 *primtop,struct SVECTOR *vertop,
	struct SVECTOR *nortop,POLY_GT3 *s,unsigned long n,unsigned long shift,
	GsOT *otp,DIVPOLYGON3 *divp);
	extern unsigned long *GsTMDdivTG3NLB(TMD_P_TG3 *primtop,struct SVECTOR *vertop,struct SVECTOR *nortop,
	POLY_GT3 *s,unsigned long n,unsigned long shift,GsOT *otp,DIVPOLYGON3 *divp);
	extern unsigned long *GsTMDdivTNG3B(TMD_P_TNG3 *primtop,struct SVECTOR *vertop,
	POLY_GT3 *s,unsigned long n,unsigned long shift,GsOT *otp,DIVPOLYGON3 *divp);

	extern unsigned long *GsTMDdivTG4LB(TMD_P_TG4 *primtop,struct SVECTOR *vertop,struct SVECTOR *nortop,
	POLY_GT4 *s,unsigned long n,unsigned long shift,GsOT *otp,DIVPOLYGON4 *divp);
	extern unsigned long *GsTMDdivTG4LFGB(TMD_P_TG4 *primtop,struct SVECTOR *vertop,
	struct SVECTOR *nortop,POLY_GT4 *s,unsigned long n,unsigned long shift,
	GsOT *otp,DIVPOLYGON4 *divp);
	extern unsigned long *GsTMDdivTG4NLB(TMD_P_TG4 *primtop,struct SVECTOR *vertop,struct SVECTOR *nortop,
	POLY_GT4 *s,unsigned long n,unsigned long shift,GsOT *otp,DIVPOLYGON4 *divp);
	extern unsigned long *GsTMDdivTNG4B(TMD_P_TNG4 *primtop,struct SVECTOR *vertop,
	POLY_GT4 *s,unsigned long n,unsigned long shift,GsOT *otp,DIVPOLYGON4 *divp);

	*/

	extern void RotSMD_F3(long *pa, unsigned long *ot, int otlen, int id,
		int sclip, int hclip, int vclip, int nclipmode);
	extern void RotSMD_G3(long *pa, unsigned long *ot, int otlen, int id,
		int sclip, int hclip, int vclip, int nclipmode);
	extern void RotSMD_FT3(long *pa, unsigned long *ot, int otlen, int id,
		int sclip, int hclip, int vclip, int nclipmode);
	extern void RotSMD_GT3(long *pa, unsigned long *ot, int otlen, int id,
		int sclip, int hclip, int vclip, int nclipmode);
	extern void RotSMD_F4(long *pa, unsigned long *ot, int otlen, int id,
		int sclip, int hclip, int vclip, int nclipmode);
	extern void RotSMD_G4(long *pa, unsigned long *ot, int otlen, int id,
		int sclip, int hclip, int vclip, int nclipmode);
	extern void RotSMD_FT4(long *pa, unsigned long *ot, int otlen, int id,
		int sclip, int hclip, int vclip, int nclipmode);
	extern void RotSMD_GT4(long *pa, unsigned long *ot, int otlen, int id,
		int sclip, int hclip, int vclip, int nclipmode);

	extern void RotSMD_SV_F3(long *pa, long *va, unsigned long *ot, int otlen, int id,
		int sclip, int hclip, int vclip, int nclipmode);
	extern void RotSMD_SV_G3(long *pa, long *va, unsigned long *ot, int otlen, int id,
		int sclip, int hclip, int vclip, int nclipmode);
	extern void RotSMD_SV_FT3(long *pa, long *va, unsigned long *ot, int otlen, int id,
		int sclip, int hclip, int vclip, int nclipmode);
	extern void RotSMD_SV_GT3(long *pa, long *va, unsigned long *ot, int otlen, int id,
		int sclip, int hclip, int vclip, int nclipmode);
	extern void RotSMD_SV_F4(long *pa, long *va, unsigned long *ot, int otlen, int id,
		int sclip, int hclip, int vclip, int nclipmode);
	extern void RotSMD_SV_G4(long *pa, long *va, unsigned long *ot, int otlen, int id,
		int sclip, int hclip, int vclip, int nclipmode);
	extern void RotSMD_SV_FT4(long *pa, long *va, unsigned long *ot, int otlen, int id,
		int sclip, int hclip, int vclip, int nclipmode);
	extern void RotSMD_SV_GT4(long *pa, long *va, unsigned long *ot, int otlen, int id,
		int sclip, int hclip, int vclip, int nclipmode);



	extern void RotRMD_F3(long *pa, unsigned long *ot, int otlen, int id,
		int sclip, int hclip, int vclip, int nclipmode);
	extern void RotRMD_G3(long *pa, unsigned long *ot, int otlen, int id,
		int sclip, int hclip, int vclip, int nclipmode);
	extern void RotRMD_FT3(long *pa, unsigned long *ot, int otlen, int id,
		int sclip, int hclip, int vclip, int nclipmode);
	extern void RotRMD_GT3(long *pa, unsigned long *ot, int otlen, int id,
		int sclip, int hclip, int vclip, int nclipmode);
	extern void RotRMD_F4(long *pa, unsigned long *ot, int otlen, int id,
		int sclip, int hclip, int vclip, int nclipmode);
	extern void RotRMD_G4(long *pa, unsigned long *ot, int otlen, int id,
		int sclip, int hclip, int vclip, int nclipmode);
	extern void RotRMD_FT4(long *pa, unsigned long *ot, int otlen, int id,
		int sclip, int hclip, int vclip, int nclipmode);
	extern void RotRMD_GT4(long *pa, unsigned long *ot, int otlen, int id,
		int sclip, int hclip, int vclip, int nclipmode);

	extern void RotRMD_SV_F3(long *pa, long *va, unsigned long *ot, int otlen, int id,
		int sclip, int hclip, int vclip, int nclipmode);
	extern void RotRMD_SV_G3(long *pa, long *va, unsigned long *ot, int otlen, int id,
		int sclip, int hclip, int vclip, int nclipmode);
	extern void RotRMD_SV_FT3(long *pa, long *va, unsigned long *ot, int otlen, int id,
		int sclip, int hclip, int vclip, int nclipmode);
	extern void RotRMD_SV_GT3(long *pa, long *va, unsigned long *ot, int otlen, int id,
		int sclip, int hclip, int vclip, int nclipmode);
	extern void RotRMD_SV_F4(long *pa, long *va, unsigned long *ot, int otlen, int id,
		int sclip, int hclip, int vclip, int nclipmode);
	extern void RotRMD_SV_G4(long *pa, long *va, unsigned long *ot, int otlen, int id,
		int sclip, int hclip, int vclip, int nclipmode);
	extern void RotRMD_SV_FT4(long *pa, long *va, unsigned long *ot, int otlen, int id,
		int sclip, int hclip, int vclip, int nclipmode);
	extern void RotRMD_SV_GT4(long *pa, long *va, unsigned long *ot, int otlen, int id,
		int sclip, int hclip, int vclip, int nclipmode);

	extern long p2otz(long p, long projection);
	extern long otz2p(long otz, long projection);

	/*
	extern void RotMeshPrimS_F3(TMESH *msh,POLY_F3 *prim,u_long *ot,
	u_long otlen,long dpq,u_long backc);
	extern void RotMeshPrimS_G3(TMESH *msh,POLY_G3 *prim,u_long *ot,
	u_long otlen,long dpq,u_long backc);
	extern void RotMeshPrimS_FC3(TMESH *msh,POLY_F3 *prim,u_long *ot,
	u_long otlen,long dpq,u_long backc);
	extern void RotMeshPrimS_GC3(TMESH *msh,POLY_G3 *prim,u_long *ot,
	u_long otlen,long dpq,u_long backc);
	extern void RotMeshPrimS_FT3(TMESH *msh,POLY_FT3 *prim,u_long *ot,
	u_long otlen,long dpq,u_long backc);
	extern void RotMeshPrimS_GT3(TMESH *msh,POLY_GT3 *prim,u_long *ot,
	u_long otlen,long dpq,u_long backc);
	extern void RotMeshPrimS_FCT3(TMESH *msh,POLY_FT3 *prim,u_long *ot,
	u_long otlen,long dpq,u_long backc);
	extern void RotMeshPrimS_GCT3(TMESH *msh,POLY_GT3 *prim,u_long *ot,
	u_long otlen,long dpq,u_long backc);
	extern void RotMeshPrimS_T3(TMESH *msh,POLY_FT3 *prim,u_long *ot,
	u_long otlen,long dpq,u_long backc);

	extern void RotMeshPrimR_F3(TMESH *msh,POLY_F3 *prim,u_long *ot,
	u_long otlen,long dpq,u _long backc);
	extern void RotMeshPrimR_G3(TMESH *msh,POLY_G3 *prim,u_long *ot,
	u_long otlen,long dpq,u_long backc);
	extern void RotMeshPrimR_FC3(TMESH *msh,POLY_F3 *prim,u_long *ot,
	u_long otlen,long dpq,u_long backc);
	extern void RotMeshPrimR_GC3(TMESH *msh,POLY_G3 *prim,u_long *ot,
	u_long otlen,long dpq,u_long backc);
	extern void RotMeshPrimR_FT3(TMESH *msh,POLY_FT3 *prim,u_long *ot,
	u_long otlen,long dpq,u_long backc);
	extern void RotMeshPrimR_GT3(TMESH *msh,POLY_GT3 *prim,u_long *ot,
	u_long otlen,long dpq,u_long backc);
	extern void RotMeshPrimR_FCT3(TMESH *msh,POLY_FT3 *prim,u_long *ot,
	u_long otlen,long dpq,u_long backc);
	extern void RotMeshPrimR_GCT3(TMESH *msh,POLY_GT3 *prim,u_long *ot,
	u_long otlen,long dpq,u_long backc);
	extern void RotMeshPrimR_T3(TMESH *msh,POLY_FT3 *prim,u_long *ot,
	u_long otlen,long dpq,u_long backc);

	extern void RotMeshPrimQ_T(QMESH *msh,POLY_FT4 *prim,u_long *ot,
	u_long otlen,long dpq,long backc);
	*/

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif
#else
#define INLINE_H <INLINE_C.H>
#endif

#include <sys/types.h>
#include <LIBGTE.H>
#include <LIBGPU.H>

struct DB_STRUCT
{
	int current_buffer;
	unsigned long* ot;
	char* polyptr;
	char* curpolybuf;
	char* polybuf_limit;
	int nOTSize;
	int nPBSize;
	unsigned long* order_table[2];
	unsigned long* poly_buffer[2];
	unsigned long* pickup_ot;
	unsigned long* pickup_order_table[2];
	DRAWENV draw[2];
	DISPENV disp[2];
};

struct room_info
{
	short* data; // size=0, offset=0
	short* door; // size=0, offset=4
	struct FLOOR_INFO* floor; // size=8, offset=8
	struct LIGHTINFO* light; // size=32, offset=12
	struct MESH_INFO* mesh; // size=20, offset=16
	long x; // size=0, offset=20
	long y; // size=0, offset=24
	long z; // size=0, offset=28
	long minfloor; // size=0, offset=32
	long maxceiling; // size=0, offset=36
	short x_size; // size=0, offset=40
	short y_size; // size=0, offset=42
	CVECTOR ambient; // size=4, offset=44
	short num_lights; // size=0, offset=48
	short num_meshes; // size=0, offset=50
	unsigned char ReverbType; // size=0, offset=52
	unsigned char FlipNumber; // size=0, offset=53
	char MeshEffect; // size=0, offset=54
	char bound_active; // size=0, offset=55
	short left; // size=0, offset=56
	short right; // size=0, offset=58
	short top; // size=0, offset=60
	short bottom; // size=0, offset=62
	short test_left; // size=0, offset=64
	short test_right;
	short test_top;
	short test_bottom;
	short item_number;
	short fx_number;
	short flipped_room;
	unsigned short flags;
};

struct object_info {
	short nmeshes; // size=0, offset=0
	short mesh_index; // size=0, offset=2
	long bone_index; // size=0, offset=4
	short *frame_base; // size=0, offset=8
	void(*initialise)(short item_number); // size=0, offset=12
	void(*control)(short item_number); // size=0, offset=16
	void(*floor)(struct ITEM_INFO* item, int x, int y, int z, int* height); // size=0, offset=20
	void(*ceiling)(struct ITEM_INFO* item, int x, int y, int z, int* height); // size=0, offset=24
	void(*draw_routine)(struct ITEM_INFO* item); // size=0, offset=28
	void(*collision)(short item_num, struct ITEM_INFO* laraitem, struct COLL_INFO* coll); // size=0, offset=32
	short object_mip; // size=0, offset=36
	short anim_index; // size=0, offset=38
	short hit_points; // size=0, offset=40
	short pivot_length; // size=0, offset=42
	short radius; // size=0, offset=44
	short shadow_size; // size=0, offset=46
	unsigned short bite_offset; // size=0, offset=48
	unsigned short loaded : 1; // offset=50.0
	unsigned short intelligent : 1; // offset=50.1
	unsigned short non_lot : 1; // offset=50.2
	unsigned short save_position : 1; // offset=50.3
	unsigned short save_hitpoints : 1; // offset=50.4
	unsigned short save_flags : 1; // offset=50.5
	unsigned short save_anim : 1; // offset=50.6
	unsigned short semi_transparent : 1; // offset=50.7
	unsigned short water_creature : 1; // offset=51.0
	unsigned short using_drawanimating_item : 1; // offset=51.1
	unsigned short HitEffect : 2; // offset=51.2
	unsigned short undead : 1; // offset=51.4
	unsigned short save_mesh : 1; // offset=51.5
	void(*draw_routine_extra)(struct ITEM_INFO* item); // size=0, offset=52
	unsigned long explodable_meshbits; // size=0, offset=56
	unsigned long padfuck; // size=0, offset=60
};

struct TEXTURE
{
	unsigned char u0;
	unsigned char v0;
	unsigned short clut;
	unsigned char u1;
	unsigned char v1;
	unsigned short tpage;
	unsigned char u2;
	unsigned char v2;
	unsigned char id[2];
	unsigned char u3;
	unsigned char v3;
	unsigned short wclut;
};

struct static_info
{
	short mesh_number;
	short flags;
	short x_minp;
	short x_maxp;
	short y_minp;
	short y_maxp;
	short z_minp;
	short z_maxp;
	short x_minc;
	short x_maxc;
	short y_minc;
	short y_maxc;
	short z_minc;
	short z_maxc;
};

struct PSXTEXTI
{
	unsigned char u0;
	unsigned char v0;
	unsigned short clut;
	unsigned char u1;
	unsigned char v1;
	unsigned short tpage;
	unsigned char u2;
	unsigned char v2;
	unsigned char codeGT4;
	unsigned char codeGT3;
	unsigned char u3;
	unsigned char v3;
	unsigned short pad3;
};

struct VECTOR3D
{
	long x;
	long y;
	long z;
};

struct PSXTEXTSTRUCT
{
	unsigned long u0v0clut;
	unsigned long u1v1tpage;
	unsigned long u2v2pad;
	unsigned long u3v3pad;
};

struct PSXSPRITESTRUCT
{
	short x1;
	short y1;
	short x2;
	short y2;
	unsigned short clut;
	unsigned short tpage;
	unsigned char u1;
	unsigned char v1;
	unsigned char u2;
	unsigned char v2;
};

struct MMTEXTURE
{
	struct TEXTURE t[3];
};

struct TSV
{
	unsigned long xy;
	unsigned long rgz;
};

typedef unsigned short PadData;

typedef struct
{
	unsigned short buttons;
	char xOffset;
	char yOffset;
} MouseData;

typedef struct
{
	unsigned short digitalButtons;
	char centralTwist;
	char buttonI;
	char buttonII;
	char topLeft;
} NegconData;

typedef struct
{
	unsigned char transStatus;
	unsigned char dataFormat;

	union
	{
		PadData    pad;
		NegconData negcon;
	}
	data;
} TapCtrllerData;

typedef struct
{
	TapCtrllerData ctrllers[4];
} MultiTapData;

typedef struct
{
	unsigned char transStatus;
	unsigned char dataFormat;

	union
	{
		PadData      pad;
		MouseData    mouse;
		NegconData   negcon;
		MultiTapData tap;
	}
	data;
} ControllerPacket;

struct pad_configs
{
	unsigned long pad_L2;
	unsigned long pad_R2;
	unsigned long pad_L1;
	unsigned long pad_R1;
	unsigned long pad_triangle;
	unsigned long pad_square; 
	unsigned long pad_circle;
	unsigned long pad_cross;
};

struct GouraudBarColourSet
{
	unsigned char abLeftRed[5];
	unsigned char abLeftGreen[5];
	unsigned char abLeftBlue[5];
	unsigned char abRightRed[5];
	unsigned char abRightGreen[5];
	unsigned char abRightBlue[5];
};

struct STASHEDOBJ
{
	short clip;
	short numnodestodraw;
	struct ITEM_INFO* item;
	short* frmptr0;
};

struct STASHEDDAT
{
	short* mesh;
	char matrix[32];
};

struct WATERTAB
{
	char shimmer;
	char choppy;
	unsigned char random;
	unsigned char abs;
};

struct VIBRATION
{
	short Rate;
	short Len;
	short Lev;
	short Acc;
	short Dec;
	short Sus;
	short Flag;
	short Vib;
};

struct REQUESTER
{
	unsigned short TitleTxt;
	unsigned short TitleCol : 5;
	unsigned short nOptions : 3;
	unsigned short CursorPos : 3;
	unsigned short OptionCol : 5;
	unsigned long JustifyL : 5;
	unsigned long JustifyR : 5;
	unsigned long Arrows : 5;
	unsigned long Ignore : 5;
	unsigned short OptionTxt[5];
};

struct SCALE
{
	short xgrid;
	char scalefactor;
	char nummarks;
};

struct COCKSUCK
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char pad;
	short finalcnt;
	short profile_xcnt;
};

struct PACKEDNAME
{
	char Name[12];
	unsigned char Days;
	unsigned char Hours;
	unsigned char Min;
	unsigned char Sec;
	unsigned short Slot;
	unsigned char Level;
	unsigned char Pad;
};

struct ILIGHT
{
	short x;
	short y;
	short z;
	short pad1;
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char pad;
};

struct ITEM_LIGHT
{
	struct ILIGHT Light[4];
};

struct ITEM_INFO {
	long floor; // size=0, offset=0
	unsigned long touch_bits; // size=0, offset=4
	unsigned long mesh_bits; // size=0, offset=8
	short object_number; // size=0, offset=12
	short current_anim_state; // size=0, offset=14
	short goal_anim_state; // size=0, offset=16
	short required_anim_state; // size=0, offset=18
	short anim_number; // size=0, offset=20
	short frame_number; // size=0, offset=22
	short room_number; // size=0, offset=24
	short next_item; // size=0, offset=26
	short next_active; // size=0, offset=28
	short speed; // size=0, offset=30
	short fallspeed; // size=0, offset=32
	short hit_points; // size=0, offset=34
	unsigned short box_number; // size=0, offset=36
	short timer; // size=0, offset=38
	short flags; // size=0, offset=40
	short shade; // size=0, offset=42
	short trigger_flags; // size=0, offset=44
	short carried_item; // size=0, offset=46
	short after_death; // size=0, offset=48
	unsigned short fired_weapon; // size=0, offset=50
	short item_flags[4]; // size=8, offset=52
	void* data; // size=0, offset=60
	struct PHD_3DPOS pos; // size=20, offset=64
	struct ITEM_LIGHT il; // size=48, offset=84
	unsigned long active : 1; // offset=132.0
	unsigned long status : 2; // offset=132.1
	unsigned long gravity_status : 1; // offset=132.3
	unsigned long hit_status : 1; // offset=132.4
	unsigned long collidable : 1; // offset=132.5
	unsigned long looked_at : 1; // offset=132.6
	unsigned long dynamic_light : 1; // offset=132.7
	unsigned long poisoned : 1; // offset=133.0
	unsigned long ai_bits : 5; // offset=133.1
	unsigned long really_active : 1; // offset=133.6
	unsigned long InDrawRoom : 1; // offset=133.7
	unsigned long meshswap_meshbits; // size=0, offset=136
	short draw_room; // size=0, offset=140
	short TOSSPAD; // size=0, offset=142
};

struct creature_info {
	short joint_rotation[4]; // size=8, offset=0
	short maximum_turn; // size=0, offset=8
	short flags; // size=0, offset=10
	unsigned short alerted : 1; // offset=12.0
	unsigned short head_left : 1; // offset=12.1
	unsigned short head_right : 1; // offset=12.2
	unsigned short reached_goal : 1; // offset=12.3
	unsigned short hurt_by_lara : 1; // offset=12.4
	unsigned short patrol2 : 1; // offset=12.5
	unsigned short jump_ahead : 1; // offset=12.6
	unsigned short monkey_ahead : 1; // offset=12.7
	enum mood_type mood; // size=4, offset=16
	struct ITEM_INFO* enemy; // size=144, offset=20
	struct ITEM_INFO ai_target; // size=144, offset=24
	short pad; // size=0, offset=168
	short item_num; // size=0, offset=170
	struct PHD_VECTOR target; // size=12, offset=172
	struct lot_info LOT; // size=44, offset=184
};

struct DRIP_STRUCT
{
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
	unsigned char On; // size=0, offset=12
	unsigned char R; // size=0, offset=13
	unsigned char G; // size=0, offset=14
	unsigned char B; // size=0, offset=15
	short Yvel; // size=0, offset=16
	unsigned char Gravity; // size=0, offset=18
	unsigned char Life; // size=0, offset=19
	short RoomNumber; // size=0, offset=20
	unsigned char Outside; // size=0, offset=22
	unsigned char Pad; // size=0, offset=23
};

#endif