struct NCB {
    char command;
    unsigned char retcode;
    unsigned char lsn;
    unsigned char number;
    void far *buffer;
    unsigned int length;
    char callName[16];
    char name[16];
    unsigned char receiveTimeout;
    unsigned char sendTimeout;
    void (far *post)(void);
    unsigned char lana;
    char commandComplete;
    unsigned char reserved[14];
};

struct ProcessPostWork {
    struct NCB completed;
    struct NCB far *localNCB;
    int sendResult;
    unsigned int length;
};

struct NetbiosControlBlock {
    unsigned char command;
    unsigned char immediateStatus;
    unsigned char reserved[0x2f];
    unsigned char finalStatus;
};

extern unsigned int far ncbTail;
extern unsigned int far ncbOffset[];
extern unsigned int far ncbSegment[];
extern int near MapPlane;
extern char far * near theNetBiosBuffer;
extern char near processPostServerName[8];
extern char near processPostClientName[8];
extern int near processPostState;

extern unsigned char near MapA[128][64];
extern unsigned char near MapB[128][64];
extern unsigned char near MapR[128][64];
extern unsigned char near LifeA[128][64];
extern unsigned char near LifeB[128][64];
extern unsigned char near LifeR[128][64];
extern unsigned char near ForSaleState[];
extern unsigned char near DataBlockEnd[];

extern void far movedata(unsigned int sourceSegment,
                         unsigned int sourceOffset,
                         unsigned int destinationSegment,
                         unsigned int destinationOffset,
                         unsigned int count);
extern volatile void far NbFinalStatus(
    volatile struct NetbiosControlBlock far *ncb);
extern int far NbHangUp(char session);
extern int far NbSend(unsigned char far *buffer, int length, char session);
extern unsigned int far NbReceive(unsigned char session,
                                  unsigned char far *buffer,
                                  unsigned int far *length);

extern unsigned int far NbPostListen(char far *name, char far *callName,
                                     unsigned char session,
                                     unsigned char number,
                                     void far *post);
extern unsigned int far NbPostReceiveAny(unsigned char session,
                                         unsigned char far *buffer,
                                         unsigned int length,
                                         unsigned long timeout);
extern void interrupt far NetBIOSPost(unsigned int segment,
                                      unsigned int savedDS,
                                      unsigned int savedDI,
                                      unsigned int savedSI,
                                      unsigned int savedBP,
                                      unsigned int savedSP,
                                      unsigned int offset);

#define POST_OFF(p) ((unsigned int)(unsigned long)(void far *)(p))
#define POST_SEG(p) ((unsigned int)(((unsigned long)(void far *)(p)) >> 16))

