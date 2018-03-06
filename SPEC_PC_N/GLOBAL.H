#ifndef GLOBAL_H
#define GLOBAL_H

#define phd_sqrt_asm phd_sqrt


#include "SPECTYPES.H"

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

sint32		S_SoundPlaySample(int nSample, uint16 wVol, int nPitch, sint16 wPan);
sint32		S_SoundPlaySampleLooped(int nSample, uint16 wVol, int nPitch, sint16 wPan);
sint32		S_SoundSampleIsPlaying(sint32 handle);
void 		S_SoundStopAllSamples(void);
void	 	S_SoundStopSample(sint32 handle);
void		S_SoundSetPanAndVolume(sint32 handle, sint16 wPan, uint16 newvol);
void		S_SoundSetPitch(sint32 handle, int nPitch);

void		S_CDPlay(sint16 track, int mode);
void		S_CDStop(void);
void		S_CDPause(void);
void		S_CDRestart(void);
int		S_StartSyncedAudio(int num);
extern char			exit_message[128];
extern void S_ExitSystem(char *message);

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

#define EndOfArray(a) ((a)+ArraySize(a))

extern void phd_PushUnitMatrix();
extern void phd_UnitMatrix();
extern void phd_TransposeMatrix();
extern unsigned long mGetAngle(long x1, long y1, long x2, long y2);
#define phd_PopMatrix()		phd_mxptr -= 12

#ifdef __cplusplus
}
#endif


#endif