#ifndef EMULATOR_PRIVATE_H
#define EMULATOR_PRIVATE_H

extern void Emulator_HintTextureAtlas(unsigned short tpage, unsigned short clut, unsigned char u0, unsigned char v0, unsigned char u1, unsigned char v1, unsigned char u2, unsigned char v2, unsigned char u3, unsigned char v3, unsigned short bIsQuad);
extern void Emulator_Initialise(char* windowName, int screenWidth, int screenHeight);
extern void Emulator_BeginScene();
extern void Emulator_EndScene();
extern void Emulator_UpdateInput();
extern void Emulator_ShutDown();
extern void Emulator_InjectTIM(char* fileName, unsigned short texTpage, unsigned short texClut, unsigned char u0, unsigned char v0, unsigned char u1, unsigned char v1, unsigned char u2, unsigned char v2, unsigned char u3, unsigned char v3);
extern void Emulator_DestroyAllTextures();

#endif