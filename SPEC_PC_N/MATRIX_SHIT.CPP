#include "SPECTYPES.H"
#include "3DGLODEF.H"
#include "SPECIFIC.H"
#include "GLOBAL.H"
#include "INCLUDE.H"
#include "CAMERA.H"
#include "LARA.H"
#include "CONTROL.H"

#ifdef __cplusplus
//extern "C" {
#endif
	struct SVECTOR CamRot;
	int32_t		phd_left;  				/* Left Clipping Value */
	int32_t		phd_right;              /* Right Clipping Value */
	int32_t		phd_top;                /* Top Clipping Value */
	int32_t		phd_bottom;             /* Bottom Clipping Value */
	int16_t		phd_winxmin;
	int16_t		phd_winymin;
	int16_t		phd_winxmax;        	/* Maximum Window X coord*/
	int16_t		phd_winymax;        	/* Maximum Window Y coord*/
	int32_t		phd_winwidth;       	/* Window Width*/
	int32_t		phd_winheight;      	/* Window Height*/
	int32_t		phd_centerx;        	/* Vanishing point X*/
	int32_t		phd_centery;        	/* Vanishing point Y*/
	int32_t		phd_znear;          	/* Distance to near clip plane in View.Frame*/
	int32_t		phd_zfar;           	/* Distance to far clip plane in View.Frame*/
	int32_t		phd_viewdist;       	/* Distance you can see in World.Frame*/
	int32_t		phd_scrwidth;       	/* Width of Screen ie. 320 or 640*/
	int32_t		phd_scrheight;       	/* Height of Screen ie. 200 or 480*/
	int32_t		phd_persp;				/* perspective thang*/
	int32_t		*phd_mxptr;				/* matrix pointer.... column major*/
	int32_t		phd_oopersp;
	float* phd_dxptr;

	float clip_xmin;
	float clip_xmax;
	float clip_ymin;
	float clip_ymax;

	float		one = 2048.0;				// in 3dinsert.cpp
	float		f_znear;			// phd_znear
	float		f_zfar;				// phd_zfar
	float		f_oneoznear;		// one / phd_znear
	float		f_persp;			// phd_persp
	float		f_oneopersp;		// one / phd_persp
	float		f_perspoznear;		// phd_persp / phd_znear
	float		f_centerx;			// phd_centrex
	float		f_centery;			// phd_centrey
	float		f_invzfar;			// 1.0/phd_zfar (actually 65535/65536 at the moment)
	float		f_oneozfar;			// one/phd_zfar
	float		f_a, f_b, f_boo;		// a/b factors for z buffering (f_boo is f_b/one)
	float f_persp_bis;
	float f_znear3;
	float f_persp_bis_over_znear3;
	float LfAspectCorrection;
	float flt_55D1F8;
	float dword_50A440 = SECTOR(32768);
	int32_t		w2v_matrix[12]={0};		// World to View Matrix...
	
	int32_t		matrix_stack[12 * MAX_MAT]={0};		// matrix stack for animations etc..
	float		matrix_stack_dx[12 * MAX_MAT]={0};
	float		sin_flt_table[65536];

	D3DMATRIX transform_projection;
	D3DMATRIX w2v_matrix_d3d;

	void D3DIdentityMatrix(LPD3DMATRIX mat)// (F)
	{
		mat->_11 = 1.0;
		mat->_12 = 0.0;
		mat->_13 = 0.0;
		mat->_14 = 0.0;
		mat->_21 = 0.0;
		mat->_22 = 1.0;
		mat->_23 = 0.0;
		mat->_24 = 0.0;
		mat->_31 = 0.0;
		mat->_32 = 0.0;
		mat->_33 = 1.0;
		mat->_34 = 0.0;
		mat->_41 = 0.0;
		mat->_42 = 0.0;
		mat->_43 = 0.0;
		mat->_44 = 1.0;
	}

	void SetD3DMatrix(LPD3DMATRIX dst, int* src)// (F)
	{
		D3DIdentityMatrix(dst);
		dst->_11 = src[M00] / 16384.0f;
		dst->_12 = src[M10] / 16384.0f;
		dst->_13 = src[M20] / 16384.0f;
		dst->_21 = src[M01] / 16384.0f;
		dst->_22 = src[M11] / 16384.0f;
		dst->_23 = src[M21] / 16384.0f;
		dst->_31 = src[M02] / 16384.0f;
		dst->_32 = src[M12] / 16384.0f;
		dst->_33 = src[M22] / 16384.0f;
		dst->_41 = src[M03] / 16384.0f;
		dst->_42 = src[M13] / 16384.0f;
		dst->_43 = src[M23] / 16384.0f;
	}

	void SetD3DMatrixF(LPD3DMATRIX dst, LPD3DMATRIX src)// (F)
	{
		D3DIdentityMatrix(dst);
		dst->_11 = src->_11;
		dst->_12 = src->_21;
		dst->_13 = src->_31;
		dst->_21 = src->_12;
		dst->_22 = src->_22;
		dst->_23 = src->_32;
		dst->_31 = src->_13;
		dst->_32 = src->_23;
		dst->_33 = src->_33;
		dst->_41 = src->_14;
		dst->_42 = src->_24;
		dst->_43 = src->_34;
	}

	

	tr5_vertex stru_51D0B0[5];
	float		w2v_matrix_f[12] = { 0 };		// World to View Matrix...

	void Normalize(tr5_vertex* a)
	{
		double norm = sqrt(a->x * a->x + a->y * a->y + a->z * a->z);
		a->x /= norm;
		a->y /= norm;
		a->z /= norm;
	}

	void CrossProduct(tr5_vertex* a, tr5_vertex* b, tr5_vertex* res)
	{
		res->x = b->z * a->y - a->z * b->y;
		res->y = a->z * b->x - a->x * b->z;
		res->z = a->x * b->y - b->x * a->y;
	}

	void __cdecl sub_491170(tr5_vertex* a1, tr5_vertex* a2, tr5_vertex* a3)
	{
		
		tr5_vertex cross; // [esp+18h] [ebp-18h]
		
		Normalize(a1);
		
		if (a1->x != 0.0 || a1->y != 0.0)
		{
			CrossProduct(a3, a1, &cross);
		}
		else
		{
			cross = *a2;
		}
		
		CrossProduct(a1, &cross, a3);

		*a2 = cross;
		Normalize(a2);
		Normalize(a3);
		 
	}

	void __cdecl Identity3(MATRIX3* a1)
	{
		a1->_11 = 1.0;
		a1->_12 = 0.0;
		a1->_13 = 0.0;
		a1->_21 = 0.0;
		a1->_22 = 1.0;
		a1->_23 = 0.0;
		a1->_31 = 0.0;
		a1->_32 = 0.0;
		a1->_33 = 1.0;
		a1->_14 = 0.0;
		a1->_24 = 0.0;
		a1->_34 = 0.0;
	}

	void __cdecl sub_490FA0(tr5_vertex* a1, tr5_vertex* a2)
	{
		MATRIX3 v13; // [esp+18h] [ebp-60h]
		MATRIX3 v14; // [esp+48h] [ebp-30h]

		Identity3(&v13);
		Identity3(&v14);
		a1[0].x = a2[1].x;
		a1[0].y = a2[1].y;
		a1[0].z = a2[1].z;
		
		a1[1].x = -a2[3].z * a1->z + -a2[3].y * a1->y + -a2[3].x * a1->x;
		a1[1].y = -a2[2].x;
		a1[1].z = -a2[2].y;
		
		a1[2].x = -a2[2].z;
		a1[2].y = -a2[3].z * a1[2].x + -a2[3].x * a1[1].y + -a2[3].y * a1[1].z;
		a1[2].z = -a2->x;
		
		a1[3].x = -a2->y;
		a1[3].y = -a2->z;
		a1[3].z = -a2[3].x * a1[2].z + -a2[3].y * a1[3].x + -a2->z * -a2[3].z;
	}

	void __cdecl sub_490F30()
	{
		tr5_vertex* v1; // esi
		double v2; // st7
		double v3; // st7
		tr5_vertex* a1 = stru_51D0B0;
		v1 = a1;
		v2 = a1[3].x - a1[4].x;
		a1[2].y = -1.0;
		a1[2].z = 0.0;
		a1->x = v2;
		v3 = v1[3].y - v1[4].y;
		a1[2].x = 0.0;
		a1->y = v3;
		v1->z = v1[3].z - v1[4].z;
		sub_491170(a1, a1 + 1, a1 + 2);
		sub_490FA0((tr5_vertex*)w2v_matrix_f, v1);
	}

