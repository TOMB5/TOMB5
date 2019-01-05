#ifndef IEPAELLA_H
#define IEPAELLA_H

#define SPU_MALLOC_RECSIZ 8
#define SPU_SUCCESS	0
#define SPU_INVALID_ARGS (-3)
#define SPU_DIAG	(-2)
#define SPU_CHECK	(-1)
#define SPU_OFF		0
#define SPU_ON		1
#define SPU_CLEAR	2
#define SPU_RESET	3
#define SPU_DONT_CARE	4
#define SPU_ALL		0
#define SPU_CDONLY	5
#define SPU_VOICEONLY	6
#define SPU_CONT	7
#define SPU_BIT		8
#define SPU_NULL	0
/* Macros below will be obsoleted. */
#define SpuDiag		SPU_DIAG
#define SpuCheck	SPU_CHECK
#define SpuOff		SPU_OFF
#define SpuOn		SPU_ON
#define SpuClear	SPU_CLEAR
#define SpuReset	SPU_RESET
#define SpuDontCare	SPU_DONT_CARE
#define SpuALL		SPU_ALL
#define SpuCDOnly	SPU_CDONLY
#define SpuVoiceOnly	SPU_VOICEONLY
#define SpuCont		SPU_CONT
#define SpuNull		SPU_NULL

#define SPU_OFF_ENV_ON	2
#define SPU_ON_ENV_OFF	3
/* Macros below will be obsoleted. */
#define SpuOffEnvOn	SPU_OFF_ENV_ON
#define SpuOnEnvOff	SPU_ON_ENV_OFF

#define SPU_ERROR	(-1)
/* Macros below will be obsoleted. */
#define SpuError	SPU_ERROR

#define SPU_TRANSFER_BY_DMA 0L
#define SPU_TRANSFER_BY_IO 1L
/* Macros below will be obsoleted. */
#define SpuTransferByDMA SPU_TRANSFER_BY_DMA
#define SpuTransferByIO  SPU_TRANSFER_BY_IO
#define SpuTransByDMA SpuTransferByDMA
#define SpuTransByIO SpuTransferByIO

#define SPU_TRANSFER_WAIT 1
#define SPU_TRANSFER_PEEK 0
#define SPU_TRANSFER_GLANCE SPU_TRANSFER_PEEK

typedef struct {
	short left;	       /* Lch */
	short right;       /* Rch */
} SpuVolume;

typedef struct {
	unsigned long	voice;		/* set voice:
								SpuSetVoiceAttr: each voice is a bit array
								SpuGetVoiceAttr: voice is a bit value */
	unsigned long	mask;		/* settings attribute bit (invalid with Get) */
	SpuVolume		volume;		/* volume                         */
	SpuVolume		volmode;	/* volume mode                    */
	SpuVolume		volumex;	/* current volume (invalid with Set) */
	unsigned short	pitch;		/* tone (pitch setting) */
	unsigned short	note;		/* tone (note setting) */
	unsigned short	sample_note;	/* tone (note setting) */
	short		envx;		/* current envelope value (invalid with Set) */
	unsigned long	addr;		/* waveform data start address */
	unsigned long	loop_addr;	/* loop start address */
	long		a_mode;		/* Attack rate mode			*/
	long		s_mode;		/* Sustain rate mode			*/
	long		r_mode;		/* Release rate mode			*/
	unsigned short	ar;		/* Attack rate				*/
	unsigned short	dr;		/* Decay rate				*/
	unsigned short	sr;		/* Sustain rate				*/
	unsigned short	rr;		/* Release rate				*/
	unsigned short	sl;		/* Sustain level			*/
	unsigned short	adsr1;		/* adsr1 for `VagAtr' */
	unsigned short	adsr2;		/* adsr2 for `VagAtr' */
} SpuVoiceAttr;

