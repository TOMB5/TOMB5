#ifndef EMULATOR_PRIVATE_H
#define EMULATOR_PRIVATE_H

/* Usually called at the beginning of main function */
extern void Emulator_Initialise(char* windowName, int screenWidth, int screenHeight);

/* Usually called after ClearOTag/ClearOTagR */
extern void Emulator_BeginScene();

/* Usually called after DrawOTag/DrawOTagEnv */
extern void Emulator_EndScene();

/* Explicitly updates emulator input loop */
extern void Emulator_UpdateInput();

/* Usually called at the end if main function */
extern void Emulator_ShutDown();

#endif