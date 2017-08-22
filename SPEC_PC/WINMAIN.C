#include "WINMAIN.H"
#include "SPECIFIC.H"

HWND SendMsg(char a1, char *a2, ...)
{
	S_Warn("[SendMsg] - Unimplemented!\\n");
	return NULL;
}

int WinProcMsg()
{
	S_Warn("[WinProcMsg] - Unimplemented!\\n");
	return 0;
}

char* WinProcessCommandLine(char *a1)
{
	S_Warn("[WinProcessCommandLine] - Unimplemented!\\n");
	return NULL;
}

char WinRunCheck(const CHAR *lpName, const CHAR *lpClassName, HANDLE *mutex)
{
	S_Warn("[WinRunCheck] - Unimplemented!\\n");
	return 0;
}

HWND WinClose()
{
	S_Warn("[WinClose] - Unimplemented!\\n");
	return NULL;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	S_Warn("[WinMain] - Unimplemented!\\n");
}
