#include "SPECTYPES.H"

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
	}

	void	phd_UnitMatrix(void)
	{
		sint32	*p1;

		p1 = phd_mxptr;
		*(p1 + M00) = *(p1 + M11) = *(p1 + M22) = W2V_SCALE;
		*(p1 + M01) = *(p1 + M02) =
			*(p1 + M10) = *(p1 + M12) =
			*(p1 + M20) = *(p1 + M21) = 0;
	}

	void	phd_PushUnitMatrix(void)
	{
		phd_mxptr += 12;
		phd_UnitMatrix();
	}

#ifdef __cplusplus
}
#endif