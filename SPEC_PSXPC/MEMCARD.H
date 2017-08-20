#ifndef MEMCARD_H
#define MEMCARD_H

extern unsigned char mcInit;
extern unsigned char mcStatus;
extern unsigned long mcNumFiles;
extern unsigned char mcBlocksFree;
extern char mcFileNames[7][20];
extern int mcFileLengths[7];

extern void mcDir();
extern void mcOpen(int sync);
extern void mcClose();
extern unsigned char mcGetStatus();
extern long mcFormat();

#endif