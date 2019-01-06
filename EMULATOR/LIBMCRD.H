#ifndef MEMCARD_H
#define MEMCARD_H

#include <kernel.h>

typedef void (*MemCB)( long cmds, long rslt );

#define McFuncExist		(1)
#define McFuncAccept		(2)
#define McFuncReadFile		(3)
#define McFuncWriteFile		(4)
#define McFuncReadData		(5)
#define McFuncWriteData		(6)

#define	McErrNone		(0)
#define	McErrCardNotExist	(1)
#define	McErrCardInvalid	(2)
#define	McErrNewCard		(3)
#define	McErrNotFormat		(4)
#define	McErrFileNotExist	(5)
#define	McErrAlreadyExist	(6)
#define	McErrBlockFull		(7)
#define	McErrExtend		(0x8000)

void MemCardInit( long val );
void MemCardEnd( void );
void MemCardStart(void);
void MemCardStop(void);
long MemCardExist( long chan );
long MemCardAccept( long chan );
long MemCardOpen( long chan, char* file, long flag );
void MemCardClose(void);
long MemCardReadData( unsigned long* adrs, long ofs, long bytes );
long MemCardReadFile( long chan, char* file, unsigned long* adrs, long ofs, long bytes );
long MemCardWriteData( unsigned long* adrs, long ofs, long bytes );
long MemCardWriteFile( long chan, char* file, unsigned long* adrs, long ofs ,long bytes );
long MemCardCreateFile( long chan, char* file, long blocks );
long MemCardDeleteFile( long chan, char* file );
long MemCardFormat( long chan );
long MemCardUnformat(long chan);
long MemCardSync( long mode, long* cmds, long* rslt );
MemCB MemCardCallback( MemCB func );
long MemCardGetDirentry( long chan, char* name, struct DIRENTRY* dir, long* files, long ofs, long max );

#endif