void RotX(long angle)
{
	if (angle == 0)
		return;

	int sin = sin_flt_table[angle];
	int cos = sin_flt_table[angle + ANGLE(90)];

	float* m = phd_dxptr;

	m[M01] = cos * m[M01] + sin * m[M02];
	m[M02] = cos * m[M02] - sin * m[M01];
	m[M11] = cos * m[M11] + sin * m[M12];
	m[M12] = cos * m[M12] - sin * m[M11];
	m[M21] = cos * m[M21] + sin * m[M22];
	m[M22] = cos * m[M22] - sin * m[M21];
}
void RotY(long angle)
{
	if (angle == 0)
		return;

	int sin = sin_flt_table[angle];
	int cos = sin_flt_table[angle + ANGLE(90)];

	float* m = phd_dxptr;

	m[M00] = cos * m[M00] + sin * m[M02];
	m[M02] = cos * m[M02] - sin * m[M00];
	m[M10] = cos * m[M10] + sin * m[M12];
	m[M12] = cos * m[M12] - sin * m[M10];
	m[M20] = cos * m[M20] + sin * m[M22];
	m[M22] = cos * m[M22] - sin * m[M20];
}
void RotZ(long angle)
{
	if (angle == 0)
		return;

	int sin = sin_flt_table[angle];
	int cos = sin_flt_table[angle + ANGLE(90)];

	float* m = phd_dxptr;

	m[M00] = cos * m[M00] + sin * m[M01];
	m[M01] = cos * m[M01] - sin * m[M00];
	m[M10] = cos * m[M10] + sin * m[M11];
	m[M11] = cos * m[M11] - sin * m[M10];
	m[M20] = cos * m[M20] + sin * m[M21];
	m[M21] = cos * m[M21] - sin * m[M20];
}

