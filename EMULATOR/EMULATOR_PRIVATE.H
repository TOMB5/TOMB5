#ifndef EMULATOR_PRIVATE_H
#define EMULATOR_PRIVATE_H

extern void Emulator_Initialise(char* windowName, int screenWidth, int screenHeight);
extern void Emulator_BeginScene();
extern void Emulator_EndScene();
extern void Emulator_UpdateInput();
extern void Emulator_ShutDown();

#endif