/* Candidate translation unit simant_01B6_DoUserButtonUpdate_12_scaffold_split: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _DoUserButtonUpdate, _SetUserButton, _ClearBookmarks, _DrawRibbonMessage, _HelpKeyDown, _DoNextWindow, _RedrawWindows, _DoDebugWin, _LoadFancyCursor, _SetFancyCursor, _InitInstance, _PatchColorArrays
 * SCAFFOLDED: unclaimed members _DoUserButton, _DoBookMark, _DoMouse, _DoMenuEntry, _AdjustWndMinMax, _ProcessPost, _UpdateWindows, MYTIMERFUNC are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

extern int far GamePaused;
extern int far OptionStates[];
extern void far win_SetObjSelectedState(int object, int selected);
struct WinButtonObject {
    unsigned char reserved1[0x1c];
    unsigned char flagsLo;
    unsigned char reserved1d_1f[3];
    union {
        unsigned int group;
        struct {
            unsigned char groupLow;
            unsigned char type;
        } bytes;
    } groupType;
    unsigned char reserved22_23[2];
    unsigned char flags24;
    unsigned char flags25;
};
#define flags1 flags24
#define flags2 flags25
extern int far showTrails;
extern void far win_SetButtonBitmaps(int objectNumber, unsigned int bitmapUp,
                                     unsigned int bitmapDown);
extern void far win_LockWin(int objectNumber);
extern struct WinButtonObject far * far win_ObjAddr(int objectNumber);
extern void far win_UnlockWin(int objectNumber);
struct BookMark {
    int object;
    int plane;
    int x;
    int y;
    int flags;
};
extern struct BookMark far bookMark[7];
extern int near win_hwnd[];
extern long far editMessage;
extern long far mapMessage;
extern long far mapMessageRemoveTime;
extern void far MSClipStart(int window);
extern long far TickCount(void);
extern void far font_SetFont(int font);
extern void far win_PrintfAtObj(int object, long message);
extern int far ConvColor(int color);
extern void far win_FillObjRect(int object, int color);
extern void far MSClipEnd(void);
extern int near bHelp;
extern int near rootWnd;
extern int far hHelpCursor;
extern char far helpFile[];
extern int far pascal GetKeyState(int key);
extern unsigned int far pascal SetCursor(unsigned int cursor);
extern int far pascal WinHelp(int window, char far *file, unsigned int command, unsigned long data);
extern unsigned int far pascal GetClassWord(unsigned int window, int index);
extern int far pascal GetNextWindow(int window, int relation);
extern int far pascal GetWindow(int window, int relation);
extern int far pascal IsWindowVisible(int window);
extern void far pascal BringWindowToTop(int window);
typedef void (far *WindowProc)(void);
extern int near hInst;
extern int near ribbonBarWnd;
extern int far pascal MyEnumFunc(int window, unsigned long parameter);
extern WindowProc far pascal MakeProcInstance(WindowProc procedure,
                                              int instance);
extern void far pascal FreeProcInstance(WindowProc procedure);
extern int far pascal EnumChildWindows(int parent, WindowProc procedure,
                                       unsigned long parameter);
extern int far pascal InvalidateRect(int window, void far *rect,
                                     unsigned flags);
extern unsigned long far pascal GetTickCount(void);
extern unsigned int far pascal LoadCursor(unsigned int instance,
                                          char far *name);
extern unsigned int near magCursor;
extern unsigned int near rockCursor;
extern unsigned int near digCursor;
extern unsigned int near antCursor;
extern unsigned int near foodCursor;
extern unsigned int near dropCursor;
extern unsigned int near sprayCursor;
extern int far win_IsWinInFront(int window);
extern int far pascal GetAsyncKeyState(int key);
extern int far CurGameType;
extern int far CurExpTool;
struct Rect {
    int left;
    int top;
    int right;
    int bottom;
};
extern int near mainRootWnd;
extern int near screenWidth;
extern int near screenHeight;
extern int far pascal GetSystemMetrics(int index);
extern int far pascal CreateWindow(char far *className, char far *windowName,
    unsigned long style, int x, int y, int width, int height,
    int parent, int menu, int instance, void far *param);
extern int far pascal SetProp(int window, char far *name, int data);
extern void far pascal ShowWindow(int window, int command);
extern void far pascal UpdateWindow(int window);
extern void far pascal GetClientRect(unsigned int window, struct Rect far *rect);
extern unsigned char near CTab[144];
extern unsigned char near HTab[208];
extern unsigned char near LTab[32];
extern unsigned char near CTabB[24];
extern unsigned char near CTabR[24];
extern unsigned char near PherColorTab[16];


#define MAKEINTRESOURCE(id) ((char far *)(unsigned long)(id))
typedef long (far pascal *WNDPROC)(int, unsigned int, int, long);
struct WndClass {
    unsigned int style;
    WNDPROC lpfnWndProc;
    int cbClsExtra;
    int cbWndExtra;
    unsigned int hInstance;
    unsigned int hIcon;
    unsigned int hCursor;
    unsigned int hbrBackground;
    char far *lpszMenuName;
    char far *lpszClassName;
};
extern long far pascal MainWndProc(int window, unsigned int message, int wParam, long lParam);
extern unsigned int far pascal LoadIcon(unsigned int instance, char far *name);
extern unsigned int far pascal GetStockObject(int object);
extern unsigned int far pascal RegisterClass(struct WndClass far *wndClass);

/* Natural initialized fields in target DGROUP address order. */
struct SimantPrivateData {
    char privateDataPrefix[1]; /* 014A */
    char buttonSpeedSlow[21]; /* 014B */
    char buttonSpeedNormal[23]; /* 0160 */
    char buttonSpeedFast[21]; /* 0177 */
    char buttonSpeedUltra[22]; /* 018C */
    char bookmarkPlaced[26]; /* 01A2 */
    char bookmarkNotPlaced[30]; /* 01BC */
    unsigned int keyCheatPosition; /* 01DA */
    unsigned int keyCheatLength; /* 01DC */
    char keyPropertyIndex[6]; /* 01DE */
    char keyFlashStart[29]; /* 01E4 */
    char keyFlashAlmost[35]; /* 0201 */
    char keyFlashDone[28]; /* 0224 */
    char mousePropertyIndex[6]; /* 0240 */
    char mouseFlashStart[27]; /* 0246 */
    char mouseFlashAlmost[33]; /* 0261 */
    char mouseFlashDone[26]; /* 0282 */
    long lastTick; /* 029C */
    long frames; /* 02A0 */
    long total; /* 02A4 */
    char debugFormat[28]; /* 02A8 */
    int processPostState; /* 02C4 */
    char processPostServerName[8]; /* 02C6 */
    char processPostClientName[8]; /* 02CE */
    char networkClientName[8]; /* 02D6 */
    char networkServerName[8]; /* 02DE */
    long updateStamp; /* 02E6 */
    int yardDrawPending; /* 02EA */
    int editDrawPending; /* 02EC */
    unsigned int timerCallCount; /* 02EE */
    int timerBusy; /* 02F0 */
    int timerState02F2; /* 02F2 */
    int timerState02F4; /* 02F4 */
    char timerIconNormal[7]; /* 02F6 */
    char timerIconPaused[7]; /* 02FD */
    char timerIconBlackWin[9]; /* 0304 */
    char timerIconBlackWon[9]; /* 030D */
    char timerIconRedWin[7]; /* 0316 */
    char timerIconRedLost[7]; /* 031D */
    char timerAntFormat[6]; /* 0324 */
    char cursorMagResource[10]; /* 032A */
    char cursorRockResource[11]; /* 0334 */
    char cursorDigResource[10]; /* 033F */
    char cursorAntResource[10]; /* 0349 */
    char cursorFoodResource[11]; /* 0353 */
    char cursorDropResource[11]; /* 035E */
    char cursorSprayResource[13]; /* 0369 */
    int mainWndState0376; /* 0376 */
    int mainWndState0378; /* 0378 */
    int mainWndState037A; /* 037A */
    int mainWndMessageMap[8]; /* 037C */
    int mainWndState038C; /* 038C */
    char mainWndTitle[19]; /* 038E */
    char mainWndPropertyIndex0[6]; /* 03A1 */
    char capturePrompt[47]; /* 03A7 */
    char captureTitle0[15]; /* 03D6 */
    char captureTitle1[15]; /* 03E5 */
    char noCaptureMessage[28]; /* 03F4 */
    char ribbonMessage0[24]; /* 0410 */
    char ribbonMessage1[24]; /* 0428 */
    char mainWndPropertyIndex1[6]; /* 0440 */
    char mainWndPropertyIndex2[6]; /* 0446 */
    char mainWndPropertyIndex3[6]; /* 044C */
    char mainWndPropertyIndex4[6]; /* 0452 */
    char mainWndPropertyIndex5[6]; /* 0458 */
    char wmSizeFormat[95]; /* 045E */
    char activateStart[28]; /* 04BD */
    char mainWndPropertyIndex6[6]; /* 04D9 */
    char activateCapture[35]; /* 04DF */
    char activateReady[28]; /* 0502 */
    char deactivateStart[30]; /* 051E */
    char deactivateRelease[39]; /* 053C */
    char deactivateReady[30]; /* 0563 */
    char paletteChangedCalled[31]; /* 0581 */
    char paletteChangedCalling[32]; /* 05A0 */
    char paletteChangedSame[32]; /* 05C0 */
    char paletteChangedInvalidate[50]; /* 05E0 */
    char memoryLowMessage[20]; /* 0612 */
    char initInstanceMainClass[7]; /* 0626 */
    char initInstanceMainTitle[8]; /* 062D */
    char initInstancePropertyIndex[6]; /* 0635 */
    char initInstanceRibbonTitle[18]; /* 063B */
    char initInstanceRibbonClass[13]; /* 064D */
    char initInstanceRootTitle[19]; /* 065A */
    char initInstanceRootClass[8]; /* 066D */
    char initApplicationIcon[7]; /* 0675 */
    char initApplicationRootClass[8]; /* 067C */
    char initApplicationGenericClass[14]; /* 0684 */
    char initApplicationRibbonClass[13]; /* 0692 */
    char winMainClassName[8]; /* 069F */
    char notInstalledPattern[11]; /* 06A7 */
    char notInstalledMessage[52]; /* 06B2 */
    char winMainPropertyIndex[6]; /* 06E6 */
    char optionSound[6]; /* 06EC */
    char optionAutotrack[10]; /* 06F2 */
    char appSection0[7]; /* 06FC */
    char optionMusic[6]; /* 0703 */
    char appSection1[7]; /* 0709 */
    char optionEffects[8]; /* 0710 */
    char appSection2[7]; /* 0718 */
    char optionEvents[7]; /* 071F */
    char appSection3[7]; /* 0726 */
    char optionMessages[9]; /* 072D */
    char appSection4[7]; /* 0736 */
    char optionSilly[6]; /* 073D */
    char appSection5[7]; /* 0743 */
    char cancelledMessage[18]; /* 074A */
    char mapButtonProfile[16]; /* 075C */
    char appSection6[7]; /* 076C */
    char yardButtonProfile[17]; /* 0773 */
    char appSection7[7]; /* 0784 */
    char acceleratorResource[17]; /* 078B */
    char releasingCaptureMessage[24]; /* 079C */
    char profileOne0[2]; /* 07B4 */
    char profileZero0[2]; /* 07B6 */
    char optionAutotrackAgain[10]; /* 07B8 */
    char appSection8[7]; /* 07C2 */
    char profileOne1[2]; /* 07C9 */
    char profileZero1[2]; /* 07CB */
    char optionMusicAgain[6]; /* 07CD */
    char appSection9[7]; /* 07D3 */
    char profileOne2[2]; /* 07DA */
    char profileZero2[2]; /* 07DC */
    char optionEffectsAgain[8]; /* 07DE */
    char appSection10[7]; /* 07E6 */
    char profileOne3[2]; /* 07ED */
    char profileZero3[2]; /* 07EF */
    char optionEventsAgain[7]; /* 07F1 */
    char appSection11[7]; /* 07F8 */
    char profileOne4[2]; /* 07FF */
    char profileZero4[2]; /* 0801 */
    char optionMessagesAgain[9]; /* 0803 */
    char appSection12[7]; /* 080C */
    char profileOne5[2]; /* 0813 */
    char profileZero5[2]; /* 0815 */
    char optionSillyAgain[6]; /* 0817 */
    char appSection13[7]; /* 081D */
    char mapButtonProfileAgain[16]; /* 0824 */
    char integerFormat0[3]; /* 0834 */
    char appSection14[7]; /* 0837 */
    char yardButtonProfileAgain[17]; /* 083E */
    char integerFormat1[3]; /* 084F */
};
static struct SimantPrivateData near privateDGROUP = {
    "\000", /* 014A: privateDataPrefix */
    "Game speed now slow.\000", /* 014B: buttonSpeedSlow */
    "Game speed now normal.\000", /* 0160: buttonSpeedNormal */
    "Game speed now fast.\000", /* 0177: buttonSpeedFast */
    "Game speed now ultra.\000", /* 018C: buttonSpeedUltra */
    "Bookmark has been placed.\000", /* 01A2: bookmarkPlaced */
    "Bookmark has not been placed.\000", /* 01BC: bookmarkNotPlaced */
    0U, /* 01DA: keyCheatPosition */
    0U, /* 01DC: keyCheatLength */
    "INDEX\000", /* 01DE: keyPropertyIndex */
    "DoKeyDown: Flash(start)(%d)\n\000", /* 01E4: keyFlashStart */
    "DoKeyDown: Flash(almost done)(%d)\n\000", /* 0201: keyFlashAlmost */
    "DoKeyDown: Flash(done)(%d)\n\000", /* 0224: keyFlashDone */
    "INDEX\000", /* 0240: mousePropertyIndex */
    "DoMouse: Flash(start)(%d)\n\000", /* 0246: mouseFlashStart */
    "DoMouse: Flash(almost done)(%d)\n\000", /* 0261: mouseFlashAlmost */
    "DoMouse: Flash(done)(%d)\n\000", /* 0282: mouseFlashDone */
    -1L, /* 029C: lastTick */
    0L, /* 02A0: frames */
    0L, /* 02A4: total */
    "Ave Length: %lu Speed: %lu\000\000", /* 02A8: debugFormat */
    1, /* 02C4: processPostState */
    "SERVANT\000", /* 02C6: processPostServerName */
    "CLIEANT\000", /* 02CE: processPostClientName */
    "CLIEANT\000", /* 02D6: networkClientName */
    "SERVANT\000", /* 02DE: networkServerName */
    0L, /* 02E6: updateStamp */
    0, /* 02EA: yardDrawPending */
    0, /* 02EC: editDrawPending */
    0U, /* 02EE: timerCallCount */
    0, /* 02F0: timerBusy */
    0, /* 02F2: timerState02F2 */
    0, /* 02F4: timerState02F4 */
    "SimAnt\000", /* 02F6: timerIconNormal */
    "SimAnt\000", /* 02FD: timerIconPaused */
    "BlackWin\000", /* 0304: timerIconBlackWin */
    "BlackWin\000", /* 030D: timerIconBlackWon */
    "RedWin\000", /* 0316: timerIconRedWin */
    "RedWin\000", /* 031D: timerIconRedLost */
    "Ant%d\000", /* 0324: timerAntFormat */
    "MagCursor\000", /* 032A: cursorMagResource */
    "RockCursor\000", /* 0334: cursorRockResource */
    "DigCursor\000", /* 033F: cursorDigResource */
    "AntCursor\000", /* 0349: cursorAntResource */
    "FoodCursor\000", /* 0353: cursorFoodResource */
    "DropCursor\000", /* 035E: cursorDropResource */
    "SprayCursor\000\000", /* 0369: cursorSprayResource */
    0, /* 0376: mainWndState0376 */
    0, /* 0378: mainWndState0378 */
    0, /* 037A: mainWndState037A */
    {-1, 3072, 3840, 4096, 4352, 3328, 3584, -1}, /* 037C: mainWndMessageMap */
    0, /* 038C: mainWndState038C */
    "SimAnt For Windows\000", /* 038E: mainWndTitle */
    "INDEX\000", /* 03A1: mainWndPropertyIndex0 */
    "Window %#x has the capture.\nDo capture debug?\n\000", /* 03A7: capturePrompt */
    "SimAnt Capture\000", /* 03D6: captureTitle0 */
    "SimAnt Capture\000", /* 03E5: captureTitle1 */
    "No windows has the capture.\000", /* 03F4: noCaptureMessage */
    "This is the ribbon bar.\000", /* 0410: ribbonMessage0 */
    "This is the ribbon bar.\000", /* 0428: ribbonMessage1 */
    "INDEX\000", /* 0440: mainWndPropertyIndex1 */
    "INDEX\000", /* 0446: mainWndPropertyIndex2 */
    "INDEX\000", /* 044C: mainWndPropertyIndex3 */
    "INDEX\000", /* 0452: mainWndPropertyIndex4 */
    "INDEX\000", /* 0458: mainWndPropertyIndex5 */
    "WM_SIZE: newWidth(%d) newHeight(%d) editWidth(%d) editHeight(%d) rectWidth(%d) rectHeight(%d)\n\000", /* 045E: wmSizeFormat */
    "ActivateApplication(START)\n\000", /* 04BD: activateStart */
    "INDEX\000", /* 04D9: mainWndPropertyIndex6 */
    "ActivateApplication(CAPTURE)(%#x)\n\000", /* 04DF: activateCapture */
    "ActivateApplication(READY)\n\000", /* 0502: activateReady */
    "DeActivateApplication(START)\n\000", /* 051E: deactivateStart */
    "DeActivateApplication(RELEASECAPTURE)\n\000", /* 053C: deactivateRelease */
    "DeActivateApplication(READY)\n\000", /* 0563: deactivateReady */
    "WM_PALETTECHANGED(called)(%s)\n\000", /* 0581: paletteChangedCalled */
    "WM_PALETTECHANGED(calling)(%s)\n\000", /* 05A0: paletteChangedCalling */
    "WM_PALETTECHANGED(same window)\n\000", /* 05C0: paletteChangedSame */
    "WM_PALETTECHANGED/WM_QUERYNEWPALETTE(Invalidate)\n\000", /* 05E0: paletteChangedInvalidate */
    "Memory is very low.\000", /* 0612: memoryLowMessage */
    "SimAnt\000", /* 0626: initInstanceMainClass */
    "AntRoot\000", /* 062D: initInstanceMainTitle */
    "INDEX\000", /* 0635: initInstancePropertyIndex */
    "SimAnt Ribbon Bar\000", /* 063B: initInstanceRibbonTitle */
    "RibbonWindow\000", /* 064D: initInstanceRibbonClass */
    "SimAnt Root Window\000", /* 065A: initInstanceRootTitle */
    "AntRoot\000", /* 066D: initInstanceRootClass */
    "SimAnt\000", /* 0675: initApplicationIcon */
    "AntRoot\000", /* 067C: initApplicationRootClass */
    "GenericWindow\000", /* 0684: initApplicationGenericClass */
    "RibbonWindow\000", /* 0692: initApplicationRibbonClass */
    "AntRoot\000", /* 069F: winMainClassName */
    "YYYYYYYYYY\000", /* 06A7: notInstalledPattern */
    "Program not installed correctly.\nPlease re-install.\000", /* 06B2: notInstalledMessage */
    "INDEX\000", /* 06E6: winMainPropertyIndex */
    "sound\000", /* 06EC: optionSound */
    "autotrack\000", /* 06F2: optionAutotrack */
    "SimAnt\000", /* 06FC: appSection0 */
    "music\000", /* 0703: optionMusic */
    "SimAnt\000", /* 0709: appSection1 */
    "effects\000", /* 0710: optionEffects */
    "SimAnt\000", /* 0718: appSection2 */
    "events\000", /* 071F: optionEvents */
    "SimAnt\000", /* 0726: appSection3 */
    "messages\000", /* 072D: optionMessages */
    "SimAnt\000", /* 0736: appSection4 */
    "silly\000", /* 073D: optionSilly */
    "SimAnt\000", /* 0743: appSection5 */
    "SimAnt cancelled.\000", /* 074A: cancelledMessage */
    "mapuserbutton%d\000", /* 075C: mapButtonProfile */
    "SimAnt\000", /* 076C: appSection6 */
    "yarduserbutton%d\000", /* 0773: yardButtonProfile */
    "SimAnt\000", /* 0784: appSection7 */
    "AcceleratorTable\000", /* 078B: acceleratorResource */
    "ReleasingCapture(quit)\n\000", /* 079C: releasingCaptureMessage */
    "1\000", /* 07B4: profileOne0 */
    "0\000", /* 07B6: profileZero0 */
    "autotrack\000", /* 07B8: optionAutotrackAgain */
    "SimAnt\000", /* 07C2: appSection8 */
    "1\000", /* 07C9: profileOne1 */
    "0\000", /* 07CB: profileZero1 */
    "music\000", /* 07CD: optionMusicAgain */
    "SimAnt\000", /* 07D3: appSection9 */
    "1\000", /* 07DA: profileOne2 */
    "0\000", /* 07DC: profileZero2 */
    "effects\000", /* 07DE: optionEffectsAgain */
    "SimAnt\000", /* 07E6: appSection10 */
    "1\000", /* 07ED: profileOne3 */
    "0\000", /* 07EF: profileZero3 */
    "events\000", /* 07F1: optionEventsAgain */
    "SimAnt\000", /* 07F8: appSection11 */
    "1\000", /* 07FF: profileOne4 */
    "0\000", /* 0801: profileZero4 */
    "messages\000", /* 0803: optionMessagesAgain */
    "SimAnt\000", /* 080C: appSection12 */
    "1\000", /* 0813: profileOne5 */
    "0\000", /* 0815: profileZero5 */
    "silly\000", /* 0817: optionSillyAgain */
    "SimAnt\000", /* 081D: appSection13 */
    "mapuserbutton%d\000", /* 0824: mapButtonProfileAgain */
    "%d\000", /* 0834: integerFormat0 */
    "SimAnt\000", /* 0837: appSection14 */
    "yarduserbutton%d\000", /* 083E: yardButtonProfileAgain */
    "%d\000", /* 084F: integerFormat1 */
};
static char near appSection15[] = "SimAnt"; /* 0852: trailing string */
#define privateDataPrefix (privateDGROUP.privateDataPrefix)
#define privateDataPrefix (privateDGROUP.privateDataPrefix)
#define buttonSpeedSlow (privateDGROUP.buttonSpeedSlow)
#define buttonSpeedNormal (privateDGROUP.buttonSpeedNormal)
#define buttonSpeedFast (privateDGROUP.buttonSpeedFast)
#define buttonSpeedUltra (privateDGROUP.buttonSpeedUltra)
#define bookmarkPlaced (privateDGROUP.bookmarkPlaced)
#define bookmarkNotPlaced (privateDGROUP.bookmarkNotPlaced)
#define keyCheatPosition (privateDGROUP.keyCheatPosition)
#define keyCheatLength (privateDGROUP.keyCheatLength)
#define keyPropertyIndex (privateDGROUP.keyPropertyIndex)
#define keyFlashStart (privateDGROUP.keyFlashStart)
#define keyFlashAlmost (privateDGROUP.keyFlashAlmost)
#define keyFlashDone (privateDGROUP.keyFlashDone)
#define mousePropertyIndex (privateDGROUP.mousePropertyIndex)
#define mouseFlashStart (privateDGROUP.mouseFlashStart)
#define mouseFlashAlmost (privateDGROUP.mouseFlashAlmost)
#define mouseFlashDone (privateDGROUP.mouseFlashDone)
#define lastTick (privateDGROUP.lastTick)
#define frames (privateDGROUP.frames)
#define total (privateDGROUP.total)
#define debugFormat (privateDGROUP.debugFormat)
#define processPostState (privateDGROUP.processPostState)
#define processPostServerName (privateDGROUP.processPostServerName)
#define processPostClientName (privateDGROUP.processPostClientName)
#define networkClientName (privateDGROUP.networkClientName)
#define networkServerName (privateDGROUP.networkServerName)
#define updateStamp (privateDGROUP.updateStamp)
#define yardDrawPending (privateDGROUP.yardDrawPending)
#define editDrawPending (privateDGROUP.editDrawPending)
#define timerCallCount (privateDGROUP.timerCallCount)
#define timerBusy (privateDGROUP.timerBusy)
#define timerState02F2 (privateDGROUP.timerState02F2)
#define timerState02F4 (privateDGROUP.timerState02F4)
#define timerIconNormal (privateDGROUP.timerIconNormal)
#define timerIconPaused (privateDGROUP.timerIconPaused)
#define timerIconBlackWin (privateDGROUP.timerIconBlackWin)
#define timerIconBlackWon (privateDGROUP.timerIconBlackWon)
#define timerIconRedWin (privateDGROUP.timerIconRedWin)
#define timerIconRedLost (privateDGROUP.timerIconRedLost)
#define timerAntFormat (privateDGROUP.timerAntFormat)
#define cursorMagResource (privateDGROUP.cursorMagResource)
#define cursorRockResource (privateDGROUP.cursorRockResource)
#define cursorDigResource (privateDGROUP.cursorDigResource)
#define cursorAntResource (privateDGROUP.cursorAntResource)
#define cursorFoodResource (privateDGROUP.cursorFoodResource)
#define cursorDropResource (privateDGROUP.cursorDropResource)
#define cursorSprayResource (privateDGROUP.cursorSprayResource)
#define mainWndState0376 (privateDGROUP.mainWndState0376)
#define mainWndState0378 (privateDGROUP.mainWndState0378)
#define mainWndState037A (privateDGROUP.mainWndState037A)
#define mainWndMessageMap (privateDGROUP.mainWndMessageMap)
#define mainWndState038C (privateDGROUP.mainWndState038C)
#define mainWndTitle (privateDGROUP.mainWndTitle)
#define mainWndPropertyIndex0 (privateDGROUP.mainWndPropertyIndex0)
#define capturePrompt (privateDGROUP.capturePrompt)
#define captureTitle0 (privateDGROUP.captureTitle0)
#define captureTitle1 (privateDGROUP.captureTitle1)
#define noCaptureMessage (privateDGROUP.noCaptureMessage)
#define ribbonMessage0 (privateDGROUP.ribbonMessage0)
#define ribbonMessage1 (privateDGROUP.ribbonMessage1)
#define mainWndPropertyIndex1 (privateDGROUP.mainWndPropertyIndex1)
#define mainWndPropertyIndex2 (privateDGROUP.mainWndPropertyIndex2)
#define mainWndPropertyIndex3 (privateDGROUP.mainWndPropertyIndex3)
#define mainWndPropertyIndex4 (privateDGROUP.mainWndPropertyIndex4)
#define mainWndPropertyIndex5 (privateDGROUP.mainWndPropertyIndex5)
#define wmSizeFormat (privateDGROUP.wmSizeFormat)
#define activateStart (privateDGROUP.activateStart)
#define mainWndPropertyIndex6 (privateDGROUP.mainWndPropertyIndex6)
#define activateCapture (privateDGROUP.activateCapture)
#define activateReady (privateDGROUP.activateReady)
#define deactivateStart (privateDGROUP.deactivateStart)
#define deactivateRelease (privateDGROUP.deactivateRelease)
#define deactivateReady (privateDGROUP.deactivateReady)
#define paletteChangedCalled (privateDGROUP.paletteChangedCalled)
#define paletteChangedCalling (privateDGROUP.paletteChangedCalling)
#define paletteChangedSame (privateDGROUP.paletteChangedSame)
#define paletteChangedInvalidate (privateDGROUP.paletteChangedInvalidate)
#define memoryLowMessage (privateDGROUP.memoryLowMessage)
#define initInstanceMainClass (privateDGROUP.initInstanceMainClass)
#define initInstanceMainTitle (privateDGROUP.initInstanceMainTitle)
#define initInstancePropertyIndex (privateDGROUP.initInstancePropertyIndex)
#define initInstanceRibbonTitle (privateDGROUP.initInstanceRibbonTitle)
#define initInstanceRibbonClass (privateDGROUP.initInstanceRibbonClass)
#define initInstanceRootTitle (privateDGROUP.initInstanceRootTitle)
#define initInstanceRootClass (privateDGROUP.initInstanceRootClass)
#define initApplicationIcon (privateDGROUP.initApplicationIcon)
#define initApplicationRootClass (privateDGROUP.initApplicationRootClass)
#define initApplicationGenericClass (privateDGROUP.initApplicationGenericClass)
#define initApplicationRibbonClass (privateDGROUP.initApplicationRibbonClass)
#define winMainClassName (privateDGROUP.winMainClassName)
#define notInstalledPattern (privateDGROUP.notInstalledPattern)
#define notInstalledMessage (privateDGROUP.notInstalledMessage)
#define winMainPropertyIndex (privateDGROUP.winMainPropertyIndex)
#define optionSound (privateDGROUP.optionSound)
#define optionAutotrack (privateDGROUP.optionAutotrack)
#define appSection0 (privateDGROUP.appSection0)
#define optionMusic (privateDGROUP.optionMusic)
#define appSection1 (privateDGROUP.appSection1)
#define optionEffects (privateDGROUP.optionEffects)
#define appSection2 (privateDGROUP.appSection2)
#define optionEvents (privateDGROUP.optionEvents)
#define appSection3 (privateDGROUP.appSection3)
#define optionMessages (privateDGROUP.optionMessages)
#define appSection4 (privateDGROUP.appSection4)
#define optionSilly (privateDGROUP.optionSilly)
#define appSection5 (privateDGROUP.appSection5)
#define cancelledMessage (privateDGROUP.cancelledMessage)
#define mapButtonProfile (privateDGROUP.mapButtonProfile)
#define appSection6 (privateDGROUP.appSection6)
#define yardButtonProfile (privateDGROUP.yardButtonProfile)
#define appSection7 (privateDGROUP.appSection7)
#define acceleratorResource (privateDGROUP.acceleratorResource)
#define releasingCaptureMessage (privateDGROUP.releasingCaptureMessage)
#define profileOne0 (privateDGROUP.profileOne0)
#define profileZero0 (privateDGROUP.profileZero0)
#define optionAutotrackAgain (privateDGROUP.optionAutotrackAgain)
#define appSection8 (privateDGROUP.appSection8)
#define profileOne1 (privateDGROUP.profileOne1)
#define profileZero1 (privateDGROUP.profileZero1)
#define optionMusicAgain (privateDGROUP.optionMusicAgain)
#define appSection9 (privateDGROUP.appSection9)
#define profileOne2 (privateDGROUP.profileOne2)
#define profileZero2 (privateDGROUP.profileZero2)
#define optionEffectsAgain (privateDGROUP.optionEffectsAgain)
#define appSection10 (privateDGROUP.appSection10)
#define profileOne3 (privateDGROUP.profileOne3)
#define profileZero3 (privateDGROUP.profileZero3)
#define optionEventsAgain (privateDGROUP.optionEventsAgain)
#define appSection11 (privateDGROUP.appSection11)
#define profileOne4 (privateDGROUP.profileOne4)
#define profileZero4 (privateDGROUP.profileZero4)
#define optionMessagesAgain (privateDGROUP.optionMessagesAgain)
#define appSection12 (privateDGROUP.appSection12)
#define profileOne5 (privateDGROUP.profileOne5)
#define profileZero5 (privateDGROUP.profileZero5)
#define optionSillyAgain (privateDGROUP.optionSillyAgain)
#define appSection13 (privateDGROUP.appSection13)
#define mapButtonProfileAgain (privateDGROUP.mapButtonProfileAgain)
#define integerFormat0 (privateDGROUP.integerFormat0)
#define appSection14 (privateDGROUP.appSection14)
#define yardButtonProfileAgain (privateDGROUP.yardButtonProfileAgain)
#define integerFormat1 (privateDGROUP.integerFormat1)
extern unsigned char near doKeyDownCheatBuffer[4];