typedef struct {
	unsigned char minute;		/* minute (BCD) */
	unsigned char second;		/* second (BCD) */
	unsigned char sector;		/* sector (BCD) */
	unsigned char track;		/* track (void) */
} CdlLOC;

typedef struct {
	CdlLOC	pos;		/* file location */
	unsigned long	size;		/* file size */
	char	name[16];	/* file name (body) */
} CdlFILE;

struct RECTPSX {
	short x; // size=0, offset=0
	short y; // size=0, offset=2
	short w; // size=0, offset=4
	short h; // size=0, offset=6
};

struct DISPENV {
	struct RECTPSX disp; // size=8, offset=0
	struct RECTPSX screen; // size=8, offset=8
	unsigned char isinter; // size=0, offset=16
	unsigned char isrgb24; // size=0, offset=17
	unsigned char pad0; // size=0, offset=18
	unsigned char pad1; // size=0, offset=19
};

struct DR_ENV {
	unsigned long tag; // size=0, offset=0
	unsigned long code[15]; // size=60, offset=4
};
struct DRAWENV {
	struct RECTPSX clip; // size=8, offset=0
	short ofs[2]; // size=4, offset=8
	struct RECTPSX tw; // size=8, offset=12
	unsigned short tpage; // size=0, offset=20
	unsigned char dtd; // size=0, offset=22
	unsigned char dfe; // size=0, offset=23
	unsigned char isbg; // size=0, offset=24
	unsigned char r0; // size=0, offset=25
	unsigned char g0; // size=0, offset=26
	unsigned char b0; // size=0, offset=27
	struct DR_ENV dr_env; // size=64, offset=28
};


struct DB_STRUCT {
	int current_buffer; // size=0, offset=0
	unsigned long *ot; // size=0, offset=4
	char *polyptr; // size=0, offset=8
	char *curpolybuf; // size=0, offset=12
	char *polybuf_limit; // size=0, offset=16
	int nOTSize; // size=0, offset=20
	int nPBSize; // size=0, offset=24
	unsigned long *order_table[2]; // size=8, offset=28
	unsigned long *poly_buffer[2]; // size=8, offset=36
	unsigned long *pickup_ot; // size=0, offset=44
	unsigned long *pickup_order_table[2]; // size=8, offset=48
	struct DRAWENV draw[2]; // size=184, offset=56
	struct DISPENV disp[2]; // size=40, offset=240
};