void phd_RotX(long angle)
{
	if (angle == 0)
		return;

	int sin = 4 * SIN(angle);
	int cos = 4 * COS(angle);

	int* m = phd_mxptr;

	m[M01] = cos * m[M01] + sin * m[M02] >> W2V_SHIFT;
	m[M02] = cos * m[M02] - sin * m[M01] >> W2V_SHIFT;
	m[M11] = cos * m[M11] + sin * m[M12] >> W2V_SHIFT;
	m[M12] = cos * m[M12] - sin * m[M11] >> W2V_SHIFT;
	m[M21] = cos * m[M21] + sin * m[M22] >> W2V_SHIFT;
	m[M22] = cos * m[M22] - sin * m[M21] >> W2V_SHIFT;

	RotX(angle);
}
void phd_RotY(long angle)
{
	if (angle == 0)
		return;

	int sin = 4 * SIN(angle);
	int cos = 4 * COS(angle);

	int* m = phd_mxptr;

	m[M00] = cos * m[M00] + sin * m[M02] >> W2V_SHIFT;
	m[M02] = cos * m[M02] - sin * m[M00] >> W2V_SHIFT;
	m[M10] = cos * m[M10] + sin * m[M12] >> W2V_SHIFT;
	m[M12] = cos * m[M12] - sin * m[M10] >> W2V_SHIFT;
	m[M20] = cos * m[M20] + sin * m[M22] >> W2V_SHIFT;
	m[M22] = cos * m[M22] - sin * m[M20] >> W2V_SHIFT;

	RotY(angle);
}
void phd_RotZ(long angle)
{
	if (angle == 0)
		return;

	int sin = 4 * SIN(angle);
	int cos = 4 * COS(angle);

	int* m = phd_mxptr;

	m[M00] = cos * m[M00] + sin * m[M01] >> W2V_SHIFT;
	m[M01] = cos * m[M01] - sin * m[M00] >> W2V_SHIFT;
	m[M10] = cos * m[M10] + sin * m[M11] >> W2V_SHIFT;
	m[M11] = cos * m[M11] - sin * m[M10] >> W2V_SHIFT;
	m[M20] = cos * m[M20] + sin * m[M21] >> W2V_SHIFT;
	m[M21] = cos * m[M21] - sin * m[M20] >> W2V_SHIFT;

	RotZ(angle);
}

