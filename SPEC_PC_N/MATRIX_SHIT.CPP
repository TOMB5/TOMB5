#include "SPECTYPES.H"
#include "3DGLODEF.H"
#include "SPECIFIC.H"

#ifdef __cplusplus
extern "C" {
#endif

	sint32		phd_left;  				/* Left Clipping Value */
	sint32		phd_right;              /* Right Clipping Value */
	sint32		phd_top;                /* Top Clipping Value */
	sint32		phd_bottom;             /* Bottom Clipping Value */
	sint16		phd_winxmin;
	sint16		phd_winymin;
	sint16		phd_winxmax;        	/* Maximum Window X coord*/
	sint16		phd_winymax;        	/* Maximum Window Y coord*/
	sint32		phd_winwidth;       	/* Window Width*/
	sint32		phd_winheight;      	/* Window Height*/
	sint32		phd_centerx;        	/* Vanishing point X*/
	sint32		phd_centery;        	/* Vanishing point Y*/
	sint32		phd_znear;          	/* Distance to near clip plane in View.Frame*/
	sint32		phd_zfar;           	/* Distance to far clip plane in View.Frame*/
	sint32		phd_viewdist;       	/* Distance you can see in World.Frame*/
	sint32		phd_scrwidth;       	/* Width of Screen ie. 320 or 640*/
	sint32		phd_scrheight;       	/* Height of Screen ie. 200 or 480*/
	sint32		phd_persp;				/* perspective thang*/
	sint32		*phd_mxptr;				/* matrix pointer....*/
	sint32		phd_oopersp;
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

	sint32		w2v_matrix[12];		// World to View Matrix...
	sint32		matrix_stack[12 * MAX_MAT];		// matrix stack for animations etc..

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

	void	phd_PushMatrix(void)
	{
		sint32	*p1, *p2;

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

	void	phd_UnitMatrix(void)
	{
		sint32	*p1;

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

	void	phd_PushUnitMatrix(void)
	{
		phd_dxptr += 12;
		phd_mxptr += 12;
		phd_UnitMatrix();
	}

	void phd_TranslateAbs(long x, long y, long z)
	{
		Unimpl();
	}

	void phd_RotYXZ(long y, long x, long z)
	{
		Unimpl();
	}

#ifdef __cplusplus
}
#endif