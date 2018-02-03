#ifdef PAELLA

#include "PAELLA.H"
#include <libcd.h>
#include <stdio.h>
#include <LIBAPI.H>



// TODO UGLY WORKAROUND

int CdControlB(u_char com, u_char *param, u_char *result)
{
	return CdControl(com, param, result);
}

int CdControlF(u_char com, u_char *param)
{
	return CdControl(com, param, NULL);
}

int printf(const char *fmt, ...)
{
	return 0;
}

int sprintf(char *buffer, const char *fmt, ...)
{
	return 0;
}

void gte_SetGeomScreen(long h)
{

}

unsigned long SetSp(unsigned long new_sp)
{
	return 0;
}

int CdSync(int mode, unsigned char* result)
{
	return CdlComplete;
}

int CdLastCom()
{
	return 0;
}

void gte_SetRotMatrix(struct MATRIX3D* m)
{
	
}

void gte_SetTransMatrix(struct MATRIX3D* m)
{
	
}

void gte_ReadLightMatrix(struct MATRIX3D* m)
{
	
}

void gte_ReadRotMatrix(struct MATRIX3D* m)
{

}

void gte_SetLightMatrix(struct MATRIX3D* m)
{

}

void gte_ldtr(long x, long y, long z)
{
	
}

#endif