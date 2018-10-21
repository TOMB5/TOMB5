#ifndef SPECIFIC_H
#define SPECIFIC_H

#include "SPECTYPES.H"

#define UNIMPLEMENTED() printf("[%s] - Unimplemented!\n", __func__);

extern char			cd_drive;
extern bool loadBarShown;

#ifdef __cplusplus
extern "C" {
#endif

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

	extern void S_ExitSystem(char *message);

	void		S_DumpScreenFrame();
	long		S_DumpScreen();

	void S_LoadBar();
	void S_InitLoadBar(int size);
	bool S_DrawLoadBar();

	bool Decompress(void* buf, void* compressed, int compSize, int uncompSize);

	LPDIRECTDRAWSURFACE4 CreateTexturePage(int width, int height, int mipmaps, int *buf, void(*a5)(uchar *, uchar *, uchar *, uchar *), int bpp);
	extern void CalcColorSplit(uint32_t clr, uint32_t* out1, uint32_t* out2);
	void DoBar(int x, int y, int w, int h, float pc, D3DCOLOR color1, D3DCOLOR color2);
	void S_DrawAirBar(int size);
	void S_DrawHealthBar(int size);
	void S_DrawHealthBar2(int size);
	void S_CDFade(int a1);
extern void S_Warn(const char* warning_message, ...);

extern void S_SetReverbType(sint16 reverb);

extern unsigned short *AnimTextureRanges; // offset 0xA4670
extern unsigned short nAnimUVRanges; // offset 0xA4660

extern void SetFogColor(uint8_t r, uint8_t g, uint8_t b);

extern void ClearFXFogBulbs();

extern void SetFade(int a1, int a2);

extern void S_InitialiseScreen();

extern BYTE IsVolumetric();

extern void S_AnimateTextures(long nFrames);

extern void S_OutputPolyList();

extern void S_CalculateStaticMeshLight(int x, int y, int z, int shade, room_info* room);

extern void S_CalculateLight(long x, long y, long z, short room, ITEM_LIGHT* light);

extern void S_CDLoop();

extern int S_LoadSave(int input, int in_inventory);
extern int S_DisplayPauseMenu(int a1);
extern int S_PauseMenu();

#ifdef __cplusplus
}
#endif

#endif