extern "C"
{
	/* extern void ??0IPaellaScreenButtons@@QAE@ABV0@@Z();
	extern void ??0IPaellaScreenButtons@@QAE@XZ();
	extern void ??4IPaellaScreenButtons@@QAEAAV0@ABV0@@Z();
	extern void ??_7IPaellaScreenButtons@@6B@();
	extern void ?SetColours@IPaellaScreenButtons@@SAXJJ@Z();
	extern void ?create@IPaellaScreenButtons@@SAPAV1@XZ();
	extern void ?currentPSSurfaceAddress@@3PAXA();
	extern void ?destroy@IPaellaScreenButtons@@SAXXZ();
	extern void ?segundomain@@YA?AW4EResult@@PBD@Z();*/
	extern void AddPrim();
	extern void AddPrims();
	extern void ApplyMatrix();
	extern void ApplyMatrixLV();
	extern void ApplyMatrixSV();
	extern void ApplyRotMatrix();
	extern void ApplyRotMatrixLV();
	extern void ApplyRotMatrixLV_S();
	extern void ApplyRotMatrixSV();
	extern void ApplyRotTransMatrix();
	extern void AverageZ3();
	extern void AverageZ4();
	extern void CatPrim();
	extern int CdControl(unsigned char com, unsigned char *param, unsigned char *result);
	extern int CdInit(void);
	extern CdlLOC* CdIntToPos(int i, CdlLOC *p);
	extern int CdPosToInt(CdlLOC *p);
	extern int CdRead(int sectors, unsigned long *buf, int mode);
	extern int CdReadSync(int mode, unsigned char *result);
	extern CdlFILE *CdSearchFile(CdlFILE *fp, char *name);
	extern int CdSetDebug(int level);
	extern void ChangeClearPAD();
	extern void ClearImage();
	extern void ClearOTag();
	extern void ClearOTagR();
	extern void CloseEvent();
	extern void CompMatrix();
	extern void CompMatrixLV();
	extern void CrossProduct();
	extern void DecodeGIF();
	extern void DisableEvent();
	extern void DrawOTag();
	extern void DrawOTagCallback();
	extern void DrawOTagEnv(unsigned long *p, DRAWENV *env);
	extern void DrawPrim();
	extern int DrawSync(int mode);
	extern unsigned long DrawSyncCallback(void(*func)(void));
	extern void FreeJPEG();
	extern void GetClut();
	extern void GetFilePrefix();
	extern void GetFullFileName();
	extern void GetTPage();
	extern void GetVSyncTime();
	extern void InitGeom();
	extern void InitPAD();
	extern void IsEndPrim();
	extern void LoadAverage12();
	extern void LoadAverageShort0();
	extern void LoadAverageShort12();
	extern void LoadClut();
	extern void LoadClut2();
	extern int LoadImage(RECTPSX *rect, unsigned long *p);
	extern void LoadImageConvert();
	extern void LoadJPEG();
	extern void Lzc();
	extern void MVMVA();
	extern void MatrixNormal();
	extern void MatrixNormal_1();
	extern void MatrixNormal_2();
	extern void MoveImage();
	extern void MoveImage_Convert12To16();
	extern void MulMatrix();
	extern void MulMatrix0();
	extern void MulMatrix2();
	extern void MulRotMatrix();
	extern void MulRotMatrix0();
	extern void NextPrim();
	extern void NormalClip();
	extern void OpenEvent();
	extern void OpenTIM();
	extern void OuterProduct0();
	extern void PCclose();
	extern void PClseek();
	extern void PCopen();
	extern void PCopenAbsolute();
	extern void PCread();
	extern void PCwrite();
	extern void PalletiseSpriteIntoVRAM();
	extern void PalletiseTextureIntoVRAM();
	extern void PopMatrix();
	extern void PushMatrix();
	extern DISPENV *PutDispEnv(DISPENV *env);
	extern DRAWENV *PutDrawEnv(DRAWENV *env);
	extern void ReadAlpha();
	extern void ReadRotMatrix();
	extern void ReadTIM();
	extern void ResetCallback();
	extern int ResetGraph(int mode);
	extern void ResetTextureCache();
	extern void RestartCallback();
	extern void RotAverageNclip3();
	extern void RotAverageNclip4();
	extern void SetBackColor();
	extern void SetClutTransparencies();
	extern void SetDefDispEnv(DISPENV *env, int x, int y, int w, int h);
	extern void SetDefDrawEnv(DRAWENV *env, int x, int y, int w, int h);
	extern void SetDispMask(int mask);
	extern void SetDrawArea();
	extern void SetDrawEnv();
	extern void SetDrawMode();
	extern void SetDrawTPage();
	extern void SetFilePrefix();
	extern void SetGeomOffset();
	extern void SetGeomScreen();
	extern int SetGraphDebug(int level);
	extern void SetLineF2();
	extern void SetLineF3();
	extern void SetLineF4();
	extern void SetLineG2();
	extern void SetLineG3();
	extern void SetLineG4();
	extern void SetMulMatrix();
	extern void SetMulRotMatrix();
	extern void SetPolyF3();
	extern void SetPolyF4();
	extern void SetPolyFT3();
	extern void SetPolyFT4();
	extern void SetPolyG3();
	extern void SetPolyG4();
	extern void SetPolyGT3();
	extern void SetPolyGT4();
	extern void SetRotMatrix();
	extern void SetSemiTrans();
	extern void SetShadeTex();
	extern void SetTexWindow();
	extern void SetTransMatrix();
	extern void SetVideoMode();
	extern void SpuGetAllKeysStatus();
	extern void SpuGetKeyStatus();
	extern void SpuInit();
	extern void SpuIsTransferCompleted();
	extern void SpuQuit();
	extern void SpuSetKey();
	extern void SpuSetKeyOnWithAttr();
	extern void SpuSetReverbModeParam();
	extern long SpuSetTransferMode(long mode);
	extern void SpuSetTransferStartAddr();
	extern void SpuSetVoiceAttr();
	extern void SpuWrite();
	extern void SquareRoot12();
	extern void SsEnd();
	extern void SsInit();
	extern void SsQuit();
	extern void SsSeqClose();
	extern void SsSeqOpen();
	extern void SsSeqPause();
	extern void SsSeqPlay();
	extern void SsSeqReplay();
	extern void SsSeqSetVol();
	extern void SsSeqStop();
	extern void SsSetReservedVoice();
	extern void SsSetTableSize();
	extern void SsSetTickMode();
	extern void SsStart();
	extern void SsUtFlush();
	extern void SsUtKeyOffV();
	extern void SsUtKeyOnV();
	extern void SsUtKeyOnVex();
	extern void SsUtSetVVol();
	extern void SsVabClose();
	extern void SsVabOpenHead();
	extern void SsVabOpenHeadSticky();
	extern void SsVabTransBodyCallback();
	extern void SsVabTransCompleted();
	extern void StartPAD();
	extern void StopCallback();
	extern void StopPAD();
	extern void StoreImage();
	extern void TermPrim();
	extern void TidyFilePrefix();
	extern void TransMatrix();
	extern void TransposeMatrix();
	extern int VSync(int mode);
	extern int VSyncCallback(void(*f)(void));
	extern void VectorNormal();
	extern void VectorNormalS();
	extern void VectorNormalSS();
	extern void WaitEvent();
	extern void _MulMatrix();
	extern void __FlipRotMatrixX();
	extern void __ScratchPadMirror();
	extern void __adddvd();
	extern void __adddvl();
	extern void __check_quit_request();
	extern void __gte_SetTransMatrix();
	extern void __gte_controlRegisters();
	extern void __gte_dataRegisters();
	extern void __gte_ld_intpol_bv0();
	extern void __gte_ld_intpol_bv1();
	extern void __gte_ld_intpol_sv0();
	extern void __gte_ld_intpol_sv1();
	extern void __gte_ld_intpol_uv0();
	extern void __gte_ld_intpol_uv1();
	extern void __gte_ldbv();
	extern void __gte_ldclmv();
	extern void __gte_ldcv();
	extern void __gte_ldlv0();
	extern void __gte_ldopv1();
	extern void __gte_ldrgb3c();
	extern void __gte_ldsv();
	extern void __gte_ldv3c_vertc();
	extern void __gte_stbv();
	extern void __gte_stclmv();
	extern void __gte_stcv();
	extern void __gte_stsv();
	extern void __request_quit();
	extern void __strgb3__();
	extern void __stsxy3__();
	extern void __subdvd();
	extern void __subdvl();
	extern void _swc2block();
	extern void g_gamval();
	extern void g_noBlankOnBlit();
	extern void getPaellaFatalError();
	extern void get_control_reg_iQ();
	extern void gte_LoadAverageShort12();
	extern void gte_OuterProduct12();
	extern void gte_avsz3();
	extern void gte_avsz4();
	extern void gte_nclip();
	extern void gte_ncs();
	extern void gte_nct();
	extern void gte_rtps();
	extern void gte_rtpt();
	extern void mapKeys();
	extern void psx_GetTimeDate();
	extern void psx_doFlipScreen();
	extern void psx_setLeftHanded();
	extern void psx_signal_renderer();
	extern void runGame();
	extern void setPaellaFatalError();
	extern void set_control_regQ();
	extern void set_data_regQ();
}

#endif