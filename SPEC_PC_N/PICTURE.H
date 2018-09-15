#ifndef PICTURE_H
#define PICTURE_H

#include "INCLUDE.H"
#include "TEXTURE.H"

#ifdef __cplusplus
extern "C" {
#endif

	bool LoadPicture(char* File, LPDIRECTDRAWSURFACE3 lpPictureBuffer, int);
	void FadePictureUp();
	void FadePictureDown();
	void ConvertSurfaceToTextures(LPDIRECTDRAWSURFACE3 lpSurface);
	void ConvertSurfaceToTextures16Bit(LPDIRECTDRAWSURFACE3 lpSurface);
	void DrawPicture();
	void FreePictureTextures();
	void CreateMonoScreen();
	void DrawMonoScreen();
	void RemoveMonoScreen(int);

	extern DXTEXTURE PicTextureList[];

#ifdef __cplusplus
}
#endif

#endif