/* Candidate translation unit simant_01B6_DoUserButtonUpdate_12_scaffold_split: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _DoUserButtonUpdate, _SetUserButton, _ClearBookmarks, _DrawRibbonMessage, _HelpKeyDown, _DoNextWindow, _RedrawWindows, _DoDebugWin, _LoadFancyCursor, _SetFancyCursor, _InitInstance, _PatchColorArrays
 * SCAFFOLDED: unclaimed members _DoUserButton, _DoBookMark, _DoMouse, _DoMenuEntry, _AdjustWndMinMax, _NetBIOSPost, _ProcessPost, _UpdateWindows are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

extern int far GamePaused;
extern int far OptionStates[];
extern void far win_SetObjSelectedState(int object, int selected);
struct WinButtonObject {
    unsigned char reserved1[0x24];
    unsigned char flags1;
    unsigned char flags2;
};
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
extern void far pascal InvalidateRect(int window, void far *rect,
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


#define iconNormal timerIconNormal
#define iconPaused timerIconPaused
#define iconWon timerIconBlackWin
#define iconLost timerIconRedWin
#define timerFormat timerAntFormat
void far pascal __export MYTIMERFUNC(int window, int message, int timerId, unsigned int lowTime, unsigned int highTime);
/*
 * MYTIMERFUNC services the main window timer: refresh the icon for paused or
 * completed play, update simulation/network/audio state, invalidate the
 * client when needed, and drain the timer-message queue.  The private timer
 * words are kept as natural counters; their original data ownership is still
 * provisional.
 */
struct WinRect { int left; int top; int right; int bottom; };
struct MSG {
    int hwnd;
    unsigned int message;
    unsigned int wParam;
    long lParam;
    unsigned long time;
    int pt_x;
    int pt_y;
};

extern int far GamePaused;
extern int far IsGameOver;
extern int far BlackWon;
extern unsigned long far gameCycles;
extern int far SimAntClientFlag;
extern int far SimAntServerFlag;
extern int far SimAntClientNum;
extern int far MeMoveMe;
extern int far CurGameTool;
extern int far GameSpeed;
extern int far SpeedDelayVals[];
extern int far ncbHead;
extern int far ncbTail;
extern int far activeAppFlag;



extern int far pascal IsIconic(int window);
extern unsigned int far pascal LoadIcon(unsigned int instance, char far *name);

extern unsigned int far pascal GetClassWord(unsigned int window, int index);

extern unsigned int far pascal SetClassWord(int window, int index,
                                             unsigned int value);
extern void far pascal InvalidateRect(int window, void far *rect,
                                      unsigned flags);

extern int far pascal PeekMessage(struct MSG far *message, int window,
                                  unsigned int first, unsigned int last,
                                  unsigned int remove);
extern int far pascal GetAsyncKeyState(int key);
extern int far SRand1(int range);
extern int far sprintf(char far *buffer, char far *format, ...);
extern void far DoAntSim(void);
extern void myServiceSong(void);

extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern int far win_IsWinOpen(int window);
extern void far win_FillObjRect(int object, int color);
extern void far UpdateYardMessage(void);
extern void near ProcessPost(int state);
extern int far NetworkSend(void);

extern void near UpdateWindows(void);

/* One byte-packed representation of private DGROUP _DATA 014A..0858; strings start at 014B.
 * Entries follow the target addresses below; names are typed views into this run.
 */