extern int far mapUserButton;  /* scaffold reference for pool word BE74 (segment 10, SEGMENT_REPRESENTATIVE) */
extern int far match_position;  /* scaffold reference for pool word BE76 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Dx8;  /* scaffold reference for pool word BE78 (segment 8, MAPSYM_SITE_NAME) */
extern int far match_length;  /* scaffold reference for pool word BE7C (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Dy8;  /* scaffold reference for pool word BE7E (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far yardUserButton;  /* scaffold reference for pool word BE88 (segment 10, SEGMENT_REPRESENTATIVE) */
extern int far paletteFlag;  /* scaffold reference for pool word BE8A (segment 10, SEGMENT_REPRESENTATIVE) */
extern int far editBuf;  /* scaffold reference for pool word BE8E (segment 10, MAPSYM_SITE_NAME) */
extern int far pack_buf;  /* scaffold reference for pool word BE90 (segment 9, SEGMENT_REPRESENTATIVE) */
extern unsigned int far ncbHead;
extern unsigned int far ncbSegment[];
extern unsigned int far ncbOffset[];
extern unsigned int far ncbTail;
extern int far Scycle;  /* scaffold reference for pool word BE98 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far EditColumns;  /* scaffold reference for pool word BE9A (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far MiscStrs;  /* scaffold reference for pool word BE9C (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far LastQueenPlane;  /* scaffold reference for pool word BE9E (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far EditDragPnt;  /* scaffold reference for pool word BEA0 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Dx9;  /* scaffold reference for pool word BEA2 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far SMode;  /* scaffold reference for pool word BEA4 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far modeButtonState;  /* scaffold reference for pool word BEA6 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far CurRestPlane;  /* scaffold reference for pool word BEA8 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Dy9;  /* scaffold reference for pool word BEAA (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far TurnTab;  /* scaffold reference for pool word BEAC (segment 8, SEGMENT_REPRESENTATIVE) */

