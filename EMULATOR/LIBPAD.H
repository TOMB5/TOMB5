#ifndef LIBPAD_H
#define LIBPAD_H

#ifndef TRUE
#define TRUE		1
#endif
#ifndef FALSE
#define FALSE		0
#endif
#ifndef NULL
#define NULL		0
#endif

#define PadStateDiscon		0
#define PadStateFindPad		1
#define PadStateFindCTP1	2
#define PadStateFindCTP2	3
#define PadStateReqInfo		4
#define PadStateExecCmd		5
#define PadStateStable		6

#define InfoModeCurID		1
#define InfoModeCurExID		2
#define InfoModeCurExOffs	3
#define InfoModeIdTable		4

#define InfoActFunc		1
#define InfoActSub		2
#define InfoActSize		3
#define InfoActCurr		4
#define InfoActSign		5

#define PadMaxCurr		60
#define PadCurrCTP1		10

void PadInitDirect(unsigned char* unk00, unsigned char* unk01);
void PadInitMtap(unsigned char* unk00, unsigned char* unk01);
void PadInitGun(unsigned char* unk00, int unk01);
int PadChkVsync();
void PadStartCom();
void PadStopCom();
unsigned int PadEnableCom(unsigned int unk00);
void PadEnableGun(unsigned char unk00);
void PadRemoveGun();
int PadGetState(int unk00);
int PadInfoMode(int unk00, int, int unk01);
int PadInfoAct(int unk00, int, int unk01);
int PadInfoComb(int unk00, int, int unk01);
int PadSetActAlign(int unk00, unsigned char* unk01);
int PadSetMainMode(int socket, int offs, int lock);
void PadSetAct(int unk00, unsigned char* unk01, int unk02);

#endif