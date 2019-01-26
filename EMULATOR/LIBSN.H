#ifndef LIBSN_H
#define LIBSN_H

extern int PCinit();
extern int PCopen(char* name, int flags, int perms);
extern int PCcreat(char* name, int perms);
extern int PClseek(int fd, int offset, int mode);
extern int PCread(int fd, char* buff, int len);
extern int PCwrite(int fd, char* buff, int len);
extern int PCclose(int fd);

#endif