void far pool_stub_DoUserButton(void);
void far pool_stub_DoBookMark(void);
void far pool_stub_DoMouse(void);
void far pool_stub_DoMenuEntry(void);
void far pool_stub_AdjustWndMinMax(void);
void far pool_data_DoUserButton(void);
void far pool_data_DoBookMark(void);
void far pool_data_DoKeyDown(void);
void far pool_data_DoMouse(void);
void far pool_data_NetworkSend(void);
void far pool_data_UpdateWindows(void);
void far pool_data_MYTIMERFUNC(void);
void far pool_data_MAINWNDPROC(void);
void far pool_data_WINMAIN(void);
void interrupt far NetBIOSPost(unsigned int segment, unsigned int savedDS, unsigned int savedDI, unsigned int savedSI, unsigned int savedBP, unsigned int savedSP, unsigned int offset);
void far pool_stub_UpdateWindows(void);
void far pool_stub_MYTIMERFUNC(void);
void far SetUserButton(int object, int button);
void far ClearBookmarks(void);
void far DrawRibbonMessage(void);
int far HelpKeyDown(unsigned int window, int key);
void DoNextWindow(int window);
void far RedrawWindows(int window);
void far DoDebugWin(void);
void far LoadFancyCursor(void);
int far SetFancyCursor(int window, int button);
int far InitInstance(int hInstance, int cmdShow);
int far InitApplication(int hInstance);
void far PatchColorArrays(void);