static char near privateDGROUP[0x070f] =
    "\000" /* 014A: alignment byte before private run */
    "Game speed now slow.\000" /* 014B: buttonSpeedSlow */
    "Game speed now normal.\000" /* 0160: buttonSpeedNormal */
    "Game speed now fast.\000" /* 0177: buttonSpeedFast */
    "Game speed now ultra.\000" /* 018C: buttonSpeedUltra */
    "Bookmark has been placed.\000" /* 01A2: bookmarkPlaced */
    "Bookmark has not been placed.\000" /* 01BC: bookmarkNotPlaced */
    "\000\000" /* 01DA: keyCheatPosition */
    "\000\000" /* 01DC: keyCheatLength */
    "INDEX\000" /* 01DE: keyPropertyIndex */
    "DoKeyDown: Flash(start)(%d)\n\000" /* 01E4: keyFlashStart */
    "DoKeyDown: Flash(almost done)(%d)\n\000" /* 0201: keyFlashAlmost */
    "DoKeyDown: Flash(done)(%d)\n\000" /* 0224: keyFlashDone */
    "INDEX\000" /* 0240: mousePropertyIndex */
    "DoMouse: Flash(start)(%d)\n\000" /* 0246: mouseFlashStart */
    "DoMouse: Flash(almost done)(%d)\n\000" /* 0261: mouseFlashAlmost */
    "DoMouse: Flash(done)(%d)\n\000" /* 0282: mouseFlashDone */
    "\377\377\377\377" /* 029C: lastTick */
    "\000\000\000\000" /* 02A0: frames */
    "\000\000\000\000" /* 02A4: total */
    "Ave Length: %lu Speed: %lu\000\000" /* 02A8: debugFormat */
    "\001\000" /* 02C4: processPostState */
    "SERVANT\000" /* 02C6: processPostServerName */
    "CLIEANT\000" /* 02CE: processPostClientName */
    "CLIEANT\000" /* 02D6: networkClientName */
    "SERVANT\000" /* 02DE: networkServerName */
    "\000\000\000\000" /* 02E6: updateStamp */
    "\000\000" /* 02EA: yardDrawPending */
    "\000\000" /* 02EC: editDrawPending */
    "\000\000" /* 02EE: timerCallCount */
    "\000\000" /* 02F0: timerBusy */
    "\000\000" /* 02F2: timerState02F2 */
    "\000\000" /* 02F4: timerState02F4 */
    "SimAnt\000" /* 02F6: timerIconNormal */
    "SimAnt\000" /* 02FD: timerIconPaused */
    "BlackWin\000" /* 0304: timerIconBlackWin */
    "BlackWin\000" /* 030D: timerIconBlackWon */
    "RedWin\000" /* 0316: timerIconRedWin */
    "RedWin\000" /* 031D: timerIconRedLost */
    "Ant%d\000" /* 0324: timerAntFormat */
    "MagCursor\000" /* 032A: cursorMagResource */
    "RockCursor\000" /* 0334: cursorRockResource */
    "DigCursor\000" /* 033F: cursorDigResource */
    "AntCursor\000" /* 0349: cursorAntResource */
    "FoodCursor\000" /* 0353: cursorFoodResource */
    "DropCursor\000" /* 035E: cursorDropResource */
    "SprayCursor\000\000" /* 0369: cursorSprayResource */
    "\000\000" /* 0376: mainWndState0376 */
    "\000\000" /* 0378: mainWndState0378 */
    "\000\000" /* 037A: mainWndState037A */
    "\377\377\000\014\000\017\000\020\000\021\000\r\000\016\377\377" /* 037C: mainWndMessageMap */
    "\000\000" /* 038C: mainWndState038C */
    "SimAnt For Windows\000" /* 038E: mainWndTitle */
    "INDEX\000" /* 03A1: mainWndPropertyIndex0 */
    "Window %#x has the capture.\nDo capture debug?\n\000" /* 03A7: capturePrompt */
    "SimAnt Capture\000" /* 03D6: captureTitle0 */
    "SimAnt Capture\000" /* 03E5: captureTitle1 */
    "No windows has the capture.\000" /* 03F4: noCaptureMessage */
    "This is the ribbon bar.\000" /* 0410: ribbonMessage0 */
    "This is the ribbon bar.\000" /* 0428: ribbonMessage1 */
    "INDEX\000" /* 0440: mainWndPropertyIndex1 */
    "INDEX\000" /* 0446: mainWndPropertyIndex2 */
    "INDEX\000" /* 044C: mainWndPropertyIndex3 */
    "INDEX\000" /* 0452: mainWndPropertyIndex4 */
    "INDEX\000" /* 0458: mainWndPropertyIndex5 */
    "WM_SIZE: newWidth(%d) newHeight(%d) editWidth(%d) editHeight(%d) rectWidth(%d) rectHeight(%d)\n\000" /* 045E: wmSizeFormat */
    "ActivateApplication(START)\n\000" /* 04BD: activateStart */
    "INDEX\000" /* 04D9: mainWndPropertyIndex6 */
    "ActivateApplication(CAPTURE)(%#x)\n\000" /* 04DF: activateCapture */
    "ActivateApplication(READY)\n\000" /* 0502: activateReady */
    "DeActivateApplication(START)\n\000" /* 051E: deactivateStart */
    "DeActivateApplication(RELEASECAPTURE)\n\000" /* 053C: deactivateRelease */
    "DeActivateApplication(READY)\n\000" /* 0563: deactivateReady */
    "WM_PALETTECHANGED(called)(%s)\n\000" /* 0581: paletteChangedCalled */
    "WM_PALETTECHANGED(calling)(%s)\n\000" /* 05A0: paletteChangedCalling */
    "WM_PALETTECHANGED(same window)\n\000" /* 05C0: paletteChangedSame */
    "WM_PALETTECHANGED/WM_QUERYNEWPALETTE(Invalidate)\n\000" /* 05E0: paletteChangedInvalidate */
    "Memory is very low.\000" /* 0612: memoryLowMessage */
    "SimAnt\000" /* 0626: initInstanceMainClass */
    "AntRoot\000" /* 062D: initInstanceMainTitle */
    "INDEX\000" /* 0635: initInstancePropertyIndex */
    "SimAnt Ribbon Bar\000" /* 063B: initInstanceRibbonTitle */
    "RibbonWindow\000" /* 064D: initInstanceRibbonClass */
    "SimAnt Root Window\000" /* 065A: initInstanceRootTitle */
    "AntRoot\000" /* 066D: initInstanceRootClass */
    "SimAnt\000" /* 0675: initApplicationIcon */
    "AntRoot\000" /* 067C: initApplicationRootClass */
    "GenericWindow\000" /* 0684: initApplicationGenericClass */
    "RibbonWindow\000" /* 0692: initApplicationRibbonClass */
    "AntRoot\000" /* 069F: winMainClassName */
    "YYYYYYYYYY\000" /* 06A7: notInstalledPattern */
    "Program not installed correctly.\nPlease re-install.\000" /* 06B2: notInstalledMessage */
    "INDEX\000" /* 06E6: winMainPropertyIndex */
    "sound\000" /* 06EC: optionSound */
    "autotrack\000" /* 06F2: optionAutotrack */
    "SimAnt\000" /* 06FC: appSection0 */
    "music\000" /* 0703: optionMusic */
    "SimAnt\000" /* 0709: appSection1 */
    "effects\000" /* 0710: optionEffects */
    "SimAnt\000" /* 0718: appSection2 */
    "events\000" /* 071F: optionEvents */
    "SimAnt\000" /* 0726: appSection3 */
    "messages\000" /* 072D: optionMessages */
    "SimAnt\000" /* 0736: appSection4 */
    "silly\000" /* 073D: optionSilly */
    "SimAnt\000" /* 0743: appSection5 */
    "SimAnt cancelled.\000" /* 074A: cancelledMessage */
    "mapuserbutton%d\000" /* 075C: mapButtonProfile */
    "SimAnt\000" /* 076C: appSection6 */
    "yarduserbutton%d\000" /* 0773: yardButtonProfile */
    "SimAnt\000" /* 0784: appSection7 */
    "AcceleratorTable\000" /* 078B: acceleratorResource */
    "ReleasingCapture(quit)\n\000" /* 079C: releasingCaptureMessage */
    "1\000" /* 07B4: profileOne0 */
    "0\000" /* 07B6: profileZero0 */
    "autotrack\000" /* 07B8: optionAutotrackAgain */
    "SimAnt\000" /* 07C2: appSection8 */
    "1\000" /* 07C9: profileOne1 */
    "0\000" /* 07CB: profileZero1 */
    "music\000" /* 07CD: optionMusicAgain */
    "SimAnt\000" /* 07D3: appSection9 */
    "1\000" /* 07DA: profileOne2 */
    "0\000" /* 07DC: profileZero2 */
    "effects\000" /* 07DE: optionEffectsAgain */
    "SimAnt\000" /* 07E6: appSection10 */
    "1\000" /* 07ED: profileOne3 */
    "0\000" /* 07EF: profileZero3 */
    "events\000" /* 07F1: optionEventsAgain */
    "SimAnt\000" /* 07F8: appSection11 */
    "1\000" /* 07FF: profileOne4 */
    "0\000" /* 0801: profileZero4 */
    "messages\000" /* 0803: optionMessagesAgain */
    "SimAnt\000" /* 080C: appSection12 */
    "1\000" /* 0813: profileOne5 */
    "0\000" /* 0815: profileZero5 */
    "silly\000" /* 0817: optionSillyAgain */
    "SimAnt\000" /* 081D: appSection13 */
    "mapuserbutton%d\000" /* 0824: mapButtonProfileAgain */
    "%d\000" /* 0834: integerFormat0 */
    "SimAnt\000" /* 0837: appSection14 */
    "yarduserbutton%d\000" /* 083E: yardButtonProfileAgain */
    "%d\000" /* 084F: integerFormat1 */
    "SimAnt" /* 0852: appSection15 */;

