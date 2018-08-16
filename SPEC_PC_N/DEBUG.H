#ifndef DEBUG_H
#define DEBUG_H
#include "GLOBAL.H"

extern UINT dbm_logout, dbm_clearlog, dbm_deftype, dbm_command;
extern FILE* fplog;

void DB_InitLog(char opt);
void DB_DefType(char* name, LPARAM lParam, WPARAM wParam);

#endif