int far NetworkSend(void);
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoUserButton)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoBookMark)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoMouse)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoMenuEntry)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_AdjustWndMinMax)
#pragma alloc_text(POOLSTUB_TEXT, pool_data_DoUserButton)
#pragma alloc_text(POOLSTUB_TEXT, pool_data_DoBookMark)
#pragma alloc_text(POOLSTUB_TEXT, pool_data_DoKeyDown)
#pragma alloc_text(POOLSTUB_TEXT, pool_data_DoMouse)
#pragma alloc_text(POOLSTUB_TEXT, pool_data_NetworkSend)
#pragma alloc_text(POOLSTUB_TEXT, pool_data_UpdateWindows)
#pragma alloc_text(POOLSTUB_TEXT, pool_data_MYTIMERFUNC)
#pragma alloc_text(POOLSTUB_TEXT, pool_data_MAINWNDPROC)
#pragma alloc_text(POOLSTUB_TEXT, pool_data_WINMAIN)
#pragma alloc_text(RUN10_TEXT, NetBIOSPost)
#pragma alloc_text(RUN11_TEXT, NetworkSend)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_UpdateWindows)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_MYTIMERFUNC)
#pragma alloc_text(RUN2_TEXT, SetUserButton)
#pragma alloc_text(RUN3_TEXT, ClearBookmarks, DrawRibbonMessage)
#pragma alloc_text(RUN4_TEXT, HelpKeyDown)
#pragma alloc_text(RUN5_TEXT, DoNextWindow)
#pragma alloc_text(RUN6_TEXT, RedrawWindows, DoDebugWin)
#pragma alloc_text(RUN7_TEXT, LoadFancyCursor, SetFancyCursor)
#pragma alloc_text(RUN8_TEXT, InitInstance, InitApplication, PatchColorArrays)

void far DoUserButtonUpdate(int button, int object)
{
    switch (button) {
    case 5:
        win_SetObjSelectedState(object, GamePaused);
        break;
    case 7:
        win_SetObjSelectedState(object, OptionStates[1]);
        break;
    case 9:
        win_SetObjSelectedState(object, OptionStates[2]);
        break;
    case 10:
        win_SetObjSelectedState(object, OptionStates[5]);
        break;
    case 11:
        win_SetObjSelectedState(object, OptionStates[0]);
        break;
    case 12:
        win_SetObjSelectedState(object, OptionStates[3]);
        break;
    case 13:
        win_SetObjSelectedState(object, OptionStates[4]);
        break;
    }
}