#define buttonSpeedSlow (privateDGROUP + 0x001)
#define buttonSpeedNormal (privateDGROUP + 0x016)
#define buttonSpeedFast (privateDGROUP + 0x02d)
#define buttonSpeedUltra (privateDGROUP + 0x042)
#define bookmarkPlaced (privateDGROUP + 0x058)
#define bookmarkNotPlaced (privateDGROUP + 0x072)
#define keyCheatPosition (*( unsigned int near *)(privateDGROUP + 0x090))
#define keyCheatLength (*( unsigned int near *)(privateDGROUP + 0x092))
#define keyPropertyIndex (privateDGROUP + 0x094)
#define keyFlashStart (privateDGROUP + 0x09a)
#define keyFlashAlmost (privateDGROUP + 0x0b7)
#define keyFlashDone (privateDGROUP + 0x0da)
#define mousePropertyIndex (privateDGROUP + 0x0f6)
#define mouseFlashStart (privateDGROUP + 0x0fc)
#define mouseFlashAlmost (privateDGROUP + 0x117)
#define mouseFlashDone (privateDGROUP + 0x138)
#define lastTick (*( long near *)(privateDGROUP + 0x152))
#define frames (*( long near *)(privateDGROUP + 0x156))
#define total (*( long near *)(privateDGROUP + 0x15a))
#define debugFormat (privateDGROUP + 0x15e)
#define processPostState (*( int near *)(privateDGROUP + 0x17a))
#define processPostServerName (privateDGROUP + 0x17c)
#define processPostClientName (privateDGROUP + 0x184)
#define networkClientName (privateDGROUP + 0x18c)
#define networkServerName (privateDGROUP + 0x194)
#define updateStamp (*( long near *)(privateDGROUP + 0x19c))
#define yardDrawPending (*( int near *)(privateDGROUP + 0x1a0))
#define editDrawPending (*( int near *)(privateDGROUP + 0x1a2))
#define timerCallCount (*( int near *)(privateDGROUP + 0x1a4))
#define timerBusy (*( unsigned long near *)(privateDGROUP + 0x1a6))
#define timerState02F2 (*( int near *)(privateDGROUP + 0x1a8))
#define timerState02F4 (*( int near *)(privateDGROUP + 0x1aa))
#define timerIconNormal (privateDGROUP + 0x1ac)
#define timerIconPaused (privateDGROUP + 0x1b3)
#define timerIconBlackWin (privateDGROUP + 0x1ba)
#define timerIconBlackWon (privateDGROUP + 0x1c3)
#define timerIconRedWin (privateDGROUP + 0x1cc)
#define timerIconRedLost (privateDGROUP + 0x1d3)
#define timerAntFormat (privateDGROUP + 0x1da)
#define cursorMagResource (privateDGROUP + 0x1e0)
#define cursorRockResource (privateDGROUP + 0x1ea)
#define cursorDigResource (privateDGROUP + 0x1f5)
#define cursorAntResource (privateDGROUP + 0x1ff)
#define cursorFoodResource (privateDGROUP + 0x209)
#define cursorDropResource (privateDGROUP + 0x214)
#define cursorSprayResource (privateDGROUP + 0x21f)
#define mainWndState0376 (*( int near *)(privateDGROUP + 0x22c))
#define mainWndState0378 (*( int near *)(privateDGROUP + 0x22e))
#define mainWndState037A (*( int near *)(privateDGROUP + 0x230))
#define mainWndMessageMap ((int near *)(privateDGROUP + 0x232))
#define mainWndState038C (*( int near *)(privateDGROUP + 0x242))
#define mainWndTitle (privateDGROUP + 0x244)
#define mainWndPropertyIndex0 (privateDGROUP + 0x257)
#define capturePrompt (privateDGROUP + 0x25d)
#define captureTitle0 (privateDGROUP + 0x28c)
#define captureTitle1 (privateDGROUP + 0x29b)
#define noCaptureMessage (privateDGROUP + 0x2aa)
#define ribbonMessage0 (privateDGROUP + 0x2c6)
#define ribbonMessage1 (privateDGROUP + 0x2de)
#define mainWndPropertyIndex1 (privateDGROUP + 0x2f6)
#define mainWndPropertyIndex2 (privateDGROUP + 0x2fc)
#define mainWndPropertyIndex3 (privateDGROUP + 0x302)
#define mainWndPropertyIndex4 (privateDGROUP + 0x308)
#define mainWndPropertyIndex5 (privateDGROUP + 0x30e)
#define wmSizeFormat (privateDGROUP + 0x314)
#define activateStart (privateDGROUP + 0x373)
#define mainWndPropertyIndex6 (privateDGROUP + 0x38f)
#define activateCapture (privateDGROUP + 0x395)
#define activateReady (privateDGROUP + 0x3b8)
#define deactivateStart (privateDGROUP + 0x3d4)
#define deactivateRelease (privateDGROUP + 0x3f2)
#define deactivateReady (privateDGROUP + 0x419)
#define paletteChangedCalled (privateDGROUP + 0x437)
#define paletteChangedCalling (privateDGROUP + 0x456)
#define paletteChangedSame (privateDGROUP + 0x476)
#define paletteChangedInvalidate (privateDGROUP + 0x496)
#define memoryLowMessage (privateDGROUP + 0x4c8)
#define initInstanceMainClass (privateDGROUP + 0x4dc)
#define initInstanceMainTitle (privateDGROUP + 0x4e3)
#define initInstancePropertyIndex (privateDGROUP + 0x4eb)
#define initInstanceRibbonTitle (privateDGROUP + 0x4f1)
#define initInstanceRibbonClass (privateDGROUP + 0x503)
#define initInstanceRootTitle (privateDGROUP + 0x510)
#define initInstanceRootClass (privateDGROUP + 0x523)
#define initApplicationIcon (privateDGROUP + 0x52b)
#define initApplicationRootClass (privateDGROUP + 0x532)
#define initApplicationGenericClass (privateDGROUP + 0x53a)
#define initApplicationRibbonClass (privateDGROUP + 0x548)
#define winMainClassName (privateDGROUP + 0x555)
#define notInstalledPattern (privateDGROUP + 0x55d)
#define notInstalledMessage (privateDGROUP + 0x568)
#define winMainPropertyIndex (privateDGROUP + 0x59c)
#define optionSound (privateDGROUP + 0x5a2)
#define optionAutotrack (privateDGROUP + 0x5a8)
#define appSection0 (privateDGROUP + 0x5b2)
#define optionMusic (privateDGROUP + 0x5b9)
#define appSection1 (privateDGROUP + 0x5bf)
#define optionEffects (privateDGROUP + 0x5c6)
#define appSection2 (privateDGROUP + 0x5ce)
#define optionEvents (privateDGROUP + 0x5d5)
#define appSection3 (privateDGROUP + 0x5dc)
#define optionMessages (privateDGROUP + 0x5e3)
#define appSection4 (privateDGROUP + 0x5ec)
#define optionSilly (privateDGROUP + 0x5f3)
#define appSection5 (privateDGROUP + 0x5f9)
#define cancelledMessage (privateDGROUP + 0x600)
#define mapButtonProfile (privateDGROUP + 0x612)
#define appSection6 (privateDGROUP + 0x622)
#define yardButtonProfile (privateDGROUP + 0x629)
#define appSection7 (privateDGROUP + 0x63a)
#define acceleratorResource (privateDGROUP + 0x641)
#define releasingCaptureMessage (privateDGROUP + 0x652)
#define profileOne0 (privateDGROUP + 0x66a)
#define profileZero0 (privateDGROUP + 0x66c)
#define optionAutotrackAgain (privateDGROUP + 0x66e)
#define appSection8 (privateDGROUP + 0x678)
#define profileOne1 (privateDGROUP + 0x67f)
#define profileZero1 (privateDGROUP + 0x681)
#define optionMusicAgain (privateDGROUP + 0x683)
#define appSection9 (privateDGROUP + 0x689)
#define profileOne2 (privateDGROUP + 0x690)
#define profileZero2 (privateDGROUP + 0x692)
#define optionEffectsAgain (privateDGROUP + 0x694)
#define appSection10 (privateDGROUP + 0x69c)
#define profileOne3 (privateDGROUP + 0x6a3)
#define profileZero3 (privateDGROUP + 0x6a5)
#define optionEventsAgain (privateDGROUP + 0x6a7)
#define appSection11 (privateDGROUP + 0x6ae)
#define profileOne4 (privateDGROUP + 0x6b5)
#define profileZero4 (privateDGROUP + 0x6b7)
#define optionMessagesAgain (privateDGROUP + 0x6b9)
#define appSection12 (privateDGROUP + 0x6c2)
#define profileOne5 (privateDGROUP + 0x6c9)
#define profileZero5 (privateDGROUP + 0x6cb)
#define optionSillyAgain (privateDGROUP + 0x6cd)
#define appSection13 (privateDGROUP + 0x6d3)
#define mapButtonProfileAgain (privateDGROUP + 0x6da)
#define integerFormat0 (privateDGROUP + 0x6ea)
#define appSection14 (privateDGROUP + 0x6ed)
#define yardButtonProfileAgain (privateDGROUP + 0x6f4)
#define integerFormat1 (privateDGROUP + 0x705)
#define appSection15 (privateDGROUP + 0x708)
extern unsigned char near doKeyDownCheatBuffer[4];


