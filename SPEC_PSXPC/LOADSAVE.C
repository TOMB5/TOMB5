#include "LOADSAVE.H"

#include "SPECTYPES.H"
#include "SPECIFIC.H"

static struct REQUESTER InsertReq;
static struct REQUESTER CheckingReq;
static struct REQUESTER FormatReq;
static struct REQUESTER OverwriteReq;
static struct REQUESTER LoadingReq;
static struct REQUESTER SavingReq;
static struct REQUESTER FormattingReq;
static struct REQUESTER LoadOkReq;
static struct REQUESTER LoadErrorReq;
static struct REQUESTER SaveOkReq;
static struct REQUESTER SaveErrorReq;
static struct REQUESTER FormatErrorReq;
static struct REQUESTER NotFormatReq;
static struct REQUESTER NoSpaceReq;
static struct REQUESTER NoGamesReq;


int SaveGame()//62E3C, 63520
{
	S_Warn("[SaveGame] - Unimplemented!\n");
	return 0;
}

int LoadGame()//6297C, 63060
{
	S_Warn("[LoadGame] - Unimplemented!\n");
	return 0;
}

int DisplayFiles(int cursor, int maxfiles)//626E4, 62DC8
{
	S_Warn("[DisplayFiles] - Unimplemented!\n");
	return 0;
}