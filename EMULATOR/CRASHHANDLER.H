#ifndef CRASHHANDLER_H
#define CRASHHANDLER_H

#ifdef WIN32
#include <windows.h>
#include <Dbghelp.h>
#include <tchar.h>

LONG WINAPI unhandled_handler(struct _EXCEPTION_POINTERS* apExceptionInfo);

#endif

#endif