extern int near mapUserButton[8];
  /* scaffold reference for pool word BE74 (segment 10, SEGMENT_REPRESENTATIVE) */
extern int far match_position;  /* scaffold reference for pool word BE76 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Dx8;  /* scaffold reference for pool word BE78 (segment 8, MAPSYM_SITE_NAME) */
extern int far match_length;  /* scaffold reference for pool word BE7C (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Dy8;  /* scaffold reference for pool word BE7E (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far yardUserButton;  /* scaffold reference for pool word BE88 (segment 10, SEGMENT_REPRESENTATIVE) */
extern int far paletteFlag;  /* scaffold reference for pool word BE8A (segment 10, SEGMENT_REPRESENTATIVE) */
extern int far editBuf;  /* scaffold reference for pool word BE8E (segment 10, MAPSYM_SITE_NAME) */
extern int far pack_buf;  /* scaffold reference for pool word BE90 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far ncbSegment;  /* scaffold reference for pool word BE92 (segment 9, MAPSYM_SITE_NAME) */
extern int far ncbOffset;  /* scaffold reference for pool word BE94 (segment 9, MAPSYM_SITE_NAME) */
extern int far ncbTail;  /* scaffold reference for pool word BE96 (segment 9, MAPSYM_SITE_NAME) */
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
void far pool_data_ProcessPost(void);
void far pool_data_NetworkSend(void);
void far pool_data_UpdateWindows(void);
void far pool_data_MYTIMERFUNC(void);
void far pool_data_MAINWNDPROC(void);
void far pool_data_InitApplication(void);
void far pool_data_WINMAIN(void);
void far pool_stub_NetBIOSPost(void);
void far pool_stub_ProcessPost(void);
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
void far PatchColorArrays(void);

