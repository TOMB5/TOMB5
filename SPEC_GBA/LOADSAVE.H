#ifndef LOADSAVE_H
#define LOADSAVE_H

extern int DisplayFiles(int cursor, int maxfiles);
extern int LoadGame();
extern int SaveGame();
extern struct REQUESTER NoGamesReq;
extern struct REQUESTER LoadingReq;

#endif