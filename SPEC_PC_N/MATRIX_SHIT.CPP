#include "SPECTYPES.H"
#include "3DGLODEF.H"
#include "SPECIFIC.H"
#include "GLOBAL.H"
#include "INCLUDE.H"
#include "CAMERA.H"
#include "LARA.H"
#include "CONTROL.H"

#ifdef __cplusplus
extern "C" {
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
	int32_t		*phd_mxptr;				/* matrix pointer....*/
	int32_t		phd_oopersp;
	float* phd_dxptr;

	float		one;				// in 3dinsert.cpp
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

	int32_t		w2v_matrix[12];		// World to View Matrix...
	float		w2v_matrix_f[12];		// World to View Matrix...
	int32_t		matrix_stack[12 * MAX_MAT];		// matrix stack for animations etc..
	float		matrix_stack_dx[12 * MAX_MAT];
	float		sin_flt_table[(int)ANGLE(360)];

	D3DMATRIX transform_projection;
	D3DMATRIX w2v_matrix_d3d;
	static float LfAspectCorrection;

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

	void S_InitD3DMatrix()// (F)
	{
		D3DIdentityMatrix(&App.WorldMatrix);
		D3DIdentityMatrix(&transform_projection);

		transform_projection._22 = -1.0;

		DX_TRY(App.lpD3DDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &App.WorldMatrix));
		DX_TRY(App.lpD3DDevice->SetTransform(D3DTRANSFORMSTATE_PROJECTION, &transform_projection));
	}

	void SetD3DViewMatrix()
	{
		D3DIdentityMatrix(&App.ViewMatrix);

		App.ViewMatrix._11 = phd_mxptr[M00] >> 14;
		App.ViewMatrix._12 = phd_mxptr[M10] >> 14;
		App.ViewMatrix._13 = phd_mxptr[M20] >> 14;
		App.ViewMatrix._21 = phd_mxptr[M01] >> 14;
		App.ViewMatrix._22 = phd_mxptr[M11] >> 14;
		App.ViewMatrix._23 = phd_mxptr[M21] >> 14;
		App.ViewMatrix._31 = phd_mxptr[M02] >> 14;
		App.ViewMatrix._32 = phd_mxptr[M12] >> 14;
		App.ViewMatrix._33 = phd_mxptr[M22] >> 14;
		App.ViewMatrix._41 = phd_mxptr[M03] >> 14;
		App.ViewMatrix._42 = phd_mxptr[M13] >> 14;
		App.ViewMatrix._43 = phd_mxptr[M23] >> 14;

		DX_TRY(App.lpD3DDevice->SetTransform(D3DTRANSFORMSTATE_VIEW, &App.ViewMatrix));
	}

	void SetViewMatrix()// (F)
	{
		SetD3DMatrixF(&App.ViewMatrix, (LPD3DMATRIX)phd_dxptr);
		DX_TRY(App.lpD3DDevice->SetTransform(D3DTRANSFORMSTATE_VIEW, &App.ViewMatrix));
	}

	void phd_RotX(long angle)
	{
		Unimpl();
	}
	void phd_RotY(long angle)
	{
		Unimpl();
	}
	void phd_RotZ(long angle)
	{
		Unimpl();
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

	void phd_RotYXZ(long y, long x, long z)
	{
		Unimpl();
	}

	void SetTransl(long x, long y, long z)// (F)
	{
		phd_dxptr[M03] = x;
		phd_dxptr[M13] = y;
		phd_dxptr[M23] = z;
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

	void ScaleCurrentMatrix(VECTOR* vec)// (F)
	{
		phd_mxptr[M00] = TRIGMULT2(phd_mxptr[M00], vec->vx);
		phd_mxptr[M10] = TRIGMULT2(phd_mxptr[M10], vec->vx);
		phd_mxptr[M20] = TRIGMULT2(phd_mxptr[M20], vec->vx);

		phd_mxptr[M01] = TRIGMULT2(phd_mxptr[M01], vec->vy);
		phd_mxptr[M11] = TRIGMULT2(phd_mxptr[M11], vec->vy);
		phd_mxptr[M21] = TRIGMULT2(phd_mxptr[M21], vec->vy);

		phd_mxptr[M02] = TRIGMULT2(phd_mxptr[M02], vec->vz);
		phd_mxptr[M12] = TRIGMULT2(phd_mxptr[M12], vec->vz);
		phd_mxptr[M22] = TRIGMULT2(phd_mxptr[M22], vec->vz);

		ScaleCurrentMatrixF(vec);
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

		short poison;
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
				ScaleCurrentMatrix(&vec);
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

		phd_GenerateW2V(&viewer);
		S_InitD3DMatrix();
	}

	

#ifdef __cplusplus
}
#endif