void far SetUserButton(int object, int button)
{
    struct WinButtonObject far *obj;

    win_SetButtonBitmaps(object, button + 0x3889, button + 0x3857);
    win_LockWin(object);
    obj = win_ObjAddr(object);
    switch (button) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 6:
    case 8:
    case 14:
    case 15:
        obj->flags1 &= ~8;
        obj->flags2 |= 8;
        win_SetObjSelectedState(object, 0);
        break;
    case 4:
        obj->flags1 |= 8;
        obj->flags2 &= ~8;
        win_SetObjSelectedState(object, showTrails);
        break;
    case 5:
        obj->flags1 |= 8;
        obj->flags2 &= ~8;
        win_SetObjSelectedState(object, GamePaused);
        break;
    case 7:
        obj->flags1 |= 8;
        obj->flags2 &= ~8;
        win_SetObjSelectedState(object, OptionStates[1]);
        break;
    case 9:
        obj->flags1 |= 8;
        obj->flags2 &= ~8;
        win_SetObjSelectedState(object, OptionStates[2]);
        break;
    case 10:
        obj->flags1 |= 8;
        obj->flags2 &= ~8;
        win_SetObjSelectedState(object, OptionStates[5]);
        break;
    case 11:
        obj->flags1 |= 8;
        obj->flags2 &= ~8;
        win_SetObjSelectedState(object, OptionStates[0]);
        break;
    case 12:
        obj->flags1 |= 8;
        obj->flags2 &= ~8;
        win_SetObjSelectedState(object, OptionStates[3]);
        break;
    case 13:
        obj->flags1 |= 8;
        obj->flags2 &= ~8;
        win_SetObjSelectedState(object, OptionStates[4]);
        break;
    }
    win_UnlockWin(object);
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DoUserButton.
 * It only reproduces the object's selector-pool allocation order for the
 * words BE74 BE76 BE78; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoUserButton(void)
{
    volatile int t;

    t = mapUserButton;
    t = match_position;
    t = Dx8;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DoBookMark.
 * It only reproduces the object's selector-pool allocation order for the
 * words BE7A BE7C BE7E; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoBookMark(void)
{
    volatile int t;

    t = *(int far *)bookMark;
    t = match_length;
    t = Dy8;
}

void far ClearBookmarks(void)
{
    int i;

    for (i = 0; i < 7; i++) {
        bookMark[i].object = -1;
        bookMark[i].plane = 0;
        bookMark[i].x = 0;
        bookMark[i].y = 0;
        bookMark[i].flags = 0;
        win_SetButtonBitmaps(0x2218 + i, 0x3899 + i, 0x3867 + i);
        win_SetObjSelectedState(0x2218 + i, 0);
        win_SetButtonBitmaps(0x2313 + i, 0x3899 + i, 0x3867 + i);
        win_SetObjSelectedState(0x2313 + i, 0);
    }
}

void far DrawRibbonMessage(void)
{
    MSClipStart(win_hwnd[34]);
    if (TickCount() > mapMessageRemoveTime) {
        editMessage = 0L;
        mapMessage = 0L;
        win_FillObjRect(0x221f, ConvColor(12));
    } else if (mapMessage != 0L) {
        font_SetFont(2);
        win_PrintfAtObj(0x221f, mapMessage);
        font_SetFont(0);
    } else {
        win_FillObjRect(0x221f, ConvColor(12));
    }
    MSClipEnd();
}

int far HelpKeyDown(unsigned int window, int key)
{
    if (key == 0x70) {
        if (GetKeyState(0x10) & 0x8000) {
            bHelp = !bHelp;
            if (bHelp)
                SetCursor(hHelpCursor);
            else
                SetCursor(GetClassWord(window, -12));
        } else
            WinHelp(rootWnd, helpFile, 3, 0L);
        return 1;
    }
    if (key == 0x1b) {
        if (bHelp) {
            bHelp = 0;
            SetCursor(GetClassWord(window, -12));
            return 1;
        }
    }
    if (key == 0x2e) {
        bHelp = !bHelp;
        if (bHelp)
            SetCursor(hHelpCursor);
        else
            SetCursor(GetClassWord(window, -12));
    }
    return 0;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DoMouse.
 * It only reproduces the object's selector-pool allocation order for the
 * words BE88; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoMouse(void)
{
    volatile int t;

    t = yardUserButton;
}

void DoNextWindow(int window)
{
    int nextWindow;

    if (window == 0)
        return;

    while ((nextWindow = GetNextWindow(window, 2)) != 0)
        window = nextWindow;

    while (GetWindow(window, 4) != 0 || !IsWindowVisible(window))
        window = GetNextWindow(window, 3);

    BringWindowToTop(window);
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DoMenuEntry.
 * It only reproduces the object's selector-pool allocation order for the
 * words BE8A BE8C; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoMenuEntry(void)
{
    volatile int t;

    t = paletteFlag;
    t = (int)CurGameType;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _AdjustWndMinMax.
 * It only reproduces the object's selector-pool allocation order for the
 * words BE8E; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_AdjustWndMinMax(void)
{
    volatile int t;

    t = editBuf;
}

void far RedrawWindows(int window)
{
    WindowProc procedure;
    int procedureSegment;

    procedure = MakeProcInstance((WindowProc)MyEnumFunc, hInst);
    EnumChildWindows(rootWnd, procedure, (unsigned long)(unsigned int)window);
    FreeProcInstance(procedure);
    if (ribbonBarWnd != 0 && window != ribbonBarWnd)
        InvalidateRect(ribbonBarWnd, (void far *)0, 0);
}

void far DoDebugWin(void)
{
    if (lastTick != -1) {
        frames++;
        total += GetTickCount() - lastTick;
        if (frames % 5 == 0) {
            MSClipStart(win_hwnd[28]);
            font_SetFont(2);
            win_PrintfAtObj(0x1c03, debugFormat, total / frames, 60000L / (total / frames));
            font_SetFont(0);
            MSClipEnd();
        }
    }
    lastTick = GetTickCount();
}

void interrupt far NetBIOSPost(unsigned int segment,
                               unsigned int savedDS,
                               unsigned int savedDI,
                               unsigned int savedSI,
                               unsigned int savedBP,
                               unsigned int savedSP,
                               unsigned int offset)
{
    unsigned int slot;

    slot = ncbHead;
    ncbSegment[slot] = segment;
    ncbOffset[slot] = offset;
    ++ncbHead;
    if (ncbHead == 10)
        ncbHead = 0;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _ProcessPost.
 * It only reproduces the object's selector-pool allocation order for the
 * words BE96; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
int far ProcessPost(char session)
{
    struct ProcessPostWork work;
    int returnStatus = 0;

    work.localNCB = (struct NCB far *)&work.completed;
    work.sendResult = 0;
    movedata(ncbSegment[ncbTail], ncbOffset[ncbTail], POST_SEG(work.localNCB),
             POST_OFF(work.localNCB), 0x40);
    ncbTail++;
    if (ncbTail == 10)
        ncbTail = 0;

    switch (work.completed.command) {
    case -111:
        switch (work.completed.commandComplete) {
        case 0:
            break;
        default:
            NbFinalStatus((struct NetbiosControlBlock far *)&work.completed);
            NbHangUp(work.completed.lsn);
            returnStatus = 1;
            goto processPostExit;
        }

        NbSend((unsigned char far *)&MapPlane, 2, work.completed.lsn);
        switch (MapPlane) {
        case 0:
        case 1:
            work.length = 0x1000;
            NbReceive(work.completed.lsn, MapA, &work.length);
            NbSend((unsigned char far *)&work.sendResult, 2, work.completed.lsn);
            work.length = 0x1000;
            NbReceive(work.completed.lsn,
                      (unsigned char far *)((unsigned long)MapA + 0x1000L),
                      &work.length);
            NbSend((unsigned char far *)&work.sendResult, 2, work.completed.lsn);
            work.length = 0x1000;
            NbReceive(work.completed.lsn, LifeA, &work.length);
            NbSend((unsigned char far *)&work.sendResult, 2, work.completed.lsn);
            work.length = 0x1000;
            NbReceive(work.completed.lsn,
                      (unsigned char far *)((unsigned long)LifeA + 0x1000L),
                      &work.length);
            break;
        case 2:
            work.length = 0x1000;
            NbReceive(work.completed.lsn, MapB, &work.length);
            NbSend((unsigned char far *)&work.sendResult, 2, work.completed.lsn);
            work.length = 0x1000;
            NbReceive(work.completed.lsn, LifeB, &work.length);
            break;
        case 3:
            work.length = 0x1000;
            NbReceive(work.completed.lsn, MapR, &work.length);
            NbSend((unsigned char far *)&work.sendResult, 2, work.completed.lsn);
            work.length = 0x1000;
            NbReceive(work.completed.lsn, LifeR, &work.length);
            break;
        }

        NbSend((unsigned char far *)&work.sendResult, 2, work.completed.lsn);
        work.length = DataBlockEnd - ForSaleState;
        NbReceive(work.completed.lsn, (unsigned char far *)ForSaleState,
                  &work.length);
        NbHangUp(work.completed.lsn);
        NbPostListen(processPostClientName, processPostServerName, 0x3c,
                     0, (void far *)NetBIOSPost);
        goto processPostExit;

    case -106:
        switch (work.completed.commandComplete) {
        case 10:
            processPostState = 1;
            goto processPostExit;
        case 0:
        case 5:
            NbPostReceiveAny((unsigned char)session,
                             (unsigned char far *)theNetBiosBuffer,
                             0x2000, (unsigned long)NetBIOSPost);
            goto processPostExit;
        default:
            NbFinalStatus((struct NetbiosControlBlock far *)&work.completed);
            returnStatus = 1;
            goto processPostExit;
        }
    }

processPostExit:
    return returnStatus;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _UpdateWindows.
 * It only reproduces the object's selector-pool allocation order for the
 * words BE98 BE9A; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_UpdateWindows(void)
{
    volatile int t;

    t = Scycle;
    t = EditColumns;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member MYTIMERFUNC.
 * It only reproduces the object's selector-pool allocation order for the
 * words BE9C BE9E BEA0 BEA2 BEA4 BEA6 BEA8 BEAA BEAC; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_MYTIMERFUNC(void)
{
    volatile int t;

    t = MiscStrs;
    t = LastQueenPlane;
    t = EditDragPnt;
    t = Dx9;
    t = SMode;
    t = modeButtonState;
    t = CurRestPlane;
    t = Dy9;
    t = TurnTab;
}

/* SCAFFOLD, not recovered source: unclaimed body literals before _LoadFancyCursor (DGROUP 02C3-032A), unclaimed members' body literals. */

#define hInst (*(unsigned int near *)&hInst)  /* shape view of the unit declaration for this member only */
void far LoadFancyCursor(void)
{
    magCursor = LoadCursor(hInst, cursorMagResource);
    rockCursor = LoadCursor(hInst, cursorRockResource);
    digCursor = LoadCursor(hInst, cursorDigResource);
    antCursor = LoadCursor(hInst, cursorAntResource);
    foodCursor = LoadCursor(hInst, cursorFoodResource);
    dropCursor = LoadCursor(hInst, cursorDropResource);
    sprayCursor = LoadCursor(hInst, cursorSprayResource);
}
/* hInst cleanup omitted: no later references in this unit */

int far SetFancyCursor(int window, int button)
{
    if ((window == win_hwnd[0] && win_IsWinInFront(0)) ||
        (window == win_hwnd[1] && win_IsWinInFront(0x100) && (GetAsyncKeyState(0x10) & 0x8000))) {
        if (button == 1 && CurGameType == 3) {
            switch (CurExpTool) {
            case 0:
                SetCursor(magCursor);
                break;
            case 1:
                SetCursor(rockCursor);
                break;
            case 2:
                SetCursor(digCursor);
                break;
            case 3:
                SetCursor(antCursor);
                break;
            case 4:
                SetCursor(foodCursor);
                break;
            case 5:
                SetCursor(dropCursor);
                break;
            case 6:
                SetCursor(sprayCursor);
                break;
            }
            return 1;
        }
    }
    return 0;
}

/* SCAFFOLD, not recovered source: body literals between _LoadFancyCursor and _InitInstance (DGROUP 0375-0626), unclaimed members' body literals. */

int far InitInstance(int hInstance, int cmdShow)
{
    struct Rect rect1, rect2;
    int hwnd;

    hInst = hInstance;

    hwnd = CreateWindow(initInstanceMainTitle, initInstanceMainClass, 0x02cf0000L,
        GetSystemMetrics(0) / 100,
        GetSystemMetrics(1) / 100,
        (int)((long)GetSystemMetrics(0) * 98 / 100),
        (int)((long)GetSystemMetrics(1) * 90 / 100) - GetSystemMetrics(12),
        0, 0, hInstance, 0);

    if (hwnd == 0)
        return 0;

    SetProp(hwnd, initInstancePropertyIndex, -1);
    mainRootWnd = hwnd;
    ShowWindow(hwnd, cmdShow | 3);
    UpdateWindow(hwnd);

    GetClientRect(hwnd, &rect1);
    screenWidth = rect1.right;
    screenHeight = rect1.bottom;

    GetClientRect(mainRootWnd, &rect2);

    ribbonBarWnd = CreateWindow(initInstanceRibbonClass, initInstanceRibbonTitle, 0x52000000L,
        0, 0, rect2.right, 0,
        mainRootWnd, 0, hInstance, 0);

    rootWnd = CreateWindow(initInstanceRootClass, initInstanceRootTitle, 0x52000000L,
        0, 0, rect2.right, rect2.bottom,
        mainRootWnd, 0, hInstance, 0);

    UpdateWindow(ribbonBarWnd);
    UpdateWindow(rootWnd);

    return 1;
}

int far InitApplication(int hInstance)
{
    struct WndClass wcRoot, wcGeneric, wcRibbon;
    char spare[26];

    wcRoot.style = 0;
    wcRoot.lpfnWndProc = MainWndProc;
    wcRoot.cbClsExtra = 0;
    wcRoot.cbWndExtra = 0;
    wcRoot.hInstance = hInstance;
    wcRoot.hIcon = LoadIcon(hInstance, initApplicationIcon);
    wcRoot.hCursor = LoadCursor(0, MAKEINTRESOURCE(0x7f00));
    wcRoot.hbrBackground = 0xd;
    wcRoot.lpszMenuName = 0;
    wcRoot.lpszClassName = initApplicationRootClass;

    wcGeneric.style = 0x1008;
    wcGeneric.lpfnWndProc = MainWndProc;
    wcGeneric.cbClsExtra = 0;
    wcGeneric.cbWndExtra = 0;
    wcGeneric.hInstance = hInstance;
    wcGeneric.hIcon = LoadIcon(0, MAKEINTRESOURCE(0x7f00));
    wcGeneric.hCursor = LoadCursor(0, MAKEINTRESOURCE(0x7f00));
    wcGeneric.hbrBackground = 6;
    wcGeneric.lpszMenuName = 0;
    wcGeneric.lpszClassName = initApplicationGenericClass;

    wcRibbon.style = 0x1008;
    wcRibbon.lpfnWndProc = MainWndProc;
    wcRibbon.cbClsExtra = 0;
    wcRibbon.cbWndExtra = 0;
    wcRibbon.hInstance = hInstance;
    wcRibbon.hIcon = LoadIcon(0, MAKEINTRESOURCE(0x7f00));
    wcRibbon.hCursor = LoadCursor(0, MAKEINTRESOURCE(0x7f00));
    wcRibbon.hbrBackground = GetStockObject(1);
    wcRibbon.lpszMenuName = 0;
    wcRibbon.lpszClassName = initApplicationRibbonClass;

    return RegisterClass(&wcRibbon) | RegisterClass(&wcGeneric) | RegisterClass(&wcRoot);
}

void far PatchColorArrays(void)
{
    unsigned char table[16] = {15, 11, 2, 9, 14, 5, 4, 12, 2, 10, 7, 3, 6, 8, 7, 0};
    int i;

    for (i = 0; i < 144; i++)
        CTab[i] = table[CTab[i]];
    for (i = 0; i < 208; i++)
        HTab[i] = table[HTab[i]];
    for (i = 0; i < 32; i++)
        LTab[i] = table[LTab[i]];
    for (i = 0; i < 24; i++) {
        CTabB[i] = table[CTabB[i]];
        CTabR[i] = table[CTabR[i]];
    }
    for (i = 0; i < 16; i++)
        PherColorTab[i] = table[PherColorTab[i]];
}



/* POOLSTUB_TEXT data owners; code is scaffold, initializers retain DATA bytes. */
void far pool_data_DoUserButton(void)
{
    char near * volatile literal;
    volatile int wordValue;
    volatile long longValue;
    literal = privateDataPrefix;
    literal = buttonSpeedSlow;
    literal = buttonSpeedNormal;
    literal = buttonSpeedFast;
    literal = buttonSpeedUltra;
}

void far pool_data_DoBookMark(void)
{
    char near * volatile literal;
    volatile int wordValue;
    volatile long longValue;
    literal = bookmarkPlaced;
    literal = bookmarkNotPlaced;
}

void far pool_data_DoKeyDown(void)
{
    char near * volatile literal;
    volatile int wordValue;
    volatile long longValue;
    literal = keyPropertyIndex;
    literal = keyFlashStart;
    literal = keyFlashAlmost;
    literal = keyFlashDone;
    wordValue = keyCheatPosition;
    wordValue = keyCheatLength;
    literal = (char near *)doKeyDownCheatBuffer;
}

void far pool_data_DoMouse(void)
{
    char near * volatile literal;
    volatile int wordValue;
    volatile long longValue;
    literal = mousePropertyIndex;
    literal = mouseFlashStart;
    literal = mouseFlashAlmost;
    literal = mouseFlashDone;
}

void far pool_data_NetworkSend(void)
{
    char near * volatile literal;
    volatile int wordValue;
    volatile long longValue;
    literal = networkClientName;
    literal = networkServerName;
}

void far pool_data_UpdateWindows(void)
{
    char near * volatile literal;
    volatile int wordValue;
    volatile long longValue;
    longValue = updateStamp;
    wordValue = yardDrawPending;
    wordValue = editDrawPending;
}

void far pool_data_MYTIMERFUNC(void)
{
    char near * volatile literal;
    volatile int wordValue;
    volatile long longValue;
    literal = timerIconNormal;
    literal = timerIconPaused;
    literal = timerIconBlackWin;
    literal = timerIconBlackWon;
    literal = timerIconRedWin;
    literal = timerIconRedLost;
    literal = timerAntFormat;
    wordValue = timerCallCount;
    wordValue = timerBusy;
    wordValue = timerState02F2;
    wordValue = timerState02F4;
}

void far pool_data_MAINWNDPROC(void)
{
    char near * volatile literal;
    volatile int wordValue;
    volatile long longValue;
    literal = mainWndTitle;
    literal = mainWndPropertyIndex0;
    literal = capturePrompt;
    literal = captureTitle0;
    literal = captureTitle1;
    literal = noCaptureMessage;
    literal = ribbonMessage0;
    literal = ribbonMessage1;
    literal = mainWndPropertyIndex1;
    literal = mainWndPropertyIndex2;
    literal = mainWndPropertyIndex3;
    literal = mainWndPropertyIndex4;
    literal = mainWndPropertyIndex5;
    literal = wmSizeFormat;
    literal = activateStart;
    literal = mainWndPropertyIndex6;
    literal = activateCapture;
    literal = activateReady;
    literal = deactivateStart;
    literal = deactivateRelease;
    literal = deactivateReady;
    literal = paletteChangedCalled;
    literal = paletteChangedCalling;
    literal = paletteChangedSame;
    literal = paletteChangedInvalidate;
    literal = memoryLowMessage;
    wordValue = mainWndState0376;
    wordValue = mainWndState0378;
    wordValue = mainWndState037A;
    wordValue = mainWndMessageMap[0];
    wordValue = mainWndState038C;
}


void far pool_data_WINMAIN(void)
{
    char near * volatile literal;
    volatile int wordValue;
    volatile long longValue;
    literal = winMainClassName;
    literal = notInstalledPattern;
    literal = notInstalledMessage;
    literal = winMainPropertyIndex;
    literal = optionSound;
    literal = optionAutotrack;
    literal = appSection0;
    literal = optionMusic;
    literal = appSection1;
    literal = optionEffects;
    literal = appSection2;
    literal = optionEvents;
    literal = appSection3;
    literal = optionMessages;
    literal = appSection4;
    literal = optionSilly;
    literal = appSection5;
    literal = cancelledMessage;
    literal = mapButtonProfile;
    literal = appSection6;
    literal = yardButtonProfile;
    literal = appSection7;
    literal = acceleratorResource;
    literal = releasingCaptureMessage;
    literal = profileOne0;
    literal = profileZero0;
    literal = optionAutotrackAgain;
    literal = appSection8;
    literal = profileOne1;
    literal = profileZero1;
    literal = optionMusicAgain;
    literal = appSection9;
    literal = profileOne2;
    literal = profileZero2;
    literal = optionEffectsAgain;
    literal = appSection10;
    literal = profileOne3;
    literal = profileZero3;
    literal = optionEventsAgain;
    literal = appSection11;
    literal = profileOne4;
    literal = profileZero4;
    literal = optionMessagesAgain;
    literal = appSection12;
    literal = profileOne5;
    literal = profileZero5;
    literal = optionSillyAgain;
    literal = appSection13;
    literal = mapButtonProfileAgain;
    literal = integerFormat0;
    literal = appSection14;
    literal = yardButtonProfileAgain;
    literal = integerFormat1;
    literal = appSection15;
}


extern int far NbCall(char far *name2, char far *name1, int len2, int len1);
extern unsigned int far NbReceive(unsigned char session,
                                  unsigned char far *buffer,
                                  unsigned int far *length);
extern int far NbSend(unsigned char far *buffer, int length, char session);
extern int far NbHangUp(char session);

extern unsigned char near MapA[128][64];
extern unsigned char near MapB[128][64];
extern unsigned char near MapR[128][64];
extern unsigned char near LifeA[128][64];
extern unsigned char near LifeB[128][64];
extern unsigned char near LifeR[128][64];
extern unsigned char near ForSaleState[];
extern unsigned char near DataBlockEnd[];

int far NetworkSend(void)
{
    char retcode;
    int cmd;
    int result;
    int firstResult;

    retcode = NbCall(networkServerName, networkClientName, 0x1e, 0x1e);
    if (retcode != 0) {
    cmd = 2;
    NbReceive(retcode, &firstResult, &cmd);
    switch (firstResult) {
    case 0:
    case 1:
        goto send_01;
    case 2:
        goto send_2;
    case 3:
        goto send_3;
    default:
        goto close_round;
    }
    goto close_round;

send_01:
    NbSend(MapA, 0x1000, retcode);
    cmd = 2;
    NbReceive(retcode, &result, &cmd);
    NbSend((unsigned char far *)((unsigned long)MapA + 0x1000L), 0x1000, retcode);
    cmd = 2;
    NbReceive(retcode, &result, &cmd);
    NbSend((unsigned char far *)((unsigned long)LifeA + 0x1000L), 0x1000, retcode);
    cmd = 2;
    NbReceive(retcode, &result, &cmd);
    NbSend(LifeA, 0x1000, retcode);
    goto close_round;

send_2:
    NbSend(MapB, 0x1000, retcode);
    cmd = 2;
    NbReceive(retcode, &result, &cmd);
    NbSend(LifeB, 0x1000, retcode);
    goto close_round;

send_3:
    NbSend(MapR, 0x1000, retcode);
    cmd = 2;
    NbReceive(retcode, &result, &cmd);
    NbSend(LifeR, 0x1000, retcode);

close_round:
    cmd = 2;
    NbReceive(retcode, &result, &cmd);
    NbSend(ForSaleState, DataBlockEnd - ForSaleState, retcode);
    return NbHangUp(retcode);
    }
}
