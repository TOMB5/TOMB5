#ifndef EMULATOR_PRIVATE_H
#define EMULATOR_PRIVATE_H

/* Usually called at the beginning of main function */
extern void Emulator_Initialise(char* windowName, int screenWidth, int screenHeight);

/* Usually called after ClearOTag/ClearOTagR */
extern int Emulator_BeginScene();

/* Usually called after DrawOTag/DrawOTagEnv */
extern void Emulator_EndScene();

/* Explicitly updates emulator input loop */
extern void Emulator_UpdateInput();

/* Usually called at the end of main function */
extern void Emulator_ShutDown();

/* Sets the maximum vertex count value for PGXP vertex caching */
extern void Emulator_SetPGXPVertexCount(int vertexCount);

/* Waits for timer */
extern void Emulator_WaitForTimestep(int count);

/* Stores framebuffer */
extern void Emulator_StoreFrameBuffer(int x, int y, int w, int h);

#endif