D3DMATRIX stru_55D168;

	void phd_QuickW2VMatrix(tr5_vertex src, tr5_vertex tar, int rot)
	{
				stru_51D0B0[3] = src;
		stru_51D0B0[4] = tar;
		
		phd_dxptr = matrix_stack_dx;

		sub_490F30();
		phd_dxptr[M00] = w2v_matrix_f[M00];
		phd_dxptr[M01] = w2v_matrix_f[M01];
		phd_dxptr[M02] = w2v_matrix_f[M02];
		phd_dxptr[M03] = w2v_matrix_f[M03] = src.x;
		phd_dxptr[M10] = w2v_matrix_f[M10];
		phd_dxptr[M11] = w2v_matrix_f[M11];
		phd_dxptr[M12] = w2v_matrix_f[M12];
		phd_dxptr[M13] = w2v_matrix_f[M13] = src.y;
		phd_dxptr[M20] = w2v_matrix_f[M20];
		phd_dxptr[M21] = w2v_matrix_f[M21];
		phd_dxptr[M22] = w2v_matrix_f[M22];
		phd_dxptr[M23] = w2v_matrix_f[M23] = src.z;

		if (rot)
		{
			RotZ(rot);
			w2v_matrix_f[M00] = phd_dxptr[M00];
			w2v_matrix_f[M01] = phd_dxptr[M01];
			w2v_matrix_f[M02] = phd_dxptr[M02];
			w2v_matrix_f[M10] = phd_dxptr[M10];
			w2v_matrix_f[M11] = phd_dxptr[M11];
			w2v_matrix_f[M12] = phd_dxptr[M12];
			w2v_matrix_f[M20] = phd_dxptr[M20];
			w2v_matrix_f[M21] = phd_dxptr[M21];
			w2v_matrix_f[M22] = phd_dxptr[M22];
		}

		w2v_matrix_f[M10] *= LfAspectCorrection;
		w2v_matrix_f[M11] *= LfAspectCorrection;
		w2v_matrix_f[M12] *= LfAspectCorrection;
		D3DMATRIX v7;
		SetD3DMatrixF(&v7, (LPD3DMATRIX)w2v_matrix_f);
		stru_55D168._11 = v7._11;
		stru_55D168._12 = v7._21;
		stru_55D168._13 = v7._31;
		stru_55D168._14 = v7._41;
		stru_55D168._21 = v7._12;
		stru_55D168._22 = v7._22;
		stru_55D168._23 = v7._32;
		stru_55D168._24 = v7._42;
		stru_55D168._31 = v7._13;
		stru_55D168._32 = v7._23;
		stru_55D168._33 = v7._33;
		stru_55D168._34 = v7._43;
		stru_55D168._41 = v7._14;
		stru_55D168._42 = v7._24;
		stru_55D168._43 = v7._34;
		stru_55D168._44 = v7._44;
	}

	void S_InitD3DMatrix()// (F)
	{
		//Log(LT_Enter, "S_InitD3DMatrix");
		
		D3DIdentityMatrix(&App.WorldMatrix);
		D3DIdentityMatrix(&transform_projection);

		transform_projection._22 = -1.0;

		DX_TRY(App.lpD3DDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &App.WorldMatrix));
		DX_TRY(App.lpD3DDevice->SetTransform(D3DTRANSFORMSTATE_PROJECTION, &transform_projection));
	}

	void SetD3DViewMatrix()// (F)
	{
		//Log(LT_Enter, "SetD3DViewMatrix");

		D3DIdentityMatrix(&App.ViewMatrix);

		App.ViewMatrix._11 = phd_mxptr[M00] >> W2V_SHIFT;
		App.ViewMatrix._12 = phd_mxptr[M10] >> W2V_SHIFT;
		App.ViewMatrix._13 = phd_mxptr[M20] >> W2V_SHIFT;
		App.ViewMatrix._21 = phd_mxptr[M01] >> W2V_SHIFT;
		App.ViewMatrix._22 = phd_mxptr[M11] >> W2V_SHIFT;
		App.ViewMatrix._23 = phd_mxptr[M21] >> W2V_SHIFT;
		App.ViewMatrix._31 = phd_mxptr[M02] >> W2V_SHIFT;
		App.ViewMatrix._32 = phd_mxptr[M12] >> W2V_SHIFT;
		App.ViewMatrix._33 = phd_mxptr[M22] >> W2V_SHIFT;
		App.ViewMatrix._41 = phd_mxptr[M03] >> W2V_SHIFT;
		App.ViewMatrix._42 = phd_mxptr[M13] >> W2V_SHIFT;
		App.ViewMatrix._43 = phd_mxptr[M23] >> W2V_SHIFT;

		DX_TRY(App.lpD3DDevice->SetTransform(D3DTRANSFORMSTATE_VIEW, &App.ViewMatrix));
	}

	void SetViewMatrix()// (F)
	{
		//Log(LT_Enter, "SetViewMatrix");

		SetD3DMatrixF(&App.ViewMatrix, (LPD3DMATRIX)phd_dxptr);
		DX_TRY(App.lpD3DDevice->SetTransform(D3DTRANSFORMSTATE_VIEW, &App.ViewMatrix));
	}





	void	phd_PushMatrix(void)// (F)
	{
		int32_t	*p1, *p2;

		p1 = phd_mxptr;
		phd_mxptr += 12;
		p2 = phd_mxptr;
		*(p2 + M00) = *(p1 + M00);
		*(p2 + M01) = *(p1 + M01);
		*(p2 + M02) = *(p1 + M02);
		*(p2 + M03) = *(p1 + M03);
		*(p2 + M10) = *(p1 + M10);
		*(p2 + M11) = *(p1 + M11);
		*(p2 + M12) = *(p1 + M12);
		*(p2 + M13) = *(p1 + M13);
		*(p2 + M20) = *(p1 + M20);
		*(p2 + M21) = *(p1 + M21);
		*(p2 + M22) = *(p1 + M22);
		*(p2 + M23) = *(p1 + M23);

		float* f1 = phd_dxptr;
		phd_dxptr += 12;
		float* f2 = phd_dxptr;
		*(f2 + M00) = *(f1 + M00);
		*(f2 + M01) = *(f1 + M01);
		*(f2 + M02) = *(f1 + M02);
		*(f2 + M03) = *(f1 + M03);
		*(f2 + M10) = *(f1 + M10);
		*(f2 + M11) = *(f1 + M11);
		*(f2 + M12) = *(f1 + M12);
		*(f2 + M13) = *(f1 + M13);
		*(f2 + M20) = *(f1 + M20);
		*(f2 + M21) = *(f1 + M21);
		*(f2 + M22) = *(f1 + M22);
		*(f2 + M23) = *(f1 + M23);
	}

	void	phd_UnitMatrix(void)// (F)
	{
		int32_t	*p1;

		p1 = phd_mxptr;
		*(p1 + M00) = *(p1 + M11) = *(p1 + M22) = W2V_SCALE;
		*(p1 + M01) = *(p1 + M02) =
			*(p1 + M10) = *(p1 + M12) =
			*(p1 + M20) = *(p1 + M21) = 0;

		float* f1 = phd_dxptr;

		*(f1 + M00) = *(f1 + M11) = *(f1 + M22) = 1.0f;
		*(f1 + M01) = *(f1 + M02) =
			*(f1 + M10) = *(f1 + M12) =
			*(f1 + M20) = *(f1 + M21) = 0.0f;
	}

	void	phd_PushUnitMatrix(void)// (F)
	{
		phd_dxptr += 12;
		phd_mxptr += 12;
		phd_UnitMatrix();
	}

	void TranslateAbs(long x, long y, long z)// (F)
	{
		float* mptr = phd_dxptr;

		x -= w2v_matrix_f[M03];
		y -= w2v_matrix_f[M13];
		z -= w2v_matrix_f[M23];

		mptr[M03] = mptr[M00] * x + mptr[M01] * y + mptr[M02] * z;
		mptr[M13] = mptr[M10] * x + mptr[M11] * y + mptr[M12] * z;
		mptr[M23] = mptr[M20] * x + mptr[M21] * y + mptr[M22] * z;
	}

	void phd_TranslateAbs(long x, long y, long z)// (F)
	{
		int* mptr = phd_mxptr;

		TranslateAbs(x, y, z);

		x -= w2v_matrix[M03];
		y -= w2v_matrix[M13];
		z -= w2v_matrix[M23];

		mptr[M03] = mptr[M00] * x + mptr[M01] * y + mptr[M02] * z;
		mptr[M13] = mptr[M10] * x + mptr[M11] * y + mptr[M12] * z;
		mptr[M23] = mptr[M20] * x + mptr[M21] * y + mptr[M22] * z;
	}

	void TranslateRel(long x, long y, long z)// (F)
	{
		float* mptr = phd_dxptr;

		mptr[M03] += mptr[M00] * x + mptr[M01] * y + mptr[M02] * z;
		mptr[M13] += mptr[M10] * x + mptr[M11] * y + mptr[M12] * z;
		mptr[M23] += mptr[M20] * x + mptr[M21] * y + mptr[M22] * z;
	}

	void phd_TranslateRel(long x, long y, long z)// (F)
	{
		int* mptr = phd_mxptr;

		mptr[M03] += mptr[M00] * x + mptr[M01] * y + mptr[M02] * z;
		mptr[M13] += mptr[M10] * x + mptr[M11] * y + mptr[M12] * z;
		mptr[M23] += mptr[M20] * x + mptr[M21] * y + mptr[M22] * z;

		TranslateRel(x, y, z);
	}

	void RotYXZ(long y, long x, long z)
	{
		if (y)
			RotY(y);
		
		if (x)
			RotX(x);
		
		if (z)
			RotZ(z);
	}

	void phd_RotYXZ(long y, long x, long z)// (F)
	{
		RotYXZ(y, x, z);
		
		sint32 sina, cosa;
		sint32* mptr = phd_mxptr;
		
		if (y)
		{
			sina = 4 * SIN(y);
			cosa = 4 * COS(y);
			mptr[M00] = (mptr[M00] * cosa - mptr[M02] * sina) >> W2V_SHIFT;
			mptr[M02] = (mptr[M02] * cosa + mptr[M00] * sina) >> W2V_SHIFT;
			mptr[M10] = (mptr[M10] * cosa - mptr[M12] * sina) >> W2V_SHIFT;
			mptr[M12] = (mptr[M12] * cosa + mptr[M10] * sina) >> W2V_SHIFT;
			mptr[M20] = (mptr[M20] * cosa - mptr[M22] * sina) >> W2V_SHIFT;
			mptr[M22] = (mptr[M22] * cosa + mptr[M20] * sina) >> W2V_SHIFT;
		}
		if (x)
		{
			sina = 4 * SIN(x);
			cosa = 4 * COS(x);
			mptr[M01] = (mptr[M01] * cosa + mptr[M02] * sina) >> W2V_SHIFT;
			mptr[M02] = (mptr[M02] * cosa - mptr[M01] * sina) >> W2V_SHIFT;
			mptr[M11] = (mptr[M11] * cosa + mptr[M12] * sina) >> W2V_SHIFT;
			mptr[M12] = (mptr[M12] * cosa - mptr[M11] * sina) >> W2V_SHIFT;
			mptr[M21] = (mptr[M21] * cosa + mptr[M22] * sina) >> W2V_SHIFT;
			mptr[M22] = (mptr[M22] * cosa - mptr[M21] * sina) >> W2V_SHIFT;
		}
		if (z)
		{
			sina = 4 * SIN(z);
			cosa = 4 * COS(z);
			mptr[M00] = (mptr[M00] * cosa + mptr[M01] * sina) >> W2V_SHIFT;
			mptr[M01] = (mptr[M01] * cosa - mptr[M00] * sina) >> W2V_SHIFT;
			mptr[M10] = (mptr[M10] * cosa + mptr[M11] * sina) >> W2V_SHIFT;
			mptr[M11] = (mptr[M11] * cosa - mptr[M10] * sina) >> W2V_SHIFT;
			mptr[M20] = (mptr[M20] * cosa + mptr[M21] * sina) >> W2V_SHIFT;
			mptr[M21] = (mptr[M21] * cosa - mptr[M20] * sina) >> W2V_SHIFT;
		}
	}

	void mRotSuperPackedYXZ(short** a0, long a1)
	{
		UNIMPLEMENTED();
	}

	void SetTransl(long x, long y, long z)// (F)
	{
		phd_dxptr[M03] = x;
		phd_dxptr[M13] = y;
		phd_dxptr[M23] = z;
	}

	void gte_sttr(PHD_VECTOR *v)
	{
		v->x = phd_mxptr[M03] >> W2V_SHIFT;
		v->y = phd_mxptr[M13] >> W2V_SHIFT;
		v->z = phd_mxptr[M23] >> W2V_SHIFT;
	}

	void phd_SetTrans(long x, long y, long z)// (F)
	{
		x <<= W2V_SHIFT;
		y <<= W2V_SHIFT;
		z <<= W2V_SHIFT;

		phd_dxptr[M03] = x;
		phd_dxptr[M13] = y;
		phd_dxptr[M23] = z;

		SetTransl(x, y, z);
	}

	void ScaleCurrentMatrixF(VECTOR* vec)// (F)
	{
		phd_dxptr[M00] = TRIGMULT2F(phd_dxptr[M00], vec->vx);
		phd_dxptr[M10] = TRIGMULT2F(phd_dxptr[M10], vec->vx);
		phd_dxptr[M20] = TRIGMULT2F(phd_dxptr[M20], vec->vx);

		phd_dxptr[M01] = TRIGMULT2F(phd_dxptr[M01], vec->vy);
		phd_dxptr[M11] = TRIGMULT2F(phd_dxptr[M11], vec->vy);
		phd_dxptr[M21] = TRIGMULT2F(phd_dxptr[M21], vec->vy);

		phd_dxptr[M02] = TRIGMULT2F(phd_dxptr[M02], vec->vz);
		phd_dxptr[M12] = TRIGMULT2F(phd_dxptr[M12], vec->vz);
		phd_dxptr[M22] = TRIGMULT2F(phd_dxptr[M22], vec->vz);
	}

	void ScaleCurrentMatrix(VECTOR vec)// (F)
	{
		phd_mxptr[M00] = TRIGMULT2(phd_mxptr[M00], vec.vx);
		phd_mxptr[M10] = TRIGMULT2(phd_mxptr[M10], vec.vx);
		phd_mxptr[M20] = TRIGMULT2(phd_mxptr[M20], vec.vx);

		phd_mxptr[M01] = TRIGMULT2(phd_mxptr[M01], vec.vy);
		phd_mxptr[M11] = TRIGMULT2(phd_mxptr[M11], vec.vy);
		phd_mxptr[M21] = TRIGMULT2(phd_mxptr[M21], vec.vy);

		phd_mxptr[M02] = TRIGMULT2(phd_mxptr[M02], vec.vz);
		phd_mxptr[M12] = TRIGMULT2(phd_mxptr[M12], vec.vz);
		phd_mxptr[M22] = TRIGMULT2(phd_mxptr[M22], vec.vz);

		ScaleCurrentMatrixF(&vec);
	}

	void phd_GenerateW2V(PHD_3DPOS* viewpos)// (F)
	{
		int32_t	sx, sy, sz;
		int32_t	cx, cy, cz;
		int32_t	*mptr, *nptr;

		mptr = phd_mxptr = matrix_stack;    /* Put W2V at Top Of matrix Stack */
		nptr = w2v_matrix;

		sx = 4 * SIN(viewpos->x_rot);		/* get sin and cos values*/
		cx = 4 * COS(viewpos->x_rot);
		sy = 4 * SIN(viewpos->y_rot);
		cy = 4 * COS(viewpos->y_rot);
		sz = 4 * SIN(viewpos->z_rot);
		cz = 4 * COS(viewpos->z_rot);

		*(nptr + M00) = *(mptr + M00) = (TRIGMULT3(sx, sy, sz) + TRIGMULT2(cy, cz));
		*(nptr + M01) = *(mptr + M01) = (TRIGMULT2(cx, sz));
		*(nptr + M02) = *(mptr + M02) = (TRIGMULT3(sx, cy, sz) - TRIGMULT2(sy, cz));
		*(nptr + M10) = *(mptr + M10) = (TRIGMULT3(sx, sy, cz) - TRIGMULT2(cy, sz));
		*(nptr + M11) = *(mptr + M11) = (TRIGMULT2(cx, cz));
		*(nptr + M12) = *(mptr + M12) = (TRIGMULT3(sx, cy, cz) + TRIGMULT2(sy, sz));
		*(nptr + M20) = *(mptr + M20) = (TRIGMULT2(cx, sy));
		*(nptr + M21) = *(mptr + M21) = -(sx);
		*(nptr + M22) = *(mptr + M22) = (TRIGMULT2(cx, cy));

		short poison = lara.poisoned;
		if (lara.dpoisoned != lara.poisoned)
		{
			poison = ((lara.dpoisoned - lara.poisoned) >> 4) + lara.poisoned;
			lara.poisoned = poison;
			if (abs(lara.dpoisoned - poison) < 16)
			{
				poison = lara.dpoisoned;
				lara.poisoned = lara.dpoisoned;
			}
		}

		if (poison >= 256)
		{
			short p = poison - 256;
			long x = p * (SIN(XSoff1) + SIN(XSoff2));
			long y = p * (SIN(XSoff1) + SIN(XSoff2));
			long z = p * (SIN(XSoff1) + SIN(XSoff2));
			if (x != 0 || y != 0 || z != 0)
			{
				VECTOR vec;
				vec.vx = (x >> 12) + 0x4000;
				vec.vy = (y >> 12) + 0x4000;
				vec.vz = (z >> 12) + 0x4000;
				ScaleCurrentMatrix(vec);
			}
		}

		*(nptr + M03) = *(mptr + M03) = viewpos->x_pos;
		*(nptr + M13) = *(mptr + M13) = viewpos->y_pos;
		*(nptr + M23) = *(mptr + M23) = viewpos->z_pos;

		*(nptr + M10) = *(mptr + M10) = (int32_t)(float(*(mptr + M10))*LfAspectCorrection);
		*(nptr + M11) = *(mptr + M11) = (int32_t)(float(*(mptr + M11))*LfAspectCorrection);
		*(nptr + M12) = *(mptr + M12) = (int32_t)(float(*(mptr + M12))*LfAspectCorrection);

		SetD3DMatrix(&w2v_matrix_d3d, w2v_matrix);
	}

	void D3DNormalise(tr5_vertex* m)
	{
		if (m->x == 0.0 && m->y == 0.0)
			return;
		long double v1 = 1.0 / sqrt(m->z * m->z + m->y * m->y + m->x * m->x);;
		m->x = v1 * m->x;
		m->y = v1 * m->y;
		m->z = v1 * m->z;
	}

	void phd_GetVectorAngles(int32_t x, int32_t y, int32_t z, short* dest)// (F)
	{
		short	pitch;

		dest[0] = phd_atan(z, x);
		while ((int16_t)x != x || (int16_t)y != y || (int16_t)z != z)
		{
			x >>= 2;
			y >>= 2;
			z >>= 2;
		}
		pitch = phd_atan(phd_sqrt(x * x + z * z), y);
		if ((y > 0 && pitch > 0) || (y < 0 && pitch < 0))
			pitch = -pitch;
		dest[1] = pitch;
	}

	void phd_LookAt(int32_t xsrc, int32_t ysrc, int32_t zsrc, int32_t xtar, int32_t ytar, int32_t ztar, short roll)// (F)
	{
		//Log(LT_Enter, "phd_LookAt src(%5d, %5d, %5d) tar(%5d, %5d, %5d), roll=%5d", xsrc, ysrc, ysrc, xtar, ytar, ztar, roll);
		
		short	angles[2];
		PHD_3DPOS 	viewer;

		phd_GetVectorAngles(xtar - xsrc, ytar - ysrc, ztar - zsrc, angles);
		viewer.x_pos = xsrc;
		viewer.y_pos = ysrc;
		viewer.z_pos = zsrc;
		viewer.x_rot = angles[1];
		viewer.y_rot = angles[0];
		viewer.z_rot = roll;

		int dx, dy, dz;
		dx = xsrc - xtar;
		dy = ysrc - ytar;
		dz = zsrc - ztar;

		int len = (int)sqrt((dx*dx) + (dz*dz));

		CamRot.vx = mGetAngle(0, 0, len, dy) >> 4;
		CamRot.vy = mGetAngle(zsrc, xsrc, ztar, xtar) >> 4;
		CamRot.vz = 0;

		lookatpos.x = xsrc;
		lookatpos.y = ysrc;
		lookatpos.z = zsrc;

		phd_GenerateW2V(&viewer);
		S_InitD3DMatrix();
	}

	

#ifdef __cplusplus
//}
#endif