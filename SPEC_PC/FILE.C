#include "FILE.H"
#include "SPECIFIC.H"

FILE *FileOpen(const char *filename)
{
	FILE *v1; // esi@1
	char v3; // [sp+Ch] [bp-50h]@1
	char v4; // [sp+Dh] [bp-4Fh]@1
	char v5; // [sp+Eh] [bp-4Eh]@1

	memset(&v3, 0, 80u);
	v3 = 0;
	v4 = 0;
	v5 = 0;
	strcat(&v3, filename);
	sub_4DEB10(5, "FileOpen - %s", &v3);
	v1 = fopen(&v3, "rb");
	if (!v1)
		sub_4DEB10(1, "Unable To Open %s", &v3);
	return v1;
}

int FileClose(FILE *fp)
{
	sub_4DEB10(2, "FileClose");
	return fclose(fp);
}