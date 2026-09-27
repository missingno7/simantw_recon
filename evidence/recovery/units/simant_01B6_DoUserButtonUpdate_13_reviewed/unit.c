/* Candidate translation unit simant_01B6_DoUserButtonUpdate_12_scaffold_split: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _DoUserButtonUpdate, _SetUserButton, _ClearBookmarks, _DrawRibbonMessage, _HelpKeyDown, _DoNextWindow, _RedrawWindows, _DoDebugWin, _LoadFancyCursor, _SetFancyCursor, _InitInstance, _PatchColorArrays
 * SCAFFOLDED: unclaimed members _DoUserButton, _DoBookMark, _DoMouse, _DoMenuEntry, _AdjustWndMinMax, _ProcessPost, _UpdateWindows, MYTIMERFUNC are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

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
#define timerCallCount (*( unsigned int near *)(privateDGROUP + 0x1a4))
#define timerBusy (*( int near *)(privateDGROUP + 0x1a6))
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
void far pool_data_ProcessPost(void);
void far pool_data_NetworkSend(void);
void far pool_data_UpdateWindows(void);
void far pool_data_MYTIMERFUNC(void);
void far pool_data_MAINWNDPROC(void);
void far pool_data_InitApplication(void);
void far pool_data_WINMAIN(void);
void interrupt far NetBIOSPost(unsigned int segment, unsigned int savedDS, unsigned int savedDI, unsigned int savedSI, unsigned int savedBP, unsigned int savedSP, unsigned int offset);
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

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoUserButton)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoBookMark)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoMouse)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoMenuEntry)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_AdjustWndMinMax)
#pragma alloc_text(POOLSTUB_TEXT, pool_data_DoUserButton)
#pragma alloc_text(POOLSTUB_TEXT, pool_data_DoBookMark)
#pragma alloc_text(POOLSTUB_TEXT, pool_data_DoKeyDown)
#pragma alloc_text(POOLSTUB_TEXT, pool_data_DoMouse)
#pragma alloc_text(POOLSTUB_TEXT, pool_data_ProcessPost)
#pragma alloc_text(POOLSTUB_TEXT, pool_data_NetworkSend)
#pragma alloc_text(POOLSTUB_TEXT, pool_data_UpdateWindows)
#pragma alloc_text(POOLSTUB_TEXT, pool_data_MYTIMERFUNC)
#pragma alloc_text(POOLSTUB_TEXT, pool_data_MAINWNDPROC)
#pragma alloc_text(POOLSTUB_TEXT, pool_data_InitApplication)
#pragma alloc_text(POOLSTUB_TEXT, pool_data_WINMAIN)
#pragma alloc_text(RUN10_TEXT, NetBIOSPost)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_ProcessPost)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_UpdateWindows)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_MYTIMERFUNC)
#pragma alloc_text(RUN2_TEXT, SetUserButton)
#pragma alloc_text(RUN3_TEXT, ClearBookmarks, DrawRibbonMessage)
#pragma alloc_text(RUN4_TEXT, HelpKeyDown)
#pragma alloc_text(RUN5_TEXT, DoNextWindow)
#pragma alloc_text(RUN6_TEXT, RedrawWindows, DoDebugWin)
#pragma alloc_text(RUN7_TEXT, LoadFancyCursor, SetFancyCursor)
#pragma alloc_text(RUN8_TEXT, InitInstance)
#pragma alloc_text(RUN9_TEXT, PatchColorArrays)

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
void far pool_stub_ProcessPost(void)
{
    volatile int t;

    t = ncbTail;
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
#undef hInst

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

void far pool_data_ProcessPost(void)
{
    char near * volatile literal;
    volatile int wordValue;
    volatile long longValue;
    literal = processPostServerName;
    literal = processPostClientName;
    wordValue = processPostState;
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

void far pool_data_InitApplication(void)
{
    char near * volatile literal;
    volatile int wordValue;
    volatile long longValue;
    literal = initApplicationIcon;
    literal = initApplicationRootClass;
    literal = initApplicationGenericClass;
    literal = initApplicationRibbonClass;
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