void far pascal __export MYTIMERFUNC(int window, int message, int timerId,
                            unsigned int lowTime, unsigned int highTime)
{
    struct MSG timerMessage;
    struct WinRect invalid;
    volatile int delay;
    int status;
    register int innerCount;
    register int outerCount;
    int loopValue;
    long far * volatile messagePointer;
    char statusText[10];

    innerCount = 0;
    outerCount = 0;
    if (mainRootWnd == 0)
        return;

    if (IsIconic(mainRootWnd)) {
        if (GamePaused) {
            volatile unsigned int normalIcon;
            normalIcon = LoadIcon(hInst, iconNormal);
            if (GetClassWord(mainRootWnd, -14) != normalIcon) {
                SetClassWord(mainRootWnd, -14, LoadIcon(hInst, iconPaused));
                InvalidateRect(mainRootWnd, 0, 1);
            }
        } else if (IsGameOver) {
            if (BlackWon) {
                volatile unsigned int wonIcon;
                wonIcon = LoadIcon(hInst, iconWon);
                if (GetClassWord(mainRootWnd, -14) != wonIcon) {
                    SetClassWord(mainRootWnd, -14,
                                 LoadIcon(hInst, timerIconBlackWon));
                    InvalidateRect(mainRootWnd, 0, 1);
                }
            } else {
                volatile unsigned int lostIcon;
                lostIcon = LoadIcon(hInst, iconLost);
                if (GetClassWord(mainRootWnd, -14) != lostIcon) {
                    SetClassWord(mainRootWnd, -14,
                                 LoadIcon(hInst, timerIconRedLost));
                    InvalidateRect(mainRootWnd, 0, 1);
                }
            }
        } else {
            volatile unsigned int randomIcon;
            status = SRand1(7);
            sprintf(statusText, timerFormat, status);
            randomIcon = LoadIcon(hInst, statusText);
            if (GetClassWord(mainRootWnd, -14) != randomIcon) {
                SetClassWord(mainRootWnd, -14, LoadIcon(hInst, statusText));
                InvalidateRect(mainRootWnd, 0, 1);
            }
        }
    }

    ++timerCallCount;
    messagePointer = &mapMessage;
    for (;;) {
        ++gameCycles;
    if (SimAntClientFlag) {
        if (ncbHead == ncbTail)
            goto status_update;
        ProcessPost((signed char)MeMoveMe);
    } else {
        if (GamePaused || (MeMoveMe && CurGameTool < 10)) {
            delay = SpeedDelayVals[GameSpeed];
            if (delay != -1 && delay != 0 && timerCallCount >= delay &&
                timerState02F4 == 0) {
                timerState02F4 = 1;
                timerCallCount = 0;
                DoAntSim();
                myServiceSong();
                timerState02F4 = 0;
            }
        }
        if (SimAntServerFlag)
            NetworkSend();
    }

    if (mainRootWnd && !IsIconic(mainRootWnd) && !activeAppFlag &&
        !(timerBusy & 7L)) {
        UpdateWindows();
        ++timerBusy;
    }

status_update:
    if (mainRootWnd && !IsIconic(mainRootWnd) && activeAppFlag) {
        if (win_IsWinOpen(0x2200)) {
            MSClipStart(win_hwnd[34]);
            if (TickCount() > mapMessageRemoveTime) {
                editMessage = 0L;
                mapMessage = 0L;
                win_FillObjRect(0x221f, ConvColor(12));
            } else if (*messagePointer != 0L) {
                font_SetFont(2);
                win_PrintfAtObj(0x221f, *messagePointer);
                font_SetFont(0);
            } else {
                win_FillObjRect(0x221f, ConvColor(12));
            }
            MSClipEnd();
        }
        UpdateYardMessage();
    }

        status = PeekMessage(&timerMessage, 0, 0x113, 0x113, 3);
        while (status) {
            loopValue = outerCount;
            ++timerCallCount;
            ++innerCount;
            status = PeekMessage(&timerMessage, 0, 0x113, 0x113, 3);
        }
        ++outerCount;
        myServiceSong();
        if (!mainRootWnd)
            break;
        if (innerCount >= 2 && (outerCount >= 3 || innerCount >= 3))
            break;
        if (GetAsyncKeyState(1) & 1)
            break;
    }
}
